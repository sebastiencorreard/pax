target=OeufsdePques
\language{fr}
\range{-5..5}
\author{XIAO Dingyu}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{noms=Patrick, Fabien, Fabrice, Carole, Elodie, Jean-Pierre, Paul, Gérard, Louis, Catherine, Julie, George, Dominique, Charles, Sylvie}
\text{noms=shuffle(\noms)}
\text{nom1=item(1,\noms)}
\text{nom2=item(2,\noms)}
\text{nom3=item(3,\noms)}
\matrix{donnee=
\name_donne[1;], 1, 4
\name_donne[2;], 1, 6
\name_donne[3;], 2, 4
\name_donne[4;], 1, 3
\name_donne[5;], 5, 12}
\text{ligne=randomrow(\donnee)}
\text{q1=item(1,\ligne)}
\text{q2=item(2,\ligne)}
\integer{num=item(3,\ligne)}
\integer{den=item(4,\ligne)}
\integer{part=random(2..10)}
\integer{q3=\num*\part}
\integer{reponse=\part*\den}
\text{enonce=\name_enonce}
\text{enonce=wims(replace internal XXXX by \nom1 in \enonce)}
\text{enonce=wims(replace internal YYYY by \q1 in \enonce)}
\text{enonce=wims(replace internal ZZZZ by \nom2 in \enonce)}
\text{enonce=wims(replace internal TTTT by \q2 in \enonce)}
\text{enonce=wims(replace internal NNNN by \nom3 in \enonce)}
\text{enonce=wims(replace internal QQQQ by \q3 in \enonce)}

\statement{\enonce \name_question?}

\answer{\name_answer}{\reponse}{type=default}
