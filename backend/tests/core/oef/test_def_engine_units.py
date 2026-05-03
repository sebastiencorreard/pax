"""
Unit tests for def_engine internals.

Covers individual commands, variable resolution helpers, condition evaluation,
find_def_path, and _call_pari — all exercised below the integration level.
"""

import re


from core.oef.def_engine import DefEngine, _call_pari
from core.oef.engine import find_def_path


# ── Helpers ────────────────────────────────────────────────────────────────────


def engine(seed: int = 1) -> DefEngine:
    return DefEngine(seed=seed)


# ── find_def_path ──────────────────────────────────────────────────────────────


class TestFindDefPath:
    def test_same_dir(self, tmp_path):
        oef = tmp_path / "exo.oef"
        def_ = tmp_path / "exo.def"
        oef.touch()
        def_.touch()
        assert find_def_path(str(oef)) == str(def_)

    def test_sibling_def_dir(self, tmp_path):
        src = tmp_path / "src"
        defdir = tmp_path / "def"
        src.mkdir()
        defdir.mkdir()
        oef = src / "exo.oef"
        def_ = defdir / "exo.def"
        oef.touch()
        def_.touch()
        assert find_def_path(str(oef)) == str(def_)

    def test_returns_none_when_absent(self, tmp_path):
        oef = tmp_path / "exo.oef"
        oef.touch()
        assert find_def_path(str(oef)) is None

    def test_same_dir_wins_over_sibling(self, tmp_path):
        src = tmp_path / "src"
        defdir = tmp_path / "def"
        src.mkdir()
        defdir.mkdir()
        oef = src / "exo.oef"
        same_dir_def = src / "exo.def"
        sibling_def = defdir / "exo.def"
        oef.touch()
        same_dir_def.touch()
        sibling_def.touch()
        assert find_def_path(str(oef)) == str(same_dir_def)


# ── _call_pari ─────────────────────────────────────────────────────────────────


class TestCallPari:
    def test_addition(self):
        assert _call_pari("5+1") == "6"

    def test_power(self):
        assert _call_pari("3^2") == "9"

    def test_float_result(self):
        assert _call_pari("10/4") == "2.5"

    def test_integer_float(self):
        assert _call_pari("sqrt(9)") == "3"

    def test_trailing_semicolon(self):
        assert _call_pari("2+3;") == "5"

    def test_unparseable_returns_input(self):
        result = _call_pari("not_an_expr!!!")
        assert result == "not_an_expr!!!"


# ── !values ────────────────────────────────────────────────────────────────────


class TestCmdValues:
    def test_identity_loop(self):
        e = engine()
        assert e._eval_cmd("values", "v for v=2 to 5") == "2,3,4,5"

    def test_expression_loop(self):
        e = engine()
        assert e._eval_cmd("values", "v*v for v=1 to 4") == "1,4,9,16"

    def test_single_iteration(self):
        e = engine()
        assert e._eval_cmd("values", "v for v=3 to 3") == "3"

    def test_loop_variable_restored_after(self):
        e = engine()
        e.ctx["v"] = "original"
        e._eval_cmd("values", "v for v=1 to 2")
        assert e.ctx.get("v") == "original"

    def test_loop_variable_removed_if_not_pre_existing(self):
        e = engine()
        e._eval_cmd("values", "v for v=1 to 2")
        assert "v" not in e.ctx

    def test_bad_syntax_returns_empty(self):
        e = engine()
        assert e._eval_cmd("values", "no for clause here") == ""


# ── !randint / !random ─────────────────────────────────────────────────────────


class TestCmdRandom:
    def test_randint_in_range(self):
        for seed in range(10):
            e = engine(seed)
            val = int(e._eval_cmd("randint", "1,10"))
            assert 1 <= val <= 10

    def test_randint_deterministic(self):
        assert engine(42)._eval_cmd("randint", "1,100") == engine(42)._eval_cmd(
            "randint", "1,100"
        )

    def test_random_in_range(self):
        e = engine(5)
        val = float(e._eval_cmd("random", "0,1"))
        assert 0.0 <= val <= 1.0


# ── !randitem / !shuffle ───────────────────────────────────────────────────────


