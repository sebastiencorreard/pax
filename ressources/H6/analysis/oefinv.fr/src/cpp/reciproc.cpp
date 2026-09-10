target=reciproc
#include "lang_titles.inc"
#include "lang.inc"
\range{-5..5}
#include "xiao.inc"
\computeanswer{yes}
\precision{1000}

\integer{a=random(1..5)*random(-1,1)}
\integer{b=random(abs(\a)+1..abs(\a)+3)*random(-1,1)}
\integer{c1=random(1..20)*random(-1,1)}
\integer{c2=random(1..20)*random(-1,1)}
\text{sincos=random(sin,cos)}
\text{sign=random(+,-)}
\function{f=\b*x \sign \sincos(\a*x+\c1) + \c2}

\integer{y0=random(-100..100)}
\real{x0=solve(\f - (\y0),x=-1000..1000)}
\function{der=diff(\f,x)}
\real{sol=1/evalue(\der,x=\x0)}
\statement{\name_instruction[1;]
  <div class="wimscenter">\(f(x) = \f ).</div>
  \name_instruction[2;]
  \(g=f^{-1}). \name_instruction[3;1] \(g'(\y0)) \name_instruction[3;2] \(\y0).
  <div class="wims_instruction">
  \name_hint
  </div>
}

\answer{\(g'(\y0)) }{\sol}

\latex{
  \name_instruction[1;]
  \begin{center}\(f(x) = \f \).\end{center}
  \name_instruction[2;] \(g=f^{-1}\). \name_instruction[3;1]
  \(g'(\y0)\) \name_instruction[3;2] \(\y0\).
}
