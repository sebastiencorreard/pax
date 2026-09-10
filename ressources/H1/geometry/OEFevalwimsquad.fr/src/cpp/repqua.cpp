target=oefrepqua1 oefrepqua2 oefrepqua3 oefrepqua4 oefrepqua5

\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\format{html}
#if defined TARGET_oefrepqua1
\integer{m1=randint(35..70)}
\text{tricode=xrange -150,150
yrange -150,150
linewidth 1
text black,-145,15,medium,A
text black,140,15,medium,B
rotate -45
poly black,0,0,0,100,100,100,100,0
rotate 135
poly black,0,0,0,100,100,100,100,0}
\integer{mm=2*\m1*sqrt(2)}
#endif
#if defined TARGET_oefrepqua2
\integer{m1=randint(35..65)}
\text{tricode=xrange -150,150
yrange -150,150
linewidth 1
text black,-145,15,medium,A
text black,140,15,medium,B
rotate -135
poly black,-20,-20,-20,60,60,60,60,-20
poly black,20,-20,100,-20,100,-100,20,-100
rotate 45
poly black,-20,-20,-20,60,60,60,60,-20
poly black,20,-20,100,-20,100,-100,20,-100}
\integer{mm=5*\m1*sqrt(2)/2}
#endif
#if defined TARGET_oefrepqua1 || defined TARGET_oefrepqua2
\real{mi=(\mm-1)/10}
\real{ma=(\mm+1)/10}
\real{m1=\m1/10}
#endif
#if defined TARGET_oefrepqua3
\integer{m1=randint(4..8)}
\integer{m2=randint(\m1+1..12)}
\text{tricode=xrange -170,130
yrange -80,220
linewidth 1
triangle 0,0,-150,0,-150,120,black
triangle 0,0,0,120,-150,120,black
text black,-160,130,medium,A
text black,85,185,medium,B
rotate -38.5
triangle 0,0,-150,0,-150,120,black
triangle 0,0,0,120,-150,120,black
rotate -77
triangle 0,0,-150,0,-150,120,black
triangle 0,0,0,120,-150,120,black}
\integer{mm=20*\m1}
\real{mi=(\mm-2)/10}
\real{ma=(\mm+2)/10}
#endif
#if defined TARGET_oefrepqua4
\integer{m1=randint(3..6)}
\integer{m2=randint(\m1+1..10)}
\text{tricode=xrange -150,150
yrange -150,150
linewidth 1
poly black,0,120,60,40,0,-40,-60,40
text black,-5,140,medium,A
text black,130,-30,medium,B
poly black,60,40,120,-40,60,-120,0,-40
poly black,-60,40,0,-40,-60,-120,-120,-40}
\integer{mm=20*sqrt(\m1^2/4+\m2^2/4)}
\real{mi=(\mm-2)/10}
\real{ma=(\mm+2)/10}
#endif
#if defined TARGET_oefrepqua5
\integer{m1=randint(3..5)}
\integer{m2=randint(\m1+2..10)}
\text{tricode=xrange -150,150
yrange -150,150
linewidth 1
poly black,0,0,-30,70,0,140,30,70
text black,-70,-40,medium,A
text black,70,-40,medium,B
rotate -46
poly black,0,0,-30,70,0,140,30,70
rotate -92
poly black,0,0,-30,70,0,140,30,70
rotate 46
poly black,0,0,-30,70,0,140,30,70
rotate 92
poly black,0,0,-30,70,0,140,30,70}

\real{ang=(2*pi-10*atan(\m1/\m2))/2}
\integer{mm=20*sqrt(\m1^2/4+\m2^2/4)*sin(\ang)}
\real{mi=(\mm-2)/10}
\real{ma=(\mm+2)/10}
#endif
\text{fig=draw(300,300
\tricode)}
\text{figurl=<img src="\fig" alt="">}
\text{figtikz=drawtikz(300,300
\tricode)}
\statement{<div class="wims_columns">
 <div class="medium_size img_col">\figurl</div>
 <div class="medium_size text_col">
 \name_enonce
#if defined TARGET_oefrepqua1 || defined TARGET_oefrepqua2
\name_enonce2 \m1 cm.
#endif
#if defined TARGET_oefrepqua3 || defined TARGET_oefrepqua4 || defined TARGET_oefrepqua5
\name_enonce2[1] \m1 cm \name_enonce2[2] \m2 cm.
#endif
<p>\name_question:</p>
<div class="spacer"> <label for="reply1">AB =</label> \embed{r1,5} cm.</div>
</div></div>
}
\answer{}{\mi,\ma}{type=range}

\latex{
\begin{statement}
#if defined TARGET_oefrepqua1 || defined TARGET_oefrepqua2
\name_enonce2 \m1 cm.
#endif
#if defined TARGET_oefrepqua3 || defined TARGET_oefrepqua4 || defined TARGET_oefrepqua5
\name_enonce2[1] \m1 cm \name_enonce2[2] \m2 cm.
#endif
\par
\name_question:
\(AB =\cdots\) cm.
\begin{center}
\figtikz
\end{center}
\end{statement}}