class TestCmdListOps:
    def test_randitem_from_list(self):
        e = engine(7)
        assert e._eval_cmd("randitem", "a,b,c") == "b"

    def test_randitem_single(self):
        e = engine(1)
        assert e._eval_cmd("randitem", "only") == "only"

    def test_shuffle_preserves_items(self):
        e = engine(42)
        e.ctx["lst"] = "3,1,4,1,5"
        result = e._eval_cmd("shuffle", "$lst")
        assert sorted(result.split(",")) == sorted("3,1,4,1,5".split(","))

    def test_shuffle_deterministic(self):
        e1, e2 = engine(42), engine(42)
        e1.ctx["lst"] = e2.ctx["lst"] = "a,b,c,d"
        assert e1._eval_cmd("shuffle", "$lst") == e2._eval_cmd("shuffle", "$lst")

    def test_nonempty_items(self):
        e = engine()
        assert e._eval_cmd("nonempty", "items a,,b,") == "a,b"

    def test_nonempty_rows(self):
        e = engine()
        assert e._eval_cmd("nonempty", "rows a\t\tb") == "a\tb"

    def test_itemcnt(self):
        e = engine()
        assert e._eval_cmd("itemcnt", "a,b,c") == "3"

    def test_rowcnt(self):
        e = engine()
        assert e._eval_cmd("rowcnt", "a\tb\tc") == "3"


# ── !item / !row ───────────────────────────────────────────────────────────────


class TestCmdItemRow:
    def test_item_first(self):
        e = engine()
        assert e._eval_cmd("item", "1 of a,b,c") == "a"

    def test_item_second(self):
        e = engine()
        assert e._eval_cmd("item", "2 of a,b,c") == "b"

    def test_item_out_of_range(self):
        e = engine()
        assert e._eval_cmd("item", "9 of a,b,c") == ""

    def test_item_tab_separated(self):
        e = engine()
        assert e._eval_cmd("item", "2 of x\ty\tz") == "y"

    def test_row_second(self):
        e = engine()
        assert e._eval_cmd("row", "2 of a\tb\tc") == "b"

    def test_row_out_of_range(self):
        e = engine()
        assert e._eval_cmd("row", "5 of a\tb") == ""


# ── !replace / !append ────────────────────────────────────────────────────────


class TestCmdStringOps:
    def test_replace_basic(self):
        e = engine()
        assert e._eval_cmd("replace", "internal x by y in exy") == "eyy"

    def test_replace_no_match(self):
        e = engine()
        assert e._eval_cmd("replace", "internal z by y in abc") == "abc"

    def test_append_to_existing(self):
        e = engine()
        e.ctx["mylist"] = "a,b"
        assert e._eval_cmd("append", "item c to $mylist") == "a,b\tc"

    def test_append_to_empty_var(self):
        e = engine()
        e.ctx["empty"] = ""
        assert e._eval_cmd("append", "item x to $empty") == "x"

    def test_lower(self):
        e = engine()
        assert e._eval_cmd("lower", "ABC") == "abc"

    def test_upper(self):
        e = engine()
        assert e._eval_cmd("upper", "abc") == "ABC"

    def test_trim(self):
        e = engine()
        assert e._eval_cmd("trim", "  hello  ") == "hello"


# ── Variable resolution ────────────────────────────────────────────────────────


class TestVariableResolution:
    def test_indexed1_tab_separated(self):
        e = engine()
        e.ctx["lst"] = "A\tB\tC"
        m = re.match(r"\$\((\w+)\[([^\]]+)\]\)", "$(lst[3])")
        assert m is not None
        assert e._resolve_indexed1(m) == "C"

    def test_indexed1_comma_separated(self):
        e = engine()
        e.ctx["lst"] = "10,20,30"
        m = re.match(r"\$\((\w+)\[([^\]]+)\]\)", "$(lst[2])")
        assert m is not None
        assert e._resolve_indexed1(m) == "20"

    def test_indexed1_out_of_range(self):
        e = engine()
        e.ctx["lst"] = "a,b"
        m = re.match(r"\$\((\w+)\[([^\]]+)\]\)", "$(lst[5])")
        assert m is not None
        assert e._resolve_indexed1(m) == ""

    def test_indexed1_empty_var(self):
        e = engine()
        m = re.match(r"\$\((\w+)\[([^\]]+)\]\)", "$(missing[1])")
        assert m is not None
        assert e._resolve_indexed1(m) == ""

    def test_indexed2_matrix(self):
        e = engine()
        e.ctx["mat"] = "a;b\tc;d"  # row1: a;b  row2: c;d
        m = re.match(r"\$\((\w+)\[([^\]]+);([^\]]+)\]\)", "$(mat[2;1])")
        assert m is not None
        assert e._resolve_indexed2(m) == "c"

    def test_dollar_bracket_arithmetic(self):
        e = engine()
        e.ctx["x"] = "3"
        assert e._eval_dollar_bracket("$[$x*2]") == "6"

    def test_subst_paren_var(self):
        e = engine()
        e.ctx["foo"] = "bar"
        assert e._subst("$(foo)") == "bar"

    def test_subst_dollar_var(self):
        e = engine()
        e.ctx["n"] = "5"
        assert e._subst("$n items") == "5 items"


