target=cycliste automobile

#include "header.inc"

#if defined TARGET_cycliste 
 \title{Cycliste}
 \text{Nom=Un cycliste}
 \integer{minv=15}
 \integer{maxv=50}
#endif

#if defined TARGET_automobile 
 \title{Automobile}
 \text{Nom=Une voiture}
 \integer{minv=40}
 \integer{maxv=130}
#endif

\text{mlist= 8, 9,16,18,24,25,27,35,36,42}
\text{nlist= 2, 3, 4, 3, 2, 5, 9, 7, 3, 7}
\text{dlist=15,20,15,10, 5,12,20,12, 5,10}
\integer{r=random(1..10)}
\integer{min=\mlist[\r]}
\integer{den=\dlist[\r]}
\integer{num=\nlist[\r]}
\real{v=randint(\minv*10/\den..\maxv*10/\den)*\den/10}
\real{dist=\v/\den*\num}

\statement{
\Nom parcourt \dist km en \min minutes. Quelle est sa vitesse ?
<div class="wimscenter">
\embed{r1,6} kilomètre/heure.
</div>
}

\reply{La vitesse}{\v}
