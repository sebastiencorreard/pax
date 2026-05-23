target=mediane3
\title{Réciproque de la propriété de la médiane}
\language{fr}
\format{html}
\author{P, Olivetti}
\computeranswer{no}
\precision{1000}

\text{lettres=shuffle(A,B,C,D,E,F,G)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}
\text{C=\lettres[3]}
\text{D=\lettres[4]}

\integer{x1=random(60..120)}
\integer{y1=random(100..150)}
\integer{x2= \x1+random(70..80)}
\integer{y2= \y1-random(80..100)}
\integer{x3=random(20..50)}
\integer{u=random(65..70)}
\integer{v=randitem(1,2,4,5)}


\text{dessin=draw(200,200
triangle \x1,\y1,\x2,\y2,\x3,\x3+\u, blue
text black,\x1+5,\y1-6,medium,\A
text black,\x2+2,\y2+2,medium,\B
text black,\x3+2,\x3+\u+2,medium,\C
point (\x1+\x2)/2,(\y1+\y2)/2,black
text black, (\x1+\x2)/2 +5,(\y1+\y2)/2 -4,medium,\D
segment \x3,\x3+\u,(\x1+\x2)/2,(\y1+\y2)/2,blue
)}

\text{listechoix=Propriété de la médiane,Réciproque
 de la propriété de la médiane, Contraposée de la propriété}
\integer{x=random(1..20)}
\text{list=Oui &#44; le triangle est rectangle,Non &#44; le triangle n'est pas rectangle}

\if{\x/\v=\x/2}{
 \text{X=1}
}{
 \text{X=2}
}
\if{\x/\v=\x/2}{
 \text{T=2}
}{
 \text{T=3}
}

\real{vv=simplify(\x/\v)}

\statement{
Voici ci-dessous le triangle \(\A\B\C).
<div class="wimscenter"><img src="\dessin" alt=""> </div>
On sait que [\C\D] est la médiane issue du sommet \C.
On a les données suivantes: <div class="wimscenter">
  \(\A\B = \x) cm et \(\C\D = \vv) cm
</div>
<ol>
    <li> Le triangle \(\A\B\C) est-il rectangle en \C ? \embed{r1}</li>
    <li> Quelle propriété utilisez-vous pour démontrer cela ? \embed{r2}</li>
</ol>
}

\answer{Question 1}{\X;\list}{type=radio}{weight=9}
\answer{Question 2}{\T;\listechoix}{type=checkbox}{weight=1}

\solution{<ol>
<li>
 Pour vérifier si le triangle est rectangle, on calcule la fraction \(\frac{\A\B}{2})
 et on vérifie si c'est égale à la longueur de la médiane \(\C\D).
</li><li>
\if{\x/\v=\x/2}{
 Si la médiane issue du point \(\C) mesure la moitié du côté relatif, alors on utilise
la propriété réciproque de la médiane.
}{
 On a montré que la médiane \(\C\D) ne mesure pas la moitié du côté relatif, on utilise donc la
contraposée de la propriété de la médiane.
En effet, si l'on souhaite utiliser la réciproque, il faut avoir l'égalité
\(\frac{\A\B}{2}=\C\D) ce qui n'est pas le cas. Si l'on souhaite utiliser la propriété, on doit
savoir que le triangle est rectangle ce que l'on ne sait pas.}
 </li>
</ul>
}

\hint{La médiane issue du sommet \(\C) est la demi-droite passant par \(\C)
et qui coupe le côté opposé [\A\B] en son milieu.}
