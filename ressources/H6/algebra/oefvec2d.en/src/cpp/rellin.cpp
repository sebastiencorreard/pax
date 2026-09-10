target=rellin
#include "header.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{c11=random(2..10)*random(-1,1)}
\integer{c12=random(2..10)*random(-1,1)}
\integer{c13=random(2..10)*random(-1,1)}
\integer{c21=random(2..10)*random(-1,1)}
\integer{c22=random(2..10)*random(-1,1)}
\integer{c23=random(2..10)*random(-1,1)}

\statement{\name_instruction[1;]:
  <div class="wimscenter">
   \(v_1 = (\c11,\c21), v_2=(\c12,\c22), v_3 =(\c13,\c23)).
  </div>
  \name_instruction[2;]
  <div class="wimscenter">\(a v_1 + b v_2 + c v_3 = 0),</div>
  \name_instruction[3;]
}

\answer{a}{\sx}
\answer{b}{\sy}
\answer{c}{\sz}

\condition{\(a,b,c) \name_cond1}{
  abs(\sx)+abs(\sy)+abs(\sz)>0 and
  abs(round(\sx)-(\sx))<=0 and
  abs(round(\sy)-(\sy))<=0 and
  abs(round(\sz)-(\sz))<=0
}

\condition{\name_cond2}{
  (\c11)*(\sx)+(\c12)*(\sy)+(\c13)*(\sz)=0 and
  (\c21)*(\sx)+(\c22)*(\sy)+(\c23)*(\sz)=0
}
