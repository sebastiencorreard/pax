target=arithmetico
\title{Suite arithmético-géométrique}
#include "author.inc"

\format{html}

\integer{u0=randint(-10..10)}
\rational{a=simplify(randint(1..10)/randint(1..10))*randint(1,-1)}
\rational{a=\a=1?2}
\integer{b=randint(1..10)*randint(1,-1)}
\text{limupinf=\(\displaystyle\lim u_n=+\infty\)}
\text{limuminf=\(\displaystyle\lim u_n=-\infty\)}
\text{rien=On ne peut rien dire}
\text{sans=\((u_n)\) n'a pas de limite}
\text{finie=\((u_n)\) a une limite finie}

\text{lstrep=\limupinf,\limuminf,\sans,\finie}

\text{recur=texmath(pari(\a*x+\b))}
\text{recur=wims(replace internal x by u_n in \recur)}
\rational{l=simplify(\b/(1-\a))}
\rational{v0=simplify(\u0-\l)}
\text{un=\v0>0 ?\l+\v0*(\a)^n:\l \v0*(\a)^n }
\text{un=\v0=0 ? \l}
\if{\a>0}{
 \if{\v0>0}{\integer{rep=\a>1?1:4}}
  {\integer{rep=\a>1?2:4}}
}{
 \integer{rep=\a<=-1?3:4}
 \integer{rep=\a=-1 and \b=2*\u0 ?4}
}
\integer{lim=\l}
\text{mstep=\rep=4?r1,r2
r3:r1,r2}
\steps{\mstep}

\statement{
  On considère la suite \((u_n)\) définie par:
  <div class="wimscenter">
  \( \left \lbrace \begin{array}{l} u_0=\u0 \\ u_{n+1}=\recur \end{array} \right .\)
  </div>

  \if{\step=1}{
    <ol>
    <li>Donner une formule explicite de \(u_n\):
    <div class="wimscenter">
    <label for="reply1">\(u_n\)=</label>\embed{reply1}
    </div></li>
    <li>Que peut-on dire ?
    <ul>
    \for{j=1 to 4}
     {<li>\embed{reply2,\j}</li>
     }
    </ul>
    </li>
    </ol>
  }{
  <label for="reply3">Quelle est la limite finie de \((u_n)\)</label> ? \embed{reply3,5}
  }

}
\answer{terme général}{\un}{type=formal}
\answer{convergence}{\rep;\lstrep}{type=radio}
\answer{limite}{\l}{type=numexp}
