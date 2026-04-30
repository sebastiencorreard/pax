target=equatcar3 equatcar4 equatcar5

#include "author.inc"
#include "lang_titles.inc"

\text{x=randitem(x,y,z,a,b,u,v)}

#if defined TARGET_equatcar3
 \integer{v=randint(2..13)}
 \integer{a=\v^2}
 \text{enonce=\x^2=\a}
 \text{rep=\v,-\v}
#endif
#if defined TARGET_equatcar4
 \integer{v=randitem(2,3,5,6,7,8,10,11,12,13,14,15)}
 \text{enonce=\x^2=\v}
 \text{rep=sqrt(\v),-sqrt(\v)}
#endif
#if defined TARGET_equatcar5
 \integer{v=randitem(2,3,5,6,7,8,10,11,12,13,14,15)}
 \text{enonce=\x^2 - \v=0}
 \text{rep=sqrt(\v),-sqrt(\v)}
#endif
\text{name_enonce=Quelles sont les solutions de l'équation&nbsp;}
\statement{\name_enonce:
<div class="wimscenter">\(\enonce).</div>
<b>Votre réponse</b><br>
  <label for="reply1">L'ensemble des solutions de l'équation est </label>\embed{r1,15}.
<div class="wims_instruction">
  S'il y a plusieurs solutions, séparez les par des virgules.
  pour écrire \(\sqrt{2}), taper <span class="tt">sqrt(2)</span>.</div>}
\answer{Solutions}{\rep}{type=fset}
