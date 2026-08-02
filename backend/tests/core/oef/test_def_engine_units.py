"""
Unit tests for def_engine internals.

Covers individual commands, variable resolution helpers, condition evaluation,
find_def_path, _call_pari, _call_maxima (SymPy backend), and _expr_to_latex.
"""

import re


from core.oef.def_engine import (
    DefEngine,
    _call_maxima,
    _call_pari,
    _close_inline_math,
    _expr_to_latex,
)
from core.oef.engine import find_def_path
from core.oef.def_engine.slib import _fr_cardinal, _ecriture_lettre


class TestEcritureLettre:
    def test_french_cardinal_words(self):
        cases = {
            0: "zéro", 7: "sept", 15: "quinze", 21: "vingt-et-un",
            60: "soixante", 70: "soixante-dix", 71: "soixante-et-onze",
            80: "quatre-vingts", 81: "quatre-vingt-un", 90: "quatre-vingt-dix",
            91: "quatre-vingt-onze", 100: "cent", 200: "deux-cents",
            201: "deux-cent-un", 1000: "mille", 1000000: "un-million",
            7060000: "sept-millions-soixante-mille",
        }
        for n, expected in cases.items():
            assert _fr_cardinal(n) == expected

    def test_ecriturelettre_single_and_list(self):
        assert _ecriture_lettre("7") == "sept"
        assert _ecriture_lettre("[7,60]") == "sept,soixante"

    def test_ecriturelettre_falls_back_for_non_french(self):
        # en/it and options aren't ported natively → None signals fallback.
        assert _ecriture_lettre("5,en") is None
        assert _ecriture_lettre("4,fr,[type=ord]") is None


# ── Helpers ────────────────────────────────────────────────────────────────────


def engine(seed: int = 1) -> DefEngine:
    return DefEngine(seed=seed)


class TestColumnAndRangeSlice:
    """Regression for liaison3's correspond table (empty before the fix)."""

    def test_range_slice_with_to(self):
        e = engine()
        e.ctx["val30"] = "3,4,2,5,8,7,1,6"
        e.ctx["val7"] = "3"
        assert e._subst("$(val30[1 to $val7])") == "3,4,2"
        assert e._subst("$(val30[1..3])") == "3,4,2"

    def test_column_single_index_vector(self):
        e = engine()
        # A single column → that column's cells across rows, comma-joined.
        assert e._cmd_column("3 of a,b,c;d,e,f") == "c,f"

    def test_column_multiple_indices_submatrix(self):
        e = engine()
        # Several columns → sub-matrix preserving rows (newline-joined), which
        # callers translate to ``;`` (liaison3's correspond pairs).
        assert e._cmd_column("3,1,2 of a,b,c;d,e,f") == "c,a,b\nf,d,e"


class TestResolveAnalyzeExpected:
    """Regression for ineqva1interv: `issametext` suffix matched as `sametext`,
    leaving the captured value as the leftover "is"."""

    def _df(self, **sections):
        from types import SimpleNamespace
        return SimpleNamespace(sections={k: v for k, v in sections.items()})

    def test_issametext_not_captured_as_is(self):
        from core.oef.def_parser import IfBlock
        e = engine()
        # `\({\cup}\) issametext $val40`: literal (parenthesised) operand, must
        # resolve to "" — never the suffix "is" of "issametext".
        cond = r"(\({\cup}\) issametext $val40) and ($val46=0)"
        df = self._df(postdef=[IfBlock(kind="if", condition=cond)], test=[])
        assert e._resolve_analyze_expected("val40", df) == ""

    def test_valn_reference_still_resolves(self):
        from core.oef.def_parser import IfBlock
        e = engine()
        e.ctx["val20"] = r"\(\rbrack\)"
        df = self._df(test=[IfBlock(kind="if", condition="($val20 issametext $val22)")])
        assert e._resolve_analyze_expected("val22", df) == r"\(\rbrack\)"

    def test_empty_math_normalised(self):
        from core.oef.def_parser import IfBlock
        e = engine()
        e.ctx["val34"] = r"\(\)"  # unused slot in a single-interval answer
        df = self._df(postdef=[IfBlock(kind="if", condition="($val34 issametext $val41)")])
        assert e._resolve_analyze_expected("val41", df) == ""


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


# ── _close_inline_math ─────────────────────────────────────────────────────────


class TestCloseInlineMath:
    def test_closes_plain_paren(self):
        # WIMS authors close with `)` not `\)`.
        assert _close_inline_math(r"\(-4) text") == r"\(-4\) text"

    def test_normalizes_equation(self):
        result = _close_inline_math(r"\(-3*x + 3 = -1*x+-5).")
        assert result == r"\(3 - 3 x = - x - 5\)."

    def test_preserves_already_closed_latex(self):
        # `\frac{}{}` content has backslashes — left untouched.
        assert (
            _close_inline_math(r"Already \(\frac{1}{2}\) ok")
            == r"Already \(\frac{1}{2}\) ok"
        )

    def test_no_math_unchanged(self):
        assert _close_inline_math("Plain text no math") == "Plain text no math"

    def test_handles_unparseable_content(self):
        # Variable substitutions not resolved → fallback to plain close
        assert _close_inline_math(r"\($x = $y\)") == r"\($x = $y\)"

    def test_renders_sqrt(self):
        # `sqrt(2)` must become `\sqrt{2}`, not literal italic "sqrt(2)".
        assert _close_inline_math(r"\(sqrt(2))") == r"\(\sqrt{2}\)"

    def test_maps_wims_bracket_macros(self):
        # WIMS `\lbracket`/`\rbracket` (balayage1 intervals) → `\lbrack`/`\rbrack`
        # (KaTeX-valid, inline). NOT literal `[`/`]`: those would be mistaken for
        # a column vector. The valid short `\lbrack`/`\rbrack` stays untouched.
        assert _close_inline_math(r"\(\lbracket1;2\rbracket\)") == r"\(\lbrack 1;2\rbrack \)"
        assert _close_inline_math(r"\(x \in \lbrack a;b \rbrack\)") == r"\(x \in \lbrack a;b \rbrack\)"

    def test_interval_not_turned_into_vector(self):
        # An interval `[1;2]` (from \lbracket…\rbracket) must stay inline, NOT
        # become a pmatrix column vector — only a *literal* `[a;b]` is a vector.
        from core.oef.def_engine.presentation import wims_matrices_to_latex
        out = wims_matrices_to_latex(_close_inline_math(r"\(\lbracket1;2\rbracket\)"))
        assert "pmatrix" not in out
        # …while a literal bracketed pair is still read as a column vector.
        assert "pmatrix" in wims_matrices_to_latex(r"\([7;5]\)")

    def test_skips_mathml_blocks(self):
        # A native <math> block (mathmlinput) is copied verbatim — its already
        # finalized \(…\) spans must not be re-scanned/mangled — while prose
        # WIMS math around it is still converted.
        out = _close_inline_math(
            r'A <math class="oef-mathml">X\(f(\)<input>\()\)Y</math> B \(K) C', "fr"
        )
        assert r'<math class="oef-mathml">X\(f(\)<input>\()\)Y</math>' in out
        assert r"B \(K\) C" in out  # prose outside the block still closed

    def test_idempotent_on_trailing_paren_span(self):
        # A mathmlinput cell like `f(reply2)` emits `\(f(\)<input>\()\)`. Re-running
        # the pass must keep `\()\)` intact (content `)`), not collapse it to an
        # empty `\(\)` and leak the `\)` as literal text (balayage1 conclusion).
        assert _close_inline_math(r"\()\)") == r"\()\)"
        assert _close_inline_math(r"\(f(\)X\()\)") == r"\(f(\)X\()\)"

    def test_closes_at_first_unmatched_paren(self):
        # WIMS find_matching: `\(K) sont (5;10)` closes right after `K`, it does
        # NOT swallow the trailing `) sont (5;10` (cercle1 statement bug).
        assert _close_inline_math(r"\(K) sont (5 ; 10).") == r"\(K\) sont (5 ; 10)."
        # A balanced inner group still closes on its own matching paren.
        assert _close_inline_math(r"\((a+b)) plus") == r"\(\left(a + b\right)\) plus"
        # Trailing text after a closed span isn't pulled into the math.
        assert _close_inline_math(r"\(2^3) et sqrt(3)") == r"\(2^{3}\) et sqrt(3)"

    def test_bare_word_unit_rendered_as_upright_text(self):
        # A bare word (unit/label) must NOT go through the CAS: `min`/`max`
        # would become \operatorname{Min/Max} (capitalised) and `cm` → `c m`.
        # WIMS renders it as upright normal text → wrap in \text{} (quizz 0505
        # ends with `\(min\)` for "minutes").
        assert _close_inline_math(r"\(min\).") == r"\(\text{min}\)."
        assert _close_inline_math(r"\(max)") == r"\(\text{max}\)"
        assert _close_inline_math(r"\(cm)") == r"\(\text{cm}\)"

    def test_single_letter_stays_italic_variable(self):
        # A lone letter is a variable, not a unit — left as-is (italic).
        assert _close_inline_math(r"\(x)") == r"\(x\)"

    def test_escaped_backslash_paren_left_alone(self):
        # `\\(` (escaped backslash) is a literal backslash, not a math opener
        # — e.g. JSON-escaped `\\(` inside a widget's data-config. It must not
        # be turned into KaTeX math (that shredded cof's correspond table).
        src = r'<span data-config="{&quot;a&quot;:&quot;\\(d_3\\) x&quot;}"></span>'
        assert _close_inline_math(src) == src

    def test_renders_sqrt_with_decimal_comma(self):
        # ecrdec1: a French decimal comma inside a function arg
        # (`sqrt(0,01)/2`) breaks SymPy as-is; retry reads digit,digit as a
        # decimal so it renders instead of leaking literal "sqrt".
        assert _close_inline_math(r"\(sqrt(0,01)/2)") == (
            r"\(\frac{\sqrt{0.01}}{2}\)"
        )

    def test_implicit_product_with_sqrt(self):
        # ecrdec1: an implicit product `)(` parses via implicit
        # multiplication and each sqrt renders — and the product is NOT
        # simplified to -4 (which would give the answer away).
        assert _close_inline_math(r"\((1+sqrt(5))(1-sqrt(5)))") == (
            r"\(\left(1 - \sqrt{5}\right) \left(1 + \sqrt{5}\right)\)"
        )

    def test_renders_fraction_of_sqrt(self):
        assert _close_inline_math(r"\(2sqrt(5)/sqrt(10))") == (
            r"\(\frac{2 \sqrt{5}}{\sqrt{10}}\)"
        )

    def test_special_color_to_katex_color(self):
        # WIMS `\special{color=NAME}` (TeX colour switch) → KaTeX `\color{NAME}`.
        # deve1 colours the factors in its worked solution.
        assert _close_inline_math(
            r"\(\special{color=green} -4 \special{color=black} (5)\)"
        ) == r"\(\color{green} -4 \color{black} (5)\)"
        # The colour value may be a resolved variable holding any CSS colour.
        assert _close_inline_math(r"\(\special{color=purple}x)") == r"\(\color{purple}x\)"


