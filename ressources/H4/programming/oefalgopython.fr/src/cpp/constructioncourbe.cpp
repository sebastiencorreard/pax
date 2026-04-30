target=decoupage1 secante1 tangente1 rectangle1 milieu1 trapeze1 droitered1 droitered2 droitecar1 euler1 euler2

\language{fr}
\author{Julien, Lyotard}
\email{Julien.Lyotard@ac-dijon.fr}

\computeanswer{yes}
\precision{1000}

\text{theme=(\confparm1==)?ambiance:\confparm1}

\integer{nn=randint(10..50)}
\integer{a=randitem(+,-)randint(1..10)}
\integer{b=randint(-4..4)}
\integer{c=randint(-10..10)}
\function{f=maxima(expand(\a*x^2+\b*x+\c))}
\function{fp=diff(\f,x)}
\text{fpp=wims(replace x by x_i in \fp)}
\text{fct_pari=wims(replace x by t in \f)}
\text{fct_parip=wims(replace x by t in \fp)}
\text{fpyth=wims(replace \^ by ** in \f)}
\text{fpythp=wims(replace \^ by ** in \fp)}
\text{fjss=wims(replace \^2 by *x in \f)}
\text{fjs=wims(replace \^3 by *x*x in \fjss)}
\text{ft=texmath(\f)}
\real{x1=-\b/2/\a}
\integer{xg=randint(2..5)}
\integer{xd=randint(2..5)}
\integer{xmin=floor(\x1)-\xg}
\integer{xmax=floor(\x1)+\xd}
\rational{ymin=(\a>0)?evalue(\f,x=\x1)-10}
\rational{ymax=(\a>0 and abs(\xg)>=abs(\xd))?evalue(\f,x=\xmin)+10:evalue(\f,x=\xmax)+10}
\rational{ymax=(\a<0)?evalue(\f,x=\x1)+10}
\rational{ymin=(\a<0 and abs(\xg)>=abs(\xd))?evalue(\f,x=\xmin)-10:evalue(\f,x=\xmax)-10}
\text{tymin=texmath(\ymin)}
\text{tymax=texmath(\ymax)}
\integer{xming=(\xmin>0)?-1:\xmin-1}
\integer{xmaxg=(\xmax<0)?1:\xmax+1}
\integer{ymaxg=(\ymax<0 and \ymin<0 )?10:\ymax}
\integer{yming=(\ymax>0 and \ymin>0)?-10:\ymin}
\matrix{repere=\xming,\ymaxg,\xmaxg,\yming}
\text{zz=pari(f(t)=\fct_pari;)}

# include "graph_decoupage.inc"
#if defined TARGET_decoupage1
# include "decoupage1.inc"
\integer{reppyth=3}
\text{enonce_algo=Compléter l'algorithme en découpant l'intervalle \(\lbracket \xmin;\xmax \rbracket \)
 en \nn sous-intervalles de même longueur.}
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){return \fjs;}, \xmin, \xmax], {strokeWidth: 2});}
#endif
#if defined TARGET_secante1
# include "secante1.inc"
\integer{reppyth=9}
\text{enonce_algo=Compléter l'algorithme en découpant l'intervalle \(\lbracket \xmin;\xmax \rbracket \)
 en \nn sous-intervalles de même longueur.}
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){return \fjs;}, \xmin, \xmax], {strokeWidth: 2});}
#endif
#if defined TARGET_tangente1
\text{zzz=pari(ffp(t)=\fct_parip;)}
# include "tangente1.inc"
\integer{reppyth=8}
\text{enonce_algo=Compléter l'algorithme en découpant l'intervalle \(\lbracket \xmin;\xmax \rbracket \)
 en \nn sous-intervalles de même longueur.}
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){return \fjs;}, \xmin, \xmax], {strokeWidth: 2});}
#endif
#if defined TARGET_rectangle1
# include "rectangle1.inc"
\integer{reppyth=7}
\real{aG=pari(print(aire_gauche);)}
\real{aD=pari(print(aire_droite);)}
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){return \fjs;}, \xmin, \xmax], {strokeWidth: 2});}
\text{enonce_algo=Compléter l'algorithme en découpant l'intervalle \(\lbracket \xmin;\xmax \rbracket \)
 en \nn sous-intervalles de même longueur.}
