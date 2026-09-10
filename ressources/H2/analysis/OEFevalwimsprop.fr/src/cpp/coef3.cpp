target=coef3
\language{ fr }
\author{Denis,Guicheteau}
\email{ math.42@laposte.net }
\format{ html }
#include "lang_titles.inc"
#include "lang.inc"
\real{r=randint(1..5)+randint(1..9)/10}

\integer{d=randint(2..20)}
\real{a=\r * \d}

\integer{b=randint(2..20)}
\while{\b==\d}{
\integer{b=randint(2..20)}
}
\real{c= \b * \r}

\statement{
\name_question
<table class="wimscenter wimsborder">
  <tr>
    <th>\name_head[1]</th><td> \d </td><td> \b</td>
    <td rowspan="2"> <img src="\imagedir/fleche1.jpg" alt="fleche1">
    <br>\(times)\embed{r1,4}<br><img src="\imagedir/fleche2.jpg" alt="fleche2"></td>
  </tr><tr>
    <th>\name_head[2]</th><td> \a </td> <td> \c </td>
  </tr>
</table>
}

\answer{}{\r}
