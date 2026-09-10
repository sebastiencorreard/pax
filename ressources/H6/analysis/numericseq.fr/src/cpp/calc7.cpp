target=calctersuite7
#include "author.inc"
#define NUM A
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000}

\integer{u0=randint(10..50)}
\integer{r=randint(2..15) *random(-1,1) }
\integer{rg1=randint(2..8)}
\integer{rg2=\rg1+randint(5..12)}
\integer{urg1=\u0+\r*\rg1}
\integer{urg2=\u0+\r*\rg2}

\statement{
<p>
\name_statement[1;]
\( u_\rg1 = \urg1\) \name_and \( u_\rg2 = \urg2 \).
</p><p>
\name_statement[2;] \(u_0\):
</p>
<ul><li>
  <label for="reply1">\(r\) =</label> \embed{reply 1,3}
</li><li>
  <label for="reply2">\(u_0) =</label> \embed{reply 2,3}
</li></ul>
}

\reply{ }{\r}{numeric}
\reply{ }{\u0}{numeric}

