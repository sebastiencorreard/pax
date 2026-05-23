target=cocyclique1

\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

\text{let=shuffle(A,B,C,D,E,F,G,H,R,S,T)}
\text{A=\let[1]}
\text{B=\let[2]}
\text{C=\let[3]}
\integer{ax=randint(1..4)*20}
\integer{L=2*randint(5..7)}
\text{x=wims(values v,\L-v for v=2 to \L/2-1)}
\integer{x=randitem(\x)}
\integer{l=\L*20}
\integer{ay=10*20}
\integer{bx=\ax+\l}
\integer{by=\ay}
\integer{Cx=(\ax+\bx)/2}
\integer{Cy=\ay}
\integer{cx=\ax+\x*20}
\integer{cy=\Cy-sqrt((\l/2)^2-(\cx-\Cx)^2)}

\integer{chc=randint(1..4)}
\text{acolor=item(\chc,\name_color)}
\text{color=item(\chc,red,blue,green,purple)}

\text{dessin=draw(400,400
parallel 0,0,0,400,20,0,21,grey
parallel 0,0,400,0,0,20,21,grey
text black,\Cx,\Cy,medium,O
text black,\ax-8,\ay-4,medium,\A
text black,\bx+2,\by-4,medium,\B
text black,\cx,\cy-15,medium,\C
linewidth 2
triangle \ax,\ay,\bx,\by,\cx,\cy,black
circle \Cx,\Cy,\l,black
segment \Cx,\Cy,\cx,\cy,\color)}
\integer{rep=\L/2}
\statement{
\C \name_enonce[1] [\A\B] \name_enonce[2]<p>
\name_question[1] [O\C] \name_question[2] \acolor ?
</p>
<div class="wimscenter"><img src="\dessin" alt=""></div>
<label for="reply1"><b\name_answer</b>:</label> \embed{r1,8} \name_carreau.}

\answer{}{\rep}{type=numexp}
