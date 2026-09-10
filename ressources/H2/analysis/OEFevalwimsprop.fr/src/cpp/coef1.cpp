target=coef1
\language{ fr }
\author{Denis,Guicheteau}
\email{ math.42@laposte.net }
\format{ html }
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=randint(1..20)}
\integer{b=randint(2..20)}
\integer{c= \b * \a}
\integer{r=\a}

\statement{
\name_question
<table class="wimscenter wimsborder">
  <tr>
    <td>1</td>
    <td> \b </td>
    <td rowspan="2"> <img src="\imagedir/fleche1.jpg" alt="">
    <br>\(times)\embed{r1,4}
    <br><img src="\imagedir/fleche2.jpg" alt=""></td>
  </tr><tr>
      <td> \a </td> <td> \c </td>
  </tr>
</table>
}

\answer{}{\r}
