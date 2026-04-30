target=appartenance

\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{de=random(0,1)}

\rational{m=random(-1,1)*randint(0..8)/random(2,3)}
\integer{p0=random(0..10)}
\integer{p=random(-1,1)*\p0}
\integer{xA=random(-1,1)*random(0..8)}
\rational{yA=\de==1?\m*\xA+\p:random(-1,1)*randint(0..8)/random(1,2,3,5)}

\function{eq=maxima(expand(simplify(\m*x+\p)))}
\text{tXA=\xA<0?(\xA):\xA}
\text{tp=\p<0? - \p0:+ \p0}
\text{tp=\p0==0? }
\text{eqtex=texmath(\eq)}
\rational{\eqptA=\m*\xA+\p}
\integer{rep3=\eqptA==\yA?1:2}

\statement{
<div style="background-color:#FFFF66">
Dans un repère \((O,\vec{i},\vec{j})\) du plan, on considère la droite \(D\)
d'équation \(y = \eqtex\).
<br>On se propose de déterminer si le point \(A\left( \xA ; \yA \right) \)
appartient à \(D\) ou non.
<ul><li>
Pour \(x = x_A\), dans l'équation de \(D\) on obtient :
<label for="reply1">\(y\) =</label> \embed{reply1, 5}.
</li><li>
L'ordonnée du point \(A\) est : <label for="reply2">\(y_A\) = </label>
\embed{reply2, 5}.
</li><li>
Donc les coordonnées du point \(A\) \embed{reply3,10}
l'équation de \(D\). <br> On conclut que le point \(A\)
\embed{reply4,10} à \(D\).
</li></ul>
</div>
}

\answer{\name_answer[1] m x_A+p }{\eqptA}{type=default}{option=nonstop}
\answer{\name_answer[2] A}{\yA}{type=default}{option=nonstop}
\answer{}{\rep3;\name_choix[1;]}{type=menu}{option=shuffle}
\answer{}{\rep3;\name_choix[2;]}{type=menu}{option=shuffle}

\solution{
Les coordonnées du point \(A\) \if{\rep3==1}{vérifient}{ne vérifient pas}
l'équation \(y = \eq\) de la droite, puisque \(y_A\)
\if{\rep3==1}{=}{\(\neq\)} \(\m\times \tXA \tp\).
 <div class="wimscenter">
\draw{400,400}{xrange -20,20
yrange -20,20
parallel -20,-20,-20,20,1,0,40,grey
parallel -20,-20,20,-20,0,1,40,grey
hline 0,0,black
vline 0,0,black
linewidth 2
arrow 0,0,0,1,5,black
arrow 0,0,1,0,5,black
plot blue,\eq
text green,\xA+1,\yA,large,"A"
text blue,1,\p,large,"D"
linewidth 6
point \xA,\yA,green}
</div>
}
