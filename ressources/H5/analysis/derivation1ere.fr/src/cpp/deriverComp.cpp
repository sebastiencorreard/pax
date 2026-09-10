target=deriverComp

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format	{html}

\integer{a1=random(1..8)*random(1,-1)}
\integer{a2=random(1..8)*random(1,-1)}
\integer{k=random(1..8)*random(1,-1)}

\function{u= \a1*x+\a2}

\rational{zero=-\a2/\a1}

\function{flist= sqrt(\u),
 \k/(\u),
 \k*(\u)^random(2,3),
 (\u)^random(2,3)+\k,
}

\integer{casf=random(1..4)}

\function{f=item(\casf,\flist)}
\function{F=diff(\f,x)}

\text{inf=&#8734;}

/** casdef1 : intervalle de definition dans le cas d'une racine **/
\text{borne1=\casf==1 and \a1>0?\(\zero)}
\text{borne2=\casf==1 and \a1>0?+\inf}
\text{borne2=\casf==1 and \a1<0?\(\zero)}
\text{borne1=\casf==1 and \a1<0?-\inf}

/** casdef2 : valeur interdite dans le cas d'un inverse **/

\text{ensdef=\casf==1?&#93; \borne1 &#44; \borne2 &#91;}
\text{ensdef=\casf==2? \(\RR \setminus \{\zero\}\)}
\text{ensdef=\casf>2? \(\, \RR\) }
\statement{
<div class="wims_question">
\name_question[1] \ensdef \name_question[2] \(f(x) = \f \) :
<div class="wimscenter"> \(f'(x)\) = \embed{reply1, 40}</div>
</div>
\if{\casf==1}{
  <div class="wims_instruction">
    \name_write "sqrt(a x+b)" \name_for \(sqrt(a x+b))</div>}
}

\answer{name_answer \(f'(x)\)}{\F}{type=formal}

\hint{\name_hint}

\feedback{0==0}{\name_feed: \(f'(x) = \F\).}
