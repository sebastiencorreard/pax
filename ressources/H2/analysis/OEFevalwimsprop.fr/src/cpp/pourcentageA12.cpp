target=pourcentageA1 pourcentageA2
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#if defined TARGET_pourcentageA1
\integer{pour1=randitem(10,20,30,40,50)}
\integer{pour2=randint(25,75)}
\integer{pour3=randint(1..5)*10+randint(1..9)}
#endif
#if defined TARGET_pourcentageA2
\integer{pour1=100}
\integer{pour2=100+randint(25,75)}
\integer{pour3=200+randint(1..5)*10+randint(1..9)}
#endif
\integer{N1=randint(201..299)}
\integer{N3=randint(11..19)*10}
\integer{N2=randint(201..299)}
\real{rep1=\N1*\pour1/100}
\real{rep2=\N2*\pour2/100}
\real{rep3=\N3*\pour3/100}

\statement{
\name_question:
<table>
 <tr>
  <td>\pour1 % \name_of \N1 : </td><td>\embed{r1,5}</td>
 </tr><tr>
  <td>\pour2 % \name_of \N2 : </td><td>\embed{r2,5}</td>
 </tr><tr>
  <td>\pour3 % \name_of \N3 : </td><td>\embed{r3,5}</td>
 </tr>
</table>}
\answer{\name_answer 1}{\rep1}{type=litexp}
\answer{\name_answer 2}{\rep2}{type=litexp}
\answer{Réponse 3}{\rep3}{type=litexp}
