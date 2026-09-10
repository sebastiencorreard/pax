target=signeEvident
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = (-1)^random(0,1)*random(1..10)}
\integer{b = (-1)^random(0,1)*random(1..10)}
\integer{k = (-1)^random(0,1)*random(1..10)}
\integer{signk=\k<0?1:3}
\integer{signku2=\k<0?2:4}
\integer{k1=random(1..10)}
\integer{k2=random(1..10)}
\integer{n=random(2,4)}
\rational{zero=-\b/\a}
\function{u=\a *x + \b}
\function{u=\a==1?x + \b}
\function{u=\a==-1?-x + \b}
\text{ff=\k,\k(\u)^\n,\k1(\u)^\n + \k2,-\k1(\u)^\n - \k2}

\integer{cas=random(1..4)}
\text{f=item(\cas,\ff)}
\text{item1=\name_choix[1]}
\text{item2=\name_choix[2]}
\text{item3=\name_choix[3]}
\text{item4=\name_choix[4]}
\text{choix=\item1,\item2,\item3,\item4}
\text{reps=\signk,\signku2,3,1}
\text{rep=item(\cas,\reps)}
\text{question=wims(replace internal XXXX by \(f(x) = \f\) in \name_question)}

\statement{
  <div class="wims_question">
  <p>\question[1]</p>
  <div class="center">\(f(x)\) \question[2] \embed{reply1}.</div>
  </div>
}
\answer{}{\rep ; \choix}{type=menu}
\feedback{\reply1 notsametext item(\rep,\choix)}{
<div class="macorrection">
<strong>Explications :</strong>
\if{\cas==1}{\name_feed1[1;1] \(f(x) = \f\) \name_feed1[1;2] \(x\),
  \name_feed1[2;1] \(f(x)\) \name_feed1[2;2] \(\k\) \name_feed1[2;3] }
\if{\cas==2}{\name_feed1[1;1] \(f(x) = \f\) \name_feed1[1;2] \(x\).<br>
  \name_now \((\u)^\n\) \name_feed1[3;] \(x = \zero\),
  \name_feed1[2;1] \(f(x)\) \name_feed1[2;2] \(\k\) \name_feed1[4;] \(\zero\).}
\if{\cas==3}{ \(\k1(\u)^\n\) \name_feed1[3;] \(x = \zero\).<br>
  \name_feed1[5;1] \(\k2\) \name_feed1[5;2] \name_feed1[5;3]
  \(f(x) = \k1(\u)^\n + \k2\) \name_feed1[5;4], \name_feed1[1;2] \(x\).}
\if{\cas==4}{ \((\u)^\n\) \name_feed1[3;] \(x = \zero\).
  \name_feed1[2;1] \(-\k1(\u)^\n\) \name_feed1[6;].
  <br>\name_feed1[5;1] \(-\k2\) \name_feed1[7;]
  \(f(x) = -\k1(\u)^\n + (-\k2)\).
  \name_feed1[2;1] \(f(x)\) \name_feed1[8;] \name_feed1[1;2] \(x\).}
</div>}
