target=ptecarre1 ptecarre2 ptecarre3

\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}
\computeanswer{no}

#if #TARGET(ptecarre1)
\title{Propriété de la fonction carré 1}
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(-9..9)}
\integer{c=randint(-9..9)}
\text{f=texmath(maxima(\a*x^2+\b*x+\c))}
\integer{rep=\a>0?1:2}
\statement{
Quelle est l'orientation de la parabole, courbe représentative de la fonction \(f) définie par :
<div class="wimscenter">\(f(x)=\f)<br>
\embed{reply1}</div>
}
\answer{orientation}{\rep;Vers le haut,Vers le bas}{type=radio}
#endif
#if #TARGET(ptecarre2)
\title{Propriété de la fonction carré 2}
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(-9..9)}
\integer{c=randint(-9..9)}
\text{f=\c=0?texmath((maxima(\a*x+\b))^2):texmath((maxima(\a*x+\b))^2+\c)}
\rational{rep=-\b/\a}
\statement{
Quelle est l'équation de l'axe de symétrie de la parabole, courbe représentative de la fonction \(f) définie par :
<div class="wimscenter">\(f(x)=\f)<br>
<label for="reply1">\(x=)</label>\embed{reply1}</div>
}
\answer{axe}{\rep}{type=numeric}
#endif
#if #TARGET(ptecarre3)
\title{Propriété de la fonction carré 3}
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(-9..9)}
\integer{c=randint(-9..9)}
\text{f=\c=0?texmath((maxima(\a*x+\b))^2):texmath((maxima(\a*x+\b))^2+\c)}
\rational{xs=-\b/\a}
\integer{ys=\c}
\statement{
Quelles sont les coordonnées du sommet de la parabole, courbe représentative de la fonction \(f) définie par :
<div class="wimscenter">\(f(x)=\f)<br>
<label for="reply1">abscisse du sommet:</label>\embed{reply1,4}<br>
<label for="reply2">ordonnée du sommet:</label>\embed{reply2,4}</div>
}
\answer{abscisse}{\xs}{type=numeric}
\answer{ordonnée}{\ys}{type=numeric}
#endif
