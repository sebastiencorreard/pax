"""Étapes `\\nextstep` : l'état de `:postdef` et les verdicts d'étape.

Chez WIMS, après chaque envoi, `screply.proc` pose `m_sc_reply`, puis
`nextstep.proc` exécute `:postdef` ; l'étape suivante s'affiche dans l'état
qu'il laisse. PAX rejoue `:postdef` pour `m_step` = 2…N au rendu, et prend les
verdicts que `/api/check` a rendus au lieu de renoter.
"""
import os

import pytest

from core.oef import render_cache
from core.oef.def_engine import sc_reply_wims


@pytest.mark.parametrize("note,sc", [(1.0, "1"), (0.9, "0.5"), (0.5, "0.5"), (0.0, "0")])
def test_m_sc_reply_comme_screply(note, sc):
    assert sc_reply_wims(note) == sc


def test_les_notes_entrent_dans_la_cle_du_cache():
    # Deux verdicts différents pour la même réponse ne rendent pas la même
    # étape : un exercice à reprises repose le champ manqué.
    rep = {"reply1": "x"}
    juste = render_cache.cache_key("p", 1, 2, rep, None, {"reply1": 1.0})
    faux = render_cache.cache_key("p", 1, 2, rep, None, {"reply1": 0.0})
    assert juste != faux != render_cache.cache_key("p", 1, 2, rep)


def _histocap():
    from tests import corpus
    chemins = dict(corpus.exercises())
    ex = "H4~stat~oefstatistiques.fr~src~histocap"
    if ex not in chemins:
        pytest.skip("histocap absent de ce corpus")
    return chemins[ex]


def test_histocap_affiche_les_temps_a_l_etape_2():
    """Le tableau des temps naît dans `:postdef` : sans rejeu, il était vide."""
    os.environ.setdefault("PAX_WIMS_NOW", "20260101.12:00:00")
    import core.oef.def_engine as E
    from core.oef.engine import find_def_path

    temps = [str(200 + 7 * i % 190) for i in range(40)]
    r = E.load_and_render(find_def_path(_histocap()), seed=42, m_step=2,
                          prev_replies={"reply1": ",".join(temps)},
                          prev_scores={"reply1": 1.0})
    assert all(t in r.statement_html for t in temps[:5])


def test_une_requete_ne_garde_que_vsavelist():
    from core.oef.def_engine import nouvelle_requete, vsave_de

    ctx = {"val7": "a", "val56": "reply6", "val107": "x", "m_step": "7"}
    nouvelle_requete(ctx, vsave_de("1,6,7,8"))
    assert ctx == {"val7": "a", "val56": "", "val107": "", "m_step": "7"}
    # Sans `vsavelist`, rien n'est touché.
    ctx = {"val56": "reply6"}
    nouvelle_requete(ctx, None)
    assert ctx == {"val56": "reply6"}


def test_histocap_s_arrete_apres_six_etapes():
    """`nextstep` désigne `val56`, hors `vsavelist` : `:postdef` la pose aux
    étapes 2 à 6, pas à la 7ᵉ. Gardée d'une étape à l'autre, elle relançait
    l'exercice sans fin (étape 7, 8, 9…) — comme 26 autres exercices."""
    os.environ.setdefault("PAX_WIMS_NOW", "20260101.12:00:00")
    import core.oef.def_engine as E
    from core.oef.def_engine.analyze import etape_suivante_existe
    from core.oef.engine import find_def_path

    d = find_def_path(_histocap())
    rep = {"reply1": ",".join(str(200 + 7 * i % 190) for i in range(40))}
    etapes = 0
    for k in range(1, 12):
        r = E.load_and_render(d, seed=42, m_step=k, prev_replies=dict(rep),
                              prev_scores={x: 1.0 for x in rep})
        for a in r.answers:
            rep.setdefault(a.input_name, a.expected or "1")
        etapes = k
        if etape_suivante_existe(r, dict(rep), 42, k, {x: 1.0 for x in rep}) is not True:
            break
    assert etapes == 6
