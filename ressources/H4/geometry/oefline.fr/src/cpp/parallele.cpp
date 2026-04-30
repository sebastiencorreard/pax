target=parallele

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}
\integer{a=randitem(-1,1)*randint(1..20)}
\integer{b=randitem(-1,1)*randint(1..20)}
\integer{c=randitem(-1,1)*randint(1..20)}

\integer{cm=randitem(-1,1)*randint(1..10)}
\integer{cm1=randitem(-1,1)*randint(1..10)}
\integer{a1=\cm1*\a}
\integer{b1=\cm1*\b}
\integer{c1=\cm1*\c+random(-20..20)}

\function{f=maxima(expand(\cm*(\a*x+\b*y+\c)))}

\integer{r=randint(1..2)}
\if{\r=1}{
\function{f1=maxima(expand(\cm1*\a*x+k*y+\c1))}
\integer{k=\b1}
}
\if{\r=2}{
\function{f1=maxima(\cm1*\b*y+k*x+\c1)}
\integer{k=\a1}
}

#include "lang.inc"

\statement{\name_statement[1] \(k\) \name_statement[2] \(\math_droite\) \name_and
\(\math_droite'\) \name_statement[3]:
<div class="wimscenter">\(\f=0)</div>
\name_and
<div class="wimscenter">\(\f1=0)</div>
 \name_statement[4].
 <div class="spacer">
\name_statement[5] \(k\) \name_is \embed{reply 1}.
</div>
}

\answer{\(k\)}{\k}{type=default}
