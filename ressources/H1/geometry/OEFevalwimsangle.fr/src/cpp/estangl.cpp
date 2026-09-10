target=oefestangl1 oefestangl2 oefestangl3 oefestangl4 oefestangl5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}

\integer{rep=randint(1..8)}
#if defined TARGET_oefestangl1
\integer{ang=\rep*20+10}
#endif
#if defined TARGET_oefestangl2
\integer{ang=\rep*2+1}
\integer{ang1=randint(1..18-\ang)}
\integer{ang2=(\ang1+\ang)*10}
\integer{ang1=\ang1*10}
#endif
#if defined TARGET_oefestangl3
\integer{a=randint(3..11)}
\integer{rep=(\a-2)*20}
\text{enonc=\(\widehat{\nom[\a]\nom[1]\nom[2]})}
#endif
#if defined TARGET_oefestangl4
\integer{a=randint(3..10)}
\integer{b=randint(\a+1..11)}
\integer{rep=(\b-\a)*20}
\text{enonc=\(\widehat{\nom[\a]\nom[1]\nom[\b]})}
#endif
#if defined TARGET_oefestangl5
\integer{a=randint(3..10)}
\integer{repi=(\a-2)*20}
\integer{repa=\repi+20}
\integer{ang1=randint(\repi+4..\repa-4)}
\text{enonc=\(\widehat{\nom[12]\nom[1]\nom[2]})}
#endif
#if defined TARGET_oefestangl1
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang*pi/180)*9,sin(\ang*pi/180)*9,black
segment 0,0,9,0,black
arc 0,0,2,2,0,\ang,black
fill  cos((\ang/2)*pi/180)/2,sin((\ang/2)*pi/180)/2,red
text black,-0.5,0,medium,\nom[1])}
#endif
#if defined TARGET_oefestangl2
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
arc 0,0,2,2,\ang1,\ang2,black
fill  cos(((\ang1+\ang2)/2)*pi/180)/2,sin(((\ang1+\ang2)/2)*pi/180)/2,red
text black,-0.5,0,medium,\nom[1])}
#endif
#if defined TARGET_oefestangl3 || defined TARGET_oefestangl4 || defined TARGET_oefestangl5
\text{dessin=}
\for{i=0 to 9}{
  \integer{ang=\i*20}
  \text{dessin=\dessin
segment 0,0,cos(\ang*pi/180)*9,sin(\ang*pi/180)*9,black
text black,cos((\ang+9-\i)*pi/180)*6,sin((\ang+9-\i)*pi/180)*6,medium,\nom[2+\i]
segment cos((\ang)*pi/180)*5-0.2*sin((\ang)*pi/180),sin((\ang)*pi/180)*5+0.2*cos((\ang)*pi/180),cos((\ang)*pi/180)*5+0.2*sin((\ang)*pi/180),sin((\ang)*pi/180)*5-0.2*cos((\ang)*pi/180),black}}
# if defined TARGET_oefestangl3
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
\dessin
text black,0,-0.2,medium,\nom[1])}
#endif
# if defined TARGET_oefestangl4
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
\dessin
text black,0,-0.2,medium,\nom[1])}
# endif
# if defined TARGET_oefestangl5
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
\dessin
text black,0,-0.2,medium,\nom[1]
segment 0,0,9,0,red
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,red
text red,cos((\ang1+10-\a)*pi/180)*8,sin((\ang1+10-\a)*pi/180)*8,medium,\nom[12]
segment cos((\ang1)*pi/180)*7-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*7+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*7+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*7-0.2*cos((\ang1)*pi/180),black)}
# endif
#endif
\text{fig=<img src="\dessin" alt="">}
\text{reps=30°,50°,70°,90°,110°,130°,150°,170°}
#if defined TARGET_oefestangl1 || defined TARGET_oefestangl2
\statement{
  <div class="wims_columns">
  <div class="medium_size img_col"> \fig</div>
  <div class="medium_size text_col">\name_enonce: \embed{r1}.
  </div></div>
}
\answer{}{\rep;\reps}{type=click}
#endif
#if defined TARGET_oefestangl3 || defined TARGET_oefestangl4
\statement{
  <div class="wims_columns">
  <div class="medium_size img_col">\fig</div>
  <div class="medium_size text_col">
  <label for="reply1">\name_enonce \enonc</label> = \embed{r1,4}°
  </div></div>
}
\answer{}{\rep}{type=numeric}
#endif
#if defined TARGET_oefestangl5
\statement{
  <div class="wims_columns">
  <div class="medium_size img_col">\fig</div>
  <div class="medium_size text_col"><label for="reply1">\name_enonce</label>
<div class="wimscenter">\embed{r1,4}° <label for="reply2">&lt; \enonc &lt;</label>
\embed{r2,4}° </div></div></div>}

\answer{}{\repi}{type=numeric}
\answer{}{\repa}{type=numeric}
#endif