\text{titregraph=Représentation graphique de la courbe \(C_f\) et des rectangles créés}
#endif
#if defined TARGET_milieu1
# include "milieu1.inc"
\integer{reppyth=5}
\real{aM=pari(print(aire_milieu);)}
\text{enonce_algo=Compléter l'algorithme en découpant l'intervalle \(\lbracket \xmin;\xmax \rbracket \)
 en \nn sous-intervalles de même longueur.}
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){return \fjs;}, \xmin, \xmax], {strokeWidth: 2});}
\text{titregraph=Représentation graphique de la courbe \(C_f\) et des rectangles créés}
#endif
#if defined TARGET_trapeze1
# include "trapeze1.inc"
\integer{reppyth=5}
\real{aT=pari(print(aire_trapeze);)}
\text{enonce_algo=Compléter l'algorithme en découpant l'intervalle \(\lbracket \xmin;\xmax \rbracket \)
 en \nn sous-intervalles de même longueur.}
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){return \fjs;}, \xmin, \xmax], {strokeWidth: 2});}
\text{titregraph=Représentation graphique de la courbe \(C_f\) avec les points et les trapèzes créés}
#endif
#if defined TARGET_droitered1
# include "droitered1.inc"
\integer{reppyth=7}
\text{enonce_algo=Compléter l'algorithme et vérifier vos calculs à l'aide du graphique.}
\text{Bfonction=}
#endif
#if defined TARGET_droitered2
# include "droitered2.inc"
\integer{reppyth=(\nch==1)?3}
\integer{reppyth=(\nch==2)?4}
\integer{reppyth=(\nch==3)?5}
\text{enonce_algo=Compléter l'algorithme et vérifier vos calculs à l'aide du graphique.}
\text{Bfonction=}
#endif
#if defined TARGET_droitecar1
# include "droitecar1.inc"
\integer{reppyth=2}
\text{enonce_algo=Compléter l'algorithme et vérifier vos calculs à l'aide du graphique.}
\text{Bfonction=}
#endif
#if defined TARGET_euler1
# include "euler1.inc"
\integer{reppyth=11}
#endif
#if defined TARGET_euler2
# include "euler2.inc"
\integer{reppyth=14}
#endif
#if defined TARGET_euler1 || defined TARGET_euler2
\text{enonce_algo=Compléter l'algorithme afin de tracer la fonction exponentielle sur
 l'intervalle \(\lbracket \aalea;\balea \rbracket \) en découpant l'intervalle de définition de la fonction \(f\) en \nn sous-intervalles.}
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){ return Math.exp(x);}, \xmin, \xmax], {strokeWidth: 2});}
\text{titregraph=Représentation graphique de la courbe théorique de la fonction exponentielle en bleu et de la ligne
 polygonale construite avec la méthode d'Euler}
\integer{nvaex=randint(1..2)}
\text{vaex=\sqrt{1+h},\frac{1}{1+h}}
\text{fvaex=1+h/2,1-h}
\text{vaexcal=\sqrt{1.1},\frac{1}{1.1}}
\text{repva1=1.05,0.9}
\text{repva2=1.049,0.909}
\real{repvaex1=\repva1[\nvaex]}
\real{repvaex2=\repva2[\nvaex]}
#endif

#if defined TARGET_decoupage1 || defined TARGET_secante1 || defined TARGET_tangente1
\text{enon3=Pour construire une approximation de la représentation graphique de la fonction \(f\)
 sur l'intervalle \(\lbracket a;b \rbracket \), on découpe l'intervalle \(\lbracket a;b \rbracket \)
 en un nombre fini \(n\) de sous-intervalles de même longueur.}
#endif
#if defined TARGET_rectangle1 || defined TARGET_milieu1 || defined TARGET_trapeze1
\text{enon3=Pour déterminer une approximation de l'intégrale d'une fonction \(f\) sur un intervalle [a;b], on découpe l'intervalle [a;b] en un nombre fini \(n\) de sous-intervalles de même longueur.}
#endif

#if defined TARGET_secante1
\text{Bfonction=var c1=brd.create('functiongraph', [function(x){return \fjs;}, \xmin, \xmax], {strokeWidth: 2});}
\text{titregraph=Représentation graphique de la courbe \(C_f\) avec les points et les droites créées}
#endif

\text{B=JXG.Options.point.showInfobox = true;
JXG.Options.point.infoboxDigits = 5;
JXG.Options.point.face = "+";
JXG.Options.point.withLabel=true;
JXG.Options.point.size =4;
JXG.Options.text.useMathJax = true;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:true, boundingbox: [\repere],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,
  zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: false,eps: 0.001},
  pan: {needShift: false,enabled: true,needTwoFingers: true,pinchHorizontal: true, pinchVertical: true,pinchSensitivity: 7}});
