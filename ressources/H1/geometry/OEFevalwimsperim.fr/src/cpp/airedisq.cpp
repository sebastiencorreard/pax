target=oefairedisq3 oefairedisq4 oefairedisq5
\keywords{area}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000}
#if defined TARGET_oefairedisq3
\integer{r=randint(3..29)}
\integer{res=\r*\r*3}
\text{enonc1=\name_enonc1[1] \r cm. \name_enonc1[2]}
#endif
#if defined TARGET_oefairedisq4
\integer{a=randint(1..2)}
\text{mot=diamètre,rayon}
\integer{r=randint(3..20)*2}
\if{\a=1}{\integer{res=\r*\r*3/4}}{\integer{res=\r*\r*3}}
\text{enonc1=\name_enonc1[1] \mot[\a] \r cm. \name_enonc1[2]}
#endif
#if defined TARGET_oefairedisq5
\integer{a=randint(1..2)}
\text{mot=diamètre,rayon}
\real{r=randint(6..44)/5}
\if{\a=1}{\real{res=\r*\r*0.785}}{\real{res=\r*\r*3.14}}
\text{enonc1=\name_enonc1[1] \mot[\a] \r cm. \name_enonc1[2]}
#endif
\statement{
  <label for="reply1">\enonc1:</label>\embed{r1,7}\enonc2 cm².
  <div class="wims_instruction">\instruction</div>
}
\answer{}{\res}{type=numeric}
