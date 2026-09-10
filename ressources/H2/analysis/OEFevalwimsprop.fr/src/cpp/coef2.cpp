target=coef2

\language{ fr }
\author{Denis,Guicheteau}
\email{ math.42@laposte.net }
\format{ html }
#include "lang_titles.inc"
#include "lang.inc"
\integer{r=randint(1..12)}

\integer{d=randint(2..20)}
\integer{a=\r * \d}

\integer{b=randint(2..20)}
\integer{c= \b * \r}

\statement{
\name_question
<table class="wimscenter wimsborder">
  <tr>
    <td> \d </td> <td> \b </td><td rowspan="2">
     <img src="\imagedir/fleche1.jpg" alt=""><br>
     \(times)\embed{r1,4}<br>
     <img src="\imagedir/fleche2.jpg" alt=""></td>
  </tr><tr>
    <td> \a </td> <td> \c </td>
  </tr>
</table>
}

\answer{}{\r}