\Bfonction
}
\text{A=slib(geo2D/jsxgraph jsxbox,500 x 500,\B)}

\text{xD=pari(print(xxli);)}
\text{yD=pari(print(yyli);)}
\matrix{xl=wims(declosing \xD)}
\matrix{yl=wims(declosing \yD)}
\text{mD=pari(print(mmli);)}
\text{pD=pari(print(ppli);)}
\matrix{ml=wims(declosing \mD)}
\matrix{pl=wims(declosing \pD)}

\#debug
L'utilisation de special mathml ne marche pas pour les coordonnées des points.
 Cela interfére avec le type coding.
contin=\contin||step=\step |etp=\etp|vddd=\vddd||vfff=\vfff|
<br>xlli=\xl
<br>ylli=\yl


\statement{<div class="encadre">
<div id="boited">
<img src="\imagedir/python.png" alt="Logo de Python">
</div>
<p class="problematique">\prob</p>
<div class="enonce">
\enonce
<div class="question">
#if defined TARGET_decoupage1 || defined TARGET_secante1 || defined TARGET_tangente1 || defined TARGET_rectangle1 || defined TARGET_milieu1 || defined TARGET_trapeze1
<div class="bold">Soit \(n\) un entier naturel non nul. Découpage de l'intervalle \(\lbracket a;b \rbracket \) en \(n\)
 sous-intervalles :</div>
<ul><li>Soit \(a\) et \(b\) deux nombres réels définis tels que \(a<b\).
<br>\enon3</li></ul>
<div class="wimscenter">\B1</div>
<ul>
<li>Modifier le nombre de sous-intervalles de la figure proposée puis déterminer la longueur d'un intervalle \(h\)
 en fonction de \(a\), \(b\) et \(n\).
 En survolant les points à l'aide de la souris, on peut lire leurs coordonnées.
<div class="wimscenter"> \(h=\)\embed{reply1,10}</div></li>
<li>Modifier le nombre de sous-intervalles de la figure proposée et déplacer le point \(x_i\). Exprimer
 la valeur de \(x_{i}\) en fonction de \(a\), \(h\) et de l'index \(i\) :
<div class="wimscenter">\(x_{i}=\)\embed{reply2,10}</div></li>
</ul>
#if defined TARGET_secante1
On considère deux points \(A_i\) et \(A_{i+1}\) comme le montre la construction ci-dessous.
<div class="wimscenter"><img src="\imagedir/secante.png" alt="Coefficient directeur"></div>
On souhaite relier ces deux points \(A_i\) et \(A_{i+1}\) par une droite d'équation de la forme \(y=m_i x+p_i\).
<ul>
<li>À l'aide du graphique, déterminer les coordonnées de chacun des points en fonction
 de la fonction \(f\) de \(x_i\) et de \(h\).
<div class="wims_instruction"> Pour écrire correctement \(x_i\), taper x_i .Utiliser cette syntaxe
 \(m_i\) ou \(p_i\).</div>
<div class="wimscenter">\(A_{i}=\huge\lpar \) \embed{reply3,6};\embed{reply4,6} \(\huge\rpar\)</div>
<div class="wimscenter">\(A_{i+1}=\huge\lpar \) \embed{reply5,7};\embed{reply6,7} \(\huge\rpar\)</div></li>
<li>Déterminer le coefficient directeur de cette droite en fonction de \(f\),
 de \(x_i\) et de \(h\) :
<div class="wimscenter">\(m_i=\)\embed{reply7,15}</div></li>
<li>Déterminer l'ordonnée à l'origine de cette droite en sachant que le point \(A_i\)
 appartient à la droite :
<div class="wimscenter">\(p_i=\)\embed{reply8,15}</div></li>
</ul>
#endif
#if defined TARGET_tangente1
On souhaite construire l'enveloppe des tangentes à la courbe représentative de la fonction
 \(f\). Par conséquent on va construire la tangente associée à chaque point \(A_i\).
 <div class="wimscenter"><img src="\imagedir/tangente.png" alt="Tangente"></div>
<ul>
<li>À l'aide du graphique, déterminer les coordonnées du point \(A_i\).
<div class="wims_instruction"> Pour écrire correctement \(x_i\), taper x_i .</div>
<div class="wimscenter">\(A_{i}=\huge\lpar\) \embed{reply3,6};\embed{reply4,6} \(\huge\rpar\)</div></li>
<li>Calculer la dérivée de la fonction \(f\) au point d'abscisse \( {x} = {x_i} \) :
<div class="wimscenter">\(f^\prime(x_i) =\) \embed{reply5,6}</div></li>
<li>Soit \(y = m_i x + p_i\) l'équation réduite de la tangente à la courbe représentant \(f\) au point \(A_i\).
Exprimer le coefficient directeur de la tangente au point \(A_i\) en fonction de \(f^\prime\)
 et de \(x_i\) :
<div class="wimscenter">\(m_i=\) \embed{reply6,6}</div></li>
<li>Soit en utilisant l'équation générale de la tangente soit en utilisant le fait que le point \(A_i\)
 appartient à la tangente, déterminer l'ordonnée à l'origine de cette tangente. On l'exprimera
 à l'aide des fonctions \(f\) et \(f^\prime\) ainsi que \(x_i\) :
 <div class="wimscenter">\(p_i=\)\embed{reply7,15}</div></li>
</ul>
#endif
#if defined TARGET_rectangle1
</div>
<div class="question">
<div class="bold">Après avoir découpé l'intervalle \(\lbracket a;b \rbracket\), on utilise la méthode des rectangles.
 Pour chaque sous-intervalle \(\lbracket x_i;x_{i+1} \rbracket\), on construit un rectangle :</div>
<ul>
<li><u>Méthode des rectangles à gauche représentée en vert :</u> Le rectangle passe par le point d'intersection de la
 courbe \(\C_f\) avec la droite verticale ayant pour abscisse l'abscisse <u>à gauche</u> de l'intervalle. Les 4 sommets
 du rectangle ont donc respectivement pour coordonnées \((x_i ;0)\), \((x_{i+1} ;0)\), \((x_i ;f(x_i))\) et
 \((x_{i+1} ;f(x_i))\).</li>
<li><u>Méthode des rectangles à droite représentée en rouge :</u> Le rectangle passe par le point d'intersection de la
 courbe \(\C_f\) avec la droite verticale ayant pour abscisse l'abscisse <u>à droite</u> de l'intervalle. Les 4 sommets
 du rectangle ont donc respectivement pour coordonnées \((x_i ;0)\), \((x_{i+1} ;0)\), \((x_i ;f(x_{i+1}))\) et
 \((x_{i+1} ;f(x_{i+1}))\).</li>
</ul>
<div class="wimscenter">\B2</div>
<ul>
<li>Déterminer l'aire à gauche du premier rectangle vert en fonction de \(f\), \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{gauche}}=\) \embed{reply3,10} </div></li>
<li>Si on découpe l'intervalle en trois parties égales, déterminer l'aire à gauche des rectangles
 verts en fonction de \(f\), \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{gauche}}=\) \embed{reply4,30}</div></li>
