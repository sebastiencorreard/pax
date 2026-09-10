target=varInvRac

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format	{html}

\integer{a=random(1..8)*random(1,-1)}
\integer{b=random(1..8)*random(1,-1)}
\integer{b2= (\b)^2}
\integer{k=random(1..8)*random(1,-1)}

\function{u= \a*x+\b}

\rational{zero=-\b/\a }

\function{fs= sqrt(\u), 1/(\u) , (\u)^2}

\integer{casf=random(1..3)}
\function{f=item(\casf,\fs)}

\function{F=diff(\f,x)}


/** bornes de  l'intervalle  où (a x + b) est strict. positif **/
\text{borne1= \a>0?\zero:-\infty}
\text{borne2= \a>0?+\infty:\zero}

/** bornes de  l'intervalle où (a x + b) est strict. negatif **/
\text{borne3= \a>0?-\infty:\zero}
\text{borne4= \a>0?\zero:+\infty}

\text{I=\( &#93; \borne1 ; \borne2 &#91; )}
\text{J=\( &#93; \borne3 ; \borne4 &#91; )}

/** ens de dérivabilité **/
\text{ensdef= \casf==1? \( &#93; \borne1 ; \borne2 &#91; \) }
\text{ensdef= \casf==2? \(\RR \setminus \{\zero\}\) }
\text{ensdef= \casf==3? \(\,\RR\) }

/** choix de la bonne réponse **/
\if{\casf==1}{
  \integer{rep1=\a>0 ? 1}
  \integer{rep1=\a<0 ? 2}
  \integer{rep2=3}
}
\if{\casf==2}{
  \integer{rep1=\a>0 ? 2}
  \integer{rep1=\a<0 ? 1}
  \integer{rep2=\rep1}
}
\if{\casf==3}{
  \integer{rep1=\a>0 ? 1}
  \integer{rep1=\a<0 ? 2}
  \integer{rep2=\a>0 ? 2}
  \integer{rep2=\a<0 ? 1}
}
\statement{
  <div class="wims_question">
  \name_enonce[1] \ensdef \name_enonce[2] \(f(x) = \f\).
  <div>
  \name_question[1] \I, \name_question[2] \embed{reply1}.</div>
  <div>\name_question[1] \J,
  \name_question[2] \embed{reply2}.</div>
  </div>
}

\answer{\name_answer I }{\rep1 ; \name_choix}{type=radio}
\answer{\name_answer J }{\rep2 ; \name_choix}{type=radio}
\hint{
<p>\name_hint1</p>
<p>\name_hint2</p>
<p>\name_hint3</p>}
