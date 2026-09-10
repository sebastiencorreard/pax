target=pteinverse1 pteinverse2

\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\precision{1000}
\computeanswer{no}

#if #TARGET(pteinverse1)
\title{Propriété de la fonction inverse 1}
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(-9..9)}
\integer{c=randint(-9..9)}
\text{f=texmath(maxima(1/(\a*x+\b)+\c))}
\integer{rep=\a>0?1:2}
\statement{
Dans quels secteurs se situe l'hyperbole, courbe représentative
de la fonction \(f) définie par
\(f(x)=\f).
<div class="wimscenter">
\embed{reply1}</div>
}
\answer{orientation}{\rep;Bas gauche et haut droit ,Haut gauche et bas droit}{type=radio}
#endif
#if #TARGET(pteinverse2)
\title{Propriété de la fonction inverse 2}
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(-9..9)}
\integer{c=randint(-9..9)}
\text{f=texmath(maxima(1/(\a*x+\b)+\c))}
\rational{xs=-\b/\a}
\integer{ys=\c}
\statement{
Quelles sont les coordonnées du centre de symétrie de l'hyperbole,
courbe représentative de la fonction \(f) définie par
\(f(x)=\f).
<div class="wimscenter">
<label for="reply1">Abscisse du centre:</label>\embed{reply1,4}<br>
<label for="reply2">Ordonnée du centre:</label>\embed{reply2,4}
</div>
}
\answer{abscisse}{\xs}{type=numeric}
\answer{ordonnée}{\ys}{type=numeric}
#endif