<li>Déterminer l'aire à droite du premier rectangle rouge en fonction de \(f\), \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{droite}}=\) \embed{reply5,10} </div></li>
<li>Si on découpe l'intervalle en trois parties égales, déterminer l'aire à droite des rectangles rouges
 en fonction de \(f\), \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{droite}}=\) \embed{reply6,30}</div></li>
</ul>
#endif
#if defined TARGET_milieu1
</div>
<div class="question">
<div class="bold">Après avoir découpé l'intervalle \(\lbracket a;b \rbracket\), on utilise la méthode des milieux.</div>
<div class="wimscenter">\B2</div>
<ul>
<li>Déterminer l'aire du premier rectangle orange en fonction de \(f\), \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{milieu}}=\) \embed{reply3,10} </div></li>
<li>Si on découpe l'intervalle en trois parties égales, déterminer l'aire des rectangles oranges en fonction de \(f\),
 \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{milieux}}=\) \embed{reply4,30}</div></li>
</ul>
#endif
#if defined TARGET_trapeze1
</div>
<div class="question">
<div class="bold">Après avoir découpé l'intervalle \(\lbracket a;b \rbracket\), on utilise la méthode des trapèzes.</div>
<div class="wimscenter">\B2</div>
<ul><li>Déterminer l'aire du premier trapèze violet en fonction de \(f\), \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{trapèze}}=\) \embed{reply3,10} </div></li>
<li>Si on découpe l'intervalle en trois parties égales, déterminer l'aire des trapèzes violets en fonction de \(f\),
 \(a\) et \(h\) :
