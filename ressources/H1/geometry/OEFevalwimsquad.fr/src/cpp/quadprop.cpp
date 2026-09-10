target=oefquadprop1 oefquadprop2 oefquadprop3
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
#if defined TARGET_oefquadprop1
\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
\integer{d1=randint(6..13)}
\integer{ang1=random(20,30,40,45,45,45,50,60,70,80,90)}
\integer{ang2=random(120,130,135,135,135,140,150,160,170)}
\integer{a=\ang2-\ang1}
\if{\a=90}{\integer{ang2=\ang2+20}}

\text{rect=draw(300,300
xrange -15,15
yrange -15,15
segment \d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),\d1*cos(\ang2*pi/180),\d1*sin(\ang2*pi/180),black
text black,\d1*cos(\ang1*pi/180)+1,\d1*sin(\ang1*pi/180)+1,medium,\nom[1]
segment \d1*cos(\ang2*pi/180),\d1*sin(\ang2*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
text black,\d1*cos(\ang2*pi/180)-1,\d1*sin(\ang2*pi/180)+1,medium,\nom[2]
segment -\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),-\d1*cos(\ang2*pi/180),-\d1*sin(\ang2*pi/180),black
text black,-\d1*cos(\ang1*pi/180)-0.5,-\d1*sin(\ang1*pi/180)-0.5,medium,\nom[3]
segment -\d1*cos(\ang2*pi/180),-\d1*sin(\ang2*pi/180),\d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),black
text black,-\d1*cos(\ang2*pi/180)+0.5,-\d1*sin(\ang2*pi/180)-0.5,medium,\nom[4])
}

\integer{d1=randint(6..13)}
\integer{ang1=random(20,30,40,45,45,45,50,60,70,80,90)}
\integer{ang2=\ang1+90}

\text{carr=draw(300,300
xrange -15,15
yrange -15,15
segment \d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),\d1*cos(\ang2*pi/180),\d1*sin(\ang2*pi/180),black
text black,\d1*cos(\ang1*pi/180)+1,\d1*sin(\ang1*pi/180)+1,medium,\nom[1]
segment \d1*cos(\ang2*pi/180),\d1*sin(\ang2*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
text black,\d1*cos(\ang2*pi/180)-1,\d1*sin(\ang2*pi/180)+1,medium,\nom[2]
segment -\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),-\d1*cos(\ang2*pi/180),-\d1*sin(\ang2*pi/180),black
text black,-\d1*cos(\ang1*pi/180)-0.5,-\d1*sin(\ang1*pi/180)-0.5,medium,\nom[3]
segment -\d1*cos(\ang2*pi/180),-\d1*sin(\ang2*pi/180),\d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),black
text black,-\d1*cos(\ang2*pi/180)+0.5,-\d1*sin(\ang2*pi/180)-0.5,medium,\nom[4])
}

\text{l=shuffle(4)}
\integer{d1=\l[1]*2+5}
\integer{d2=\l[2]*2+5}
\integer{ang1=random(20,30,40,45,45,45,50,60,70,80,90)}
\integer{ang2=\ang1+90}

\text{losa=draw(300,300
xrange -15,15
yrange -15,15
segment \d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),\d2*cos(\ang2*pi/180),\d2*sin(\ang2*pi/180),black
text black,\d1*cos(\ang1*pi/180)+1,\d1*sin(\ang1*pi/180)+1,medium,\nom[1]
segment \d2*cos(\ang2*pi/180),\d2*sin(\ang2*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
text black,\d2*cos(\ang2*pi/180)-1,\d2*sin(\ang2*pi/180)+1,medium,\nom[2]
segment -\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),-\d2*cos(\ang2*pi/180),-\d2*sin(\ang2*pi/180),black
text black,-\d1*cos(\ang1*pi/180)-0.5,-\d1*sin(\ang1*pi/180)-0.5,medium,\nom[3]
segment -\d2*cos(\ang2*pi/180),-\d2*sin(\ang2*pi/180),\d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),black
text black,-\d2*cos(\ang2*pi/180)+0.5,-\d2*sin(\ang2*pi/180)-0.5,medium,\nom[4])
}