class TestFinalizeAnswerMath:
    """The single guarantee point: every answer's display fields have their
    WIMS inline math closed, whatever the type-specific code did upstream."""

    def _engine(self):
        e = DefEngine(seed=1)
        e.lang = "fr"
        return e

    def test_closes_label_choices_and_choice_expected(self):
        from core.oef.engine import AnswerDef

        # A `menu` answer whose inline math was historically left unclosed.
        a = AnswerDef(
            label=r"Choisis \(f(x))",
            expected=r"\(x^2)",
            answer_type="menu",
            options={"choices": [r"\(x^2)", r"\(x^3)"]},
            weight=1.0,
            input_name="reply1",
            logical_name="reply1",
        )
        self._engine()._finalize_answer_math([a])
        assert a.label == r"Choisis \(f{\left(x \right)}\)"
        assert a.expected == r"\(x^{2}\)"
        assert a.options["choices"] == [r"\(x^{2}\)", r"\(x^{3}\)"]

    def test_free_input_expected_left_raw(self):
        from core.oef.engine import AnswerDef

        # A numeric/litexp answer keeps `expected` raw for the CAS/numeric
        # checker — only label (and any choices) are closed.
        a = AnswerDef(
            label="", expected="(x+1)(x-1)", answer_type="litexp",
            options={}, weight=1.0, input_name="reply1", logical_name="reply1",
        )
        self._engine()._finalize_answer_math([a])
        assert a.expected == "(x+1)(x-1)"

    def test_idempotent_on_already_closed(self):
        from core.oef.engine import AnswerDef

        a = AnswerDef(
            label="", expected=r"\(x^{2}\)", answer_type="radio",
            options={"choices": [r"\(x^{2}\)"]}, weight=1.0,
            input_name="reply1", logical_name="reply1",
        )
        self._engine()._finalize_answer_math([a])
        assert a.expected == r"\(x^{2}\)"
        assert a.options["choices"] == [r"\(x^{2}\)"]


# ── slib helper commands ─────────────────────────────────────────────────────


class TestMathmlinput:
    def test_pmatrix_vector_renders_mathml(self):
        # `\begin{pmatrix} reply1 \\ reply2 \end{pmatrix}` (cercle1's centre
        # coordinates) → native MathML <mtable> + stretchy fences, NOT split
        # \(…\) spans that leak `\begin{pmatrix}` and break KaTeX.
        e = engine()
        out = e._mathmlinput_html(r"\begin{pmatrix} reply1 \\ reply2 \end{pmatrix}", {}, 5)
        assert out.startswith('<math class="oef-mathml"')
        assert "begin{pmatrix}" not in out
        assert "<mtable>" in out and out.count("<mtr>") == 2  # one row per cell
        assert '<mo fence="true" stretchy="true">(</mo>' in out
        assert out.count('class="oef-input"') == 2

    def test_left_right_vector_renders_mathml(self):
        e = engine()
        out = e._mathmlinput_html(r"\left( reply1 ; reply2 \right)", {}, 5)
        assert "<math" in out and "left(" not in out
        assert '<mo fence="true" stretchy="true">(</mo>' in out
        assert out.count('class="oef-input"') == 2

    def test_plain_exponent_stays_inline(self):
        # elassaoui3's `reply1^{reply2}` is not a container → inline sup, no MathML.
        e = engine()
        out = e._mathmlinput_html(r"reply1^{reply2}", {}, 5)
        assert "<math" not in out
        assert "<sup>" in out

    def test_frac_with_fields_renders_mathml(self):
        # `\frac{reply1}{reply2}` (frac3) → native <mfrac>, not split \(\frac{\).
        e = engine()
        out = e._mathmlinput_html(r"\frac{reply1}{reply2}", {}, 5)
        assert "<mfrac>" in out and "frac{" not in out
        assert out.count('class="oef-input"') == 2

    def test_frac_without_field_stays_katex(self):
        # A reply-free \frac is left for KaTeX (only the reply one becomes MathML).
        e = engine()
        out = e._mathmlinput_html(r"\frac{5}{4} = \frac{reply1}{reply2}", {}, 5)
        assert r"\(\frac{5}{4} =\)" in out  # static part KaTeX'd in annotation-xml
        assert "<mfrac>" in out

    def test_prefixed_interval_renders_mathml(self):
        # `I_c=\left[reply9;reply10\right]` (carlo) — prefix + bracket container.
        e = engine()
        out = e._mathmlinput_html(r"I_c=\left[reply9;reply10\right]", {}, 5)
        assert r"\(I_c=\)" in out and "left[" not in out
        assert '<mo fence="true" stretchy="true">[</mo>' in out
        assert out.count('class="oef-input"') == 2

    def test_cases_array_renders_mathml_table(self):
        # `\left.\begin{array}{lcl}…\end{array}\right\rbrace` (balayage) → mtable.
        e = engine()
        code = (r"\left.\begin{array}{lcl}f(reply2) &=& reply3 \\ "
                r"f(reply4) &=& reply5\end{array}\right \rbrace")
        out = e._mathmlinput_html(code, {}, 5)
        assert "<mtable>" in out and "begin{array}" not in out
        assert out.count('class="oef-input"') == 4

    def test_fields_in_annotation_xml(self):
        # Inputs sit in <annotation-xml> (WIMS' pattern) so the browser keeps
        # them interactive and the front's `.oef-input` binding finds them.
        e = engine()
        out = e._mathmlinput_html(r"\frac{reply1}{reply2}", {}, 5)
        assert 'annotation-xml encoding="application/xhtml+xml"' in out


class TestWimsListSplit:
    """Un item WIMS se termine à la virgule de profondeur zéro, un point.

    Le `;` a longtemps été traité ici comme une seconde frontière, parce que
    notre `!append item` séparait par des tabulations et que l'idiome
    `!translate \\t to ;` des QCM (brevet01) les transformait en `;`. Le
    producteur corrigé, ce `;` n'apparaît plus qu'à l'intérieur d'un choix —
    c'est de la donnée. `oef/embed.phtml` le confirme : il lit `replygood` en
    `!rows2lines` + `!distribute lines … into ts,tt`, puis prend `!item N of
    $tt`.
    """

    def test_semicolon_is_not_a_separator(self):
        e = engine()
        val = r"1|\(\large 25),0|\(\large 1000);0|\(\large 2,5 \times 10^{19})"
        assert e._split_wims_items(val) == [
            r"1|\(\large 25)",
            r"0|\(\large 1000);0|\(\large 2,5 \times 10^{19})",
        ]

    def test_protects_parens(self):
        e = engine()
        # La virgule de `\(2,5)` est protégée par la parenthèse ouvrante.
        assert e._split_wims_items(r"\(2,5),\(a;b)") == [r"\(2,5)", r"\(a;b)"]

    def test_semicolon_is_not_an_item_border(self):
        """`find_item_end` vaut `strparstr(p, ",")` : seule la virgule sépare.
        Le `;` est une frontière de *ligne de matrice*, et le prendre pour un
        item hachait le JavaScript des tableaux JSXGraph de `couf`."""
        e = engine()
        e.ctx["v"] = r"\(\large 25),\(\large 1000);\(\large 2,5 \times 10^{19})"
        assert e._subst(r"$(v[2])") == r"\(\large 1000);\(\large 2,5 \times 10^{19})"
        assert e._subst(r"$(v[3])") == ""


