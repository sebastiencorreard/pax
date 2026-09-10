target=oeftracecerc1 oeftracecerc2 oeftracecerc3 oeftracecerc4 oeftracecerc5
#include "lang_titles.inc"
\text{nom=shuffle(A,B,C,E,F,G,H,I,J,K,L,M,N,R,S,T,U)}
\integer{r=randint(1..9)}
\integer{d=\r*2}
#if defined TARGET_oeftracecerc2
\integer{e=\e*2}
#endif
#if defined TARGET_oeftracecerc3 || defined TARGET_oeftracecerc4 || defined TARGET_oeftracecerc5
\integer{r2=randint(2..5)}
\integer{r3=randint(\r2+1..7)}
\integer{r1=randint(\r3+1..12)}
# if defined TARGET_oeftracecerc4 || defined TARGET_oeftracecerc5
\text{r=\r1,\r2,\r3}
# endif
#endif
#if defined TARGET_oeftracecerc1 || defined TARGET_oeftracecerc2
\text{dess=draw(300,300
circle 150,150,260,black
circle 215,150,130,black
segment 20,150,280,150,black
text black,140,132,medium,\nom[1]
segment 146,146,154,154,black
segment 146,154,154,146,black
text black,205,132,medium,\nom[2]
segment 211,146,219,156,black
segment 211,156,219,146,black
text black,285,132,medium,\nom[3]
text black,10,132,medium,\nom[4]
text black,40,40,medium,(C1)
text black,160,80,medium,(C2)
)}
#endif
#if defined TARGET_oeftracecerc3 || defined TARGET_oeftracecerc4 || defined TARGET_oeftracecerc5
\text{dess=draw(300,300
circle 90,190,180,black
circle 130,75,100,black
circle 210,160,150,black
segment 86,186,94,194,black
segment 94,186,86,194,black
text black,80,170,medium,\nom[1]
segment 126,71,134,79,black
segment 134,71,126,79,black
text black,120,55,medium,\nom[2]
segment 206,156,214,164,black
segment 214,156,206,164,black
text black,200,140,medium,\nom[3]
text black,70,85,medium,\nom[4]
text black,185,75,medium,\nom[5]
text black,175,230,medium,\nom[6]
text black,145,130,medium,\nom[7]
text black,140,270,medium,\nom[8]
text black,240,78,medium,\nom[9]
segment 130,264,136,274,black
segment 248,96,174,222,black)}
#endif
#include "lang.inc"
#if defined TARGET_oeftracecerc1 || defined TARGET_oeftracecerc2
\integer{cnt=rows(\quest)}
\integer{a=randint(1..\cnt)}
\text{quest=row(\a,\quest)}
\text{reps=(C1),(C2),\name_none}
#endif
#if defined TARGET_oeftracecerc3
\matrix{r=4,6,7,8
4,5,7
5,6,7,9}
\integer{a=randint(1..3)}
\if{\a=1}{\text{r=shuffle(row(\a,\r))}
\text{rep=\r1}}
\if{\a=2}{\text{r=shuffle(row(\a,\r))}
\text{rep=\r2}}
\if{\a=3}{\text{r=shuffle(row(\a,\r))}
\text{rep=\r3}}
#endif
#if defined TARGET_oeftracecerc4
\matrix{c=1,2
2,3
1,3
1,2,3}
\integer{a=randint(4..7)}
\if{\a=4}{\text{c=shuffle(row(\a-3,\c))}
\text{rep1=\r[\c[1]]}
\text{rep2=\r[\c[2]]}}
\if{\a=5}{\text{c=shuffle(row(\a-3,\c))}
\text{rep1=\r[\c[1]]}
\text{rep2=\r[\c[2]]}}
\if{\a=6}{\text{c=shuffle(row(\a-3,\c))}
\text{rep1=\r[\c[1]]}
\text{rep2=\r[\c[2]]}}
\if{\a=7}{\text{c=shuffle(row(\a-3,\c))}
\text{rep1=\r[\c[1]]}
\text{rep2=\r[\c[2]]}}
#endif
#if defined TARGET_oeftracecerc5
\matrix{c=4,6,7,8
4,5,7
5,6,7,9}

\text{a=shuffle(3)}
\text{c=wims(listintersect row(\a[1],\c) and row(\a[2],\c))}
\text{reps=\nom[\c[1]],\nom[\c[2]]}
#endif
\statement{<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dess" alt=""></div>
 <div class="medium_size text_col">
#if defined TARGET_oeftracecerc1 || defined TARGET_oeftracecerc2
\name_enonce[1;]
# if defined TARGET_oeftracecerc1
\name_enonce[2;1] [\nom[1]\nom[2]] \name_enonce[2;2] \d cm.
# endif
# if defined TARGET_oeftracecerc2
\name_enonce[2;1] [\nom[1]\nom[3]] \name_enonce[2;2] \d cm.
# endif
<p>\name_coche:</p>
<div class="wims_question">\quest[1]: \embed{r1}</div>
#endif
#if defined TARGET_oeftracecerc3 || defined TARGET_oeftracecerc4 || defined TARGET_oeftracecerc5
\name_enonce[1;]:
<ul><li>
\name_enonce[2;] \r1 cm;
</li><li>
\name_enonce[3;] \r2 cm;
</li><li>
\name_enonce[4;] \r3 cm.
</li><li>
\name_enonce[5;]
</li></ul>
<div class="wims_question">
# if defined TARGET_oeftracecerc3
\name_enonce2[1] \nom[\r[1]] \name_enonce2[2] \embed{r1,3} cm \name_enonce2[3] \nom[\a].
# endif
# if defined TARGET_oeftracecerc4
\name_enonce2[1] \nom[\a] \name_enonce2[2] \embed{r1,3} cm \name_enonce2[3] \nom[\c[1]]
\name_enonce2[4] \embed{r2,3} cm \name_enonce2[3] \nom[\c[2]].
# endif
# if defined TARGET_oeftracecerc5
\name_enonce2[1] \r[\a[1]] cm \name_enonce2[2] \nom[\a[1]] \name_enonce2[3] \r[\a[2]] cm
  \name_enonce2[4] \nom[\a[2]] :
 <div class="wimscenter">\embed{r1,4}</div>
# endif
</div>
#endif
</div></div>
}
#if defined TARGET_oeftracecerc1 || defined TARGET_oeftracecerc2
\answer{}{\quest[2];\reps}{type=radio}
#endif
#if defined TARGET_oeftracecerc3
\answer{}{\rep}{type=numeric}
#endif
#if defined TARGET_oeftracecerc4
\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}
#endif
#if defined TARGET_oeftracecerc5
\answer{}{\reps}{type=set}
#endif
