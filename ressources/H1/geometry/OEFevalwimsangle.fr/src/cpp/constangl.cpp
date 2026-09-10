target=oefconstangl1 oefconstangl2 oefconstangl3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{nom=shuffle(A,B,C,E,F,G,H,J,K,L,M,N,R,S,T)}
#if defined TARGET_oefconstangl1
\text{plac1=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue,0,0,-10,0,0,-0.2,0,0.2
text blue,0.5,2,medium,A
text blue,-10,1.5,medium,x)}

\text{plac2=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue 6.2,0,-10,0,6.2,-0.2,6.2,0.2
text blue,5,1.5,medium,A
text blue,-10,1.5,medium,x)}

\text{plac3=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 0,-1,-10,-1, 0,-1.2,0,-0.8
text blue,0.5,-1,medium,A
text blue,-10,-1,medium,x)}

\text{plac4=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso8.jpg
linewidth 2
segments blue,0,0,-10,0,0,-0.2,0,0.2
text blue,0.5,2,medium,A
text blue,-10,1.5,medium,x
)}

\matrix{reps=<img src="\plac1" alt="">,1
<img src="\plac2" alt="">,2
<img src="\plac3" alt="">,2
<img src="\plac4" alt="">,2
}
\text{ch=shuffle(4)}
\text{fig=item(1,row(\ch[1],\reps)),item(1,row(\ch[2],\reps)),
item(1,row(\ch[3],\reps)),item(1,row(\ch[4],\reps))}
\text{r=item(2,row(\ch[1],\reps)),item(2,row(\ch[2],\reps)),item(2,row(\ch[3],\reps)),item(2,row(\ch[4],\reps))}
#endif
#if defined TARGET_oefconstangl2
\text{plac1=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10.1,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 0,0,10,0,0,-0.2,0,0.2
text blue,-0.5,2,medium,A
text blue,9.2,1.5,medium,x)}
\text{plac2=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10.1,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, -6.2,0,10,0,-6.2,-0.2,-6.2,0.2
text blue,-6,1.5,medium,A
text blue,9.2,1.5,medium,x)}
\text{plac3=draw(200,200
xrange -10,10
yrange -10,9.9
copy -10.2,9.8,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 0,-1,10,-1,0,-1.2,0,-0.8
text blue,-0.5,-1.5,medium,A
text blue,9.2,-1,medium,x)}
\text{plac4=draw(200,200
xrange -10,10
yrange -10,10
copy -10.3,10,-1,-1,-1,-1,rapporteurperso9.jpg
linewidth 2
segments blue, 0,0,10,0,0,-0.2,0,0.2
text blue,-0.5,2,medium,A
text blue,9.2,1.5,medium,x
)}
\matrix{reps=<img src="\plac1" alt="">,1
<img src="\plac2" alt="">,2
<img src="\plac3" alt="">,2
<img src="\plac4" alt="">,2
}
\text{ch=shuffle(4)}
\text{fig=item(1,row(\ch[1],\reps)),item(1,row(\ch[2],\reps)),
item(1,row(\ch[3],\reps)),item(1,row(\ch[4],\reps))}
\text{r=item(2,row(\ch[1],\reps)),item(2,row(\ch[2],\reps)),item(2,row(\ch[3],\reps)),item(2,row(\ch[4],\reps))}
#endif
#if TARGET_oefconstangl3
\text{plac1=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 0,0,-10,0,0,-0.2,0,0.2
text blue,0.5,2,medium,A
text blue,-10,1.5,medium,x)}