class TestCommutesom:
    def test_returns_permutation_list_canonical_first(self):
        # `slib/commutesom POLY,VAR` → liste des permutations commutatives des
        # monômes (comme WIMS), forme réduite canonique (degré décroissant) en
        # tête. Certains exercices l'utilisent via `!item N of` (oefremplacer2).
        e = engine()
        e._cmd_readproc("slib/commutesom 3*b+2-8*b-9,b")
        items = e.ctx["slib_out"].split(",")
        assert items[0].replace(" ", "") == "-5*b-7"  # canonique en tête
        assert set(items) == {"-5*b-7", "-7-5*b"}     # les 2 ordres
        assert "coeff" not in e.ctx["slib_out"]

    def test_sets_anyorder_flag(self):
        e = engine()
        e._cmd_readproc("slib/commutesom 3*x-x,x")
        assert e.ctx.get("_commutesom_anyorder") == "1"

    def test_falls_back_on_unparseable(self):
        e = engine()
        e._cmd_readproc("slib/commutesom not a poly @@,x")
        # No crash; returns the input unchanged.
        assert e.ctx["slib_out"] == "not a poly @@"


class TestSlibHelpers:
    def test_distribute_assigns_each_item(self):
        e = engine()
        e.ctx["src"] = "1,2,3"
        e._eval_cmd("distribute", "items $src into a,b,c")
        assert e.ctx["a"] == "1"
        assert e.ctx["b"] == "2"
        assert e.ctx["c"] == "3"

    def test_distribute_pads_short_lists(self):
        e = engine()
        e.ctx["src"] = "x,y"
        e._eval_cmd("distribute", "items $src into a,b,c")
        assert e.ctx["c"] == ""

    def test_distribute_protects_bracketed_commas(self):
        # Commas inside [...] must not split items — the editor slib passes
        # `[python,[code]],1,readonly …` and expects exactly 3 items, so that
        # `id` (here `b`) stays "1" and isn't polluted by the code's content.
        e = engine()
        e.ctx["src"] = "[python,[def f(): return 0]],1,readonly theme=[x,y]"
        e._eval_cmd("distribute", "items $src into a,b,c")
        assert e.ctx["a"] == "[python,[def f(): return 0]]"
        assert e.ctx["b"] == "1"
        assert e.ctx["c"] == "readonly theme=[x,y]"

    def test_solve_command_numeric_root(self):
        # !solve EQ for VAR = LO to HI — numeric root in the interval (quizz
        # 1120 places its (Cf) label this way). OEF `solve(eq, x=a..b)` compiles
        # to this command.
        e = engine()
        assert e._eval_cmd("solve", "x^2-2=0 for x = 1 to 2").startswith("1.41421")
        # No sign change in the interval → empty (label coord left blank).
        assert e._eval_cmd("solve", "x^2+1=0 for x = 0 to 1") == ""

    def test_standalone_distribute_command_executes(self):
        # A bare `!distribute` line (no `=` target) must run, not be skipped —
        # it feeds downstream vars (quizz 1120's solve setup).
        from core.oef.def_parser import Command
        e = engine()
        e.ctx["src"] = "a=1,x=0.1,0.9"
        e._exec([Command(cmd="distribute", args="items $src into t1,t2,t3")], None)
        assert e.ctx["t1"] == "a=1" and e.ctx["t2"] == "x=0.1" and e.ctx["t3"] == "0.9"

    def test_parser_keeps_standalone_ctx_commands(self):
        from core.oef.def_parser import _parse_instructions, Command
        instrs, _ = _parse_instructions(["!distribute items $tmp into a,b,c"], 0)
        assert any(isinstance(i, Command) and i.cmd == "distribute" for i in instrs)

    def test_while_loop_iterates(self):
        # `!while COND … !endwhile` must re-check COND and loop, not run the
        # body once (quizz 1126: Suite(2) with max=6,r=3 → n=2, not 1).
        from core.oef.def_parser import _parse_instructions, WhileLoop
        lines = ["!while $u<6", "n=$[$n+1]", "u=$[$u+3]", "!endwhile", "rep=$n"]
        instrs, _ = _parse_instructions(lines, 0)
        assert any(isinstance(i, WhileLoop) for i in instrs)
        e = engine()
        e.ctx["n"], e.ctx["u"] = "0", "2"
        e._exec(instrs, None)
        assert e.ctx["u"] == "8"   # 2 → 5 → 8 (stops when 8 < 6 is false)
        assert e.ctx["rep"] == "2"  # n incremented twice

    def test_bound_clamps_to_default(self):
        e = engine()
        e.ctx["v"] = "weird"
        e._eval_cmd("bound", "v within <,>,<= default <")
        assert e.ctx["v"] == "<"

    def test_bound_keeps_valid_value(self):
        e = engine()
        e.ctx["v"] = ">="
        e._eval_cmd("bound", "v within <,>,<=,>= default <")
        assert e.ctx["v"] == ">="

    def test_reset_clears_multiple_vars(self):
        # `!reset a b c` must clear each space-separated variable (slib editor
        # resets several theme/contrast vars on one line).
        e = engine()
        e.ctx.update(a="1", b="2", c="3")
        e._eval_cmd("reset", "a b c")
        assert e.ctx["a"] == "" and e.ctx["b"] == "" and e.ctx["c"] == ""

    def test_default_sets_when_missing(self):
        e = engine()
        e._eval_cmd("default", "x=42")
        assert e.ctx["x"] == "42"

    def test_default_skips_when_set(self):
        e = engine()
        e.ctx["x"] = "5"
        e._eval_cmd("default", "x=42")
        assert e.ctx["x"] == "5"

    def test_render_embed_collapses_whitespace_in_ref(self):
        # `!read oef/embed.phtml reply 1,30` (with a space) should still
        # produce a span named `reply1` so the input matches the answer.
        e = engine()
        out = e._render_embed("reply 1,30")
        assert 'name="reply1"' in out
        assert 'data-size="30"' in out

    def test_isin_substring(self):
        e = engine()
        assert e._eval_condition("if", "ab isin xabc")
        assert not e._eval_condition("if", "qq isin xabc")

    def test_string_inequality(self):
        e = engine()
        assert e._eval_condition("if", "<,3 != slib_header")
        assert not e._eval_condition("if", "abc != abc")

    def test_codeeditor_single_code(self):
        import html as _html
        import json as _json
        e = engine()
        code = "def f(b):\t   a = 0\t   return a"  # WIMS stores newlines as tabs
        out = e._render_codeeditor(
            f"[python,[{code}]],1,readonly fullscreen theme=[3024-night,3024-day]"
        )
        assert out.startswith('<div class="pax-codeeditor" data-codeeditor="')
        m = re.search(r'data-codeeditor="([^"]*)"', out)
        cfg = _json.loads(_html.unescape(m.group(1)))
        assert cfg["id"] == "1"
        assert cfg["themes"] == ["3024-night", "3024-day"]
        assert cfg["fullscreen"] is True
        assert len(cfg["codes"]) == 1
        assert cfg["codes"][0]["lang"] == "python"
        assert cfg["codes"][0]["readonly"] is True
        # Tabs (WIMS newlines) restored to real newlines for display.
        assert cfg["codes"][0]["code"] == "def f(b):\n   a = 0\n   return a"

    def test_codeeditor_multi_code(self):
        import html as _html
        import json as _json
        e = engine()
        out = e._render_codeeditor(
            "[[python,[a=1],initial],[python,[a=2],corrige,readonly]],2,init"
        )
        m = re.search(r'data-codeeditor="([^"]*)"', out)
        cfg = _json.loads(_html.unescape(m.group(1)))
        assert cfg["init"] is True
        assert [c["name"] for c in cfg["codes"]] == ["initial", "corrige"]
        assert cfg["codes"][0]["readonly"] is False
        assert cfg["codes"][1]["readonly"] is True

    def test_distribute_accepts_singular_item(self):
        # `!distribute item` (singular, used by slib/generator) is accepted.
        e = engine()
        e.ctx["src"] = "5,100"
        e._eval_cmd("distribute", "item $src into a,b")
        assert e.ctx["a"] == "5"
        assert e.ctx["b"] == "100"

    def test_bound_between_clamps_out_of_range(self):
        e = engine()
        e.ctx["v"] = "12"
        e._eval_cmd("bound", "v between 3 and 10 default 5")
        assert e.ctx["v"] == "5"

    def test_bound_between_keeps_in_range(self):
        e = engine()
        e.ctx["v"] = "7"
        e._eval_cmd("bound", "v between 3 and 10 default 5")
        assert e.ctx["v"] == "7"


