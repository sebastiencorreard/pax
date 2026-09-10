target=angle1 angle2 angle3

#include "lang_titles.inc"
#include "lang.inc"
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{1000}
#if defined TARGET_angle1
\integer{ang =randint(10..70)}
\integer{angle1=36}
\integer{angle2=\ang}
\integer{angle3=180-2*\ang}
\integer{angle4=144-2*\ang}
\text{angr=\ang}
\text{anga=\angle1}
\text{angb=\angr}
#endif
#if defined TARGET_angle2
\integer{ang = randint(10..70)}
\integer{angle1=180}
\integer{angle2=144-\ang}
\integer{angle3=36}
\integer{angle4=\ang}
\text{angr=\ang}
\text{anga=\angle3}
\text{angb=\angr}
#endif
#if defined TARGET_angle1 || defined TARGET_angle2
\text{dessin=
xrange -20,20
yrange -20,20
triangle -15,-11,-15,11,0,11,black
triangle 0,11,4,-11,-9,-2.2,black
triangle -15,-11,-9,-2.2,4,-11,black
triangle 0,11,19,11,4,-11,black
segment -4,-7,-2,-5,red
segment -5,6,-3,4,red
text black,-17,13,medium,A
text black,-17,-10,medium,B
text black,6,-10,medium,C
text black,18,14,medium,D
text black,0,14,medium,E
text black,-11,0,medium,F}
#endif
#if defined TARGET_angle3
\integer{anga = randint(10..40)}
\integer{angb = randint(50..120)}
\integer{angc = randint(10..50)}
\integer{angle1=180-\angb}
\integer{angle2=\angb-\anga}
\integer{angle3=180-\angb-\angc}
\integer{angle4=180-\anga-\angc}
\text{angr=\angc}

\text{dessin=xrange -20,20
yrange -20,20
triangle 0,11,4,-11,-15,-11,black
triangle 0,11,19,-11,4,-11,black
text black,-17,-10,medium,B
text black,6,-12,medium,C
text black,18,-13,medium,D
text black,0,14,medium,A}
#endif

\statement{<div class="wims_columns">
 <div class="medium_size img_col">
\draw{200,200}{\dessin}
</div>
<div class="medium_size txt_col">
#if defined TARGET_angle1 || defined TARGET_angle2
\name_question1
#endif
<p>\name_question2[1] \anga°. \name_question2[2] \angb°.
#if defined TARGET_angle3
\name_question2[3] \angr°.
#endif
</p>
<p>\name_question</p>
</div></div>}
#if defined TARGET_angle1
\answer{\name_ans \(\widehat{A E B}\)=}{\angle1}{type=chset}
\answer{\name_ans \(\widehat{B E C}\)=}{\angle2}{type=chset}
\answer{\name_ans \(\widehat{E F C}\)=}{\angle3}{type=chset}
\answer{\name_ans \(\widehat{F C B}\)=}{\angle4}{type=chset}
#endif
#if defined TARGET_angle2
\answer{\name_ans \(\widehat{D E C}\)=}{\angle2}{type=chset}
\answer{\name_ans \(\widehat{E D C}\)=}{\angle3}{type=chset}
\answer{\name_ans \(\widehat{E C D}\)=}{\angle4}{type=chset}
#endif
#if defined TARGET_angle3
\answer{\name_ans \(\widehat{B C A}\)=}{\angle1}{type=chset}
\answer{\name_ans \(\widehat{B A C}\)=}{\angle2}{type=chset}
\answer{\name_ans \(\widehat{C A D}\)=}{\angle3}{type=chset}
#endif
