target=point1 point2 point3 point4

#include "author.inc"
#include "lang_titles.inc"
\text{d=randitem(d,p,D)}
\integer{a=randint(-10..10)}
\integer{b=randitem(1,-1)*randint(1..10)}
#include "lang.inc"
%%%%%%%%%%%% pour solution %%%%%%%%%%%%%%%% BM
\integer{xsol=randint(-2,1,-1,2)}
%%%%%%%%%%%%  %%%%%%%%%%%%%%%% BM
#if defined TARGET_point1 || defined TARGET_point2
%%%%%%%%%%%% pour solution %%%%%%%%%%%%%%%% BM
 text{equation=y=maxima(expand(\a*x + \b);)}
\text{equation=y=pari(\a*x + \b)}
\integer{ysol=\a*\xsol + \b}
text{equationd=maxima(expand(\a*x + \b);)}
\text{equationd=pari(\a*x + \b)}
%%%%%%%%%%%%  %%%%%%%%%%%%%%%% BM
#endif
#if defined TARGET_point3
 \integer{c=randint(-10..10)}
%%%%%%%%%%%% MB
 \integer{cas=randitem(1,2)}
 text{equation= \cas=1 ? maxima(expand(\a*x + \b*y);) = \c:maxima(expand(\b*y+\a*x);) = \c}
 \text{equation= \cas=1 ? pari(\a*x + \b*y) = \c:pari(\b*y+\a*x) = \c}
#endif
#if defined TARGET_point4
 \integer{c=randint(-10..10)}
 %%%%%%%%%%%% MB
 \integer{cas=randitem(1,2)}
 text{equation= \cas=1 ? maxima(expand(\a*x + \b*y);) = \c : maxima(expand(\b*y+\a*x);) = \c}
 \text{equation= \cas=1 ? pari(\a*x + \b*y) = \c : pari(\b*y+\a*x) = \c}
\text{equation=simplify(\equation)}
%%%%%%%%%%%% fin MB
#endif
#if defined TARGET_point3 || defined TARGET_point4
%%%%%%%%%%%% pour solution %%%%%%%%%%%%%%%% BM
\rational{ysol=(\c-\a*\xsol)/\b}
\integer{csol=\a*\xsol+\b*\ysol}
text{equationd=\cas=1 ? maxima(expand(\a*\xsol + \b*y);) = \c : maxima(expand(\b*y+\a*\xsol);) = \c}
\text{equationd=\cas=1 ? pari(\a*\xsol + \b*y) = \c : pari(\b*y+\a*\xsol) = \c}
%%%%%%%%%%%%  %%%%%%%%%%%%%%%% BM
#endif
#include "lang_fr.inc"
\statement{
\name_introdroite:
<div class="wimscenter"> \(\equation\).</div>
\question.
<div class=wims_question><b>\name_answer:</b>
  Les coordonnées du point choisi sont (\embed{r1,5} ; \embed{r2,5}).</div>}

\answer{}{\x}{type=numexp}
\answer{}{\y}{type=numexp}

#if defined TARGET_point1 || defined TARGET_point2
\text{rep=pari(\a*(\x)+(\b)-(\y))}
#endif
#if defined TARGET_point3 || defined TARGET_point4
\text{rep=pari(\a*(\x)+\b*(\y)-(\c))}
#endif

\condition{Le point appartient à la droite}{\rep=0}
#if defined TARGET_point2 || defined TARGET_point4
\condition{Le point n'appartient pas à l'axe des ordonnées}{\x<>0}
#endif
%%%%%%%%%%% solution %%%%%%%%%%%%% MB

\solution{<h3>Méthode.</h3> Il faut trouver deux nombres \(x\) et \(y\)
  qui vérifient l'équation \(\equation\).
 #if defined TARGET_point4 || defined TARGET_point2
 <p>Le point ne doit pas être sur l'axe des ordonnées,
 donc son abscisse \(x\) ne doit pas être égal à zéro.</p>
 #endif
 <h3>Exemple :</h3>
 \if{\a=0}
 {Puisque l'équation est de la forme, \(y=\ysol), il suffit que la seconde
 coordonnée soit égale à \(\ysol) pour que le point appartienne à la droite \((\d)).}
{On choisit :\(x=\xsol).
#if defined TARGET_point1 || defined TARGET_point2
<br>L'expression \(\equationd) est alors égale à \(\ysol\).
#endif
#if defined TARGET_point3 || defined TARGET_point4
<br>Il faut alors résoudre :  \(\equationd). La solution est \(y=\ysol).
#endif
<br>Ainsi le point de coordonnées \((\xsol ; \ysol)) appartiennent à la droite \((\d)\).
}
}
%%%%%%%%%%%%%%%%%%%%% MB
