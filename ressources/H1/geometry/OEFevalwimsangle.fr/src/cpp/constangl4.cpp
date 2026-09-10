target=oefconstangl4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ang1=random(20,30,40,50,60,70,80,110,120,130,140,150,160)}

\text{plac1=draw(300,200
xrange -15,15
yrange -4,16
copy -15.4,15.2,-1,-1,-1,-1,rapporteurperso6.jpg
linewidth 2
segment cos(\ang1*pi/180)*13.5,sin(\ang1*pi/180)*13.5,cos(\ang1*pi/180)*14.5,sin(\ang1*pi/180)*14.5,blue
segments blue,0,0,-15,0,0,-0.2,0,0.2
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

\statement{
\nom \name_enonce[1;1] \(\widehat{xAy}) \name_enonce[1;2] \ang2 °.
<ul class="wims_nopuce">
<li>\name_enonce[2;] &#91;Ax&#41;.
</li><li>
\name_enonce[3;]
</li></ul>
<div class="wimscenter">\fig[\ch]</div>

\name_enonce[4;]? : \embed{r1}.
<div class="spacer">
\name_enonce2[1;1] \nom \name_enonce2[1;2],
<label for="reply2">\name_enonce2[2;]</label>: \embed{r2,3}°
</div>}

\answer{}{2;\name_ouinon}{type=menu}
\answer{}{\ang}{type=raw}
