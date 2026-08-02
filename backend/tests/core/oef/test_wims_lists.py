"""Socle de découpage WIMS — conformité au source C.

Chaque cas est tiré de la lecture de `liblines.c` ; les commentaires citent la
règle plutôt que le comportement attendu, pour qu'un écart futur se juge
contre le C et non contre ce fichier.
"""

import pytest

from core.oef.def_engine.wims_lists import (
    cutitems,
    cutlines,
    cutrows,
    find_item_end,
    find_matching,
    find_word_end,
    find_word_start,
    fnd_item,
    fnd_line,
    itemchr,
    itemnum,
    linenum,
    lines2rows,
    rows2lines,
    strparstr,
)


class TestFindMatching:
    def test_simple(self):
        assert find_matching("a]", 0, "]") == 1
        assert find_matching("abc]", 0, "]") == 3

    def test_nested_same_kind(self):
        assert find_matching("[x]]", 0, "]") == 3

    def test_nested_other_kinds(self):
        assert find_matching("(a[b]c)]", 0, "]") == 7

    def test_crossed_pairs_have_no_match(self):
        """Les trois compteurs sont tenus **simultanément** : le premier
        fermant qui passe sous zéro doit être celui qu'on cherche, les autres
        compteurs étant retombés. `[a)b]` n'a donc pas de `]` appariant."""
        assert find_matching("a)b]", 0, "]") == -1

    def test_unclosed(self):
        assert find_matching("abc", 0, "]") == -1
        assert find_matching("[abc", 0, "]") == -1

    def test_wrong_closer_first(self):
        assert find_matching("a}b]", 0, "]") == -1


class TestStrparstr:
    def test_top_level_only(self):
        assert strparstr("a,b", ",") == 1
        assert strparstr("[a,b],c", ",") == 5

    def test_all_three_pair_kinds_protect(self):
        assert strparstr("(a,b),c", ",") == 5
        assert strparstr("{a,b},c", ",") == 5

    def test_absent_separator_returns_length(self):
        assert strparstr("abc", ",") == 3

    def test_unbalanced_opener_falls_back_to_naive_search(self):
        """Sur un ouvrant non apparié, WIMS abandonne la protection et retombe
        sur un `strstr` **depuis le début du balayage** — c'est ce qui permet à
        une valeur aux crochets déséquilibrés de se découper quand même."""
        assert strparstr("[a,b", ",") == 2

    def test_unbalanced_and_no_separator_returns_length(self):
        assert strparstr("[ab", ",") == 3

    def test_start_offset(self):
        assert strparstr("a,b,c", ",", 2) == 3

    def test_multichar_separator(self):
        assert strparstr("a..b", "..") == 1


class TestItemnum:
    def test_empty_is_zero(self):
        assert itemnum("") == 0

    def test_plain(self):
        assert itemnum("a,b,c") == 3
        assert itemnum("a") == 1

    def test_empty_items_count(self):
        """`!nonempty items` n'existerait pas si `itemcnt` les ignorait."""
        assert itemnum("a,,b") == 3
        assert itemnum("a,") == 2
        assert itemnum(",a") == 2
        assert itemnum(",") == 2

    def test_brackets_protect(self):
        assert itemnum("[a,b],[c,d]") == 2
        assert itemnum("(1,2),(3,4)") == 2

    def test_enclosing_pair_is_not_unwrapped(self):
        """Il n'y a **aucun** déballage : `[0,4,3.5]` est un item, pas trois.
        Une valeur à lire comme une liste est déballée en amont par
        `!declosing`."""
        assert itemnum("[0,4,3.5]") == 1

    def test_tab_is_not_a_separator(self):
        """L'axiome : aucune primitive de `liblines.c` ne mentionne `\\t`."""
        assert itemnum("a\tb") == 1
        assert itemnum("a,\tb") == 2
        assert itemnum("0,r,u,rru,\tull,lld") == 6


class TestFndItem:
    def test_one_indexed(self):
        assert fnd_item("a,b,c", 1) == "a"
        assert fnd_item("a,b,c", 3) == "c"

    def test_out_of_range_is_empty(self):
        assert fnd_item("a,b", 3) == ""
        assert fnd_item("a,b", 0) == ""
        assert fnd_item("", 1) == ""

    def test_borders_are_trimmed(self):
        assert fnd_item("  a  ,  b  ", 1) == "a"
        assert fnd_item("a,\tb", 2) == "b"

    def test_inside_is_untouched(self):
        """Le cœur du correctif flydraw : une tabulation *interne* survit,
        c'est elle qui sépare deux commandes d'une même figure."""
        assert fnd_item("[p red,1\tp red,2],x", 1) == "[p red,1\tp red,2]"

    def test_empty_item(self):
        assert fnd_item("a,,b", 2) == ""


