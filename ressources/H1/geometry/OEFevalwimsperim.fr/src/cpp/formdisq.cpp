target=oefformdisq3 oefformdisq4

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\keywords{area}
\text{size=200x50}

#if defined TARGET_oefformdisq4
#include "form4.inc"
#endif
#if defined TARGET_oefformdisq3
# include "form3.inc"
#endif

\text{a=shuffle(6)}
text{chvol=\vol[\a[1]],\vol[\a[2]],\vol[\a[3]],\voli}
\text{rep=\form[\a[1]],\form[\a[2]],\form[\a[3]],\form[7]}

\statement{\voli
  <div class="wimscenter">\embed{reply 1,\size}</div>
}
\answer{}{\rep[4];\rep}{type=clickfill}{option=shuffle}
