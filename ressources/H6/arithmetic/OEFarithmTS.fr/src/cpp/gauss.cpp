target=gauss1 gauss2 gauss3 gauss4
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\computeanswer{no}
\precision{1000}
#define TITRE Autour du théorème de Gauss
\integer{n=random(2,3,5,7,11)}
\integer{m=random(2,3,5,7,11)}
\integer{N=\m*\n}
\integer{a=randint(2..15)}
\integer{a=\a=\N?\a+1}
\integer{pgc=gcd(\a,\N)}
\integer{a1=\a/\pgc}
\integer{N1=\N/\pgc}
\integer{b= random(randint(2..15), randint(2..15), randint(2..15)*\pgc)}
\integer{b=\b=\a?\b+1}
#if defined TARGET_gauss2
\integer{pgc=randint(2..10)}
\integer{a=\a1*\pgc}
\integer{N=\N1*\pgc}
\integer{b=randint(1..\N1-1)*\pgc}
#endif
#if defined TARGET_gauss3
\integer{pgc=randint(2..10)}
\integer{a=\a1*\pgc}
\integer{N=\N1*\pgc}
\integer{cas=randint(1,2)}
\if{\cas=1}{
  \integer{b=randint(1..\N1-1)*\pgc}
}
#endif
\integer{test=\b%\pgc}
\text{rep1=\test=0?\pgc:0}
\integer{b1=\b/\pgc}
\text{tsol= PGCD(\a,\N)=\pgc divise \b, on est ramené à résoudre \( \a1 x \equiv \b1\) mod \N1 dans \pgc ensembles de nombres distincts. Ce genre d'équations admet \pgc solutions distinctes.}
\text{tsol=\pgc=1? les nombres \a et \N sont premiers entre eux, ce genre d'équation admet une solution unique.}
\text{tsol=\test>0 and \pgc>1? les nombres \a et \N ne sont pas premiers entre eux, et leur PGCD \pgc ne divise pas \b. Ce genre d'équation n'admet aucune solution.}
\integer{bza=\a1}
\integer{bzb=\N1}
#include "algbezout.inc"
\integer{u=\bzb1}
\integer{v=\bzb2}
\while{\u<0}
 {
 \integer{u=\u+\N1}
 \integer{v=\v-\a1}
 }
\integer{u2=pari(lift(Mod(\b*\u,\N1)))}
\text{tsoluv=\a1 et \N1 sont premiers entre eux, il existe donc deux entiers \(u) et \(v) tels que \(\a1 u + \N1 v= 1\).<br>
  On cherche un couple (u;v) avec \(0 < u \leq \N1) et on trouve \(\a1 \times \u + \N1 \times (\v) = 1).<p>
  On en déduit la solution \(x=\u).</p>}
\text{tsol1=
  A partir de cette solution on trouve la solution de \( \a1 x \equiv \b \;(\N1)\) en prenant \(\b\times\u\; (\N1)\).}
\text{tsol2=
  A partir de cette solution on trouve la solution de \( \a1 x \equiv \b1 \;(\N1)\) en prenant \(\b1\times\u\; (\N1)\).}
#if defined TARGET_gauss1
\integer{u2=\u2=0? \u2+\N1}
\integer{u=\u=0? \u+\N1}
\title{TITRE 1}
\statement{<ol>
<li> Résoudre l'équation de congruence:
<p class="wimscenter">\( \a1*x) \equiv 1 mod \N1</p>
<div class="wims_instruction">Donner la valeur de \(x) appartenant
  à l'ensemble \(\lbrace 1,2,\cdots,\N1\rbrace).</div>
<div class="wimscenter"> \(x=)\embed{reply1,4}.</div>
</li>
<li> Résoudre l'équation de congruence:
<p class="wimscenter">\( \a1*x) \equiv \b mod \N1</p>
<div class="wims_instruction">Donner la valeur de \(x) appartenant
  à l'ensemble \(\lbrace 1,2,\cdots,\N1\rbrace).</div>.
<div class="wimscenter"> \(x= )\embed{reply2,4}.</div>
</li>
</ol>
}
\answer{\( \a1*x) \equiv 1 mod \N1}{\u}{type=numeric}
\answer{\( \a1*x) \equiv \b mod \N1}{\u2}{type=numeric}
\solution{\tsoluv \tsol1}
#endif

#if defined TARGET_gauss2
\title{TITRE 2}
\integer{u2=pari(lift(Mod(\b1*\u,\N1)))}
\integer{u2=\u2=0? \u2+\N1}
\statement{
  Résoudre l'équation de congruence:
<p class="wimscenter">\( \a*x\) \equiv \b mod \N</p>
<div class="wims_instruction">Donner la valeur de \(x\) appartenant à l'ensemble \(\lbrace 1,2, \cdots ,\N\rbrace\) la plus petite possible</div>.
<div class="wimscenter"> \(x=\)\embed{reply1,4}.</div>
}
\answer{\( \a*x\) \equiv \b mod \N}{\u2}{type=numeric}
\solution{\tsol<p>
\tsoluv</p>
 \tsol2}
#endif

#if defined TARGET_gauss3
\title{TITRE 3}
\integer{u2=pari(lift(Mod(\b1*\u,\N1)))}
\integer{u2=\u2=0? \u2+\N1}
\integer{rep1=\rep1>0?1:2}
\text{mstep=\cas=1?r1
r2:r1}
\steps{\mstep}
\statement{
\if{\step=1}{
  L'équation de congruence:
<div class="wimscenter">\( \a*x\) \equiv \b mod \N</div>
  possède-t-elle des solutions? \embed{reply1}
 }{
  Résoudre l'équation de congruence:
<p class="wimscenter">\( \a*x\) \equiv \b mod \N</p>
<div class="wims_instruction">
  Donner la valeur de \(x) appartenant à l'ensemble \(\lbrace 1,2,\cdots,\N\rbrace)
  la plus petite possible</div>.
<div class="wimscenter"> \(x=)\embed{reply2,4}.</div>
 }
}
\answer{Existence de solutions}{\rep1;Oui,Non}{type=radio}
\answer{\( \a*x\) \equiv \b mod \N}{\u2}{type=numeric}
\solution{<p>\tsol</p>
\if{\cas=1}{
<p>\tsoluv</p>
 \tsol2}}
#endif

#if defined TARGET_gauss4
\title{TITRE 4}
\statement{<p>
  Quel est le nombre de solutions dans \(\lbrace 1,2,\cdots,\N\rbrace) de l'équation
</p>
<p class="wimscenter">\( \a*x\) \equiv \b mod \N .</p>
}

\answer{Nombre de solutions}{\rep1}{type=number}
\solution{\tsol}

#endif
