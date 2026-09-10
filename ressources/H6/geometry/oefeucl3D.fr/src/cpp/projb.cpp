target=projb

\author{Bernadette, Perrin-Riou;Adeline, Grelot}

#include "author.inc"

#include "lang_title.inc"
\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}

\integer{n=3}
\text{v1=random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1))}
\text{v2=randint(-2..2),0,randint(-2..2)}
\text{v2=\v2
randint(-2..2),randint(-2..2),0}
\text{v2=\v2
0,randint(-2..2),randint(-2..2)}
\text{v2=randomrow(\v2)}

\text{v3=random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1)),random(randint(1..2), randint(-2..-1))}

la base de F est (v1,v2)
On cherche les ai, i=1,2. <v,v1>=sum(ai*<ei,v1> sur i) et idem pour v2

Calculs des produits scalaires

\text{p21=simplify((item(1,\v1))*(item(1,\v2))+(item(2,\v1))*(item(2,\v2))+(item(3,\v1))*(item(3,\v2)))}
\text{p11=simplify((item(1,\v1))^2+(item(2,\v1))^2+(item(3,\v1))^2)}
\text{p22=simplify((item(1,\v2))^2+(item(2,\v2))^2+(item(3,\v2))^2)}
\matrix{A= \p11, \p21
\p21, \p22
}
\text{p32=simplify((item(1,\v3))*(item(1,\v2))+(item(2,\v3))*(item(2,\v2))+(item(3,\v3))*(item(3,\v2)))}
\text{p31=simplify((item(1,\v3))*(item(1,\v1))+(item(2,\v3))*(item(2,\v1))+(item(3,\v3))*(item(3,\v1)))}

Calculs des solutions

\if{det(\A) =0}{
  \rational{aa=(\p31)/(\p11)}
  \text{sol = (\aa)*(item(1,\v1)) , (\aa)*(item(2,\v1)) , (\aa)*(item(3,\v1))}
  }
  {\rational{a1=simplify(((\p31)*(\p22)-(\p32)*(\p21))/((\p11)*(\p22)-(\p21)^2))}
    \rational{a2=simplify(((\p31)*(\p21)-(\p32)*(\p11))/((\p21)^2-(\p11)*(\p22)))}
    \text{sol=simplify((\a1)*(item(1,\v1)) + (\a2)*(item(1,\v2))) , simplify((\a1)*(item(2,\v1)) + (\a2)*(item(2,\v2))) , simplify((\a1)*(item(3,\v1))+(\a2)*(item(3,\v2)))}
}
#include "lang.inc"
\statement{
\name_instruction1
<p>
\name_instruction2
</p>}

\answer{\name_projorth}{\sol}{type=vector}
