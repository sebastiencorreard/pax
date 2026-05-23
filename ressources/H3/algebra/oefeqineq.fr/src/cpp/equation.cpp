target=Equation3 Equation4 optrou3 optrou4 optrou5
#include "author.inc"
\precision{10000}
#if defined TARGET_Equation3 || defined TARGET_Equation4
# if defined TARGET_Equation3
#   define NUM ax&#61;b
# else
#   define NUM x+a&#61;b
# endif
#else
# define NUM
#endif
#include "lang_titles.inc"
#include "lang.inc"
\integer{sizef=4}

\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

#include "valeurs.inc"
\text{a=item(1,\valeurs)}
\text{b=item(2,\valeurs)}
\if{\confparm1>=5}{
 \integer{ai=100*\a}
 \integer{bi=100*\b}
}{
 \text{ai=\a}
 \text{bi=\b}
}
\text{x=randitem(x,y,z,a,b)}

#if defined TARGET_Equation3
\if{\confparm1>=5}{
  \integer{tmp=\ai*\bi}
  \text{tmp=slib(decimal \tmp,4)}
}{
  \text{tmp=simplify(\a*\b)}
}
\text{d=\b}
\text{enonce=\a*\x = \tmp}
\integer{test=1}
#endif
#if defined TARGET_Equation4
\if{\confparm1>=5}{
 \integer{tmp=(\bi)-(\ai)}
 \text{d=slib(decimal \tmp,2)}
}{
  \text{d=simplify((\b)-(\a))}
}
\text{enonce=\x+(\a)=\b}
\integer{test=1}
#endif
#if defined TARGET_optrou3
\if{\confparm1>=5}{
  \integer{tmp=\ai*\bi}
  \text{tmp=slib(decimal \tmp,4)}
}{
  \text{tmp=simplify(\a*\b)}
}
\text{d=\b}
\text{enonce1=texmath(\a)\times}
\text{enonce2=texmath(=\tmp)}
\integer{test=0}
#endif
#if defined TARGET_optrou4
\if{\confparm1>=5}{
  \integer{tmp=(\bi)-(\ai)}
  \text{d=slib(decimal \tmp,2)}
}{
  \text{d=simplify((\b)-(\a))}
}
\text{enonce1=texmath(\a)+}
\text{enonce2=texmath(=\b)}
\integer{test=0}
#endif
#if defined TARGET_optrou5
\if{\confparm1>=5}{
  \integer{tmp=(\ai)-(\bi)}
  \text{d=slib(decimal \tmp,2)}
}{
  \text{d=simplify(\a-(\b))}
}
\text{enonce1=texmath(\a)-}
\text{enonce2=texmath(=\b)}
\integer{test=0}
#endif

\text{enonce=texmath(\enonce)}
\statement{
\if{\test=1}{\name_question[1] \(\enonce).
<div class="wimscenter">
<label for="reply1">\(\x =\)</label> \embed{reply 1,\sizef}.
</div>
<div class="wims_instruction">\name_instruction</div>}
{\name_question[1]:
<label for="reply1">\(\enonce1\)</label> \embed{reply 1,\sizef} \(\enonce2).}}

\answer{\name_answer}{\d}{type=numexp}
