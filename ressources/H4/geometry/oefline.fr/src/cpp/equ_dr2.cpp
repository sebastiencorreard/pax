target=equ_dr2

#include "header.inc"
#include "lang_titles.inc"

\keywords{line_equation}

\integer{xmin=-8}
\integer{xmax=8}
\integer{ymin=-8}
\integer{ymax=8}
\integer{gradx=1}
\integer{grady=1}
\integer{nx=(\xmax-\xmin)/\gradx}
\integer{ny=(\ymax-\ymin)/\grady}
\integer{b=random(-7..7)}
\integer{xm=random(1..7)}
\integer{y=random(-7..7)}
\integer{xp=random(1..2)}
\integer{x=\xm*(-1)^\xp}
\rational{a=(\y-\b)/\x}
\function{eq=maxima(expand(\a*x+\b))}
\text{eqa=texmath(\eq)}


#include "lang.inc"

\statement{
<div class="float_right">
\draw{400,400}{
xrange=\xmin,\xmax
yrange=\ymin,\ymax
linewidth=1
parallel \xmin,\ymin,\xmin,\ymax,\gradx,0,\nx,green
parallel \xmin,\ymin,\xmax,\ymin,0,\grady,\ny,green
linewidth=2
line 0,\ymin,0,\ymax,red
line \xmin,0,\xmax,0,red

text green,0,0,small,0
text green,\gradx,0,small,\gradx
text green,0,\grady,small,\grady

linewidth=1
plot blue,\a*x+\b
}
</div>
\name_statement

\name_statement2 \(\math_droite\) \name_is :
<div class="wimscenter">
\(y=) \embed{reply 1,6} x + \embed{reply 2,6}
</div>
}

\answer{\name_asnwer1}{\a}{type=default}
\answer{\name_answer2}{\b}{type=default}

\solution{\name_solutio \(\math_droite\) \name_is \(y = \eqa\)}
