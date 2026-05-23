target=vocabulaire1

# define NUM 1
#include "lang_titles.inc"
#include "author.inc"
\precision{100000}
\text{size=90x35x1}

\integer{confparm1=\confparm1 notwordof 0 1?1}
\integer{confparm2=\confparm2 notwordof 1 2?1}
\matrix{lettre=A,B,C
T,I,R
E,F,G
D,E,F}
\text{lettre=randrow(\lettre)}
\text{lettre=shuffle(\lettre)}
\text{A=item(1,\lettre)}
\text{B=item(2,\lettre)}
\text{C=item(3,\lettre)}

\integer{xrange=240}
\integer{yrange=140}

\text{chdes=shuffle(\B,\C)}
\text{Y1=item(1,\chdes)}
\text{Y2=item(2,\chdes)}
\text{dessin=segment 20,20,20,120,black
segment 20,120,220,120,black
segment 20,20,220,120,black
segment 21,110,30,110,red
segment 30,110,30,119,red
text black,10,115,medium,\A
text black,10,10,medium,\Y1
text black,230,115,medium,\Y2}

\text{rep1=\([\B\C]\)}
\text{rep2=\([\A\C]\)}
\text{rep3=\([\A\B]\)}
\text{liste=\rep1,\rep2,\rep3}

\text{enonce=Le triangle \(\A\B\C\) est rectangle en \(\A\).
  Complétez le tableau suivant en utilisant les étiquettes.}
\statement{
\if{\confparm1=1}{
<div class="wims_columns">
 <div class="medium_size img_col">
\draw{\xrange,\yrange}{\dessin}</div>
<div class="medium_size text_col">\enonce
}{
\enonce}

<table class="wimscenter wimsborder">
<tr>
 <td>Hypoténuse du triangle \(\A\B\C\)</td>
 <td>\embed{r1,\size}</td>
</tr><tr>
 <td>Côté adjacent à l'angle \(\widehat{\A\C\B}\)</td>
 <td>\embed{r2,\size}</td>
</tr><tr>
 <td>Côté opposé à l'angle \(\widehat{\A\C\B}\)</td>
 <td>\embed{r3,\size}</td>
</tr>
</table>
\if{\confparm1=1}{</div></div>}
}

\answer{Hypoténuse}{\rep1|\liste}{type=clickfill}
\answer{Côté adjacent}{\rep2|\liste}{type=clickfill}
\answer{Côté opposé}{\rep3|\liste}{type=clickfill}
