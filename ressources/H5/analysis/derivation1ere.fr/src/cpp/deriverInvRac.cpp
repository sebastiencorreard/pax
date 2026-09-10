target=deriverInvRac

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format	{html}

\integer{a=random(1..8)*random(1,-1)}
\integer{b=random(1..8)*random(1,-1)}
\integer{b2= (\b)^2}
\integer{k=random(1..8)*random(1,-1)}

\function{us= \a*x+\b, (\a*x+\b)^2 , x^2 + \b2 }

\integer{casu=random(1..3)}
\function{u = item(\casu , \us)}
\rational{zero=-\b/\a }

\function{fs= \k*sqrt(\u), \k/(\u)}

\integer{casf=random(1..2)}
\function{f=item(\casf,\fs)}

\function{F=diff(\f,x)}
/** bornes de l'intervalle où (a x + b) est strict. positif **/
\text{borne1= \a>0?\zero:-\infty}
\text{borne2= \a>0?+\infty:\zero}
/** ens de dérivabilité **/
\text{ensdef=\(\,\RR\) }

\text{ensdef=\casf==1 and \casu==1? \( &#93; \borne1 ; \borne2 &#91; \) }
\text{ensdef=(\casf==2 and \casu!=3) or (\casf==1 and \casu==2)? \(\RR \setminus \{\zero\}\) }

\statement{
<div class="wims_question">
\name_enonce[1]
 \(f(x) = \f \) \name_enonce[2] \( I\) = \ensdef.
<div>\name_onehas \name_for \(x \in I\)
<label for="reply1">\(f'(x)\)</label> = \embed{reply1 , 40}</div>
</div>
\if{\casf==1}
{<div class="wims_instruction">
  \name_write "sqrt(a x + b)" \name_for \(sqrt(a x + b)\).
  </div>}

}

\answer{name_answer \(f'(x)\)}{\F}{type=formal}
\hint{
<p>\name_hint1</p>
<p>\name_hint2</p>
}

\feedback{0==0}{\name_feed: \(f'(x) = \F\).}
