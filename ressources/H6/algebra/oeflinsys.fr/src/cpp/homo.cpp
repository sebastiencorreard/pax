target=homo3x4 homo2x3
\language{fr}
\range{-5..5}
\author{XIAO, Gang}
\email{xiao@unice.fr}
\computeanswer{no}
\format{html}
\precision{1000000}
#include "lang_titles.inc"
#if defined TARGET_homo3x4
\text{list=\(x, y, z, t\)}
\integer{c11=random(2..10)*random(-1,1)}
\integer{c12=random(2..10)*random(-1,1)}
\integer{c13=random(2..10)*random(-1,1)}
\integer{c14=random(2..10)*random(-1,1)}
\integer{c21=random(2..10)*random(-1,1)}
\integer{c22=random(2..10)*random(-1,1)}
\integer{c23=random(2..10)*random(-1,1)}
\integer{c24=random(2..10)*random(-1,1)}
\integer{c31=random(2..10)*random(-1,1)}
\integer{c32=random(2..10)*random(-1,1)}
\integer{c33=random(2..10)*random(-1,1)}
\integer{c34=random(2..10)*random(-1,1)}

\text{C12=\c12>=0?+\c12:\c12}
\text{C13=\c13>=0?+\c13:\c13}
\text{C14=\c14>=0?+\c14:\c14}
\text{C22=\c22>=0?+\c22:\c22}
\text{C23=\c23>=0?+\c23:\c23}
\text{C24=\c24>=0?+\c24:\c24}
\text{C32=\c32>=0?+\c32:\c32}
\text{C33=\c33>=0?+\c33:\c33}
\text{C34=\c34>=0?+\c34:\c34}
#endif
#if defined TARGET_homo2x3
\text{list=\(x,y,z)}
\integer{c11=random(2..10)*random(-1,1)}
\integer{c12=random(2..10)*random(-1,1)}
\integer{c13=random(2..10)*random(-1,1)}
\integer{c21=random(2..10)*random(-1,1)}
\integer{c22=random(2..10)*random(-1,1)}
\integer{c23=random(2..10)*random(-1,1)}

\text{C12=\c12>=0?+\c12:\c12}
\text{C13=\c13>=0?+\c13:\c13}
\text{C22=\c22>=0?+\c22:\c22}
\text{C23=\c23>=0?+\c23:\c23}
\text{C32=\c32>=0?+\c32:\c32}
\text{C33=\c33>=0?+\c33:\c33}
#endif
#include "lang.inc"

#if defined TARGET_homo3x4
\statement{\name_instruction
<div class="wimscenter">
\(\left\lbrace
\begin{array}{cccccc}
\c11 x &\C12 y &\C13 z &\C14 t&=& 0 & (1)\\\
 \c21 x &\C22 y &\C23 z&\C24 t&=& 0 & (2)\\\
 \c31 x &\C32 y &\C33 z&\C34 t&=& 0 & (3)
\end{array}\right .\)
</div>
<div class="wims_instruction">
\name_hint
</div>
}

\answer{x}{\sx}
\answer{y}{\sy}
\answer{z}{\sz}
\answer{t}{\st}

\condition{\list \name_cond[1]}
{abs(\sx)+abs(\sy)+abs(\sz)+abs(\st)>0 and abs(round(\sx)-(\sx))<=0 and
  abs(round(\sy)-(\sy))<=0 and abs(round(\sz)-(\sz))<=0 and abs(round(\st)-(\st))<=0}
\condition{\name_cond[2] (1) \name_cond[3]}{(\c11)*(\sx)+(\c12)*(\sy)+(\c13)*(\sz)+(\c14)*(\st)=0}
\condition{\name_cond[2] (2) \name_cond[3]}{(\c21)*(\sx)+(\c22)*(\sy)+(\c23)*(\sz)+(\c24)*(\st)=0}
\condition{\name_cond[2] (3) \name_cond[3]}{(\c31)*(\sx)+(\c32)*(\sy)+(\c33)*(\sz)+(\c34)*(\st)=0}
#endif
#if defined TARGET_homo2x3
\statement{\name_instruction
<div class="wimscenter">
\(\left\lbrace
\begin{array}{cccc}
  \c11 x &\C12 y &\C13 z&=& 0 &(1) \\\
  \c21 x &\C22 y &\C23 z&=& 0 &(2)
\end{array}\right .\)
</div>
<div class="wims_instruction">
\name_hint
</div>
}
\answer{x}{\sx}
\answer{y}{\sy}
\answer{z}{\sz}
\condition{\list \name_cond[1]} {abs(\sx)+abs(\sy)+abs(\sz)>0
  and abs(round(\sx)-(\sx))<=0
  and abs(round(\sy)-(\sy))<=0 and abs(round(\sz)-(\sz))<=0}
\condition{\name_cond[2] (1) \name_cond[3]}{(\c11)*(\sx)+(\c12)*(\sy)+(\c13)*(\sz)=0}
\condition{\name_cond[2] (2) \name_cond[3]}{(\c21)*(\sx)+(\c22)*(\sy)+(\c23)*(\sz)=0}
#endif
