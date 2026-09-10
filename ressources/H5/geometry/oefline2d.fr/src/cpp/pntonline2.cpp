target=pntonline2

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000}

\integer{a=random(2..20)*random(-1,1)}
\integer{b=random(2..20)*random(-1,1)}
\integer{c=random(1..20)*random(-1,1)}
\integer{d=random(1..20)*random(-1,1)}
\integer{g=random(-20..20)}
\text{ex=texmath(\a*t + \c)}
\text{ey=texmath(\b*t + \d)}
\integer{ch=random(1,2)}
\text{x=item(\ch,\g,m)}
\text{y=item(\ch,m,\g)}
\rational{sol=item(\ch,
  \d+(\b)*(\g-(\c))/(\a),
  \c+(\a)*(\g-(\d))/(\b)
  )}

\statement{\name_instruction
  <div class="wimscenter">
  \(\left \lbrace \begin{array}{rcl}
  x &=&\ex \\\
  y &=&\ey.
  \end{array}\right.\)
  </div>
  <label for="reply1">
  \name_question[1;] \((\x, \y)\) \name_question[2;]
  </label>
  \embed{reply1,10}.
}

\answer{\(m)}{\sol}{type=numexp}
