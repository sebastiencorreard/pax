target=distpl par1 perp1 pntonline lineonpnt lineonpnt2 pnt2eq
#if defined TARGET_pnt2eq
\precision{100}
#else
\precision{1000}
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_lineonpnt || defined TARGET_distpl || defined TARGET_par1 || defined TARGET_perp1 || defined TARGET_pntonline
\integer{a=random(2..20)*random(-1,1)}
\integer{b=random(2..20)*random(-1,1)}
\integer{c=random(-20..20)}
\integer{x=random(-20..20)}
\integer{y=random(-20..20)}
#endif
#if defined TARGET_pnt2eq
\integer{a1=random(-20..20)}
\integer{a2=random(-20..20)}
\integer{b1=random(-10..10)*2}
\integer{b2=random(-10..9)*2+1}
#endif
#if defined TARGET_lineonpnt
\integer{x=random(1..20)*random(-1,1)}
\integer{y=random(1..20)*random(-1,1)}
#endif
#if defined TARGET_lineonpnt2
\integer{a=random(2..20)*random(-1,1)}
\integer{b=random(2..20)*random(-1,1)}
\integer{x=random(1..20)*random(-1,1)}
\integer{y=random(1..20)*random(-1,1)}
\integer{c=\a*(\x)+(\b)*(\y)}
\integer{ch=random(1,2)}
\text{sol=\ch=1?\b:\a}
\text{a=\ch=1?\a:m}
\text{b=\ch=1?m:\b}
\text{L=\a*x + \b*y = \c}
#endif
#if defined TARGET_par1
\integer{g=gcd(\a,\b)}
\integer{g=gcd(\g,\c)}
\integer{a=\a/\g}
\integer{b=\b/\g}
\integer{c=\c/\g}
#endif
#if defined TARGET_distpl || defined TARGET_par1
\integer{t=\a*(\x) + (\b)*(\y)}
\text{L=pari(\a*x + \b*y) = \c}
# if defined TARGET_distpl
\real{dist=abs((\t-(\c))/sqrt((\a)^2+(\b)^2))}
# endif
# if defined TARGET_par1
\function{eq=\a*x + \b*y = \t}
# endif
#endif
#if defined TARGET_pntonline
\integer{g=random(-20..20)}
\function{L=\a*x + \b*y = \c}
\integer{ch=random(1,2)}
\text{x=item(\ch,\g,m)}
\text{y=item(\ch,m,\g)}
\rational{sol=item(\ch,(\c-(\a)*(\g))/(\b),(\c-(\b)*(\g))/(\a))}
#endif
#if defined TARGET_perp1
\integer{t=\b*(\x) - (\a)*(\y)}
\text{L=\a*x + \b*y = \c}
\function{eq=\b*x - \a*y = \t}
#endif
#if defined TARGET_lineonpnt
\integer{sol=\a*(\x)+(\b)*(\y)}
\text{L=\a*x + \b*y = m}
#endif
#if defined TARGET_pnt2eq
\integer{a=\b2-(\b1)}
\integer{b=\a1-(\a2)}
\integer{c=(\a1)*(\b2)-(\a2)*(\b1)}
\function{eq=\a*x + \b*y = \c}
\statement{\name_instruction
\((\a1, \b1)\) \name_and \((\a2, \b2)\).
<label for="reply1">\name_question</label> \embed{reply1,15}.
<div class="wims_instruction">
\name_inst \(a x + b y = c\).
</div>
}
\answer{\name_answer}{\eq,x,y}{type=equation}
#endif
#if defined TARGET_distpl
\statement{\name_instruction:
  <p class="wimscenter">\(\L).</p>
  \name_question \((\x, \y)).
}
\answer{\name_answer}{\dist}{type=numeric}
#endif
#if defined TARGET_par1 || defined TARGET_perp1
\statement{\name_instruction:
  <div class="wimscenter">\(\L\).</div>
  <label for="reply1">\name_question[1;] \((\x, \y)) \name_question[2;]</label> \embed{reply1,15}.
}
\answer{\name_answer}{\eq,x,y}{type=equation}
#endif
#if defined TARGET_pntonline || defined TARGET_lineonpnt || defined TARGET_lineonpnt2
\statement{\name_instruction:
<div class="wimscenter">\(\L\).</div>
<label for="reply1">\name_question[1;] \((\x, \y)\) \name_question[2;]</label> \embed{reply1,10}.
}
\answer{\(m) }{\sol}{type=numexp}
#endif
