target=cheveu

#include "header.inc"

\title{Cheveu}

\integer{p=random(10..20)}
\real{q=randint(8..16)/100}
\real{v=10*\p*(0.25*pi*\q^2)}

\statement{
  Un cheveu est long de \p \(cm), et il a un diamètre constant de \q \(mm).
  Quel est son volume&nbsp;?
<div class="wimscenter">
 \embed{r1,8} \(mm^2).
</div>
<div class="wims_instruction">
  Précision requise : 4 chiffres après la virgule.
</div>
}

\reply{Volume du cheveu}{\v}{type=number}

