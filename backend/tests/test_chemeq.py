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
import re

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


@pytest.mark.parametrize("entree,attendu", _cas("e"), ids=lambda v: v if isinstance(v, str) else "")
def test_charges_conformes_au_binaire(entree, attendu):
    assert chemeq(entree, "e") == attendu.strip()


@pytest.mark.parametrize("entree,attendu", _cas("C"), ids=lambda v: v if isinstance(v, str) else "")
def test_decompte_datomes_conforme_au_binaire(entree, attendu):
    assert chemeq(entree, "C") == attendu.strip()


def test_une_molecule_seule_rend_le_latex_sous_e_et_C():
    """Sans flèche, il n'y a pas d'équation à décrire : le binaire rend alors
    le LaTeX, et non un décompte. Vérifié sur `chemeq -e H2O`."""
    assert chemeq("H2O", "e") == chemeq("H2O", "l")
    assert chemeq("H2O", "C") == chemeq("H2O", "l")


def test_option_inconnue_rend_le_vide():
    """Une option hors périmètre rend le vide, comme le faisait l'appel avant
    qu'elle existe. `v` fait exception depuis qu'elle est portée."""
    for option in ("x", ""):
        assert chemeq("H2O", option) == ""


def test_version_annoncee():
    """`chemeq -v` — la **première** chose que demande
    `slib/chemistry/chemeq_equilibrium`, et de quoi dépend tout le reste :

        slib_out=!replace .*version. by $empty in $slib_out
        !if $slib_out < 1.119999
          slib_out=Warning! … install a newer version …
          !goto end

    Le vide qu'on rendait valait zéro dans la comparaison WIMS, donc
    `0 < 1.12` : le slib refusait de tourner. Le binaire ignore son entrée
    pour cette option, l'émulation aussi.
    """
    for entree in ("", "H2O", "Fe + 3/2Cl2 -> FeCl3"):
        sortie = chemeq(entree, "v")
        assert "version" in sortie
        # Ce que le `!replace` du slib en tire doit être un nombre ≥ 1.12.
        reste = re.sub(r".*version.", "", sortie).strip()
        assert float(reste) >= 1.12


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


