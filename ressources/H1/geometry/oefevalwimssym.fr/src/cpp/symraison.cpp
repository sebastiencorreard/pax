target=oefsymraison1 oefsymraison2 oefsymraison3 oefsymraison4 oefsymraison5
#define TITRE Raisonnements
#include "author.inc"
\keywords{symmetry}
\precision{1000}
#if defined TARGET_oefsymraison1
# define NUM 1
\text{geom=draw(300,300
segment 150,0,150,300,red
segment 75,150,225,150,black
segment 75,150,150,75,black
segment 150,75,225,150,black
segment 70,145,80,155,black
segment 70,155,80,145,black
segment 220,145,230,155,black
segment 230,145,220,155,black
text black,60,140,medium,A
text black,235,140,medium,B
text black,140,65,medium,C
text black,140,135,medium,M
text black,155,10,medium,D1
)}
\integer{l1=randint(5..29)}
\integer{l2=randint(1..\l1-1)}
\integer{a1=arccos(\l2/\l1)/pi*180}
\integer{rep1=(\l1+\l2)*2}
\text{rep1=\rep1 cm}
\text{rep2=\a1 °}
\text{enonc1=<li>Le point B est le symétrique du point A par rapport à la droite D1</li>
<li>Le segment [AC] mesure \l1 cm et le segment [AM] mesure \l2 cm.</li>}
 \text{question= Calculer le périmètre du triangle ABC:}
\text{enonc2=L'angle \(\widehat{CAB}) mesure \rep2.}
\text{angl=CBA}
#endif
#if defined TARGET_oefsymraison2
# define NUM 2
\text{geom=draw(300,300
segment 150,0,150,300,red
square 50,80,100,black
square 150,80,100,black

text black,45,185,medium,A
text black,140,185,medium,B
text black,140,65,medium,C
text black,45,65,medium,D
text black,250,185,medium,F
text black,250,65,medium,G

text black,155,10,medium,D1
)}
\integer{l1=randint(3..19)}
\integer{rep1=\l1*6}
\text{rep1=\rep1 cm}
\text{rep2=90°}

\text{enonc1=<li>Le quadrilatère ABCD est un carré.</li>
<li>Le point F est le symétrique du point A par rapport à la droite D1.</li>
<li>Le segment [AB] mesure \l1 cm.</li>}
\text{question=Calculer le périmètre du quadrilatère AFGD:}
\text{enonc2=L'angle \(\widehat{DAB}) mesure \rep2.}
\text{angl=BFG}
#endif

#if defined TARGET_oefsymraison3
# define NUM 3
\text{geom=draw(300,300
segment 100,0,100,300,red
segment 0,150,300,150,red
segment 20,150,100,70,black
segment 100,70,239,150,black
segment 100,230,239,150,black
segment 20,150,100,230,black
segment 50,150,100,70,black
segment 150,150,100,70,black
segment 50,150,100,230,black
segment 150,150,100,230,black
text black,10,135,medium,A
text black,90,60,medium,B
text black,245,135,medium,C
text black,90,230,medium,D
text black,45,135,medium,E
text black,90,135,medium,F
text black,155,135,medium,G
)}
\integer{l1=randint(5..12)}
\integer{l2=randint(\l1+1..29)}
\integer{l3=randint(2..\l1-1)}
\integer{l4=randint(5..12)}
\integer{a1=arctan((\l1-\l3)/\l4)/pi*180}
\integer{a2=2*\a1}
\integer{rep1=\l3+\l2-\l1}
\text{rep1=\rep1 cm}
\text{rep2=\a2 °}

\text{enonc1=<li>Le point G est le symétrique du point E par rapport à la droite (BD).</li>
  <li>Le segment [AF] mesure \l1 cm, le segment [FC] mesure \l2 cm et le segment [AE] mesure \l3 cm.</li>}
\text{question=Calculer la longueur du segment [GC]:}
\text{enonc2=L'angle \(\widehat{EBF}) mesure \a1 °.}
\text{angl=EBG}
#endif

#if defined TARGET_oefsymraison4
# define NUM 4
\text{geom=draw(300,300
rect 50,90,250,210,black
poly black,50,90,158,34,250,210,142,266
line 20,72,280,228,red
line 50,210,158,34,black
line 250,90,142,266,black
text black,40,70,medium,A
text black,255,75,medium,B
text black,250,220,medium,C
text black,40,215,medium,D
text black,140,270,medium,F
text black,150,20,medium,G)}
\integer{l1=randint(6..29)}
\integer{l2=randint(3..\l1-1)}
\integer{rep1=(\l1+\l2)*2}
\text{rep1=\rep1 cm}
\text{rep2=90°}
\text{enonc1=<li>Le quadrilatère ABCD est un rectangle.</li>
 <li>Le point F est le symétrique du point B par rapport à la droite (AC).</li>
 <li>Le point G est le symétrique du point D par rapport à la droite (AC).</li>
 <li>Le segment [AB] mesure \l1 cm et le segment [BC] mesure \l2 cm.</li>}
\text{question=Calculer le périmètre du quadrilatère AGCF:}
\text{angl=CFA}
#endif
#if defined TARGET_oefsymraison5
# define NUM 5
\text{geom=draw(300,300
segment 270,80,30,80,black
segment 10,230,290,69,red
segment 150,5,150,295,red
segment 150,10,30,80,black
segment 150,10,270,80,black
segment 30,80,150,290,black
segment 270,80,150,290,black
segment 150,150,30,80,black

text black,160,2,medium,A
text black,155,150,medium,B
text black,20,85,medium,C
text black,275,85,medium,E
text black,160,285,medium,F
)}
\real{l1=randint(40..99)/10}
\real{l2=rint(\l1*sqrt(3)*10)/10}
\integer{a1=arccos(\l2/\l1)/pi*180}
\integer{rep1=(\l1+\l2)*20}
\text{rep1=\rep1 mm}
\text{rep2=120°}

\text{enonc1=<li>Le triangle ABC est un triangle équilatéral.</li>
<li>Le point E est le symétrique du point C par rapport à la droite (AF).</li>
<li>Le point F est le symétrique du point C par rapport à la droite (BE).</li>
<li>Le segment [AB] mesure \l1 cm et le segment [CE] mesure \l2 cm.</li>
}
\text{question=Calculer le périmètre du quadrilatère ACFE:}
\text{enonc2=Tous les angles d'un triangle équilatéral mesurent 60°.}
\text{angl=CAE}
#endif
#include "lang_titles.inc"
\statement{
<div class="wims_columns">
  <div class="medium_size">
    <img src="\geom" alt="">
  </div>
  <div class="medium_size">
    <ul>
    \enonc1
    <li>
    <label for="reply1">\question</label> \embed{r1,10}
    </li>
    \if{\enonc2!=}{
      <li>\enonc2</li>
    }
    <li>
    <label for="reply2">Donner la mesure de l'angle \(\widehat{\angl}) :</label>
    \embed{r2,10}.
    </li>
    </ul>
  </div>
</div>
}

\answer{}{\rep1}{type=units}
\answer{}{\rep2}{type=units}
