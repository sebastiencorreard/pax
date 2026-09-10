target=parparam
\language{fr}
\range{-5..5}
\author{Marie-Claude,David}
\email{mcld@math.u-psud.fr}
\computeanswer{no}
\format{html}
\precision{1000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{a1=random(2..20)*random(-1,1)}
\integer{a2=random(2..20)*random(-1,1)}
\integer{b1=random(-10..10)*2}
\integer{b2=random(-10..9)*2+1}
\integer{x=random(-20..20)}
\integer{y=random(-20..20)}
\text{ex=texmath(\a1*t + \b1)}
\text{ey=texmath(\a2*t + \b2)}
\text{px=texmath(\a1*t + \x)}
\text{py=texmath(\a2*t + \y)}

\statement{\name_instruction:
<div class="wimscenter">
\(\left \lbrace \begin{array}{rcl}
  x &=&\ex \\\
  y &=&\ey .
\end{array}\right.\)
</div>
\name_question[1;] \((\x, \y)\) \name_question[2;]:
<div class="wimscenter">
\(x =\) \embed{reply1,7}t+\embed{reply2,7}<br/>
\(y =\) \embed{reply3,7}t+\embed{reply4,7}
</div>
}
\answer{\alpha}{\rep1}{type=numeric}
\answer{xx}{\rep2}{type=numeric}
\answer{\beta}{\rep3}{type=numeric}
\answer{yy}{\rep4}{type=numeric}
\real{v1=(\rep1)*\a2-(\rep3)*\a1}
\real{X=(\rep2)-\x}
\real{Y=(\rep4)-\y}
\real{v2=\X*\a2-\Y*\a1}
\condition{\name_condition[1;] \name_condition[2;] \(L\)}{\v1 = 0}{weight=0.3}
\condition{\name_condition[1;] \name_condition[3;] \(M\) }{\v2 = 0}{weight=0.7}
\feedback{1=1}{\name_feed:
<div class="wimscenter">
\(\left \lbrace \begin{array}{rcl}
  x &=&\px \\\
  y &=&\py .
\end{array}\right.\)
</div>}