# Sorties du binaire du dépôt (`wims/src/Misc/chemeq/src/chemeq`) sur ce que
# les exercices rédox lui soumettent : l'électron, et l'algèbre d'équations de
# `slib/chemistry/chemeq_add` (`#` ajoute, `~` retranche, `c *` multiplie).
# La composition a été confrontée au binaire sur 79 278 entrées — toutes les
# paires de demi-équations de `redox.dat`, `redox_mini.dat` et
# `couples_piles.dat` — sans un écart ; ces cas-ci en gardent les règles.
_REDOX = [
    # L'électron est un atome de masse nulle, dont l'état se tait.
    ("C", "Zn^2+_aq + 2e^- -> Zn_s", "Zn^2+_(aq)|Zn:1*1, 2 e^-|e:2*1; Zn_(s)|Zn:1*1"),
    ("e", "Zn^2+_aq + 2e^- -> Zn_s", "Zn^2+_(aq)|1*2, 2 e^-|2*-1; Zn_(s)|1*0"),
    ("l", "Zn^2+_aq + 2e^- -> Zn_s",
     "\\mathrm{Zn}^{2+}_{(aq)}\\,+\\,2\\,\\mathrm{e}^{-}\\,\\longrightarrow\\,\\mathrm{Zn}_{(s)}"),
    ("M", "Zn^2+_aq + 2e^- -> Zn_s", "65.38 0 65.38"),
    # `-m` : l'écriture normalisée, la flèche toujours `->` ; LaTeX sans flèche.
    ("m", "Zn^2+_aq + 2e^- -> Zn_s", "Zn^2+_(aq) + 2 e^- -> Zn_(s)"),
    ("m", "Fe^3+ + e^- <-> Fe^2+", "Fe^3+ + e^- -> Fe^2+"),
    ("m", "H2O", "\\mathrm{H}_{2}\\mathrm{O}"),
    # Une espèce écrite deux fois dans un membre se fond (`addMol`).
    ("m", "2H^+ + 2H^+ -> H2", "4 H^+ -> H2"),
    # Composition : les espèces communes s'annulent, puis tout est trié.
    ("m", "H -> H # 2 * MnO4^-_aq + 8H^+_aq + 5e^- -> Mn^2+_aq + 4H2O_l ~ 5 * Zn^2+_aq + 2e^- -> Zn_s",
     "16 H^+_(aq) + 2 MnO4^-_(aq) + 5 Zn_(s) -> 8 H2O_(l) + 2 Mn^2+_(aq) + 5 Zn^2+_(aq)"),
    ("l", "H -> H # 1/2 * Cr2O7^2- + 14H^+ + 6e^- -> 2 Cr^3+ + 7H2O",
     "\\frac{1}{2}\\,\\mathrm{Cr}_{2}\\mathrm{O}_{7}^{2-}\\,+\\,7\\,\\mathrm{H}^{+}\\,+\\,3\\,\\mathrm{e}^{-}"
     "\\,\\longrightarrow\\,\\mathrm{Cr}^{3+}\\,+\\,\\frac{7}{2}\\,\\mathrm{H}_{2}\\mathrm{O}"),
    ("C", "H -> H # 2 * Fe^3+ + e^- -> Fe^2+ ~ 3 * Zn^2+ + 2e^- -> Zn",
     "2 Fe^3+|Fe:2*1, 3 Zn|Zn:3*1; 2 Fe^2+|Fe:2*1, 3 Zn^2+|Zn:3*1, 4 e^-|e:4*1"),
    # Les atomes se trient par symbole, sans franchir un groupe (`AtomeListe::triage`).
    ("m", "H -> H # 1 * CH3COOH + OH^- -> CH3COO^- + H2O", "CCH3HOO + HO^- -> CCH3OO^- + H2O"),
    ("m", "H -> H # 1 * Fe2(SO4)3 -> 2Fe^3+ + 3SO4^2-", "Fe2(O4S)3 -> 2 Fe^3+ + 3 O4S^2-"),
    # `chemeq_add` renvoie à chaque pas ce que `chemeq` vient d'écrire : `_(aq)`.
    ("m", "8 H^+_(aq) + 2 O2Pb_(s) + 4 e^- -> 4 H2O_(l) + 2 Pb^2+_(aq) ~ 1 * Zn^2+_aq + 2e^- -> Zn_s",
     "8 H^+_(aq) + 2 O2Pb_(s) + Zn_(s) + 2 e^- -> 4 H2O_(l) + 2 Pb^2+_(aq) + Zn^2+_(aq)"),
    # Deux signatures égales (`O4PbS` trié, `PbSO4` ajouté) : le tri par
    # échange du C n'est pas stable, et c'est son ordre qui sort.
    ("m", "H -> H # 2 * PbSO4_s + 2e^- -> Pb_s +SO4^2-_aq ~ 1 * PbO2_s + 4H^+_aq + SO4^2-_aq + 2e^- -> PbSO4_s + 2H2O_l",
     "2 H2O_(l) + O4PbS_(s) + 2 O4PbS_(s) + 2 e^- -> 4 H^+_(aq) + O2Pb_(s) + 2 O4S^2-_(aq) + O4S^2-_(aq) + 2 Pb_(s)"),
]


@pytest.mark.parametrize("option,entree,attendu", _REDOX, ids=lambda v: v if isinstance(v, str) else "")
def test_redox_conforme_au_binaire(option, entree, attendu):
    assert chemeq(entree, option) == attendu


def test_une_demi_equation_redox_se_compare():
    """Sans l'électron, aucune demi-équation ne se lisait : la réponse de
    l'élève à la première étape de `redox1` était toujours fausse."""
    from core.oef.def_engine.chemeq import equations_equivalentes
    assert equations_equivalentes(" Ca_(s)   ->   Ca^2+_(aq)   +   2e^-  ",
                                  "Ca_(s) -> Ca^2+_(aq) + 2 e^-")


