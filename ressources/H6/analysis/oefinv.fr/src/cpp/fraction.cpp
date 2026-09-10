target=fraction
#include "lang_titles.inc"
#include "lang.inc"

#include "xiao.inc"
\range{-2..2}
\computeanswer{yes}
\precision{100000}


\integer{a=random(1,2,4,5)*random(-1,1)}
\integer{c=-random(3..15)*sign(\a)}
\integer{A2=\a*2}
\function{f=\a*x + \c/x}
\integer{r=random(1,2)}
\integer{A=\r=1?random(-5,-4,-2,-1):random(1,2,4,5)}
\integer{B=\r=1?random(-25,-20,-16,-10,-8):random(8,10,16,20,25)}
\integer{a1=min(\B,\A)}
\integer{b1=max(\A,\B)}
\real{A=evalue(\f,x=\a1)}
\real{B=evalue(\f,x=\b1)}
\real{a2=min(\A,\B)}
\real{b2=max(\A,\B)}
\integer{delta=-4*(\a)*(\c)}
\function{inv=\a1*(\a)>0?(x+sqrt(x^2+\delta))/(\A2):
		(x-sqrt(x^2+\delta))/(\A2)}
\statement{\name_instruction[1;1] \(f: [\a1,\b1] \to [\a2,\b2]\) \name_instruction[1;2]
  <div class="wimscenter">\(f(x) = \f ).</div>
  \name_instruction[2;]
  \(f^{-1}:[\a2,\b2] \to [\a1,\b1]\).
  <div class="wims_instruction">
  \name_hint
  </div>
}

\answer{\(f^(-1)(x))}{\inv}
\latex{
  \name_instruction[1;1] \(f: [\a1,\b1] \to [\a2,\b2]\) \name_instruction[1;2]
  \begin{center}\(f(x) = \f ).\end{center}
  \name_instruction[2;]
  \(f^{-1}:[\a2,\b2] \to [\a1,\b1]\).
}
