target=demquad1 demquad2 demquad3 demquad4
#define TITRE Choisir les bonnes propriétés
\title{TITRE}
#include "author.inc"
#include "ltprop.inc"

#if defined TARGET_demquad1
 \title{TITRE 1}
 \observation{parallélogramme}
 \text{nature=parallélogramme}
 \text{good=B;C;D;E}
 \text{liste=2,3,4,5,7,8,10,11}
#endif

#if defined TARGET_demquad2
 \title{TITRE 2}
 \observation{rectangle}
 \text{nature=rectangle}
 \text{good=B,H;C,H;D,H;E,H;B,J;C,J;D,J;E,J}
 \text{liste=2,3,4,5,7,8,10,11}
#endif

#if defined TARGET_demquad3
 \title{TITRE 3}
 \observation{losange}
 \text{nature=losange}
 \text{good=B,G;C,G;D,G;E,G;B,K;C,K;D,K;E,K}
 \text{liste=2,3,4,5,7,8,10,11}
#endif

#if defined TARGET_demquad4
 \title{TITRE 4}
 \observation{carré}
 \text{nature=carré}
 \text{good=B,G,H;C,G,H;D,G,H;E,G,H;B,K,H;C,K,H;D,K,H;E,K,H;B,G,J;C,G,J;D,G,J;E,G,J;B,K,J;C,K,J;D,K,J;E,K,J}
 \text{liste=2,3,4,5,7,8,10,11}
#endif

\text{Ltprop=wims(item \liste of \ltprop)}
\text{temoin=A,B,C,D,E,F,G,H,I,J,K}
\integer{nblist=items(\liste)}
\text{Good=\good}
\for{l=1 to \nblist}{
 \text{tmp=\ltprop[\liste[\l]]}
 \integer{tmp2=positionof(\tmp,\Ltprop)}
 \text{le=\temoin[\liste[\l]]}
 \text{Good=wims(replace internal \le by \tmp2 in \Good)}
}

\statement{
   Il faut démontrer que \name est un \nature.
<div class="wims_instruction">Il faut utiliser le moins possible de propriétés
   (tout en étant sûr que cela sera bien un \nature).</div>
   Parmi les propriétés suivantes lesquelles allez-vous utiliser ?
<ul>
\for{k=1 to \nblist}{
 <li>\embed{r1,\k}</li>
}
</ul>}

\answer{}{\rep;\Ltprop}{type=checkbox}

\text{nbrep=items(\rep)}
\text{replist=}
\for{i=1 to \nbrep}{
 \text{tmp=positionof(\rep[\i],\Ltprop)}
 \text{replist=wims(append item \tmp to \replist)}
}
\integer{nbrow=rows(\Good)}
\integer{test=0}
\for{m=1 to \nbrow}{
 \text{tmp=row(\m,\Good)}
 \integer{test=\replist issametext \tmp?1}
}

\condition{Réponse correcte}{\test=1}
