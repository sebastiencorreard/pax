target= valeur1,valeur2,valeur3,valeur4,valeur5


#if #TARGET(valeur1)
 \title{Valeur 1}
 \integer{a=randint(2..10)}
 \integer{a2=\a^2}
 \text{enonce=\sqrt{\a2}}
 \text{rep=\a}
#endif
#if #TARGET(valeur2)
 \title{Valeur 2}
 \integer{a=randint(11..19)}
 \integer{a2=\a^2}
 \text{enonce=\sqrt{\a2}}
 \text{rep=\a}
#endif
#if #TARGET(valeur3)
 \title{Valeur 3}
 \integer{a=randint(2..9)}
 \real{a2=\a^2/100}
 \text{enonce=\sqrt{\a2}}
 \real{rep=\a/10}
#endif
#if #TARGET(valeur4)
 \title{Valeur 4}
 \integer{a=randint(11..19)}
 \real{a2=\a^2/100}
 \text{enonce=\sqrt{\a2}}
 \real{rep=\a/10}
#endif
#if #TARGET(valeur5)
 \title{Valeur 5}
 \text{a=wims(values v for v=2 to 19)}
 \text{a=shuffle(\a)}
 \real{b=\a[1]^2}
 \real{c=\a[2]^2}
 \text{enonce=\sqrt{\frac{\b}{\c}}}
 \text{rep=simplify(\a[1]/\a[2])}
#endif

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\text{size=8}

\statement{
Calculer l'expression suivante sans utiliser la calculette.
<div class="center"> \(\enonce = )\embed{r1,\size} </div>}

\answer{\(\enonce)}{\rep}{type=numexp}
