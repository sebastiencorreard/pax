target=oefformpave2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

\text{size=70x200x270}
\text{form=2 \(\times) L + 2 \(\times) l,
4 \(\times) c,
c \(\times)  c,
b \(\times) h \(\div) 2,
L \(\times) l,
c \(\times)  c \(\times)  c}

\text{formi=L \(\times) l \(\times) h}

\text{a=shuffle(6)}

\text{chvol=\vol[\a[1]],\vol[\a[2]],\vol[\a[3]],\voli}
\text{rep=\form[\a[1]],\form[\a[2]],\form[\a[3]],\formi}

\statement{\name_enonce:
<div class="wimscenter">
\embed{reply 1,\size}
</div>
}
\answer{}{\chvol;\rep}{type=correspond}
