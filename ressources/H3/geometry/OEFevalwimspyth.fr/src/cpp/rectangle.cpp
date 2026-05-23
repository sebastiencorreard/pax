target=rectangle2 rectangle3 rectangle4
#define TITRE Rectangle ou non
#include "author.inc"

\text{let=shuffle(A,B,C,D,E,F,G,H)}
\text{A=\let[1]}
\text{B=\let[2]}
\text{C=\let[3]}

\integer{ch=randint(1..2)}

#if defined TARGET_rectangle2
 \title{TITRE 2}
 \integer{u=random(2..6)}
 \integer{v=random(1..\u-1)}
 \integer{ab=max(\u^2-\v^2,2*\u*\v)}
 \integer{ac=min(\u^2-\v^2,2*\u*\v)}
 \integer{bc=(\ab^2+\ac^2)^(1/2)}
 \integer{bc=\ch=1?\bc+randint(3..9)}
 \text{unit=randitem(cm,m,dm)}
 \text{ab=\ab \unit }
 \text{ac=\ac \unit}
 \text{bc=\bc \unit}
#endif
#if defined TARGET_rectangle3
 \title{TITRE 3}
 \integer{u=random(20..60)}
 \integer{v=random(10..\u-1)}
 \real{ab=max(\u^2-\v^2,2*\u*\v)/10}
 \real{ac=min(\u^2-\v^2,2*\u*\v)/10}
 \real{bc=(\ab^2+\ac^2)^(1/2)}
 \real{bc=\ch=1?\bc+randint(30..90)/10}
 \text{unit=randitem(cm,m,dm)}
 \text{ab=\ab \unit }
 \text{ac=\ac \unit}
 \text{bc=\bc \unit}
#endif
#if defined TARGET_rectangle4
 \title{TITRE 4}
 \integer{ch=randitem(1,2,2,2)}
 \integer{u=random(20..60)}
 \integer{v=random(10..\u-1)}
 \real{ab=max(\u^2-\v^2,2*\u*\v)/10}
 \real{ac=min(\u^2-\v^2,2*\u*\v)/10}
 \real{bc=(\ab^2+\ac^2)^(1/2)}
 \real{bc=\ch=1?\bc+randint(30..90)/10}
 \text{p=randint(1..2)}
 \if{\p=1}{
  \real{ac=\ac/10}
  \text{ab=\ab cm}
  \text{ac=\ac dm}
  \text{bc=\bc cm}
 }{
  \real{ab=\ab/10}
  \text{ab=\ab dm}
  \text{ac=\ac cm}
  \text{bc=\bc cm}
 }
#endif

\text{bad=Non,Oui}
\text{good=item(\ch,\bad)}

\statement{
\(\A\B\C) est un triangle tel que :
<div class="wimscenter">\A\B = \ab &nbsp;;&nbsp; \A\C = \ac &nbsp;;&nbsp; \B\C = \bc</div>
  Le triangle \(\A\B\C) est-il rectangle ? }

\choice{}{\good}{\bad}
