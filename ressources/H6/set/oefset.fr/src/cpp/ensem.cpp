target=ensem
#define GGG A3 -
\title{GGG Théorie des ensembles 1}
\language{fr}
\range{-5..1000}
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "common.inc"
#include "lang_ensem_fr.inc"
\if{\lang=it}{
#include "lang_ensem_it.inc"
}
\if{\lang=es}{
#include "lang_ensem_es.inc"
}
#include "css.inc"

\integer{a=random(1,2)}
\integer{b=random(1,2)}
\integer{c=random(1,2)}
\integer{d=random(1,2)}

\text{uni= \cup }
\text{inter= \cap }
\text{CA=A^c }
\text{CB=B^c }
\text{CC=C^c }
\text{A=A }
\text{B=B }
\text{C=C }
\text{choix3=item(\c,\etou)}

\text{choix1=item(\a,\app,\napp)}
\text{choix4=item(\d,\app,\napp)}

\text{liste1=\a=1 ? \eta,\oua:\nia,\etn}

\text{choix2= item(\b,\liste1)}

\text{solA=\a=2?\CA:\A}
\text{solB=\a=2?\CB:\B}
\text{solC=\d=2?\CC:\C}

\text{sol2=\b=2 and \a=1?\uni:\inter}
\text{sol3=\c=1?\inter:\uni}
\text{Sol=\sol3 issametext \sol2 ? \solA \sol2 \solB:(\solA \sol2 \solB)}

\text{solution=\(\Sol \sol3 \solC)}

\text{rep1=\A \uni \B \uni \C}
\text{rep2=(\A \inter \B) \uni \C}
\text{rep3=(\A \uni \B) \inter \C}
\text{rep4=\A \inter \B \inter \C}
\text{rep5=\CA \uni \CB \uni \C}
\text{rep6=( \CA \inter \CB) \uni \C}
\text{rep7=( \CA \uni \CB) \inter \C}
\text{rep8=\CA \inter \CB \inter \C}
\text{rep9=\A \uni \B \uni \CC}
\text{rep10=(\A \inter \B) \uni \CC}
\text{rep11=(\A \uni \B) \inter \CC}
\text{rep12=\A \inter \B \inter \CC}
\text{rep13=\CA \uni \CB \uni \CC}
\text{rep14=(\CA \inter \CB) \uni \CC}
\text{rep15=(\CA \uni \CB) \inter \CC}
\text{rep16=\CA \inter \CB \inter \CC}

\text{liste=\(\rep1),\(\rep2),\(\rep3),\(\rep4),\(\rep5),\(\rep6),\(\rep7),
\(\rep8),\(\rep9),\(\rep10),\(\rep11),\(\rep12),\(\rep13),\(\rep14),
\(\rep15),\(\rep16)}

\integer{ra=1+2*random(1..4)}
\integer{ra1=3^\ra%17}
\integer{ra2=3*\ra1%17}
\integer{ra3=3*\ra2%17}
\integer{ra4=3*\ra3%17}
\integer{ra5=3*\ra4%17}
\text{rra1=item(\ra1,\liste)}
\text{rra2=item(\ra2,\liste)}
\text{rra3=item(\ra3,\liste)}
\text{rra4=item(\ra4,\liste)}
\text{rra5=item(\ra5,\liste)}

\text{choixrep=shuffle(\rra1,\rra2,\rra3)}
\text{NB=wims(record 1 of notations.\lang)}
\statement{\instruction

<div class="center color1">
\phrase[1;] \phrase[2;] \choix1 \(A) \choix2 \(B) \choix3
\phrase[2;] \choix4 \(C).
</div>
}
\help{\NB}
\choice{\(F) \phrase[3;]}{\solution}{\choixrep}
