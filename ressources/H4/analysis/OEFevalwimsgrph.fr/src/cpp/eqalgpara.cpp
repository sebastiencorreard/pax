target=eqalgpara1 eqalgpara2 eqalgpara3 eqalgpara4 eqalgpara5
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_eqalgpara4
\integer{dena=random(1,1,1,1,1,2,2,3,3,4,5)}
\integer{denb=random(1,1,1,1,1,2,2,3,3,4,5)}
\integer{denc=random(1,1,1,1,1,4,4,9,9)}
\integer{dend=random(1,1,1,1,1,2,2,3,3,4,5)}
\integer{dene=random(1,1,1,1,1,2,2,3,3,4,5)}
\integer{denf=random(1,1,1,1,1,2,2,3,3,4,5)}
#else
\integer{dena=1}
\integer{denb=1}
\integer{denc=1}
\integer{dend=1}
\integer{dene=1}
\integer{denf=1}
#endif
\integer{numa=randint(1..10)*random(1,-1)}
\rational{a=simplify(\numa/(\dena))}

\integer{numb=randint(1..10)*random(1,-1)}
\rational{b=simplify(\numb/(\denb))}

\integer{rnumc=randint(1..10)}
\integer{numc=\rnumc^2*random(1,-1)}
\rational{c=simplify(\numc/(\denc))}

\integer{numd=randint(1..10)*random(1,-1)}
\rational{d=simplify(\numd/(\dend))}

\integer{nume=randint(1..10)*random(1,-1)}
\rational{e=simplify(\nume/(\dene))}

\integer{numf=randint(1..10)*random(1,-1)}
\rational{f=simplify(\numf/(\denf))}

\integer{g=randint(2..5)*random(1,-1)}

