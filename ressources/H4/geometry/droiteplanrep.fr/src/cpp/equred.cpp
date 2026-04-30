target = eqred eqredstep
#define TITRE Equation réduite
#if defined TARGET_eqred
\title{TITRE }
#else
\title{TITRE (Guidée)}
#endif
\author{Cyrille,Douriez;Bruno,Mifsud}
\email{cyrille.douriez@ac-amiens.fr;communaute.mutuwims@mlaposte.net}

\computeanswer{no}
\keywords{line,equations}

\text{confparm1= items(\confparm1)=0 ? 1:\confparm1}
\integer{m=randint(1..8)*randint(-1,1)}
\integer{p=randint(-15..15)}

\integer{x1=randint(-10..10)}
\integer{y1=\m*\x1+\p}
#if defined TARGET_eqred
\integer{choix=randint(1,2,2,2)}
\integer{x2=(\choix=1)? \x1:\x1+(randint(1..10)*randint(-1,1))}
\integer{y2=(\choix=1)? \y1+(randint(1..10)*randint(-1,1)):\m*\x2+\p}
\function{f=(\choix=1)? \x1:\m x+\p}
\integer{pos=(\choix=1)? 1:2}
#endif
#if defined TARGET_eqredstep
\integer{x2=\x1+(randint(2..7)*randint(-1,1))}
\integer{y1=\m*\x1+\p}
\integer{y2=\m*\x2+\p}
\integer{choix1=randint(1,2)}
\function{f=\m*x+\p}
\matrix{lettre=A,B
\x1,\x2
\y1,\y2}
\text{etape=r1
r2,r3
r4,r5,r6}
\nextstep{\etape}
#endif
%%%%%%%%%%%%Image

\if{\confparm1=1}{
\text{imgtemp=xrange -100,100
yrange -100,100
hline 0,0,black
vline 0,0,black
parallel -50,-2,-50,2,100,0,2,black
parallel -2,-50,2,-50,0,100,2,black
text black , 50,-0.5,small , 50
text black , 1,50,small , 50
text black , 1,-1,small , O
linewidth 1.5}

\text{image=draw(100,100
\imgtemp
crosshairs red,\x1,\y1,\x2,\y2
)}
#if defined TARGET_eqred
\text{plotdrt=\choix=1?vline \x1,0,blue:plot blue, \f}
\text{mrgtop=-0.5em}
#else
\text{plotdrt=plot blue, \f}
\text{mrgtop=-1em}
#endif
\text{img=<img src="\image" alt="représentation graphique" style="float:right;margin-top:\mrgtop;">}
\text{imagecorr=draw(100,100
\imgtemp
crosshairs red,\x1,\y1,\x2,\y2
\plotdrt)}
\text{imgcorr=<img src="\imagecorr" alt="représentation graphique" style="float:right;margin-top:-0.5em;">}

}
##Pour le corrigé et affichage dernière question##
#if defined TARGET_eqred
\text{den=(\x1<0)? \x2-(\x1):\x2-\x1}
\text{num=(\y1<0)? \y2-(\y1):\y2-\y1}
\integer{c=\m*\x1}
#else
\text{x1c=\x1<0?(\x1):\x1}
\text{x2c=\x2<0?(\x2):\x2}
\text{y1c=\y1<0?(\y1):\y1}
\text{y2c=\y2<0?(\y2):\y2}
\matrix{lettrecorr=A,B
\x1c,\x2c
\y1c,\y2c}
\integer{\cp=\m*\lettre[2;\choix1]}
#endif


