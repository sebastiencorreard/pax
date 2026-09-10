target=plan


\author{Adeline,Grelot;Bernadette, Perrin-Riou}
#include "author.inc"
#include "lang_title.inc"
\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}

Choix des équations et du vecteur v
\matrix{M=slib(matrix/invertible 3,2)}
\text{C1=column(1,\M)}
\text{C2=column(2,\M)}
\text{v=column(3,\M)}
\integer{a=item(1,\C1)}
\integer{b=item(2,\C1)}
\integer{c=item(3,\C1)}
\integer{c=\c=0?randint(1..3)*(random(-1,1))}
\integer{A=item(1,\v)}
\integer{B=item(2,\v)}
\integer{C=item(3,\v)}

Problème si A et B sont nuls (->C=0 donc v=vecteur nul)
\integer{A= \A=0 and \B=0 ? randint(1..3)*(random(-1,1))}
\integer{C=-((\A)*(\a)+(\B)*(\b))}
\integer{A=(\A)*(\c)}
\integer{B=(\B)*(\c)}
\text{v=\A , \B , \C}
\integer{test=\A*(\a)+(\B)*(\b)+(\C)*(\c)}
La normale (à P')
\text{normale=column(2,\M)}
Calcul de la projection

\text{prod=simplify((\A)*(item(1,\normale)) + (\B)*(item(2,\normale)) + (\C)*(item(3,\normale)))}
\text{norm2=simplify((item(1,\normale))^2 + (item(2 , \normale))^2 + (item(3,\normale))^2)}
\rational{vprime1=\A-(\prod)*(item(1,\normale)/\norm2)}
\rational{vprime2=\B-(\prod)*(item(2,\normale)/\norm2)}
\rational{vprime3=\C-(\prod)*(item(3,\normale))/\norm2}
\text{vprime=\vprime1 , \vprime2 , \vprime3}


\text{equation=simplify((\a)*x + (\b)*y + (\c)*z)}
\text{equation2=simplify((item(1,\C2))*x + (item(2 , \C2))*y + (item(3,\C2))*z)}

#include "lang.inc"
\statement{\name_instruction1
<div class="wimscenter">\(\equation=0)</div>
\name_instruction2
<div class="wimscenter">\(\equation2=0).</div>

<p>
\name_instruction3 (\vprime1,\vprime2,\vprime3).
</p>
}

\answer{\name_answer[1;]}{\rep}{type=vector}
\condition{(\rep) \name_answer[2;] ?}{item(1,\rep)*(\a)+(item(2,\rep))*(\b)+
(item(3,\rep))*(\c)=0 and (item(1,\rep))^2+(item(2,\rep))^2+(item(3,\rep))^2 !=0}
\real{N1=(item(1,\rep)-(\vprime1))*(item(2,\normale))
-(item(2,\rep)-(\vprime2))*(item(1,\normale))}
\real{N2=(item(1,\rep)-(\vprime1))*(item(3,\normale))
-(item(3,\rep)-(\vprime3))*(item(1,\normale))}
\real{N3=(item(3,\rep)-(\vprime3))*(item(2,\normale))
-(item(2,\rep)-(\vprime2))*(item(3,\normale))}
\condition{\name_answer[3;] (\vprime) ?}{\N1=0 and \N2=0 and \N3=0}
