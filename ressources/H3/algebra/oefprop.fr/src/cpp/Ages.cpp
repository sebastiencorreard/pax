target=Ages

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{noms=Maurice, Christophe, Laure, Carine, Michel, Céline, Joseph,
Nicolas, Renaud, Lucas, Marie, Claire, Suzanne, Henri}
\text{noms=shuffle(\noms)}
\text{nom1=item(1,\noms)}
\text{nom2=item(2,\noms)}
\matrix{donnee=
\name_donne[1], 3, 1
\name_donne[2], 4, 1
\name_donne[3], 5, 1
\name_donne[4], 3, 2
\name_donne[5], 4, 3}
\text{ligne=randomrow(\donnee)}
\text{fois=item(1,\ligne)}
\integer{m1=item(2,\ligne)}
\integer{m2=item(3,\ligne)}
\integer{r=random(5..30)}
\integer{d=\r*\m1}
\integer{R=\r*\m2}
\text{enonce=\name_enonce}
\text{enonce=wims(replace internal XXXX by \nom1 in \enonce)}
\text{enonce=wims(replace internal YYYY by \nom2 in \enonce)}
\text{enonce=wims(replace internal ZZZZ by \d in \enonce)}
\text{enonce=wims(replace internal TTTT by \fois in \enonce)}

\statement{\enonce?}

\answer{\name_answer \nom1}{\R}{type=default}
