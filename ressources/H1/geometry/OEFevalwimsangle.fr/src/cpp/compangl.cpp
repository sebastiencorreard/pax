target=oefcompangl1 oefcompangl2 oefcompangl3 oefcompangl4 oefcompangl5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
#if defined TARGET_oefcompangl1
\integer{ang1=randint(2..14)}
\integer{ang2=randint(\ang1+2..18)*10}
\integer{ang1=\ang1*10}
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
arc 0,0,2,2,0,\ang1,black
segment cos((\ang1/2)*pi/180)*0.7,sin((\ang1/2)*pi/180)*0.7,cos((\ang1/2)*pi/180)*1.3,sin((\ang1/2)*pi/180)*1.3,black
text black,cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[4]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
arc 0,0,4,4,0,\ang2,black
text black,cos((\ang2+4)*pi/180)*6,sin((\ang2+4)*pi/180)*6,medium,\nom[3]
segment cos((\ang2)*pi/180)*5-0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5+0.2*cos((\ang2)*pi/180),cos((\ang2)*pi/180)*5+0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5-0.2*cos((\ang2)*pi/180),black
segment 0,0,9,0,black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[2]
text black,-0.5,0,medium,\nom[1])}

\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}),\(\widehat{\nom[4]\nom[1]\nom[2]})}
\text{fig=<img src="\dessin" alt="">}
#endif
#if defined TARGET_oefcompangl2
\text{v=shuffle(2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)}
\integer{ang1=\v[1]*10}
\text{dessin1=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
segment 0,0,9,0,black
arc 0,0,2,2,0,\ang1,black
fill cos((\ang1/2)*pi/180)/2,sin((\ang1/2)*pi/180)/2,red
text black,cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[3]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[2]
text black,-0.5,0,medium,\nom[1])}

\integer{ang2=\v[2]*10}
\text{dessin2=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
segment 0,0,9,0,black
arc 0,0,2,2,0,\ang2,black
fill cos((\ang2/2)*pi/180)/2,sin((\ang2/2)*pi/180)/2,blue
text black,cos((\ang2+8)*pi/180)*6,sin((\ang2+8)*pi/180)*6,medium,\nom[6]
segment cos((\ang2)*pi/180)*5-0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5+0.2*cos((\ang2)*pi/180),cos((\ang2)*pi/180)*5+0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5-0.2*cos((\ang2)*pi/180),black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[5]
text black,-0.5,0,medium,\nom[4])}

\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}),\(\widehat{\nom[6]\nom[4]\nom[5]})}
\if{\ang1<\ang2}{\text{rep1=\nat[1]}
\text{rep2=\nat[2]}}{\text{rep1=\nat[2]}
\text{rep2=\nat[1]}}

\text{fig1=<img src="\dessin1" alt="">}
\text{fig2=<img src="\dessin2" alt="">}
\text{fig=\fig1 \fig2}
#endif
#if defined TARGET_oefcompangl3
\integer{ang1=randint(2,3,4,5,6,7,8,10,11,12,13,14,15,16)}
\integer{ang2=180}
\integer{ang1=\ang1*10}
\text{dessin=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
arc 0,0,2,2,0,\ang1,black
segment cos((\ang1/2)*pi/180)*0.7,sin((\ang1/2)*pi/180)*0.7,cos((\ang1/2)*pi/180)*1.3,sin((\ang1/2)*pi/180)*1.3,black
text black,cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[4]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
arc 0,0,4,4,\ang1,\ang2,black
text black,cos((\ang2+4)*pi/180)*5,sin((\ang2+4)*pi/180)*5,medium,\nom[3]
segment cos((\ang2)*pi/180)*5-0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5+0.2*cos((\ang2)*pi/180),cos((\ang2)*pi/180)*5+0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5-0.2*cos((\ang2)*pi/180),black
segment 0,0,9,0,black
segment 5,-0.2,5,0.2,black
text black,5,-0.2,medium,\nom[2]
text black,-0.5,0,medium,\nom[1])}

