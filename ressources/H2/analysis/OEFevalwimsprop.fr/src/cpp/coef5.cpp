target=coef5
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

\text{bon=simplify(\d/\a)}


\statement{
\name_question
<div class="wims_instruction">
\name_inst
</div>
<table class="wimscenter wimsborder">
  <tr>
    <td> \(\d) </td> <td> \(\b) </td><td rowspan="2">
        <img src="\imagedir/fleche3.JPG" alt=""><br>
        \(times)\embed{r1,4}<br>
        <img src="\imagedir/fleche4.JPG" alt=""></td>
  </tr><tr>
    <td> \(\a) </td> <td> \(\c) </td>
  </tr>
</table>
}

\answer{}{\bon}{type=numexp}{option=noreduced}
