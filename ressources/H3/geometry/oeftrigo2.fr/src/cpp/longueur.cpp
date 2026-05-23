target= longsin longcos longtan

#include "author.inc"
\precision{100000}
#if defined TARGET_longsin
# define NUM 1
#endif
#if defined TARGET_longcos
# define NUM 2
#endif
#if defined TARGET_longtan
# define NUM 3
#endif
#include "lang_titles.inc"
\text{size=90x35x1}
#include "common.inc"
\integer{l1=random(25..100)}
\real{l1=\l1/10}
\integer{vangle=random(30..60)}
\text{anglerad=\vangle*pi/180}

\integer{ch=random(1..2)}
#include "triangle.inc"

\text{angle=\widehat{\X2\X1\X3}}
\text{neq=\(\cos(\angle)\),\(\sin(\angle)\),\(\tan(\angle)\),\(\X1\X2\),\(\X1\X3\),\(\X2\X3\)}
\text{angle=\(\angle\)}

#if defined TARGET_longsin
\if{\ch=1}{
 \text{cote=\(\X2\X3\)}
 \text{inc=\X1\X3}
}{
 \text{cote=\(\X1\X3\)}
 \text{inc=\X2\X3}
}
\text{fonct=sin}
\text{nom=le sinus}
\text{eq1=item(2,\neq)}
\text{eq2=item(6,\neq)}
\text{eq3=item(5,\neq)}
\text{val1=\(\sin(\vangle)\)}
#endif

#if defined TARGET_longcos
\if{\ch=1}{
 \text{cote=\(\X1\X2\)}
 \text{inc=\X1\X3}
}{
 \text{cote=\(\X1\X3\)}
 \text{inc=\X1\X2}
}
\text{fonct=cos}
\text{eq1=item(1,\neq)}
\text{eq2=item(4,\neq)}
\text{eq3=item(5,\neq)}
\text{val1=\(\cos(\vangle)\)}
\text{nom=le cosinus}
#endif

#if defined TARGET_longtan
\if{\ch=1}{
 \text{cote=\(\X2\X3\)}
 \text{inc=\X1\X2}
}{
 \text{cote=\(\X1\X2\)}
 \text{inc=\X2\X3}
}
\text{fonct=tan}
\text{eq1=item(3,\neq)}
\text{eq2=item(6,\neq)}
\text{eq3=item(4,\neq)}
\text{val1=\(\tan(\vangle)\)}
\text{nom=la tangente}
#endif

\if{\ch=1}{
 \real{res=\l1/\fonct(\anglerad)}
 \text{sol3=\l1/\fonct(\vangle)}
 \text{asol3=\frac{\l1}{\fonct(\vangle)}}
}{
 \real{res=\fonct(\anglerad)*\l1}
 \text{sol3=\l1*\fonct(\vangle),\fonct(\vangle)*\l1}
 \text{asol3=\l1\times \fonct(\vangle)}
}

\integer{prec=random(1..3)}
\text{precision=dixième,centième,millième}
\text{precision=item(\prec,\precision)}
\integer{tmp=\res*10^\prec}
\real{sol=\tmp/10^\prec}

\if{\ch=1}{
 \text{val2=\l1}
 \text{val3=\(\inc\)}
}{
 \text{val3=\l1}
 \text{val2=\(\inc\)}
}
\text{val=\eq1,\eq2,\eq3,\val1,\l1}

\text{enonce=Le triangle \(\X1\X2\X3\) est rectangle en \(\X2\).
  L'angle \angle mesure \vangle degrés et le côté \cote mesure \l1 cm.
  Quelle est la longueur du côté \(\inc\)&nbsp;}
\text{instruction=Vous donnerez l'arrondi au \precision de centimètre.}

\if{\confparm2=1}{
 \matrix{test=r1,r2,r3
r4,r5,r6
r7
r8}
}{
 \matrix{test=r8}
}
\steps{\test}

\statement{\if{\confparm1=1}{
  <div class="wims_columns">
   <div class="medium_size img_col">
  \draw{\xrange,\yrange}{\dessin}
  <div class="wims_instruction">Le dessin n'est pas à l'échelle.</div>
  </div>
   <div class="medium_size text_col">\enonce?
   <div class="wims_instruction">\instruction</div></div>}
  {<div>\enonce?<div class="wims_instruction">\instruction</div>}
  </div>
  \if{\confparm2=1}{
  Pour résoudre l'exercice, répondez d'abord aux questions suivantes :
  <p>
  <b>Question 1</b> : Dans le triangle \(\X1\X2\X3\) rectangle en \(\X2\), trouvez une relation
  faisant intervenir l'angle \angle, les longueurs des côtés \(\inc\) et \cote.
  </p>
  \if{\step=1}{
  <table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\embed{reply1,\size}</td>
  <td rowspan="3"> = </td>
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
  <td rowspan="3"> = </td>
  <td>\eq2</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr><td>\eq3</td></tr>
 </table>
 <div class="spacer">
<b>Question 2</b>: Remplacez, dans l'équation de la question 1, les expressions connues
par leurs valeurs.</div>
\if{\step=2}{
<table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\embed{reply 4,\size}</td>
  <td rowspan="3"> = </td>
  <td>\embed{reply 5,\size}</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td>\embed{reply 6,\size}</td>
  </tr>
 </table>}
{<table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\val1</td>
  <td rowspan="3"> = </td>
  <td>\val2</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr><td>\val3</td></tr>
 </table>
 <div class="spacer">
<b>Question 3</b>: Écrire la valeur de la longueur du côté \(\inc\)
<b>sans effectuer de calcul</b>. </div>
\if{\step=3}{<div>
<label for="reply7">\(\inc =\)</label> \embed{reply 7}</div>
<div class="wims_instruction">ATTENTION : vous devez taper \fonct(\vangle)
et non \fonct\vangle.</div>}
{<div class="wimscenter">\(\inc=\asol3\) </div>
<div class="spacer"><b>Question 4</b> : Répondre à l'exercice.
<label for="reply8">\(\inc =\)</label> \embed{r8,5} cm.</div>
}}}
}}

\answer{Fonction}{\eq1|\neq}{type=clickfill}
\answer{Numérateur}{\eq2|\neq}{type=clickfill}
\answer{Dénominateur}{\eq3|\neq}{type=clickfill}
\answer{Fonction}{\val1|\val}{type=clickfill}
\answer{Numérateur}{\val2|\val}{type=clickfill}
\answer{Dénominateur}{\val3|\val}{type=clickfill}
\answer{\inc}{\sol3}{type=algexp}
\answer{Réponse}{\sol}{type=numexp}

\hint{Utiliser \nom de l'angle \angle.}
