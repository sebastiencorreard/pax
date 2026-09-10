target=calcexp
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = randitem(-1,1)*random(1..8)}
\integer{cas=randitem(1,2,3)}
\text{fct=exp}
\if{\cas<3}{
  \integer{b= randitem(-1,1)*random(0,0,1,2,3,4)}
  }{
  \integer{b= randitem(-1,1)*random(1..8)}
}
\integer{k=randitem(-1,1)*random(1..8)}
\text{tk=\k}
\text{tk=\k=-1?-}
\text{tk=\k=1?}

\function{u1=maxima(expand(\a*x + \b))}
\function{u2=maxima(expand(\a*x + \b)^2)}
\function{u3=sqrt(\u1)}

\text{u1=(\u1)}
\text{u=item(\cas,\u1,\u2,\u3)}
\text{u=texmath(\u)}
\text{v=e^{\tk x}}
\function{f=\u \times \v}
\text{inf=&#8734;}
\if{\cas<3}{
  \text{lim1=-\inf}
  \text{lim2=+\inf}
  \text{tolim1=x\to-\infty}
  \text{tolim2=x\to+\infty}
  \text{ensdef=\(\mathbb{R})}
}
\if{\cas=1}{
  \text{ulim=\a>0?-inf,-\infty,+inf,+\infty:+inf,+\infty,-inf,-\infty}
  \text{ucod=\a>0?-1,1:1,-1}
  \text{vlim=\k>0?0,0,+inf,+\infty:+inf,+\infty,0,0}
  \text{vcod=\k>0?0,1:1,0}
}
\if{\cas=2}{
  \text{ulim=+inf,+\infty,+inf,+\infty}
  \text{ucod=1,1}
  \text{vlim=\k>0?0,0,+inf,+\infty:+inf,+\infty,0,0}
  \text{vcod=\k>0?0,1:1,0}
}
\if{\cas=3}{
  \rational{x0=-\b/\a}
  \text{sx=\a>0?+:-}
  \integer{ssx=(\sx issametext +)?1:-1}
  \text{xinf=\sx\inf}
  \text{texinf=\sx\infty}
  \text{ensdef=\a>0? &#93; \x0 ; \xinf &#91; }
  \text{natlim=\a>0?\name_valsupinf[1]:\name_valsupinf[2]}
  \text{ineg=\a>0?>:<}
  \text{ensdef=\a<0? &#93;\xinf ; \x0 &#91; }
  \text{lim1=\a>0?\x0:\xinf}
  \text{lim2=\a>0?\xinf:\x0}
  \text{tolim1=\a>0?\begin{array}{l}x\to\x0\\x>\x0\end{array}:x\to\texinf}
  \text{tolim2=\a>0?x\to\texinf:\begin{array}{l}x\to\x0\\x<\x0\end{array}}
  \text{ulim=\a>0?0,0,+inf,+\infty:+inf,+\infty,0,0}
  \text{ucod=\a>0?0,1:1,0}
  \rational{x1=\k*\x0}
  \text{c=exp(\x1)}
  \text{tc=e^{\x1}
}
\if{\a>0}{
  \text{vlim=\k>0?\c,\tc,+inf,+\infty:\c,\tc,0,0}
  \text{vcod=\k>0?2,1:2,0}
}{
  \text{vlim=\k>0?0,0,\c,\tc:+inf,+\infty,\c,\tc}
  \text{vcod=\k>0?0,2:1,2}}
}
\text{rep1=item(1,\ulim)}
\text{rep2=item(3,\ulim)}
\text{sol1=item(2,\ulim)}
\text{sol2=item(4,\ulim)}
\text{rep3=item(1,\vlim)}
\text{rep4=item(3,\vlim)}
\text{sol3=item(2,\vlim)}
\text{sol4=item(4,\vlim)}
\integer{ul1=item(1,\ucod)}
\integer{ul2=item(2,\ucod)}
\integer{vl1=item(1,\vcod)}
\integer{vl2=item(2,\vcod)}
\integer{tmp=\ul1*\vl1}
\integer{rep5=\vl1=0?2:1}
\text{sol5=item(\rep5,\name_choice2)}
\if{\tmp=0}{
  \text{fl1=0,0}
}{
  \if{\tmp>0}{\text{fl1=+inf,+\infty}}{\text{fl1=-inf,-\infty}}
}
\integer{tmp=\ul2*\vl2}
\integer{rep7=\vl2=0?2:1}
\if{\tmp=0}{\text{fl2=0,0}}
{\if{\tmp>0}{\text{fl2=+inf,+\infty}}{\text{fl2=-inf,-\infty}}}
\text{rep6=item(1,\fl1)}
\text{sol6=item(2,\fl1)}
\text{rep8=item(1,\fl2)}
\text{sol8=item(2,\fl2)}

#include "calc.inc"