<div class="wimscenter">\(A_{\text{trapèzes}}=\) \embed{reply4,30}</div></li>
</ul>
#endif
#endif
#if defined TARGET_droitered1
<div class="bold">Déterminer une équation réduite de la droite \(( d )\) :</div>
<ul>
<li>Donner la formule permettant le calcul du coefficient directeur \(m\) lorsque les coordonnées de 2 points
 \(A(x_A;y_A)\) et \(B(x_B;y_B)\) sont connues :
<div class="wims_instruction"> Pour écrire correctement \(x_A\), taper x_A .
 Pour écrire correctement \(y_A\), taper y_A ...</div>
<div class="wimscenter">\(m=\) \embed{reply1,20} </div></li>
<li>Déterminer la valeur du coefficient directeur sous forme fractionnaire si nécessaire :
<div class="wimscenter">\(m=\) \embed{reply2,20} </div></li>
<li>À l'aide des calculs précédents, déduire l'équation réduite de la droite :
<div class="wimscenter">\(y=\) \embed{reply3,20} </div></li>
<li>Le point \(A\) ou \(B\) appartient à la droite \((d)\) donc on peut écrire l'équation suivante :
<div class="wimscenter">\embed{reply4,20} </div></li>
<li>Résoudre l'équation précédente et déterminer la valeur de l'ordonnée à l'origine \(p\).
<div class="wimscenter">\(p=\)\embed{reply5,20} </div></li>
<li>En déduire l'équation réduite de la droite \((d)\) :
<div class="wimscenter">\(y=\)\embed{reply6,20} </div></li>
</ul>
#endif
#if defined TARGET_droitered2
<div class="bold">Déterminer une équation réduite de la droite \(( d )\) :</div>
<ul>
<li>Compléter le champ permettant de donner l'équation réduite de la droite \((d)\) et
 laisser l'autre champ vide :
