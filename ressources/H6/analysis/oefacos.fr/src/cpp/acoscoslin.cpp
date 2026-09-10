target=acoscoslin
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}

\precision{10000}

\integer{ra=randitem(1,2)}
\text{cos=item(\ra,cos,sin)}
\rational{c=randint(1..5)}
\if{\ra=1}{
  \integer{a1=\c*pi+1}
  \integer{a2=(\c+1)*pi-1}
  \integer{b=\c%2=0? \c:\c+1}
}{
  \integer{a1=(\c-1/2)*pi+1}
  \integer{a2=(\c+1/2)*pi-1}
  \integer{b=\c}
}
\integer{a=\c%2=0?1:-1}
\function{bpi=\b*pi}
\statement{\name_enonce1[1] [\a1,\a2], \name_enonce1[2] \(f(x) = arc\cos(\cos(x))\) \name_enonce2?
<div class="wims_instruction">
\name_instruction[1] <span class="tt">pi</span> \name_instruction[2] \(pi\).
</div>
}

\answer{\(a\)}{\a}
\answer{\(b\)}{\bpi}

\text{rep=\reply1,\reply2}
\text{bound=pari(vecsort([\a*\a1+(\bpi),\a*\a2+(\bpi),\rep[1]*\a1+\rep[2],\rep[1]*\a2+\rep[2]]))}
\feedback{\sc_reply1<1 or \sc_reply2<1}{
\canvasdraw{200,200}{
xrange \a1,\a2
yrange \bound[1]-1,\bound[-1]+1
vline (\a1+\a2)/2,0,black
hline 0,0,black
plot red, \rep[1]*x+\rep[2]
plot blue, a\cos(\cos(x))
}
}
