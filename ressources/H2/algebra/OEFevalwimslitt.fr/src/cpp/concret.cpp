target=concret1 concret2 concret3 concret4 concret5
#if defined TARGET_concret1
# define NUM 1
#endif
#if defined TARGET_concret2
# define NUM 2
#endif
#if defined TARGET_concret3
# define NUM 3
#endif
#if defined TARGET_concret4
# define NUM 4
#endif
#if defined TARGET_concret5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "author.inc"

#if defined TARGET_concret1
#include "lang.inc"
\text{A=randitem(A,B,C,D)}
\text{x=randitem(x,y,a,b,u,v)}
\integer{a=2*randint(2..5)}
\text{rep=simplify(\a^2+\a*\x/2)}
\text{rep2=maxima(expand(\rep);)}

\text{figure=draw(300,150
square 10,100,10,red
circle 60,10,8,red
circle 10,60,8,red
circle 110,60,8,red
circle 60,110,8,red
square 10,10,100, black
triangle 110,110,110,10,290,110,black
text black,60,120,medium,\a
text black,200,120,medium,\x
)}

\statement{
\name_instruction[1] \(\A\) \name_instruction[2] \(\x\).
<div class="wimscenter">
<img src="\figure" alt="">
</div>
}
\answer{\(\A\)}{\rep,\rep2}{type=algexp}
#endif
#if defined TARGET_concret2
\text{A=randitem(A,B,C,D)}
\text{x=randitem(x,y,a,b,u,v)}
\integer{a=randint(1..4)}
\text{rep=simplify(4*\x+4*(\x+2*\a))}
\text{rep2=maxima(expand(\rep);)}
#include "lang.inc"
\text{figure=draw(300,300
linewidth 3
square 50,50,200,brown
square 75,75,150,brown
flood 150,150,green
flood 60,60,grey
text black,130,145,medium,\name_dessin[1]
text black,130,55,medium,\name_dessin[2]
)}

\statement{
\name_instruction
<p>\name_question</p>
<div class="wimscenter">
<img src="\figure" alt="">
</div>
}
\answer{\(\A\)}{\rep,\rep2}{type=algexp}
#endif
#if defined TARGET_concret3
\text{A=randitem(A,B,C,D)}
\text{x=randitem(x,y,a,b,u,v)}
\integer{a=randint(1..3)}
\text{rep=simplify(10*\a*\x)}
#include "lang.inc"
\statement{
\name_instruction
<p>
\name_question?
</p>
}
\answer{\(\A\)}{\rep}{type=algexp}
\latex{\begin{statement}
\name_instruction
\name_question?
\end{statement}}
#endif
#if defined TARGET_concret4
\text{A=randitem(A,B,C,D)}
\text{x=randitem(x,y,a,b,u,v)}
\integer{a=100*randint(1..3)}
\text{rep=simplify(2*\a/\x)}
\text{rep2=\rep+2}
#include "lang.inc"
\statement{
\name_instruction
\name_question[1] \(\A\) \name_question[2]?}

\answer{\(\A\)}{\rep,\rep2}{type=algexp}
\latex{\begin{statement}
\name_instruction
\name_question[1] \(\A\) \name_question[2]?
\end{statement}}
#endif
#if defined TARGET_concret5
\text{A=randitem(A,B,C,D)}
\text{x=randrow(x,y
a,b
u,v)}
\text{x=shuffle(\x)}
\text{a=shuffle(2,3,4,6,8,10)}
\text{rep=\a[1]*\x[1]+\a[2]*\x[2]}
#include "lang.inc"
\statement{
\name_instruction
<p>\name_question</p>
}
\answer{\A}{\rep}{type=algexp}
\latex{\begin{statement}
\name_instruction
\end{statement}
\name_question
}
#endif
