target=sys3

#include "header.inc"
#include "lang_titles.inc"

\keywords{linear_system}
\text{vide=maxima(ordergreat(x,y,z,t))}

\text{A=slib(matrix/non0 3,3,10)}

\matrix{S=pari([\A]*[x;y;z])}

\matrix{s=randint(1..10);randint(1..10);randint(1..10)}

\matrix{B=pari([\A]*[\s])}

\function{l1=maxima(\S[1;1])}
\function{l2=maxima(\S[2;1])}
\function{l3=maxima(\S[3;1])}

\text{l1=texmath(\l1)}
\text{l2=texmath(\l2)}
\text{l3=texmath(\l3)}

#include "lang.inc"

\statement{\name_statement:
<div class="wimscenter">
  \( \left\lbrace \begin{array}{ccc}  \l1 & = & \B[1;1] \\ \l2 & = & \B[2;1] \\ \l3 & = & \B[3;1] \\ \end{array} \right. \)
 </div>

<div class="wims_instruction">
\name_instruction
</div>
}

\answer{\(x\)}{\s[1;1]}{type=default}
\answer{\(y\)}{\s[2;1]}{type=default}
\answer{\(z\)}{\s[3;1]}{type=default}
