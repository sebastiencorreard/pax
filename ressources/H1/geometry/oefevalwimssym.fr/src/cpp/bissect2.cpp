target=oefbissect2
#include "lang.inc"
#include "author.inc"

#define NUM 2
#include "lang_titles.inc"
\keywords{angle_bisector}
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}

#include "dessinbiss2.inc"

\matrix{fig=\biss1,&#91;\nom[1]\nom[4]&#41;,\(\widehat{\nom[3]\nom[1]\nom[2]}),1
\biss1,&#91;\nom[1]\nom[3]&#41;,\(\widehat{\nom[2]\nom[1]\nom[4]}),2
\biss2,&#91;\nom[1]\nom[4]&#41;,\(\widehat{\nom[3]\nom[1]\nom[2]}),2
}

\integer{n=randint(1..3)}
\text{rep=row(\n,\fig)}

\statement{
<div class="wims_columns">
  <div class="medium_size">
    <img src="\rep[1]" alt="">
  </div>
  <div class="medium_size">
  \name_stat[1] \rep[2] \name_stat[2] l'angle \rep[3] :
  \embed{r1}.
  </div>
</div>}

\answer{}{\rep[4];\name_choice}{type=menu}
