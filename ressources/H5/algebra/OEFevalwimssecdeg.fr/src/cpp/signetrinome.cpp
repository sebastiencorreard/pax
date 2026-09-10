target=signetrinome1 signetrinome2 signetrinome3 signetrinome4 signetrinome5
\author{Régine, Mangeard;Maguy, Bruno}
\email{regine@mangeard.fr}
\keywords{function_variation,trinomial}
\format{html}
# if defined TARGET_signetrinome1
# define NUM 1
# endif
# if defined TARGET_signetrinome2
# define NUM 2
# endif
# if defined TARGET_signetrinome3
# define NUM 3
# endif
# if defined TARGET_signetrinome4
# define NUM 4
# endif
# if defined TARGET_signetrinome5
# define NUM 5
# endif
#include "lang_titles.inc"
\text{indictbl=Attention: Les deux lignes du tableau doivent avoir
 le même nombre d'étiquettes, utiliser l'étiquette vide pour compléter et aligner,
  mais ne pas mettre plusieurs étiquettes vides côte à côte.}
\integer{a=randint(1..9)*randint(1,-1)}
integer{a=1}
\integer{a2=2*\a}
\integer{b=randint(1..9)*randint(1,-1)}
\integer{c=randint(1..9)*randint(1,-1)}
integer{b=4}
integer{c=4}
\text{p=texmath(\a*x^2+\b*x+\c)}
\integer{del=(\b)^2-4*\a*\c}
\integer{mdel=-\del}
\text{sing1=texmath((-\b-x)/\a2)}
\text{sing2=texmath((-\b+x)/\a2)}
\text{sing1=\del>0?wims(replace internal x by \sqrt{\del} in \sing1):wims(replace internal x by \sqrt{\mdel} in \sing1)}
\text{sing2=\del>0?wims(replace internal x by \sqrt{\del} in \sing2):wims(replace internal x by \sqrt{\mdel} in \sing2)}
\text{sing0=\del=0?texmath(simplify(-\b/\a2))}
\text{sing00=\del=0?texmath(simplify(\b/\a2))}
\text{sing1=\del=0?\sing0}
\text{sing2=\del=0?\sing00}
#if defined TARGET_signetrinome1
# include "tabsigne.inc"
%% détermination de la réponse
\if{\del=0}
 {\integer{rep=\a>0?1:3}}
\if{\del>0}
 {\integer{rep=\a>0?3:4}}
\if{\del<0}
 {\integer{rep=\a>0?1:2}}
\statement{<p>
  On considère le trinôme du second degré \(P(x)=\p\).</p><p>
  Cocher le tableau des signes correspondant à \(P\).
</p>
<table class="wimsnoborder wimscenter"><tr>
  <td>\embed{reply 1,1}</td>
  <td>\tabs1</td>
  <td>\embed{reply 1,2}</td>
  <td>\tabs2</td>
</tr><tr>
  <td>\embed{reply 1,3}</td>
  <td>\tabs3</td>
  <td>\embed{reply 1,4}</td>
  <td>\tabs4</td>
</tr>
</table>
}
\answer{tableau}{\rep;1,2,3,4 }{type=radio}

#else
# if defined TARGET_signetrinome2
# endif
# if (defined TARGET_signetrinome3 || defined TARGET_signetrinome4 || defined TARGET_signetrinome5)
\integer{chsymb1=randint(1,2)}
\integer{chsymb2=randint(0,1)}
#   if defined TARGET_signetrinome5
\integer{chsymb1=2}
\integer{chsymb2=1}
#   endif
\integer{chsymb=2*\chsymb2+\chsymb1}
\text{lstsymb=<,\leq,>,\geq}
\text{symb=\lstsymb[\chsymb]}
#   if defined TARGET_signetrinome3
\text{eqp=\(P(x) \symb 0)}
#   endif
#   if defined TARGET_signetrinome4
\integer{mc=-\c}
\text{eqp=\(texmath(\a*x^2+\b*x) \symb \mc)}
#   endif
# endif
%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%
\text{plus=<span style="color:red" class="large">+</span>}
\text{moins=<span style="color:red" class="large">-</span>}
\text{vesp=&nbsp;}
\text{v0=0}
\text{infg=\(-\infty\)}
\text{infd=\(+\infty\)}
\text{tv1=\a>0?\(\sing1\):\(\sing2\)}
\text{tv2=\a>0?\(\sing2\):\(\sing1\)}
\text{tv1=\del=0?\(\sing1\)}
\text{tv2=\del=0?\(\sing2\)}
\text{v1=a}
\text{v2=b}

