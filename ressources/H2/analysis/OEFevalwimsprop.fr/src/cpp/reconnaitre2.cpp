target=reconnaitre2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"


\text{image=draw(375,150
square 25,75,25,black
square 25,100,25,black
square 50,100,25,black
square 125,50,25,black
square 125,75,25,black
square 125,100,25,black
square 150,75,25,black
square 150,100,25,black
square 175,100,25,black
square 250,25,25,black
square 250,50,25,black
square 250,75,25,black
square 250,100,25,black
square 275,50,25,black
square 275,75,25,black
square 275,100,25,black
square 300,75,25,black
square 300,100,25,black
square 325,100,25,black)}

\text{prenom=slib(lang/fname girl,fr)}
\text{mat=randrow(\name_mat[1],\name_mat[2]
\name_mat[3], \name_mat[4])}
\statement{
\prenom \name_enonce
<div class="wimscenter">
<img src="\image" alt="">
</div>
\prenom \name_enonce2[1] \mat[1] \name_enonce2[2],
\name_enonce2[3] \mat[2] \name_enonce2[4]<p>
\prenom \name_question?</p>}

\choice{Réponse}{\name_yesno[2]}{\name_yesno[1]}
