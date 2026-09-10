target=blackbox blackbox2

#include "header.inc"
#include "confparm.inc"

#if defined TARGET_blackbox
# define NUM I
\text{image=table1.gif}
#endif
#if defined TARGET_blackbox2
# define NUM II
\text{image=table2.gif}
#endif
#include "lang_titles.inc"
#include "lang.inc"
#include "data.inc"
#include "position.inc"

\integer{pick=randint(1..\datacnt)}
\text{dataline=\data[\pick;]}
\integer{pick=item(1,\dataline)}
\text{pdataline=\Pdata[\pick;]}
\integer{xs=30}
\integer{ys=30}
\integer{x=\pdataline[4]*\xs}
\integer{y=\pdataline[3]*\ys}
\integer{y=\pdataline[3]>8?\y+5}
\integer{x=\pdataline[3]>8?\x+\xs*2}
\text{blist=}
\for{i=1 to \end}{
 \text{blist=\blist r,\x,\y,\x+\xs,\y+\ys;}
 \if{\i=\pick}{\text{glist=r,\x,\y,\x+\xs,\y+\ys}}
}
\text{good=\dataline[\ask]}
\text{good=\ask=3?\good;\Data[;3]}
\text{a=r1,r2,r3,r4}
\steps{\a[\ask]}
\statement{\name_instruction \quel[\ask] \name_is \namelist[\ask] \name_instruction2?
  <div class="wimscenter">
  \draw{600,360}{
copy 0,0,-1,-1,-1,-1,\image
frect \x,\y,\x+\xs,\y+\ys,black
}
  </div>
}

\answer{\name_answer[1]}{\good}{type=number}
\answer{\name_answer[2]}{\good}{type=case}
\answer{\name_answer[3]}{\good}{type=nocase}
\answer{\name_answer[4]}{\good}{type=number}

