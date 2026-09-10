target=bijquad
#include "lang_titles.inc"
#include "lang.inc"
#include "xiao.inc"
\range{-2..2}
\computeanswer{yes}
\precision{100000}

\integer{a=random(1,-1)}
\integer{b=random(1..15)*random(-1,1)}
\integer{B=\b*2}
\real{cent=-(\b)/(\a)}
\integer{c=random(1..50)*random(-1,1)}
\function{f=\a*x^2 + \B*x + \c}
\real{base=evalue(\f,x=\cent)}
\text{hf=htmlmath(\f)}

\integer{zone=random(1,1,2,2,2,3,3)}
\integer{type=random(1,1,2,2,2,3,3,3)}
\integer{a1=item(\zone,random(\cent-20..\cent-9),
  random(\cent-6..\cent-2),
  random(\cent+2..\cent+8))}
\integer{b1=item(\zone,random(\cent-8..\cent-2),
  random(\cent+7..\cent+16),
  random(\cent+9..\cent+20))}
\text{notf=\(f) \name_notf [\a1;\b1]}
\text{noj=\(f) \name_noj}
\text{surj=\(f)\name_surj}
\text{inj=\(f) \name_inj}
\text{bij=\(f) \name_bij}
\text{bad=\notf,\noj,\surj,\inj,\bij}
\integer{A=evalue(\f,x=\a1)}
\integer{B=evalue(\f,x=\b1)}
%%%	restricted	just  extended
\integer{AA=item(\zone+\type*3-3,
	\A,\A,\A,	\A,\base,\A,	\A,\base,\base
)}
\integer{BB=item(\zone+\type*3-3,
	\B,\B,\B,	\B,\B,\B,	\base,\B,\B
)}
\text{good=item(\zone+\type*3-3,
	\notf,\notf,\notf,
	\bij,\surj,\bij,
	\inj,\noj,\inj
)}
\integer{a2=min(\AA,\BB)}
\integer{b2=max(\AA,\BB)}
\integer{rr=random(1,2)}
\integer{a2=\rr=1 and \type=1 and \zone!=2? \a2+random(1..4)}
\integer{b2=\rr=2 and \type=1 and \zone!=2? \b2-random(1..4)}
\integer{a2=\rr=1 and \type=3 and \zone=2? \a2-random(1..6)}
\integer{b2=\rr=2 and \type=3 and \zone=2? \b2+random(1..6)}

\statement{\name_instruction[1] \(f: [\a1,\b1] \to [\a2,\b2]\)
  \name_instruction[2]
  <div class="wimscenter">\(f(x) = \f \).</div>
  \name_instruction[3] \(f\)?
}

\choice{}{\good}{\bad}