# ── Condition evaluation ───────────────────────────────────────────────────────


class TestEvalCondition:
    def test_ifval_less_than_true(self):
        e = engine()
        assert e._eval_condition("ifval", "3<5") is True

    def test_ifval_less_than_false(self):
        e = engine()
        assert e._eval_condition("ifval", "5<3") is False

    def test_ifval_equals(self):
        e = engine()
        assert e._eval_condition("ifval", "4=4") is True

    def test_if_string_equal_true(self):
        e = engine()
        assert e._eval_condition("if", "hello=hello") is True

    def test_if_string_equal_false(self):
        e = engine()
        assert e._eval_condition("if", "hello=world") is False

    def test_ifval_with_variable(self):
        e = engine()
        e.ctx["val"] = "7"
        assert e._eval_condition("ifval", "$val>5") is True

    def test_ifval_zero_is_falsy(self):
        e = engine()
        assert e._eval_condition("ifval", "0") is False


# ── !makelist ─────────────────────────────────────────────────────────────────


class TestCmdMakelist:
    def test_simple_tab_separated(self):
        e = engine()
        result = e._eval_cmd("makelist", "v for v=1 to 3")
        assert result == "1\t2\t3"

    def test_multi_column_row(self):
        e = engine()
        result = e._eval_cmd("makelist", "v,-v for v=1 to 3")
        assert result == "1,-1\t2,-2\t3,-3"

    def test_expression(self):
        e = engine()
        result = e._eval_cmd("makelist", "v*v for v=1 to 4")
        assert result == "1\t4\t9\t16"

    def test_row_access_after_makelist(self):
        e = engine()
        e.ctx["mat"] = e._eval_cmd("makelist", "v,-v for v=2 to 4")
        assert e._subst("$(mat[2])") == "3,-3"

    def test_loop_var_removed_after(self):
        e = engine()
        e._eval_cmd("makelist", "v for v=1 to 3")
        assert "v" not in e.ctx


# ── !positionof ───────────────────────────────────────────────────────────────


class TestCmdPositionof:
    def test_found_first(self):
        e = engine()
        assert e._eval_cmd("positionof", "item a in a,b,c") == "1"

    def test_found_middle(self):
        e = engine()
        assert e._eval_cmd("positionof", "item b in a,b,c") == "2"

    def test_not_found(self):
        e = engine()
        assert e._eval_cmd("positionof", "item z in a,b,c") == "0"

    def test_tab_separated(self):
        e = engine()
        e.ctx["lst"] = "x\ty\tz"
        assert e._eval_cmd("positionof", "item y in $lst") == "2"

    def test_numeric_value(self):
        e = engine()
        e.ctx["lst"] = "1,2,3,4"
        assert e._eval_cmd("positionof", "item 3 in $lst") == "3"


# ── !randrow ──────────────────────────────────────────────────────────────────


class TestCmdRandrow:
    def test_returns_one_row(self):
        e = engine(1)
        e.ctx["mat"] = "a,1\tb,2\tc,3"
        result = e._eval_cmd("randrow", "$mat")
        assert result in ("a,1", "b,2", "c,3")

    def test_deterministic(self):
        e1, e2 = engine(42), engine(42)
        e1.ctx["mat"] = e2.ctx["mat"] = "x\ty\tz"
        assert e1._eval_cmd("randrow", "$mat") == e2._eval_cmd("randrow", "$mat")

    def test_empty_returns_empty(self):
        e = engine()
        assert e._eval_cmd("randrow", "") == ""


# ── !sort ─────────────────────────────────────────────────────────────────────


class TestCmdSort:
    def test_integers(self):
        e = engine()
        assert e._eval_cmd("sort", "numeric items 3,1,2") == "1,2,3"

    def test_floats(self):
        e = engine()
        assert e._eval_cmd("sort", "numeric items 3.5,1.2,2.8") == "1.2,2.8,3.5"

    def test_fractions(self):
        e = engine()
        e.ctx["v"] = "3/2,7/4,35/16,15/8"
        result = e._eval_cmd("sort", "numeric items $v")
        assert result == "3/2,7/4,15/8,35/16"

    def test_negatives(self):
        e = engine()
        assert e._eval_cmd("sort", "numeric list -1,3,-2,0") == "-2,-1,0,3"

    def test_range_slice_then_sort(self):
        # $(v[1..4]) extracts "5,3,4,1", then sort → "1,3,4,5"
        e = engine()
        e.ctx["v"] = "5,3,4,1,2"
        result = e._eval_cmd("sort", "numeric items $(v[1..4])")
        assert result == "1,3,4,5"