\text{l=shuffle(4)}
\integer{d1=\l[1]*2+5}
\integer{d2=\l[2]*2+5}
\integer{d3=\l[3]*2+5}
\integer{d4=\l[4]*2+5}
\integer{ang1=random(20,30,40,45,45,45,50,60,70,80,90)}
\integer{ang2=random(120,130,135,135,135,140,150,160,170)}
\integer{a=\ang2-\ang1}
\if{\a=90}{\integer{ang2=\ang2+20}}

\text{quad=draw(300,300
xrange -15,15
yrange -15,15
segment \d4*cos(\ang1*pi/180),\d4*sin(\ang1*pi/180),\d2*cos(\ang2*pi/180),\d2*sin(\ang2*pi/180),black
text black,\d4*cos(\ang1*pi/180)+1,\d4*sin(\ang1*pi/180)+1,medium,\nom[1]
segment \d2*cos(\ang2*pi/180),\d2*sin(\ang2*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
text black,\d2*cos(\ang2*pi/180)-1,\d2*sin(\ang2*pi/180)+1,medium,\nom[2]
segment -\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),-\d3*cos(\ang2*pi/180),-\d3*sin(\ang2*pi/180),black
text black,-\d1*cos(\ang1*pi/180)-0.5,-\d1*sin(\ang1*pi/180)-0.5,medium,\nom[3]
segment -\d3*cos(\ang2*pi/180),-\d3*sin(\ang2*pi/180),\d4*cos(\ang1*pi/180),\d4*sin(\ang1*pi/180),black
text black,-\d3*cos(\ang2*pi/180)+0.5,-\d3*sin(\ang2*pi/180)-0.5,medium,\nom[4])}
#endif
#if defined TARGET_oefquadprop1 ||defined TARGET_oefquadprop2 ||  defined TARGET_oefquadprop3
\integer{r=randint(1..4)}
#endif
#if defined TARGET_oefquadprop1 || defined TARGET_oefquadprop2
\text{prop=wims(replace internal XXXX by \nat[\r] in \prop)}
\matrix{pp= 1,2
1,2,4,5,6,7,9
1,2,3,4,5,6,7,8,9
1,2,3,4,5,6,8,9}
\text{enonc=\nat[\r]}
#endif
#if defined TARGET_oefquadprop3
\matrix{pp= 1,2,3,4
1,2,3,4
3,4
2,3,4
2,3,4
2,3,4
2,3
3,4
2,3,4
}
\text{enonc=\prop[\r]}
\text{rep=row(\r,\pp)}
#endif
#if defined TARGET_oefquadprop1
\text{reps=<img src="\quad" alt="">,<img src="\rect" alt="">,<img src="\carr" alt="">,<img src="\losa" alt="">}
#endif
#if defined TARGET_oefquadprop2
\text{enonc=\nat[\r]}
#endif
\text{rep=row(\r,\pp)}

\statement{
#if defined TARGET_oefquadprop1
<div class="wims_columns">
 <div class="medium_size img_col">\reps[\r]</div>
 <div class="medium_size text_col">
#endif
#if defined TARGET_oefquadprop1 || defined TARGET_oefquadprop2
<p>\name_question \enonc:</p>
<ul>\for{h=1 to 9}{<li>\embed{r1,\h}</li>}</ul>
#endif
#if defined TARGET_oefquadprop1
</div></div>
#endif
#if defined TARGET_oefquadprop3

\name_question :
<p>\enonc</p>
<ul>\for{h=1 to 4}{<li>\embed{r1,\h}</li>}</ul>
#endif
}
#if defined TARGET_oefquadprop1 || defined TARGET_oefquadprop2
\answer{}{\rep;\prop}{type=checkbox}
#endif
#if defined TARGET_oefquadprop3
\answer{}{\rep;\nat}{type=checkbox}
#endif
