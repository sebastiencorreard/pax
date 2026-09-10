target=pourcentageA3 pourcentageA4 pourcentageA5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{name=slib(lang/fname fr,boy)}
 \text{unit=\name_unit}
#if defined TARGET_pourcentageA3
 \text{pourcent=randitem(5,10,15,20,25)}
 \integer{prix=randint(20..500)}
 \integer{mprix=0.75*\prix}
 \integer{Mprix=1.25*\prix}
 \text{objet=slib(life/frcommodity \mprix,\Mprix)}
 \text{art=item(1,\objet)}
 \text{objet=item(2,\objet)}
 \real{diff=rint(\pourcent*\prix)/100}
 \integer{ch=randint(1..2)}
\text{enonce=\name \name_enonce[1] \art \objet \name_enonce[2] \prix \unit. \name_enonce[3] \pourcent %.}
 \if{\ch=1}{
  \real{rep=\diff}
  \text{question=\name_question[1]}
 }{
  \real{rep=\prix-\diff}
  \text{question=\name_question[2]}
 }
#endif
#if defined TARGET_pourcentageA4
\text{pourcent=randitem(15,20,25,30,35,40)}
 \real{prix=randint(500..1000)/100}
 \real{diff=rint(\pourcent*\prix)/100}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \text{enonce=\name \name_enonce[1] \prix \unit. \name_enonce[2] \pourcent %.}
  \text{question=\name_question[1]}
  \real{rep=\prix+\diff}
 }{
  \text{enonce=\name \name_enonce[1] \prix \unit. \name_enonce[2] \pourcent %.}
  \text{question=\name_question[2]}
  \real{rep=\diff}
 }
#endif
#if defined TARGET_pourcentageA5
 \integer{pourcent=randint(6..15)*5}
 \integer{prix=randitem(125,250,300,150,200,350)}
 \real{rep=rint(\pourcent*\prix)/100}
 \text{enonce=\name_enonce[1] \prix \unit, \name_enonce[2] <i>\pourcent % \name_enonce[3]</i>.}
 \text{question=\name_question}
#endif

\statement{\enonce
<p>\question ?</p>
<div class="spacer">
<b>\name_answer</b>: \embed{r1,5} \unit.</div>
<div class="wims_instruction">\name_inst</div>}

\answer{}{\rep}{type=numexp}
