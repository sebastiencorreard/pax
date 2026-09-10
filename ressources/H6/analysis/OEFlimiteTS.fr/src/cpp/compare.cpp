target=compare1 compare2
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
#if defined TARGET_compare1
# define NUM 1
#endif
#if defined TARGET_compare2
# define NUM 2
#endif
#include "lang_titles.inc"
\text{name_goodanswer=Bonne réponse}
\text{name_choice=Choisissez la bonne réponse&nbsp;}

\text{infd=\(+\infty)}
\text{infg=\(-\infty)}

\text{zero=\(0)}
\text{sans=sans limite}
\text{size=80x30x1}
\text{listinf=\infd, \infg}
\text{lstlim=a une limite finie nulle, a une limite finie non nulle, a une limite infinie, n'a pas de limite}
\text{size=50x20x1}

#if defined TARGET_compare1
\integer{a=randint(1..5)}
\integer{b=randint(2..6)}
\text{data=cos(\a*x)/x^2,\RR^*,+\infty,1,-1/x^2,1/x^2,0
1-(\a*cos(x))/x^2,\RR^*,+\infty,1,1-\a/x^2,1+\a/x^2,1
1/(sqrt(x+1)+sqrt(x)), \RR^+,+\infty,1,0,1/(2sqrt(x)),0
(\a*x)/(\b+sin(x)), \RR,+\infty,2,(\a*x)/(\b+1),(\a*x)/(\b-1),0
(-\a*x)/(\b+sin(x)), \RR,+\infty,3,(-\a*x)/(\b-1),(-\a*x)/(\b+1),0
(\a*x)/(\b+sin(x)), \RR,-\infty,3,(\a*x)/(\b-1),(\a*x)/(\b+1),0
(-\a*x)/(\b+sin(x)), \RR,-\infty,2,(-\a*x)/(\b+1),(-\a*x)/(\b-1),0
\a*x^3-\b*sin(x),\RR,+\infty,2,\a*x^3-\b,\a*x^3+\b,0
\b*sin(x)-\a*x^3,\RR,+\infty,3,-\a*x^3-\b,-\a*x^3+\b,0
\a*x^3-\b*sin(x),\RR,-\infty,3,\a*x^3-\b,\a*x^3+\b,0
\b*sin(x)-\a*x^3,\RR,-\infty,2,-\a*x^3-\b,-\a*x^3+\b,0
}
\integer{i=randint(1..rows(\data))}
///
integer{i=5}
\text{cedata=row(\i,\data)}
\text{f=\cedata[1]}
\text{ft=texmath(\f)}
\text{Df=\cedata[2]}
\text{x0=\cedata[3]}
\integer{indth=\cedata[4]}
\text{u=\cedata[5]}
\text{v=\cedata[6]}
\text{l1=\cedata[7]}
\text{liminf=\indth=2?\infd:\infg}
\text{indet=texmath(maxima(\cedata[4]))}

\if{\indth=1}{
 \text{mstep=r1
r2,r3,r4}
}
\if{\indth=2}{
 \text{mstep=r1
r2,r5}
}
\if{\indth=3}{
 \text{mstep=r1
r3,r5}
}

\text{thgend=Si pour \(x) assez proche de \(a), on a l'encadrement \(u(x) \leq f(x)
\leq v(x)) et que \(u) et \(v) aient la même limite \(l) en \(a), alors on a
\(\displaystyle\lim_{x\rightarrow a}f(x)=l).}
\text{thmin=Si pour \(x) assez proche de \(a), on a l'inégalité \(u(x) \leq
f(x)) et que \(\displaystyle\lim_{x\rightarrow a}u(x)\) soit égale à \(+\infty), alors on a
\(\displaystyle\lim_{x\rightarrow a}f(x)=+\infty).}
\text{thmaj=Si pour \(x) assez proche de \(a), on a l'inégalité \(f(x) \leq
v(x)) et que \(\displaystyle\lim_{x\rightarrow a}v(x)\) soit égale à \(-\infty), alors on a
\(\displaystyle\lim_{x\rightarrow a}f(x)=-\infty).}

