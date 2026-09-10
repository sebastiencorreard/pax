target=oefconstcompl1 oefconstcompl2 oefconstcompl3 oefconstcompl4 oefconstcompl5
\langage{fr}
#include "author.inc"
\format{html}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefconstcompl1
\integer{a=randint(40..80)}
\integer{b=randint(\a/2+5..70)}
#endif
#if defined TARGET_oefconstcompl2
\integer{a=randint(25..50)}
\integer{b=randint(\a+5..70)}
#endif
#if defined TARGET_oefconstcompl3
\integer{a=randint(40..70)}
\integer{b=randint(\a+15..100)}
#endif
#if defined TARGET_oefconstcompl4
\integer{a=randint(40..60)}
\integer{b=randint(\a+10..80)}
#endif
#if defined TARGET_oefconstcompl5
\integer{a=randint(40..60)}
\integer{b=randint(20..40)}
#endif
\real{a=\a/10}
\real{b=\b/10}
#if defined TARGET_oefconstcompl1
\text{figcode=xrange -100,100
yrange -100,100
square -50,10,150,black
triangle -50,-90,50,-90,0,80,black
triangle -50,10,50,10,0,80,black
circle -50,-40,10,red
circle 0,-90,10,red
square -50,10,10,red
square 43,10,10,red
square -50,-83,10,red
segment -28,48,-22,42,red
segment 28,48,22,42,red
text black,0,90,medium,A
text black,55,-90,medium,B
arrow2 -60,-90,-60,10,10,black
arrow2 -7,83,-57,13,10,black
text black,-90,-40,medium,\a cm
text black,-70,48,medium,\b cm}
#endif
#if defined TARGET_oefconstcompl2
\text{figcode=xrange -100,100
yrange -100,100
rect -60,80,60,-80,black
poly black,-60,0,0,80,60,0,0,-80
circle -30,-40,10,red
circle 30,-40,10,red
square -60,80,10,red
square 53,80,10,red
square -60,-73,10,red
circle 30,40,10,red
circle -30,40,10,red
text black,0,90,medium,A
text black,65,5,medium,B
arrow2 -70,0,-70,80,10,black
arrow2 -60,90,0,90,10,black
text black,-40,98,medium,\a cm
text black,-98,48,medium,\b cm}
#endif
#if defined TARGET_oefconstcompl3
\text{figcode=xrange -100,100
yrange -100,100
poly black,-90,0,0,60,90,0,0,-60
poly black,-60,0,0,60,60,0,0,-60
segment -90,0,-60,0,black
segment 90,0,60,0,black
circle -30,-30,10,red
circle 30,-30,10,red
circle -30,30,10,red
circle 30,30,10,red
segment -47,35,-41,29,red
segment 47,35,41,29,red
segment -60,-25,10,red
segment -47,-35,-41,-29,red
segment 47,-35,41,-29,red
text black,60,10,medium,A
text black,90,10,medium,B
segment -54,4,-50,0,red
segment -50,0,-54,-4,red
segment 54,4,50,0,red
segment 50,0,54,-4,red
segment 4,-54,0,-50,red
segment 0,-50,-4,-54,red
arrow2 -95,5,-5,67,10,black
arrow2 -52,-7,7,52,10,black
text black,-20,20,medium,\a cm
text black,-80,48,medium,\b cm}
#endif
#if defined TARGET_oefconstcompl4
\text{figcode=xrange -100,100
yrange -100,100
square -40,40,120,black
poly black,-40,0,0,40,90,-50,50,-90
segment 40,-40,90,-50,black
segment 40,-40,50,-90,black
circle -20,-40,10,red
circle 20,-40,10,red
circle -20,40,10,red
circle 20,40,10,red
circle -40,-20,10,red
circle 40,-20,10,red
circle -40,20,10,red
circle 40,20,10,red
square -40,40,10,red
square -40,-33,10,red
square 33,40,10,red
text black,33,-30,medium,A
text black,90,-40,medium,B
segment 20,-64,24,-60,red
segment 64,-20,60,-24,red
arrow2 -10,-45,40,-95,10,black
arrow2 -40,45,40,45,10,black
text black,-10,55,medium,\a cm
text black,-15,-65,medium,\b cm}
#endif
#if defined TARGET_oefconstcompl5
\text{figcode=xrange -100,100
yrange -100,100
triangle -40,-70,40,-70,0,0,black
triangle 40,-70,0,0,75,-50,black
triangle -40,-70,0,0,-75,-50,black
triangle -75,-50,0,0,0,90,black
triangle 75,-50,0,0,0,90,black
circle -23,-40,10,red
circle 23,-40,10,red
circle 0,-70,10,red
text black,-7,97,medium,A
text black,-7,-60,medium,B
segment -4,38,4,42,red
segment -4,36,4,40,red
segment 60,-62,56,-58,red
segment -60,-62,-56,-58,red
segment -32,-28,-38,-22,red
segment -34,-28,-40,-22,red
segment 32,-28,38,-22,red
segment 34,-28,40,-22,red
segment 37,-65,44,-61,red
segment 44,-61,46,-66,red
segment -37,-65,-44,-61,red
segment -44,-61,-46,-66,red
dsegment 0,0,0,-70,black
arrow2 77,-58,44,-80,10,black
arrow2 -40,-80,40,-80,10,black
text black,-10,-85,medium,\a cm
text black,60,-75,medium,\b cm}
#endif
\text{fig=draw(300,300
\figcode)}
\text{figtikz=drawtikz(300,300
\figcode)}

\text{fig=<img src="\fig" alt="">}
#if defined TARGET_oefconstcompl1
\integer{rep=rint(sqrt(\a*\a+\b*\b+2*\a*sqrt(\b*\b-\a*\a/4))*10)}
#endif
#if defined TARGET_oefconstcompl2
\integer{rep=rint(sqrt(\a*\a+\b*\b)*10)}
#endif
#if defined TARGET_oefconstcompl3
\integer{rep=rint((sqrt(\b*\b-\a*\a/2)-\a/sqrt(2))*10)}
#endif
#if defined TARGET_oefconstcompl4
\integer{rep=rint(sqrt(\b*\b+\a*\a/4-\a*\b*sqrt(2)/2)*10)}
#endif
#if defined TARGET_oefconstcompl5
\integer{rep=rint((sqrt(\a*\a+\b*\b)+\a*sqrt(3)/2)*10)}
#endif
\real{m=(\rep-1)/10}
\real{n=(\rep+1)/10}

\statement{<div class="wims_columns">
 <div class="medium_size img_col">\fig</div>
 <div class="medium_size text_col">
\name_enonce[1]
<p>\name_enonce[2] AB.</p>
<div class="spacer"><label for="reply1">AB =</label> \embed{r1,6} cm.</div>
</div></div>
}

\answer{}{\m,\n}{type=range}

\latex{
\begin{statement}
\name_enonce[1]
<p>\name_enonce[2] AB.</p>
\par
\(A B\)= \(\cdots\) cm.
\begin{center}
  \figtikz
\end{center}
\end{statement}
}

