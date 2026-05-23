target=droitepar
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=randint(-4..4)}
\integer{b=randint(-4..4)}
\integer{a=\a=0 and \b=0? randint(1..4)*random(1,-1)}
\function{eq=simplify(\a*x+(\b))}

\integer{B=randint(1..3)*random(1,-1)}
\integer{A=randint(-3..3)}
\integer{B=\a*(\A)+(\b)=\B? \B+random(1,-1)}
\integer{b1=-(\a)*\A+(\B)}
\function{eq1=simplify(\a*x + (\b1))}
\statement{\name_question \(A = (\A , \B)\) :

<div class="wimscenter"> \draw{200,200}{xrange -5.2,5.2
yrange -5.2,5.2
parallel -5,-5,5,-5,0,1,10, grey
parallel -5,-5,-5,5,1,0,10, grey
hline 0,0,black
disk \A,\B, 6,blue,
text black , \A,\B,medium ,A
arrow 0,0,1,0,8, black
arrow 0,0,0,1,8, black
vline 0,0,black
plot red , \eq
}
</div>
<div class="wimscenter"><label for ="reply1">\(y = )</label>
\embed{reply 1,15}</div>
}
\answer{\(y = )}{\eq1,x}{type=function}
