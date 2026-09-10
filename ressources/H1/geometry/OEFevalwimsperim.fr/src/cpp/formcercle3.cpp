target=oefformcercle3 oefformcercle4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\keywords{perimeter}
\text{size=200x60}
#if defined TARGET_oefformcercle3
\text{form=2 \(\times) \name_list[1] + 2 \(\times) \name_list[2],
  4 \(\times) \name_list[5],
  \name_list[5] \(\times) \name_list[5],
  \name_list[1] \(\times) \name_list[2],
  \name_list[7] \(\times) \name_list[6] \(\div) 2,
  \(\pi \times) \name_list[4] \(\times) \name_list[4]}
\text{formi=\(\pi \times\) \name_list[3]}
#endif
#if defined TARGET_oefformcercle4
\text{form=\(2 \times L + 2 \times l\),
\(4 \times c\),
\(c \times c\),
\(\pi \times r \times r\),
\(L \times l\),
\(b \times h \div 2\)
}
\text{formi=\(\pi \times) D}
#endif

\text{a=shuffle(6)}

\text{chvol=\vol[\a[1]],\vol[\a[2]],\vol[\a[3]],\voli}
\text{rep=\form[\a[1]],\form[\a[2]],\form[\a[3]],\formi}

\statement{\name_question \voli
<div class="wimscenter">\embed{reply 1,\size}</div>
}
\answer{}{\formi;\rep}{type=clickfill}{option=shuffle}
