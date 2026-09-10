target=slope2eq
#include "author.inc"

\precision{100}
#include "lang_titles.inc"
#include "lang.inc"
\integer{a1=random(-20..20)}
\integer{b1=random(-20..20)}
\integer{b=random(2,4,5,8,10,16)*random(-1,1)}
\integer{a=random(\b-7,\b-6,\b-3,\b-1,\b+1,\b+3,\b+6,\b+7)*random(-1,1)}
\real{slope=-(\a)/(\b)}
\integer{c=(\a)*(\a1) + (\b)*(\b1)}
\function{eq=\a*x + \b*y = \c}

\statement{\name_instruction \((\a1,\b1)\)
\name_instruction2 \(\slope\).<div>
<label for="reply1">\name_question</label> \embed{reply1,15}.
</div>
<div class="wims_instruction">
\name_inst \(a x + b y = c\).
</div>
}

\answer{\name_answer}{\eq}{type=equation}
