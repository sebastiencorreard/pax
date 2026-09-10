target=deflim1 deflim2 deflim3
\format{html}
#define TITLE Limites: Définition
#if defined TARGET_deflim1
# define NUM 1
#endif
#if defined TARGET_deflim2
# define NUM 2
#endif
#if defined TARGET_deflim3
# define NUM 3
#endif
\title{TITLE NUM}
#include "author.inc"
#if defined TARGET_deflim1
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)}
\integer{d=randint(1..9)}
\text{u=texmath((\a*n+\b)/(\c*n+\d))}
\text{defsuite=\(u_n=\u\) pour tout \(n \in \mathbb{N}\)}
\rational{l=simplify(\a/\c)}
\integer{p=randint(-4..-2)}
\text{e=10^{\p}}
\text{ep=10^{-p}}
\text{n00=-\d/\c+abs((\b-(\l)*\d)*10^(-(\p))/\c)}
\integer{n0=ceil(\n00)}
\integer{n0=pari(\n0==\n00)=1 ? \n0+1}

\statement{
  On considère la suite \((u_n)\) définie par :
  <div class="wimscenter"> \defsuite.</div>
  On veut montrer que sa limite est \(\l\).<br>
  Pour cela, étant donné un entier positif \(p\), il existe un rang \(n_0\)
   à partir duquel tous les termes de la suite sont dans l'intervalle
  <div class="wimscenter"> &#93; \(\,\l-\epsilon\);\(\,\l+\epsilon) &#91;</div>
  avec \(\,\epsilon=\ep\).
  Déterminer le plus petit entier \(n_0\) vérifiant cette propriété pour \(\epsilon=\e\).
  <div class="wimscenter"><label for="reply1">\(n_0\)=</label>\embed{reply1}.</div>
}

\answer{Rang \(n_0\)}{\n0}{type=numeric}
\hint{Calculer \(v_n = |u_n - \l|\). Trouver le plus entier \(n_0\)
  tel que \(v_n\) soit majoré par \(\e\).}
#endif
#if defined TARGET_deflim2
\integer{a=randint(1..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
\integer{d=randint(1..9)}
\integer{e=randint(1..9)}
 \text{u=texmath((\a*n^2+\b*n+\c)/(\d*n+\e))}
 \text{defsuite=\(u_n=\u\) pour tout \(n \in \mathbb{N}\)}
\text{l=\a>0?\(+\infty\):\(-\infty\)}
\text{inter=\a>0?&#93; \(A\); \(+\infty\) &#91;:&#93; \(-\infty\);\(A\) &#91;}
\text{signe=\a>0?positif:négatif}
\integer{p=randint(2..3)}
\text{A=\a>0?10^\p:-10^\p}
\integer{delt=(\b-\A*\d)^2-4*\a*(\c-\e*\A)}
\integer{n1=ceil((-\b+\A*\d+sqrt(\delt))/(2*\a))}
\integer{n2=ceil((-\b+\A*\d-sqrt(\delt))/(2*\a))}
\integer{n0=\n1>\n2?\n1:\n2}

\statement{
  On considère la suite \((u_n)\) définie par :
  <div class="wimscenter"> \defsuite.</div>

  On veut montrer que cette suite diverge et que sa limite est \l.<br>
  Pour cela, étant donné un entier \signe \(A\), il existe un rang \(n_0\)
  à partir duquel tous les termes de la suite sont dans l'intervalle
  <div class="wimscenter">\inter.</div>
  Déterminer le plus petit entier \(n_0\) vérifiant cette propriété pour \(A=\A\).
  <div class="wimscenter"><label for="reply1">\(n_0\)=</label>\embed{reply1} </div>
}
\answer{Rang \(n_0\)}{\n0}{type=numeric}
#endif
#if defined TARGET_deflim3
\rational{l=simplify(randint(-5..5)/randint(1,1,1,2,3))}
\rational{e=randint(1,1/2,10^(-8))}
\integer{n0=randint(10,1000,4000)}
\text{data=abs(u-\l)<\e,n<\n0,la suite converge vers \l, la suite ne converge pas vers \l, la suite diverge, on ne peut rien dire,4,
abs(u-\l)<\e,n>\n0,la suite converge vers \l, la suite ne converge pas vers \l, la suite diverge, on ne peut rien dire,4,
abs(u-\l)>\e,n>\n0,la suite converge vers \l, la suite ne converge pas vers \l, la suite diverge, on ne peut rien dire,2,
abs(u-\l)<\e/n,n>\n0,la suite converge vers \l, la suite ne converge pas vers \l, la suite diverge, on ne peut rien dire,1,
abs(u-\l)<\e/n,n<\n0,la suite converge vers \l, la suite ne converge pas vers \l, la suite diverge, on ne peut rien dire,4,
abs(u-\l)>\e/n,n>\n0,la suite converge vers \l, la suite ne converge pas vers \l, la suite diverge, on ne peut rien dire,4,
}
\text{cedata=randomrow(\data)}
\text{equa=texmath(maxima(\cedata[1]))}
\text{equa=wims(replace internal u by u_n in \equa)}
\text{cond=texmath(\cedata[2])}
\text{rep=item(3..-1,\cedata)}
\integer{nbr=items(\rep)-1}
\integer{irep=item(\nbr,\rep)}
\text{lstrep=item(1..\nbr-1,\rep)}

\statement{
  On considère une suite \((u_n)\), qui vérifie :
  <div class="wimscenter"> \(\equa\) pour tout \(\cond\)</div>
  Que peut-on dire de cette suite ?
  <div class="wims_instruction">Choisir l'affirmation la plus pertinente.</div>
  <ul>
  \for{i=1 to \nbr-1}{
  <li>\embed{reply1,\i}</li>
  }
  </ul>
}
\answer{}{\irep;\lstrep}{type=radio}
#endif