\text{permut=\v1,\v2,\plus,\moins,\vesp,\v0,\infg,\infd}
\text{permut=wims(listuniq \permut)}
# if (defined TARGET_signetrinome3 || defined TARGET_signetrinome4 || defined TARGET_signetrinome5)
\text{crocg=&#91;}
\text{crocd=&#93;}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup\)}
\text{inter=\(\cap\)}
\text{infg=\(-\infty\)}
\text{infd=\(+\infty\)}
\text{empt=\(\emptyset\)}
\text{ptvirg=&#59;}
\text{clicList2=\permut,\crocg,\crocd,\bracd,\bracg,\union,\inter,\ptvirg,\empt}
\text{clicList2=shuffle(\clicList2)}
\text{size2=40x40x17}
\text{crochg=\chsymb1=1?\crocd:\crocg}
\text{crochd=\chsymb1=1?\crocg:\crocd}
# endif
\text{clicList=shuffle(\permut)}
\text{size=40x40x7}

\if{\del>0}
 {
\text{grepx=\infg,\vesp,\v1,\vesp,\v2,\vesp,\infd}
\text{grepp=\a>0?\vesp,\plus,\v0,\moins,\v0,\plus,\vesp:\vesp,\moins,\v0,\plus,\v0,\moins,\vesp}
\text{grep=(\a>0 and \chsymb2=1) or (\a<0 and \chsymb2=0)?\crocd,\infg,\ptvirg,\v1,\crochd,\union,\crochg,\v2,\ptvirg,\infd,\crocg:\crochg,\v1,\ptvirg,\v2,\crochd}
 }
\if{\del=0}
 {
\text{grepx=\infg,\vesp,\v1,\vesp,\infd}
\text{grepp=\a>0?\vesp,\plus,\v0,\plus,\vesp:\vesp,\moins,\v0,\moins,\vesp}
\if{\chsymb1=1}
 {
%%inégalité stricte
\text{grep=(\a>0 and \chsymb2=1) or (\a<0 and \chsymb2=0)?\crocd,\infg,\ptvirg,\v1,\crochd,\union,\crochg,\v1,\ptvirg,\infd,\crocg:\empt}
 }
 {
\text{grep=(\a>0 and \chsymb2=1) or (\a<0 and \chsymb2=0)?\crocd,\infg,\ptvirg,\infd,\crocg:\bracg,\v1,\bracd}
 }
 }
\if{\del<0}
 {
\text{grepx=\infg,\vesp,\infd}
\text{grepp=\a>0?\vesp,\plus,\vesp:\vesp,\moins,\vesp}
\text{grep=(\a>0 and \chsymb2=1) or (\a<0 and \chsymb2=0)?\crocd,\infg,\ptvirg,\infd,\crocg:\empt}
 }
# if defined TARGET_signetrinome5
\statement{<div class="wims_warning">\calcindic</div>
<p>
  On définit les réels \(a\) et \(b\) par \(a=\)\tv1 et \(b=\)\tv2.</p><p>
  Déterminer le plus grand ensemble de réels sur lequel on peut définir la fonction \(f\) telle que:
</p>
<div class="wimscenter"> \(f(x)=\sqrt{\p}\)</div>
<div>
<label for="reply1">\(\mathcal{D}_f\)=</label>\embed{reply1,\size2}
</div>
}
\answer{Domaine de définition}{\grep;\clicList}{type=clickfill}
# else
\statement{<p>
  On définit les réels \(a\) et \(b\) par \(a=\)\tv1 et \(b=\)\tv2.
  </p>
#   if (defined TARGET_signetrinome3 || defined TARGET_signetrinome2)
  On considère le trinôme du second degré \(P(x)=\p\).
<p>
  Construire le tableau des signes correspondant à \(P\).
</p>
#   else
  On considère l'inéquation \eqp.<p>
  Construire le tableau des signes permettant de résoudre cette inéquation.
</p>
<div class="wims_instruction"> Consigne: garder les termes en \(x\)
  dans le membre de gauche de l'inégalité.</div>
#   endif

<table class="wimscenter wimsborder">
  <tr><th> \(x\) </th><td> \embed{reply1,\size}
 </td></tr><tr>
 <th>signe P </th><td> \embed{reply2,\size}
 </td></tr>
</table>
<div class="wims_instruction">\indictbl</div>
#   if (defined TARGET_signetrinome3 || defined TARGET_signetrinome4)
<p>En déduire l'ensemble solution de l'inéquation \eqp:</p>
<div class="wimscenter"> <label for="reply1">S=</label>\embed{reply3,\size2}</div>
#   endif
}
\answer{}{\grepx;\clicList}{type=clickfill}
\answer{}{\grepp;\clicList}{type=clickfill}
#   if (defined TARGET_signetrinome3 || defined TARGET_signetrinome4)
\answer{Solution}{\grep;\clicList2}{type=clickfill}
#   endif
# endif
#endif