#if defined TARGET_eqalgpara1
\rational{cc=\a*(\c)}
\text{equat= \a*x^2 - \cc}
\text{equat=\(texmath(\equat=0))}
\if{\c>0}{
 \rational{sol1=\rnumc}
 \rational{sol2=\sol1*(-1)}
 \text{goodrep=\sol1,\sol2}
 \text{tsol=\equat \(\Leftrightarrow \a x^2=\cc \Leftrightarrow x^2=\c \Leftrightarrow x=\rnumc) ou \(x=-\rnumc)}
 }{
 \text{goodrep=vide}
 \text{tsol=\equat \(\Leftrightarrow \a x^2=\cc ) Or un carré est toujours positif donc il n'y a pas de solution.}
 }
#endif
#if defined TARGET_eqalgpara2
\integer{b=\numb}
\text{equat= (\a*x+\b)^2 }
\text{eq1=texmath(\a*x+\b)}
\text{equat=\(texmath(\equat=\c))}
\if{\c>0}{
 \rational{sol1=(\rnumc-\b) / (\a)}
 \rational{sol2=(-\rnumc-\b) / (\a)}
 \text{goodrep=\sol1,\sol2}
 \text{tsol=\equat \(\Leftrightarrow \eq1=\rnumc) ou \(\eq1=-\rnumc)<br>
 On est donc ramené à résoudre deux équations du premier degré.}
 }{
 \text{goodrep=vide}
 \text{tsol=un carré est toujours positif donc il n'y a pas de solution.}
 }
#endif
#if defined TARGET_eqalgpara3
\text{equat= \a*x^2+\b*x }
\text{eq1=texmath(\a*x+\b)}
\text{equat=\(texmath(\equat=0))}
\rational{sol1=-\b/(\a)}
\rational{sol2=0}
  \text{goodrep=\sol1,\sol2}
\text{tsol=Dans ce genre d'équation, il faut mettre \(x) en facteur:<br>
\equat \(\Leftrightarrow x(\eq1)=0 \Leftrightarrow x=0) ou \(x=\sol1)}
#endif

#if defined TARGET_eqalgpara4
\text{equat= (\a*x+\b)*(\c*x+\d) }
\text{equat=\(texmath(\equat=0))}
\rational{sol1=-\b/(\a)}
\rational{sol2=-\d/(\c)}
\if{\sol1=\sol2}{
  \text{goodrep=\sol1}
  }{
  \text{goodrep=\sol1,\sol2}
  }
\text{tsol=Un produit de facteur est nul si et seulement si l'un des facteurs est nul.<br>
  On résoud séparemment deux équations du premier degré.}
#endif

#if defined TARGET_eqalgpara5
\integer{k=random(1..3)}
\text{equat1= (\a*x+\b)*(\c*x+\d) }
\text{eq1=texmath(\a*x+\b)}
\rational{sol1=-\b/(\a)}
\if{\k=1}{
  \text{equat2= (\a*x+\b)*(\e*x+\f) }
  \rational{sol2=(\f - (\d))/(\c - (\e))}
  \text{eq2=texmath((\c*x+\d)-(\e*x+\f))}
 \integer{a2=\c-\e}
 \integer{b2=\d-\f}
  \text{eq3=texmath(\a2*x+\b2)}
 }
\if{\k=2}{
  \text{equat2= (\a*x+\b)^2 }
  \rational{sol2=(\b - (\d))/(\c - (\a))}
  \text{eq2=texmath((\c*x+\d)-(\a*x+\b))}
 \integer{a2=\c-\a}
 \integer{b2=\d-\b}
  \text{eq3=texmath(\a2*x+\b2)}
 }
\if{\k=3}{
  \text{equat2= \g*(\a*x+\b) }
  \rational{sol2=(\g - (\d))/(\c)}
  \text{eq2=texmath((\c*x+\d)-\g)}
 \integer{a2=\c}
 \integer{b2=\d-\g}
  \text{eq3=texmath(\a2*x+\b2)}
 }

\text{equat=\(texmath(\equat1=\equat2))}
\if{\sol1=\sol2}{
  \text{goodrep=\sol1}
  }{
  \text{goodrep=\sol1,\sol2}
  }
\text{tsol=Pour résoudre ce genre d'équation, il faut factoriser.
<ul>
<li> Tout regrouper à gauche: \(\equat1 - \equat2=0)</li>
</li><li> Factoriser: \((\eq1)[\eq2]=0 \Leftrightarrow (\eq1)(\eq3)=0)
</li><li> Résoudre plusieurs équations du premier degré:<br>
 \(\eq1=0) ou \(\eq3=0)</li>
</ul>}
#endif
#if defined TARGET_eqalgpara6
\rational{ag=\a*\g}
\rational{bg=\b*\g}
\integer{k=random(1..3)}
\text{equat1= (\ag*x+\bg)*(\c*x+\d) }
\rational{sol1=-\b/(\a)}
\if{\k=1}{
  \text{equat2= (\a*x+\b)*(\e*x+\f) }
  \rational{sol2=(\f - (\d)*(\g))/(\c*(\g) - (\e))}
 }
\if{\k=2}{
  \text{equat2= (\a*x+\b)^2 }
  \rational{sol2=(\b - (\d)*(\g))/(\c*(\g) - (\a))}
 }
\if{\k=3}{
  \text{equat2= \e*(\a*x+\b) }
  \rational{sol2=(\e - (\d)*(\g))/((\c)*(\g))}
 }

\text{equat=\(texmath(\equat1=\equat2))}
\if{\sol1=\sol2}{
  \text{goodrep=\sol1}
  }{
  \text{goodrep=\sol1,\sol2}
  }
#endif
\statement{
  Résoudre dans \(\ \RR) l'équation:
<div class="wimscenter"> \equat .</div>
<div class="wims_instruction"> S'il n'y a pas de solution, taper <span class="tt">vide</span>.<br>
  S'il y a plusieurs solutions, les séparer par une virgule.<br>
  Pour saisir une racine carrée, taper <span class="tt">sqrt(..)</span>,
  par exemple, taper <span class="tt">sqrt(2)</span> pour saisir \(\sqrt{2}).
</div>
<div class="wimscenter"><label for="reply1">S=</label>\embed{reply1}</div>
<div class="wimscenter"><b>Brouillon</b></div>
<div class="wimscenter">\embed{reply2,10x30}</div>
}
\answer{Solution(s)}{\goodrep}{type=fset}
\answer{}{\rien}{type=draft}{option=default=empty}
\solution{\tsol}