# ── !randrecord ──────────────────────────────────────────────────────────────


class TestCmdRandrecord:
    def test_picks_record_from_don_file(self, tmp_path):
        # Records separated by lines starting with `:`. Set up a tiny .def
        # so the engine can resolve a relative `src/<name>` path.
        mod = tmp_path / "mod"
        (mod / "def").mkdir(parents=True)
        (mod / "src").mkdir()
        (mod / "src" / "data.don").write_text(
            ":alpha\nfirst-record-body\n:beta\nsecond-record-body\n"
        )
        def_path = mod / "def" / "x.def"
        def_path.write_text("")
        e = DefEngine(seed=1, def_path=str(def_path))
        result = e._eval_cmd("randrecord", "src/data.don")
        # Both candidates are valid; the seed determines which.
        assert "alpha" in result or "beta" in result
        assert "record-body" in result

    def test_returns_empty_when_file_missing(self, tmp_path):
        def_path = tmp_path / "def" / "x.def"
        def_path.parent.mkdir()
        def_path.write_text("")
        e = DefEngine(seed=1, def_path=str(def_path))
        assert e._eval_cmd("randrecord", "src/missing.don") == ""


# ── _call_pari ─────────────────────────────────────────────────────────────────


class TestCallPari:
    def test_addition(self):
        assert _call_pari("5+1") == "6"

    def test_power(self):
        assert _call_pari("3^2") == "9"

    def test_rational_division(self):
        # PARI: integer / integer → Rational
        assert _call_pari("10/4") == "5/2"

    def test_float_division(self):
        assert _call_pari("5.5/2") == "2.75"

    def test_integer_float(self):
        assert _call_pari("sqrt(9)") == "3"

    def test_trailing_semicolon(self):
        assert _call_pari("2+3;") == "5"

    def test_unparseable_returns_input(self):
        result = _call_pari("not_an_expr!!!")
        assert result == "not_an_expr!!!"

    # ── Pari helpers ──────────────────────────────────────────────────────
    def test_concat_strings(self):
        assert _call_pari('concat("a", "b", "c")') == "abc"

    def test_expand(self):
        assert _call_pari("expand((x+1)*(x-1))") == "x^2 - 1"

    def test_polynomial_is_auto_expanded(self):
        # PARI canonicalises polynomial expressions to expanded form.
        assert _call_pari("(x-3)*(x+3)") == "x^2 - 9"
        assert _call_pari("3*(x-7)*(x+7)") == "3*x^2 - 147"
        assert _call_pari("(x-5)^2") == "x^2 - 10*x + 25"

    def test_polcoeff(self):
        assert _call_pari("polcoeff(x^2 + 3*x + 2, 1)") == "3"

    def test_poldegree(self):
        assert _call_pari("poldegree(x^3 + 2*x)") == "3"

    def test_divrem(self):
        assert _call_pari("divrem(17, 5)") == "3,2"

    def test_denominator(self):
        assert _call_pari("denominator(3/4)") == "4"

    def test_numerator(self):
        assert _call_pari("numerator(3/4)") == "3"

    def test_vecmax(self):
        assert _call_pari("vecmax([3, 7, 2, 9, 1])") == "9"

    def test_vecmin(self):
        assert _call_pari("vecmin([3, 7, 2, 9, 1])") == "1"

    def test_matdet_2x2(self):
        assert _call_pari("matdet([[1,2],[3,4]])") == "-2"

    def test_isprime_true(self):
        assert _call_pari("isprime(7)") == "1"

    def test_isprime_false(self):
        assert _call_pari("isprime(8)") == "0"

    def test_subst(self):
        assert _call_pari("subst(x^2+1, x, 3)") == "10"

    def test_core_squarefree(self):
        # 12 = 2^2 * 3 → squarefree part is 3
        assert _call_pari("core(12)") == "3"

    def test_core_negative(self):
        # -50 = -1 * 2 * 5^2 → squarefree part is -2 (sign preserved)
        assert _call_pari("core(-50)") == "-2"

    def test_print_unwraps(self):
        assert _call_pari('print(concat("hi", "!"))') == "hi!"


# ── !values ────────────────────────────────────────────────────────────────────


class TestCmdValues:
    def test_identity_loop(self):
        e = engine()
        assert e._eval_cmd("values", "v for v=2 to 5") == "2,3,4,5"

    def test_comma_separated_expr_flat_list(self):
        # `v,-v` per iteration must produce a flat list of pairs, not Python
        # tuple repr `(2, -2),(3, -3),...`.
        e = engine()
        assert e._eval_cmd("values", "v,-v for v=2 to 4") == "2,-2,3,-3,4,-4"

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

    def test_nonempty_rows_uses_semicolons(self):
        """`calc_nonempty` découpe les rows par `rows2lines` — donc `;`, jamais
        la tabulation — et les rejoint par `;`. Une valeur tabulée ne convertit
        rien : WIMS bascule alors sur les lignes, et elle ressort telle quelle."""
        e = engine()
        assert e._eval_cmd("nonempty", "rows a;;b") == "a;b"
        assert e._eval_cmd("nonempty", "rows a\t\tb") == "a\t\tb"

    def test_itemcnt(self):
        e = engine()
        assert e._eval_cmd("itemcnt", "a,b,c") == "3"

    def test_rowcnt(self):
        """`rownum` = `rows2lines` puis `linenum` : `;` ou `\n`, jamais `\t`."""
        e = engine()
        assert e._eval_cmd("rowcnt", "a;b;c") == "3"
        assert e._eval_cmd("rowcnt", "a\nb\nc") == "3"
        assert e._eval_cmd("rowcnt", "a\tb\tc") == "1"


# ── !item / !row ───────────────────────────────────────────────────────────────


class TestCmdItemRow:
    def test_item_first(self):
        e = engine()
        assert e._eval_cmd("item", "1 of a,b,c") == "a"

    def test_item_index_list(self):
        # WIMS `!item 4,7,8 of LIST` picks multiple items by index — used by
        # rotation/colour-permutation exercises.
        e = engine()
        result = e._eval_cmd("item", "3,1,2 of red,blue,yellow")
        assert result == "yellow,red,blue"

    def test_item_second(self):
        e = engine()
        assert e._eval_cmd("item", "2 of a,b,c") == "b"

    def test_item_out_of_range(self):
        e = engine()
        assert e._eval_cmd("item", "9 of a,b,c") == ""

    def test_item_range_to(self):
        e = engine()
        assert e._eval_cmd("item", "2 to 3 of a,b,c,d") == "b,c"

    def test_item_range_negative_end(self):
        # WIMS `-1` = last item: "2 to -1" = from 2 to the end (simpquot keeps
        # every accepted answer form after the displayed expression).
        e = engine()
        assert e._eval_cmd("item", "2 to -1 of a,b,c,d") == "b,c,d"
        assert e._eval_cmd("item", "2 to -1 of expr,15") == "15"

    def test_tab_is_not_an_item_border(self):
        """La tabulation encode un retour à la ligne du source OEF ; elle se
        fait élaguer aux bords d'item, jamais découper."""
        e = engine()
        assert e._eval_cmd("item", "1 of a\tb\tc") == "a\tb\tc"
        assert e._eval_cmd("item", "2 of a,\tb") == "b"

    def test_row_second(self):
        """`calc_rowof` : les lignes se séparent par `;` ou `\n`."""
        e = engine()
        assert e._eval_cmd("row", "2 of a;b;c") == "b"
        assert e._eval_cmd("row", "2 of a\nb\nc") == "b"

    def test_row_of_a_tabbed_value_is_the_whole_value(self):
        """Aucune tabulation ne coupe une matrice : elle n'a qu'une ligne."""
        e = engine()
        assert e._eval_cmd("row", "1 of a\tb\tc") == "a\tb\tc"
        assert e._eval_cmd("row", "2 of a\tb\tc") == ""

    def test_row_out_of_range(self):
        e = engine()
        assert e._eval_cmd("row", "5 of a;b") == ""


# ── !replace / !append ────────────────────────────────────────────────────────


