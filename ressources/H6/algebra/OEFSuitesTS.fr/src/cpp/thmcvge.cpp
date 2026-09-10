target=thmcvge1 thmcvge2

\format{html}
#define TITLE Théorèmes de convergence / divergence
#if defined TARGET_thmcvge1
#define NUM 1
#endif
#if defined TARGET_thmcvge2
#define NUM 2
#endif
\title{TITLE NUM}
#include "author.inc"
\text{diff=\(u_{n+1}-u_n\)}
\text{ratio=\(u_{n+1}/u_n\)}
\text{seq=(\(u_n\))}
\integer{lim=random(-5,-4,-3,-2,2,3,4,5)}
\text{half=random(1/2,2/3,1/3,1/4,3/4,-1/2,-2/3,-1/3,-1/4,-3/4)}
\text{lstrep=Seul l'énoncé A est vrai, Seul l'énoncé B est vrai, Aucun des énoncés n'est vrai, Les deux énoncés sont vrais}


#if defined TARGET_thmcvge1
\text{cvdvs=est convergente,
	est convergente,
	converge vers \lim,
	converge vers \lim,
	converge vers \lim,
	est divergente et tend vers \(+\infty),
	est divergente et tend vers \(+\infty),
	est divergente,
	est convergente,
	est convergente
}
\text{conds=(\diff) est convergente,
  \diff tend vers 0,
	(\diff) est convergente,
	\diff tend vers \lim,
	\diff tend vers \lim,
	(\diff) est divergente et tend vers \(+\infty),
	(\diff) est divergente,
	(\diff) est divergente,
	(\diff) est décroissante,
	(|\diff|) est décroissante
}
\text{cvdv2s=est convergente,
	est convergente,
	est convergente,
	converge vers \lim,
  est divergente,
  est divergente et tend vers \(+\infty),
 est divergente et tend vers \(+\infty),
	est divergente,
	est convergente,
	est convergente
}
\text{g1s=1,1,1,0,0,0,0,0,0,0
}
\text{g2s=0,0,0,0,1,1,0,1,0,0
}
\text{gs=1,1,1,3,2,2,3,2,3,3}
\text{ans=Il y a des suites divergentes dont \diff tend vers 0.,
	Il y a des suites divergentes dont \diff tend vers 0.,
	Si \diff ne tend pas vers 0 alors la suite \seq est certainement divergente. Mais l'inverse n'est pas vrai.,
	Si (\diff) converge vers une valeur autre que 0 alors \seq est divergente.,
	Il y a des suites divergentes dont \diff tend vers 0.,

	Il y a des suites divergentes dont \diff tend vers 0.,
	Si (\diff) converge vers 1 alors \seq est divergente.,
	Pensez au cas où \diff sont négatives!,
	(|\diff|) peut converger vers 0 sans être décroissante.
}
\text{exmpA=la convergence de (\diff) vers 0 est une condition nécessaire à la convergence de \seq,
la convergence de (\diff) vers 0 est une condition nécessaire à la convergence de \seq,
la convergence de (\diff) vers 0 est une condition nécessaire à la convergence de \seq,
,
,
,
,
,
,
,
}

\text{cntA=,
,
,
Si \seq converge alors \diff tend vers 0!,
Si \seq converge alors \diff tend vers 0!,
Prenons \(u_n=n+\frac{1}{n}) &#44; \seq diverge et tend vers \(+\infty) et \diff tend vers 1!,
Prenons \(u_n=n+\frac{1}{n}) &#44; \seq diverge et tend vers \(+\infty) et \diff tend vers 1!,
Prenons \(u_n=n+\frac{1}{n}) &#44; \seq diverge et tend vers \(+\infty) et \diff tend vers 1!,
\(u_n=1+\frac{1}{n}) converge vers 1 et \diff=\(\frac{-1}{n(n+1)}<0) converge vers 0 donc \diff n'est pas décroissante,
\(u_{2n}=1+\frac{1}{n}) et \(u_{2n+1}=u_{2n}) \seq converge vers 1 mais \diff vaut 0 ou \(\frac{-1}{n(n+1)}) et &#124;\(u_{n+1}-u_n)&#124; n'est donc pas décroissante}

\text{exmpB=,
,
,
,
La convergence de (\diff) vers 0 est une condition nécessaire à la convergence de \seq donc lorsque (\diff) diverge \seq ne peut pas converger,
Si \diff tend vers \(+\infty) &#44; pour tout A>0 &#44; à partir d'un certain &#44; \(u_n) est positif et \(u_{n+1}-u_n > A \Rightarrow u_{n+1}> A+u_n > A) donc \seq tend vers \(+\infty),
,
La convergence de (\diff) vers 0 est une condition nécessaire à la convergence de \seq donc lorsque (\diff) diverge \seq ne peut pas converger,
,
,
}
\text{cntB=Si \(u_{n+1}=u_n+1) &#44; \diff est constante et vaut 1 donc converge alors que \seq est une suite arithmétique et tend vers \(+\infty),
Si \(u_n=\sqrt{n}) &#44; \diff=\(\sqrt{n+1}-\sqrt{n}=\frac{1}{\sqrt{n+1}+\sqrt{n}}<\frac{1}{2\sqrt{n}}) tend vers 0 alors que \seq tend vers \(+\infty),
Si \(u_{n+1}=u_n+1) &#44; \diff est constante et vaut 1 donc converge alors que \seq est une suite arithmétique et tend vers \(+\infty),
Si \(u_{n+1}=u_n+\lim) &#44; \diff est constante et vaut \lim donc converge alors que \seq est une suite arithmétique et tend vers \(+\infty),
,
,
Si \(u_n=(-1)^n) &#44; \diff vaut 2 ou -2 et diverge et \(u_n) vaut 1 ou -1 donc ne tend pas vers \(+\infty),
,
Si \(u_n=\sqrt{n}) &#44; \diff=\(\sqrt{n+1}-\sqrt{n}=\frac{1}{\sqrt{n+1}+\sqrt{n}}<\frac{1}{2\sqrt{n}}) &#44; \diff décroit vers 0 alors que \seq tend vers \(+\infty),
Si \(u_n=\sqrt{n}) &#44; \diff=\(\sqrt{n+1}-\sqrt{n}=\frac{1}{\sqrt{n+1}+\sqrt{n}}<\frac{1}{2\sqrt{n}}) &#44; (|\diff|) décroit vers 0 alors que \seq tend vers \(+\infty),
}

\integer{cnt=items(\cvdvs)}
\integer{t=random(1..\cnt)}
#### integer{t=6}
\text{cvdv=item(\t,\cvdvs)}
\text{cvdv2=item(\t,\cvdv2s)}
\text{cond=item(\t,\conds)}
\text{an=item(\t,\ans)}
\integer{g1=item(\t,\g1s)}
\integer{g2=item(\t,\g2s)}
\integer{g=item(\t,\gs)}

\statement{Soit \seq une suite de nombres réels.<br>
 Parmi les énoncés suivants, lesquels sont vrais ?
  <ol style="list-style-type:upper-alpha">
  <li>Si \seq \cvdv, alors \cond.
  </li>
  <li>Si \cond, alors \seq \cvdv2.
  </li></ol>
}

\answer{}{\g;\lstrep}{type=radio}
\feedback{(\reply1 issametext \lstrep[1] or \reply1 issametext \lstrep[4]) and \g1=0}
{\cntA[\t]<br>
  Donc l'énoncé A est faux.
}
\feedback{(\reply1 issametext \lstrep[2] or \reply1 issametext \lstrep[3]) and \g1=1}
{l'enoncé A est vrai : \exmpA[\t]
}
\feedback{(\reply1 issametext \lstrep[2] or \reply1 issametext \lstrep[4]) and \g2=0}
{\cntB[\t]<br>
  Donc l'énoncé B est faux.
}
\feedback{(\reply1 issametext \lstrep[1] or \reply1 issametext \lstrep[3]) and \g2=1}
{l'énoncé B est vrai : \exmpB[\t]
}
#endif
#if defined TARGET_thmcvge2
\text{cvdvs=converge vers \lim,
	est convergente,
	converge vers \lim,
	converge vers -1,
	est divergente,

	converge vers 0,
	converge vers 0,
	converge vers 0,
	converge vers une valeur non nulle,
	converge vers \half,

	converge vers 0

}
\text{conds=\ratio tend vers 1,
	\ratio tend vers 1,
	\ratio tend vers 1,
	\ratio tend vers -1,
	\ratio tend vers \lim,

	\ratio tend vers \half,
	|\ratio| tend vers une valeur plus petit que 1,
	|\ratio|&lt;1 à partir d'un certain rang,
	\ratio tend vers 1,
	\ratio tend vers \half,

	|\ratio|&lt;1 à partir d'un certain rang,
}
\text{cvdv2s=est convergente,
	est convergente,
	ne converge pas vers 0,
	est divergente,
	est divergente,

	converge vers 0,
	converge vers 0,
	converge vers 0,
	peut être divergente,
	converge vers \half,

	est convergente,
}
\text{g1s=1,0,1,0,0, 0,0,0,1,0, 0,
}
\text{g2s=0,0,0,0,1, 1,1,0,1,0, 0,
}
\text{gs=1,3,1,3,2,2,2,3,4,3,3,
}
\text{ans=Il y a des suites divergentes dont \ratio tend vers 1.,
	Il y a des suites divergentes dont \ratio tend vers 1 et des suite convergeant vers 0 dont \ratio ne tend pas vers 1.,
	Il y a des suite convergeant vers 0 dont \ratio tend vers 1.,
	Il y a des suite convergeant vers 0 dont \ratio tend vers -1.,
	Il y a des suite divergentes dont \ratio n'a pas de limite.,

	Il y a des suite convergeant vers 0 dont \ratio n'a pas de limite.,
	Il y a des suite convergeant vers 0 dont \ratio n'a pas de limite.,
	,
	Il y a des suites divergentes dont \ratio tend vers 1.,
	\seq converge vers 0 quand \ratio tend vers \half.,

	Rien n'empeche \ratio de sauter de temps à autre. Et la suite ((-<i>n</i>-1)<sup><i>n</i></sup>/<i>n</i>) est divergente.,
}
\text{cntA=,
avec \(u_n=(\frac{1}{2})^n) \seq converge et \ratio =\(\frac{1}{2}) ne tend pas vers 1!,
,
avec \(u_n=-1-\frac{1}{n}) \seq converge vers -1 alors que \ratio tend vers 1,
avec \(u_n=n) \seq diverge et \ratio converge vers 1,
avec \(u_n=\frac{1}{n}) \seq converge vers 0 et \ratio converge vers 1,
avec \(u_n=\frac{1}{n})\seq converge vers 0 et \ratio=\(\frac{n}{n-1} > 1),
avec \(u_n=\frac{1}{n})\seq converge vers 0 et \ratio=\(\frac{n}{n-1} > 1),
,
avec \(u_n=\half+\frac{1}{n}) \seq converge vers \half et \ratio tend vers 1,
avec \(u_n=\frac{1}{n})\seq converge vers 0 et \ratio=\(\frac{n}{n-1} > 1),
}

\text{cntB=avec \(u_n=n) \ratio converge vers 1 et \seq diverge,
avec \(u_n=n) \ratio converge vers 1 et \seq diverge,
avec \(u_n=\frac{1}{n}) \ratio converge vers 1 et \seq converge vers 0,
avec \(u_n=\frac{(-1)^n}{n}) \ratio converge vers -1 et \seq converge vers 0,
,
,
,
avec \(u_n=1+\frac{1}{n}) et \ratio=\(\frac{n^2+2n}{n^2+2n+1}<1) et \seq tend vers 1!,
,
avec \(u_n=(\half)^n) \ratio tend vers \half alors que \seq converge vers 0,
avec \(u_n=\frac{n+1}{n}(-1)^n) (|\ratio|)=\(\frac{n^2+2n}{n^2+2n+1}<1) et \seq diverge!,
}

\integer{cnt=items(\cvdvs)}
\integer{t=random(1..\cnt)}
##### integer{t=11}
\text{cvdv=item(\t,\cvdvs)}
\text{cvdv2=item(\t,\cvdv2s)}
\text{cond=item(\t,\conds)}
\text{an=item(\t,\ans)}
\integer{g1=item(\t,\g1s)}
\integer{g2=item(\t,\g2s)}
\integer{g=item(\t,\gs)}
\text{ch1=\g1=1?Vrai:Faux}
\text{ch2=\g2=1?Vrai:Faux}

\statement{Soit \seq une suite de nombres réels.<br>
  Parmi les énoncés suivants, lesquels sont vrais ?
  <ol style="list-style-type:upper-alpha">
  <li>
  Si \seq \cvdv, alors \cond.
  </li><li>
  Si \cond, alors \seq \cvdv2.
  </li>
  </ol>
}

\answer{}{\g;\lstrep}{type=radio}
\feedback{(\reply1 issametext \lstrep[1] or \reply1 issametext \lstrep[4]) and \g1=0}
{\cntA[\t]<br>
  Donc l'énoncé A est faux.
}
\feedback{(\reply1 issametext \lstrep[2] or \reply1 issametext \lstrep[3]) and \g1=1}
{l'enoncé A est vrai : \exmpA[\t]
}
\feedback{(\reply1 issametext \lstrep[2] or \reply1 issametext \lstrep[4]) and \g2=0}
{\cntB[\t]<br>
  Donc l'énoncé B est faux.
}
\feedback{(\reply1 issametext \lstrep[1] or \reply1 issametext \lstrep[3]) and \g2=1}
{l'énoncé B est vrai : \exmpB[\t]
}

#endif
