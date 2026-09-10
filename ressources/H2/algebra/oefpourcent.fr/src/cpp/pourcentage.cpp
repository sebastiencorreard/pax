target=pourcentage
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\integer{n=randint(10..90)}
\text{u=randint(1..5)}
\text{longueur=item(\u,\name_longueur)}
\text{l=item(\u,l,v,h,m,p)}
\text{choix=random(1,-1)}
\text{augdim=\name_augdim}
\text{augmente=\choix=1 ? item(1,\augdim):item(2,\augdim)}

\real{rep=(100+(\choix)*\n)/100}

\statement{
\name_question[1] \augmente \longueur \(\l) \name_question[2] \n %.
\name_question[3] \(\l) ? }
\answer{\name_answer}{\rep}{type=numeric}
