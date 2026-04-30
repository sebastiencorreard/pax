target=eqalghyper1 eqalghyper2 eqalghyper3 eqalghyper4 eqalghyper5
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_eqalghyper6
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

\integer{numc=randint(1..10)^2*random(1,-1)}
\rational{c=simplify(\numc/(\denc))}

\integer{numd=randint(1..10)*random(1,-1)}
\rational{d=simplify(\numd/(\dend))}

\integer{nume=randint(1..10)*random(1,-1)}
\rational{e=simplify(\nume/(\dene))}

\integer{numf=randint(1..10)*random(1,-1)}
\rational{f=simplify(\numf/(\denf))}

\integer{g=randint(2..5)*random(1,-1)}
\integer{h=randint(2..5)*random(1,-1)}

#if defined TARGET_eqalghyper1
\text{equat= (\a*x + \b)/(\c*x+\d)}
\text{equat=\(texmath(\equat=0))}
\rational{sol=simplify(-(\d)/(\c))}
\rational{bad1=0}
\rational{bad2=-\d}
\rational{bad3=simplify(-(\b)/(\a))}
\rational{bad4=simplify(-(\c)/(\d))}
\text{lstrep=\(texmath(\sol)),\(texmath(\bad1)),\(texmath(\bad2)),\(texmath(\bad3)),\(texmath(\bad4))}
\text{lstrep=wims(listuniq \lstrep)}
\integer{goodrep=position(\(texmath(\sol)),\lstrep)}
#endif
#if defined TARGET_eqalghyper2
\integer{k=random(1..3)}
\if{\k=1}{
   \text{equat= (\a*x + \b)/(\c*x+\d)}
   \text{equat=\(texmath(\equat=0))}
   \rational{sol=simplify(-(\d)/(\c))}
   \text{goodrep=\sol}
  }
\if{\k=2}{
   \text{equat= (\a*x + \b)/((\c*x+\d)*(\e*x+\f))}
   \text{equat=\(texmath(\equat=0))}
   \rational{sol1=simplify(-(\d)/(\c))}
   \rational{sol2=simplify(-(\f)/(\e))}
   \text{goodrep=\sol1,\sol2}
  }
\if{\k=3}{
   \text{equat1= (\a*x + \b)/(\c*x+\d)}
   \text{equat2= (\g*x + \h)/(\e*x+\f)}
   \text{equat=\(texmath(\equat1=\equat2))}
   \rational{sol1=simplify(-(\d)/(\c))}
   \rational{sol2=simplify(-(\f)/(\e))}
   \text{goodrep=\sol1,\sol2}
  }
#endif
#if defined TARGET_eqalghyper3
\integer{k=random(1..3)}
\if{\k=1}{
   \text{equat= (\a*x+\b)/(\c*x+\d) }
   \text{equat=\(texmath(\equat=0))}
   \rational{sol=-\b/(\a)}
   \text{goodrep=\sol}
  }
\if{\k=2}{
   \text{equat= (\a*x+\b)/((\c*x+\d)*(\g*x+\f)) }
   \text{equat=\(texmath(\equat=0))}
   \rational{sol=-\b/(\a)}
   \text{goodrep=\sol}
  }
\if{\k=3}{
   \text{equat= ((\a*x+\b)*(\c*x+\d))/(\g*x+\f) }
   \text{equat=\(texmath(\equat=0))}
   \rational{sol1=-\b/(\a)}
   \rational{sol2=-\d/(\c)}
   \rational{vi=-\f/(\g)}
   \text{badsol=\vi}
   \text{goodrep=\sol1,\sol2}
   \text{goodrep=wims(listcomplement \badsol in \goodrep)}
  }
#endif
#if defined TARGET_eqalghyper4
\integer{k=random(1..2)}
\if{\k=1}{
   \rational{dd=\a-(\e)*(\c)}
   \if{\dd=0}{
    \rational{a=\a+1}
    }
   \text{equat= (\a*x+\b)/(\c*x+\d) }
   \text{equat=\(texmath(\equat=\e))}
   \rational{sol=(\e*(\d)-(\b))/(\a-(\e)*(\c))}
   \text{goodrep=\sol}
  }
