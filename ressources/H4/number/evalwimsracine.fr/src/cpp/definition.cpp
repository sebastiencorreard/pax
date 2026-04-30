target= definition1,definition3,definition4


\integer{a=randint(12..24)}
#if #TARGET(definition1)
 \title{Définition 1}
 \text{enonce=(sqrt(\a))^2}
#endif
#if #TARGET(definition3)
 \title{Définition 3}
 \text{enonce=sqrt(\a^2)}
#endif
#if #TARGET(definition4)
 \title{Définition 4}
 \text{enonce=sqrt((-\a)^2)}
#endif

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\text{size=8}

\integer{rep=\enonce}
\text{enonce=texmath(\enonce)}

\statement{Calculer l'expression suivante :
<div class="center"> \(\enonce = )\embed{r1,\size} </div>}

\answer{\(\enonce)}{\rep}{type=numexp}
