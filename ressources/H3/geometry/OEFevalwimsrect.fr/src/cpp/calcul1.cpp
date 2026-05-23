target=calcul1
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

\text{angle=randint(5..85)}
\integer{ch=randint(1..3)}
\text{arr=item(\ch,\name_precision)}

\text{bad=<img src="\imagedir/cos.gif" alt="">,<img src="\imagedir/acos.gif" alt="">}

\statement{
\name_question[1] \arr \name_question[2] \angle \name_question[3]
<p>\name_question[4]?</p>
<div class="wimscenter">
\embed{r1,1}&nbsp;\embed{r1,2}</div>}

\answer{}{1;\bad}{type=click}