\if{\k=2}{
   \rational{dd=\a*(\f)-(\e)*(\c)}
   \if{\dd=0}{\rational{a=\a+1}}
   \text{equat1= \f/(\c*x+\d) }
   \text{equat2= \e/(\a*x+\b) }
   \text{equat=\(texmath(\equat1=\equat2))}
   \rational{sol=(\f*(\b)-(\e)*(\d))/(\e*(\c)-(\a)*(\f))}
   \text{goodrep=\sol}
  }
#endif
#if defined TARGET_eqalghyper5
\integer{a=randint(1..5)}
\integer{b=randint(1..5)*randint(1,-1)}
\integer{c=1}
\integer{d=randint(1..5)*randint(1,-1)}
\integer{d=(\b=\d and \a=\b)?-\d}
\integer{e=randint(1..5)}
\integer{f=randint(1..5)}
\integer{k=random(1,2)}
\if{\k=1}{
%%%% retirer la valeur interdite
   \rational{g=\a*(\b)/(\c)}
   \rational{h=(\b)^2-(\b)*(\a)*(\d)/(\c)}
   \text{equat1= \a*x/(\c*x+\d)- (\g)/(\a*x+\b) }
   \text{equat2= \h / ((\a*x+\b)*(\c*x+\d))}
   \rational{sol=\b/(\a)}
   \text{equat=\(texmath(\equat1=\equat2))}
   \text{goodrep=\sol}
  }{
%%%% 2 solutions
   \rational{n=(\e)^2}
   \rational{g=(\e)^2*(\b)/(\c)}
   \rational{h=(\f)^2*(\a)-(\b)*(\e)^2*(\d)/(\c)}
   \text{equat1= \n*x/(\c*x+\d)- (\g)/(\a*x+\b) }
   \text{equat2= \h / ((\a*x+\b)*(\c*x+\d))}
   \rational{sol1=\f/(\e)}
   \rational{sol2=\sol1*(-1)}
   \rational{int1=-\d / \c}
   \rational{int2=-\b / \a}
   \text{goodrep=}
   \if{\sol1<>\int1 and \sol1<>\int2}
     {\text{goodrep=wims(append item \sol1 to \goodrep)}}
   \if{\sol2<>\int1 and \sol2<>\int2}
     {\text{goodrep=wims(append item \sol2 to \goodrep)}}
   \text{equat=\(texmath(\equat1=\equat2))}
  }
#endif
\statement{
#if defined TARGET_eqalghyper1
  On considère l'équation quotient:
<div class="wimscenter"> \equat.</div>
  Cocher la valeur interdite.
<div class="wimscenter">\embed{reply1}</div>
#endif
#if defined TARGET_eqalghyper2
  On considère l'équation quotient:
<div class="wimscenter"> \equat.</div>
  Indiquer la ou les valeurs interdites:
<div class="wimscenter">\embed{reply1}</div>
#endif
#if (defined TARGET_eqalghyper3  || defined TARGET_eqalghyper4  || defined TARGET_eqalghyper5 )
  Résoudre dans \(\ \RR) l'équation quotient:
<div class="wimscenter"> \equat .</div>
<div class="wims_instruction"> S'il n'y a pas de solution taper <span class="tt">vide</span>.
<br>
  S'il y a plusieurs solutions, les séparer par une virgule.<br>
  Pour saisir une racine carrée, taper <span class="tt">sqrt(..)</span>,
  par exemple, taper <span class="tt">sqrt(2)</span> pour saisir \(\sqrt{2}).
</div>
#endif
<div class="wimscenter"><b>Brouillon</b></div>

<div class="wimscenter">\embed{reply2,10x30}</div>
}
#if defined TARGET_eqalghyper1
\answer{Valeur interdite: }{\goodrep;\lstrep}{type=radio}{option=shuffle}
#endif
#if defined TARGET_eqalghyper2
\answer{Valeur(s) interdite(s): }{\goodrep}{type=fset}
#endif
#if (defined TARGET_eqalghyper3  || defined TARGET_eqalghyper4  || defined TARGET_eqalghyper5 )
\answer{Solution(s)}{\goodrep}{type=fset}
#endif
\answer{}{\rien}{type=matrix}{option=default=empty}
