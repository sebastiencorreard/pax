target=QCMDroitesRem
\author{Marie-Claude, David}
\email{marie-claude.david@math.u-psud.fr}

\text{letters=shuffle(A,B,C,D,E,F,G)}
\text{A=item(1,\letters)}
\text{B=item(2,\letters)}
\text{C=item(3,\letters)}

\integer{k=random(1..3)}

#include "lang_QCMDroitesRem.inc"
\title{TITLE}
\title_en{TITLE_en}


\statement{\name_enonce ?}

\choice{}{\name_answer[\k]}{\name_answer}

\solution{\name_question[\k] \name_is \name_answer[\k]}
