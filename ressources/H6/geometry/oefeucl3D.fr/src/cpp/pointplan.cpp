target=pointplan

\author{Bernadette, Perrin-Riou}
#include "author.inc"
#include "lang_title.inc"

\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}

\real{a=random(1,-1)*randint(10^2..10^4)/100}
\real{b=random(1,-1)*randint(10^2..10^4)/100}
\real{c=random(1,-1)*randint(10^2..10^4)/100}
\integer{u=randint(-10..10)}
\integer{v=randint(-10..10)}
\integer{w=randint(-10..10)}
\integer{u=(\u)^2+(\v)^2+(\w)^2=0 ? \u+randint(1..4)}
\integer{h=randint(-10..10)}
\function{equ = simplify((\u)*x + (\v)*y + (\w)*z)}
\real{sol= abs((\u)*(\a)+(\v)*(\b)+(\w)*(\c)-\h)/((\u)^2+(\v)^2+(\w)^2)^(1/2)}

#include "lang.inc"
\statement{\name_instruction \(\equ  = \h).
}
\answer{\name_voca[1;]}{\sol}{type=numeric}

\feedback{\reply1< 0}{\name_voca[2;]}
