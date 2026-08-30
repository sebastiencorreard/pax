"""L'émulation de `chemeq` face au binaire de WIMS.

`chemeq_oracle.json` fige les sorties du binaire du dépôt
(`wims/other/bin/chemeq`) pour **toutes** les entrées que le corpus lui
soumet — relevées en instrumentant `_cmd_readproc` sur les 4278 exercices.
C'est la seule référence qui vaille : l'émulation n'a pas à être « plausible »,
elle doit rendre exactement ce que WIMS rend, au chiffre et à l'accolade près.

Pour régénérer la référence après avoir élargi le périmètre :

    for e in <entrées>; do echo "$e" | wims/other/bin/chemeq -M; done

Le binaire ne vit pas dans l'image — PAX n'appelle aucun processus externe —,
d'où cette capture figée plutôt qu'un appel au fil du test.
"""
import json
import os

import pytest

from core.oef.def_engine.chemeq import chemeq

_ORACLE = json.load(
    open(os.path.join(os.path.dirname(__file__), "chemeq_oracle.json"))
)


def _cas(option: str):
    return sorted(_ORACLE[option].items())


@pytest.mark.parametrize("entree,attendu", _cas("M"), ids=lambda v: v if isinstance(v, str) else "")
def test_masse_molaire_conforme_au_binaire(entree, attendu):
    assert chemeq(entree, "M") == attendu.strip()


@pytest.mark.parametrize("entree,attendu", _cas("l"), ids=lambda v: v if isinstance(v, str) else "")
def test_latex_conforme_au_binaire(entree, attendu):
    assert chemeq(entree, "l") == attendu.strip()


def test_option_inconnue_rend_le_vide():
    """`v` (version), `e` et `C` (équilibrage) sortent du périmètre porté :
    ils rendent le vide, comme le faisait l'appel avant qu'il existe."""
    for option in ("v", "e", "C", ""):
        assert chemeq("H2O", option) == ""


def test_entree_hors_grammaire_rend_le_vide():
    """Le binaire écrit `ERROR: syntax error at N` sur sa sortie standard ;
    faire remonter ce texte dans une variable WIMS ferait plus de dégâts qu'un
    vide, que les scripts savent déjà traiter."""
    for mauvaise in ("", "   ", "Zz9", "H2O +", "((H2O)", "42"):
        assert chemeq(mauvaise, "M") == ""


def test_indice_souligne_vaut_indice_collé():
    """`H_2O` et `H2O` désignent la même molécule — les auteurs du corpus
    emploient les deux, et `chemeq` les tient pour équivalents."""
    for collé, souligné in (("H2O", "H_2O"), ("Fe2(SO4)3", "Fe_2(SO_4)_3")):
        assert chemeq(collé, "M") == chemeq(souligné, "M")
        assert chemeq(collé, "l") == chemeq(souligné, "l")


def test_le_coefficient_compte_dans_la_masse():
    """`-M` rend une masse **par espèce**, coefficient stœchiométrique inclus :
    `2Al` pèse 53.964, non 26.982. C'est ce que lit `chemeq_mass`."""
    assert chemeq("2Al + 3Cu^2+ -> 2Al^3+ + 3Cu", "M") == "53.964 190.638 53.964 190.638"