\statement{
#if defined TARGET_eqred
<div class=wims_question>\img Déterminer l'équation réduite de la droite \((AB)\) avec \(A(\x1; \y1)\) et \(B(\x2; \y2)\).
<br >L'équation est \embed{r1}\embed{r2,10}</div>
#endif
#if defined TARGET_eqredstep
<p>\img L'objectif de cet exercice à étapes est de déterminer l'équation de la droite \((AB)\) avec :
<br >\(A(\x1; \y1)\) et \(B(\x2; \y2)\).</p>
\if{\step=1}{La droite \((AB)\) n'est pas verticale car \(x_A  \neq x_B\). Son équation est donc de la forme \(y = m x+p\). Les valeurs de \(m\) et \(p\) sont à déterminer.
<div class=wims_question>Le coefficient directeur \(m) de \((AB)\) est égal à : \(\frac{y_B-y_A}{x_B-x_A})=\embed{r1,4}.</div>}
\if{\step=2 and \sc_reply1=1}{<font color="green">Correct</font>, \(m=\m). \((AB)\) a donc pour équation \(y = \m x+p\).
<p>Pour calculer l'ordonnée à l'origine \(p), on remplace \(x) et \(y) par les coordonnées d'un point de la droite.</p>
<div class=wims_question>Avec les coordonnées de \(\lettre[1;\choix1]), on a donc \embed{r2,4}\(=\m \times)\embed{r3,4} +\(p\).</div>}
\if{\step=2 and \sc_reply1=0}{<font color="red">Erreur</font>, \(m=\m) (pas  \reply1 ). \((AB)\) a donc pour équation \(y=\m x+p\).
<p>Pour calculer l'ordonnée à l'origine \(p\), on remplace \(x) et \(y) par les coordonnées d'un point de la droite.</p>
<div class=wims_question>Avec les coordonnées de \(\lettre[1;\choix1]), on a donc \embed{r2,4} \(=\m \times) \embed{r3,4}+\(p\).</div>}
\if{\step=3 and \sc_reply2=1}{<font color="green">Correct</font>. \((AB)\) a pour équation \(y=\m x+p\) et \(p\) est solution de : \(\lettre[3;\choix1]=\cp+p\).
<div class=wims_question>L'ordonnée à l'origine \(p\) est donc égale à \embed{r4,4}. <br>L'équation réduite de la droite \((AB)\) est \embed{r5}\embed{r6,10}. </div>}
\if{\step=3 and \sc_reply2=0}{<font color="red">Erreur</font>. \((AB)\) a pour équation \(y=\m x+p) et \(\lettre[3;\choix1]=\cp+p\).
<div class=wims_question>L'ordonnée à l'origine \(p\) est donc égale à \embed{r4,4}. <br>L'équation réduite de la droite \((AB)\) est \embed{r5}\embed{r6,10}.</div>}

#endif
}
#if defined TARGET_eqred
\answer{}{\pos;x=,y=}{type=menu}
\answer{}{\f}{type=function}
#else
\answer{}{\m}{type=numeric}{option=nonstop}
\answer{}{\lettre[3;\choix1]}{type=numeric}{option=nonstop}
\answer{}{\lettre[2;\choix1]}{type=numeric}{option=nonstop}
\answer{}{\p}{type=numeric}
\answer{}{2;x=,y=}{type=menu}
\answer{}{\f}{type=function}
#endif
\solution{
\imgcorr
#if defined TARGET_eqred
\if{\choix=1}{\(A) et \(B) ont la même abscisse \(\x1) donc la droite \((AB)) est parallèle à l'axe des ordonnées et son équation est \(x=\x1).}
{<p>\(A) et \(B) n'ont pas la même abscisse donc la droite \((AB)) n'est pas parallèle à l'axe des ordonnées et son équation réduite est de la forme \(y=mx+p).</p>
<p> Il reste à déterminer les valeurs de \(m) et \(p)
<ul><li>Le coefficient directeur \(m) est égal à \(\frac{y_B-y_A}{x_B-x_1}=\frac{\num}{\den}=\m).</li>
<li class="wims_nopuce">L'équation réduite de \((AB)) est donc de la forme \(y=\m x+p).</li>
<li>Pour déterminer la valeur de \(p), on remplace \(x) et \(y) dans l'équation par les coordonnées d'un point de la droite.</li>
<li class="wims_nopuce">En prenant par exemple \(A(\x1; \y1)), on obtient \if{\x1<0}{\(\y1=\m \times (\x1)+p)}{\(\y1=\m \times \x1+p)} c'est à dire \(\y1=\c+p).</li>
<li class="wims_nopuce">On en déduit que \if{\c<0}{\(p=\y1-(\c)=\p)}{\(p=\y1-\c=\p)} </li>
</ul>
<p> Conclusion : l'équation réduite de la droite \((AB)) est \if{\p<0}{\(y=\m x\p)}{\(y=\m x+\p)}. </p>
}
#else
<p>Equation de la droite \((AB)) avec \(A(\x1; \y1)) et \(B(\x2; \y2)).</p>
<ul>
<li>La droite \((AB)) n'est pas verticale car \(x_A  \ne x_B). Son équation est donc de la forme \(y = m x+p). Il faut calculer les valeurs de \(m) et \(p).</li>
<li>Le coefficient directeur \(m) de \((AB)) est égal à : \(\frac{y_B-y_A}{x_B-x_A}=\m).</li>
<li>Pour calculer l'ordonnée à l'origine \(p), on remplace \(x) et \(y) par les coordonnées d'un point de la droite.</li>
<li>Avec les coordonnées de \(\lettrecorr[1;\choix1]), on a donc \(\lettrecorr[3;\choix1]=\m \times \lettrecorr[2;\choix1] + p).</li>
<li>En résolvant l'équation précédente, on obtient : \(p = \p)</li>
</ul>
 <p>\((AB)) a pour équation \(y=\m x+\p) </p>
#endif
}
:: fini MB
