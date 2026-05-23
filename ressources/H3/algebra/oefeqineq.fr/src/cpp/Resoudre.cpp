target= resoudre1 resoudre2 resoudre3
#include "author.inc"
#if defined TARGET_resoudre1
# define NUM
#endif
#if defined TARGET_resoudre2
# define NUM x^2-b^2&#61;0
#endif
#if defined TARGET_resoudre3
# define NUM x^2-b&#61;0
#endif
#include "lang_titles.inc"
#include "lang.inc"


\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

#include "valeurs.inc"

\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\text{c=item(3,\valeurs)}
\text{d=item(4,\valeurs)}
\text{e=item(5,\valeurs)}
\text{f=item(6,\valeurs)}

\if{\confparm1>=5}{
  \integer{ai=100*\a}
  \integer{bi=100*\b}
  \integer{ci=100*\c}
  \integer{di=100*\d}
  \integer{ei=100*\e}
  \integer{fi=100*\f}
}{
  \text{ai=\a}
  \text{bi=\b}
  \text{ci=\c}
  \text{di=\d}
  \text{ei=\e}
  \text{fi=\f}
}
\text{var=randitem(x,y,a,b)}

#if defined TARGET_resoudre1
\text{tmp1=\a*\var+(\b)}
\text{tmp2=\c*\var+(\d)}
\text{tmp3=\e*\var+(\f)}
\if{\c+(\e)=0 or  \c-(\e)=0}{\text{e=2}\text{c=3}}

\matrix{donnees=(\tmp1)*(\tmp2)=0,simplify(-(\bi)/(\ai)),simplify(-(\di)/(\ci))
(\tmp1)*(\tmp2)+(\tmp3)*(\tmp1)=0,simplify(-(\bi)/(\ai)),simplify(-(\di+(\fi))/(\ci+(\ei)))
(\tmp1)*(\tmp2)-(\tmp3)*(\tmp1)=0,simplify(-(\bi)/(\ai)),simplify(-(\di-(\fi))/(\ci-(\ei)))}
#endif
#if defined TARGET_resoudre2
\if{\confparm1>=5}{
  \integer{Bi=\bi^2}
  \text{B=slib(decimal \Bi,4)}
  \integer{Ai=\ai^2}
  \text{A=slib(decimal \Ai,4)}
}{
  \text{A=simplify((\a)^2)}
  \text{B=simplify((\b)^2)}
}
\text{r1=simplify(-(\bi)/(\ai))}
\text{r2=simplify((\bi)/(\ai))}
\text{r3=simplify(-\b)}
\matrix{donnees=\A*\var^2-(\B)=0,\r1,\r2
\var^2-(\B)=0,\r3,\b
\B-(\A)*\var^2=0,\r1,\r2
\B-\var^2=0,\r3,\b}
#endif
#if defined TARGET_resoudre3
\text{a=simplify(abs(\a))}
\text{b=simplify(abs(\b))}
\if{\confparm1>=5}{
 \integer{Ai=\ai^2}
 \text{A=slib(decimal \Ai,4)}
 \text{ai=\ai/100}
 \text{bi=\bi/100}
 \text{ci=\ci/100}
 \text{di=\di/100}
 \text{ei=\ei/100}
 \text{fi=\fi/100}
}{
 \text{A=simplify((\a)^2)}
}
\matrix{donnees=\A*\var^2-\b=0,simplify(-sqrt(\bi)/(\ai)),simplify(sqrt(\bi)/(\ai))
\var^2-\b=0,simplify(-sqrt(\bi)),simplify(sqrt(\bi))
\a*\var^2-\b=0,simplify(-sqrt((\bi)/(\ai))),simplify(sqrt((\bi)/(\ai)))
\b-\A*\var^2=0,simplify(-sqrt(\bi)/(\ai)),simplify(sqrt(\bi)/(\ai))
\b-\var^2=0,simplify(-sqrt(\bi)),simplify(sqrt(\bi))
\b-\a*\var^2=0,simplify(-sqrt((\bi)/(\ai))),simplify(sqrt((\bi)/(\ai)))}
#endif

\text{don=randrow(\donnees)}
\text{enonce=texmath(item(1,\don))}
\text{rep=wims(item 2 to -1 of \don)}

\statement{
\name_question:
<div class="wimscenter">\(\enonce\)</div>
<label for="reply1">\name_question1</label> \embed{r1,10}.
<div class="wims_instruction">\name_instruction</div>
}

\answer{\var}{\rep}{type=fset}
