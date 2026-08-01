"""
`\\nextstep` — étapes dynamiques (§4.3.3-4 de docOEF4).

WIMS relit `$nextstep` après chaque étape (`scripts/oef/nextstep.proc`) et
s'arrête dès qu'il est vide : le nombre d'étapes n'est jamais écrit dans le
`.def`. PAX rejoue donc la section `:postdef` pour le retrouver, en refusant
d'annoncer un total quand la suite dépend des réponses de l'élève.
"""

import pytest

from core.oef.def_engine import DefEngine, load_and_render
from core.oef.def_parser import Assign, IfBlock


RES = "/ressources"


class TestNormalisation:
    """Port de `nextstep.proc` : minuscules, `reply`→`r`, sans espaces,
    tabulations promues en lignes, puis première ligne non vide."""

    @pytest.mark.parametrize(
        ("raw", "expected"),
        [
            ("reply1", "r1"),
            ("Reply1, Reply2", "r1,r2"),
            ("replies 1,2", "r1,2"),
            ("choice 3", "c3"),
            ("choices1", "c1"),
            # `!rows2lines` : la tabulation sépare deux étapes, seule la
            # première est retenue (abatjour.def).
            ("reply1\treply2,reply3,reply4", "r1"),
            # `!nonempty lines` : les lignes vides en tête sont sautées.
            ("\n\n  \nreply2", "r2"),
            ("", ""),
            ("   ", ""),
            ("\t\n", ""),
        ],
    )
    def test_normalise(self, raw, expected):
        assert DefEngine._normalise_nextstep(raw) == expected


class TestDependencyDetection:
    """Seules les affectations de la variable désignée par `\\nextstep`
    comptent : un `:postdef` qui lit `$m_sc_reply2` pour composer un feedback
    ne rend pas la progression dépendante des réponses (heron1.def)."""

    def test_plain_assignment_is_deterministic(self):
        postdef = [Assign(name="val6", value="r1,r2")]
        assert not DefEngine._nextstep_depends_on_replies(postdef, "$val6")

    def test_assignment_guarded_by_a_score_is_dynamic(self):
        postdef = [
            IfBlock(
                kind="ifval",
                condition="$m_step==2 and $m_sc_reply1==1",
                then_body=[Assign(name="val25", value="$val23")],
                else_body=[],
            )
        ]
        assert DefEngine._nextstep_depends_on_replies(postdef, "$val25")

    def test_step_only_guard_is_deterministic(self):
        postdef = [
            IfBlock(
                kind="ifval",
                condition="$m_step==2 and $val58>=$m_step",
                then_body=[Assign(name="val6", value="$val67")],
                else_body=[],
            )
        ]
        assert not DefEngine._nextstep_depends_on_replies(postdef, "$val6")

    def test_reply_read_for_another_variable_is_ignored(self):
        """Le feedback de heron1 lit les scores, mais pas pour `val6`."""
        postdef = [
            IfBlock(
                kind="ifval",
                condition="$m_sc_reply2=1",
                then_body=[Assign(name="val25", value="bravo")],
                else_body=[],
            ),
            Assign(name="val6", value="r1"),
        ]
        assert not DefEngine._nextstep_depends_on_replies(postdef, "$val6")

    def test_literal_nextstep_needs_no_replay(self):
        assert not DefEngine._nextstep_depends_on_replies([], "reply1\treply2")


class TestCorpus:
    def test_deterministic_exercise_knows_its_total(self):
        """inst2 : `:postdef` vide la variable dès `m_step=2`, donc une seule
        étape — et le total ne bouge pas si le client demande au-delà."""
        path = f"{RES}/H4/programming/oefaffectatpython.fr/def/inst2.def"
        totals = [load_and_render(path, seed=42, m_step=s).total_steps for s in (1, 2, 3)]
        assert totals == [1, 1, 1]

    def test_reply_dependent_exercise_reports_no_total_upfront(self):
        """de4 : l'étape 2 n'existe que si la réponse 1 est juste
        (`!ifval ($m_step==2 and $m_sc_reply1==1)`). À l'étape 1, le total est
        inconnaissable — on préfère `None` à un chiffre faux."""
        path = f"{RES}/H4/programming/oefechpython.fr/def/de4.def"
        assert load_and_render(path, seed=42, m_step=1).total_steps is None
        # Une fois l'étape atteinte, le total ne peut plus lui être inférieur.
        assert load_and_render(path, seed=42, m_step=2).total_steps == 2

    def test_course_exercise_is_untouched(self):
        """`oefsteps` statique (course) : `\\nextstep` est inactif
        (`postvarcnt=0`), le comportement d'origine est conservé."""
        path = f"{RES}/H4/geometry/OEFcone.fr/def/abatjour.def"
        r1 = load_and_render(path, seed=42, m_step=1)
        r2 = load_and_render(path, seed=42, m_step=2)
        assert (r1.exercise_type, r1.total_steps) == ("course", 2)
        assert [a.input_name for a in r1.answers] == ["reply1"]
        assert [a.input_name for a in r2.answers] == ["reply2", "reply3", "reply4"]
