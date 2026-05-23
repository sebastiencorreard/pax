target=eqdroite eqdroite1
\language{fr}
\author{Fabien,Sommier} d'après un exercice de B. Perrin-Riou
\email{math.sommier@gmail.com}
\format{html }
\precision{10000 }
\range{-5..5 }
\computeanswer{ no }
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{grille =
xrange -5.2, 5.2
yrange -5.2, 5.2
parallel -5.2,-5,5.2,-5,0,1,11, grey
parallel -5,-5.2,-5,5.2,1,0,11, grey
segment 1,-0.2,1,0.2, black
segment -0.2,1,0.2,1, black
text black, 0.9,-0.25,medium, 1
text black, -0.5,1.25,medium, 1
text black, -0.5,-0.25,medium, "0"
point 0,0, black
hline 0,0, black
vline 0,0, black
arrow -5.2,0,5.2,0, 10, black
arrow 0,-5.2,0,5.2, 10, black
}
#if defined TARGET_eqdroite
 \title{Déterminer graphiquement une équation de droite (niveau 1)}
 \integer{ a = randint( -4..4 ) }
\integer{ b = randint( -4..4 ) }
\integer{ a = \a = 0 and \b = 0? randint(1..4)*random(1,-1) }
#endif
#if defined TARGET_eqdroite1
 \title{Déterminer graphiquement une équation de droite (niveau 2)}
  \rational{ a = random(-1,1)*randint( 1/2,1/3,1/4,3/2,2/3,3/4,4/3) }
\integer{ b = randint( -4..4 ) }
#endif
\function{ eq = simplify(\a*x + (\b)) }

\statement{Compléter l'équation réduite de la droite tracée :
<div class="wimscenter">
\draw{200,200 }{
\grille
plot blue, \eq }
<br>
<label for ="reply1">\(y = ) </label>\embed{ reply 1, 15 }
</div>
}
\answer{ \(y = ) }{ \eq,x }{ type = function }{option=noanalyzeprint}
\text{ test=simplify(\reply1-(\eq)) }
\text{solution=pari(\eq)}
\feedback{ \test<>0 }{
La droite tracée a pour équation y=\solution<br>

Voici en rouge la droite correspondant à l'équation que vous avez donnée :
<div class="wimscenter">
\draw{ 200,200 }{
\grille
plot red, \reply1
plot blue,\eq
 } </div> }
