target=coef4
\language{ fr }
\author{Denis,Guicheteau}
\email{ math.42@laposte.net }
\format{ html }
\precision{ 100 }
#include "lang_titles.inc"
#include "lang.inc"
\real{m2=randint(1..5)+randint(1..9)/10}

\integer{a=randint(2..20)}
\integer{d=\a+randitem(1,3,5)}

\integer{b=randint(2..20)}
\while{\b==\d}{
\integer{b=randint(2..20)}
}
\text{c= texmath(simplify(\b * \a / \d))}

\text{bon=texmath(\d/\a)}
\integer{m1=\d/\a}
\real{m2=\d/\a + 0.01}
\integer{mm=\m2*100}
\real{m2=\mm/100}
\real{m3=\a/\d}
\text{m4=texmath(\a/\d)}

\statement{
\name_question
<table class="wimscenter wimsborder">
  <tr><td> \(\d) </td> <td> \(\b) </td><td rowspan="2">
       <img src="\imagedir/fleche3.JPG" alt=""><br>
       \(times)\embed{r1,80x60}<br>
      <img src="\imagedir/fleche4.JPG" alt=""></td>
  </tr><tr>
    <td> \(\a) </td> <td> \(\c) </td>
  </tr>
</table>
}

\answer{}{\(\bon);\(\m1),\(\m2),\(\m3),\(\m4)}{type=dragfill}
