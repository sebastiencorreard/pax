target=solvesys1 solvesys2 solvesys3 solvesys4 solvesys5

#include "author.inc"
#include "lang_titles.inc"

#if defined TARGET_solvesys1
 \text{c=wims(values v for v=2 to 5)}
 \text{c=shuffle(\c)}
 \text{c=\c[1],\c[2],0,\c[4]}
 \integer{sx=randint(-3..3)}
 \integer{sy=randint(-3..3)}
#endif
#if defined TARGET_solvesys2
 \text{c=wims(values v for v=2 to 5)}
 \text{c=shuffle(\c)}
 \text{c=\c[1],\c[2],\c[3],\c[2]}
 \integer{sx=randint(-3..3)}
 \integer{sy=randint(-3..3)}
#endif
#if defined TARGET_solvesys3
 \text{c=wims(values v for v=2 to 5)}
 \text{c=shuffle(\c)}
 \text{c=\c[1],\c[2],-\c[1],\c[4]}
 \integer{sx=randint(-3..3)}
 \integer{sy=randint(-3..3)}
#endif
#if defined TARGET_solvesys4
 \text{c=wims(values v for v=2 to 5)}
 \text{c=shuffle(\c)}
 \integer{sx=randint(-3..3)}
 \integer{sy=randint(-3..3)}
#endif
#if defined TARGET_solvesys5
 \text{c=wims(values v,-v for v=2 to 9)}
 \text{c=shuffle(\c)}
 \text{sx=simplify(randitem(1,-1)*randitem(1/4,1/3,2/3,3/4,1/2))}
 \text{sy=simplify(randitem(1,-1)*randitem(1/4,1/3,2/3,3/4,1/2))}
#endif

\text{inc=randrow(x,y
u,v
a,b)}
\text{x=\inc[1]}
\text{y=\inc[2]}
\text{t1=\c[1]*\c[2]=0?maxima(\c[1]*\x+\c[2]*\y;):\c[1]*\x+\c[2]*\y}
\text{t1=texmath(\t1)}
\text{t2=\c[3]*\c[4]=0?maxima(\c[3]*\x+\c[4]*\y;):\c[3]*\x+\c[4]*\y}
\text{t2=texmath(\t2)}
\text{d1=texmath(simplify(\c[1]*\sx+\c[2]*\sy))}
\text{d2=texmath(simplify(\c[3]*\sx+\c[4]*\sy))}
\text{enonce=\(\left\lbrace\begin{array}{ccc}\t1&=&\d1\\ \t2&=&\d2\end{array}\right.)}



\statement{
  Résoudre le système d'équations suivant :
<div class="wimscenter">\enonce</div>
<b>Votre réponse </b><br>
  <label for="reply1">La solution du système
  est le couple</label> (\embed{r1,5} ; \embed{r2,5}).}

\answer{\x}{\sx}{type=numexp}
\answer{\y}{\sy}{type=numexp}
