target=planplan


\author{Bernadette, Perrin-Riou}
#include "author.inc"
#include "lang_title.inc"
\title{TITLE}
\title_en{TITLE_en}
\title_es{TITLE_es}
\title_ca{TITLE_ca}
#include "lang.inc"
\integer{a=randint(-10..10)}
\integer{b=randint(-10..10)}
\integer{c=randint(-10..10)}
\if{(\a)^2+(\b)^2+(\c)^2=0}{\integer{c=randint(1..4)}}
\integer{x1=randint(-5..5)}
\integer{y1=randint(-5..5)}
\integer{z1=randint(-1..1)}
\integer{r=randint(1..5)*random(1,-1)}
\real{d=(\a)*(\x1)+(\b)*(\y1)+(\c)*(\z1)}
\text{par=random(1,2)}
\integer{u=\par=1 ? randint(-10..10): \r*(\a)}
\integer{v=\par=1 ? randint(-10..10): \r*(\b)}
\integer{w=\par=1 ? randint(-10..10): \r*(\c)}
\integer{u=(\u)^2+(\v)^2+(\w)^2=0? randint(1..4)}
\integer{h=randint(-10..10)}
\function{equ1=simplify((\u)*x + (\v)*y + (\w)*z)}
\function{equ2=simplify((\a)*x + (\b)*y + (\c)*z)}
\real{cond=((\u)*(\b)-(\v)*(\a))^2+((\w)*(\b)-(\v)*(\c))^2+((\u)*(\c)-(\w)*(\a))^2}
\text{para=\cond=0 ? item(1,\choix): item(2,\choix)}
\real{sol=\cond=0 ?
abs((\u)*(\x1)+(\v)*(\y1)+(\w)*(\z1)-(\h))/((\u)^2+(\v)^2+(\w)^2)^(1/2):
(abs((\a)*(\u)+(\b)*(\v)+(\c)*(\w)))/(((\u)^2+(\v)^2+(\w)^2)^(1/2)*((\a)^2+(\b)^2+(\c)^2)^(1/2))}
\text{distan=\cond=0 ? \name_choix[1]:\name_choix[2]}
\steps{choice 1
reply 1}

\statement{\name_instruction[1;]\(\equ1= \h) \name_instruction[2;] \(\equ2 = \d).
\if{\step <= 1}{\name_instruction[3;] \embed{choice 1}.
}
\if{\step=2}{
  \if{\cond=0}{\name_instruction[4;]
  }{\name_instruction[5;]}
  }
}
\choice{\name_instruction[6;]}{\para}{\choix}
\answer{\distan}{\sol}{type=numeric}

\feedback{\reply1 <0 and \cond=0}{\name_instruction[7;]}
\feedback{abs(\reply1)>1 and \cond<>0}{\name_instruction[8;] }
\hint{
\if{\cond <>0 and \step=2}{\name_hint1
<div class="wimscenter">
 \(cos u= \frac{\vec{n}_1 . \vec{n}_2}{||\vec{n}_1||\; ||\vec{n}_2||})
</div>}
\if{\cond =0 and \step=2}{\name_hint2
<div class="wimscenter">\(\frac{|d_1 - d_2|}{\sqrt{a^2 + b^2 + c^2}})
</div>}
}