class TestCutitems:
    def test_matches_fnd_item(self):
        s = "  a , [b,c] ,, d\t"
        assert cutitems(s) == [fnd_item(s, i) for i in range(1, itemnum(s) + 1)]

    def test_empty_string(self):
        assert cutitems("") == []

    def test_trailing_empty_item_is_kept(self):
        """La nuance assumée face au `cutitems` du C.

        `_cutit_` s'arrête sur `*pp` et perd un dernier item vide ; `itemnum`
        et `fnd_item`, eux, le voient (`"a,"` = 2 items). Nos appelants
        modélisent cette paire-là — `!item -1 of "a,"` doit rendre le vide.
        """
        assert cutitems("a,") == ["a", ""]
        assert cutitems("a,") == [fnd_item("a,", i) for i in (1, 2)]
        assert itemnum("a,") == 2


class TestItemchr:
    def test_membership(self):
        assert itemchr("a,b,c", "b")
        assert itemchr("a,b,c", "a")
        assert itemchr("a,b,c", "c")

    def test_absent(self):
        assert not itemchr("a,b,c", "d")

    def test_empty_needle(self):
        assert not itemchr("a,b", "")

    def test_spaces_around_borders_ignored(self):
        assert itemchr("a , b , c", "b")

    def test_substring_needs_item_borders(self):
        assert not itemchr("abc,d", "b")
        assert not itemchr("ab,cd", "a")

    def test_no_bracket_protection(self):
        """`itemchr` est une recherche de sous-chaîne encadrée, pas une égalité
        item à item : `a` n'est pas un item de `[a,b]`, son voisin de gauche
        étant `[`."""
        assert not itemchr("[a,b]", "a")

    def test_bracketed_item_is_found_whole(self):
        assert itemchr("[a,b],[c,d]", "[a,b]")


class TestLines:
    def test_count(self):
        assert linenum("a\nb\nc") == 3
        assert linenum("") == 0
        assert linenum("a") == 1

    def test_trailing_newline_adds_no_line(self):
        assert linenum("a\nb\n") == 2

    def test_leading_newline_makes_an_empty_first_line(self):
        assert linenum("\na") == 2
        assert fnd_line("\na", 1) == ""

    def test_fnd_line_does_not_trim(self):
        assert fnd_line("  a  \nb", 1) == "  a  "

    def test_out_of_range(self):
        assert fnd_line("a\nb", 5) == ""

    def test_cutlines(self):
        assert cutlines("a\nb\n") == ["a", "b"]


class TestRows2Lines:
    def test_converts_top_level_semicolons(self):
        assert rows2lines("a;b;c") == ("a\nb\nc", 2)

    def test_no_op_when_newlines_present(self):
        """La présence d'un `\\n` suffit à ne rien faire : la valeur est déjà
        en lignes."""
        assert rows2lines("a;b\nc") == ("a;b\nc", 0)

    def test_brackets_protect(self):
        out, n = rows2lines("[a;b];c")
        assert (out, n) == ("[a;b]\nc", 1)

    def test_named_entity_is_not_a_separator(self):
        out, n = rows2lines("&alpha;x;y")
        assert (out, n) == ("&alpha;x\ny", 1)

    def test_numeric_entity_is_not_a_separator(self):
        out, n = rows2lines("&#44;x;y")
        assert (out, n) == ("&#44;x\ny", 1)

    def test_count_is_reported(self):
        """À zéro, `!nonempty rows` bascule sur les lignes."""
        assert rows2lines("abc")[1] == 0

    def test_lines2rows_is_the_inverse_without_protection(self):
        assert lines2rows("a\nb\nc") == "a;b;c"

    def test_cutrows(self):
        assert cutrows("a,b;c,d") == ["a,b", "c,d"]


class TestWordHelpers:
    def test_word_start_skips_wims_spaces_only(self):
        assert find_word_start("  \t\n\ra") == 5
        # `myisspace` est plus étroit que `str.isspace` : \v n'en est pas.
        assert find_word_start("\va") == 0

    def test_word_end(self):
        assert find_word_end("abc def") == 3
        assert find_word_end("abc") == 3


class TestFindItemEnd:
    @pytest.mark.parametrize("s,expected", [
        ("a,b", 1),
        ("[a,b],c", 5),
        ("abc", 3),
        ("", 0),
    ])
    def test_is_strparstr_on_comma(self, s, expected):
        assert find_item_end(s) == expected == strparstr(s, ",")
