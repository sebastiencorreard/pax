target=Moyenne
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
\text{nom=slib(lang/fname \lang boy)}
\integer{mm=randint(50..150)}
\integer{dev=20}
\integer{min=\mm-\dev}
\integer{max=\mm+\dev}
\real{p=randint(\min..\max)/10}
\real{s=randint(\min..\max)/10}
\real{t=randint(\min..\max)/10}
\real{r=rint(10*(\p+\s+\t)/3)/10}
\text{enonce=wims(replace internal XXXX by \p in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \s in \enonce)}
\text{enonce=wims(replace internal ZZZZ by \t in \enonce)}
\text{enonce=wims(replace internal NNNN by \nom in \enonce)}
\statement{\nom \enonce?}

\answer{\name_answer}{\r}{type=default}