<div class="wimscenter">\(x=\) \embed{reply1,20} </div>
<div class="wimscenter">\(y=\) \embed{reply2,20} </div></li>
</ul>
#endif
#if defined TARGET_droitecar1
<div class="bold">Déterminer une équation cartésienne de la droite \(( d )\) :</div>
<ul>
<li>Une équation cartésienne de la droite \((d)\) est :
<div class="wimscenter">\embed{reply1,20} </div></li>
</ul>
#endif
#if defined TARGET_euler1 || defined TARGET_euler2
<div class="bold">Approximation affine d'une fonction :</div>
Soit \(f\) une fonction dérivable sur un intervalle \(I\) et \(x_0 \in I\). La fonction \(f\)
peut être approchée par une fonction affine au voisinage de \(x_0\).
L'opération consiste à remplacer l'expression d'une fonction \(f\) au voisinage d’un point \(\x_0\) par celle d'une
 fonction affine tangente à la courbe \(C_f\)
 en ce point. Graphiquement on considère que les points \(A_1\) et \(A\prime_1\) sont confondus lorsque \(\h\) est
 proche de 0.
 <div class="wimscenter"><img src="\imagedir/App_Aff.png" alt="Schéma pour l'approximation affine"></div>
<ul>
<li>Déterminer l'équation réduite de la tangente à la courbe \(C_f\) au point d'abscisse \(\x_0\) en fonction de \(f\),
 \(f \prime\), \(x_0\) et \(x\).
<div class="wims_instruction"> Pour écrire correctement \(x_0\), taper x_0 .</div>
<div class="wimscenter">\(y=\) \embed{reply1,20} </div></li>
<li>Quelle expression peut-on écrire à l'aide de l'approximation réalisée, de l'équation de tangente
au point d'abscisse \(x_0+h\) en fonction de \(f\), \(f \prime\), \(x_0\) et \(h\) ?
<div class="wimscenter"> Pour \(h\) proche de zéro, \(f(x_0+h)=\) \embed{reply2,20} </div></li>
<li>En reconnaissant une fonction de référence, vérifier la validité de cette formule sur l' exemple suivant :
<div class="wimscenter"> Pour \(h\) proche de zéro, \(\vaex[\nvaex]=\)\embed{reply3,10}</div>
Arrondir les résultats au millième.
<div class="wimscenter">À l'aide de l'approximation, on a \(\vaexcal[\nvaex]=\)\embed{reply4,10}</div>
<div class="wimscenter">La valeur arrondie à \(10^(-4)\) est de \(\vaexcal[\nvaex]=\)\embed{reply5,10}</div></li>
</ul>
</div>
<div class="question">
<div class="bold">Application à la fonction exponentielle :</div>
La méthode d'Euler consiste à approcher la courbe \(C\) de la fonction \(f\) en utilisant l'approximation affine.
<div class="wimscenter"><img src="\imagedir/Euler1.png" alt="Méthode d'Euler"></div>
<ul>
<li>À l'aide de la définition de la fonction exponentielle, déterminer l'ordonnée
 \(y_0\) du point \(A_0\) en fonction de la fonction \(f\) et de \(x_0\).
<div class="wimscenter">\(y_0=\)\embed{reply6,10} </div></li>
<li>En utilisant l'approximation affine, exprimer l'ordonnée \(y_1\) du point \(A_1\)
en fonction de \(y_0\) et \(h\).
<div class="wimscenter">\(y_1=f(x_0+h)=\)\embed{reply7,10} </div></li>
<li>En utilisant l'approximation affine, exprimer l'ordonnée \(y_2\) du point\(A_2\)
en fonction de \(y_1\) et \(h\).
<div class="wimscenter">\(y_2=f(x_1+h)=\)\embed{reply8,10}</div></li>
<li>Généraliser cette écriture en exprimant \(y_{k+1}\) en fonction de \(y_k\) et \(h\).
<div class="wimscenter">\(y_{k+1}=f(x_k+h)=\)\embed{reply9,10} </div></li>
<li>Généraliser l'écriture de \(x_{k+1}\) en fonction de \(x_k\) et \(h\).
<div class="wimscenter">\(x_{k+1}=\)\embed{reply10,10} </div></li>
</ul>
#endif
#if defined TARGET_euler2
<ul>
<li>En ayant pris soin de reconnaitre une suite particulière, déterminer la formule implicite de \(x_{k}\) en fonction de
 \(k\) et \(h\).