\text{nat=\(\widehat{\nom[3]\nom[1]\nom[4]}),\(\widehat{\nom[4]\nom[1]\nom[2]})}
\if{\ang1<90}{\text{rep1=\nat[2]}
\text{rep2=\nat[1]}}{\text{rep1=\nat[1]}
\text{rep2=\nat[2]}}
\text{fig=<img src="\dessin" alt="">}
#endif
#if defined TARGET_oefcompangl4
\integer{rep1=randint(1..8)}
\integer{ang=\rep1*2+1}
\integer{ang1=randint(1..18-\ang)}
\integer{ang2=(\ang1+\ang)*10}
\integer{ang1=\ang1*10}

\text{dessin1=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang1*pi/180)*9,sin(\ang1*pi/180)*9,black
segment 0,0,cos(\ang2*pi/180)*9,sin(\ang2*pi/180)*9,black
arc 0,0,2,2,\ang1,\ang2,black
fill cos(((\ang1+\ang2)/2)*pi/180)/2,sin(((\ang1+\ang2)/2)*pi/180)/2,red
text black,-0.5,0,medium,\nom[1]
segment cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
segment cos((\ang2)*pi/180)*5-0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5+0.2*cos((\ang2)*pi/180),cos((\ang2)*pi/180)*5+0.2*sin((\ang2)*pi/180),sin((\ang2)*pi/180)*5-0.2*cos((\ang2)*pi/180),black
text black,cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[2]
text black,cos((\ang2+8-\rep1)*pi/180)*6,sin((\ang2+8-\rep1)*pi/180)*6,medium,\nom[3])}

\integer{rep2=randint(1..8)}
\integer{angb=\rep2*2+1}
\integer{ang3=randint(1..18-\angb)}
\integer{ang4=(\ang3+\angb)*10}
\integer{ang3=\ang3*10}

\text{dessin2=draw(400,200
xrange -10,10
yrange -1,10
segment 0,0,cos(\ang3*pi/180)*9,sin(\ang3*pi/180)*9,black
segment 0,0,cos(\ang4*pi/180)*9,sin(\ang4*pi/180)*9,black
arc 0,0,2,2,\ang3,\ang4,black
fill cos(((\ang3+\ang4)/2)*pi/180)/2,sin(((\ang3+\ang4)/2)*pi/180)/2,blue
text black,-0.5,0,medium,\nom[4]
segment cos((\ang3)*pi/180)*5-0.2*sin((\ang3)*pi/180),sin((\ang3)*pi/180)*5+0.2*cos((\ang3)*pi/180),cos((\ang3)*pi/180)*5+0.2*sin((\ang3)*pi/180),sin((\ang3)*pi/180)*5-0.2*cos((\ang3)*pi/180),black
segment cos((\ang4)*pi/180)*5-0.2*sin((\ang4)*pi/180),sin((\ang4)*pi/180)*5+0.2*cos((\ang4)*pi/180),cos((\ang4)*pi/180)*5+0.2*sin((\ang4)*pi/180),sin((\ang4)*pi/180)*5-0.2*cos((\ang4)*pi/180),black
text black,cos((\ang3+8)*pi/180)*6,sin((\ang3+8)*pi/180)*6,medium,\nom[5]
text black,cos((\ang4+8-\rep1)*pi/180)*6,sin((\ang4+8-\rep1)*pi/180)*6,medium,\nom[6])}

\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}),\(\widehat{\nom[6]\nom[4]\nom[5]})}

