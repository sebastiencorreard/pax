target=oefconstcer1 oefconstcer2 oefconstcer3 oefconstcer4 oefconstcer5
#include "author.inc"
\precision{100000}
#include "lang_titles.inc"
\text{nom=shuffle(A,B,C,E,F,G,H,I,J,K,L,M,N,R,S,T)}
#if defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
\integer{r=randint(20..40)}
#endif
#include "lang.inc"
#if defined TARGET_oefconstcer1
\text{dess=draw(300,300
linewidth 1
circle 150,150,260,black
text black,135,150,medium,\nom[1]
segment 58,58,242,242,black
segment 146,146,154,154,black
segment 146,154,154,146,black
text black,45,45,medium,\nom[2]
text black,247,247,medium,\nom[3])
}
#endif
#if defined TARGET_oefconstcer2
\text{dess=draw(300,300
linewidth 1
circle 150,150,260,black
circle 85,150,130,black
text black,85,130,medium,\nom[1]
segment 20,150,280,150,black
segment 81,146,89,154,black
segment 81,154,89,146,black
text black,10,135,medium,\nom[2]
text black,155,135,medium,\nom[3]
text black,40,40,medium,(C2)
text black,75,70,medium,(C1))
}
#endif
#if defined TARGET_oefconstcer3
\text{dess=draw(300,300
linewidth 1
circle 150,150,260,black
text black,150,130,medium,\nom[1]
segment 20,150,150,150,black
segment 146,146,154,154,black
segment 146,154,154,146,black
segment 20,150,87,37,black
segment 87,37,213,37,black
segment 213,37,280,150,black
text black,10,135,medium,\nom[2]
text black,80,20,medium,\nom[3]
text black,215,20,medium,\nom[4]
text black,285,135,medium,\nom[5])
}
#endif
#if defined TARGET_oefconstcer4
\real{r=\r*2/10}
\real{r1=\r-0.2}
\real{r2=\r+0.2}
\real{inf=\r-0.4}
\real{sup=\r+0.4}

\text{dess=draw(300,300
linewidth 1
circle 150,150,260,black
text black,150,130,medium,\nom[1]
segment 42,78,258,222,black
segment 42,222,258,78,black
segment 42,78,258,78,black
segment 258,78,258,222,black
segment 150,78,258,150,black
segment 150,78,42,222,black
segment 258,150,42,222,black
segment 146,146,154,154,black
segment 146,154,154,146,black
text black,30,65,medium,\nom[2]
text black,265,220,medium,\nom[3]
text black,265,65,medium,\nom[4]
text black,30,220,medium,\nom[5]
text black,150,60,medium,\nom[6]
text black,265,140,medium,\nom[7])
}
#endif
#if defined TARGET_oefconstcer5
\real{r=\r*2/10}
\real{d=\r*sqrt(2.5)}
\real{d1=\d-0.2}
\real{d2=\d+0.2}
\real{inf=\d-0.4}
\real{sup=\d+0.4}

\text{dess=draw(300,300
linewidth 1
circle 150,150,260,black
text black,150,130,medium,\nom[1]
segment 42,78,258,222,black
segment 96,114,193,28,black
segment 193,28,258,222,black
segment 146,154,154,146,black
text black,30,65,medium,\nom[2]
text black,265,220,medium,\nom[3]
text black,95,95,medium,\nom[4]
text black,200,15,medium,\nom[5])
}
#endif
\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dess" alt=""></div>
 <div class="medium_size text_col">
\name_statement
#if defined TARGET_oefconstcer1
<ol><li>\embed{r1,400x30}
</li><li>\embed{r2,400x30}
</li><li>\embed{r3,400x30}
</li></ol>
#endif
#if defined TARGET_oefconstcer2
<ol><li>\embed{r1,500x30}
</li><li>\embed{r2,500x30}
</li><li>\embed{r3,500x30}
</li><li>\embed{r4,500x30}
</li></ol>
#endif
#if defined TARGET_oefconstcer2 || defined TARGET_oefconstcer3 || defined TARGET_oefconstcer4
<div class="wims_instruction">\name_instruction</div>
#endif
#if defined TARGET_oefconstcer3 || defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
<ol><li>\embed{r1,500x40}
</li><li>\embed{r2,500x40}
</li><li>\embed{r3,500x40}
</li><li>\embed{r4,500x40}
</li><li>\embed{r5,500x40}
</li></ol>
#endif
 </div>
</div>
#if defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
<p>\name_stat2</p>
<div class="spacer">
# if defined TARGET_oefconstcer4
\nom[6]\nom[7] = \embed{r6,5} cm.
# endif
# if defined TARGET_oefconstcer5
\nom[3]\nom[5] = \embed{r6,5} cm
# endif
</div>
#endif
}

\answer{}{\enonc[1]}{type=dragfill}{option=shuffle}
\answer{}{\enonc[2]}{type=dragfill}
\answer{}{\enonc[3]}{type=dragfill}
#if defined TARGET_oefconstcer2 || defined TARGET_oefconstcer3 || defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
\answer{}{\enonc[4]}{type=dragfill}
#endif
#if defined TARGET_oefconstcer3 || defined TARGET_oefconstcer4 || defined TARGET_oefconstcer5
\answer{}{\enonc[5]}{type=dragfill}
#endif
#if defined TARGET_oefconstcer4
\answer{}{\rep}{type=numeric}
\condition{\name_cond[1]:}{\rep<=\r2 and \rep>=\r1}
\condition{\name_cond[2]:}{\rep<=\sup and \rep>=\inf}
#endif
#if defined TARGET_oefconstcer5
\answer{}{\rep}{type=numeric}
\condition{\name_cond[1]:}{\rep<=\d2 and \rep>=\d1}
\condition{\name_cond[2]:}{\rep<=\sup and \rep>=\inf}
#endif
