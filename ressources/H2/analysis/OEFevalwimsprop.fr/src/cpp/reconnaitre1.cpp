target=reconnaitre1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a=randint(4..6)}
\integer{b=50*randint(4..6)}
\integer{c=randint(2..3)}
\integer{d=\c*\b}
\integer{c=\c*\a}

\statement{
\name_enonce[1] \name_enonce[2] \a oeufs \name_enonce[3] \b g \name_enonce[4].
\name_question[1] \c \name_question[2]?}

\answer{\name_answer}{\d}{type=numexp}
