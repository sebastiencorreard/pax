"""Un exercice qui mêle les deux notations : conditions **et** checkers.

`?analyze` confie la note à la section `:test` de l'exercice. Mais un même
exercice peut poser, à côté de ses champs analysés, des réponses que leur type
sait juger seul — un `numeric` avec son `replygood`. `oefresolalg/fill2deg` en
compte quatre sur neuf ; `quizz/course04_1`, quinze sur seize. Cinquante-trois
exercices du corpus sont dans ce cas.

Ne garder que les conditions revenait à ne pas noter ces réponses-là : sur
`fill2deg`, fausser trois champs sur quatre ne changeait pas le score, et une
seule condition manquée coûtait la moitié des points. Et comme le score global
était recopié sur chaque champ, un champ juste s'affichait en rouge dès qu'une
condition échouait ailleurs.

Ces tests fixent les deux règles, sur un exercice de fabrication : la note se
partage entre les deux ensembles, et le verdict d'un champ est celui de son
propre checker quand il en a un.
"""
from core.answer.schemas import AnswerResult
from core.answer.strategies import analyze as A


class _Def:
    """Le minimum d'une `AnswerDef` pour `run_analyze`."""

    def __init__(self, nom, type_, attendu="", options=None, weight=1.0):
        self.input_name = nom
        self.answer_type = type_
        self.expected = attendu
        self.options = options or {}
        self.weight = weight
        self.label = ""


class _Rendu:
    check_sections = {"ctx": {}, "postdef": [], "test": []}
    lang = "fr"


def _run(monkeypatch, defs, replies, condtest, weights):
    """Exécute `run_analyze` en fixant le verdict des conditions."""
    monkeypatch.setattr(
        A, "run_analyze", A.run_analyze
    )  # garde le vrai appelant
    import core.oef.def_engine as DE

    monkeypatch.setattr(
        DE, "check_analyze", lambda **kw: (condtest, weights)
    )
    return A.run_analyze(_Rendu(), defs, replies, 42)


# Quatre champs jugés par leur type, deux notés par les conditions.
def _defs():
    return [
        _Def("reply1", "numeric", "3"),
        _Def("reply2", "numeric", "0"),
        _Def("reply3", "analyze", "", {"analyze_var": "val27"}),
        _Def("reply4", "analyze", "", {"analyze_var": "val28"}),
    ]


_JUSTES = {"reply1": "3", "reply2": "0", "reply3": "", "reply4": ""}


class TestNote:
    """`(Σ réponses·poids + Σ conditions·poids) / Σ de tous les poids`."""

    def test_tout_juste_vaut_un(self, monkeypatch):
        score, _ = _run(monkeypatch, _defs(), _JUSTES, {1: 1, 2: 1}, {1: 1, 2: 1})
        assert score == 1.0

    def test_une_reponse_fausse_coute_sa_part(self, monkeypatch):
        """Deux réponses jugées + deux conditions = quatre parts ; une réponse
        fausse en retire une. C'est ce qui manquait : le score n'en bougeait
        pas d'un pouce."""
        replies = dict(_JUSTES, reply1="999")
        score, _ = _run(monkeypatch, _defs(), replies, {1: 1, 2: 1}, {1: 1, 2: 1})
        assert score == 0.75

    def test_une_condition_manquee_coute_la_meme_part(self, monkeypatch):
        score, _ = _run(monkeypatch, _defs(), _JUSTES, {1: 1, 2: 0}, {1: 1, 2: 1})
        assert score == 0.75

    def test_les_deux_se_cumulent(self, monkeypatch):
        replies = dict(_JUSTES, reply1="999")
        score, _ = _run(monkeypatch, _defs(), replies, {1: 1, 2: 0}, {1: 1, 2: 1})
        assert score == 0.5

    def test_le_poids_d_une_reponse_est_suivi(self, monkeypatch):
        defs = _defs()
        defs[0].weight = 3.0
        replies = dict(_JUSTES, reply1="999")
        # 0·3 + 1·1 + 1 + 1 = 3 sur 3+1+1+1 = 6
        score, _ = _run(monkeypatch, defs, replies, {1: 1, 2: 1}, {1: 1, 2: 1})
        assert score == 0.5


class TestExerciceSansReponseJugeable:
    """Les 324 exercices dont **toutes** les réponses passent par `?analyze` :
    la formule doit retomber exactement sur celle d'avant, leur premier terme
    étant vide."""

    def test_la_note_reste_celle_des_conditions(self, monkeypatch):
        defs = [
            _Def("reply1", "analyze", "", {"analyze_var": "val1"}),
            _Def("reply2", "analyze", "", {"analyze_var": "val2"}),
        ]
        score, _ = _run(
            monkeypatch, defs, {"reply1": "", "reply2": ""}, {1: 1, 2: 0}, {1: 1, 2: 1}
        )
        assert score == 0.5

    def test_sans_condition_la_note_est_nulle(self, monkeypatch):
        defs = [_Def("reply1", "analyze", "", {"analyze_var": "val1"})]
        score, _ = _run(monkeypatch, defs, {"reply1": ""}, {}, {})
        assert score == 0.0


class TestVerdictParChamp:
    """Peindre tout l'exercice de la note globale mettait en rouge des réponses
    justes. Un champ que son type sait juger porte **son** verdict."""

    def test_une_reponse_juste_reste_juste(self, monkeypatch):
        replies = dict(_JUSTES, reply1="999")
        _, res = _run(monkeypatch, _defs(), replies, {1: 1, 2: 0}, {1: 1, 2: 1})
        par_nom = {r.input_name: r for r in res}
        assert par_nom["reply1"].score == 0.0
        assert par_nom["reply2"].score == 1.0
        assert par_nom["reply2"].correct

    def test_un_champ_analyze_porte_la_note_globale(self, monkeypatch):
        """Aucun checker ne le juge : la note d'ensemble est tout ce qu'on a."""
        _, res = _run(monkeypatch, _defs(), _JUSTES, {1: 1, 2: 0}, {1: 1, 2: 1})
        par_nom = {r.input_name: r for r in res}
        assert par_nom["reply3"].method == "analyze"
        assert par_nom["reply3"].score == par_nom["reply4"].score

    def test_le_verdict_nomme_la_methode_du_checker(self, monkeypatch):
        _, res = _run(monkeypatch, _defs(), _JUSTES, {1: 1, 2: 1}, {1: 1, 2: 1})
        par_nom = {r.input_name: r for r in res}
        assert par_nom["reply1"].method != "analyze"

    def test_chaque_champ_a_bien_un_verdict(self, monkeypatch):
        _, res = _run(monkeypatch, _defs(), _JUSTES, {1: 1, 2: 1}, {1: 1, 2: 1})
        assert {r.input_name for r in res} == {
            "reply1", "reply2", "reply3", "reply4"
        }
        assert all(isinstance(r, AnswerResult) for r in res)
