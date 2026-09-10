target=quadratic
#include "lang_titles.inc"
#include "lang.inc"
\range{-2..2}
#include "xiao.inc"
\computeanswer{yes}
\precision{100000}

\integer{a=random(1,2,4,5)*random(-1,1)}
\integer{b=random(1..7)*random(-1,1)}
\integer{B=\b*2}
\real{cent=-(\b)/(\a)}
\real{neut=(\b)^2/(\a)}
\integer{c=\a>0?random(\neut-10..\neut-3):random(\neut+3..\neut+10)}
\function{f=\a*x^2 + \B*x + \c}
\integer{r=random(1,2)}
\integer{A=\r=1?random(floor(\cent)-4..floor(\cent)-1):
		random(ceil(\cent)+1..ceil(\cent)+4)}
\integer{B=\r=1?random(\A-4..\A-1):random(\A+1..\A+4)}
\integer{a1=min(\B,\A)}
\integer{b1=max(\A,\B)}
\real{A=evalue(\f,x=\a1)}
\real{B=evalue(\f,x=\b1)}
\real{a2=min(\A,\B)}
\real{b2=max(\A,\B)}
\integer{delta=(\b)^2-(\a)*(\c)}
\function{inv=\A<\B?(-\b+sqrt(\a*x+\delta))/(\a):
		(-\b-sqrt(\a*x+\delta))/(\a)}

\statement{\name_instruction[1;1] \(f: [\a1,\b1] \to [\a2,\b2]\) \name_instruction[1;2]
  <div class="wimscenter">\(f(x) = \f\).</div>
  \name_instruction[2;]
  \(f^{-1}:[\a2,\b2] \to [\a1,\b1]\).
  <div class="wims_instruction">
  \name_hint
  </div>
}

\answer{\(f^{-1}(x)\)}{\inv}
\latex{
\begin{statement}\name_instruction[1;1] \(f: [\a1,\b1] \to [\a2,\b2]\) \name_instruction[1;2]
  \begin{center}\(f(x) = \f\).\end{center}
  \name_instruction[2;]
  \(f^{-1}:[\a2,\b2] \to [\a1,\b1]\).
  <div class="wims_instruction">
  \name_hint
  </div>
\end{statement}
}
