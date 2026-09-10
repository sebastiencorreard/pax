target=invval
#include "lang_titles.inc"
#include "lang.inc"

#include "xiao.inc"
\range{-5..5}
\precision{10000}
\computeanswer{no}
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

\statement{\name_instruction[1;1] \(f: \RR \to \RR\) \name_instruction[1;2]
  <div class="wimscenter">\(f(x) = \f\).</div>
  \name_instruction[2;]
  \(f^{-1}: \RR \to \RR\).
  \name_instruction[3;]
  \(\y0\).
  <div class="wims_instruction">
  \name_hint
  </div>
}

\answer{\(f^{-1}(\y0)\)}{\x0}
\latex{\begin{statement}
\name_instruction[1;1] \(f: \RR \to \RR\) \name_instruction[1;2]
  \begin{center}\(f(x) = \f\).\end{center}
  \name_instruction[2;]
  \(f^{-1}: \RR \to \RR\).
  \name_instruction[3;]
  \(\y0\).
\end{statement}
}