class TestCmdStringOps:
    def test_replace_basic(self):
        e = engine()
        assert e._eval_cmd("replace", "internal x by y in exy") == "eyy"

    def test_replace_no_match(self):
        e = engine()
        assert e._eval_cmd("replace", "internal z by y in abc") == "abc"

    def test_replace_empty_with_internal_prefix(self):
        # `!replace internal , by in TEXT` deletes commas — the `internal`
        # prefix must be consumed (interint3 strips the clickfill list
        # separators from the displayed interval `[,15,;,17,[` → `[15;17[`).
        e = engine()
        assert e._eval_cmd("replace", "internal , by in [,15,;,17,[") == "[15;17["
        assert e._eval_cmd("replace", ", by in [,a,;,b,[") == "[a;b["

    def test_append_to_comma_list(self):
        # No tabs in the list → append with comma so slib helpers building
        # comma-separated frequency lists (e.g. slib/generator) work.
        e = engine()
        e.ctx["mylist"] = "a,b"
        assert e._eval_cmd("append", "item c to $mylist") == "a,b,c"

    def test_append_item_always_uses_a_comma(self):
        """`calc_append` prend son séparateur dans `apch_list` — `item`→`,` —
        sans regarder le contenu. Le basculement vers la tabulation était l'un
        des producteurs qui obligeaient les consommateurs à traiter la
        tabulation en séparateur."""
        e = engine()
        e.ctx["mylist"] = "a\tb"
        assert e._eval_cmd("append", "item c to $mylist") == "a\tb,c"

    def test_append_to_empty_var(self):
        e = engine()
        e.ctx["empty"] = ""
        assert e._eval_cmd("append", "item x to $empty") == "x"

    def test_append_item_with_a_comma_still_uses_a_comma(self):
        """Même quand l'item porte lui-même une virgule : c'est au consommateur
        de protéger ses crochets, pas au producteur de changer de séparateur."""
        e = engine()
        e.ctx["mylist"] = "a"
        assert e._eval_cmd("append", "item [x,y] to $mylist") == "a,[x,y]"


class TestSlibDataRandom:
    def test_picks_n_distinct_items(self):
        # slib/data/random N,item,LIST → N distinct random items (seeded).
        e = engine()
        e._cmd_readproc("slib/data/random 2,item, a,b,c,d,e")
        out = e.ctx["slib_out"].split(",")
        assert len(out) == 2 and len(set(out)) == 2
        assert set(out) <= set("abcde")

    def test_word_type(self):
        e = engine()
        e._cmd_readproc("slib/data/random 3,word, un deux trois quatre")
        out = e.ctx["slib_out"].split(" ")
        assert len(out) == 3 and set(out) <= {"un", "deux", "trois", "quatre"}

    def test_deterministic_for_seed(self):
        a = engine(seed=42); a._cmd_readproc("slib/data/random 2,item, 1,2,3,4,5")
        b = engine(seed=42); b._cmd_readproc("slib/data/random 2,item, 1,2,3,4,5")
        assert a.ctx["slib_out"] == b.ctx["slib_out"]

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
    def test_indexed1_tab_is_not_a_separator(self):
        e = engine()
        e.ctx["v"] = "a\tb\tc"
        assert e._subst("$(v[1])") == "a\tb\tc"
        e.ctx["w"] = "a,\tb"
        assert e._subst("$(w[2])") == "b"

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

    def test_indexed2_nested_column(self):
        # ecrdec1: $(val14[$m_h;$(val11[$m_h])]) — the column index is itself
        # an indexed lookup. The inner $(val11[…]) must resolve first, then
        # the outer matrix access. Previously the outer regex grabbed the
        # inner "]" and left a literal "])" behind.
        e = engine()
        e.ctx["mat"] = "Finie;Infinie périodique\tFinie;Je ne sais pas"
        e.ctx["pos"] = "2,1"  # correct column per row
        e.ctx["m_h"] = "1"
        assert e._subst("$(mat[$m_h;$(pos[$m_h])])") == "Infinie périodique"
        e.ctx["m_h"] = "2"
        assert e._subst("$(mat[$m_h;$(pos[$m_h])])") == "Finie"

    def test_indexed1_nested_subscript(self):
        # $(outer[$(inner[$i])]) still resolves inner-first then outer.
        e = engine()
        e.ctx["outer"] = "a,b,c,d"
        e.ctx["inner"] = "10,3"
        e.ctx["i"] = "2"
        assert e._subst("$(outer[$(inner[$i])])") == "c"

    def test_indexed2_arithmetic_index(self):
        # Parenthesised arithmetic in a subscript must still resolve — the
        # nesting-defer trick excludes "$(" only, not plain "(" (nature).
        e = engine()
        e.ctx["m"] = "a;b;c;d;e;f"
        e.ctx["k"] = "1"
        e.ctx["n"] = "3"
        assert e._subst("$(m[(1+3);])") == "d"
        assert e._subst("$(m[($k+$n);])") == "d"

    def test_indexed1_arithmetic_index(self):
        e = engine()
        e.ctx["v"] = "red,green,blue"
        e.ctx["k"] = "1"
        assert e._subst("$(v[(2*$k-1)%3+1])") == "green"

    def test_indexed2_empty_row_is_column(self):
        # $(m[;col]) → column `col` of every row, comma-joined (cof builds a
        # correspond's right column this way).
        e = engine()
        e.ctx["m"] = "a1,a2;b1,b2;c1,c2"
        assert e._subst("$(m[;1])") == "a1,b1,c1"
        assert e._subst("$(m[;2])") == "a2,b2,c2"

    def test_range_slice_as_matrix_row_list(self):
        # $(m[$(rows[1..n]);]) — a range slice used as the row-list of a
        # matrix access. The slice's ".." must not trick the range regex into
        # matching the OUTER ref (cof's shuffled line selection).
        e = engine()
        e.ctx["m"] = "A;B;C;D;E"
        e.ctx["rows"] = "4,3,2,5,1"
        e.ctx["n"] = "3"
        assert e._subst("$(m[$(rows[1..$n]);])") == "D;C;B"

    def test_for_in_list_loop(self):
        # `!for VAR in LIST` iterates VAR over each item — distinct from the
        # numeric `X = a to b` form (nature builds its correct-answer set this
        # way). The parser leaves loop.var empty, the var lives in range_expr.
        from core.oef.def_parser import Assign, ForLoop  # noqa: PLC0415
        e = engine()
        e.ctx["lst"] = "3,4,5"
        e.ctx["acc"] = ""
        loop = ForLoop(
            var="",
            range_expr="x in $lst",
            body=[Assign(name="acc", value="!append item $x to $acc")],
        )
        e._exec([loop], None)
        assert e.ctx["acc"] == "3,4,5"

    def test_dollar_bracket_arithmetic(self):
        e = engine()
        e.ctx["x"] = "3"
        assert e._eval_dollar_bracket("$[$x*2]") == "6"

    def test_arctan_arc_aliases(self):
        # WIMS spells inverse trig `arc*`; rectangle.oef's angle reply uses
        # `$[rint(arctan(...)*180/pi)]` — must evaluate to a number, not leak
        # the literal expression.
        e = engine()
        assert e._eval_dollar_bracket(
            "$[rint(arctan((sqrt(21)-1)/(sqrt(21)+1))*180/pi)]"
        ) == "33"
        assert e._eval_dollar_bracket("$[rint(arcsin(1)*180/pi)]") == "90"

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
    """`_values` (`calc.c`) joint **toutes** ses valeurs par une virgule —
    `if(pp>p) *pp++=','` — sans séparateur de lignes.

    PAX les séparait par des tabulations, ce qui donnait à `slib/stat/dataproc`
    un `slib_weight` en `1<TAB>1<TAB>…` : invalide en PARI, d'où le
    `print((…)` en clair d'`oefstat/mean`.
    """

    def test_comma_separated(self):
        e = engine()
        assert e._eval_cmd("makelist", "v for v=1 to 3") == "1,2,3"

    def test_multi_expression_stays_flat(self):
        """Plusieurs expressions ne font pas des *lignes* : la liste reste
        plate, chaque valeur séparée par une virgule."""
        e = engine()
        assert e._eval_cmd("makelist", "v,-v for v=1 to 3") == "1,-1,2,-2,3,-3"

    def test_expression(self):
        e = engine()
        assert e._eval_cmd("makelist", "v*v for v=1 to 4") == "1,4,9,16"

    def test_item_access_after_makelist(self):
        e = engine()
        e.ctx["mat"] = e._eval_cmd("makelist", "v,-v for v=2 to 4")
        assert e._subst("$(mat[2])") == "-2"

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

    def test_tab_is_not_a_separator(self):
        """`_pos` passe par `fnd_item` : la virgule seule sépare, et l'item
        est élagué avant comparaison."""
        e = engine()
        e.ctx["lst"] = "x,\ty,\tz"
        assert e._eval_cmd("positionof", "item y in $lst") == "2"

    def test_numeric_value(self):
        e = engine()
        e.ctx["lst"] = "1,2,3,4"
        assert e._eval_cmd("positionof", "item 3 in $lst") == "3"


# ── !randrow ──────────────────────────────────────────────────────────────────


