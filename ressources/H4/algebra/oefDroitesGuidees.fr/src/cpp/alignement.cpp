target=alignement

\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{xA=random(-1,1)*random(0..8)}
\integer{yA=random(-1,1)*random(0..8)}
\integer{xB=random(-1,1)*random(0..8)}
\integer{xB=\xB==\xA?\xA+random(-3,-4,3,4,-5,5)}
\integer{yB=random(-1,1)*random(0..8)}
\rational{m=(\yB-\yA)/(\xB-\xA)}
\rational{p=\yA-\m*\xA}

\integer{xC=random(-1,1)*random(10..50)/random(1..5)}
\integer{de=random(0,1)}
\rational{yC=\de==1?\m*\xC+\p:random(-1,1)*randint(10..50)/random(1,2,3,5)}

\function{eq=maxima(expand(simplify(\m*x+\p)))}
\text{eqtex=texmath(\eq)}
\rational{\rep3=\m*\xC+\p}
\integer{rep4=\rep3==\yC?1:2}

\statement{
<div style="background-color:#FFFF66">
Dans un repère \((O,\vec{i},\vec{j})\) du plan, on considère les trois points
suivants :
<div class="wimscenter">\(A\left( \xA ; \yA \right) \) ; \(B\left( \xB ; \yB \right) \) ; \(C\left( \xC ; \yC \right) \). </div>
<b>On se propose de déterminer si ces trois points sont
alignés ou non.</b>
Dans ce but, on examine si le point \(C\) appartient à la droite \((A B)\).
\if{\step=1}{
<h2 class="small">\name_quest 1.</h2>
La droite \((A B)\) \embed{reply1, 10} parallèle à l'axe des ordonnées.
<br>
Elle a donc une équation de la forme \(y = m x+p\) avec
 <label for="reply2">\(m\) = </label>\embed{reply2, 10} et
 <label for="reply3">\(p\) =</label> \embed{reply3, 10}.
}
\if{\step=2}{
<h2 class="small">\name_quest 1.</h2>
\if{\reply2=\m and \reply3=\p}{<span class="oef_indgood">Bonne réponse !</span>}
  {< <span class="oef_indbad">Mauvaise réponse...</span>}
La droite \((A B)\) admet comme équation : \(y = \eqtex\).
<h2 class="small">\name_quest 2.</h2>
Pour \(x = \xC\), on a : <label for="reply4">\(\eqtex\) =</label> \embed{reply4, 5}.
<div>L'ordonnée du point \(C\) est :
<label for="reply5">\(y_C\) =</label> \embed{reply5, 5}.
</div><div>
Donc les coordonnées du point \(C\) \embed{reply6}
l'équation de \((A B)\).
</div><div>On conclut que les points \(A\), \(B\) et \(C\)
\embed{reply7}.
</div>
}
</div>
}

\steps{reply1,reply2,reply3
reply4,reply5,reply6,reply7
}
\answer{}{1;\name_choix}{type=menu}{option=shuffle}
\answer{\name_answer[1] m}{\m}{type=default}{option=nonstop}
\answer{\name_answer[2] p}{\p}{type=default}{option=nonstop}
\answer{\name_answer[3] m x_C+p }{\rep3}{type=default}{option=nonstop}
\answer{\name_answer[4] C}{\yC}{type=default}{option=nonstop}
\answer{\name_answer[5] C}{\rep4;\name_choix2}{type=menu}{option=shuffle}{option=nonstop}
\answer{C}{\rep4;\name_choix3}{type=menu}{option=shuffle}{option=nonstop}
