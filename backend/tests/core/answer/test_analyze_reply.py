"""La réponse de l'élève, telle que la section `:test` l'attend.

Un exercice noté par analyse fait tourner son propre `:postdef` puis son
`:test` sur la réponse. Encore faut-il la lui donner sous la forme qu'il range
dans ses variables — et deux maillons y manquaient.
"""

import html

from core.answer.strategies.analyze import _forme_brute


class _Def:
    """Le minimum d'une `AnswerDef` pour `_forme_brute`."""

    def __init__(self, options):
        self.options = options


class TestFormeBrute:
    """Ce que le front renvoie est la forme **affichée** : math refermé pour
    KaTeX, entité HTML restée en clair. `OEFevalwimsgrph/ineqalghyper1` cherche
    le rang de la réponse dans sa propre liste (`!positionof item $m_reply1 in
    $val111`) — il ne l'y retrouvait jamais, et **aucune réponse ne pouvait
    être juste**.
    """

    @staticmethod
    def _ans():
        return _Def({
            "choices": [r"\(a\) &#59; \(b\)", r"\(c\) &#59; \(d\)"],
            "choices_raw": [r"\(a) &#59; \(b)", r"\(c) &#59; \(d)"],
        })

    def test_retrouve_la_forme_rangee(self):
        """Le rang du choix affiché désigne l'item de même rang dans la liste
        d'origine — exact par construction, sans défaire les transformations
        à l'aveugle."""
        out = _forme_brute(r"\(c\) &#59; \(d\)", self._ans())
        # Math rouvert…
        assert r"\(c)" in out
        # …et entité décodée : c'est le `;` que le navigateur soumet, et que le
        # `:postdef` ré-échappe juste après en `&#59;`. Lui rendre l'entité
        # produirait `&#59&#59;`, introuvable dans la liste.
        assert "&#59;" not in out
        assert ";" in out

    def test_une_reponse_hors_palette_passe_telle_quelle(self):
        assert _forme_brute("autre chose", self._ans()) == "autre chose"

    def test_sans_palette_brute_on_ne_touche_a_rien(self):
        ans = _Def({"choices": ["a", "b"]})
        assert _forme_brute("a", ans) == "a"

    def test_sans_reponse_declaree(self):
        assert _forme_brute("x", None) == "x"

    def test_palettes_de_tailles_differentes_sont_ignorees(self):
        """Garde-fou : sans correspondance rang à rang, on ne devine pas."""
        ans = _Def({"choices": ["a", "b", "c"], "choices_raw": ["a", "b"]})
        assert _forme_brute("a", ans) == "a"


class TestMReplyEstPose:
    """`check_analyze` ne posait que `val<N>` pour un `?analyze N`. WIMS rend
    aussi `m_reply<n>` et `reply<n>`, **bruts**, à toute réponse soumise — et
    121 `.def` du corpus les lisent dans leur `:postdef` ou leur `:test`, dont
    47 avec un `?analyze`."""

    def test_les_deux_variables_arrivent(self):
        from core.oef.def_engine import check_analyze
        from core.oef.def_parser import Assign

        condtest, _ = check_analyze(
            ev_ctx={},
            postdef_instructions=[
                Assign(name="val9", value="$m_reply1"),
                Assign(name="val8", value="$reply1"),
            ],
            test_instructions=[
                Assign(name="condtest1", value="1"),
            ],
            analyze_replies={},
            seed=1,
            replies_by_number={1: "42"},
        )
        assert condtest == {"condtest1": 1}

    def test_sans_replies_by_number_rien_ne_change(self):
        """Le paramètre est optionnel : les appels existants restent valides."""
        from core.oef.def_engine import check_analyze
        from core.oef.def_parser import Assign

        condtest, _ = check_analyze(
            ev_ctx={},
            postdef_instructions=[],
            test_instructions=[Assign(name="condtest1", value="0")],
            analyze_replies={},
            seed=1,
        )
        assert condtest == {"condtest1": 0}
