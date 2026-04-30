target=representation3 representation4
#include "author.inc"
#include "lang_titles.inc"

\text{x=randitem(x,y,z,a,b,u,v)}
\integer{xsize=300}
\integer{ysize=80}

#if defined TARGET_representation3
 \integer{a=randint(2..10)}
#endif
#if defined TARGET_representation4
 \integer{a=-randint(2..10)}
#endif

 \text{sy=shuffle(<,>,<=,>=)}
 \text{dessin=slib(repinequation \sy[1],\a,\xsize,\ysize,-15,15,black,red)}
 \text{good=draw(\xsize,\ysize
\dessin)}

\text{ine=}
\for{i=1 to 4}{
 \text{t=texmath(\x \sy[\i] \a)}
 \text{ine=wims(append item \(\t) to \ine)}
}

\statement{
  Quelle inégalité les nombres représentés ci-dessous vérifient-ils ?
<div class="wimscenter"><img src="\good" alt=""></div>}

\choice{réponse}{\ine[1]}{\ine[2],\ine[3],\ine[4]}
