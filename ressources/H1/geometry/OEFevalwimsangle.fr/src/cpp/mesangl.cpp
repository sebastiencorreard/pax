target=oefmesangl1 oefmesangl2 oefmesangl3 oefmesangl4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
#if defined TARGET_oefmesangl1
\integer{ang1=randint(1..17)*10}
\integer{rep=180-\ang1}
#endif
#if defined TARGET_oefmesangl2
\integer{ang1=randint(2..17)*10}
\integer{rep=\ang1}
#endif
#if defined TARGET_oefmesangl3
\integer{ang1=randint(1..17)*10+randint(2..8)}
\integer{rep=180-\ang1}
#endif
#if defined TARGET_oefmesangl4
\integer{ang1=randint(2..17)*10+randint(2..8)}
\integer{rep=\ang1}
#endif
\text{biss1=draw(515,284
xrange -10,10
yrange -1,10
copy -10.225,9.75,-1,-1,-1,-1,rapport.jpg
linewidth 2
segment 0,0,cos(\ang1*pi/180)*10,sin(\ang1*pi/180)*10,blue
#if defined TARGET_oefmesangl1 || defined TARGET_oefmesangl3
arc 0,0,2,2,\ang1,180,blue
text blue,cos((\ang1-8)*pi/180)*5,sin((\ang1-8)*pi/180)*5,medium,\nom[4]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),blue
segments blue, 0,0,-10,0,-5,-0.2,-5,0.2
text blue,-5,-0.2,medium,\nom[2]
text blue,-0.5,0,medium,\nom[1])}
#endif
#if defined TARGET_oefmesangl2 || defined TARGET_oefmesangl4
arc 0,0,2,2,0,\ang1,blue
segment cos((\ang1/2)*pi/180)*0.7,sin((\ang1/2)*pi/180)*0.7,cos((\ang1/2)*pi/180)*1.3,sin((\ang1/2)*pi/180)*1.3,blue
text blue,cos((\ang1+8)*pi/180)*5,sin((\ang1+8)*pi/180)*5,medium,\nom[4]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),blue
segments blue,0,0,10,0,5,-0.2,5,0.2
text blue,5,-0.2,medium,\nom[2]
text blue,-0.5,0,medium,\nom[1])}
#endif
\text{fig1=<img src="\biss1" alt="">}
\statement{<div class="wims_columns">
 <div class="medium_size img_col">\fig1</div>
 <div class="medium_size text_col">
\name_enonce \(\widehat{\nom[4]\nom[1]\nom[2]}) :
 \embed{r1,2}°
 </div></div>}

\answer{}{\rep}{type=raw}
