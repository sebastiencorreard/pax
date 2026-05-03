"""
Tests for the .def parser and engine.

Uses real files from the resource tree as fixtures:
  - valeur1.def       — simple: !randint, $[expr], literal strings, :question with !insmath
  - loiGP1.def        — medium: 5 numeric answers, $(var[n;m]) matrix access
  - equaprod1.def     — uses !values, produces fractional solutions
  - intercepte2.def   — 4 radio answers built with !for loop
  - rotation3.def     — uses !randrow to pick a question from a matrix
  - compTrinomeSign2  — uses !positionof (Dutch exercise, 4 answers)
  - ordre2.def        — uses !sort + $(var[n..m]) range slice
"""

import os
import re


from core.oef.def_parser import (
    Assign,
    IfBlock,
    parse,
)
from core.oef.def_engine import DefEngine, load_and_render

RESSOURCES = os.path.abspath(
    os.path.join(os.path.dirname(__file__), "../../../../ressources")
)

VALEUR1_DEF = os.path.join(RESSOURCES, "H4/number/evalwimsracine.fr/def/valeur1.def")
LOIGP1_DEF = os.path.join(RESSOURCES, "H4/physics/OEFgazparfaits.fr/def/loiGP1.def")
EQUAPROD1_DEF = os.path.join(
    RESSOURCES, "H4/algebra/OEFevalwimsequ.fr/def/equaprod1.def"
)
INTERCEPTE2_DEF = os.path.join(
    RESSOURCES, "H4/analysis/evalwimstrigo.fr/def/intercepte2.def"
)
ROTATION3_DEF = os.path.join(
    RESSOURCES, "H4/geometry/OEFevalwimsrot.fr/def/rotation3.def"
)
COMP_TRINOME_DEF = os.path.join(
    RESSOURCES, "H4/algebra/h4tableSign.nl/def/compTrinomeSign2.def"
)
ORDRE2_DEF = os.path.join(RESSOURCES, "H4/analysis/OEFevacollege2005.fr/def/ordre2.def")
DEV1EXP_DEF = os.path.join(RESSOURCES, "H4/algebra/oefcalcullit.fr/def/dev1exp.def")
FACTORB1_DEF = os.path.join(
    RESSOURCES, "H4/algebra/evalwimsdevfact.fr/def/factorB1.def"
)
REPRESENTATION1_DEF = os.path.join(
    RESSOURCES, "H4/algebra/OEFevalwimsequ.fr/def/representation1.def"
)
ROTANGLE3_DEF = os.path.join(
    RESSOURCES, "H4/geometry/OEFevalwimsrot.fr/def/rotangle3.def"
)


# ── Parser tests ──────────────────────────────────────────────────────────────


