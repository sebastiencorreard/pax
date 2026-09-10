target=oefquaddiag1
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}

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
text black,-\d1*cos(\ang2*pi/180)+0.5,-\d1*sin(\ang2*pi/180)-0.5,medium,\nom[4]
segment \d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
segment \d1*cos(\ang2*pi/180),\d1*sin(\ang2*pi/180),-\d1*cos(\ang2*pi/180),-\d1*sin(\ang2*pi/180),black)}

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
text black,-\d1*cos(\ang2*pi/180)+0.5,-\d1*sin(\ang2*pi/180)-0.5,medium,\nom[4]
segment \d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
segment \d1*cos(\ang2*pi/180),\d1*sin(\ang2*pi/180),-\d1*cos(\ang2*pi/180),-\d1*sin(\ang2*pi/180),black)
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
text black,-\d2*cos(\ang2*pi/180)+0.5,-\d2*sin(\ang2*pi/180)-0.5,medium,\nom[4]
segment \d1*cos(\ang1*pi/180),\d1*sin(\ang1*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
segment \d2*cos(\ang2*pi/180),\d2*sin(\ang2*pi/180),-\d2*cos(\ang2*pi/180),-\d2*sin(\ang2*pi/180),black)
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
text black,-\d3*cos(\ang2*pi/180)+0.5,-\d3*sin(\ang2*pi/180)-0.5,medium,\nom[4]
segment \d4*cos(\ang1*pi/180),\d4*sin(\ang1*pi/180),-\d1*cos(\ang1*pi/180),-\d1*sin(\ang1*pi/180),black
segment \d2*cos(\ang2*pi/180),\d2*sin(\ang2*pi/180),-\d3*cos(\ang2*pi/180),-\d3*sin(\ang2*pi/180),black)}

\integer{r=randint(1..4)}
\text{prop=wims(replace internal XXXX by \nat[\r] in \prop)}

\matrix{pp= 1
1,2,5
1,2,3,5
1,3,5}

\text{enonc=\nat[\r]}
\text{reps=<img src="\quad" alt="">,<img src="\rect" alt="">,<img src="\carr" alt="">,<img src="\losa" alt="">}
\text{rep=row(\r,\pp)}

\text{latextext=}
\for{k=1 to 5}{
\text{latextext=\latextext
\item \prop[\k]}
}

\statement{
 <div class="wims_columns">
 <div class="medium_size img_col">\reps[\r]</div>
 <div class="medium_size text_col">
<p>\name_question \enonc&nbsp;:</p>
<ul>\for{h=1 to 5}{<li>\embed{r1,\h}</li>}</ul>
</div></div>
}

\answer{}{\rep;\prop}{type=checkbox}

\latex{
\begin{statement}
\name_question \par
\enonc
\par
\begin{checkbox}
\latextext
\end{checkbox}
\end{statement}
}

