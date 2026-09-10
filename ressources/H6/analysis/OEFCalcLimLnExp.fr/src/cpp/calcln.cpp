target=calcln
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = randitem(-1,1)*random(1..8)}
\text{fct=ln}
\text{\sa=\a>0?+:-}
\text{\soa=\a>0?-:+}
\integer{b=randitem(0,0,1,2,3,4)}
\integer{b=randitem(-1,1)*\b}

\text{bc=\b>0?2:-2}
\text{bc=\b=0?0}
\integer{k=randitem(-1,1)*random(1..8)}

\function{u1=maxima(expand(\a*x + \b))}
\function{u2=maxima(expand(\a*x + \b)^2)}
\function{u3=1/(\u1)}
\integer{cas=randitem(1,2,3,3)}

/** interdire x1=1 qui donnerait limite ln(t)/(t-1) avec t->1 ; changer k en -k et mettre à jour x1**/
\if{\cas=3}{
\rational{x0=-\b/\a}
\rational{x1=\k*\x0}
\if{\x1=1}{\integer{k=-\k}
 \rational{x1=-1}}
}
\text{tk=\k}
\text{tk=\k=-1?-}
\text{tk=\k=1?}
\text{u1=(\u1)}
\text{u=item(\cas,\u1,\u2,\u3)}
\text{u=texmath(\u)}
\text{v=\ln(\tk x)}
\function{f=\u \times \v}
\text{inf=&#8734;}
\text{ic=1}
\if{\k>0}{
  \text{lim1=0}
  \text{lim2=+\inf}
  \text{tolim1=\begin{array}{l}x\to 0\\x > 0\end{array}}
  \text{tolim2=x\to+\infty}
  \text{natlim=\name_valsupinf[1]}
}{
  \text{lim2=0}
  \text{lim1=-\inf}
  \text{tolim2=\begin{array}{l}x\to 0\\x < 0\end{array}}
  \text{tolim1=x\to-\infty}
  \text{natlim=\name_valsupinf[2]}
}
\if{\cas=1}{
  \text{ulim=\k>0?\b,\b,\sa inf,\sa\infty:\soa inf,\soa\infty,\b,\b}
  \text{ucod=\k>0?\bc,\sa\ic:\soa\ic,\bc}
  \text{vlim=\k>0?-inf,-\infty,+inf,+\infty:+inf,+\infty,-inf,-\infty}
  \text{vcod=\k>0?-1,1:1,-1}
}
\if{\cas=2}{
  \integer{b2=(\b)^2}
  \integer{tmp=\b=0?0:2}
  \text{ulim=\k>0?\b2,\b2,+inf,+\infty:+inf,+\infty,\b2,\b2}
  \text{ucod=\k>0?\tmp,1:1,\tmp}
  \text{vlim=\k>0?-inf,-\infty,+inf,+\infty:+inf,+\infty,-inf,-\infty}
  \text{vcod=\k>0?-1,1:1,-1}
}
\if{\cas=3}{
  \rational{ib=1/(\b)}
  \integer{s=\x1>0?1:-1}
  \integer{s=\x1=0?0}
  \if{\k>0}{
    \text{lim1=\s>0?\x0}
  \text{tolim1=\s>0?\begin{array}{l}x\to \x0\\x > \x0\end{array}}
  }{
  \text{lim2=\s>0?\x0}
  \text{tolim2=\s>0?\begin{array}{l}x\to \x0\\x < \x0\end{array}}}
  \if{\k>0}{
    \text{tmp=\s>=0?\sa inf,\sa\infty:\ib,\ib}
    \text{tc=\s>=0?\sa\ic:\bc}
  }{
    \text{tmp=\s>=0?\soa inf,\soa\infty:\ib,\ib}
    \text{tc=\s>=0?\soa\ic:\bc}
  }
  \text{ulim=\k>0?\tmp,0,0:0,0,\tmp}
  \text{ucod=\k>0?\tc,0:0,\tc}
  \text{c=ln(\x1)}
  \text{tc=\ln(\x1)}
  \text{cc=\x1>1?2:-2}
  \text{cc=\x1=1?0}
  \if{\k>0}{
    \text{vlim=\s=1?\c,\tc,+inf,+\infty:-inf,-\infty,+inf,+\infty}
    \text{vcod=\s=1?\cc,1:-1,1}
    }{
    \text{vlim=\s=1?+inf,+\infty,\c,\tc:+inf,+\infty,-inf,-\infty}
    \text{vcod=\s=1?1,\cc:1,-1}
  }
}
\text{ensdef=&#93; \lim1 ; \lim2 &#91; }
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
\integer{rep5=\tmp=0?2:1}
\text{sol5=item(\rep5,\name_choice2)}
\if{\tmp=0}{
  \text{fl1=0,0}
}{
  \if{\tmp>0}{\text{fl1=+inf,+\infty}}{\text{fl1=-inf,-\infty}}
}
\integer{tmp=\ul2*\vl2}
\integer{rep7=\tmp=0?2:1}
\if{\tmp=0}{\text{fl2=0,0}}
{\if{\tmp>0}{\text{fl2=+inf,+\infty}}{\text{fl2=-inf,-\infty}}}
\text{rep6=item(1,\fl1)}
\text{sol6=item(2,\fl1)}
\text{rep8=item(1,\fl2)}
\text{sol8=item(2,\fl2)}

#include "calc.inc"
