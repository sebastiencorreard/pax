target=compoexp
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{a = random(-1,1)*random(1..5)}
\integer{b = random(-8..8)}
\integer{k=random(-1,1)*random(1..8)}
\text{tk=\k}
\text{tk=\k=-1?-}
\text{tk=\k=1?}
\integer{op=randitem(1,2)}

\function{u=maxima(expand(\a*x + \b))}
\text{u=texmath(\u)}
\text{g=e^{t}}
\text{gg=e^{u}}
\text{ggx=e^{u(x)}}
\function{expu=e^{\u}}
\function{funct=\expu}
\text{f=item(\op,\tk \expu, \frac{\k}{\expu})}
\text{ff=item(\op, k \gg, \frac{k}{\gg})}
\text{tf=texmath(\f)}

\text{inf=&#8734;}
\text{sx=random(-,+)}
\integer{ssx=(\sx issametext +)?1:-1}
\text{xlim=\sx\inf}
\text{texlim=\sx\infty}
\text{ensdef=\(\,\RR\)}

\text{ulim=(\a*\ssx)>0?+inf,+\infty:-inf,-\infty}
\text{rep3=item(1,\ulim)}
\text{sol3=item(2,\ulim)}
\text{xtol=x\to\texlim}
\text{ttol=t\to\sol3}
\text{glim=\rep3 issametext -inf?0,0:+inf,+\infty}
!!!!\text{neglim=\rep3 issametext -inf?-inf:0}
\text{neglim=\rep3 issametext -inf?0:-inf}
\text{invlim=\rep3 issametext -inf?+inf:0}

\text{neginvlim=\rep3 issametext -inf?-inf:0}
\text{rep4=item(1,\glim)}
\text{sol4=item(2,\glim)}

\text{rep5=\rep4}
\text{sol5=\sol4}
\text{deduc2=wims(replace internal XXXX by \(\displaystyle \lim_{\ttol} \g = \sol4\) in \name_deduc2)}

\if{\op=1}
{\text{rep6=\k>0?\rep5:\neglim}}
{\text{rep6=\k>0?\invlim:\neginvlim}}

\text{natlim=.}

#include "compstat.inc"