\text{reps=\(\ <\ \),\(\ =\ \),\(\ >\ \)}
\if{\rep1<\rep2}{\text{r=\reps[1]}}
\if{\rep1=\rep2}{\text{r=\reps[2]}}
\if{\rep1>\rep2}{\text{r=\reps[3]}}
\text{fig1=<img src="\dessin1" alt="">}
\text{fig2=<img src="\dessin2" alt="">}
\text{fig=\fig1 \fig2}
#endif
#if defined TARGET_oefcompangl5
\integer{ang1=randint(2..11)*10}
\integer{ang3=randint(7..16)*10}

\text{dessin=draw(300,300
xrange -10,10
yrange -2,18
segment -7,0,-7+cos(\ang1*pi/180)*19,sin(\ang1*pi/180)*19,black
segment -7,0,7,0,black
arc -7,0,3,3,0,\ang1,black
fill -7+cos(\ang1*pi/360),sin(\ang1*pi/360),red
text black,-7.5,-0.5,medium,\nom[1]
segment -7+cos((\ang1)*pi/180)*5-0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5+0.2*cos((\ang1)*pi/180),-7+cos((\ang1)*pi/180)*5+0.2*sin((\ang1)*pi/180),sin((\ang1)*pi/180)*5-0.2*cos((\ang1)*pi/180),black
text black,-7+cos((\ang1+8)*pi/180)*6,sin((\ang1+8)*pi/180)*6,medium,\nom[2]
segment 7,0,7+cos(\ang3*pi/180)*19,sin(\ang3*pi/180)*19,black
arc 7,0,3,3,\ang3,180,black
fill 7+cos((\ang3+180)*pi/360),sin((\ang3+180)*pi/360),blue
text black,7,-0.5,medium,\nom[3]
segment 7+cos((\ang3)*pi/180)*5-0.2*sin((\ang3)*pi/180),sin((\ang3)*pi/180)*5+0.2*cos((\ang3)*pi/180),7+cos((\ang3)*pi/180)*5+0.2*sin((\ang3)*pi/180),sin((\ang3)*pi/180)*5-0.2*cos((\ang3)*pi/180),black
text black,7+cos((\ang3+8)*pi/180)*6,sin((\ang3+8)*pi/180)*6,medium,\nom[4]
)}

\text{nat=\(\widehat{\nom[3]\nom[1]\nom[2]}),\(\widehat{\nom[1]\nom[3]\nom[4]})}

\text{reps=\(\ < \),\(\ = \),\(\ > \)}
\integer{a=180-\ang3}
\if{\ang1<\a}{\text{rep=\reps[1]}}
\if{\ang1=\a}{\text{rep=\reps[2]}}
\if{\ang1>\a}{\text{rep=\reps[3]}}
\text{fig=<img src="\dessin" alt="">}
#endif
\statement{
<div class="wims_columns">
 <div class="medium_size text_col">
 \name_enonce:
#if defined TARGET_oefcompangl1 || defined TARGET_oefcompangl2 || defined TARGET_oefcompangl3
<div class="wimscenter">\embed{r1,120x40} \(< \) \embed{r2,120x40}
</div>
#endif
#if defined TARGET_oefcompangl4
<div class="wimscenter">\nat[1] \embed{r1,80x50} \nat[2]</div>
#endif
#if defined TARGET_oefcompangl5
\nat[1] \embed{r1,80x50} \nat[2]
#endif
</div>
<div class="medium_size img_col">\fig</div>
</div>
}
#if defined TARGET_oefcompangl1
\answer{}{\nat[2]}{type=dragfill}{option=shuffle}
\answer{}{\nat[1]}{type=dragfill}{option=shuffle}
#endif
#if defined TARGET_oefcompangl2 || defined TARGET_oefcompangl3
\answer{}{\rep1}{type=dragfill}{option=shuffle}
\answer{}{\rep2}{type=dragfill}{option=shuffle}
#endif
#if defined TARGET_oefcompangl4
\answer{}{\r;\reps}{type=clickfill}{option=shuffle}
#endif
#if defined TARGET_oefcompangl5
\answer{}{\rep;\reps}{type=clickfill}{option=shuffle}
#endif
