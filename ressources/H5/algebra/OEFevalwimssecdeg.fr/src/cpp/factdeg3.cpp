target=factdeg31 factdeg32 factdeg33 factdeg34 factdeg35
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\keywords{polynomials,factorization}
#if defined TARGET_factdeg31
# define NUM 1
#endif
#if defined TARGET_factdeg32
# define NUM 2
#endif
#if defined TARGET_factdeg33
# define NUM 3
#endif
#if defined TARGET_factdeg34
# define NUM 4
#endif
#if defined TARGET_factdeg35
# define NUM 5
#endif
#include "lang_titles.inc"
#if defined TARGET_factdeg32
\integer{x0=0}
#else
\integer{x0=randitem(1,-1,2,-2)}
#endif
\integer{k=randint(1..3)}
\integer{a=randint(1..3)*randint(1,-1)}
\integer{e=randint(-5..5)}
\text{fact1=(maxima(x-(\x0)))}
\integer{x1=\x0}
\integer{x2=\x0}
\if{\k=1}{ %% pas de racine réelle
 \integer{d=\a*randint(1..5)^2}
 }
\if{\k=2}{ %% une racine double
 \integer{d=0}
 \integer{x1=-(\e)}
 \integer{x2=-(\e)}
 }
\if{\k=3}{ %%% deux racines réelles
 \integer{d=-\a*randint(1..5)^2}
 \complex{x1=pari(-(\e)-sqrt(\d/\a))}
 \complex{x2=pari(-(\e)+sqrt(\d/\a))}
}
\integer{b=2*\a*\e}
\integer{c=\a*(\e)^2+\d}
\text{xsol=\x0,\x1,\x2}
\text{xsol=wims(listuniq \xsol)}
\integer{nbsol=items(\xsol)}
\text{pol=texmath(maxima(expand((x-(\x0))*(\a*(x+(\e))^2+(\d)))))}
\text{factt=maxima(factor((x-(\x0))*(\a*(x+(\e))^2+(\d))))}

#if defined TARGET_factdeg31
\steps{r1,r2,r3}
#endif
#if defined TARGET_factdeg32
\steps{r1,r2,r3,r4}
\text{fact1=x}
#endif
#if defined TARGET_factdeg33
\steps{r1,r2,r3,r4}
#endif
#if defined TARGET_factdeg34
\steps{r1,r2,r3,r5}
#endif
#if defined TARGET_factdeg34 || defined TARGET_factdeg35
\text{name_hint=Les polynômes irréductibles intervenant dans la factorisation
  doivent avoir leur coefficient de plus haut degré égal à 1. Par exemple,
\( 4x^2-9= 4(x-3/2)(x+3/2)=4(x-1.5)(x+1.5)\)}
#endif
#if defined TARGET_factdeg35
\function{f=(x-(\x0))*(\a*(x+(\e))^2+(\d))}
\integer{p1=evalue(\f,x=1)}
\integer{pm1=evalue(\f,x=-1)}
\integer{p2=evalue(\f,x=2)}
\integer{pm2=evalue(\f,x=-2)}

\steps{r6,r7,r8,r9,r5}
\statement{
  Soit le polynôme \(P(x)=\pol\).
  Calculer \(P(1)),\(P(-1)),\(P(2)) et \(P(-2)) :
<div class="wimscenter">
<label for="reply6">\(P(1))=</label>\embed{reply6,4},
<label for="reply7">\(P(-1))=</label>\embed{reply7,4},
<label for="reply8">\(P(2))=</label>\embed{reply8,4},
<label for="reply9">\(P(-2))=</label>\embed{reply9,4}
</div>
<p>
  En déduire la factorisation complète du polynôme \(P) :
</p>
<div class="wimscenter">
<label for="reply5">Factorisation de \(P) : </label>\(P(x)=\) \embed{reply5} </div>
}
\hint{\name_hint}
#else

\statement{
  Soit le polynôme \(P(x)=\pol\).
  On remarque que \(P(\x0)=0\).<p>
  Trouver des réels \(a), \(b) et \(c) tels que \(P(x)=\fact1(a x^2+b x+c)\).</p>
<div class="wimscenter">
<label for="reply1">\(a=)</label> \embed{reply1,4},
<label for="reply2">\(b=)</label> \embed{reply2,4} et
<label for="reply3">\(c=)</label> \embed{reply3,4}
</div>
# if (defined TARGET_factdeg32 || defined TARGET_factdeg33)
<p>
  En déduire le nombre de racines réelles distinctes du polynôme \(P\).</p>
<div class="wimscenter">
<label for="reply4">Nombre de racines réelles distinctes :</label> \embed{reply4,3} </div>

# endif
# if defined TARGET_factdeg34
<p>
  En déduire la factorisation complète du polynôme \(P\).
</p>
<div class="wimscenter">Factorisation de \(P) : <label for="reply5">\(P(x)\)=</label> \embed{reply5} </div>
# endif
}
# if defined TARGET_factdeg34
\hint{\name_hint}
# endif
#endif
\answer{a}{\a}{type=numeric}
\answer{b}{\b}{type=numeric}
\answer{c}{\c}{type=numeric}
\answer{nombre de racines}{\nbsol}{type=numeric}
\answer{factorisation}{\factt}{type=algexp}
\answer{\(P(1))}{\p1}{type=numeric}
\answer{\(P(-1))}{\pm1}{type=numeric}
\answer{\(P(2))}{\p2}{type=numeric}
\answer{\(P(-2))}{\pm2}{type=numeric}
