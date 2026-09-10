target=oefanglenat1 oefanglenat2 oefanglenat3 oefanglenat4 oefanglenat5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
#if defined TARGET_oefanglenat1 || defined TARGET_oefanglenat5
\real{ang=randint(1,2,3,4,5,6,7,8,9,9,9,9,10,11,12,13,14,15,16,17,18,18)*10}
#endif
#if defined TARGET_oefanglenat2
\integer{ang=randint(3,4,5,6,7,8,9,9,9,9,10,11,12,13,14,15)}
\integer{ang1=randint(2..18-\ang)}
\integer{ang2=(\ang1+\ang)*10}
\integer{ang1=\ang1*10}
\integer{ang=\ang*10}
#endif
#if defined TARGET_oefanglenat3
\integer{ang=randint(1,2,3,4,5,6,7,8,9,9,9,9,10,11,12,13,14,15,16,17,18,18,18)}
\if{\ang=18 or \ang=9}{\integer{ang=\ang*10}}{\integer{ang=\ang*10+randint(0..9)}}

\if{\ang<90}{\text{rep=1}}
\if{\ang=90}{\text{rep=2}}
\if{\ang>90 and \ang<180}{\text{rep=3}}
\if{\ang=180}{\text{rep=4}}
#endif
#if defined TARGET_oefanglenat1 || defined TARGET_oefanglenat2 || defined TARGET_oefanglenat5
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
# if defined TARGET_oefanglenat1 || defined TARGET_oefanglenat5
segment 0,0,cos(\ang*pi/180)*9,sin(\ang*pi/180)*9,black
segment 0,0,9,0,black
arc 0,0,2,2,0,\ang,black
fill  cos((\ang/2)*pi/180)/2,sin((\ang/2)*pi/180)/2,red
# endif
# if defined TARGET_oefanglenat2
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
arc 0,0,2,2,\ang1,\ang2,black
fill  cos(((\ang1+\ang2)/2)*pi/180)/2,sin(((\ang1+\ang2)/2)*pi/180)/2,red
# endif
text black,-0.5,0,medium,\nom[1])}

\if{\ang<90}{\text{rep=1}}
\if{\ang=90}{\text{rep=2}}
\if{\ang>90 and \ang<180}{\text{rep=3}}
\if{\ang=180}{\text{rep=4}}
#endif
\text{fig=<img src="\dessin" alt="">}
#if defined TARGET_oefanglenat1 || defined TARGET_oefanglenat2 || defined TARGET_oefanglenat5
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\fig</div>
 <div class="medium_size text_col">
\name_enonce \embed{r1}
</div></div>
}
#endif
#if defined TARGET_oefanglenat3
\statement{
\name_enonce[1] \ang° \name_enonce[2] \embed{r1}.
}
#endif
#if defined TARGET_oefanglenat1 || defined TARGET_oefanglenat2 || defined TARGET_oefanglenat3
\answer{}{\rep;\nat}{type=radio}{option=shuffle}
#endif
#if defined TARGET_oefanglenat5
\answer{}{\nat[\rep]}{type=atext}
#endif
#if defined TARGET_oefanglenat4
\integer{a=randint(1..4)}
\statement{
<label for="reply1">\name_enonce \nat[\a] :</label> \embed{r1,4}°
}
\answer{}{\rp1}{type=numeric}
\condition{(\rp1<90 and \a=1 and \rp1>0) or (\rp1=90 and \a=2) or
(\rp1>90 and \a=3 and \rp1<180) or (\rp1=180 and \a=4)}
#endif

