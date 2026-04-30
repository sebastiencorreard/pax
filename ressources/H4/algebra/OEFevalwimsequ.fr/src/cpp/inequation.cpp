target=inequation1 inequation2 inequation3 inequation4 inequation5

#include "author.inc"
#include "lang_titles.inc"
\text{name_enonce=Résoudre l'inéquation suivante&nbsp;}
\text{v=wims(values v for v=2 to 9)}
\text{v=shuffle(\v)}

#if defined TARGET_inequation1
 \text{d=1,\v[2],0,\v[4]}
#endif
#if defined TARGET_inequation2
 \text{d=\v[1],0,0,\v[4]}
#endif
#if defined TARGET_inequation3
 \text{d=-\v[1],0,0,\v[4]}
#endif
#if defined TARGET_inequation4
 \text{d=\v[1],\v[2],0,\v[4]}
#endif
#if defined TARGET_inequation5
 \text{d=\v[1],\v[2],\v[3],\v[4]}
#endif

\integer{ch=randint(1..4)}
\text{sy=item(\ch,<,>,<=,>=)}
\text{list=inférieurs stricts,supérieurs stricts,inférieurs ou égaux,supérieurs ou égaux}
\text{te=item(\ch,\list)}
\text{cte=item(\ch,supérieurs stricts,inférieurs stricts,supérieurs ou égaux,inférieurs ou égaux)}
\text{x=randitem(x,y,z,a,b,u,v)}

\text{t1=maxima(\d[1]*\x+\d[2];)}
\text{t2=maxima(\d[3]*\x+\d[4];)}
\text{enonce=texmath(\t1 \sy \t2)}
\text{rep=simplify((\d[4]-\d[2])/(\d[1]-\d[3]))}

\text{good=\d[1]-\d[3]>0?\te:\cte}

\statement{\name_enonce:
<div class="wimscenter">\(\enonce).</div>
<b>Votre réponse :</b><br>
  Les solutions de cette inéquation sont les nombres \embed{c1}
  <label for="reply1">à</label> \embed{r1,6}.}

\choice{Sens}{\good}{\list}
\answer{Frontière}{\rep}{type=numexp}