class TestCmdRandrow:
    def test_returns_one_row(self):
        """`calc_randrow` : `rows2lines(p)` puis `calc_randline` (calc.c:498)."""
        e = engine(1)
        e.ctx["mat"] = "a,1;b,2;c,3"
        result = e._eval_cmd("randrow", "$mat")
        assert result in ("a,1", "b,2", "c,3")

    def test_tabs_make_a_single_row(self):
        """Une valeur tabulée n'a qu'une ligne : elle ressort entière."""
        e = engine(1)
        e.ctx["mat"] = "a,1\tb,2\tc,3"
        assert e._eval_cmd("randrow", "$mat") == "a,1\tb,2\tc,3"

    def test_deterministic(self):
        e1, e2 = engine(42), engine(42)
        e1.ctx["mat"] = e2.ctx["mat"] = "x;y;z"
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

    def test_tab_is_not_a_separator(self):
        """`calc_listuniq` passe par `cutitems`, donc par `find_item_end` : la
        virgule seule sépare. Une valeur tabulée est **un** item, qu'aucun
        doublon ne vient réduire."""
        e = engine()
        assert e._eval_cmd("listuniq", "a\tb\ta\tc") == "a\tb\ta\tc"

    def test_output_is_comma_joined_without_space(self):
        """`strcat(lout,",")` : virgule sans espace."""
        e = engine()
        assert e._eval_cmd("listuniq", "a , b , a") == "a,b"

    def test_empty_items_are_dropped(self):
        e = engine()
        assert e._eval_cmd("listuniq", "a,,b,") == "a,b"


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

    def test_getopt_bracketed_value_keeps_commas(self):
        # `theme=[3024-night,3024-day]` must come back whole — the comma is
        # inside [...] and must not split the value (slib editor theme list).
        e = engine()
        e.ctx["opts"] = "readonly fullscreen theme=[3024-night,3024-day]"
        assert e._eval_cmd("getopt", "theme in $opts") == "[3024-night,3024-day]"

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

    def test_tab_is_not_a_separator(self):
        """La tabulation ne coupe rien : la valeur entière est l'item 1."""
        e = engine()
        e.ctx["v"] = "x\ty\tz"
        assert e._subst("$(v[1..2])") == "x\ty\tz"
        e.ctx["w"] = "x,\ty,\tz"
        assert e._subst("$(w[1..2])") == "x,y"

    def test_single_element(self):
        e = engine()
        e.ctx["v"] = "a,b,c"
        assert e._subst("$(v[2..2])") == "b"

    def test_variable_bound(self):
        # Bounds may be variable refs, not just literals: $(v[1..$n]).
        # This is the "first N items" idiom that ecrdec1 relies on.
        e = engine()
        e.ctx["v"] = "a,b,c,d,e"
        e.ctx["n"] = "3"
        assert e._subst("$(v[1..$n])") == "a,b,c"

    def test_arithmetic_bound(self):
        # Bounds may be arithmetic expressions: $(v[1..$n+1]).
        e = engine()
        e.ctx["v"] = "a,b,c,d,e"
        e.ctx["n"] = "3"
        assert e._subst("$(v[1..$n+1])") == "a,b,c,d"

    def test_variable_start(self):
        e = engine()
        e.ctx["v"] = "a,b,c,d,e"
        e.ctx["n"] = "3"
        assert e._subst("$(v[$n..5])") == "c,d,e"


# ── _render_embed reply ref normalisation ─────────────────────────────────────


class TestRenderEmbedReplyRef:
    def test_reply_loop_var_text(self):
        # `reply\h` (full `reply` prefix + loop var) must resolve the loop
        # variable just like `r\h` does → name="reply2" when h=2.
        e = engine()
        e.ctx["h"] = "2"
        assert e._render_embed(r"reply\h,10") == (
            '<span class="oef-input" name="reply2" data-size="10"></span>'
        )

    def test_r_loop_var_text(self):
        # The short `r\h` form still resolves to the same reply ref.
        e = engine()
        e.ctx["h"] = "2"
        assert e._render_embed(r"r\h,10") == (
            '<span class="oef-input" name="reply2" data-size="10"></span>'
        )

    def test_reply_loop_var_radio_registers_index(self):
        # For a radio reply the widget is rendered by the frontend (returns
        # ""), but the resolved index must still be recorded so the choices
        # get exposed. With h=1 → reply1.
        e = engine()
        e.ctx["h"] = "1"
        e.ctx["replytype1"] = "radio"
        assert e._render_embed(r"reply\h,10") == ""
        assert "reply1" in e._touched_replies


# ── _call_maxima (SymPy backend) ──────────────────────────────────────────────


class TestCallMaxima:
    def test_expand_polynomial(self):
        result = _call_maxima("expand((n + 2)*(n + 3))")
        assert "n**2" in result or "n^2" in result or "5*n" in result

    def test_wims_capital_pi_constant(self):
        # WIMS spells π as `Pi` (capital): both the arith eval (`$[rint(…+Pi)]`,
        # quizz 1211) and the sympy path must treat it as the constant, not a
        # free symbol/NameError.
        e = engine()
        assert e._eval_arith("rint(1.41421356237 + Pi)") == "5"
        assert e._eval_arith("Pi") == "3.14159265359"
        assert _call_maxima("Pi*2").startswith(("6.28318", "2*pi"))

    def test_expand_with_minus(self):
        result = _call_maxima("expand(-(n + 2)*(n + 3))")
        assert "n**2" in result or "n^2" in result
        assert "-" in result

    def test_factor_simple(self):
        result = _call_maxima("factor(n**2 - 4)")
        # SymPy factor: (n - 2)*(n + 2)
        assert "n" in result

    def test_fullratsimp_numeric(self):
        result = _call_maxima("fullratsimp(-10*(-2+3))")
        assert result.strip() == "-10"

    def test_fullratsimp_fraction(self):
        result = _call_maxima("fullratsimp(6/4)")
        # SymPy simplify(Rational(6, 4)) = 3/2
        assert "3" in result and "2" in result

    def test_printtex(self):
        result = _call_maxima("printtex(x**2 + 2*x + 1)")
        assert "x^{2}" in result or "\\left" in result or "x" in result

    def test_fallback_arithmetic(self):
        result = _call_maxima("3 + 4")
        assert result.strip() == "7"

    def test_strips_semicolon(self):
        result = _call_maxima("fullratsimp(-10*(-2+3));")
        assert result.strip() == "-10"

    def test_unknown_function_returns_expr(self):
        result = _call_maxima("weirdunknownfunc(x + 1)")
        assert "weirdunknownfunc" in result or "x" in result

    # ── Multi-arg Maxima functions ────────────────────────────────────────
    def test_diff_polynomial(self):
        assert _call_maxima("diff(x^3, x)") == "3*x**2"

    def test_diff_trig(self):
        assert _call_maxima("diff(sin(x), x)") == "cos(x)"

    def test_subst(self):
        # Maxima: subst(val, var, expr) — replace var with val in expr
        assert _call_maxima("subst(2, x, x^2 + 1)") == "5"

    def test_coeff(self):
        assert _call_maxima("coeff(3*x^2 + 5*x + 7, x, 2)") == "3"

    def test_hipow(self):
        assert _call_maxima("hipow(x^4 + x^2, x)") == "4"

    def test_cardinality(self):
        # Cardinality of a set with duplicates
        assert _call_maxima("cardinality({1,2,3,2,1})") == "3"


# ── _expr_to_latex ───────────────────────────────────────────────────────────


class TestSympyToLatex:
    def test_polynomial(self):
        result = _expr_to_latex("n**2 + 2*n - 15")
        assert "n^{2}" in result
        assert "n" in result

    def test_fraction(self):
        result = _expr_to_latex("3/2")
        assert "frac" in result or "3" in result

    def test_integer_fraction_not_reduced(self):
        # The author's un-reduced form must be preserved (quizz 0512 displays
        # 10/20 and asks for *other* writings of it) — NOT collapsed to 1/2.
        assert _expr_to_latex("10/20") == r"\frac{10}{20}"
        assert _expr_to_latex("5/10") == r"\frac{5}{10}"

    def test_unit_numerator_no_spurious_coefficient(self):
        # `1/4` must be \frac{1}{4}, not `1 \cdot \frac{1}{4}`.
        assert _expr_to_latex("1/4") == r"\frac{1}{4}"
        assert _expr_to_latex("7/-4") == r"-\frac{7}{4}"

    def test_negative(self):
        result = _expr_to_latex("-10")
        assert result.strip() == "-10"

    def test_fallback_on_unparseable(self):
        # Should return original string on parse failure
        result = _expr_to_latex("some random non-math text @#$")
        assert result  # non-empty

    def test_equation_is_left_untouched(self):
        # A top-level lone "=" means an equation/assignment, not an expression:
        # _expr_to_latex must return it verbatim. Regression for distribuer1,
        # where "C = -(7b+3)" (C poisoned into local_dict) was silently parsed
        # as an assignment and reduced to just the distributed RHS "-7b-3".
        for name in ("A", "C", "E", "N"):
            assert _expr_to_latex(f"{name} = - (7 b + 3)") == f"{name} = - (7 b + 3)"
        # Relational "=" (<=, >=) must still render via sympy.
        assert "\\leq" in _expr_to_latex("x <= 3")


# ── !texmath command ──────────────────────────────────────────────────────────