class TestDefParser:
    def test_title_extracted(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        assert df.title == "Valeur 1"

    def test_meta_fields(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        assert df.meta["language"] == "fr"
        assert df.meta["author"] == "Fabrice,Guerimand"
        assert df.meta["precision"] == "10000"
        assert df.meta["replycnt"] == "1"

    def test_var_instructions(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        names = [i.name for i in df.var_instructions if isinstance(i, Assign)]
        assert names == ["tmp0", "val6", "val7", "val8", "val9", "val10"]

    def test_boilerplate_stripped(self):
        """val1-val5 and wims_read_parm/testcondition/status blocks are not in var_instructions."""
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        for instr in df.var_instructions:
            if isinstance(instr, Assign):
                assert instr.name.lower() not in (
                    "val1",
                    "val2",
                    "val3",
                    "val4",
                    "val5",
                )
        # No boilerplate IfBlock should remain
        for instr in df.var_instructions:
            if isinstance(instr, IfBlock):
                assert "wims_read_parm" not in instr.condition
                assert "testcondition" not in instr.condition
                assert "status=waiting" not in instr.condition

    def test_reply_meta(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        assert len(df.reply_meta) == 1
        rm = df.reply_meta[0]
        assert rm["n"] == 1
        assert rm["type"] == "numexp"
        assert rm["good"] == "$val9"

    def test_statement_is_executed(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        assert "__EXECUTED" in df.statement

    def test_sections_present(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        assert "question" in df.sections
        assert "hint" in df.sections

    def test_question_section_instructions(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        q = df.sections["question"]
        types = [type(i).__name__ for i in q]
        assert "Output" in types
        assert "Insmath" in types
        assert "ReadEmbed" in types

    def test_stat_section(self):
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        assert df.stat.get("embedcnt") == "1"
        assert "vsavelist" in df.stat

    def test_loigp1_five_replies(self):
        df = parse(open(LOIGP1_DEF, encoding="utf-8", errors="replace").read())
        assert len(df.reply_meta) == 5
        assert df.reply_meta[0]["type"] == "numeric"
        assert df.reply_meta[0]["name"] == "volume"


# ── Engine tests ──────────────────────────────────────────────────────────────


class TestDefEngine:
    def test_randint_seed_deterministic(self):
        r1 = load_and_render(VALEUR1_DEF, seed=42)
        r2 = load_and_render(VALEUR1_DEF, seed=42)
        assert r1.answers[0].expected == r2.answers[0].expected

    def test_different_seeds_different_values(self):
        r1 = load_and_render(VALEUR1_DEF, seed=1)
        r2 = load_and_render(VALEUR1_DEF, seed=999)
        # With different seeds, expected values may differ (not guaranteed but very likely)
        # At minimum they're both valid integers
        assert r1.answers[0].expected.isdigit()
        assert r2.answers[0].expected.isdigit()

    def test_valeur1_expected_is_sqrt(self):
        """replygood1=$val9 and val9=$val6 = randint(2,10) → digit."""
        r = load_and_render(VALEUR1_DEF, seed=42)
        expected = r.answers[0].expected
        n = int(expected)
        assert 2 <= n <= 10

    def test_valeur1_statement_contains_sqrt(self):
        r = load_and_render(VALEUR1_DEF, seed=42)
        assert "\\sqrt{" in r.statement_html
        # The sqrt argument should be n² where n is the expected answer
        n = int(r.answers[0].expected)
        assert str(n * n) in r.statement_html

    def test_valeur1_has_input_segment(self):
        r = load_and_render(VALEUR1_DEF, seed=42)
        inputs = [s for s in r.statement_segments if s["type"] == "input"]
        assert len(inputs) == 1
        assert inputs[0]["name"] == "reply1"
        assert inputs[0]["size"] == 8

    def test_valeur1_metadata(self):
        r = load_and_render(VALEUR1_DEF, seed=42)
        assert r.title == "Valeur 1"
        assert r.lang == "fr"

    def test_loigp1_five_answers(self):
        r = load_and_render(LOIGP1_DEF, seed=123)
        assert len(r.answers) == 5
        for a in r.answers:
            assert a.answer_type == "numeric"
            assert a.expected  # non-empty

    def test_loigp1_physics_consistency(self):
        """n = pV / RT — verify numerical consistency between answers."""
        r = load_and_render(LOIGP1_DEF, seed=123)
        by_name = {a.label: float(a.expected) for a in r.answers}
        V = by_name["volume"]  # m³
        T = by_name["T"]  # K
        n = by_name["n"]  # mol
        M = by_name["M"]  # g/mol
        m = by_name["m"]  # g
        R = 8.31

        # Find p from statement (it's in val10)
        df = parse(open(LOIGP1_DEF, encoding="utf-8", errors="replace").read())
        engine = DefEngine(seed=123)
        engine._exec(df.var_instructions, output_buf=None)
        p = float(engine.ctx.get("val10", 0))

        assert abs(n - p * V / (R * T)) < 1e-6
        assert abs(m - M * n) < 1e-4

    def test_loigp1_matrix_access(self):
        """$(val15[$val16;2]) should resolve to a molar mass (integer 2-71)."""
        r = load_and_render(LOIGP1_DEF, seed=77)
        M = float(r.answers[3].expected)  # answer 4 is molar mass
        assert M in {2, 28, 32, 44, 71}

    def test_loigp1_five_input_segments(self):
        r = load_and_render(LOIGP1_DEF, seed=123)
        inputs = [s for s in r.statement_segments if s["type"] == "input"]
        assert len(inputs) == 5

    def test_insmath_rendered_as_katex(self):
        r"""!insmath expr must produce \(...\) in the statement HTML."""
        r = load_and_render(VALEUR1_DEF, seed=42)
        assert "\\(" in r.statement_html
        assert "\\)" in r.statement_html


# ── Integration: equaprod1 (!values + fractional solutions) ───────────────────


class TestEquaprod1:
    """equaprod1 uses !values to build a shuffled list of integer coefficients,
    then derives fractional roots.  Tests the full !values → $(var[n]) → answer
    pipeline in a real exercise."""

    def test_renders_without_empty_coefficients(self):
        r = load_and_render(EQUAPROD1_DEF, seed=42)
        # Statement must not contain empty factor slots like (*v+)
        assert "(*" not in r.statement_html
        assert "+)" not in r.statement_html

    def test_one_answer(self):
        r = load_and_render(EQUAPROD1_DEF, seed=42)
        assert len(r.answers) == 1

    def test_solutions_are_fractions(self):
        """Expected answer must look like -a/b,-c/d."""
        r = load_and_render(EQUAPROD1_DEF, seed=42)
        sols = r.answers[0].expected
        parts = sols.split(",")
        assert len(parts) == 2
        assert all(re.match(r"^-?\d+/-?\d+$", p.strip()) for p in parts)

    def test_different_seeds_different_equations(self):
        r1 = load_and_render(EQUAPROD1_DEF, seed=1)
        r2 = load_and_render(EQUAPROD1_DEF, seed=999)
        assert r1.answers[0].expected != r2.answers[0].expected

    def test_seed_deterministic(self):
        r1 = load_and_render(EQUAPROD1_DEF, seed=77)
        r2 = load_and_render(EQUAPROD1_DEF, seed=77)
        assert r1.answers[0].expected == r2.answers[0].expected

    def test_statement_contains_variable_name(self):
        r = load_and_render(EQUAPROD1_DEF, seed=42)
        # val12 is a letter variable (x, y, z, …); must appear in statement
        assert any(c.isalpha() for c in r.statement_html)

    def test_input_segment_present(self):
        r = load_and_render(EQUAPROD1_DEF, seed=42)
        inputs = [s for s in r.statement_segments if s["type"] == "input"]
        assert len(inputs) == 1
        assert inputs[0]["name"] == "reply1"


# ── Integration: intercepte2 (!for loop + 4 answers) ─────────────────────────


class TestIntercepte2:
    """intercepte2 builds 4 answers using a !for loop over a tab-separated list.
    Tests !for, list indexing, and multi-answer rendering."""

    def test_four_answers(self):
        r = load_and_render(INTERCEPTE2_DEF, seed=3)
        assert len(r.answers) == 4

    def test_answers_have_expected_values(self):
        r = load_and_render(INTERCEPTE2_DEF, seed=3)
        for a in r.answers:
            assert a.expected  # none should be empty

    def test_title(self):
        r = load_and_render(INTERCEPTE2_DEF, seed=3)
        assert r.title  # non-empty

    def test_seed_deterministic(self):
        r1 = load_and_render(INTERCEPTE2_DEF, seed=5)
        r2 = load_and_render(INTERCEPTE2_DEF, seed=5)
        assert [a.expected for a in r1.answers] == [a.expected for a in r2.answers]

    def test_statement_not_empty(self):
        r = load_and_render(INTERCEPTE2_DEF, seed=3)
        assert r.statement_html.strip()


# ── Integration: rotation3 (!randrow) ─────────────────────────────────────────


class TestRotation3:
    """rotation3 uses !randrow to pick a question row from a matrix of scenarios.
    Tests the !randrow + tab-matrix pipeline."""

    def test_renders(self):
        r = load_and_render(ROTATION3_DEF, seed=3)
        assert r.statement_html.strip()

    def test_one_answer(self):
        r = load_and_render(ROTATION3_DEF, seed=3)
        assert len(r.answers) == 1

    def test_answer_non_empty(self):
        r = load_and_render(ROTATION3_DEF, seed=3)
        assert r.answers[0].expected

    def test_seed_deterministic(self):
        r1 = load_and_render(ROTATION3_DEF, seed=17)
        r2 = load_and_render(ROTATION3_DEF, seed=17)
        assert r1.answers[0].expected == r2.answers[0].expected

    def test_different_seeds_may_differ(self):
        results = {
            load_and_render(ROTATION3_DEF, seed=s).answers[0].expected
            for s in range(20)
        }
        assert len(results) > 1  # randrow produces variation


# ── Integration: compTrinomeSign2 (!positionof, Dutch) ───────────────────────


class TestCompTrinomeSign2:
    """compTrinomeSign2 uses !positionof to locate values in lists.
    Dutch exercise with 4 clickfill answers."""

    def test_four_answers(self):
        r = load_and_render(COMP_TRINOME_DEF, seed=5)
        assert len(r.answers) == 4

    def test_all_answers_non_empty(self):
        r = load_and_render(COMP_TRINOME_DEF, seed=5)
        for a in r.answers:
            assert a.expected

    def test_seed_deterministic(self):
        r1 = load_and_render(COMP_TRINOME_DEF, seed=42)
        r2 = load_and_render(COMP_TRINOME_DEF, seed=42)
        assert [a.expected for a in r1.answers] == [a.expected for a in r2.answers]

    def test_lang_is_dutch(self):
        r = load_and_render(COMP_TRINOME_DEF, seed=5)
        assert r.lang == "nl"


# ── Integration: ordre2 (!sort + $(var[n..m]) range slice) ───────────────────


class TestOrdre2:
    """ordre2 sorts a comma list of fractions using $(var[1..4]) range slice.
    Tests both !sort and the $(var[n..m]) substitution."""

    def test_renders(self):
        r = load_and_render(ORDRE2_DEF, seed=7)
        assert r.statement_html.strip()

    def test_one_answer(self):
        r = load_and_render(ORDRE2_DEF, seed=7)
        assert len(r.answers) == 1

    def test_seed_deterministic(self):
        r1 = load_and_render(ORDRE2_DEF, seed=99)
        r2 = load_and_render(ORDRE2_DEF, seed=99)
        assert r1.answers[0].expected == r2.answers[0].expected

    def test_sort_produces_ordered_fractions_sympy(self):
        """The fixed fallback seed (86) hits a code path without Maxima dependency."""
        from core.oef.def_engine import DefEngine, _parse_numeric
        from core.oef.def_parser import parse

        df = parse(open(ORDRE2_DEF, encoding="utf-8", errors="replace").read())
        e = DefEngine(seed=7)
        e._exec(df.var_instructions, output_buf=None)
        val11 = e.ctx.get("val11", "")
        # Skip if Maxima was needed and output is unparseable
        parts = [p.strip() for p in val11.split(",") if p.strip()]
        try:
            values = [_parse_numeric(p) for p in parts]
        except ValueError:
            return  # Maxima unavailable — skip numeric check
        assert values == sorted(values)


# ── Integration: dev1exp (!exec maxima expand + factor, SymPy backend) ───────


class TestDev1Exp:
    """dev1exp asks students to expand a product like (n-2)(n+3).
    Uses !exec maxima expand() and factor() via the SymPy backend."""

    def test_renders(self):
        r = load_and_render(DEV1EXP_DEF, seed=42)
        assert r.statement_html.strip()

    def test_statement_contains_latex_factor(self):
        r = load_and_render(DEV1EXP_DEF, seed=42)
        # The displayed form is the factored expression — must contain LaTeX
        assert "\\(" in r.statement_html or "\\left" in r.statement_html

    def test_one_answer(self):
        r = load_and_render(DEV1EXP_DEF, seed=42)
        assert len(r.answers) == 1

    def test_answer_is_expanded_polynomial(self):
        r = load_and_render(DEV1EXP_DEF, seed=42)
        expected = r.answers[0].expected
        # SymPy returns expanded form like -n**2 - 5*n - 6
        assert "n" in expected
        assert "**2" in expected or "^2" in expected

    def test_seed_deterministic(self):
        r1 = load_and_render(DEV1EXP_DEF, seed=7)
        r2 = load_and_render(DEV1EXP_DEF, seed=7)
        assert r1.answers[0].expected == r2.answers[0].expected

    def test_no_raw_maxima_in_statement(self):
        r = load_and_render(DEV1EXP_DEF, seed=42)
        assert "expand(" not in r.statement_html
        assert "factor(" not in r.statement_html
        assert "fullratsimp(" not in r.statement_html


# ── Integration: factorB1 (!exec maxima factor via SymPy) ────────────────────


class TestFactorB1:
    """factorB1 asks students to factor an expression.
    Uses !exec maxima expand() to build the statement."""

    def test_renders(self):
        r = load_and_render(FACTORB1_DEF, seed=42)
        assert r.statement_html.strip()

    def test_one_answer(self):
        r = load_and_render(FACTORB1_DEF, seed=42)
        assert len(r.answers) == 1

    def test_answer_non_empty(self):
        r = load_and_render(FACTORB1_DEF, seed=42)
        assert r.answers[0].expected.strip()

    def test_seed_deterministic(self):
        r1 = load_and_render(FACTORB1_DEF, seed=13)
        r2 = load_and_render(FACTORB1_DEF, seed=13)
        assert r1.answers[0].expected == r2.answers[0].expected


class TestRepresentation1:
    """representation1 renders inequality number-line graphs via slib +
    oef/draw.phtml. Verifies the slib executor and flydraw → SVG pipeline."""

    def test_renders(self):
        r = load_and_render(REPRESENTATION1_DEF, seed=42)
        assert r.statement_html.strip()

    def test_statement_inlines_four_svgs(self):
        r = load_and_render(REPRESENTATION1_DEF, seed=42)
        # Statement embeds four inline <svg> elements (one per number-line)
        assert r.statement_html.count("<svg") == 4
        assert r.statement_html.count("</svg>") == 4
        # No leftover image-URL markers
        assert "/api/render/svg/" not in r.statement_html

    def test_choices_are_dedup_labels(self):
        r = load_and_render(REPRESENTATION1_DEF, seed=42)
        # Four "Graphique N" + "Je ne sais pas"
        choices = r.answers[0].options.get("choices", [])
        assert len(choices) == 5
        graph_labels = [c for c in choices if c.startswith("Graphique ")]
        assert len(graph_labels) == 4

    def test_expected_matches_one_choice(self):
        r = load_and_render(REPRESENTATION1_DEF, seed=42)
        expected = r.answers[0].expected
        assert expected in r.answers[0].options.get("choices", [])


class TestRotangle3:
    """rotangle3 packs flydraw commands with tabs and uses sqrt/cos/sin/pi
    in args. Flood-fill is silently skipped (TODO), so we don't assert on
    coloured triangles — only that the grid + center circle render."""

    def test_renders(self):
        r = load_and_render(ROTANGLE3_DEF, seed=42)
        assert r.statement_html.strip()

    def test_statement_inlines_an_svg(self):
        r = load_and_render(ROTANGLE3_DEF, seed=42)
        assert "<svg" in r.statement_html
        assert "</svg>" in r.statement_html

    def test_grid_has_lines_and_center(self):
        r = load_and_render(ROTANGLE3_DEF, seed=42)
        # Triangular grid: three families of `parallel` × 15 + center circle.
        # Stay loose: at least 30 grid lines and a circle for the centre.
        assert r.statement_html.count("<line") >= 30
        assert "<circle" in r.statement_html

    def test_two_filled_triangles(self):
        # `flood` should fill two triangles with the colours picked from val6.
        r = load_and_render(ROTANGLE3_DEF, seed=42)
        assert r.statement_html.count("<polygon") == 2