# ── !mathsubst ────────────────────────────────────────────────────────────────


class TestCmdMathsubst:
    def test_basic(self):
        e = engine()
        e.ctx["expr"] = "2*x+1"
        assert e._eval_cmd("mathsubst", "x=(3) in $expr") == "2*(3)+1"

    def test_already_has_parens(self):
        e = engine()
        e.ctx["expr"] = "x^2+x"
        assert e._eval_cmd("mathsubst", "x=(a+b) in $expr") == "(a+b)^2+(a+b)"

    def test_no_match(self):
        e = engine()
        e.ctx["expr"] = "y+1"
        assert e._eval_cmd("mathsubst", "x=(3) in $expr") == "y+1"


# ── !listuniq ─────────────────────────────────────────────────────────────────


class TestCmdListuniq:
    def test_removes_duplicates(self):
        e = engine()
        assert e._eval_cmd("listuniq", "a,b,a,c,b") == "a,b,c"

    def test_preserves_order(self):
        e = engine()
        assert e._eval_cmd("listuniq", "c,a,b,c,a") == "c,a,b"

    def test_no_duplicates_unchanged(self):
        e = engine()
        assert e._eval_cmd("listuniq", "x,y,z") == "x,y,z"

    def test_tab_separated(self):
        e = engine()
        assert e._eval_cmd("listuniq", "a\tb\ta\tc") == "a\tb\tc"


# ── !declosing ────────────────────────────────────────────────────────────────


class TestCmdDeclosing:
    def test_removes_parens(self):
        e = engine()
        assert e._eval_cmd("declosing", "(x+1)") == "x+1"

    def test_removes_brackets(self):
        e = engine()
        assert e._eval_cmd("declosing", "[1,2,3]") == "1,2,3"

    def test_removes_braces(self):
        e = engine()
        assert e._eval_cmd("declosing", "{a,b}") == "a,b"

    def test_no_brackets_unchanged(self):
        e = engine()
        assert e._eval_cmd("declosing", "x+1") == "x+1"

    def test_mismatched_unchanged(self):
        e = engine()
        assert e._eval_cmd("declosing", "(x+1]") == "(x+1]"


# ── !nospace / !getopt / !word / !column / !charcnt ──────────────────────────


class TestCmdMiscNew:
    def test_nospace(self):
        e = engine()
        assert e._eval_cmd("nospace", "a b  c") == "abc"

    def test_getopt_found(self):
        e = engine()
        e.ctx["opts"] = "audio=file.mp3 image=img.png"
        assert e._eval_cmd("getopt", "audio in $opts") == "file.mp3"

    def test_getopt_not_found(self):
        e = engine()
        assert e._eval_cmd("getopt", "missing in key=val") == ""

    def test_getdef_same_as_getopt(self):
        e = engine()
        e.ctx["defs"] = "title=My Title size=3"
        assert e._eval_cmd("getdef", "title in $defs") == "My"

    def test_word_first(self):
        e = engine()
        assert e._eval_cmd("word", "1 of hello world foo") == "hello"

    def test_word_second(self):
        e = engine()
        assert e._eval_cmd("word", "2 of hello world foo") == "world"

    def test_word_out_of_range(self):
        e = engine()
        assert e._eval_cmd("word", "9 of hello") == ""

    def test_column_first(self):
        e = engine()
        e.ctx["mat"] = "a;b;c\td;e;f"
        assert e._eval_cmd("column", "1 of $mat") == "a,d"

    def test_column_second(self):
        e = engine()
        e.ctx["mat"] = "a;b;c\td;e;f"
        assert e._eval_cmd("column", "2 of $mat") == "b,e"

    def test_charcnt(self):
        e = engine()
        assert e._eval_cmd("charcnt", "hello") == "5"

    def test_charcnt_empty(self):
        e = engine()
        assert e._eval_cmd("charcnt", "") == "0"


# ── $(var[n..m]) range slice ──────────────────────────────────────────────────


class TestRangeSlice:
    def test_full_range(self):
        e = engine()
        e.ctx["v"] = "a,b,c,d"
        assert e._subst("$(v[1..4])") == "a,b,c,d"

    def test_partial_range(self):
        e = engine()
        e.ctx["v"] = "a,b,c,d,e"
        assert e._subst("$(v[2..4])") == "b,c,d"

    def test_tab_separated(self):
        # Range slice always returns comma-joined items regardless of source separator
        e = engine()
        e.ctx["v"] = "x\ty\tz"
        assert e._subst("$(v[1..2])") == "x,y"

    def test_single_element(self):
        e = engine()
        e.ctx["v"] = "a,b,c"
        assert e._subst("$(v[2..2])") == "b"
