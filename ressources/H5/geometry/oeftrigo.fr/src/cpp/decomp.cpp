target=decomp1 decomp2
#include "header.inc"
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

#if defined TARGET_decomp1
 \text{sign=}
#endif
#if defined TARGET_decomp2
 \text{sign=-}
#endif


\text{x=randitem(x,y,r,s,t)}
\text{n=randint(2..9)}
\function{arg=\n*\x}
\real{A=randint(50..1000)/100}
\real{p=randint(5..628)*random(-0.01,0.01)}
\text{sincos=randitem(sin,cos)}
\function{f=\sign\A*\sincos(\arg + \p)}
\integer{rr=randitem(1,2)}
\if{\rr=1}{
 \function{f2=a*cos(\arg) + b*sin(\arg)}
 \real{a=\sign\A*\sincos(\p)}
 \real{b=\sign\A*\sincos(\p+pi/2)}
}{
 \function{f2=a*sin(\arg) + b*cos(\arg)}
 \real{b=\sign\A*\sincos(\p)}
 \real{a=\sign\A*\sincos(\p+pi/2)}
}

\statement{\name_instruction
<div class="wimscenter">
   \(\f = \f2).
</div>
}

\answer{\(a)}{\a}{type=number}
\answer{\(b)}{\b}{type=number}
