target=compln
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

\rational{x0=-\b/\a}
\text{inf=&#8734;}
\text{sx=\a>0?+:-}
\integer{ssx=(\sx issametext +)?1:-1}
\text{xinf=\sx\inf}
\text{texinf=\sx\infty}
\text{ensdef=\a>0? &#93; \(\x0\) ; \xinf &#91; }
\text{natlim=\a>0?\name_valsupinf[1]:\name_valsupinf[2]}
\text{ineg=\a>0?>:<}
\text{ensdef=\a<0? &#93;\xinf ; \(\x0\) &#91; }
\integer{cas=randitem(1,2)}
\text{xlim=item(\cas,\x0,\xinf)}
\text{texlim=item(\cas,\x0,\texinf)}
\function{u=maxima(expand(\a*x + \b))}
\text{u=texmath(\u)}
\text{g=\ln(t)}
\text{gg=\ln(u)}
\text{ggx=\ln(u(x))}
\function{lnu=\ln(\u)}
\function{funct=\lnu}
\text{f=item(\op,\tk \lnu, \frac{\k}{\lnu})}
\text{ff=item(\op, k \gg, \frac{k}{\gg})}
\text{tf=texmath(\f)}
\if{\cas=1}{\text{ulim=0,0}}
{\text{ulim=+inf,+\infty}}
\text{rep3=item(1,\ulim)}
\text{sol3=item(2,\ulim)}
\if{\cas=1}{
\text{xtol=\begin{array}{l}x\to \x0\\x \ineg\x0\end{array}}
\text{ttol=\begin{array}{l}t\to 0\\t > 0\end{array}}
 }{
\text{xtol=x\to\texlim}
\text{ttol=t\to\sol3}
}
\text{glim=\rep3 issametext 0?-inf,-\infty:+inf,+\infty}
\text{invlim=0}
\text{neginvlim=0}
\text{neglim=\rep3 issametext 0?+inf:-inf}
\text{rep4=item(1,\glim)}
\text{sol4=item(2,\glim)}

\text{rep5=\rep4}
\text{sol5=\sol4}
\text{deduc2=wims(replace internal XXXX by in \name_deduc2)}

\if{\op=1}
{\text{rep6=\k>0?\rep5:\neglim}}
{\text{rep6=\k>0?\invlim:\neginvlim}}

\text{natlim=\cas=1? \natlim.:.}

#include "compstat.inc"
