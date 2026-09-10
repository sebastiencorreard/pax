target=oefvocangle1 oefvocangle2 oefvocangle3 oefvocangle4 oefvocangle5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}

\real{ang=randint(3..16)*10}
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang*pi/180)*9,sin(\ang*pi/180)*9,black
segment 0,0,9,0,black
arc 0,0,2,2,0,\ang,black
fill cos((\ang/2)*pi/180)/2,sin((\ang/2)*pi/180)/2,red
text black,cos((\ang+8)*pi/180)*6,sin((\ang+8)*pi/180)*6,medium,\nom[3]
segment cos((\ang)*pi/180)*5-0.2*sin((\ang)*pi/180),sin((\ang)*pi/180)*5+0.2*cos((\ang)*pi/180),cos((\ang)*pi/180)*5+0.2*sin((\ang)*pi/180),sin((\ang)*pi/180)*5-0.2*cos((\ang)*pi/180),black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[2]
text black,-0.5,0,medium,\nom[1])}
#if defined TARGET_oefvocangle1
\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}),\(\widehat{\nom[1]\nom[2]\nom[3]}),\(\widehat{\nom[2]\nom[3]\nom[1]})}
\text{rep=1}
#endif
#if defined TARGET_oefvocangle2
\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}),<big> &#91; <span style="font-style: italic">\(\nom[1]\nom[2])</span> &#41;</big>,\(\nom[1])}
\text{rep=2}
#endif
#if defined TARGET_oefvocangle3
\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}), &#91; \(\nom[1]\nom[2]) &#41;,\(\nom[1])}
\text{rep=3}
#endif
#if defined TARGET_oefvocangle4 || defined TARGET_oefvocangle5
\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}),\(\widehat{\nom[1]\nom[2]\nom[3]}),\(\widehat{\nom[2]\nom[3]\nom[1]}),
 &#91; \(\nom[1]\nom[2]) &#41; et &#91; \(\nom[1]\nom[3]) &#41;,
 &#91; \(\nom[1]\nom[2]) &#41; et &#91; \(\nom[3]\nom[1]) &#41;,
 &#91; \(\nom[2]\nom[1]) &#41; et &#91; \(\nom[3]\nom[1]) &#41;,
 &#91; \(\nom[2]\nom[1]) &#41; et &#91; \(\nom[1]\nom[3]) &#41;,
\(\nom[1]),\(\nom[2]),\(\nom[3])}
\text{aff=\nat[2],\nat[3],\nat[5],\nat[6],\nat[7],\nat[9],\nat[10]}
#endif
\text{fig=<img src="\dessin" alt="">}
#if defined TARGET_oefvocangle1 || defined TARGET_oefvocangle2 || defined TARGET_oefvocangle3
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\fig</div>
 <div class="medium_size text_col">
\name_enonce: \embed{r1,120x40}
 </div></div>
}
\answer{}{\nat[\rep];\nat}{type=dragfill}{option=shuffle}
#endif
#if defined TARGET_oefvocangle4
\statement{
<div class="wimscenter">\fig</div>
\name_enonce[1] \embed{r1,120x40} \name_enonce[2] \embed{r2,120x40}
 \name_enonce[3] \embed{r3,120x40}
}
\answer{}{\nat[1];\aff}{type=dragfill}{option=shuffle}
\answer{}{\nat[8]}{type=dragfill}{option=shuffle}
\answer{}{\nat[4]}{type=dragfill}
#endif
#if defined TARGET_oefvocangle5
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\fig</div>
 <div class="medium_size text_col">
<label for="reply1">\name_enonce[1] </label>\embed{r1,8}
<label for="reply2">\nat[1] \name_enonce[2]</label> \embed{r2,8}
\nat[8] <label for="reply3">\name_enonce[3]</label> \embed{r3,8} \nat[4].
 </div></div>
}
\answer{}{angle}{type=text}
\answer{}{sommet}{type=text}
\answer{}{côtés}{type=text}
#endif
