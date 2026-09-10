target=reciproc

#include "xiao.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}
\format{html}
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
\statement{\name_enonce[1] \(f: \RR \to \RR\) \name_enonce[2]
<div class="wimscenter">\(f(x) = \f \).</div>
\name_enonce2 \(g = f^{-1}\). \name_question[1] \(g'(\y0)) \name_question[2] \(\y0\).
<div class="wims_instruction">
\name_instruction</div>
}

\answer{\(g'(\y0)\)}{\sol}
