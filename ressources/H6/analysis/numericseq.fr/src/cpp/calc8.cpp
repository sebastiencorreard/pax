target=calctersuite8
#include "author.inc"
#define NUM G
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000}

\integer{chx= random(-1,1)}

\if {\chx=1}
{\real{u0=randint(10..20)/1000}
\integer{q=randint(2..6)}}

\if {\chx=-1}
{\integer {u0=randint(100..200)}
\real{q=randint(2..5)/10}}

\integer{rg1=randint(2..4)}
\integer{rg2=\rg1+randint(2..5)}
\real{urg1=\u0*\q^\rg1}
\real{urg2=\u0*\q^\rg2}

\statement{
<p>
\name_statement[1;]
\( u_\rg1 )=\urg1 \name_and \( u_\rg2 )=\urg2.
</p><p>
\name_statement[2;] \(u_0\).
</p>
<div class="wims_instruction">
 \name_instruction \( u_\rg1 \) \name_and \( u_\rg2 \).
</div>
<ul><li>
  <label for="reply1">\(q\) =</label> \embed{reply 1,3}
</li><li>
  <label for="reply2">\(u_0) =</label> \embed{reply 2,3}
</li></ul>
}

\reply{ }{\q}{type=numeric}
\reply{ }{\u0}{type=numeric}
