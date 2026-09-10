target=oefcontvol1 oefcontvol2 oefcontvol3 oefcontvol4 oefcontvol5

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{1000000000}
#if defined TARGET_oefcontvol1 || defined TARGET_oefcontvol2 || defined TARGET_oefcontvol3 || defined TARGET_oefcontvol4
\text{unit1=\(\textrm{km}^3),\(\textrm{hm}^3),\(\textrm{dam}^3),\(\textrm{m}^3),\(\textrm{dm}^3),\(\textrm{cm}^3),\(\textrm{mm}^3)}
\text{unit2=\(\textrm{hL}),\(\textrm{daL}),\(\textrm{L}),\(\textrm{dL}),\(\textrm{cL}),\(\textrm{mL})}
#endif
#if defined TARGET_oefcontvol1
\text{enonc1=\name_enonce: 1 L = 1 }
\text{ty=click}
\text{rep=5;\unit1}
\integer{s=10}
#endif
#if defined TARGET_oefcontvol2
\text{enonc1=\name_enonce: 1 L = }
\text{enonc2=\unit1[5]}
\text{ty=raw}
\text{rep=1}
\integer{s=10}
#endif
#if defined TARGET_oefcontvol3
\text{ty=menu}
\integer{a=random(6,7)}
\text{v=1,10,100,1 000,10 000,100 000,1 000 000}
\text{enonc1=\name_enonce: 1 L = }
\text{enonc2=\unit1[\a]}
\if{\a=6}{\integer{a=4}}
\text{rep=\a;\v}
\integer{s=10}
#endif
#if defined TARGET_oefcontvol4
\text{ty=menu}
\integer{a=random(4,5)}
\integer{b=randitem(3,4,5,6)}
\text{v=1,10,100,1 000,10 000,100 000,1 000 000}
\text{enonc1=\name_enonce : 1 \unit1[\a] = }
\text{enonc2=\unit2[\b]}
\integer{c=13+\b-3*\a}
\text{rep=\c;\v}
\integer{s=10}
#endif
#if defined TARGET_oefcontvol5
\text{ty=correspond}
\integer{a=random(4,5)}
\integer{b=random(3,4,5,6)}
\text{unit1=1 \(\textrm{m}^3\),100 \(\textrm{dm}^3\),10 \(\textrm{dm}^3\),1 \(\textrm{dm}^3\),100 \(\textrm{cm}^3\),10 \(\textrm{cm}^3\),1 \(\textrm{cm}^3\)}
\text{unit2=1 000 L,100 L,10 L,1 L,1 dL,1 cL,1 mL}
\text{v=shuffle(7)}
\text{enonc1=\name_enonce}
\text{list1=\unit1[\v[1]],\unit1[\v[2]],\unit1[\v[3]],\unit1[\v[4]]}
\text{list2=\unit2[\v[1]],\unit2[\v[2]],\unit2[\v[3]],\unit2[\v[4]]}
\text{rep=\list1;\list2}
\integer{s=100x30}
#endif

\statement{
\enonc1
\if{\ty=correspond}{<div class="wimscenter">}
\embed{r1,\s}
\if{\ty=correspond}{</div>}
\enonc2
}

\answer{}{\rep}{type=\ty}