class TestTexmath:
    def test_texmath_converts_to_latex(self):
        e = engine()
        e.ctx["v"] = "n**2 + 2*n - 15"
        result = e._eval_cmd("texmath", "$v")
        assert "n^{2}" in result

    def test_rawmath_keeps_python_form(self):
        # `!rawmath` normalises but does NOT convert to LaTeX (that's
        # `!texmath`). Result must stay Python/Pari-evaluable so downstream
        # `!exec pari print(...)` and `plot` can use it.
        e = engine()
        e.ctx["v"] = "1/3"
        result = e._eval_cmd("rawmath", "$v")
        assert result == "1/3"
        assert "\\frac" not in result


# ── !translate (both with and without internal) ───────────────────────────────


class TestTranslate:
    def test_internal_dollar_delimited_charset(self):
        # WIMS syntax: $CHARS$ delimits the character set.
        # $<tab>$ means {tab}, so each tab in the source → ';'.
        e = engine()
        e.ctx["v"] = "a\tb\tc"
        result = e._eval_cmd("translate", "internal $\t$ to ; in $v")
        assert result == "a;b;c"

    def test_internal_dollar_tab_newline_to_double_semicolon(self):
        # $<tab><newline>$ → char set {tab, newline}; both map to the
        # corresponding char in ";;" (tab→';', newline→';').
        e = engine()
        e.ctx["v"] = "Q1\n0|A\n0|B\n1|C"
        result = e._eval_cmd("translate", "internal $\t\n$ to ;; in $v")
        assert result == "Q1;0|A;0|B;1|C"

    def test_internal_pairwise(self):
        # Equal-length FROM and TO → straightforward char map.
        e = engine()
        result = e._eval_cmd("translate", "internal abc to xyz in apple+banana+chair")
        assert result == "xpple+yxnxnx+zhxir"

    def test_plain_char_translation(self):
        # WIMS pattern: chars_to has a trailing char to separate it from " in "
        # ";" → "$", ":" → " ", "<" → ">"
        e = engine()
        result = e._eval_cmd("translate", '";: to $ _ in abc;def"ghi:jkl')
        # " → $,  ; → space,  : → _
        assert result == "abc def$ghi_jkl"

    def test_plain_noop(self):
        # No chars to translate → identity (arithmetic chars not in translation set)
        e = engine()
        result = e._eval_cmd("translate", "\";': to $     $ in -10*(-2+3)")
        assert result == "-10*(-2+3)"

    def test_plain_with_variable(self):
        e = engine()
        e.ctx["val"] = "1+2+3"
        result = e._eval_cmd("translate", "\";': to $     $ in $val")
        assert result == "1+2+3"

    def test_dollar_delimiters_apply_to_the_target_too(self):
        """`slib/stat/dataproc` sépare données et effectifs avec
        `!translate internal ; to $<LF>$`. WIMS déballe les deux opérandes de
        la même façon (`calc.c:calc_translate` leur applique `substit()`) ;
        ne le faire que sur la source produisait un `$` littéral, les deux
        séries restaient collées et toute statistique pondérée basculait dans
        la branche non pondérée."""
        e = engine()
        result = e._eval_cmd("translate", "internal ; to $\n$ in 1,4,6;2,3,3")
        assert result == "1,4,6\n2,3,3"

    def test_variable_reference_in_target_is_still_substituted(self):
        """Le déballage ne doit pas manger une référence de variable : `$sep`
        ne commence et finit pas par `$`."""
        e = engine()
        e.ctx["sep"] = ":"
        result = e._eval_cmd("translate", "internal ; to $sep in a;b")
        assert result == "a:b"


# ── !exec pari print() unwrapping ─────────────────────────────────────────────


class TestPariPrint:
    def test_print_unwrapped(self):
        assert _call_pari("print(6)") == "6"

    def test_print_negative(self):
        assert _call_pari("print(-6)") == "-6"

    def test_print_expression(self):
        result = _call_pari("print(3 + 4)")
        assert result == "7"

    def test_print_with_semicolon(self):
        assert _call_pari("print(6);") == "6"


# ── jsxgraph answer embed (type=jsxgraph) ────────────────────────────────────


class TestJsxgraphEmbed:
    def test_value_dim(self):
        from core.oef.def_engine import _jsxgraph_value_dim
        assert _jsxgraph_value_dim("1") == 1
        assert _jsxgraph_value_dim("[a,b]") == 2
        assert _jsxgraph_value_dim("[f(){return Q.X()},g(){return Q.Y()}],{n:1}") == 2

    def test_embed_renders_board_with_reply_and_capture(self):
        e = engine()
        e.ctx["replytype1"] = "jsxgraph"
        # ref,size <TAB> divid boardvar [opts] <TAB> script <TAB> variable line
        args = (
            "r1,400x200\tid1 brd [responsive min=250px max=400px]\t"
            "let p2_rep1=brd.create('glider',[p2_var1,0,l1]);\tp2_var1=1;"
        )
        html = e._render_embed(args)
        assert 'class="pax-jsxgraph"' in html
        assert 'data-reply="reply1"' in html
        assert 'data-w="400"' in html and 'data-h="200"' in html
        # placeholder p2_var1 substituted with its value 1 in the glider
        assert "[1,0,l1]" in html
        # capture hook present (drives __paxReport on every board update)
        assert "__paxReport" in html
        assert "p2_rep1.X()" in html

    def test_embed_no_capture_without_variable_line(self):
        # No trailing "name=value" line → no draggable reply, no data-reply.
        e = engine()
        e.ctx["replytype1"] = "jsxgraph"
        args = "r1,300x300\tjxgbox brd\tbrd.create('point',[1,1]);"
        html = e._render_embed(args)
        assert 'class="pax-jsxgraph"' in html
        assert "data-reply" not in html


# ── PARI vector arithmetic (elementwise, not Python list concat) ─────────────


class TestPariVectorArithmetic:
    def test_vector_addition(self):
        # PARI: [6,5]+[1,-2] = [7,3], NOT list concat [6,5,1,-2].
        assert _call_pari("[6,5]+[1,-2]") == "7,3"

    def test_vector_subtraction(self):
        assert _call_pari("[6,5]-[1,2]") == "5,3"

    def test_scalar_times_vector(self):
        assert _call_pari("2*[1,2,3]") == "2,4,6"

    def test_vector_times_scalar(self):
        assert _call_pari("[1,2]*3") == "3,6"

    def test_singleton_vector(self):
        assert _call_pari("[3]+[4]") == "7"

    def test_bare_vector_unchanged(self):
        assert _call_pari("[1,2,3]") == "1,2,3"

    def test_indexing_not_treated_as_vector(self):
        # v[1] is an index, not a vector literal — left symbolic.
        assert _call_pari("v[1]") == "v[1]"

    def test_polynomial_unaffected(self):
        assert _call_pari("(x-3)*(x+3)") == "x^2 - 9"


# ── mark answer embed (type=mark) ────────────────────────────────────────────


class TestMarkEmbed:
    def _engine_with_mark(self):
        e = engine()
        e.ctx["replytype1"] = "mark"
        # replygood = "correct_pos;choice1,choice2,choice3"
        e.ctx["replygood1"] = "2;3 mm,3 dm,3 m"
        return e

    def test_single_embed_expands_to_all_choices(self):
        # One \embed{r1,10} (size, not a column index) → all choices, as WIMS.
        e = self._engine_with_mark()
        html = e._render_embed("r1,10")
        assert html.count('class="oef-mark-choice"') == 3
        assert 'data-pos="1">3 mm</span>' in html
        assert 'data-pos="2">3 dm</span>' in html
        assert 'data-pos="3">3 m</span>' in html

    def test_valid_column_index_renders_single_choice(self):
        # Split mode: \embed{r1,2} places only column 2.
        e = self._engine_with_mark()
        html = e._render_embed("r1,2")
        assert html.count('class="oef-mark-choice"') == 1
        assert 'data-pos="2">3 dm</span>' in html


# ── nested $(var[$(inner);]) matrix resolution ───────────────────────────────


class TestNestedMatrixSubst:
    def _engine(self):
        e = engine()
        e.ctx["mat"] = "2,La moitié,dixième(s);5,Le cinquième,dixième(s)"
        e.ctx["row"] = "1"
        return e

    def test_nested_ref_whole_row(self):
        # $(mat[$(row);]) — empty column spec → whole row. The nested simple
        # ref $(row) must collapse so the outer matrix form resolves.
        e = self._engine()
        assert e._subst("$(mat[$(row);])") == "2,La moitié,dixième(s)"

    def test_nested_ref_single_cell(self):
        e = self._engine()
        assert e._subst("$(mat[$(row);2])") == "La moitié"

    def test_plain_row_still_works(self):
        e = self._engine()
        assert e._subst("$(mat[1;])") == "2,La moitié,dixième(s)"

    def test_undefined_nested_ref_left_alone(self):
        # An undefined nested ref shouldn't blow up; the outer simply can't
        # resolve and the form is left for the caller's final pass.
        e = self._engine()
        out = e._subst("$(mat[$(missing);])")
        assert "La moitié" not in out


# ── slib : lignes de commentaire ──────────────────────────────────────────────


