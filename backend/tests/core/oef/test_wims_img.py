"""`imgrename` — conformité à `calc_imgrename` (`calc.c`).

Chaque cas cite la règle du C plutôt que le comportement observé, pour qu'un
écart futur se juge contre l'original et non contre ce fichier.

Rappel du C, pour situer les cas ci-dessous :

    p2=find_word_start(p1+strlen("imgrename"));
    if(*p2!='(') {p1=p2; continue;}
    p2++; p3=find_matching(p2,')');
    if(*p3!=')') {p1=p2-1; continue;}
    p2=find_word_start(p2); p4=find_word_end(p2);
    memmove(buf,p2,p4-p2); buf[p4-p2]=0;
    calc_rename(buf); *p3=0;
    snprintf(buf2,sizeof(buf2),"<img src=\\"%s\\"%s alt=\\"\\">",buf, p4);
"""

from core.oef.def_engine.wims_img import calc_imgrename


class TestCalcImgrename:
    def test_chemin_et_attributs(self):
        """Le premier mot est le `src`, le reste jusqu'à la fermante suit tel quel."""
        assert calc_imgrename("imgrename(a/b.png width=150)") == (
            '<img src="a/b.png" width=150 alt="">'
        )

    def test_attribut_avec_espaces_et_guillemets(self):
        """`p4` est recopié brut : ni découpage, ni ré-encodage des guillemets."""
        assert calc_imgrename('imgrename(x style="height:200px")') == (
            '<img src="x" style="height:200px" alt="">'
        )

    def test_tabulation_separe_comme_tout_blanc(self):
        """`find_word_end` s'arrête à `isspace`, tabulation comprise — c'est la
        forme que portent les `.def` (`imgrename($val1/ttt\\t width=$val10)`)."""
        assert calc_imgrename("imgrename(a/b\t   width=150)") == (
            '<img src="a/b"\t   width=150 alt="">'
        )

    def test_sans_attribut_garde_le_blanc(self):
        """Le blanc de séparation appartient à `p4` : il subsiste entre le
        `src` et le `alt`, comme dans le C."""
        assert calc_imgrename("imgrename(a.png )") == '<img src="a.png"  alt="">'

    def test_fermante_collee_au_chemin(self):
        """`find_word_end` ne s'arrête qu'à un blanc : sans blanc avant la
        fermante, la parenthèse entre dans le chemin. Travers de l'original,
        reproduit tel quel — aucun `.def` du corpus n'écrit cette forme."""
        assert calc_imgrename("imgrename(a.png)") == '<img src="a.png)" alt="">'

    def test_occurrences_multiples(self):
        """La boucle reprend après la balise produite et traite toute la chaîne."""
        assert calc_imgrename("A imgrename(p.png w=1) B imgrename(q.png h=2) C") == (
            'A <img src="p.png" w=1 alt=""> B <img src="q.png" h=2 alt=""> C'
        )

    def test_parentheses_imbriquees(self):
        """`find_matching` tient les compteurs : la fermante retenue est celle
        de profondeur zéro, pas la première rencontrée."""
        assert calc_imgrename("imgrename(a.png alt=(x))") == (
            '<img src="a.png" alt=(x) alt="">'
        )

    def test_nom_non_suivi_de_parenthese(self):
        """`if(*p2!='(') {p1=p2; continue;}` — le texte passe intact."""
        assert calc_imgrename("imgrename sans parenthese") == "imgrename sans parenthese"

    def test_parenthese_jamais_refermee(self):
        """`if(*p3!=')') {p1=p2-1; continue;}` — pas d'appariement, rien produit."""
        assert calc_imgrename("imgrename(jamais refermee") == "imgrename(jamais refermee"

    def test_nom_englobant_non_capture(self):
        """`varchr` exige une position de variable : `myimgrename` n'en est pas une."""
        assert calc_imgrename("myimgrename(x y)") == "myimgrename(x y)"
        assert calc_imgrename("imgrenamed(x y)") == "imgrenamed(x y)"

    def test_texte_sans_appel_inchange(self):
        assert calc_imgrename("rien a faire ici") == "rien a faire ici"

    def test_reprise_apres_un_faux_appel(self):
        """Le C ne renonce pas au reste de la chaîne après une reprise."""
        assert calc_imgrename("imgrename tel quel puis imgrename(a.png w=1)") == (
            'imgrename tel quel puis <img src="a.png" w=1 alt="">'
        )

    def test_sentinelle_pax_img_recopiee(self):
        """PAX n'a pas de `calc_rename` : le chemin `pax-img:` sort intact, et
        c'est `flydraw.inline_pax_images` qui le résout en post-rendu."""
        assert calc_imgrename("imgrename(pax-img:_/ch4o/ch4o.png width=150)") == (
            '<img src="pax-img:_/ch4o/ch4o.png" width=150 alt="">'
        )
