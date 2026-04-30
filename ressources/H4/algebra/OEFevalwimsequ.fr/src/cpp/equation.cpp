target=equation1 equation2 equation3 equation4 equation5

#include "author.inc"
#include "lang_titles.inc"

\text{x=randitem(x,y,z,a,b,u,v)}
\text{v=wims(values v,-v for v=2 to 9)}
\text{v=shuffle(\v)}

#if defined TARGET_equation1
 \text{enonce=texmath(\x+\v[1]=\v[2])}
 \text{rep=simplify(\v[2]-(\v[1]))}
#endif
#if defined TARGET_equation2
 \text{enonce=texmath(\v[1]*\x=\v[2])}
 \text{rep=simplify(\v[2]/(\v[1]))}
#endif
#if defined TARGET_equation3
 \text{enonce=texmath(\v[1]*\x+\v[2]=\v[3])}
 \text{rep=simplify((\v[3]-(\v[2]))/\v[1])}
#endif
#if defined TARGET_equation4
 \text{enonce=texmath(\v[1]*\x+\v[2]=\v[3]*\x+\v[4])}
 \text{rep=simplify((\v[4]-\v[2])/(\v[1]-\v[3]))}
#endif
#if defined TARGET_equation5
 \text{v1=\v[1]=-\v[2]?10:\v[1]}
 \text{v3=\v[3]=-\v[4]?-10:\v[3]}
 \text{c=simplify(\v1/\v[2]*\v[5]+\v3/\v[4])}
 \text{enonce=texmath(\v1/\v[2]*\x+\v3/\v[4]=\c)}
 \text{rep=\v[5]}
#endif

\statement{
  Résoudre l'équation suivante :
<div class="wimscenter">\(\enonce).</div>
<b>Votre réponse :</b><br>
  <label for="reply1">La solution est</label> \embed{r1,5}.}

\answer{solution}{\rep}{type=numexp}
