target=oefformrect1 oefformrect2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\text{size=200x60}
\keywords{area}
#if defined TARGET_oefformrect1
\text{form=2 \(\times\) \name_list[1] + 2 \(\times\) \name_list[2],
  4 \(\times) \name_list[5],
  \name_list[5] \(\times\) \name_list[5],
  \(\pi \times) \name_list[4] \(\times\) \name_list[4],
  \name_list[7] \(\times\) \name_list[6] \(\div\) 2,
  \(\pi \times\) \name_list[3]}
\text{formi=\name_list[1] \(\times\) \name_list[2]}
#endif
#if defined TARGET_oefformrect2
\text{form=\(4 \times c\),
\(c \times c\),
\(\pi \times r \times r\),
\(b \times h \div 2\),
\(\pi \times D\),
\(2 \times L + 2 \times l\)}
\text{formi=\(L \times l\)}
#endif
\text{cnta=items(\form)}
\text{a=shuffle(\cnta)}
text{chvol=\vol[\a[1]],\vol[\a[2]],\vol[\a[3]],\voli}
\text{rep=\form[\a[1]],\form[\a[2]],\form[\a[3]],\formi}
\statement{\name_question:
<div class="wimscenter">
\embed{reply 1,\size}
</div>
}
\answer{}{\formi;\rep}{type=clickfill}{option=shuffle}
