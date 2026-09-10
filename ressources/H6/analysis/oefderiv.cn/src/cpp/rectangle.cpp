target=rectangle1 rectangle2 rectangle3 rectangle4 rectangle5 rectangle6

#include "xiao.inc"

\text{dir=random(1,2)}
\text{direction=item(\dir,递增,递减)}
\text{sign=item(\dir,+,-)}
\real{a=randint(15..50)/10}
\text{lw=random(1,2)}
\text{LW=item(\lw,长度,宽度)}
\integer{w=randint(10..30)}
\integer{l=randint(\w+5..2*\w+10)}
\integer{peri=2*(\w+\l)}
\integer{area=\w*\l}

#if #TARGET (rectangle1)
  \title{长方形 I}
  \text{fix=item(\lw,宽度,长度)}
  \text{fixval=item(\lw,\w,\l)}
  \text{fixunit=厘米}
  \text{first=\LW}
  \text{ref=\LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=厘米}
  \integer{C=\fixval}
  \real{sol=\sign(\C)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=它的面积}
#endif

#if #TARGET (rectangle2)
  \title{长方形 II}
  \text{fix=周长}
  \text{fixval=\peri}
  \text{fixunit=厘米}
  \text{first=\LW}
  \text{ref=\LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=厘米}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=它的面积}
#endif

#if #TARGET (rectangle3)
  \title{长方形 III}
  \text{fix=周长}
  \text{fixval=\peri}
  \text{fixunit=厘米}
  \text{first=\LW}
  \text{ref=item(\lw,宽度,长度)}
  \text{r=item(\lw,\w,\l)}
  \text{runit=厘米}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=它的面积}
#endif

#if #TARGET (rectangle4)
  \title{长方形 IV}
  \text{fix=周长}
  \text{fixval=\peri}
  \text{fixunit=厘米}
  \text{first=\LW}
  \text{ref=面积}
  \real{r=\area}
  \text{runit=平方厘米}
  \integer{C=\l+\w}
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign(\C-2*\t)*\a}
  \text{solunit=cm<sup>2</sup>/s}
  \text{second=它的面积}
#endif

#if #TARGET (rectangle5)
  \title{长方形 V}
  \text{fix=面积}
  \text{fixval=\area}
  \text{fixunit=平方厘米}
  \text{first=\LW}
  \text{ref=\LW}
  \text{r=item(\lw,\l,\w)}
  \text{runit=厘米}
  
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign 2*(1-\area/(\t^2))*\a}
  \text{solunit=cm/s}
  \text{second=它的周长}
#endif

#if #TARGET (rectangle6)
  \title{长方形 VI}
  \text{fix=面积}
  \text{fixval=\area}
  \text{fixunit=平方厘米}
  \text{first=\LW}
  \text{ref=item(\lw,宽度,长度)}
  \text{r=item(\lw,\w,\l)}
  \text{runit=厘米}
  
  \real{t=item(\lw,\l,\w)}
  \real{sol=\sign 2*(1-\area/(\t^2))*\a}
  \text{solunit=cm/s}
  \text{second=它的周长}
#endif


\statement{有一个长方形,
它的\first以每秒 \a 厘米的定速\direction,
但是它的\fix保持不变, 为 \fixval \fixunit.
当\ref等于 \r \runit时,
\second变化的速度 (以 \solunit 为单位) 是多少?
}

\answer{速度}{\sol}