class TestSlibComments:
    """`!!` ouvre un commentaire WIMS. L'interpréteur slib sautait `#` et `:`
    mais pas `!!` : chaque ligne de commentaire partait dans le dispatch de
    commandes et en revenait avec `UNKNOWN_CMD:!`, qui écrasait `slib_out`.
    `slib/function/tabsignes` ne renvoyait ainsi que son bandeau de version
    (`!!!! tabsignes v1.22`, première ligne du fichier)."""

    def test_comment_lines_are_skipped(self):
        e = engine()
        e._run_script_lines(
            ["!! un commentaire", "!!!! bandeau de version", "slib_out=ok"]
        )
        assert e.ctx.get("slib_out") == "ok"

    def test_comment_does_not_overwrite_an_earlier_result(self):
        e = engine()
        e._run_script_lines(["slib_out=valeur", "!! commentaire de fin"])
        assert e.ctx.get("slib_out") == "valeur"

    def test_a_bang_command_is_still_dispatched(self):
        """Le filtre ne doit pas avaler les vraies commandes."""
        e = engine()
        e._run_script_lines(["slib_out=!trim   espaces  "])
        assert e.ctx.get("slib_out") == "espaces"


class TestReplaceEmptyPattern:
    """`!replace internal $empty by X in Y` : motif vide → aucune occurrence.

    Python insérerait le remplacement entre *chaque* caractère
    (`"ab".replace("", "X")` vaut `"XaXbX"`). `slib/function/tabsignes` écrit
    `!replace internal $empty by \\qquad \\qquad in $slib_cel` pour espacer ses
    cellules vides, ce qui hachait toutes les autres : son marqueur `reply1`
    ressortait en `\\qquad r\\qquad e\\qquad p\\qquad l\\qquad y…`.
    """

    def test_empty_pattern_is_a_noop(self):
        e = engine()
        e.ctx["empty"] = ""
        assert e._eval_cmd("replace", "internal $empty by \\qquad in reply1") == "reply1"

    def test_normal_replacement_still_works(self):
        assert engine()._eval_cmd("replace", "internal a by X in banana") == "bXnXnX"

    def test_empty_replacement_still_deletes(self):
        assert engine()._eval_cmd("replace", "internal , by in a,b,c") == "abc"


class TestSlibOutPreservation:
    """Une commande `!xxx` isolée ne doit pas effacer `slib_out`.

    `slib/function/tabsignes` assemble son tableau dans `slib_out`, puis termine
    par le `!reset` de ses variables de travail. Ce `!reset` renvoie `""` — et
    emportait le tableau avec lui. Le cas vaut pour tout slib finissant par un
    nettoyage."""

    def test_reset_does_not_wipe_the_result(self):
        e = engine()
        e._run_script_lines(["slib_out=<table>résultat</table>", "!reset slib_tmp"])
        assert e.ctx.get("slib_out") == "<table>résultat</table>"

    def test_a_command_with_a_result_still_fills_slib_out(self):
        e = engine()
        e._run_script_lines(["!trim   valeur  "])
        assert e.ctx.get("slib_out") == "valeur"


class TestItemCount:
    """`!itemcnt` — `itemnum` (`liblines.c`), et rien d'autre.

    La virgule seule sépare, à profondeur zéro, et les cases vides comptent :
    les colonnes sans signe d'un tableau de variation (`x,reply1,,reply2`) en
    sont, et `slib/function/tabsignes` bâtissait 4 colonnes au lieu de 6 quand
    on les ignorait. Seule la chaîne **vide** vaut 0 (`if(*p==0) return 0`).

    La tabulation n'a jamais eu de rôle ici : le filtre « ligne blanche » qui
    l'accompagnait compensait un `!makelist` tabulé, corrigé depuis.
    """

    def test_empty_cells_between_commas_are_counted(self):
        assert engine()._eval_cmd("itemcnt", "f'(x),,reply4,,reply5,,reply6") == "7"

    def test_plain_comma_list(self):
        assert engine()._eval_cmd("itemcnt", "a,b,c") == "3"

    def test_tabs_are_not_separators(self):
        """Sans virgule, il n'y a qu'un item — la tabulation n'en coupe aucun."""
        assert engine()._eval_cmd("itemcnt", "a\t\tb\tc") == "1"

    def test_comma_tab_pairs_do_not_add_phantom_items(self):
        """La forme des listes multi-lignes des `.def` : `item,<TAB>item,<TAB>…`

        La virgule découpe, `fnd_item` élague la tabulation de bord : trois
        items, sans qu'aucun fantôme n'apparaisse.
        """
        assert engine()._eval_cmd("itemcnt", "x,\t  y,\t  z\t") == "3"

    def test_brackets_protect_commas(self):
        """`itemnum` passe par `find_item_end` = `strparstr(p, ",")` : la virgule
        ne sépare qu'à profondeur zéro.

        L'assertion inverse a longtemps tenu ici, parce que protéger seul
        cassait `oefstat/mean` : la protection fait passer `slib/stat/dataproc`
        dans sa branche pondérée — la bonne — mais celle-ci recevait un
        `slib_weight` tabulé, invalide en PARI. C'est le séparateur de
        `!makelist` qu'il fallait corriger en même temps.
        """
        assert engine()._eval_cmd("itemcnt", "[0,4,3.5]") == "1"
        assert engine()._eval_cmd("itemcnt", "[a,b],[c,d]") == "2"

    def test_empty_input(self):
        assert engine()._eval_cmd("itemcnt", "  ") == "0"


class TestDistributeEnclosedList:
    """`!distribute items` : une paire de crochets englobant *toute* la chaîne
    est la notation de liste, pas une protection de virgules.

    `slib/function/tabsignes` reçoit ses positions de réponses sous la forme
    `[[1,2;1,4],[2]]` — positions puis rang de départ. Sans déballage, les deux
    arrivaient collés et le slib ne voyait plus qu'une réponse au lieu de six.
    """

    def test_enclosing_pair_is_unwrapped(self):
        e = engine()
        e.ctx["src"] = "[[1,2;1,4],[2]]"
        e._eval_cmd("distribute", "items $src into a,b")
        assert e.ctx["a"] == "[1,2;1,4]"
        assert e.ctx["b"] == "[2]"

    def test_inner_brackets_still_protect_commas(self):
        e = engine()
        e.ctx["src"] = "[python,[code]],1,readonly"
        e._eval_cmd("distribute", "items $src into x,y,z")
        assert (e.ctx["x"], e.ctx["y"], e.ctx["z"]) == ("[python,[code]]", "1", "readonly")


class TestListMembershipWithBrackets:
    """`isitemof` et `!positionof item` : les virgules protégées par des
    crochets ne séparent pas des items.

    `slib/function/tabsignes` teste `[ligne,colonne] isitemof <liste de
    couples>` puis cherche `positionof item [ligne,colonne]` pour numéroter la
    réponse. Avec un découpage naïf, le premier était toujours faux et le
    second toujours 0 : toutes les cellules recevaient le même numéro
    (`0 + rang - 1`), et le tableau affichait `reply1` en clair partout.
    """

    def test_isitemof_protects_brackets(self):
        e = engine()
        assert e._eval_condition("if", "[1,2] isitemof [1,2],[3,4]")
        assert not e._eval_condition("if", "[9,9] isitemof [1,2],[3,4]")

    def test_isitemof_ne_normalise_pas_les_espaces(self):
        """`itemchr(buf2,buf1)` (compare.c:165) — recherche de sous-chaîne.

        Aucune normalisation n'entoure l'appel : un `[1, 2]` espacé ne contient
        pas la sous-chaîne `[1,2]`. WIMS n'en produit d'ailleurs jamais, son
        `gp` tournant en mode brut (`default(output,0)`, Interfaces/pari.c).
        """
        assert not engine()._eval_condition("if", "[1,2] isitemof [1, 2], [3, 4]")
        assert engine()._eval_condition("if", "[1, 2] isitemof [1, 2], [3, 4]")

    def test_isitemof_plain_list_unchanged(self):
        e = engine()
        assert e._eval_condition("if", "b isitemof a,b,c")
        assert not e._eval_condition("if", "z isitemof a,b,c")

    def test_positionof_protects_brackets(self):
        e = engine()
        assert e._eval_cmd("positionof", "item [2,3] in [1,2],[2,3],[3,4]") == "2"

    def test_positionof_compare_sans_normaliser(self):
        """`_pos` (calc.c) : `strcmp` sur l'item élagué, rien de plus.

        Les blancs de **bord** tombent avec `fnd_item`, ceux de l'intérieur
        restent — `[2,3]` n'est pas `[2, 3]`.
        """
        e = engine()
        assert e._eval_cmd("positionof", "item [2,3] in [1, 2], [2, 3]") == "0"
        assert e._eval_cmd("positionof", "item [2, 3] in [1, 2], [2, 3]") == "2"

    def test_positionof_absent_returns_zero(self):
        assert engine()._eval_cmd("positionof", "item [9,9] in [1,2],[2,3]") == "0"

    def test_positionof_plain_list_unchanged(self):
        assert engine()._eval_cmd("positionof", "item b in a,b,c") == "2"