<div class="wimscenter">\(x_{k}=\)\embed{reply11,10} </div></li>
<li>En ayant pris soin de reconnaitre une suite particulière, déterminer la formule implicite de \(y_{k}\) en fonction de
 \(k\) et \(h\).
<div class="wimscenter">\(y_{k}=\)\embed{reply12,10}</div></li>
<li>En déduire une expression de \(y_{k}\) en fonction de
 \(x_k\) et \(h\).
<div class="wimscenter">\(y_{k}=\)\embed{reply13,10}</div></li>
</ul>
#endif
</div>
<div class="question">
<div class="bold">\enonce_algo</div>
<div class="wimsborder box">
\embed{reply\reppyth,[python,[\code]];[idtest2,theme=\theme canvas init \instruction_code,Jouer le code !]}
</div>
<div class="wimscenter wimsborder box">
<b>\titregraph</b>
\A
</div>


</div></div></div>

<script>
function graph(){
x_liste=Sk.ffi.remapToJs(Sk.globals["x_list"]);
y_liste=Sk.ffi.remapToJs(Sk.globals["y_list"]);
\coefi
const xlen=x_liste.length;
const brd = JXG.JSXGraph.initBoard('jsxbox', {axis:true, boundingbox: [\repere],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,
  zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: false,eps: 0.001},
  pan: {needShift: false,enabled: true,needTwoFingers: true,pinchHorizontal: true, pinchVertical: true,pinchSensitivity: 7}});
