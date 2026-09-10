target=oefformpave1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\text{size=70x200x270}
\text{form=2 \(\times) \name_voc[1] + 2 \(\times) \name_voc[2],
4 \(\times) \name_voc[4],
\name_voc[4] \(\times) \name_voc[4],
base \(\times) \name_voc[3] \(\div) 2,
\name_voc[1] \(\times) \name_voc[2],
\name_voc[4] \(\times) \name_voc[4] \(\times) \name_voc[4]}

\text{a=shuffle(6)}

\text{chvol=\vol[\a[1]],\vol[\a[2]],\vol[\a[3]],\voli}
\text{rep=\form[\a[1]],\form[\a[2]],\form[\a[3]],\formi}

\statement{\name_enonce:
<div class="wimscenter">

\embed{reply 1,\size}
</div>
}
\answer{}{\chvol;\rep}{type=correspond}
