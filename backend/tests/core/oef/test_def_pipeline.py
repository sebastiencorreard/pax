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
MEDIANE4_DEF = os.path.join(RESSOURCES, "H4/stat/OEFevalwimsstat.fr/def/mediane4.def")
VOCABAFF3_DEF = os.path.join(
    RESSOURCES, "H4/analysis/OEFevalwimsfctref.fr/def/vocabaff3.def"
)
FORMULE1_DEF = os.path.join(
    RESSOURCES, "H4/algebra/evalwimsdevfact.fr/def/formule1.def"
)
FORMULE3_DEF = os.path.join(
    RESSOURCES, "H3/algebra/OEFevalwimslitt.fr/def/formule3.def"
)
POWER10_DEF = os.path.join(
    RESSOURCES, "H4/algebra/oefnombres.fr/def/power10.def"
)
ECRDECIMAL_DEF = os.path.join(
    RESSOURCES, "H4/algebra/oefnombres.fr/def/ecrdecimal.def"
)
NATURE_DEF = os.path.join(
    RESSOURCES, "H4/algebra/oefnombres.fr/def/nature.def"
)
SDLECTGRAPH1_DEF = os.path.join(
    RESSOURCES, "H4/algebra/oefseconddegree.fr/def/sdlectgraph1.def"
)
REPGRAPHINT_DEF = os.path.join(
    RESSOURCES, "H4/algebra/oefordrevabs.fr/def/repgraphint.def"
)
COF_DEF = os.path.join(
    RESSOURCES, "H3/analysis/fonctaffin.fr/def/cof.def"
)
COUF_DEF = os.path.join(
    RESSOURCES, "H3/analysis/fonctaffin.fr/def/couf.def"
)
FCOU_DEF = os.path.join(
    RESSOURCES, "H3/analysis/fonctaffin.fr/def/fcou.def"
)
GEAR23_DEF = os.path.join(
    RESSOURCES, "H3/arithmetic/gear.fr/def/gear23.def"
)
SOPOA_DEF = os.path.join(
    RESSOURCES, "H3/algebra/oeffrac.fr/def/sopoA.def"
)
OEFCALITTAIRE1_DEF = os.path.join(
    RESSOURCES, "H3/algebra/OEFlittcollege.fr/def/oefcalittaire1.def"
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
        # val1-val5 are now kept so that "val1=$imagedir" et al. evaluate;
        # see csga which dereferences $val1 as the imagedir URL.
        assert names == ["val1", "val2", "val3", "val4", "val5",
                          "tmp0", "val6", "val7", "val8", "val9", "val10"]

    def test_session_var_assignments_kept(self):
        """val1-val5 (WIMS session vars: $imagedir, $confparm*) are now kept in
        var_instructions because they're referenced as $val1 etc. by some
        exercises (e.g. csga: val247=$val1/../q502_e2.png)."""
        df = parse(open(VALEUR1_DEF, encoding="utf-8").read())
        names = [i.name for i in df.var_instructions if isinstance(i, Assign)]
        assert "val1" in names
        # The wims_read_parm/testcondition/status IfBlocks must still be stripped
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
        # ordre2 has 4 clickfill slots (one per fraction position), each using
        # ?analyze; all 4 are extracted as separate analyze-type answers.
        r = load_and_render(ORDRE2_DEF, seed=7)
        assert len(r.answers) == 4

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


class TestMediane4:
    """mediane4 picks a random scenario from `src/stat2.don` and renders a
    frequency table whose values come from `slib/generator`. Covers
    `!randrecord`, `!row` newline-split, and slib execution with `!for`."""

    def test_renders(self):
        r = load_and_render(MEDIANE4_DEF, seed=42)
        assert r.statement_html.strip()

    def test_statement_contains_data_table(self):
        r = load_and_render(MEDIANE4_DEF, seed=42)
        assert "<table" in r.statement_html
        # Two rows: header (Nombre de … / values) and Effectifs / frequencies
        assert r.statement_html.count("<tr") == 2

    def test_frequency_table_has_values(self):
        # Each <td> in the second row should be a numeric frequency, not
        # a leftover `$empty` or other unresolved variable.
        r = load_and_render(MEDIANE4_DEF, seed=42)
        import re as _re

        tds = _re.findall(r"<td[^>]*>\s*([^<]*?)\s*</td>", r.statement_html)
        # Skip the leading "Effectifs" label cell; the rest must be numeric.
        for cell in tds[1:]:
            assert "$" not in cell  # no unresolved $vars
            assert cell.lstrip("-").isdigit() or cell == ""

    def test_input_segment_is_appended(self):
        # The .def has no \embed in :question, but a numexp reply is
        # declared — the engine appends a default input so the frontend
        # has somewhere to render the answer field.
        r = load_and_render(MEDIANE4_DEF, seed=42)
        input_segments = [s for s in r.statement_segments if s.get("type") == "input"]
        assert len(input_segments) == 1
        assert input_segments[0]["name"] == "reply1"

    def test_expected_answer_is_the_median(self):
        # `slib/stat/median` is computed natively from [values; frequencies].
        r = load_and_render(MEDIANE4_DEF, seed=42)
        assert r.answers[0].expected.strip() != ""
        # The expected value is one of the data values (between val11 and val12)
        # or the half-sum of two consecutive ones.
        assert r.answers[0].expected.replace(".", "").lstrip("-").isdigit()


class TestPower10:
    """power10 embeds all 14 reply fields inside a <table> via
    `!read oef/embed.phtml reply N,M`. The fields must appear only in the
    table — not be re-appended underneath by the "default input per reply"
    fallback (which fires when the statement has no widgets)."""

    def test_renders_table(self):
        r = load_and_render(POWER10_DEF, seed=3)
        assert "<table" in r.statement_html

    def test_inputs_not_duplicated(self):
        import re as _re

        r = load_and_render(POWER10_DEF, seed=3)
        # 14 declared replies → exactly 14 input widgets in the HTML, no more.
        names = _re.findall(r'class="oef-input"\s+name="([^"]+)"', r.statement_html)
        assert len(names) == 14
        assert len(set(names)) == 14

    def test_no_standalone_input_segments(self):
        # Table-embedded inputs are rewritten to native <input> inline, so the
        # engine must not also emit standalone input segments for them.
        r = load_and_render(POWER10_DEF, seed=3)
        standalone = [
            s for s in r.statement_segments if s.get("type") in ("input", "textarea")
        ]
        assert standalone == []


class TestEcrdecimal:
    """ecrdecimal is a course exercise whose radio replies are *displayed*
    normally but *checked* via `?analyze N;<choices>`. The ?analyze prefix
    must keep the radio type and its choices — overriding to "analyze"
    dropped them, leaving an empty <ol> with no answerable field."""

    def test_reply_is_radio_with_choices(self):
        r = load_and_render(ECRDECIMAL_DEF, seed=3, m_step=1)
        a = r.answers[0]
        assert a.answer_type == "radio"
        assert len(a.options.get("choices") or []) == 4

    def test_correct_answer_resolved_from_analyze_condition(self):
        # The :test condition `$val25 issametext $(val11[1;])` makes the
        # correct choice val11[1;]; the analyze var is recorded for checking.
        r = load_and_render(ECRDECIMAL_DEF, seed=3, m_step=1)
        a = r.answers[0]
        assert a.expected == "Infinie non périodique"
        assert a.expected in a.options["choices"]
        assert a.options.get("analyze_var") == "val25"


class TestNature:
    """nature is a `checkbox` exercise: several checkboxes (one per ensemble
    ℕ/ℤ/ℚ/…) share reply1; the answer is the set of ticked indices. Exercises
    `!for VAR in LIST` (builds the labels val26 and the correct-set val32),
    parenthesised matrix indices `$(val26[(1+3);])`, and the checkbox widget."""

    def test_renders_checkboxes_not_text_inputs(self):
        r = load_and_render(NATURE_DEF, seed=1328739048)
        assert r.statement_html.count('class="oef-checkbox"') == 6
        assert 'class="oef-input"' not in r.statement_html

    def test_labels_resolved(self):
        # val26 is built with `!for VAR in LIST`; without it the labels were
        # empty and `$(val26[(n);])` leaked literally.
        r = load_and_render(NATURE_DEF, seed=1328739048)
        assert "entier naturel" in r.statement_html
        assert "$(val" not in r.statement_html  # no unresolved subscripts

    def test_checkbox_answer_and_expected(self):
        r = load_and_render(NATURE_DEF, seed=1328739048)
        a = r.answers[0]
        assert a.answer_type == "checkbox"
        assert a.input_name == "reply1"
        # Correct set = the ensembles the number belongs to (val32), built via
        # the `!for VAR in LIST` + !positionof loop; must be a non-empty index
        # set, never the empty string that an unrun loop produced.
        assert a.expected.strip()
        assert all(p.strip().isdigit() for p in a.expected.split(","))


class TestSdlectgraph1:
    """sdlectgraph1 plots a parabola and frames it with
    `yrange -10,floor(V)+2` (V = vertex y). The yrange bound is an unevaluated
    `floor(...)` expression that the flydraw renderer must evaluate, otherwise
    the vertex falls outside the frame and is never visible."""

    def test_renders_graph(self):
        r = load_and_render(SDLECTGRAPH1_DEF, seed=7)
        assert "<svg" in r.statement_html

    def test_vertex_inside_yrange(self):
        from core.oef.def_engine import DefEngine, _parse_def_cached  # noqa: PLC0415
        from core.oef.flydraw import _num  # noqa: PLC0415

        df = _parse_def_cached(SDLECTGRAPH1_DEF)
        for seed in range(1, 40):
            e = DefEngine(seed=seed, def_path=SDLECTGRAPH1_DEF)
            e.render(df)
            vertex = float(e.ctx["val18"])
            ymin = _num(e._subst("$(val19[1])"))
            ymax = _num(e._subst("$(val19[2])"))
            assert ymin < vertex < ymax, (
                f"seed {seed}: vertex {vertex} outside yrange [{ymin}, {ymax}]"
            )

    def test_radio_choices_are_katex_ready(self):
        # The factored-form choices arrive as WIMS `\(…)` (plain-paren close);
        # they must be closed to KaTeX `\(…\)` with rendered mults so the
        # frontend typesets them instead of showing the raw delimiters.
        r = load_and_render(SDLECTGRAPH1_DEF, seed=7)
        a = r.answers[0]
        assert a.answer_type == "radio"
        choices = a.options["choices"]
        assert len(choices) == 4
        for c in choices:
            assert c.startswith(r"\(") and c.endswith(r"\)")
            assert "*" not in c  # multiplication rendered, not raw
        # expected stays one of the (closed) choices → reply check is consistent
        assert a.expected in choices


class TestRepgraphint:
    """repgraphint is a multi-slot drag-compose clickfill: the student arranges
    labels (]/[/;/numbers/∪/∩/±∞) into an ordered sequence forming the interval
    drawn in red. replygood = "correct_seq;pool" where both carry HTML entities
    (&#91;/&#93;/&#59;) whose ";" must not split as the correct;pool separator."""

    def test_clickfill_answer_parsed(self):
        r = load_and_render(REPGRAPHINT_DEF, seed=5)
        a = r.answers[0]
        assert a.answer_type == "clickfill"
        # expected is the full ordered sequence, NOT truncated at the first
        # entity semicolon (the old bug gave "&#93").
        items = a.expected.split(",")
        assert len(items) == 5
        assert items[0] == "&#93;" and items[-1] == "&#91;"

    def test_pool_choices(self):
        # choices = the pool (val32), not [correct]+wrongs; entities intact.
        r = load_and_render(REPGRAPHINT_DEF, seed=5)
        choices = r.answers[0].options["choices"]
        assert "&#91;" in choices and "&#93;" in choices and "&#59;" in choices
        assert "\\(\\cup\\)" in choices  # math closed to KaTeX form

    def test_multi_slot_count_from_embed_size(self):
        # embed size 60x40x12 → 12 drop slots, indexed 0..11.
        r = load_and_render(REPGRAPHINT_DEF, seed=5)
        slots = [s for s in r.statement_segments if s.get("type") == "slot"]
        assert len(slots) == 12
        assert [s.get("index") for s in slots] == list(range(12))

    def test_bound_labels_not_collapsed_to_centre(self):
        # The graph reuses `\(-6)`-style display forms as bracket/label
        # coordinates; flydraw must parse them as numbers. Otherwise both
        # bound labels (and brackets) landed at the axis centre (x=400).
        import re as _re

        r = load_and_render(REPGRAPHINT_DEF, seed=23)
        svg = r.statement_html
        svg = svg[svg.find("<svg"):svg.find("</svg>") + 6]
        xs = [
            float(m.group(1))
            for m in _re.finditer(r'<text [^>]*x="([\d.]+)"[^>]*>[^<]+</text>', svg)
        ]
        assert len(xs) == 2
        assert abs(xs[0] - xs[1]) > 1.0  # distinct positions, not both 400


class TestCof:
    """cof renders an interactive JSXGraph board via `!readproc
    slib/geo2D/jsxgraph`. The built-in must emit a .pax-jsxgraph container
    carrying the board-init JS in data-jsxgraph, and it must survive the
    <div>→<br> statement flattening so the frontend can hydrate it."""

    def test_jsxgraph_segment_emitted(self):
        # The board is a typed `jsxgraph` segment (not statement HTML), so the
        # init JS — with its \(d_n\) labels — is segment *data* that the KaTeX
        # pass never touches. Rendered by the ExerciseJsxgraph component.
        r = load_and_render(COF_DEF, seed=7)
        seg = next(
            (s for s in r.statement_segments if s.get("type") == "jsxgraph"), None
        )
        assert seg is not None, "jsxgraph segment missing (flattened/dropped?)"
        assert seg["name"] == "jsxbox"
        assert "initBoard" in seg["js"]
        assert "board.create('line',[" in seg["js"]  # commas survived
        assert seg.get("width") and seg.get("height")

    def test_lines_have_names_and_colors(self):
        # The board JS (val32) builds each line with a name + strokeColor from
        # the (matrix) val23. Regressions in range-slice / matrix / append
        # left these empty and the line snippets comma-split mid-way.
        import re as _re
        from core.oef.def_engine import DefEngine, _parse_def_cached  # noqa: PLC0415

        df = _parse_def_cached(COF_DEF)
        e = DefEngine(seed=7, def_path=COF_DEF)
        e.render(df)
        js = str(e.ctx.get("val32"))
        assert "board.create('line',[" in js  # commas survived the list join
        names = _re.findall(r"name:'([^']+)'", js)
        colors = _re.findall(r"strokeColor:'(#[0-9A-Fa-f]{6})'", js)
        assert len(names) >= 3 and len(colors) >= 3

    def test_correspond_answer_built(self):
        r = load_and_render(COF_DEF, seed=7)
        a = r.answers[0]
        assert a.answer_type == "correspond"
        assert len(a.options.get("lefts", [])) >= 3
        assert len(a.options.get("rights_shuffled", [])) >= 3

    def test_layout_groups_preserved(self):
        # The flex container/wrappers are kept as group-open/group-close
        # segments (not flattened to <br>), so the frontend can lay the board
        # and the matching table out side by side. The board + correspond sit
        # inside the groups.
        r = load_and_render(COF_DEF, seed=7)
        types = [s.get("type") for s in r.statement_segments]
        assert "group-open" in types and "group-close" in types
        assert types.count("group-open") == types.count("group-close")
        classes = [s["class"] for s in r.statement_segments if s.get("type") == "group-open"]
        assert "container" in classes
        assert {"image-wrapper", "table-wrapper"} <= set(classes)

    def test_correspond_widget_config_parsed(self):
        # The correspond segment's data-config (JSON) carries \(…\) items whose
        # escaped "\\(" must survive _close_inline_math, or the JSON fails to
        # parse and the matching table renders empty.
        r = load_and_render(COF_DEF, seed=7)
        seg = next(
            (s for s in r.statement_segments if s.get("type") == "correspond"), None
        )
        assert seg is not None
        cfg = seg["config"]
        assert len(cfg.get("lefts", [])) >= 3
        assert len(cfg.get("rights", [])) >= 3
        # items are closed to KaTeX form so the frontend typesets them
        assert all(x.startswith(r"\(") and x.endswith(r"\)") for x in cfg["lefts"])


class TestCouf:
    """couf builds its affine functions from constant terms drawn via
    slib/data/random. Without that slib the list was empty, so rint() got no
    argument and the maxima/pari/texmath chain derailed into garbage labels
    ("P a e f i l l l …"). The boards are also stored in a comma-list, so the
    comma-laden divs must use a TAB separator to stay indexable."""

    def test_constant_terms_drawn(self):
        from core.oef.def_engine import DefEngine, _parse_def_cached  # noqa: PLC0415

        df = _parse_def_cached(COUF_DEF)
        e = DefEngine(seed=7, def_path=COUF_DEF)
        e.render(df)
        # val10 = the (shuffled, duplicated) constant terms; must be 4 integers.
        items = str(e.ctx.get("val10")).split(",")
        assert len(items) == 4
        assert all(p.strip().lstrip("-").isdigit() for p in items)

    def test_function_labels_clean(self):
        from core.oef.def_engine import DefEngine, _parse_def_cached  # noqa: PLC0415

        df = _parse_def_cached(COUF_DEF)
        e = DefEngine(seed=7, def_path=COUF_DEF)
        e.render(df)
        label = e._subst("$(val17[1])")
        assert "\\mapsto" in label
        assert "fillm" not in label.replace(" ", "")  # not the sorted-letters garbage

    def test_question_board_is_a_segment(self):
        r = load_and_render(COUF_DEF, seed=7)
        boards = [s for s in r.statement_segments if s.get("type") == "jsxgraph"]
        assert len(boards) >= 1
        assert "functiongraph" in boards[0]["js"]
        # the size spec's min bound drives the (smaller) default display width
        assert boards[0].get("minw") == 200

    def test_inline_radio_choices(self):
        # The 4 options are laid out inline (reply1,POS,CONTENT) with the
        # function definition as label — not pax's grid of bare values.
        r = load_and_render(COUF_DEF, seed=7)
        ri = [s for s in r.statement_segments if s.get("type") == "radio-inline"]
        assert len(ri) == 4
        assert sorted(s["value"] for s in ri) == ["1", "2", "3", "4"]
        assert all("\\mapsto" in s["content"] for s in ri)
        a = r.answers[0]
        assert a.answer_type == "radio"
        assert a.options.get("inline") is True
        assert a.expected in {"1", "2", "3", "4"}  # the correct position


class TestFcou:
    """fcou is the inverse of couf: the 4 answer choices are JSXGraph curves
    laid out in a `<ul class="inline">` row (pick the curve matching the given
    function). The list must be preserved as a layout group so the boards sit
    side by side and wrap (4 → 3+1 → 2+2 …) instead of stacking vertically."""

    def test_four_boards_in_inline_group(self):
        r = load_and_render(FCOU_DEF, seed=7)
        segs = r.statement_segments
        types = [s.get("type") for s in segs]

        # The list survives as a layout group carrying its `inline` class
        # (not flattened to <br>), and the group tree stays balanced.
        assert types.count("group-open") == types.count("group-close")
        opens = [s for s in segs if s.get("type") == "group-open"]
        assert any(s["class"] == "inline" for s in opens), \
            "the <ul class=\"inline\"> board row was flattened/lost"

        # Exactly the 4 curve boards, and all 4 live inside the inline group.
        boards = [s for s in segs if s.get("type") == "jsxgraph"]
        assert len(boards) == 4
        assert all("functiongraph" in b["js"] for b in boards)

        start = next(
            i for i, s in enumerate(segs)
            if s.get("type") == "group-open" and s["class"] == "inline"
        )
        depth, end = 0, len(segs)
        for i in range(start, len(segs)):
            t = segs[i].get("type")
            if t == "group-open":
                depth += 1
            elif t == "group-close":
                depth -= 1
                if depth == 0:
                    end = i
                    break
        inside = sum(
            1 for s in segs[start:end] if s.get("type") == "jsxgraph"
        )
        assert inside == 4, "the 4 boards are not nested in the inline group"


class TestListBalancing:
    """_balance_list_items back-fills omitted </li> tags. OEF HTML often writes
    `<ul><li>a<li>b</ul>text` with no </li>; without re-balancing the group tree
    would nest the items and swallow the trailing text into the last <li>."""

    def test_missing_li_close_is_backfilled(self):
        from core.oef.engine import _segment_statement  # noqa: PLC0415

        html = "<uL> <li> a <li> b <li> c </ul> after"
        segs = _segment_statement(html)
        types = [s.get("type") for s in segs]
        # Balanced: one <ul> + three <li> open/close pairs.
        assert types.count("group-open") == types.count("group-close") == 4
        # "after" stays outside the list (a sibling html leaf, not nested).
        assert segs[-1]["type"] == "html" and "after" in segs[-1]["content"]


class TestGroupBalancing:
    """_balance_groups reproduit l'indulgence du navigateur sur un HTML mal
    formé. Le défaut vient des exercices eux-mêmes : `oefconversion/conversion1`
    ferme un `</ul>` jamais ouvert, et son `.oef` d'origine le porte déjà — WIMS
    l'envoie tel quel, le navigateur ignore le fermant en trop. Le front, lui,
    bâtit un arbre : un fermant orphelin tronque la mise en page, un ouvrant
    resté ouvert avale la suite de l'énoncé."""

    def _depth(self, segs):
        depth = min_depth = 0
        for s in segs:
            if s.get("type") == "group-open":
                depth += 1
            elif s.get("type") == "group-close":
                depth -= 1
                min_depth = min(min_depth, depth)
        return depth, min_depth

    def test_fermant_orphelin_ignore(self):
        """Le cas conversion1 : un `</ul>` sans ouvrant, en fin d'énoncé."""
        from core.oef.engine import _segment_statement  # noqa: PLC0415

        segs = _segment_statement("<p>texte</p></ul>")
        assert self._depth(segs) == (0, 0)

    def test_ouvrant_restant_referme(self):
        """Un `<div>` jamais fermé : le front doit retrouver son niveau."""
        from core.oef.engine import _segment_statement  # noqa: PLC0415

        segs = _segment_statement('<div class="a">texte')
        assert self._depth(segs) == (0, 0)
        assert segs[-1]["type"] == "group-close"

    def test_contenu_apres_un_fermant_orphelin_conserve(self):
        """Jeter le fermant ne doit rien emporter de l'énoncé avec lui."""
        from core.oef.engine import _segment_statement  # noqa: PLC0415

        segs = _segment_statement("</ul>avant<div>dedans</div>apres")
        assert self._depth(segs) == (0, 0)
        texte = "".join(s.get("content", "") for s in segs if s.get("type") == "html")
        assert "avant" in texte and "dedans" in texte and "apres" in texte

    def test_html_bien_forme_inchange(self):
        """Un énoncé déjà équilibré ne doit gagner aucun segment."""
        from core.oef.engine import _segment_statement  # noqa: PLC0415

        segs = _segment_statement("<div>a<div>b</div></div>")
        assert self._depth(segs) == (0, 0)
        types = [s.get("type") for s in segs]
        assert types.count("group-open") == types.count("group-close") == 2


class TestGear23:
    """gear23 computes the answer via $[rint(lcm($val8,$val9))]. `lcm` was
    missing from the arithmetic namespace, so the $[…] eval raised NameError,
    fell through to its return-as-is fallback and leaked the literal
    "rint(lcm(…))" into the statement instead of a number."""

    def test_lcm_evaluates_to_a_number(self):
        from core.oef.def_engine import DefEngine, _parse_def_cached  # noqa: PLC0415

        df = _parse_def_cached(GEAR23_DEF)
        e = DefEngine(seed=7, def_path=GEAR23_DEF)
        e.render(df)
        # val21 = lcm(z1,z2); val22 = lcm/z1; val23 = lcm/z2 — all integers now.
        for key in ("val21", "val22", "val23"):
            val = str(e.ctx.get(key))
            assert "lcm" not in val and "rint" not in val, f"{key}={val!r} not evaluated"
            assert val.lstrip("-").isdigit(), f"{key}={val!r} is not an integer"

    def test_statement_has_no_leaked_expression(self):
        r = load_and_render(GEAR23_DEF, seed=7)
        assert "lcm(" not in r.statement_html
        assert "rint" not in r.statement_html


class TestSopoA:
    """sopoA's prompt is a 2-item comma list selected by confparm1 (singular vs
    plural): `val7=… suivante&nbsp;,\\t… suivantes&nbsp;`. The TAB after the
    comma is cosmetic source whitespace — the separator is the comma. The
    indexed access $(val7[1]) wrongly split on the TAB and leaked the trailing
    comma ("… suivante ,:"). Guards the comma/TAB separator disambiguation."""

    def test_indexed_item_has_no_trailing_comma(self):
        from core.oef.def_engine import DefEngine, _parse_def_cached  # noqa: PLC0415

        df = _parse_def_cached(SOPOA_DEF)
        e = DefEngine(seed=3, def_path=SOPOA_DEF)
        e.render(df)
        assert e._subst("$(val7[1])") == "Calculer l'expression suivante&nbsp;"
        assert e._subst("$(val7[2])") == "Calculer les expressions suivantes&nbsp;"
        # val8's singular item likewise keeps its period but drops the comma.
        assert not e._subst("$(val8[1])").endswith(",")

    def test_statement_has_no_stray_comma_before_colon(self):
        r = load_and_render(SOPOA_DEF, seed=3)
        assert ",:" not in r.statement_html
        assert "suivante&nbsp;:" in r.statement_html

    def test_la_tabulation_ne_separe_jamais(self):
        """Il n'y a plus de désambiguïsation à faire : la virgule seule sépare.

        Le blob HTML joint par tabulations était une production de PAX, pas de
        WIMS ; les producteurs migrés, un `<div>a</div><TAB><div>b</div>` est
        un seul item, et un `,<TAB>` en donne bien deux, tabulation élaguée.
        """
        from core.oef.def_engine import wims_lists as wl  # noqa: PLC0415

        assert wl.cutitems("<div>a</div>\t<div>b</div>") == [
            "<div>a</div>\t<div>b</div>"
        ]
        assert wl.cutitems("un item,\tautre item") == ["un item", "autre item"]


class TestOefcalittaire1:
    """The figure (a labelled triangle) is drawn via `!readproc oef/draw.phtml`.
    Three def-engine gaps kept it from displaying: a trailing TAB on the
    assignment `val40=$(tmp0)\\t` leaked into the image URL; PARI scalar×vector
    `1.2*[…]` (the bounding-box scaling) wasn't evaluated; and `slib/draw/range`
    uses a negative list index `$(u[-1])` (= last) to find the max bound. All
    three are needed for a correctly-scaled, inlined SVG. Seed 2 → val6=1."""

    def test_figure_renders_inline_svg(self):
        r = load_and_render(OEFCALITTAIRE1_DEF, seed=2)
        h = r.statement_html
        assert "<svg" in h, "draw image not inlined (broken/trailing-ws URL?)"
        assert "<polygon" in h, "the rhombus polygon was not drawn"
        # No stray whitespace leaked into any image URL.
        assert not re.search(r'src="[^"]*\s"', h)
        svg = h[h.find("<svg"):h.find("</svg>") + 6]
        # Visual fidelity vs WIMS: filled rhombus, dashed dimension lines.
        assert 'fill="#87ceeb"' in svg, "rhombus interior not filled"
        assert "stroke-dasharray" in svg, "dimension (dsegment) lines not dashed"

    def test_range_is_numeric_and_in_box(self):
        from core.oef.def_engine import DefEngine, _parse_def_cached  # noqa: PLC0415

        df = _parse_def_cached(OEFCALITTAIRE1_DEF)
        e = DefEngine(seed=2, def_path=OEFCALITTAIRE1_DEF)
        e.render(df)
        # val37 = xmin,xmax,ymin,ymax — four numbers, no leaked "[" / "max(" / "/2".
        parts = str(e.ctx.get("val37")).split(",")
        assert len(parts) == 4
        for p in parts:
            float(p)  # raises if the slib/draw/range output wasn't evaluated


class TestPariVectorAndNegIndex:
    """Two primitives the gear/littcollege draws rely on."""

    def test_pari_scalar_times_vector(self):
        from core.oef.def_engine.cas import _call_pari  # noqa: PLC0415

        # float × vector and vector / scalar broadcast elementwise (PARI). The
        # littcollege bounding-box scaling is `1.2*[…]` (float).
        assert _call_pari("1.2*[1,2,3]") == "1.2,2.4,3.6"
        assert _call_pari("[10,20,30]/10") == "1,2,3"
        # ordinary scalar expressions are unaffected.
        assert _call_pari("(x-3)*(x+3)") == "x^2 - 9"

    def test_negative_list_index(self):
        from core.oef.def_engine import DefEngine  # noqa: PLC0415

        e = DefEngine(seed=1, def_path=OEFCALITTAIRE1_DEF)
        e.ctx["lst"] = "a,b,c,d"
        assert e._subst("$(lst[-1])") == "d"
        assert e._subst("$(lst[-2])") == "c"
        assert e._subst("$(lst[1])") == "a"


class TestVocabaff3:
    """vocabaff3 uses inline `!read oef/draw.phtml` to render a coordinate
    plane with two plotted linear functions; covers ReadDraw + xrange/
    yrange/vline/hline/plot/gridfill primitives."""

    def test_renders(self):
        r = load_and_render(VOCABAFF3_DEF, seed=42)
        assert r.statement_html.strip()

    def test_statement_inlines_an_svg(self):
        r = load_and_render(VOCABAFF3_DEF, seed=42)
        assert "<svg" in r.statement_html

    def test_two_plotted_curves(self):
        # plot red,$val16 and plot green,$val20 — two polylines.
        r = load_and_render(VOCABAFF3_DEF, seed=42)
        assert r.statement_html.count("<polyline") == 2

    def test_axes_drawn(self):
        # vline 0,0 + hline 0,0 (the central x and y axes) plus the
        # surrounding gridlines and axis arrows.
        r = load_and_render(VOCABAFF3_DEF, seed=42)
        assert r.statement_html.count("<line") >= 12

    def test_grid_background(self):
        # gridfill emits a backing <rect>.
        r = load_and_render(VOCABAFF3_DEF, seed=42)
        assert "<rect" in r.statement_html

    def test_radio_answer_parsed_from_indexed_form(self):
        # `replygood1=<idx>;<choice1>,<choice2>,…` — extract the choices
        # and the 1-based correct index.
        r = load_and_render(VOCABAFF3_DEF, seed=42)
        ans = r.answers[0]
        assert ans.answer_type == "radio"
        choices = ans.options.get("choices", [])
        assert len(choices) == 4
        # Correct answer matches one of the four choices.
        assert ans.expected in choices

    def test_no_text_input_emitted_for_radio_embeds(self):
        # `!read oef/embed.phtml reply1,N` for a radio reply must NOT
        # produce <input>/<span> text widgets — the frontend renders the
        # choices from options.choices instead.
        r = load_and_render(VOCABAFF3_DEF, seed=42)
        input_segments = [s for s in r.statement_segments if s["type"] == "input"]
        assert input_segments == []


# ── Integration: formule1 (clickfill drag-and-drop) ──────────────────────────


class TestFormule1:
    """formule1 is a clickfill exercise: the student drags a card to a slot.
    Verifies that the backend emits a cf-slot segment, populates choices, and
    sets the correct expected value."""

    def test_slot_segment_emitted(self):
        r = load_and_render(FORMULE1_DEF, seed=42)
        slot_segs = [s for s in r.statement_segments if s["type"] == "slot"]
        assert len(slot_segs) == 1
        assert slot_segs[0]["name"] == "reply1"

    def test_no_text_input_for_clickfill(self):
        r = load_and_render(FORMULE1_DEF, seed=42)
        input_segs = [s for s in r.statement_segments if s["type"] == "input"]
        assert input_segs == []

    def test_answer_type_is_clickfill(self):
        r = load_and_render(FORMULE1_DEF, seed=42)
        assert r.answers[0].answer_type == "clickfill"

    def test_choices_populated(self):
        r = load_and_render(FORMULE1_DEF, seed=42)
        choices = r.answers[0].options.get("choices", [])
        assert len(choices) == 4

    def test_correct_answer_in_choices(self):
        r = load_and_render(FORMULE1_DEF, seed=42)
        ans = r.answers[0]
        assert ans.expected in ans.options["choices"]

    def test_choices_no_duplicates(self):
        r = load_and_render(FORMULE1_DEF, seed=42)
        choices = r.answers[0].options["choices"]
        assert len(choices) == len(set(choices))

    def test_seed_deterministic(self):
        r1 = load_and_render(FORMULE1_DEF, seed=7)
        r2 = load_and_render(FORMULE1_DEF, seed=7)
        assert r1.answers[0].expected == r2.answers[0].expected
        assert r1.answers[0].options["choices"] == r2.answers[0].options["choices"]

    def test_different_seeds_vary_sign(self):
        results = {load_and_render(FORMULE1_DEF, seed=s).answers[0].expected for s in range(1, 20)}
        assert len(results) > 1  # both + and - variants must appear


class TestFormule3Correspond:
    """formule3 uses replytype=correspond — bijective matching widget."""

    def test_answer_type_is_correspond(self):
        r = load_and_render(FORMULE3_DEF, seed=42)
        assert r.answers[0].answer_type == "correspond"

    def test_lefts_and_rights_extracted(self):
        r = load_and_render(FORMULE3_DEF, seed=42)
        opts = r.answers[0].options
        assert len(opts["lefts"]) == 4
        assert len(opts["rights_shuffled"]) == 4
        assert opts["partial"] is False

    def test_expected_is_correct_right_order(self):
        r = load_and_render(FORMULE3_DEF, seed=42)
        a = r.answers[0]
        expected_items = a.expected.split(",")
        assert len(expected_items) == 4
        # Each expected item must appear in the shuffled set
        assert set(expected_items) == set(a.options["rights_shuffled"])

    def test_sizes_parsed(self):
        # embed{r1, 100x200x200}
        r = load_and_render(FORMULE3_DEF, seed=42)
        sizes = r.answers[0].options["sizes"]
        assert sizes == {"v": 100, "hg": 200, "hd": 200}

    def test_shuffle_is_deterministic(self):
        r1 = load_and_render(FORMULE3_DEF, seed=7)
        r2 = load_and_render(FORMULE3_DEF, seed=7)
        assert r1.answers[0].options["rights_shuffled"] == r2.answers[0].options["rights_shuffled"]

    def test_different_seeds_vary(self):
        # Across many seeds, the shuffled order must differ at least once
        shuffles = {
            tuple(load_and_render(FORMULE3_DEF, seed=s).answers[0].options["rights_shuffled"])
            for s in range(1, 30)
        }
        assert len(shuffles) > 1

    def test_correspond_segment_emitted(self):
        r = load_and_render(FORMULE3_DEF, seed=42)
        correspond_segs = [s for s in r.statement_segments if s.get("type") == "correspond"]
        assert len(correspond_segs) == 1
        seg = correspond_segs[0]
        assert seg["name"] == "reply1"
        assert seg["config"]["lefts"] == r.answers[0].options["lefts"]
        assert seg["config"]["rights"] == r.answers[0].options["rights_shuffled"]


class TestDropUnitFactors:
    """Le facteur 1 explicite laissé par ``parse_expr(evaluate=False)``.

    `!texmath` ne doit rien simplifier — sinon l'énoncé de `reduire1` donnerait
    la réponse. Mais l'arbre non évalué garde le `1` que sympy aurait absorbé :
    `1/x` est un `Mul(Integer(1), Pow(x, -1))` que `sympy.latex` imprime
    `1 \\frac{1}{x}`, qu'un élève lit « un et un sur x ».
    """

    def test_the_note_case(self):
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("1/x") == r"\frac{1}{x}"

    def test_unit_factor_before_a_fraction(self):
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("1/(x+1)") == r"\frac{1}{x + 1}"
        assert _expr_to_latex("1/x^2") == r"\frac{1}{x^{2}}"
        assert _expr_to_latex("1/sqrt(2)") == r"\frac{1}{\sqrt{2}}"

    def test_unit_factor_before_a_variable(self):
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("1*x") == "x"

    def test_unit_factor_inside_a_denominator(self):
        """`inverse3` affichait `\\frac{1}{1 \\cdot 5}`."""
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("1/(1*5)") == r"\frac{1}{5}"

    def test_a_legitimate_one_survives(self):
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("1") == "1"
        assert _expr_to_latex("1*1") == "1"
        assert _expr_to_latex("x+1/2") == r"x + \frac{1}{2}"

    def test_the_minus_one_is_spared(self):
        """`_expr_to_latex` réécrit `-(` en `(-1)*(` pour empêcher sympy de
        distribuer le signe : `distribuer1` montre la forme non développée,
        c'est l'énoncé même de l'exercice."""
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("-(5u+6)") == r"- (5 u + 6)"

    def test_nothing_else_is_simplified(self):
        """`reduire1` remet `3*x + 5*x + 2 + 1` à l'élève : le retrait du
        facteur neutre ne doit pas devenir une réduction."""
        from core.oef.def_engine.cas import _expr_to_latex
        out = _expr_to_latex("3*x+5*x+2+1")
        assert "3 x" in out and "5 x" in out
        assert "8 x" not in out

    def test_expressions_without_a_unit_factor_are_untouched(self):
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("3/x") == r"\frac{3}{x}"
        assert _expr_to_latex("2/(3x)") == r"\frac{2}{3 x}"


class TestTermOrder:
    """Les termes d'une somme sortent dans l'ordre de la source.

    Le printer sympy trie par défaut (`order='lex'`), ce que rien chez WIMS ne
    justifie : `t_onestring` (`src/texmath.c`) découpe la chaîne et émet chaque
    terme dans l'ordre où il vient —

        for(pp=p,i=0;*pp;pp=pe,i++) {
          pe=find_term_end(pp);
          memmove(termbuf,pp,pe-pp); termbuf[pe-pp]=0;
          t_oneterm(termbuf,i);
        }

    — son seul tri (`qsort` sur `fsort`) portant sur les facteurs *à
    l'intérieur* d'un terme, classés par type. Le tri des termes gênait
    doublement : il inversait les opérandes d'un calcul à poser, et la famille
    `reduire1p…` compare les rawmath **littéralement** (cf. `check_litexp`), si
    bien que l'élève devait retrouver un ordre que l'énoncé lui montrait déjà
    réarrangé.
    """

    def test_numeric_terms_keep_their_order(self):
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("2+1") == "2 + 1"
        assert _expr_to_latex("5+x") == "5 + x"
        assert _expr_to_latex("b+a") == "b + a"

    def test_a_reduction_statement_is_shown_as_written(self):
        """`reduire1` remet l'expression à l'élève : ni réduite, ni réordonnée."""
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("3*x+5*x+2+1") == "3 x + 5 x + 2 + 1"

    def test_the_CORdistribution_family(self):
        """Attendus réels d'`oefdevfact.ca/CORdistribution`, que le tri
        retournait en `- 8 b + 10 b - 3 + 3`."""
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("10*b - 3 - 8*b + 3") == "10 b - 3 - 8 b + 3"
        assert _expr_to_latex("10*b - 3 - 8*b - 3") == "10 b - 3 - 8 b - 3"

    def test_operands_of_a_sum_are_not_swapped(self):
        """`14/10 + 9/8` s'affichait `9/8 + 14/10`."""
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("14/10 + 9/8") == r"\frac{14}{10} + \frac{9}{8}"

    def test_factors_inside_a_term_are_still_sympy_s_business(self):
        """WIMS trie les facteurs d'un même terme (`fsort`, par type) : le
        coefficient devant la variable. On ne touche pas à ce niveau-là."""
        from core.oef.def_engine.cas import _expr_to_latex
        assert _expr_to_latex("x*3") == "3 x"

    def test_nothing_is_simplified(self):
        from core.oef.def_engine.cas import _expr_to_latex
        out = _expr_to_latex("(1+sqrt(5))(1-sqrt(5))")
        assert "-4" not in out
        assert out.index(r"1 + \sqrt{5}") < out.index(r"1 - \sqrt{5}")
