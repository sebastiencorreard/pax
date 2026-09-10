target=oefutibiss4
#define NUM 4
#include "lang_titles.inc"
#include "author.inc"
\keywords{symmetry,angle_bisector,angles}
\integer{ang1=randint(20..80)}
\integer{ang2=\ang1*2}
#include "dessinbiss.inc"
\text{fig=\biss1}
\text{t2=donc \(\widehat{BAE} = \frac{\widehat{BAC}}{2})}
\text{t1=La demi-droite &#91;AE&#41; est la bissectrice de l'angle \(\widehat{BAC}) &#44;}
\text{t3=donc \(\widehat{BAE} = \frac{\ang2}{2})}
\text{t4=\(\widehat{BAE}) =}
\integer{t5=\ang1}

\statement{<div class="wims_columns">
  <div class="medium_size">
    <img src="\fig" alt="">
  </div>
  <div class="medium_size">
<ul><li>
La demi-droite &#91;AE&#41; est la bissectrice de l'angle \(\widehat{BAC})
</li><li>
\(\widehat{BAC}) = \ang2°
</li></ul>
</div></div>
Placer les étiquettes dans le bon ordre :
<ul>
<li>\embed{r1,280x60}</li>
<li>\embed{r2,280x60}</li>
<li>\embed{r3,280x60}</li>
<li>\t4 \embed{r4,4}°</li>
</ul>
}

\answer{}{\t1}{type=dragfill}
\answer{}{\t2}{type=dragfill}
\answer{}{\t3}{type=dragfill}
\answer{}{\t5}{type=raw}
