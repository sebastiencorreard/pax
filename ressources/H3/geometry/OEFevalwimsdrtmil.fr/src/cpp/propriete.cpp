target=propriete1 propriete2 propriete3 propriete4 propriete5
#include "author.inc"
#define TITRE Connaître les propriétés
#include "ltprop.inc"

#if defined TARGET_propriete1
 \title{TITRE 1}
 \observation{quadrilatère}
 \text{enonce=quadrilatère}
 \text{good=1}
#endif
#if defined TARGET_propriete2
\title{TITRE 2}
 \observation{parallélogramme}
 \text{enonce=parallélogramme}
 \text{good=1,2,3,4,5}
#endif
#if defined TARGET_propriete3
 \title{TITRE 3}
 \observation{rectangle}
 \text{enonce=rectangle}
 \text{good=1,2,3,4,5,8,9,10}
#endif
#if defined TARGET_propriete4
 \title{TITRE 4}
 \observation{losange}
 \text{enonce=losange}
 \text{good=1,2,3,4,5,6,7,11}
#endif
#if defined TARGET_propriete5
 \title{TITRE 5}
 \observation{carré}
 \text{enonce=carré}
 \text{good=1,2,3,4,5,7,8,9,10,11}
#endif

\statement{
\name est un \enonce. Quelles sont ses propriétés ?
<ul>
\for{k=1 to \nbprop}{
 <li>
  \embed{r1,\k}
 </li>
}
</ul>}

\answer{}{\good;\ltprop}{type=checkbox}{option=split shuffle}
