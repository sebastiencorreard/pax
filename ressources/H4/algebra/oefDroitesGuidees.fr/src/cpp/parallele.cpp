target=parallele

\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\rational{m=random(-1,1)*randint(0..8)/random(2,3)}
\integer{p=random(-10..10)}
\integer{x2=random(-1,1)*random(0..6)}
\integer{y2=random(-1,1)*random(0..6)}
\rational{p2=\y2-\m*\x2}
\function{eq=maxima(expand(simplify(\m*x+\p)))}
\function{eqs=maxima(expand(simplify(\m*x+\p2)))}
\text{eqa=texmath(\eq)}
\text{eqsa=texmath(\eqs)}
\integer{nat=1}
\integer{pen=1}
\integer{i=random(1,2)}
\text{coefdir=item(\i,m,a)}
\text{ordori=item(\i,p,b)}

\statement{
<div style="background-color:#FFFF66">
<p>Dans un repère \((O,\vec{i},\vec{j})\) du plan, on considère la droite
\(D\) d'équation réduite \(y = \eqa\).
<br>
On se propose de déterminer l'équation réduite de la droite \(\Delta\)
parallèle à la droite \(D\) et passant par le point
\(A\left( \x2 ; \y2 \right) \).
</p>
<ul><li>
On cherche l'équation de \(\Delta\) sous la forme : \( y = \coefdir x + \ordori\)
parce qu'il s'agit d'une droite \embed{reply1, 10}.
</li><li>
<label for="reply2">La pente de la droite \(D\) vaut</label> \embed{reply2, 5}.
</li><li>
Comme les droites \(D\) et \(\Delta\) sont parallèles, alors elles
ont des coefficients directeurs \embed{reply3, 10}. Donc
<label for="reply4">\(\coefdir\) vaut</label>
\embed{reply4, 5}.
</li><li>
On écrit que \(A\) appartient à \(\Delta\) pour calculer la valeur de
\(\ordori\). On obtient alors :
<div class="wimscenter"><label for="reply5">\(\ordori\) = </label>
\embed{reply5, 5}</div></li>
</ul>
</div>
}
\answer{\name_answer[1] \(D\)}{\nat;\natures}{type=menu}{option=shuffle}
\answer{\name_answer[2] \(D\)}{\m}{type=default}
\answer{\name_answer[4]}{\pen;\pentes}{type=menu}{option=shuffle}
\answer{\name_answer[2]\(D'\)}{\m}{type=default}
\answer{\name_answer[3] \(b\) }{\p2}{type=default}

\solution{L'équation réduite de la droite \(\Delta\) est \(y = \eqs\).
Les droites \(\Delta\) et \(D\) ont le même coefficient directeur, mais des ordonnées à l'origine
différentes. Voir dessin (\(\Delta\) est représentée en vert, et \(D\) en bleu).
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
plot green,\eqs
text green,\x2+1,\y2,large,"A"
text blue,1,\p,large,"D"
linewidth 6
point \x2,\y2,green}
</div>
}
