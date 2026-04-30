target=mkequation

#include "author.inc"
#include "lang_titles.inc"

\text{d=randitem(D,d,m,p)}
#include "lang.inc"

\text{l=wims(values v for v=-10 to 10)}
\text{l=shuffle(\l)}
\text{info=shuffle(le coefficient directeur est \l[1],l'ordonnée à l'origine est \l[2])}

\statement{
Soit \((\d)) une droite dont \info[1] et \info[2]. Quelle est son équation ?}

\answer{\(y\)}{\l[1]*x+\l[2]}{type=algexp}
