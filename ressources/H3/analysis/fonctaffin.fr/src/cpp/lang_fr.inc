#if defined TARGET_cant || defined TARGET_cim
\text{name_enonc1a=Soit \(\nomfct\) la fonction affine définie pour tout nombre \(x\) par <span class="nowrap">\(\nomfct(x)=\texprfon\).</span>}
\text{name_enonc1l=Soit \(\nomfct\) la fonction linéaire de coefficient <span class="nowrap">\(\tcoefa\).</span>}
\text{name_inst=Vous donnerez la réponse sous la forme d'un nombre entier si possible ou d'une fraction irréductible de dénominateur positif.}
\text{name_cond1=Bonne réponse}
\text{name_cond2=Bonne réponse en écriture fractionnaire irréductible ou entière}
\text{name_feed=Votre réponse n'est pas une fraction irréductible.}
\text{name_ans1a=La fonction affine \(\nomfct\) est définie pour tout nombre \(x\) par  <span class="nowrap">\(\nomfct(x)=\texprfon\).</span>}
\text{name_ans1l=La fonction linéaire \(\nomfct\) a pour coefficient \(\tcoefa\) donc la fonction \(\nomfct\) est définie pour tout nombre \(x\) par <span class="nowrap">\(\nomfct(x)=\texprfon\).</span>}
#if defined TARGET_cant
\text{name_quest=Calculer un antécédent de \(\nb2\) par la fonction <span class="nowrap">\(\nomfct).</span>}
\text{name_phrase=Un antécédent de \(\nb2\) par la fonction \(\nomfct\) est égal à}
\text{name_antecedent=antécédent}
\text{name_ans2=Calculer un antécédent de \(\nb2\) par la fonction \(\nomfct\) revient à résoudre l'équation&nbsp;}
\text{name_feeda=Vous avez calculé l'image de \(\nb2\) par la fonction \(\nomfct\) alors qu'on demande un antécédent de \(\nb2\) par la fonction <span class="nowrap">\(\nomfct\).</span>
<p>Pour calculer un antécédent, vous devez trouver un nombre \(x\) qui vérifie l'égalité&nbsp;}
\if{\b>0}{\text{name_eq1=On soustrait \(\absb\) aux deux membres de l'équation.}}
\if{\b=0}{\text{name_eq1=}}
\if{\b<0}{\text{name_eq1=On ajoute \(\absb\) aux deux membres de l'équation.}}
\text{name_eq2=On divise par \(\ta\) les deux membres de l'équation.}
\if{\coef[1] isitemof \coefr}{\text{name_eq3=Diviser par une fraction revient à multiplier par son inverse}}
#endif
#if defined TARGET_cim
\text{name_quest=Calculer l'image du nombre \(\nb1\) par la fonction <span class="nowrap">\(\nomfct).</span>}
\text{name_ans2=<p>Pour calculer l'image de \(\nb1\), on remplace \(x\) par \(\nb1\) dans l'expression algébrique de la fonction.</p>
<span class="nowrap">\tim1</span>
<p><span class="nowrap">\tim2</span></p>
<span class="nowrap">\tim3</span>}
\text{name_phrase=L'image de \(\nb1\) par la fonction \(\nomfct\) est égale à }
\text{name_image=image}
\text{name_feedi=Vous avez calculé l'antécédent de \(\nb1\) par la fonction \(\nomfct\) alors qu'on demande l'image de \(\nb1\) par la fonction <span class="nowrap">\(\nomfct\).</span>
<p>Pour calculer l'image de \(\nb1\) par la fonction <span class="nowrap">\(\nomfct\)</span>, vous remplacez le nombre \(x\) par \(\nb1\) dans l'expression algébrique de la fonction <span class="nowrap">\(\nomfct\).</span></p>}
#endif
#endif

#if defined TARGET_cof || defined TARGET_coeq
#if defined TARGET_cof
\text{name_quest=Associer chaque fonction à la couleur de sa représentation graphique dans le repère.}
#endif
#if defined TARGET_coeq
\text{name_quest=Associer chaque équation de droite à la couleur de la droite correspondante dans le repère.}
#endif
\text{name_red=rouge}
\text{name_orange=orange}
\text{name_brown=marron}
\text{name_blue=bleu}
\text{name_black=noir}             
#endif

#if defined TARGET_ptcou
\text{name_list=Oui, Non}
\text{name_ans21=Comme <span class="nowrap">\(\nomfct(\xok)=\tordo\),</span> le point de coordonnées \((\xok \, ; \, \tordo)\) appartient à la courbe représentant la fonction}
\text{name_ans22=Comme <span class="nowrap">\(\nomfct(\xok) \ne\tordo\),</span> le point de coordonnées \((\xok \, ; \, \tordo)\) n'appartient pas à la courbe représentant la fonction}         
\text{name_enon=On considère la fonction \(\nomfct\) définie pour tout nombre \(x\) par <span class="nowrap">\(\fonction\).</span>} 
\text{name_quest=Le point de coordonnées \((\xok \, ; \, \tordo)\) appartient-il à la représentation graphique de la fonction}
\text{name_ans1=<p>On calcule l'image de \(\xok\) par la fonction <span class="nowrap">\(\nomfct\).</span></p>
<p>Pour calculer l'image de \(\xok\), on remplace \(x\) par \(\xok\) dans l'expression algébrique de la fonction.</p>}
\text{name_hint=La courbe représentative de la fonction \(\nomfct\) est l'ensemble des points de coordonnées \((x \, ; \, y)\) avec <span class="nowrap">\(y=\nomfct(x)\).</span>}
#endif

#if defined TARGET_fcou
\text{name_questl=Parmi les courbes ci-dessous, quelle est celle qui représente la fonction linéaire \(\propnomfct[\rep]\) définie pour tout nombre \(x\) par <span class="nowrap">\propfonction[\rep]&nbsp;&#63;</span>}
\text{name_questa=Parmi les courbes ci-dessous, quelle est celle qui représente la fonction affine \(\propnomfct[\rep]\) définie pour tout nombre \(x\) par <span class="nowrap">\propfonction[\rep]&nbsp;&#63;</span>}
\if{\confparm1=1}{\text{nature=affine}}{\text{nature=linéaire}
                                        \text{originel=passant par l'origine}
                                       }
\text{name_sol1=La fonction \nature \(\propnomfct[\rep]\) est définie pour tout nombre \(x\) par <span class="nowrap">\propfonction[\rep].</span>}
\text{name_sol2=<p>La courbe représentant la fonction \nature \(\propnomfct[\rep]\) est une droite \originel composée de l'ensemble des points de coordonnées \((x \, ; \, y)\) avec \(y=\propnomfct[\rep] (x)\).</p>}
\text{name_sol3l=Comme <span class="nowrap">\proplistimsol[\rep],</span> la droite cherchée passe par le point \(\mathrm{M}\) de coordonnées <span class="nowrap">\((\propant[\rep] \, ; \, \propim[\rep])\).</span>}
\text{name_sol3a=Comme \proplistim0[\rep]
                 <p>et <span class="nowrap">\proplistimsol[\rep],</span></p>
                 la droite cherchée passe par les points de coordonnées \(\mathrm{M}(0 \, ; \, \propcoefb[\rep])\) et <span class="nowrap">\(\mathrm{N}(\propant[\rep] \, ; \, \propim[\rep])\).</span>} 
\text{Courbe=Courbe A,Courbe B,Courbe C,Courbe D}
\text{courbe=courbe A.,courbe B.,courbe C.,courbe D.}
\text{name_sol4=Il s'agit de la <span class="nowrap">\courbe[\rep]</span>}

#endif

#if defined TARGET_couf
\text{naturea=affine.}
\text{naturel=linéaire.}
\text{name_enon=On considère la représentation graphique d'une fonction}
\text{name_quest=Parmi les fonctions proposées, laquelle correspond à la représentation graphique donnée&nbsp;&#63;}
\text{name_sol1a=<p>Pour faciliter les calculs, sur la représentation graphique, on prend deux points à coordonnées entières : \(A(0 \, ; \, \propcoefb[\rep])\) et <span class="nowrap">\(B(\propant[\rep] \, ; \, \propim[\rep])\).</span></p>}
\text{name_sol2a=Ainsi, pour la fonction cherchée,
                <p>le nombre \(0\) doit avoir pour image le nombre <span class="nowrap">\(\propcoefb[\rep]\),</span></p>
                et le nombre \(\propant[\rep]\) doit avoir pour image le nombre <span class="nowrap">\(\propim[\rep]\).</span>
                <p>Or,</p>}
\text{name_sol3a=et}
\text{name_sol1l=<p>Pour faciliter les calculs, sur la représentation graphique, on prend un point à coordonnées entières autre que l'origine du repère&nbsp;: <span class="nowrap">\((\propant[\rep] \, ; \, \propim[\rep])\).</span></p>}
\text{name_sol2l=Ainsi, pour la fonction cherchée, le nombre \(\propant[\rep]\) doit avoir pour image le nombre <span class="nowrap">\(\propim[\rep]\).</span>
                    <p>Or,</p>}
\text{name_sol4=La fonction cherchée est donc la fonction}
#endif

#if defined TARGET_gfon
\text{name_sol1a=La fonction \(\nomfct\) étant affine, sa représentation graphique est une droite.}
\text{name_sol3a=Comme \(\nomfct(0)=\b\) (ordonnée à l'origine), la droite passe par le point de coordonnées <span class="nowrap">\(\mathrm{A}(0 \, ; \, \b)\).</span>}
\text{name_sol1l=La fonction \(\nomfct\) étant linéaire, sa représentation graphique est une droite <span style="color:red">passant par l'origine</span> <span class="nowrap">\(\mathrm{A}(0;0)\).</span>}
\text{namesol2=La courbe représentative de la fonction \(\nomfct\) est l'ensemble des points de coordonnées \((x \, ; \, y)\) avec <span class="nowrap">\(y=\nomfct(x)\).</span>}
\text{name_questa=Déplacer les points A et B de manière à ce que la droite obtenue soit la représentation graphique de la fonction affine \(\nomfct\) définie pour tout nombre \(x\) par}
\text{name_questl=Déplacer les points A et B de manière à ce que la droite obtenue soit la représentation graphique de la fonction linéaire \(\nomfct\) définie pour tout nombre \(x\) par}
\text{name_condA=Point A bien placé}                                    
\text{name_condB=Point B bien placé}
\text{name_sol4e=On calcule l'image d'un nombre non nul.}
\text{name_sol4f=On calcule l'image d'un nombre non nul (on s'arrange pour prendre un nombre entier qui a une image entière pour la fonction \(\nomfct\) afin de simplifier le placement du point dans le repère).}
\text{name_sol5=Pour calculer l'image de \(\ant\), on remplace \(x\) par \(\ant\) dans l'expression algébrique de la fonction.}
\text{name_sol6l=Finalement, la droite passe par les points \(\mathrm{A}(0 \, ; \, 0)\) et }
\text{name_sol6a=Finalement, la droite passe par les points \(\mathrm{A}(0 \, ; \, \b)\) et }
\text{name_yourans=Votre réponse}
\text{name_goodans=Bonne réponse}
\text{name_sol0a=La fonction affine \(\nomfct\) est définie pour tout nombre \(x\) par}
\text{name_sol0l=La fonction linéaire \(\nomfct\) est définie pour tout nombre \(x\) par}
\text{name_sol7=La droite passe par le point}
#endif

#if defined TARGET_afeg
\text{name_quest=Associer l'égalité de gauche à la fonction qui lui correspond.}
#endif

#if defined TARGET_tval
\text{name_enona=On a repéré 4 points \(\mathrm{A}\), \(\mathrm{B}\), \(\mathrm{C}\) et \(\mathrm{D}\) sur la courbe représentative d'une fonction affine <span class="nowrap">\(f\).</span>}
\text{name_enonl=On a repéré 4 points \(\mathrm{A}\), \(\mathrm{B}\), \(\mathrm{C}\) et \(\mathrm{D}\) sur la courbe représentative d'une fonction linéaire <span class="nowrap">\(f\).</span>}
\text{name_quest=Par lecture graphique, compléter le tableau de valeurs correspondant.}
\text{name_hint=Dans un repère, la représentation graphique d'une fonction \(f\) est l'ensemble des points de coordonnées <span class="nowrap">\((x \, ; \, y)\) avec \(y=f(x)\).</span>}
\text{name_sol1=On regarde les coordonnées de chaque point pour complèter le tableau de valeurs.}
\text{name_feed=Vous avez inversé image et antécédent !}
\text{name_cond=Bonne réponse}
#endif

#if defined TARGET_gant || defined TARGET_gim
\text{name_enona=On considère la représentation graphique d'une fonction affine}
\text{name_enonl=On considère la représentation graphique d'une fonction linéaire}
\text{name_quest1= Compléter la phrase (vous pouvez déplacer le point <span class="nowrap">\(\mathrm{A}\))&nbsp;:</span>}
\text{name_ans=Réponse}
\text{name_instr=Vous donnerez la réponse la plus précise possible.<p>Une marge d'erreur inférieure à 0&#44;1 est acceptée.</p>}
\text{name_hint=Dans un repère, la représentation graphique d'une fonction \(\nom\) est l'ensemble des points de coordonnées <span class="nowrap">\((x \, ; \, y)\) avec \(y=\nom(x)\).</span>}
\text{name_feed=Vous semblez confondre image et antécédent.}
\text{name_cond=Bonne réponse}
#if defined TARGET_gant
\text{name_quest3= par la fonction \(\nom\) est égal à}
\text{name_quest2=Par lecture graphique, l'antécédent de}
\text{name_ans1=<b><span style="color: red;">L'antécédent</span></b> du nombre \(\vimg\) par la fonction \(\nom\) est, par définition,
<b><span style="color: red;">l'abscisse</span></b> du point de la droite dont l'ordonnée est <span class="nowrap">\(\vimg\).</span><p>
On se place sur le point de la droite dont l'ordonnée est \(\vimg\) puis, on lit son abscisse.}
\text{name_ans2=Par lecture graphique, \(\vimg\) a pour antécédent \(\vantarron\) par la fonction}
#endif
#if defined TARGET_gim
\text{name_quest3= par la fonction \(\nom\) est égale à}
\text{name_quest2=Par lecture graphique, l'image de}
\text{name_ans1=<b><span style="color: red;">L'image</span></b> du nombre \(\vant\) par la fonction \(\nom\) est, par définition,
<b><span style="color: red;">l'ordonnée</span></b> du point de la droite dont l'abscisse est <span class="nowrap">\(\vant\).</span><p>
On se place sur le point de la droite dont l'abscisse est \(\vant\) puis, on lit son ordonnée.}
\text{name_ans2=Par lecture graphique, \(\vant\) a pour image \(\vimg\) par la fonction}
#endif
#endif

#if defined TARGET_coef 
\text{name_ans=Par lecture graphique, le coefficient de la fonction linéaire est égal à}
\text{name_quest=En déplaçant le point \(\mathrm{A}\) sur les points de la droite d'abscisse entière, déterminer le coefficient de la fonction linéaire.}
\text{name_signen=négatif}
\text{name_signep=positif}
\text{name_inst=Vous donnerez la réponse sous la forme d'un nombre entier si possible ou d'une fraction irréductible de dénominateur positif.}
\text{name_goodans=coefficient}
\text{name_cond1=Bonne réponse}
\text{name_cond2=Bonne réponse en écriture fractionnaire irréductible ou entière}
\text{name_method1=Méthode 1&nbsp;:}
\text{name_sol1=Soit \(a\) le coefficient de la fonction linéaire \(f\).} 
\text{name_sol2=<p>Ainsi, pour tout nombre \(x\), on a <span class="nowrap">\(f(x)=a \times x\)</span> où \(a\) est également le coefficient directeur (ou <span style="color:red">pente</span>) de la droite représentant la fonction \(f\).
<p>Graphiquement, le coefficient directeur \(a\)  de la droite signifie qu'à partir de n'importe quel point de la droite, <span style="color:red">en avançant d'une unité en abscisse, l'ordonnée augmente de \(a\) unité(s).</span></p>}
\text{name_sol3=On repère un point sur la droite à coordonnées entières&nbsp;:}
\text{name_sol4=<p>Pour aller de l'origine du repère au point \(A\), on se déplace de \(\den\) unité(s) sur l'axe des abscisses et de \(\num\) unité(s) sur l'axe des ordonnées donc \(\den \times a = \num\) soit finalement}
\text{name_method2=Méthode 2&nbsp;:}
\text{name_sol5=<p>Une fonction linéaire \(f\) de coefficient \(a\) est définie pour tout nombre \(x\) par }
\text{name_sol6=Ainsi, pour \(x\) non nul, <span class="nowrap">\(a=\frac{f(x)}{x}\).</span>
<p>On repère ensuite un point sur la droite&nbsp;:}
\text{name_sol7=Cela signifie que le nombre \(\den\) a pour image \(\num\) par la fonction <span class="nowrap">\(f\).</span>
<p>Donc} 
\text{name_hint=Le coefficient d'une fonction linéaire est également le coefficient directeur (ou pente) de la droite représentant cette fonction linéaire.}
\text{name_feed1m=<span class="font-weight: bold">Attention&nbsp;:</span> Sur cette droite, lorsque les abscisses des points augmentent, leurs ordonnées augmentent également donc le coefficient directeur de la droite représentant la fonction est positif.}
\text{name_feed1d=<span class="font-weight: bold">Attention&nbsp;:</span> Sur cette droite, lorsque les abscisses des points augmentent, leurs ordonnées diminuent donc le coefficient directeur de la droite représentant la fonction est négatif.}
\text{name_feed=Votre coefficient n'est pas une fraction irréductible.}
\text{name_accord=Cliquer ici pour voir la démonstration}
\text{name_enon=La droite ci-dessous est la représentation graphique d'une fonction linéaire <span class="nowrap">\(f\).</span>}
\text{name_dem1=Pour tout nombre <span class="nowrap">\(x\),</span>}
\text{name_illu=Illustration cas a>0 et x>0}
#endif

#if defined TARGET_scora || defined TARGET_scol
\text{name_signen=négatif,diminuent}
\text{name_signep=positif,augmentent}
\text{name_sol=<p>Sur cette droite&#44; lorsque les abscisses des points augmentent&#44; leurs ordonnées, donc le coefficient directeur de la droite est}
\text{name_enon=Dans un repère, on a tracé une droite représentant une fonction affine \(f\) définie par \(f(x)=a \times x + b\) où \(a\) et \(b\) désignent les coefficients de la fonction affine.}
\text{name_quest1=Cocher la bonne réponse&nbsp;:}
#if defined TARGET_scol
\text{name_ansl=Le signe du coefficient de la fonction linéaire est}
\text{name_enon=Dans un repère, on a tracé une droite représentant une fonction linéaire.}
\text{name_hint=Le coefficient d'une fonction linéaire est également le coefficient directeur (ou pente) de la droite représentant cette fonction linéaire.}
\text{name_soll=Donc le signe du coefficient de la fonction linéaire est }
#endif
#if defined TARGET_scora
\text{name_ansa=Le signe du coefficient \(a\) de la fonction affine est}
\text{name_hint=On considère une fonction affine \(f\) définie par \(f(x)=a \times x + b\) où \(a\) et \(b\) désignent les coefficients de la fonction affine.}
\text{name_hinta=Le coefficient \(a\) de la fonction affine est également le coefficient directeur (ou pente) de la droite représentant la fonction affine.}
\text{name_hintb=Le coefficient \(b\) de la fonction affine est l'ordonnée à l'origine de la droite représentant la fonction affine.}
\text{name_quest2=Compléter (vous pouvez déplacer le point \(\mathrm{A}\))&nbsp;:}
\text{name_ans2=Par lecture graphique, le coefficient \(b\) de la fonction affine est égal à}
\text{name_solaa=Donc le signe du coefficient \(a\) de la fonction affine est }
\text{name_sol3=Ainsi, le coefficient \(b\) est égal à l'ordonnée du point d'intersection de la droite avec l'axe des ordonnées.
<p>Il correspond à l'image de <span class="nowrap">\(0\).</span></p>
Ici, le coefficient \(b\) de la fonction affine est égal à }
#endif
#endif 

#if defined TARGET_fli1 || defined TARGET_fli2
\text{name_inst=Vous donnerez la réponse sous la forme d'un nombre entier si possible ou d'une fraction irréductible de dénominateur positif.}
\text{name_goodans=Bonne réponse}
\text{name_cond=Bonne réponse en écriture fractionnaire irréductible ou entière}
\text{name_feed1=Votre réponse n'est pas une fraction irréductible.}
\text{name_enon=On considère une fonction linéaire <span class="nowrap">\(\nom\).</span>}
\text{name_feed2=Vous semblez avoir mal effectué votre calcul.,Vous avez effectué,au lieu de}
#endif

#if defined TARGET_fli1
\text{name_quest=Calculer le coefficient de la fonction linéaire \(\nom\) sachant que,par cette fonction., l'image de \(\ant1) est égal à \(\img1\),
\(\ant1) est l'antécédent de \(\img1\),\(\img1) est l'image de \(\ant1\),\(\img1\) a pour antécédent \(\ant1\)}
\text{name_ans1=Le coefficient de la fonction linéaire \(\nom\) est égal à }
\text{name_hint=Une fonction linéaire \(\nom\) de coefficient \(a\) est définie pour tout nombre \(x\) par <span class="nowrap">\(\nom (x)=a \times x\).</span>} 
\text{name_sol1=Ainsi, pour tout nombre \(x\) non nul, <span class="nowrap">\(a=\frac{\nom (x)}{x}\).</span>}
\text{name_sol2=D'après l'énoncé, \name_quest[\ch] c'est à dire <span class="nowrap">\(\nom (\ant1)=\img1\).</span> }
\text{name_sol3=On déduit alors que}
\text{name_feed2=Vous avez inversé dans votre calcul l'image et l'antécédent.}
#endif

#if defined TARGET_fli2
\text{name_quest=Calculer \(\nom (\ant2)\) sachant que <span class="nowrap">\(\nom (\ant1)=\img1\).</span>}
\text{name_ans1=\(\nom (\ant2)=\)}
\text{name_hint=Une fonction linéaire modélise une situation de proportionnalité.<p>On peut ainsi traduire l'énoncé en un tableau de valeurs pour trouver le nombre demandé.</p>}
\text{name_sol1=On traduit l'énoncé en un tableau de valeurs.}
\text{name_sol2=Comme \(\nom\) est une fonction linéaire, ce tableau est un tableau de proportionnalité.}
\text{name_sol3=Donc}
#endif

#if defined TARGET_repar
\text{name_inst=Vous donnerez la réponse sous la forme d'un nombre entier si possible ou d'une fraction irréductible de dénominateur positif.}
\text{name_questl=Donner le coefficient de la fonction linéaire \(\nomfct\) définie pour tout nombre \(x\) par <span class="nowrap">\(\nomfct(x)=\data[1]\).</span>}
\text{name_ans1l=Le coefficient de la fonction linéaire \(\nomfct\) est égal à}
\text{name_hintl=Une fonction linéaire \(\nomfct\) est définie pour tout nombre \(x\) par \(\nomfct(x)= a \times x\) où \(a\) désigne le coefficient de la fonction linéaire <span class="nowrap">\(\nomfct\).</span>}
\text{name_hinta=Une fonction affine \(\nomfct\) est définie pour tout nombre \(x\) par \(\nomfct(x)= a \times x + b\) où \(a\)  et \(b\) sont les coefficients de la fonction affine mais également pour \(a\) le coefficient directeur
et pour \(b\) l'ordonnée à l'origine de la droite représentant la fonction affine.}
\text{name_questa=<p>Retrouver le coefficient directeur et l'ordonnée à l'origine de la droite représentant la fonction affine \(\nomfct\) définie pour tout nombre \(x\) par <span class="nowrap">\(\nomfct(x)=\data[1]\).</span></p>}
\text{name_ans1a=Le coefficient directeur de la droite est égal à }
\text{name_ans2a=L'ordonnée à l'origine de la droite est égale à }
\text{name_sol3a=Le coefficient directeur de la droite est égal à <span class="nowrap">\(\data[2]\).</span>
                 <p>L'ordonnée à l'origine de la droite est égale à <span class="nowrap">\(\data[3]\).</span></p>}
#endif

#if defined TARGET_clas
\text{name_enona=ni linéaires, ni constantes}
\text{name_quest=Classer les fonctions suivantes suivant leur nature.}
\text{name_enonafpart=Fonctions affines particulières}
\text{name_enonfl=Fonctions linéaires}
\text{name_enonfc=Fonctions constantes}
\text{name_enonfa=Fonctions affines \name_enona}
\text{name_enonfna=Fonctions non affines}
\text{name_listfl=Liste des fonctions linéaires}
\text{name_listfc=Liste des fonctions constantes}
\text{name_listfa=Liste des fonctions affines \name_enona}
\text{name_listfna=Liste des fonctions non affines}
\text{name_hint=\(a,b,c\) désignent 3 nombres avec \(a\) et \(b\) non nuls.
<ul><li>Une fonction constante est de la forme \(x \mapsto c \).</li>
    <li>Une fonction linéaire est de la forme \(x \mapsto a x \).</li>
    <li>Une fonction affine quelconque (non linéaire, non constante) est de la forme <span class="nowrap">\(x \mapsto a x + b \).</span></li>
</ul>}
#endif
