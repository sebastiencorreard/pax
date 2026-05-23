target=vocabulaire2

# define NUM 2
#include "lang_titles.inc"
#include "author.inc"

\precision{100000}
\text{size=50x25x1}

\integer{confparm1=\confparm1 notwordof 0 1?1}
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

\matrix{donnees=\([\B\C]\),Quelle est l'hypoténuse du triangle \(\A\B\C\)
\([\A\C]\),Quel est le côté adjacent à l'angle \(\widehat{\A\C\B}\)
\([\A\B]\),Quel est le côté opposé à l'angle \(\widehat{\A\C\B}\)}

\text{don=randrow(\donnees)}
\text{rep=item(1,\don)}
\text{question=item(2,\don)}
\text{reponse=wims(word 3 to -1 of \question)}
\text{liste=\([\B\C]\),\([\A\C]\),\([\A\B]\)}
\text{enonce=Le triangle \(\A\B\C\) est rectangle en \(\A\).}

\statement{
\if{\confparm1=1}{
  <div class="wims_columns"><div class="medium_size img_col">
    \draw{\xrange,\yrange}{\dessin}</div>
    <div class="medium_size text_col">\enonce \question?}{
    <div>\enonce \question?
  }
  <div class="spacer">
  <b>Votre réponse</b> :
  \reponse est \embed{r1,\size}.
  </div>
  </div>
  \if{\confparm1=1}{</div>}
}
\answer{réponse}{\rep|\liste}{type=clickfill}
