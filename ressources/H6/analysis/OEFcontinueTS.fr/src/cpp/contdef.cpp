target=contdef1 contdef2
#include "author.inc"
\keywords{real_function,continuity}
#include "lang_titles.inc"
#include "lang.inc"
\text{lstrep=\name_operation[1] \(u+v\), \name_operation[2] \(u \times v\),\name_operation[3] \(\frac{u}{v}\),
  \name_operation[4] \(u \circ v\)}
\integer{a=randint(1..5)*randint(1,-1)}
\integer{b=randint(-5..5)}
\text{size=80x50x1}
#if defined TARGET_contdef1
\observation{Les fonctions de bases sont les fonctions affine, cosinus, sinus, racine carrée, puissance, 1/x.}
\text{data=abs(x),\a*x+\b,cos(x),sin(x),1/x,sqrt(x),(x+1)^2,x^7}
#endif
#if defined TARGET_contdef2
\observation{Aux fonctions de base de l'exercice TITLE 2, s'ajoutent les fonctions exp et ln.}
\text{data=abs(x),\a*x+\b,cos(x),sin(x),1/x,sqrt(x),(x+1)^2,x^7,exp(x),ln(x)}
#endif
\integer{nb=items(\data)}
\text{ind=shuffle(\nb)}

\text{u=\data[\ind[1]]}
\text{v=\data[\ind[2]]}
\text{u=maxima(\u)}
\text{v=maxima(\v)}
\integer{rep1=randint(1,2,3,4,4,4)}
\if{\rep1=1}{
  \text{f=texmath(\u+\v)}
  \text{ft=\f}
}
\if{\rep1=2}{
  \text{f=texmath((\u)*(\v))}
  \text{ft=\f}
}
\if{\rep1=3}{
  \text{fn=texmath(\u)}
  \text{fd=texmath(\v)}
  \text{ft=\frac{\fn}{\fd}}
}
\if{\rep1=4}{
  \text{f=wims(replace internal x by (\v) in \u)}
  \text{f=texmath(\f)}
  \text{ft=\f}
}
\text{lstf=&#124; x &#124;}
\for{i= 2 to \nb}{
 \text{g=texmath(maxima(\data[\i]))}
 \text{lstf=wims(append item \(\g) to \lstf)}
}
\statement{
  \name_enonce[1] \(x \mapsto \ft\) \name_enonce[2]:
<div class="wimscenter"> \embed{reply1}</div>
  \name_enonce[3]<ul><li>
\(u : x \mapsto\) \embed{reply2,\size}</li><li>
\(v : x \mapsto\)  \embed{reply3,\size}</li></ul>
<div class="wims_instruction">\name_instruction</div>
}
\answer{raison}{\rep1;\lstrep}{type=radio}
\answer{u}{\fu;\lstf}{type=clickfill}
\answer{u}{\fv;\lstf}{type=clickfill}
\condition{Bonnes expressions pour \(u\) et \(v\)}{(\fu issametext \lstf[\ind[1]] and \fv issametext \lstf[\ind[2]]) or (\rep1<3 and \fu issametext \lstf[\ind[2]] and \fv issametext \lstf[\ind[1]])}
