"""`!exec crossword` — le port de `wims/src/Misc/crossword/crossword.c`.

L'algorithme est déterministe : chaque liste ci-dessous a été passée au
binaire de l'arbre (`wims/src/Misc/crossword/crossword <fichier>`), et sa
sortie est recopiée telle quelle. Le port a été confronté au binaire sur 460
listes tirées des vocabulaires du corpus, 460 grilles identiques ; ces trois
cas en gardent la trace sans exiger le binaire.
"""
from core.oef.def_engine.crossword import construire, crossword


def test_six_mots_depend_du_hachage():
    # Le cas qui a trahi le hachage : gcc -O2 a remplacé le produit qui
    # déborde par `addq $0x7fffffff` ; calculé selon le source, la grille
    # sortait autre.
    mots = "timonier\nbaleine\nflibustier\ncarene\nride\nperruche\n"
    assert crossword(mots) == (
        "f,l,i,b,u,s,t,i,e,r\n,,,a,,,,,,\n,,,l,,p,,,,\nc,a,r,e,n,e,,,,\n"
        ",,,i,,r,,,,\n,t,,n,,r,,,,\nr,i,d,e,,u,,,,\n,m,,,,c,,,,\n,o,,,,h,,,,\n"
        ",n,,,,e,,,,\n,i,,,,,,,,\n,e,,,,,,,,\n,r,,,,,,,,\n"
    )


def test_sept_mots():
    mots = "galere\nforban\ncontrebandier\ncoque\namarre\ndeferlante\nancre\n"
    assert crossword(mots) == (
        "c,o,n,t,r,e,b,a,n,d,i,e,r\no,,,,,,,n,,e,,,\nq,,,,g,,,c,,f,,,\n"
        "u,,,,a,m,a,r,r,e,,,\ne,,,,l,,,e,,r,,,\n,,,,e,,,,,l,,,\n"
        ",,f,o,r,b,a,n,,a,,,\n,,,,e,,,,,n,,,\n,,,,,,,,,t,,,\n,,,,,,,,,e,,,\n"
    )


def test_vingt_mots_le_maximum_de_la_slib():
    mots = (
        "galere forban contrebandier coque amarre deferlante ancre derive "
        "matelot ecope avarie batiment rade cale houle compas jetee "
        "scaphandrier second virement"
    ).replace(" ", "\n") + "\n"
    assert crossword(mots) == (
        "s,e,c,o,n,d,,e,,,,,,\nc,,o,,,,,c,,,,,,\na,,m,a,t,e,l,o,t,,,,,\n"
        "p,,p,,,,,p,,,,,,\nh,,a,m,a,r,r,e,,,,,,\na,,s,,v,,,,b,,,,,\n"
        "n,,,,a,,g,,a,,,c,,\nd,e,f,e,r,l,a,n,t,e,,o,,\nr,,o,,i,,l,,i,,,n,,\n"
        "i,,r,,e,,e,,m,,,t,,\ne,,b,,,,r,,e,,,r,,\nr,,a,n,c,r,e,,n,,,e,,\n"
        ",,n,,o,,,,t,,,b,,\n,,,,q,,d,,,,,a,,\n,,h,o,u,l,e,,,j,,n,,\n"
        ",,,,e,,r,a,d,e,,d,,\n,,,,,,i,,,t,,i,,\n,,,,,,v,i,r,e,m,e,n,t\n"
        ",,,c,a,l,e,,,e,,r,,\n"
    )


def test_mot_trop_long_rien():
    # `load_words` : « Word too long », sortie vide.
    assert crossword("a" * 29 + "\n") == ""


class TestConstruire:
    """La grille posée devant l'élève, comme `anstype/crossword.input`."""

    # c o q
    # a . .
    # p . .
    ATTENDU = "[c,o,q\na,,\np,,],[coq,un oiseau\ncap,une pointe : cap]"

    def test_numeros_et_definitions(self):
        attendu, cfg = construire(self.ATTENDU, False, lambda o: o[0])
        assert cfg["cells"] == [[1, 0, 0], [0, -1, -1], [0, -1, -1]]
        assert cfg["horizontal"] == [[1, "un oiseau"]]
        # Les deux-points deviennent une virgule, comme chez WIMS.
        assert cfg["vertical"] == [[1, "une pointe , cap"]]
        assert attendu.startswith("[c,o,q\na,,\np,,]")

    def test_transposee(self):
        attendu, cfg = construire(self.ATTENDU, True, lambda o: o[0])
        assert attendu.startswith("[c,a,p\no,,\nq,,]")
        # Le mot horizontal est devenu vertical, et réciproquement.
        assert cfg["horizontal"] == [[1, "une pointe , cap"]]
        assert cfg["vertical"] == [[1, "un oiseau"]]

    def test_le_masque_ne_porte_aucune_lettre(self):
        _, cfg = construire(self.ATTENDU, False, lambda o: o[0])
        assert all(isinstance(c, int) for r in cfg["cells"] for c in r)
