target=reduitsom2 reduitsom3 reduitsom4
#include "lang_titles.inc"
#include "author.inc"
\precision{10000}
\text{size=50x50x50}

#if defined TARGET_reduitsom2
\integer{nombre=2}
#endif
#if defined TARGET_reduitsom3
\integer{nombre=3}
#endif
#if defined TARGET_reduitsom4
\integer{nombre=4}
#endif
\integer{c=random(2,3,5,6,7,10)}
\text{b=wims(values v for v=2 to 15)}
\text{b=shuffle(\b)}
\text{a=wims(values v,-v for v=2 to 15)}
\text{a=shuffle(\a)}

\text{lettre=randitem(A,B,C)}

\text{enonce=}
\integer{res=0}
\for{i=1 to \nombre}{
  \integer{tmp=(\b[\i])^2*\c}
  \integer{tmp2=\a[\i]}
  \text{sg=\tmp2>0 and \i>1?+:}
  \text{enonce=\enonce \sg \tmp2\sqrt{\tmp}}
  \integer{res=\res+(\tmp2)*(\b[\i])}
}

\if{\res>0}{
 \text{rep=\res*sqrt(\c),sqrt(\c)*\res}
}{
 \integer{tmp=-(\res)}
 \text{rep=\res*sqrt(\c),sqrt(\c)*(\res),-sqrt(\c)*\tmp}
}

\statement{
<div class="wimscenter">\(\lettre = \enonce)</div>
Écrire \(\lettre) sous la forme \(a\sqrt{b}) où \(b\) est un entier positif
le plus petit possible.
<div class="wims_instruction">
Vous devez taper <span class="tt">sqrt(2)</span> pour \(\sqrt{2}).
</div>}

\hint{Faire apparaitre \(\sqrt{\c}) dans chacun des termes de la somme.}

\reply{\lettre}{\rep}{type=litexp}
