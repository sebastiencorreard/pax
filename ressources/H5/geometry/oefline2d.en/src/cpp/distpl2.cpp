target=distpl2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000}

\integer{a1=random(2..20)*random(-1,1)}
\integer{a2=random(2..20)*random(-1,1)}
\integer{b1=random(-10..10)*2}
\integer{b2=random(-10..9)*2+1}
\integer{a=-(\a2)}
\integer{b=\a1}
\integer{c=\a*(\b1)+(\b)*(\b2)}
\integer{x=random(-20..20)}
\integer{y=random(-20..20)}
\integer{t=\a*(\x) + (\b)*(\y)}
\text{ex=texmath(\a1*t + \b1)}
\text{ey=texmath(\a2*t + \b2)}
\real{dist=abs((\t-(\c))/sqrt((\a)^2+(\b)^2))}

\statement{\name_instruction
<div class="wimscenter">
\(\left \lbrace \begin{array}{rcl}
  x &=&\ex \\\
  y &=&\ey .
\end{array}\right.\)
</div>
\name_question \((\x,\y)).
}

\answer{\name_answer}{\dist}{type=numeric}
