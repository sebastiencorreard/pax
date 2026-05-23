target=cerclerect4 cerclerect5
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\computeanswer{no}
\format{html}
\precision{100}

\integer{sl=8}
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
\integer{V1x=\ax-\cx}
\integer{V1y=\ay-\cy}
\real{N1=sqrt((\V1x)^2+(\V1y)^2)/8}
\integer{V2x=\bx-\cx}
\integer{V2y=\by-\cy}
\real{N2=sqrt((\V2x)^2+(\V2y)^2)/8}

\text{dessin=draw(400,250
parallel 0,0,0,400,20,0,21,grey
#if defined TARGET_cerclerect4
parallel 0,0,400,0,0,20,21,grey
#endif
fpolygon red,\cx,\cy,\cx+\V2x/\N2,\cy+\V2y/\N2,\cx+\V2x/\N2+\V1x/\N1,\cy+\V2y/\N2+\V1y/\N1,\cx+\V1x/\N1,\cy+\V1y/\N1
linewidth 2
triangle \ax,\ay,\bx,\by,\cx,\cy,black)}

\statement{\name_question
#if defined TARGET_cerclerect4
<div class="wimscenter"><img src="\dessin" alt=""></div>
<b>\name_answer</b>: \embed{r1,8} carreaux
#endif
#if defined TARGET_cerclerect5
<div class="wimscenter">\embed{r1}</div>
#endif
}
#if defined TARGET_cerclerect4
\answer{}{\L}{type=numexp}
#endif
#if defined TARGET_cerclerect5
\answer{}{\dessin;circle,\Cx,\Cy,8}{type=coord}
#endif