\text{plac2=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 6.2,0,-10,0,6.2,-0.2,6.2,0.2
text blue,5,1.5,medium,A
text blue,-10,1.5,medium,x)}
\text{plac3=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 0,-1,-10,-1,0,-1.2,0,-0.8
text blue,0.5,-1,medium,A
text blue,-10,-1,medium,x)}
\text{plac4=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10,-1,-1,-1,-1,rapporteurperso8.jpg
linewidth 2
segments blue, 0,0,-10,0,0,-0.2,0,0.2
text blue,0.5,2,medium,A
text blue,-10,1.5,medium,x
)}
\text{plac5=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10.1,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 0,0,10,0, 0,-0.2,0,0.2
text blue,-0.5,2,medium,A
text blue,9.2,1.5,medium,x)}
\text{plac6=draw(200,200
xrange -10,10
yrange -10,10
copy -10.2,10.1,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, -6.2,0,10,0,-6.2,-0.2,-6.2,0.2
text blue,-6,1.5,medium,A
text blue,9.2,1.5,medium,x)}
\text{plac7=draw(200,200
xrange -10,10
yrange -10,9.9
copy -10.2,9.8,-1,-1,-1,-1,rapporteurperso7.jpg
linewidth 2
segments blue, 0,-1,10,-1,0,-1.2,0,-0.8
text blue,-0.5,-1.5,medium,A
text blue,9.2,-1,medium,x)}
\text{plac8=draw(200,200
xrange -10,10
yrange -10,10
copy -10.3,10,-1,-1,-1,-1,rapporteurperso9.jpg
linewidth 2
segments blue, 0,0,10,0,0,-0.2,0,0.2
text blue,-0.5,2,medium,A
text blue,9.2,1.5,medium,x
)}
\matrix{reps=<img src="\plac1" alt="">,1
<img src="\plac2" alt="">,2
<img src="\plac3" alt="">,2
<img src="\plac4" alt="">,2
<img src="\plac5" alt="">,1
<img src="\plac6" alt="">,2
<img src="\plac7" alt="">,2
<img src="\plac8" alt="">,2}

\text{ch=shuffle(8)}
\text{fig=item(1,row(\ch[1],\reps)),item(1,row(\ch[2],\reps)),
item(1,row(\ch[3],\reps)),item(1,row(\ch[4],\reps))}
\text{r=item(2,row(\ch[1],\reps)),item(2,row(\ch[2],\reps)),item(2,row(\ch[3],\reps)),item(2,row(\ch[4],\reps))}
#endif
#if defined TARGET_oefconstangl4
\integer{ang1=random(20,30,40,50,60,70,80,110,120,130,140,150,160)}

\text{plac1=draw(300,200
xrange -15,15
yrange -4,16
copy -15.4,15.2,-1,-1,-1,-1,rapporteurperso6.jpg
linewidth 2
segment cos(\ang1*pi/180)*13.5,sin(\ang1*pi/180)*13.5,cos(\ang1*pi/180)*14.5,sin(\ang1*pi/180)*14.5,blue
segments blue, 0,0,-15,0, 0,-0.2,0,0.2
text blue,0.5,2,medium,A
text blue,-15,1.5,medium,x)}

\text{plac2=draw(300,200
xrange -15,15
yrange -4,16
copy -15.4,15.2,-1,-1,-1,-1,rapporteurperso6.jpg
linewidth 2
segment cos(\ang1*pi/180)*13.5,sin(\ang1*pi/180)*13.5,cos(\ang1*pi/180)*14.5,sin(\ang1*pi/180)*14.5,blue
segments blue, 0,0,15,0,0,-0.2,0,0.2
text blue,-0.5,2,medium,A
text blue,14.2,1.5,medium,x)}

\text{nom=slib(lang/fname fr,girl)}
\text{fig=<img src="\plac1" alt="">,<img src="\plac2" alt="">}
\integer{ch=randint(1..2)}
\if{\ch=1}{\integer{ang=180-\ang1}}{\integer{ang=\ang1}}
\integer{ang2=180-\ang}
#endif
\statement{
\name_enonce
<table class="wimscenter wimsborder"><tr><td>
\fig[1]</td><td>\fig[2]</td></tr>
<tr><td>\embed{r1}</td><td>\embed{r2}</td></tr>
<tr><td>\fig[3]</td><td>\fig[4]</td></tr>
<tr><td>\embed{r3}</td><td>\embed{r4}</td></tr>
</table>}
\answer{}{\r[1];\rep}{type=menu}
\answer{}{\r[2];\rep}{type=menu}
\answer{}{\r[3];\rep}{type=menu}
\answer{}{\r[4];\rep}{type=menu}
