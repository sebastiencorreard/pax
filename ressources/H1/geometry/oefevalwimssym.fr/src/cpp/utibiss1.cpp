target=oefutibiss1
#define NUM 1
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry,angle_bisector,angles}
\integer{ang1=randint(2..8)*10}
\integer{ang2=\ang1*2}
#include "dessinbiss.inc"
\text{fig=\biss1}
\text{t1=Si la demi-droite &#91;AE&#41; est l'axe,de symétrie de l'angle \(\widehat{BAC})&#44;}
\text{t2=alors la demi-droite &#91;AE&#41; est la bissectrice ,de l'angle \(\widehat{BAC}).}
\text{rep1=\t1}
\text{rep2=\t2}

\statement{
<div class="wimscenter"><img src="\fig" alt=""></div>
Placer les étiquettes dans le bon ordre :
<ul>
<li>\embed{r1,280x40}</li>
<li>\embed{r2,280x40}</li>
</ul>
}

\answer{}{\rep1}{type=dragfill}
\answer{}{\rep2}{type=dragfill}
