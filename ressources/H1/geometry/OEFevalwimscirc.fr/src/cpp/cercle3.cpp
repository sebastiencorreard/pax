target= oefcercle3
#include "author.inc"
#include "lang_titles.inc"

\precision{100000}

\text{nom=shuffle(A,B,C,E,F,G,H,I,J,K,L,M,N,R,S,T)}
#include "lang.inc"

\text{dess=draw(300,300
linewidth 1
circle 150,150,260,black
text black,140,150,medium,\nom[1]
segment 58,58,242,242,black
segment 30,100,100,270,black
segment 150,150,210,35,black
text black,45,45,medium,\nom[2]
text black,247,247,medium,\nom[3]
text black,210,20,medium,\nom[4]
text black,20,90,medium,\nom[5]
text black,90,275,medium,\nom[6])}


\integer{a=randint(1..4)}
\text{enonc=row(\a,\enonc)}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\dess" alt=""></div>
 <div class="medium_size text_col">
\name_statement:
<div class="wims_question">\enonc[1] \embed{r1,15} \enonc[3]</div>
</div></div>
}

\answer{}{\enonc[2]}{type=nocase}
