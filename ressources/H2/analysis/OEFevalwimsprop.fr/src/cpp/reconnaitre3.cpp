target=reconnaitre3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{rep=randrow(propo1.GIF,Oui
propo2.GIF,\name_yesno[2]
propo3.GIF,\name_yesno[1])}

\text{prenom=slib(lang/fname boy,fr)}

\statement{
\prenom \name_enonce
<div class="wimscenter"><img src="\imagedir/\rep[1]" alt=""></div>
\name_question?}

\choice{Réponse}{\rep[2]}{\name_yesno[1],\name_yesno[2]}
