target=oefsolide1 oefsolide2 oefsolide3 oefsolide4 oefsolide5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{nb=12}
\matrix{figures=src="\imagedir/pave1.jpg",6,8,12,1,6
src="\imagedir/pave2.jpg",6,8,12,1,6
src="\imagedir/pave3.jpg",6,8,12,1,6
src="\imagedir/pave4.jpg",6,8,12,1,6
src="\imagedir/pave5.jpg",6,8,12,1,6
src="\imagedir/cube1.jpg",6,8,12,1,6
src="\imagedir/prism1.jpg",5,6,9,2,3
src="\imagedir/prism2.jpg",7,10,15,2,5
src="\imagedir/prism3.jpg",8,12,18,2,6
src="\imagedir/pyram1.jpg",5,5,8,2,1
src="\imagedir/pyram2.jpg",4,4,6,2,0
src="\imagedir/pyram3.jpg",6,6,10,2,0
}

#if defined TARGET_oefsolide1
\integer{a=randint(1..12)}
\text{fig=item(1,row(\a,\figures))}
\text{enonc=\name_enonce}
\text{rep=item(5,row(\a,\figures))}
\text{list=oui,non,je ne sais pas}
\text{typ=radio}
#endif
#if defined TARGET_oefsolide2
\integer{a=randint(1..12)}
\text{fig=item(1,row(\a,\figures))}
\text{enonc=\name_enonce}
\text{rep=item(2,row(\a,\figures))}
\integer{large=5}
\text{typ=case}
\text{list=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
#endif
#if defined TARGET_oefsolide3
\integer{a=randint(1..12)}
\text{fig=item(1,row(\a,\figures))}
\text{enonc=\name_enonce}
\text{rep=item(3,row(\a,\figures))}
\integer{large=5}
\text{typ=case}
\text{list=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
#endif
#if defined TARGET_oefsolide4
\integer{a=randint(1..12)}
\text{fig=item(1,row(\a,\figures))}
\text{enonc=\name_enonce}
\text{rep=item(4,row(\a,\figures))}
\integer{large=5}
\text{typ=case}
\text{list=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
#endif
#if defined TARGET_oefsolide5
\integer{a=randint(1..12)}
\text{fig=item(1,row(\a,\figures))}
\text{enonc=\name_enonce}
\text{rep=item(6,row(\a,\figures))}
\integer{large=5}
\text{typ=case}
\text{list=0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
#endif

\statement{<div class="wims_columns">
 <div class="medium_size img_col"><img \fig alt=""></div>
 <div class="medium_size text_col">\enonc: \embed{r1,\large}</div>
 </div>
}

\answer{}{\rep;\list}{type=\typ}
