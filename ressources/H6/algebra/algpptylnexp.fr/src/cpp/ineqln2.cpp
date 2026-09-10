target=ineqln2
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{sa=random(1,-1)}
\integer{a=random(1..15)*\sa}
\integer{sb=random(1,-1)}
\integer{b0=random(1..50)}
\integer{b=\b0*\sb}
\integer{sc=random(1,-1)}
\integer{c=random(1..15)*\sc}
\integer{d=random(-50..50)}
\text{x=randitem(x,y,z,t)}
\function{u=(\b=0)?\a\x:\a\x+\b}
\text{utex=texmath(\u)}
!!!! inequation cln(ax+b) symb d

\text{symb=randitem(<,>)}
\text{pos=position(\symb,<,>)}
\text{symb0=\a>0?>:<}
\rational{rep0=-\b/\a}

!!! chgment sens inégalité
\text{symb1=(\c>0)?\symb}
\text{symb1=(\c<0 && \pos=1)?item(2,<,>)}
\text{symb1=(\c<0 && \pos=2)?item(1,<,>)}
\rational{rep1=\d/\c}
\integer{chge=\a*\c}
\text{symb2=(\chge>0)?\symb}
\text{symb2=(\chge<0 && \pos=1)?item(2,<,>)}
\text{symb2=(\chge<0 && \pos=2)?item(1,<,>)}
\function{rep2=(exp(\rep1)-\b)/(\a)}
\text{oppb=(\b<0)?+\b0:-\b}
\text{texrep2=\frac{e^{\rep1} \oppb}{\a}}
\text{ineq=\c*ln(\u) \symb \d }

!!! intervalle des solutions ;
!!! alpha (la lettre!) designe rep2 pour alléger l'ecriture des solutions

\if{\symb0 issametext \symb2}{
  \if{\symb0 issametext <}{
    \integer{enssol=4}
    \text{borne=(\rep0<\rep2)?\rep0:\alpha}
  }{
    \integer{enssol=3}
    \text{borne=(\rep0<\rep2)?\alpha:\rep0}
  }
}{
  \if{\symb0 issametext <}{
    \integer{enssol=(\rep0<\rep2)?1:2}
  }{
    \integer{enssol=(\rep0<\rep2)?2:1}}
}

\statement{
<div>On veut résoudre dans \(\mathbb{R}\) l'inéquation (I) : \(\ineq) .
</div>
<p>Résolvez (I) sur papier libre,
puis complétez les affirmations suivantes.
</p>
<div class="wims_instruction">
Pour écrire \(e^{a}) vous devez entrer <span class="tt">exp(a) ou e^(a)</span>
et de préférence la formule exacte.
</div>
<ol><li>
Le premier membre de (I) est défini si et seulement si \(\x\) \embed{choice1} \embed{reply1,5}.
</li><li>
La condition 1. étant vérifiée, on peut écrire les équivalences suivantes :
<div class="wimscenter">
  (I) \(\Longleftrightarrow ln(\utex)\)
  \embed{choice2} \embed{reply2,5}
</div>
<div class="wimscenter">
  (I) \(\Longleftrightarrow \x \) \embed{choice3} \embed{reply3,20}
</div>
</li><li>
L'ensemble des solutions de (I) est
  \embed{reply4}
</li></ol>
}

\choice{ensdef1}{\symb0}{<,>}
\answer{ensdef2}{\rep0}{type=numexp}
\choice{step1}{\symb1}{<,>}
\answer{step1}{\rep1}{type=numexp}
\choice{step2}{\symb2}{<,>}
\answer{step2}{\rep2}{type=function}
\answer{ensblesol}{\enssol;vide, un gle borné, un intervalle &#93;&#945;&#160;&#59;&#160;+&#8734;&#91;, un intervalle &#93;-&#8734;&#160;&#59;&#160;&#945;&#91;}{type=menu}

\feedback{0=0}{
#include "feed2.inc"
}