\steps{\mstep}
\statement{<div class="wims_smallhelp">Cet exercice comporte plusieurs étapes.</div>
<p>On veut déterminer la limite éventuelle en \(\x0) de la fonction \(f) définie sur
\(\,\Df) par :</p>
<div class="wimscenter"> \(f(x)=\ft).</div>

\if{\step=1}{
Quel théorème faut-il utiliser&nbsp;?<p>
Soit \(a) un réel ou \(a=+\infty) ou \(a=-\infty) et \(l) un réel.
Soit \(u\), \(v) et \(f) trois fonctions définies au voisinage de \(a).</p>
<div>
\embed{reply1,1}&nbsp;: \thgend
</div><div>
\embed{reply1,2}&nbsp;: \thmin
</div><div>
\embed{reply1,3}&nbsp;: \thmaj
</div>
}
\if{\step=2}{
 \if{\indth=1}{
<span class="oef_indgood">\name_goodanswer.</span>
\thgend
<p>
Déterminer un encadrement de \(f(x)) vérifié pour \(x) assez proche de \(\x0) et
permettant d'appliquer le théorème des gendarmes.
</p>
<div class="wimscenter">\embed{reply2,10} \(\leq f(x) \leq) \embed{reply3,10}</div>

En déduire la limite finie de \(f) en \(\x0)&nbsp;:<br>
\(\displaystyle{\lim_{x \rightarrow \x0}f(x) = }) \embed{reply 4}
 }
 \if{\indth=2}{
  <span class="oef_indgood">\name_goodanswer.</span>
  \thmin
  <p>
  Déterminer une minoration de \(f(x)) vérifiée pour \(x) assez proche de \(\x0)
  et permettant d'appliquer le théorème de minoration.
  </p>
  <div class="wimscenter">\embed{reply2,10} \(\leq f(x) )</div>

  En déduire la limite infinie de \(f) en \(\x0)&nbsp;:<br>
  \(\displaystyle{\lim_{x \rightarrow \x0}f(x) = }) \embed{reply 5}
   }
  \if{\indth=3}{
   <span class="oef_indgood">\name_goodanswer.</span>
   \thmaj
  <p>
    Déterminer une majoration de \(f(x)) vérifiée pour \(x) assez proche de \(\x0)
    et permettant d'appliquer le théorème de majoration.
  </p>
  <div class="wimscenter"><label for="reply3">\( f(x) \leq )</label> \embed{reply3}</div>

    En déduire la limite infinie de \(f) en \(\x0)&nbsp;:<br>
  \(\displaystyle{\lim_{x \rightarrow \x0}f(x) = }) \embed{reply 5}
   }
  }
}
\answer{théorème}{\indth;1,2,3}{type=radio}
\answer{fonction u}{\u}{type=algexp}
\answer{fonction v}{\v}{type=algexp}
\answer{limite finie}{\l1}{type=numexp}
\answer{}{\liminf;\infg,\infd}{type=clickfill}
\feedback{\reply1=1 and \indth>1}{Attention.
Le théorème des gendarmes ne s'applique que dans le cas d'une limite finie.}
#endif
#if defined TARGET_compare2
\rational{l=simplify(randint(1..9)*randint(1,-1)/randint(1..9))}
\integer{a=randint(1..9)*randint(1,-1)}
\text{data=\leq,1/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,1,2,\l,abs
\geq,1/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,2,2,\l,abs
\leq,1/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,2,2,\l,dir
\geq,1/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,2,2,\l,dir
\leq,x/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,2,2,\l,abs
\leq,x^2/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,2,2,\l,dir
\geq,x^2/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,1,3,\infd,dir
\geq,x^2/(x-\a),&#93; \a &#59; \(+\infty) &#91;,+\infty,2,2,\l,abs
\leq,x^2/(x-\a),&#93; \(-\infty) &#59; \a &#91;,-\infty,1,3,\infg,dir
\geq,x^2/(x-\a),&#93; \(-\infty) &#59; \a &#91;,-\infty,2,3,\infd,dir
\geq,x^3/(x-\a),&#93; \(-\infty) &#59; \a &#91;,-\infty,2,3,\infd,abs
\geq,x^3/(x-\a),&#93; \(-\infty) &#59; \a &#91;,-\infty,1,3,\infd,dir
}
\text{cntdata=Le théorème des gendarmes donne \(\displaystyle\lim_{x \rightarrow +\infty}f(x) - \l=0) donc \(\displaystyle\lim_{x \rightarrow +\infty}f(x) = \l)
  Pour conclure il aurait fallu avoir le symbole \(\leq) au lieu du symbole \(\geq)
  Pour appliquer le théorème des gendarmes&#44; il aurait fallu avoir une inégalité avec valeur absolue ou un encadrement
  Pour appliquer le théorème de minoration&#44; il faut comparer à une fonction tendant vers \(+\infty)
  On obtient \(-1 \leq f(x)- \l \leq 1) ce qui ne permet pas de conclure
  Pour appliquer le théorème de majoration&#44; il faut comparer à une fonction tendant vers \(-\infty)
  Le théorème de minoration donne \(\displaystyle\lim_{x \rightarrow +\infty}f(x) =+\infty)
  On ne peut pas conclure car on ne connait pas le signe de \(f(x))
  Le théorème de majoration donne \(\displaystyle\lim_{x \rightarrow -\infty}f(x) =-\infty)
  Pour appliquer le théorème de minoration&#44; il faut comparer à une fonction tendant vers \(+\infty)
  On ne peut pas conclure car on ne connait pas le signe de \(f(x))
  Le théorème de minoration donne \(\displaystyle\lim_{x \rightarrow -\infty}f(x) =+\infty)
}
\integer{i=randint(1..rows(\data))}
///
integer{i=12}
\text{tfeed=row(\i,\cntdata)}
\text{cedata=row(\i,\data)}
\text{textcond=pour tout \(x \in) \cedata[3]}
\text{symb=\cedata[1]}
\text{ineg=\cedata[8] issametext abs?|texmath(f(x) - \l)| \symb texmath(\cedata[2]):texmath(f(x) - \l) \symb texmath(\cedata[2])}
\integer{rep1=\cedata[5]}
\text{x0=\cedata[4]}
\integer{indlim=\cedata[6]}
\text{l1=\cedata[7]}
\text{liminf=\cedata[7]}
\if{\rep1=1}{
  \if{\indlim=1}{
    \text{mstep=r4
                 r1}
  }
  \if{\indlim=2}{
    \text{mstep=r4
           r1
           r2}
  }
  \if{\indlim=3}{
    \text{mstep=r4
           r1
           r3}
  }
}{
  \text{mstep=r4}
}
\text{lstrep=Oui,Non}
\steps{\mstep}
\statement{
<div class="wims_smallhelp">Cet exercice comporte une ou plusieurs étapes.</div>
  \if{\step=1}{
    <p>Peut-on déterminer la limite de la fonction \(f) en \(\x0\) sachant que</p>
    <div class="wimscenter">\textcond, on a \(\ineg\)</div>
    <div class="wimscenter">\embed{reply4}.</div>
  }
  \if{\step=2}{
    <p>On sait que \textcond, \(\ineg\).</p>
    <p>\name_choice:</p>
    <div class="wimscenter">
    En \(\x0), la fonction \(f) \embed{reply 1}.
    </div>
  }
  \if{\step=3}{
    <p>On sait que \textcond, on a \(\ineg\).</p>
    \if{\indlim=2}{
      <p>Quelle est la limite finie de \(f) en \(\x0\)&nbsp;?</p>
      <div class="wimscenter">
      <label for="reply2">\(\displaystyle{\lim_{x \rightarrow \x0}f(x) = }\)</label> \embed{reply 2}
      </div>
       }{
      <p>\name_choice:</p>
      <div class="wimscenter">
      \(\displaystyle{\lim_{x \rightarrow \x0}f(x) = }\) \embed{reply 3}
      </div>
      }
    }
}
\answer{type limite}{\indlim;\lstlim}{type=menu}
\answer{}{\l1}{type=numexp}
\answer{}{\liminf;\infg,\infd}{type=clickfill}
\answer{}{\rep1;\lstrep}{type=radio}
\feedback{\reply4 notsametext \lstrep[\rep1]}{\tfeed.}
#endif
