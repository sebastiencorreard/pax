target=Moyennesetcoef
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}

\text{nom=slib(lang/fname \lang)}
\integer{m=random(2..18)}
\integer{f=random(3..17)}
\integer{p=random(3..17)}
\integer{cm=random(3, 4)}
\integer{cf=random(3, 4)}
\integer{cp=random(2, 3)}
\real{r=rint(10*(\m*\cm+\f*\cf+\p*\cp)/(\cm+\cf+\cp))/10}
\text{enonce=wims(replace internal XXXX by \cm in \name_enonce)}
\text{enonce=wims(replace internal YYYY by \cf in \enonce)}
\text{enonce=wims(replace internal ZZZZ by \cp in \enonce)}
\text{enonce=wims(replace internal NNNN by \nom in \enonce)}

\statement{\enonce[1] \m \enonce[2], \f \enonce[3] \p \enonce[4] ?}

\answer{\name_answer}{\r}{type=default}
