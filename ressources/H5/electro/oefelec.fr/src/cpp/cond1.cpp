target=cond1

#include "author.inc"
#include "lang_titles.inc"

\precision{100}

\real{R1=randint(100..1000)/10}
\integer{R2=randint(100..1000)/10}
\integer{R3=randint(100..1000)/10}
\integer{U=randint(6..24)}
\text{choix=série,parallèle}
\integer{cho=random(1,1,2,2)}
\text{serie=item(\cho,\choix)}
\real{R=\cho=1 ? \R1+\R2+\R3:(1/\R1+1/\R2+1/\R3)^(-1) }
\text{choix2=randint(1,2,3)}
\real{I=round(10^3*\U/\R)/1000}

\real{rep= \choix2=1? \I:\U}
\real{rep= \choix2=3? \R3}
\text{unite=\choix2=1? A: V}
\text{unite=\choix2=3? ohms}
\text{question=\choix2=1? Intensité:Tension}
\text{question=\choix2=3?Résistance}
#include "lang.inc"
\statement{\name_statement[1;] \(R_1), \(R_2) et \(R_3).
\name_statement[2;] \serie \name_statement[3;]
<div class="wimscenter">
\if{\cho=1}{\draw{150,150}
{xrange 0,5
yrange 0,5
segment 1,2.8,1,2,black
segment 1,2,1.3,2,black
segment 2.1,2,2.9,2,black
segment 3.7,2,4,2,black
segment 4,2,4,4,black
segment 4,4,2.9,4,black
segment 2.1,4,1,4,black
segment 1,4,1,3,black
segment 0.5,3,1.5,3,black
segment 0.8,2.8,1.2,2.8,black
polyline black,2.1,4.1,2.9,4.1,2.9,3.9,2.1,3.9,2.1,4.1
segment black,1.3,1.9,2.1,1.9,2.1,2.1,1.3,2.1,1.3,1.9
polyline black,2.9,1.9,3.7,1.9,3.7,2.1,2.9,2.1,2.9,1.9
text red,2.4,4.5,medium,R1
text red,1.6,1.8,medium,R2
text red,3.2,1.8,medium,R3
}
}{\draw{150,150}
{xrange 0,5
yrange 0,5
polyline black,1,2.8,1,2,4,2,4,4,1,4,1,3
segment 2,2,2,2.6,black
segment 2,3.4,2,4,black
segment 3,2,3,2.6,black
segment 3,3.4,3,4,black
segment 4,2.6,4,3.4,white
segment 0.5,3,1.5,3,black
segment 0.8,2.8,1.2,2.8,black
polyline black,1.9,2.6,1.9,3.4,2.1,3.4,2.1,2.6,1.9,2.6
polyline black,2.9,2.6,2.9,3.4,3.1,3.4,3.1,2.6,2.9,2.6
polyline black,3.9,2.6,3.9,3.4,4.1,3.4,4.1,2.6,3.9,2.6
text red,2.9,4.35,medium,R1
text red,1.8,1.8,medium,R2
text red,3.9,1.8,medium,R3
}
}
</div>
\if{\choix2<3 }{\name_choix1 \R1 ohms, \R2 ohms, \R3 ohms.}

\if{\choix2=1}{\name_choix2[1;] \U V. \name_choix2[2;]}

\if{\choix2=2}{\name_choix3}

\if{\choix2=3}{\name_choix4}
<div class="wims_instruction">
\name_instruction
</div>
}

\answer{\question}{\rep \unite}{type=units}
\real{test1=-1*\reply1+\U/\R}
\real{test2=-\reply1+\R*\I}
\feedback{\test1=0 and \cho=1 and \choix2=1}{\name_feedback1}
\feedback{\test2=0 and \cho=2 and \choix2=1}{\name_feedback2}
