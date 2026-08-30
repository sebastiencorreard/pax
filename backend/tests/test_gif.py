"""Le décodeur GIF et la région 4-connexe, face au binaire `clickzone`.

Les verdicts ci-dessous ont été relevés sur `wims/public_html/bin/clickzone`,
qui décide de l'appartenance d'un clic à une zone `bound`. La confrontation
complète — 136 clics sur les deux cartes d'`oefdepregfr`, dont 120 tirés au
hasard — s'est faite hors test, le binaire n'étant pas dans l'image ; on en
garde ici les cas caractéristiques.

Pour la rejouer :

    cp wims/public_html/bin/clickzone /tmp/ && mkdir -p /tmp/cz/gifs
    cp ressources/H3/geography/oefdepregfr.fr/images/*.gif /tmp/cz/gifs/
    cd /tmp/cz && wims_exec_parm="$(printf '204,338\\nb,dept.gif,204,338\\n')" \\
        /tmp/clickzone      # -> "1 0" (trouvé en ligne 1) ou "-1"
"""
import os

import pytest

from core.oef.def_engine.gif import GifError, lire_gif

CARTES = os.path.join(
    os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
    "ressources", "H3", "geography", "oefdepregfr.fr", "images",
)
DEPT = os.path.join(CARTES, "dept.gif")

pytestmark = pytest.mark.skipif(
    not os.path.isfile(DEPT), reason="les cartes d'oefdepregfr ne sont pas là"
)


def test_dimensions_et_palette():
    im = lire_gif(DEPT)
    assert (im.largeur, im.hauteur) == (512, 450)
    assert len(im.pixels) == 512 * 450
    # Quatre couleurs : fond, mer, terre, frontières.
    assert set(im.pixels) <= {0, 1, 2, 3}


def test_hors_image_ne_vaut_pas_zero():
    """Un index 0 est une couleur ; l'extérieur n'en est pas une. Les
    confondre ferait passer un clic hors cadre pour un clic sur le fond."""
    im = lire_gif(DEPT)
    assert im.pixel(-1, 10) is None
    assert im.pixel(512, 10) is None
    assert im.pixel(0, 0) is not None


@pytest.mark.parametrize("clic,attendu", [
    ((204, 338), True),    # le point de référence lui-même
    ((205, 338), True),    # son voisin immédiat, même département
    ((10, 10), False),     # hors de la carte, dans le fond
    ((338, 234), False),   # un autre département
])
def test_region_conforme_a_clickzone(clic, attendu):
    im = lire_gif(DEPT)
    assert im.region_atteint(clic, (204, 338)) is attendu


def test_un_clic_hors_cadre_natteint_rien():
    im = lire_gif(DEPT)
    assert im.region_atteint((-5, -5), (204, 338)) is False
    assert im.region_atteint((204, 338), (9999, 9999)) is False


def test_un_fichier_qui_nest_pas_un_gif(tmp_path):
    faux = tmp_path / "faux.gif"
    faux.write_bytes(b"pas un GIF du tout")
    with pytest.raises(GifError):
        lire_gif(str(faux))
