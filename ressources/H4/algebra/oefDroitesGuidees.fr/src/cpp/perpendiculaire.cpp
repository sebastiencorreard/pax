target=perpendiculaire
\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\rational{m=random(-1,1)*randint(1..8)/random(2,3)}
\rational{mperp=-1/(\m)}
\integer{p=random(-10..10)}
\integer{xA=random(-1,1)*random(2..10)}
\integer{yA=random(-1,1)*random(2..10)}
\rational{p2=\yA-\mperp*\xA}
\function{eq=maxima(expand(simplify(\m*x+\p)))}
\function{eqperp=maxima(expand(simplify(\mperp*x+\p2)))}
\text{eqtex=texmath(\eq)}
\text{eqperptex=texmath(\eqperp)}

\integer{nat=1}

\statement{
<div style="background-color:#FFFF66">
Dans un repère orthonormal \((O,\vec{i},\vec{j})\) du plan,
on considère la droite \(D\) d'équation réduite \(y = \eqtex\).
<p>On se propose de déterminer l'équation réduite de la droite \(\Delta\)
perpendiculaire à la droite \(D\) et passant par le point
\(A\left( \xA ; \yA \right) \).
</p>
<ul><li>
On cherche l'équation de \(\Delta\) sous la forme : \( y = m' x + p'\)
parce qu'il s'agit nécessairement d'une droite \embed{reply1, 10}.
</li><li>
La \special{tooltip pente,,\name_tooltip}
 de la droite \(D\) vaut <label for="reply2">\(m\) = </label>\embed{reply2, 5}.
</li><li>
Les droites \(D\) et \(\Delta\) étant perpendiculaires, leurs pentes respectives \(m\) et \(m'\)
vérifient \(m\times m'= -1\) (<i>résultat admis</i>).
<br> Alors on obtient : <label for="reply3">\(m'\) =</label> \embed{reply3, 5}.
</li><li>
On écrit que \(A\) appartient à \(\Delta\) pour calculer la valeur
de l'ordonnée à l'origine
\(p'\). <br> On obtient alors : <label for="reply4">\(p'\) =</label> \embed{reply4, 5}</li>
</ul>
</div>
}

\answer{\name_answer[1] \(D\)}{\nat;\natures}{type=menu}{option=shuffle}
\answer{\name_answer[2] \(D\)}{\m}{type=default}
\answer{\name_answer[2] \(D'\)}{\mperp}{type=default}
\answer{\name_answer[3] \(p'\)}{\p2}{type=default}

\feedback{0==0}{
<h2 class="small">\name_solution.</h2>
De l'égalité \(m\times m'=-1\) on tire : \(m' = -\frac{1}{m} = \mperp\).
<br/>
Le point \(A\) doit vérifier l'équation \(y = m' x + p'\) avec \(m' = \mperp\), donc
on obtient : \(p' = y_A - m'x_A = \p2\).<br>
D'où l'équation réduite de la droite \(\Delta\) : \(y = \eqperptex\).
<br>
 \(\Delta\) est représentée en vert ci-dessous.
<div class="wimscenter">
\draw{400,400}{xrange -15,15
yrange -15,15
parallel -15,-15,-15,15,1,0,30,grey
parallel -15,-15,15,-15,0,1,30,grey
hline 0,0,black
vline 0,0,black
linewidth 2
arrow 0,0,0,1,5,black
arrow 0,0,1,0,5,black
plot blue,\eq
plot green,\eqperp
text green,\xA+1,\yA,large,"A"
text blue,1,\p,large,"D"
linewidth 6
point \xA,\yA,green}
</div>
}
