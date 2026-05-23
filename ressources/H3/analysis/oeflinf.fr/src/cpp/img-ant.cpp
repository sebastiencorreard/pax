target=image,antecedant

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}

#if #TARGET(image)
 \title{Image par une fonction}
 \text{nom=randitem(f,g,h)}
 \integer{nb1=random(1,-1)*random(2..35)}
 \integer{nb2=random(1,-1)*random(2..10)}
 \integer{nb3=\nb1*\nb2}
 \text{quest=Quelle est l'image du nombre \(\nb2)}
 \text{sol=\nb3}
 \integer{n=1}
#endif
#if #TARGET(antecedant)
 \title{Antécédent par une fonction}
 \text{nom=randitem(f,g,h)}
 \integer{nb1=random(1,-1)*random(2..35)}
 \integer{nb2=random(1,-1)*random(2..10)}
 \integer{nb3=\nb1*\nb2}
 \text{quest=Quel nombre a pour image \(\nb3)}
 \text{sol=\nb2}
 \integer{n=2}
#endif

\statement{Soit \(\nom) la fonction linéaire de coefficient \(\nb1).
<p>\quest par la fonction \(\nom) ? </p>
<b>Votre réponse</b> : \embed{r1}}

\answer{réponse:}{\sol}{type=numexp}
