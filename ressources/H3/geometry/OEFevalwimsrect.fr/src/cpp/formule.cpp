target=formule1 formule2 formule3 formule4 formule5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{size=180x30x1}
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_formule1
 \text{x=randitem(x,y,z,a,b,c)}
 \text{x=\widehat{\x}}
 \text{fonct=\(\cos(\x))}
 \text{num=\name_cote[2] \(\x[1]\)}
 \text{den=\name_cote[1]}
 \text{list=\name_cote[3] \(\x\)}
 \text{enonce=\(\x\) \name_enonce}
#endif
#if defined TARGET_formule2 || defined TARGET_formule3 || defined TARGET_formule4 || defined TARGET_formule5
 \text{lettres=randrow(A,B,C
T,R,I
S,V,T
R,S,T
E,F,G)}
 \text{lettres=shuffle(\lettres)}
 \text{A=item(1,\lettres)}
 \text{B=item(2,\lettres)}
 \text{C=item(3,\lettres)}
 \text{fonct=\(\cos(\widehat{\A\B\C}))}
#endif
#if defined TARGET_formule2
 \text{num=\name_cote[1] \(\widehat{\A\B\C}\)}
 \text{den=\name_cote[2]}
 \text{list=\name_cote[3] \(\widehat{\A\B\C}\)}
#endif
#if defined TARGET_formule2 || defined TARGET_formule3 || defined TARGET_formule4 || defined TARGET_formule5
\text{enonce=\A\B\C \name_enonce \A.}
#endif
#if defined TARGET_formule3 || defined TARGET_formule4 || defined TARGET_formule5
 \text{num=\(\A\B)}
 \text{den=\(\B\C)}
 \text{list=\(\A\C)}
#endif
#if defined TARGET_formule3
 #include "triangle1.inc"
 \text{image=draw(240,140
\dessin)}
#endif
#if defined TARGET_formule4
 #include "triangle2.inc"
 \text{image=draw(240,140
\dessin)}
#endif

\statement{
 \if{\dessin!=}{
<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
}
 \enonce
 \name_question:
<table class="wimscenter wimsnoborder">
  <tr>
  <td rowspan="3">\fonct</td>
  <td rowspan="3"> = </td>
  <td>\embed{reply1,\size}</td>
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td>\embed{reply2,\size}</td>
  </tr>
 </table>
 \if{\dessin!=}{</div></div>}
}

\answer{Numérateur}{\num;\list,\fonct}{type=clickfill}
\answer{Dénominateur}{\den;\list}{type=clickfill}
