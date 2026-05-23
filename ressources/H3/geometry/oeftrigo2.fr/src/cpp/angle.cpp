target= anglesin anglecos angletan
#if defined TARGET_anglesin
# define NUM 1
#endif
#if defined TARGET_anglecos
# define NUM 2
#endif
#if defined TARGET_angletan
# define NUM 3
#endif
#include "lang_titles.inc"
#include "author.inc"
\precision{100000}
\text{size=100x35x1}
#include "common.inc"
#include "triangle.inc"

\integer{l1=random(25..100)}
\real{l1=\l1/10}
\integer{l2=random(25..100)}
\integer{l2=\l2=\l1?112}
\real{l2=\l2/10}

\text{angle=\widehat{\X2\X1\X3}}
\text{neq=\(\cos(\angle)\),\(\sin(\angle)\),\(\tan(\angle)\),\(\X1\X2\),\(\X1\X3\),\(\X2\X3\)}
\text{angle=\(\angle\)}

#if defined TARGET_anglesin  || defined TARGET_anglecos
\if{\l1>\l2}{
  \real{tmp=\l1}
  \real{l1=\l2}
  \real{l2=\tmp}
}
#endif
#if defined TARGET_anglesin
\text{fonct=sin}
\text{nom=le sinus}
\text{rfonct=arcsin}
\text{num=\(\X2\X3\)}
\text{den=\(\X1\X3\)}
\text{eq1=item(2,\neq)}
#endif
#if defined TARGET_anglecos
\text{fonct=cos}
\text{nom=le cosinus}
\text{rfonct=arccos}
\text{num=\(\X1\X2\)}
\text{den=\(\X1\X3\)}
\text{eq1=item(1,\neq)}
#endif
#if defined TARGET_angletan
\text{fonct=tan}
\text{nom=la tangente}
\text{rfonct=arctan}
\text{num=\(\X2\X3\)}
\text{den=\(\X1\X2\)}
\text{eq1=item(3,\neq)}
#endif

\text{res=\rfonct(\l1/\l2)*180/pi}

\text{val=\eq1,\den,\num,\l2,\l1}

\integer{prec=random(1..3)}
\text{precision=degré,dixième de degré,centième de degré}
\text{precision=item(\prec,\precision)}
\integer{tmp=\res*10^(\prec-1)}
\real{sol=\tmp/10^(\prec-1)}

\text{enonce=Le triangle \(\X1\X2\X3\) est rectangle en \(\X2\).
  Le côté \num mesure \l1 cm et le côté \den mesure \l2 cm.
  Quel est l'arrondi, au \precision, de la mesure de l'angle \angle&nbsp;}

\if{\confparm2=1}{
\matrix{test=r1,r2,r3
r4,r5,r6
r7}
}{
\matrix{test=r7}
}
\steps{\test}
\statement{
  \if{\confparm1=1}{
    <div class="wims_columns">
    <div class="medium_size img_col">\draw{\xrange,\yrange}{\dessin}
     <div class="wims_instruction">Le dessin n'est pas à l'échelle.</div>
    </div>
    <div class="medium_size text_col">\enonce?</div>
    </div>
}{
<div>\enonce?</div>}
\if{\confparm2=1}{
  Pour résoudre l'exercice répondez d'abord aux questions suivantes :
<div>
<b>Question 1</b> :
Dans le triangle \(\X1\X2\X3\) rectangle en \(\X2\), trouvez une relation
  faisant intervenir l'angle \angle et les longueurs des côtés \den et \num.
</div>
\if{\step=1}{
<table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\embed{reply1,\size}</td>
  <td rowspan="3"> \big1=\big2 </td>
  <td>\embed{reply2,\size}</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td>\embed{reply3,\size}</td>
  </tr>
 </table>}
{<table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\eq1</td>
  <td rowspan="3"> \big1=\big2 </td>
  <td>\num</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td>\den</td>
  </tr>
 </table>
<b>Question 2</b> : Remplacez, dans l'équation de la question 1,
  les expressions connues par leurs valeurs.
\if{\step=2}{
<table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\embed{reply 4,\size}</td>
  <td rowspan="3"> \big1=\big2 </td>
  <td>\embed{reply 5,\size}</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td>\embed{reply 6,\size}</td>
  </tr>
 </table>}
{<table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\eq1</td>
  <td rowspan="3">\big1=\big2</td>
  <td>\l1</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td>\l2</td>
  </tr>
 </table>
<b>Question 3</b> : Répondre à l'exercice.
}}
}}

\answer{Fonction}{\eq1|\neq}{type=clickfill}
\answer{Numérateur}{\num|\neq}{type=clickfill}
\answer{Dénominateur}{\den|\neq}{type=clickfill}
\answer{Fonction}{\eq1|\val}{type=clickfill}
\answer{Numérateur}{\l1|\val}{type=clickfill}
\answer{Dénominateur}{\l2|\val}{type=clickfill}
\answer{Réponse}{\sol}{type=numexp}

\if{\confparm2<>1}{\hint{Utiliser \nom de l'angle \angle.}}
