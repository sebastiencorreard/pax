target=paquet1

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}


\text{size=20x25x}
\integer{basep=row(1,\confparm4)}
\text{S=row(3,\confparm4)}
\text{S=item(1 to \basep,\S)}
w
\integer{p=randitem(3,4,5)}
\text{size=\size\p}
\integer{card=10^(\p-1)}
\text{total}
\for{k=1 to \p}{
 \text{tmp=\k=\p?randint(2..\basep):randint(1..\basep)}
 \text{total=\S[\tmp]\total}
}

#include "lang.inc"

\statement{
\txtstatement1<p>
\txtst2 \(\overline{\card}^{\basep}) \txtst3 \(\overline{\total}^{\basep}) \txtst4</p>
<div class="spacer">
<b>\txtyourreply</b>.
\txtans1 \embed{r1,\size} \txtans2.
</div>
<div class="wims_instruction">\txtinstruction</div>}



\answer{\txtnombre}{\rep;\S}{type=clickfill}

\text{test=slib(simplify \rep)}
\text{test2=slib(simplify \S[\tmp])}

\condition{\txtanalyse}{\test issametext \test2}
\text{aff=wims(items2words \test2)}
\feedback{\test notsametext \test2}{\txtgoodanswer \(\overline{\aff}^{\basep}).}