brd.suspendUpdate();
\coefr
brd.unsuspendUpdate();}
execidtest2.addEventListener('click',graph);
</script>
}
#if defined TARGET_euler1 || defined TARGET_euler2
\answer{}{f'(x_0)*(x-x_0)+f(x_0)}{type=formal}{option=nonstop}
\answer{}{f'(x_0)*h+f(x_0)}{type=formal}{option=nonstop}
\answer{}{\fvaex}{type=formal}{option=nonstop}
\answer{}{\repvaex1}{type=numeric}{option=nonstop comma}
\answer{}{\repvaex2}{type=numeric}{option=nonstop comma}
\answer{}{f(x_0)}{type=formal}{option=nonstop}
\answer{}{y_0*(1+h)}{type=formal}{option=nonstop}
\answer{}{y_1*(1+h)}{type=formal}{option=nonstop}
\answer{}{y_k*(1+h)}{type=formal}{option=nonstop}
\answer{}{x_k+h}{type=formal}{option=nonstop}
#if defined TARGET_euler2
\answer{}{h*k}{type=formal}{option=nonstop}
\answer{}{(1+h)^k}{type=formal}{option=nonstop}
\answer{}{(1+h)^(x_k/h)}{type=formal}{option=nonstop}
#endif
\answer{}{[x_list,[\xl]],[y_list,[\yl]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
#if defined TARGET_droitered1
\answer{}{(y_B-y_A)/(x_B-x_A)}{type=formal}{option=nonstop}
\answer{}{\am}{type=numexp}{option=nonstop}
\answer{}{\bm,\em}{type=formal}{option=nonstop}
\answer{}{\am*\xA+p=\yA,p}{type=equation}{option=nonstop}
\answer{}{\dm}{type=formal}{option=nonstop}
\answer{}{\em}{type=formal}{option=nonstop}
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[m,[\ml]],[p,[\pl]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
#if defined TARGET_droitered2
\answer{}{\rep1}{type=formal}{option=nonstop default="Vide"}
\answer{}{\rep2}{type=formal}{option=nonstop default="Vide"}
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[xv,[\x_A]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[yh,[\y_A]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[m,[\ml]],[p,[\pl]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
\text{nstep=}
#endif
#if defined TARGET_droitecar1
\matrix{zzzz=\reply2}
\integer{eqa=wims(declosing \zzzz[4])}
\integer{eqb=wims(declosing \zzzz[5])}
\integer{eqc=wims(declosing \zzzz[6])}
\answer{}{\ml[1]*x+\ml[2]*y+\ml[3]=0}{type=equation}{option=nonstop}
\answer{}{[x_list,[\xl]],[y_list,[\yl]],[a,[\ml[1]]],[b,[\ml[2]]],[c,[\ml[3]]]}{type=runcode}{option=precision=10000 \instruction_code noanalyzeprint}{weight=0}
\condition{Les valeurs des coefficients \(a\), \(b\) et \(c\) dans l'algorithme sont justes : }{(\eqa*\x_A+\eqb*\y_A+\eqc==0) and (\eqa*\x_B+\eqb*\y_B+\eqc==0)}{weight=1}
#endif

#if defined TARGET_decoupage1 || defined TARGET_secante1 || defined TARGET_tangente1 || defined TARGET_rectangle1 || defined TARGET_milieu1 || defined TARGET_trapeze1
\answer{}{(b-a)/n}{type=formal}{option=nonstop}
\answer{}{a+h*i}{type=formal}{option=nonstop}
#endif
#if defined TARGET_secante1
\answer{}{x_i}{type=formal}{option=nonstop}
\answer{}{f(x_i)}{type=formal}{option=nonstop}
\answer{}{x_i+h}{type=formal}{option=nonstop}
\answer{}{f(x_i+h)}{type=formal}{option=nonstop}
\answer{}{(f(x_i+h)-f(x_i))/h}{type=formal}{option=nonstop}
\answer{}{f(x_i)-m_i*x_i}{type=formal}{option=nonstop}
\answer{}{[a,[\xmin]],[b,[\xmax]],[n,[\nn]],[x_list,[\xl]],[y_list,[\yl]],[m_list,[\ml]],[p_list,[\pl]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
#if defined TARGET_tangente1
\answer{}{x_i}{type=formal}{option=nonstop}
\answer{}{f(x_i)}{type=formal}{option=nonstop}
\answer{}{\fpp}{type=formal}{option=nonstop}
\answer{}{f'(x_i)}{type=formal}{option=nonstop}
\answer{}{f(x_i)-x_i*f'(x_i)}{type=formal}{option=nonstop}
\answer{}{[a,[\xmin]],[b,[\xmax]],[n,[\nn]],[x_list,[\xl]],[y_list,[\yl]],[m_list,[\ml]],[p_list,[\pl]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
#if defined TARGET_rectangle1
\answer{}{h*f(a)}{type=formal}{option=nonstop}
\answer{}{h*(f(a)+f(a+h)+f(a+2h))}{type=formal}{option=nonstop}
\answer{}{h*f(a+h)}{type=formal}{option=nonstop}
\answer{}{h*(f(a+h)+f(a+2h)+f(a+3h))}{type=formal}{option=nonstop}
\answer{}{[a,[\xmin]],[b,[\xmax]],[n,[\nn]],[x_list,[\xl]],[y_list,[\yl]],[aire_gauche,[\aG]],[aire_droite,[\aD]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
#if defined TARGET_milieu1
\answer{}{h*f(a+0.5*h)}{type=formal}{option=nonstop}
\answer{}{h*(f(a+0.5*h)+f(a+1.5*h)+f(a+2.5*h))}{type=formal}{option=nonstop}
\answer{}{[a,[\xmin]],[b,[\xmax]],[n,[\nn]],[x_list,[\xl]],[y_list,[\yl]],[aire_milieu,[\aM]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
#if defined TARGET_trapeze1
\answer{}{h*(f(a)+f(a+h))/2}{type=formal}{option=nonstop}
\answer{}{h/2*(f(a)+2*f(a+h)+2*f(a+2*h)+f(a+3h))}{type=formal}{option=nonstop}
\answer{}{[a,[\xmin]],[b,[\xmax]],[n,[\nn]],[x_list,[\xl]],[y_list,[\yl]],[aire_trapeze,[\aT]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
#if defined TARGET_decoupage1
\answer{}{[a,[\xmin]],[b,[\xmax]],[n,[\nn]],[x_list,[\xl]],[y_list,[\yl]]}{type=runcode}{option=precision=10000 \instruction_code}{weight=10}
#endif
