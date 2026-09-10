target=poinplan2

\author{Bernadette, Perrin-Riou}
#include "author.inc"
#include "lang_title.inc"
\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}
#include "lang.inc"

\real{a=random(1,-1)*randint(10^2..10^4)/100}
\real{b=random(1,-1)*randint(10^2..10^4)/100}
\real{c=random(1,-1)*randint(10^2..10^4)/100}

\integer{a1=randint(-5..5)}
\integer{b1=randint(-5..5)}
\integer{c1=randint(-1..1)}

\integer{a2=randint(-5..5)}
\integer{b2=randint(-5..5)}
\integer{c2=randint(-1..1)}
\integer{a2= \a2=\a1 and \b2=\b1 and \c2=\c1 ? \a2-1}

\integer{a3=randint(-5..5)}
\integer{b3=randint(-5..5)}
\integer{c3=randint(-5..5)}
\text{QR= \a2-(\a1),\b2-(\b1),\c2-(\c1)}
\text{QS= \a3-(\a1),\b3-(\b1),\c3-(\c1)}
\text{test= (\a2-(\a1))*(\b3-(\b1))=(\a3-(\a1))*(\b2-(\b1))
and (\a3-(\a2))*(\b1-(\b2))=(\a1-(\a2))*(\b3-(\b2))
and (\a1-(\a3))*(\b2-(\b3))=(\a2-(\a3))*(\b1-(\b3)) ?
1:2}

\text{sol1= item(\test,\choix)}
\text{QP= \a-(\a1),\b-(\b1),\c-(\c1)}
\text{QS= \sol1=1 ? \QP}
\real{num= ((item(2,\QR))*(item(3,\QS))-(item(3,\QR))*(item(2,\QS)))^2
+((item(3,\QR))*(item(1,\QS))-(item(1,\QR))*(item(3,\QS)))^2
+((item(1,\QR))*(item(2,\QS))-(item(2,\QR))*(item(1,\QS)))^2}
\if{\sol1=1}{
  \real{sol2=((\num)/(item(1,\QR))^2+(item(2,\QR))^2+(item(3,\QR))^2)^(1/2)}
  }
  {\matrix{M= \QR
  \QS
  \QP}
  \real{sol2=abs(det(\M))/(\num)^(1/2)}
}

\steps{choice 1
reply 1
}
\statement{
\name_let \(Q = (\a1 , \b1 , \c1)) , \(R = (\a2 , \b2 , \c2)) ,
\(S = (\a3 , \b3 , \c3)).
\if{\step <= 1}{ \name_instruction[1;] \embed{choice 1}}
\if{\step=2}{\name_instruction[2;] \(P = (\a , \b , \c) )
\if{\test=2}{\name_instruction[3;]}
\if{\test=1}{\name_instruction[4;]}
}}
\choice{}{\sol1}{\choix}
\answer{\name_instruction[5;]}{\sol2}{type=numeric}

\hint{\if{\step=2 and \test=2}{
\name_hint
<div class="wimscenter">
\(\frac{ |\vec{QR}.(\vec{QS}\wedge \vec{QP})||}{|| \vec{QR}\wedge \vec{QS}|} = \frac{|det(\vec{QR} , \vec{QS} , \vec{QP})|}{|| \vec{QR}\wedge \vec{QS}|| })
</div>
}}
