target=click1

#define NUM
#include "lang_titles.inc"
#include "lang.inc"
#include "header.inc"
#include "confparm.inc"

#include "data.inc"
#include "position.inc"

\integer{f1=\given isitemof 2,3?\given:randitem(2,3)}
\integer{pick=randint(1..\datacnt)}
\text{dataline=\data[\pick;]}
\integer{pick=item(1,\dataline)}
\integer{xs=30}
\integer{ys=30}
\text{xlist=column(4,\Pdata)}
\text{ylist=column(3,\Pdata)}
\text{blist=}
\for{i=1 to \end}{
  \integer{x=\xlist[\i]*\xs}
  \integer{y=\ylist[\i]*\ys}
  \integer{y=\ylist[\i]>8?\y+5}
  \integer{x=\ylist[\i]>8?\x+\xs*2}
  \text{blist=\blist r,\x,\y,\x+\xs,\y+\ys;}
  \if{\i=\pick}{\text{glist=r,\x,\y,\x+\xs,\y+\ys}}
}
\text{give=\dataline[\f1]}
\text{flist=\Data[;\f1]}

\statement{\name_instruction \namelist[\f1] \name_is \give.
<div class="wimscenter">
\embed{r1}
</div>
}

\answer{\name_answer}{\imagedir/table2.gif;\glist;\blist}{type=coord}

\if{\result1>1}{\text{clicked=\flist[\result1-1]}}

\feedback{\result1>1}{\name_feed[1] \clicked \name_feed[2] \give.}
