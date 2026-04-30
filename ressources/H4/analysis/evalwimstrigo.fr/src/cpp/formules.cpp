target=formule1,formule2,formule3,formule4,formule5,formule6

\text{x=randitem(A,B,C,O,T,R,U,X)}
\text{x=\widehat{\x}}
\text{size=180x30x1}
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Formule
#if defined TARGET_formule1
 \title{TITRE 1}
 \text{fonct=\(\cos(\x))}
 \text{num=Côté adjacent à \(\x)}
 \text{den=Hypoténuse}
 \text{list=Côté opposé à \(\x)}
 \integer{ty=1}
#endif

#if defined TARGET_formule2
 \title{TITRE 2}
 \text{fonct=\(\sin(\x))}
 \text{list=Côté adjacent à \(\x)}
 \text{den=Hypoténuse}
 \text{num=Côté opposé à \(\x)}
 \integer{ty=1}
#endif

#if defined TARGET_formule3
 \title{TITRE 3}
 \text{fonct=\(\tan(\x))}
 \text{den=Côté adjacent à \(\x)}
 \text{list=Hypoténuse}
 \text{num=Côté opposé à \(\x)}
 \integer{ty=1}
#endif

#if defined TARGET_formule4
 \title{TITRE 4}
 \text{fonct=\(\cos(\x))}
 \text{num=Côté adjacent à \(\x)}
 \text{den=Hypoténuse}
 \text{list=Côté opposé à \(\x),\(\sin(\x)),\(\tan(\x))}
 \integer{ty=2}
#endif

#if defined TARGET_formule5
 \title{TITRE 5}
 \text{fonct=\(\sin(\x))}
 \text{list=Côté adjacent à \(\x),\(\tan(\x)),\(\cos(\x))}
 \text{den=Hypoténuse}
 \text{num=Côté opposé à \(\x)}
 \integer{ty=2}
#endif

#if defined TARGET_formule6
 \title{TITRE 6}
 \text{fonct=\(\tan(\x))}
 \text{den=Côté adjacent à \(\x)}
 \text{num=Côté opposé à \(\x)}
 \text{list=Hypoténuse,\(\sin(\x)),\(\cos(\x))}
 \integer{ty=2}
#endif

\text{r=\ty=1?r1,r2:r3}
\steps{\r}

\statement{
\(\x) est l'un des deux angles aigus d'un triangle rectangle. Compléter l'égalité suivante :
\if{\ty=1}{
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
}{
<table class="wimscenter wimsnoborder">
  <tr>
   <td>\num</td>
   <td>&nbsp;</td>
   <td>&nbsp;</td>
  </tr><tr>
   <td><hr></td>
   <td> = </td>
   <td>\embed{r3,\size}</td>
  </tr><tr>
   <td>\den</td>
   <td>&nbsp;</td>
   <td>&nbsp;</td>
  </tr>
 </table>
}
}

\answer{Numérateur}{\num;\list,\fonct}{type=clickfill}
\answer{Dénominateur}{\den;\list}{type=clickfill}
\answer{Réponse}{\fonct;\list}{type=clickfill}
