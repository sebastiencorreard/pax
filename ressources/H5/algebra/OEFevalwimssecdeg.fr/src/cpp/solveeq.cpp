target=solveeq1 solveeq2 solveeq3 solveeq4 solveeq5
\author{Régine, Mangeard;Maguy, Bruno}
\email{regine@mangeard.fr}
\keywords{equations,trinomial,roots}
\format{html}
\precision{1000}
#if defined TARGET_solveeq1
# define NUM 1
#endif
#if defined TARGET_solveeq2
# define NUM 2
#endif
#if defined TARGET_solveeq3
# define NUM 3
#endif
#if defined TARGET_solveeq4
# define NUM 4
#endif
#if defined TARGET_solveeq5
# define NUM 5
#endif
#include "lang_titles.inc"
\text{calcindic=La calculatrice n'est pas autorisée.}

#if (defined TARGET_solveeq1 || defined TARGET_solveeq3)

# if defined TARGET_solveeq1
\integer{k=randint(1,-1)}
\integer{a=randint(1..10)*\k}
\integer{b=randint(-10..10)}
\integer{c=-randint(1..10)*\k}
\text{eq=texmath(maxima(\a*x^2+\b*x+\c))}
\integer{del=(\b)^2-4*\a*\c}
\integer{a2=2*\a}
\integer{a1=\a}
\integer{c1=\c}
\text{eqd=0}
# else
\integer{k=randint(1..3)}
\integer{a=randint(2..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
\integer{m=randint(1..9)*randint(1,-1)}
\integer{p=randint(1..9)*randint(1,-1)}
\integer{q=randint(1..9)*randint(1,-1)}
\if{\k=1}
 {
\text{eq=texmath(maxima(\a*x^2+\b*x+\c))}
\text{eqd=texmath(\m*x+\p)}
\integer{del=(\b-\m)^2-4*\a*(\c-\p)}
\integer{a2=2*\a}
\integer{b=\b-\m}
\integer{c1=(\c-\p)}
\integer{a1=\a}
 }
\if{\k=2}
 {
\text{eq=texmath(maxima(x^2+\b*x+\c))}
\text{eqd=texmath((\a*x+\p)*(x+\q))}
\integer{del=(\p+\a*\q-\b)^2-4*(\a-1)*(\p*\q-\c)}
\integer{a2=2*(\a-1)}
\integer{b=\p+\a*\q-\b}
\integer{c1=(\p*\q-\c)}
\integer{a1=(\a-1)}
 }
\if{\k=3}
 {
\text{eqd=texmath(maxima(\a*x^2+\b*x+\c))}
\text{eq=texmath((x+\p)^2)}
\integer{del=(\b-2*\p)^2-4*(\a-1)*(\c-(\p)^2)}
\integer{a2=2*(\a-1)}
\integer{b=\b-2*\p}
\integer{c1=(\c-(\p)^2)}
\integer{a1=(\a-1)}

 }
# endif
\integer{mb=-\b}
\integer{nbsol=\del<0?1}
\integer{nbsol=\del=0?2}
\integer{nbsol=\del>0?3}
\text{mstep=\nbsol=1?r1,r2:r1,r2
r3,r4}
\text{mstep=\nbsol=3?\mstep,r5,r6,r7,r8}
\text{lstcond=\del>=0?1:}
\text{tsol=\del>0?Les solutions sont \(\frac{\mb-\sqrt{\del}}{\a2}\) et
  \(\frac{\mb+\sqrt{\del}}{\a2}\): la solution est \(\frac{\mb}{\a2}\)}
\text{tsol=\del<0?}
\conditions{\lstcond}
\steps{\mstep}
\statement{<div class="wims_warning">\calcindic</div>
  Résoudre l'équation \((E) : \eq=\eqd\). Pour cela,
<ol>
\if{\step=1}
{
<li> Calculer le discriminant \(\Delta\) de cette équation:
<div class="wimscenter"> <label for="reply1">\(\Delta\)</label>=\embed{reply1}</div></li>
<li> En déduire <label for="reply2">le nombre de solutions de \((E)\):</label>
<div class="wimscenter">\embed{reply2}</div></li>
}
{
<li> \(\Delta=\del\).</li>
<li> Il y a donc \reply2 solutions.</li>
<li>
 \if{\nbsol=2} {
 Compléter la solution unique :
 \special{mathmlinput [x_0 = \frac{reply3}{reply4}],5,noanswer
 reply 3
 reply 4
}
 }{
 Compléter les deux solutions distinctes :
  \special{mathmlinput [x_1=\frac{reply3 + \sqrt{reply5}}{reply4}, x_2=\frac{reply6 - \sqrt{reply8}}{reply7}],3,noanswer
 reply 3
 reply 4
 reply 5
 reply 6
 reply 7
 reply 8
}
}
</li>
}
</ol>
}
\answer{Discriminant}{\del}{type=numeric}
\answer{nombre de solutions}{\nbsol;aucune solution, une solution, deux solutions distinctes}{type=radio}
\answer{ }{\rep1}{type=numeric}{option=noanalyzeprint}
\answer{ }{\rep2}{type=numeric}{option=noanalyzeprint}
\answer{ }{\del1}{type=numeric}{option=noanalyzeprint}
\answer{ }{\rep3}{type=numeric}{option=noanalyzeprint}
\answer{ }{\rep4}{type=numeric}{option=noanalyzeprint}
\answer{ }{\del2}{type=numeric}{option=noanalyzeprint}
\text{s1=simplify((\reply3 + sqrt(\reply5))/(\reply4))}
\text{s2=simplify((\reply6 - sqrt(\reply8))/(\reply7))}
\condition{Solution(s) correcte(s) ? }{(\nbsol=2 and \reply3/(\reply4)==-\b/(\a2)) or
  (\nbsol=3 and \s1+\s2=-\b/(\a1) and (\s1)*(\s2)=\c1/(\a1))}


\solution{\tsol}
#endif

#if defined TARGET_solveeq2
\text{lsteq=}
\integer{b=randint(1..9)}
\text{eq=texmath(x^2+\b*x)}
\text{lsteq=wims(append item \(\eq=0) to \lsteq)}
\integer{a=randint(1..9)}
\integer{c=randint(1..9)}
\integer{b=-randint(1..9)}
\integer{del=(\b)^2-4*\a*\c}
\integer{c=\del=0?\c+1}
\text{eq=texmath(\a*x^2+\b*x+ \c)}
\rational{x1=3/2}
\rational{x2=randint(2..5)}
\text{eq=texmath(maxima(expand(2*(x-\x1)*(x-\x2))))}
\text{lsteq=wims(append item \(\eq=0) to \lsteq)}
\integer{k=randint(1,-1)}
\integer{a=\k*\a}
\integer{c=\k*\c}
\text{eq=texmath(\a*x^2+\c)}
\text{lsteq=wims(append item \(\eq=0) to \lsteq)}
\integer{c=-\c}
\text{eq=texmath(\a*x^2+\c)}
\text{lsteq=wims(append item \(\eq=0) to \lsteq)}
\integer{d=randint(-9..9)}
\text{eq=texmath((\a*x+\b)*(\c*x+\d))}
\text{lsteq=wims(append item \(\eq=0) to \lsteq)}
\integer{a=randint(2..9)*randint(1,-1)}
\integer{b=randint(1..9)*randint(1,-1)}
\text{eq=texmath(\a*x^2+\b*x)}
\text{lsteq=wims(append item \(\eq=0) to \lsteq)}
\integer{x1=random(1,3,5,7,9)}
\rational{x1=\x1/2}
\integer{x2=2*randint(1..9)*randint(1,-1)}
\integer{c=-2*\a*\x1*\x2}
\text{eq=texmath(maxima(expand(2*\a*(x-\x1)*(x-\x2)+\c)))}
\integer{del=(\b)^2+4*\a*\c}
\integer{c=\del=0?\c+1}
\text{eq=texmath(\a*x^2+\b*x)}
\text{lsteq=wims(append item \(\eq=\c) to \lsteq)}
\text{rep=1,3,4,5,6}
\statement{<div class="wims_warning">\calcindic</div>
<p>
  Parmi les équations suivantes, cocher celles qui peuvent être résolues sans
  utiliser le discriminant \(\Delta).
</p>
<ol>
<li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
<li>\embed{reply1,6}</li>
<li>\embed{reply1,7}</li>
</ol>
}
\answer{sans discriminant}{\rep;\lsteq}{type=checkbox}{option=shuffle}
#endif

#if defined TARGET_solveeq4
\integer{k=randint(1,-1)}
\integer{a=randint(1..9)*\k}
\integer{b=randint(-9..9)}
\integer{c=randint(-9..9)}
\text{eq=texmath(maxima(\a*x^2+\b*x+\c))}
\integer{del=(\b)^2-4*\a*\c}
\integer{a2=2*\a}
\integer{nbsol=\del<0?1}
\integer{nbsol=\del=0?2}
\integer{nbsol=\del>0?3}
\statement{<div class="wims_warning">\calcindic</div>
<p>
  Déterminer <label for="reply1">le nombre de points d'intersection</label> de la parabole \(\mathcal{P})
 avec l'axe des abscisses:
</p>
<div class="wimscenter"> \(\mathcal{P} : y=\eq)</div>

<div class="wimscenter">\embed{reply1}</div>
}
\answer{nombre de solutions}{\nbsol;Aucun point, Un point, Deux points distincts}{type=radio}
#endif

#if defined TARGET_solveeq5
\integer{a=randint(1..9)*randint(1,-1)}
\integer{a2=2*\a}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
\integer{m=randint(1..9)*randint(1,-1)}
\integer{p=randint(1..9)*randint(1,-1)}
\text{den=texmath(\a*x^2+\b*x+\c)}
\text{num=texmath(\m*x+\p)}
\text{f=\frac{\num}{\den}}
\integer{del=(\b)^2-4*(\a)*(\c)}
\integer{mdel=-\del}
\text{sing1=texmath((-\b-x)/\a2)}
\text{sing2=texmath((-\b+x)/\a2)}
\text{sing1=\del>0?wims(replace internal x by \sqrt{\del} in \sing1):wims(replace internal x by \sqrt{\mdel} in \sing1)}
\text{sing2=\del>0?wims(replace internal x by \sqrt{\del} in \sing2):wims(replace internal x by \sqrt{\mdel} in \sing2)}
\text{sing0=\del=0?texmath(simplify(-\b/\a2))}
\text{sing00=\del=0?texmath(simplify(\b/\a2))}
\text{sing1=\del=0?\sing0}
\text{sing2=\del=0?\sing00}

%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=&#59;}
\text{tv1=\a>0?\(\sing1):\(\sing2)}
\text{tv2=\a>0?\(\sing2):\(\sing1)}
\text{tv1=\del=0?\(\sing1)}
\text{tv2=\del=0?\(\sing2)}
\text{v1=a}
\text{v2=b}
\text{permut=\v1,\v2,\crocg,\crocd,\bracg,\bracd,\union,\inter,\infg,\infd,\ptvirg,\empt}
\text{permut=wims(listuniq \permut)}
\text{clicList=shuffle(\permut)}
\text{size=40x40x17}

\text{grep=\crocd,\infg,\ptvirg,\v1,\crocg,\union,\crocd,\v1,\ptvirg,\v2,\crocg,\union,\crocd,\v2,\ptvirg,\infd,\crocg}
\text{grep=\del<0?\crocd,\infg,\ptvirg,\infd,\crocg}
\text{grep=\del=0?\crocd,\infg,\ptvirg,\v1,\crocg,\union,\crocd,\v1,\ptvirg,\infd,\crocg}

\statement{<div class="wims_warning">\calcindic</div>
<p>
  On définit les réels \(a) et \(b) par \(a=)\tv1 et \(b=)\tv2.</p>
  Déterminer le plus grand ensemble de réels sur lequel on peut définir la fonction \(f) telle que:
<div class="wimscenter"> \(f(x)=\f)</div>
<div>
<label for="reply1">\(\mathcal{D}_f)=</label>\embed{reply1,\size}
</div>
}
\answer{Domaine de définition}{\grep;\clicList}{type=clickfill}
#endif
