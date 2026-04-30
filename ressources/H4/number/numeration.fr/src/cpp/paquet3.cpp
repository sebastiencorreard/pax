target=paquet3

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}


\text{size=20x25x}
\integer{basep=row(1,\confparm4)}
\text{S=row(3,\confparm4)}
\text{S=item(1 to \basep,\S)}

\integer{p=randitem(4,5,6)}
\integer{q=randint(2..\p-2)}
\text{size=\size\p}
\integer{card=10^(\q)}
\text{total=}
\text{rep=}
\for{k=1 to \p}{
 \integer{tmp=\k=1?randint(2..\basep):randint(1..\basep)}
 \integer{tmp=\k=\p and \k!=1?randint(2..\basep):randint(1..\basep)}
 \text{total=\S[\tmp]\total}
 \text{rep=\k<=\q?\S[\tmp],\rep}
}

\text{rep=wims(nonempty item \rep)}
\integer{nb=itemcnt(\rep)}
\text{t=0}
\for{k=1 to \nb}{
 \integer{t=\t=\k-1 and \rep[\k]=0?\k}
}
\text{rep=item(\t+1 to -1,\rep)}



#include "lang.inc"

\statement{
\txtstatement1<p>
\txtst2 \(\overline{\card}^{\basep}) \txtst3 \(\overline{\total}^{\basep}) \txtst4
</p><div class="spacer"><b>\txtyourreply</b>.
\txtans1 \embed{r1,\size} \txtans2.
</div>
<div class="wims_instruction">\txtinstruction</div>}

\answer{\txtnombre}{\reponse;\S}{type=clickfill}

\text{test=slib(simplify \reponse)}
\text{test2=slib(simplify \rep)}
\condition{\txtanalyse}{\test issametext \test2}
\text{aff=wims(items2words \test2)}
\feedback{\test notsametext \test2}{\txtgoodanswer \(\overline{\aff}^{\basep}).}
