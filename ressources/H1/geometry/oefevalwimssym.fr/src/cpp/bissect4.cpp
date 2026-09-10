target=oefbissect4
#include "lang.inc"
#include "author.inc"

#define NUM 4
#include "lang_titles.inc"
\keywords{angle_bisector}
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}

#include "dessinbiss2.inc"

\statement{
<div class="wims_columns">
  <div class="medium_size">
    <img src="\biss1" alt="">
  </div>
  <div class="medium_size">
  \enonc[1;1] &#91;\nom[1]\nom[4]&#41; \enonc[1;2] \(\widehat{\nom[3]\nom[1]\nom[2]}\).
  \enonc[2;1] \(\widehat{\nom[3]\nom[1]\nom[2]}\) \enonc[2;2] \ang2°.
  <div class="spacer"><label for="reply1">
    \question \(\widehat{\nom[4]\nom[1]\nom[2]}\)&nbsp;: </label>\embed{r1,4}°.</div>
  </div></div>
}

\answer{}{\ang1}{type=raw}
