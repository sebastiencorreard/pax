target=trajet
\text{name_prem=première,seconde}
#include "author.inc"
#include "lang_titles.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang.inc"
\integer{temps1= randint(2..3)}
\real{pause1=randint(1..2)/randint(2,4)}
\real{temps2=randint(1..2)}
\real{pause2=randint(1..2)/randint(2,4)}
\real{temps3=randint(1..2)}
\real{heure1=randint(7..9)}
\real{heure2=\heure1+\temps1}
\real{heure3=\heure2+\pause1}
\real{heure4=\heure3+\temps2}
\real{heure5=\heure4+\pause2}
\real{heure6=\heure5+\temps3}
\real{heure6h=floor(\heure6)}
\real{heure6mn= (\heure6-\heure6h)*60}
\text{Heure6 =\heure6mn <>0 ? \heure6h h \heure6mn min : \heure6h h}
\integer{v1= 10*randint(9..12)}
\integer{v2= 10*randint(6..9)}
\integer{v3=10*randint(9..12)}
\real{d1=\v1*\temps1}
\text{dessin= }
\for{i=0 to 20}{
  \integer{h=\i+\heure1}
  \integer{k=\i*100}
  \text{dessin=\dessin
text black, \heure1+\i,-0.5,medium,\h \name_hkm[1]
text black,\heure1-1.5,\i*100,medium,\k \name_hkm[2]
}}
\real{d2=\v1*\temps1+\v2*\temps2}
\real{dfinal=\d2+\v3*\temps3}

\real{tfinal=\temps1+\pause1+\temps2+\pause2+\temps3}
\real{vfinal=ceil(\dfinal/\tfinal)}
\real{maxy=\dfinal+2}
\real{rep1=(\pause1+\pause2)*60}
\text{choix=random(1,2)}
\text{prem=randitem(\name_prem[1],\name_prem[2])}
\real{rep2=p isin \prem? \temps1:\temps1+\pause1+\temps2}
\integer{rep2min= floor(\rep2*60)}

\text{rep3=p isin \prem? \d1:\d2}
\text{rep4=\choix=1 ? \heure6h h \heure6mn min :\v3 km/h}
\text{hk=\choix=1 ? \name_hkm[1]:\name_hkm[3]}
\real{rep5=\vfinal}
\text{heuv=\choix=1? \name_heuv[1]:\name_heuv[2]}
\steps{reply1,reply2, reply3
reply4
reply5}
text{name_question2=wims(replace internal XXXX by in \name_question2)}
\statement{ \name_enonce[1] \dfinal \name_enonce[2]:
<div class="wimscenter"> \draw{500,250}{
xrange \heure1-2,\heure6+1
yrange -40,\maxy+1
\dessin
hline \heure1,0, black
vline \heure1,0, black
parallel \heure1-0.1,0,\heure1+0.1,0,0,10,100,blue
parallel \heure1-0.5,0,\heure1+0.5,0,0,100,10,black
parallel \heure1,-1,\heure1,1,1,0,10,black
parallel \heure1,-12,\heure1,12,1,0,20,black
parallel \heure1,-5,\heure1,5,0.25,0,80,blue
linewidth 2
polyline red, \heure1,0,\heure2,\d1,\heure3,\d1,\heure4,\d2, \heure5,\d2, \heure5+\temps3, \dfinal
arrow \heure5,\d2,\heure5+\temps3, \dfinal,10, red
linewidth 1
dsegment \heure2,\d1,\heure2,0,black
dsegment \heure3,\d1,\heure3,0,black
dsegment \heure4,\d2,\heure4,0,black
dsegment \heure5,\d2,\heure5,0,black
dsegment \heure2,\d1,\heure1,\d1,black
dsegment \heure4,\d2,\heure1,\d2,black
}</div>
\if{\step=1}{\name_question1[1;]:
<ul><li>
\name_question1[2;]? \embed{reply 1,8}
</li><li> \name_question1[3;1] \prem \name_question1[3;2]?
\embed{reply 2,8}
</li><li>
\name_question1[4;]?
\embed{reply 3,8}
</li></ul>}
\if{\step=2}{
  \if{\choix=1}{\name_question2[1;]
  \v3 km/h. \name_question2[2;1]?}{\name_question2[2;2] \Heure6.
  \name_question2[3;]?}
  <div class="wimscenter">\embed{reply 4, 8}</div>}
\if{\step=3}{\name_question3[1] \Heure6 \name_question3[2] \v3 km/h.
  \name_question3[3]?
<div class="wimscenter">\embed{reply 5,8}</div>}
<div class="wims_instruction"> \name_instruction</div>}
\answer{\name_answer[1]:}{\rep1 min}{type=units}
\answer{\prem \name_answer[2]}{\rep2min min}{type =units}
\answer{\name_answer[3]}{\rep3 km}{type=units}
\answer{\heuv}{\rep4}{type=units}
\answer{ }{\rep5 km/h}{type=units}