class TestEquationsEquivalentes:
    """La comparaison de deux équations, telle que `anstype/chemeq` en a besoin.

    WIMS passe par `chemeq -n` et compare les chaînes normalisées. PAX compare
    le **sens** : chaque membre doit coïncider à un seul et même facteur
    d'échelle près. Les cas ci-dessous ont été confrontés au binaire du dépôt,
    qui les tranche tous de la même façon — sauf le dernier, où il échoue.
    """

    from core.oef.def_engine.chemeq import equations_equivalentes as _eq

    def test_mise_a_l_echelle(self):
        eq = TestEquationsEquivalentes._eq
        assert eq("2Fe + 3Cl2 -> 2FeCl3", "Fe + 3/2Cl2 -> FeCl3")
        assert eq("2H2 + O2 -> 2H2O", "H2 + 1/2 O2 -> H2O")
        assert eq("Na + 1/4O2 -> 1/2Na2O", "2Na + 1/2O2 -> Na2O")

    def test_les_blancs_et_l_ordre_des_especes_sont_indifferents(self):
        eq = TestEquationsEquivalentes._eq
        assert eq("Fe + 3/2 Cl2 -> FeCl3", "Fe + 3/2Cl2 -> FeCl3")
        assert eq("Ca_s + F2_g -> Ca^2+ + 2F^-", "F2_g + Ca_s -> Ca^2+ + 2F^-")

    def test_le_sens_de_la_reaction_compte(self):
        eq = TestEquationsEquivalentes._eq
        assert not eq("FeCl3 -> Fe + 3/2Cl2", "Fe + 3/2Cl2 -> FeCl3")

    def test_la_fleche_compte(self):
        eq = TestEquationsEquivalentes._eq
        assert not eq("Fe + 3/2Cl2 <-> FeCl3", "Fe + 3/2Cl2 -> FeCl3")

    def test_un_facteur_par_membre_ne_suffit_pas(self):
        """Doubler un seul côté donne une autre réaction : le facteur doit
        valoir pour les deux membres à la fois."""
        eq = TestEquationsEquivalentes._eq
        assert not eq("2H2 + O2 -> H2O", "H2 + 1/2 O2 -> H2O")

    def test_etat_et_charge_distinguent(self):
        eq = TestEquationsEquivalentes._eq
        assert not eq("2H2_g + O2_g -> 2H2O", "H2 + 1/2 O2 -> H2O")
        assert not eq("Mg_s + 2H^+ -> Mg + H_2_g", "Mg_s + 2H^+ -> Mg^2+ + H_2_g")

    def test_aqueux_s_efface(self):
        """`delete_aq()` (`chemeq.h:265`) — une espèce en solution s'écrit avec
        ou sans son `_(aq)`."""
        eq = TestEquationsEquivalentes._eq
        assert eq("Na^+_aq + Cl^-_aq -> NaCl", "Na^+ + Cl^- -> NaCl")

    def test_une_equation_fausse_reste_fausse(self):
        eq = TestEquationsEquivalentes._eq
        assert not eq("Fe + Cl2 -> FeCl3", "Fe + 3/2Cl2 -> FeCl3")
        assert not eq("Fe + 3/2Cl2 -> FeCl2", "Fe + 3/2Cl2 -> FeCl3")

    def test_entree_vide_ou_illisible(self):
        eq = TestEquationsEquivalentes._eq
        assert not eq("", "Fe + 3/2Cl2 -> FeCl3")
        assert not eq("n'importe quoi", "Fe + 3/2Cl2 -> FeCl3")

    def test_ecart_assume_avec_le_binaire(self):
        """`chemeq -n` rend ` -> ` sur `Fe2(SO4)3 -> Fe2(SO4)3` : deux membres
        vides, qu'il déclare donc *égaux* — n'importe quelle réponse y
        passerait. Ici, une équation n'est égale qu'à elle-même."""
        eq = TestEquationsEquivalentes._eq
        assert eq("Fe2(SO4)3 -> Fe2(SO4)3", "Fe2(SO4)3 -> Fe2(SO4)3")
        assert not eq("H2O -> H2O", "Fe2(SO4)3 -> Fe2(SO4)3")
