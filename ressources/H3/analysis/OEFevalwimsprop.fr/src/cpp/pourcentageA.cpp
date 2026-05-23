target=pourcentageA2 pourcentageA3 pourcentageA4 pourcentageA5

\keywords{pbsolving,percents}
#include "author.inc"

\text{name=slib(lang/fname fr,boy)}

include "author..inc"
#if defined TARGET_pourcentageA1
# define NUM 1
#endif
#if defined TARGET_pourcentageA2
# define NUM 2
#endif
#if defined TARGET_pourcentageA3
# define NUM 3
#endif
#if defined TARGET_pourcentageA4
# define NUM 4
#endif
#if defined TARGET_pourcentageA5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_pourcentageA2
 \text{pourcent=randitem(5,10,15,20,25)}
 \integer{prix=randint(20..500)}
 \integer{mprix=0.75*\prix}
 \integer{Mprix=1.25*\prix}
 \text{objet=slib(life/frcommodity \mprix,\Mprix)}
 \text{art=item(1,\objet)}
 \text{objet=item(2,\objet)}
 \real{diff=rint(\pourcent*\prix)/100}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \real{rep=\diff}
  \text{enonce=\name a acheté \art \objet à \prix euros. Le vendeur lui a fait une remise de \pourcent %.}
  \text{question=Quel est le montant de son économie}
 }{
  \real{rep=\prix-\diff}
  \text{enonce=\name a acheté \art \objet à \prix euros. Le vendeur lui a fait une remise de \pourcent %.}
  \text{question=Quel prix a-t-il finalement payé}
 }
 \text{unit=euros}
#endif
#if defined TARGET_pourcentageA3
 \text{pourcent=randitem(15,20,25,30,35,40)}
 \real{prix=randint(500..1000)/100}
 \real{diff=rint(\pourcent*\prix)/100}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \text{enonce=\name a acheté une action à \prix euros.
   Il lit dans le journal que sa valeur a augmenté de \pourcent %.}
  \text{question=Quel est le prix actuel de cette action&nbsp;}
  \real{rep=\prix+\diff}
 }{
  \text{enonce=\name a acheté une action à \prix euros.
  Il lit dans le journal que sa valeur a augmenté de \pourcent %.}
  \text{question=Combien a-t-il gagné&nbsp;}
  \real{rep=\diff}
 }
 \text{unit=euros}
#endif
#if defined TARGET_pourcentageA4
 \integer{pourcent=randint(6..15)*5}
 \integer{prix=randitem(125,250,300,150,200,350)}
 \real{rep=rint(\pourcent*\prix)/100}
 \text{enonce=Sur une tablette de chocolat pesant \prix grammes, il est écrit <i>\pourcent % de cacao</i>.}
 \text{question=Quel est le poids de cacao dans la tablette&nbsp;}
 \text{unit=grammes}
#endif
#if defined TARGET_pourcentageA5
 \text{pourcent=randint(5..10)}
 \real{prix=randint(120000..200000)/100}
 \text{enonce=\name a eu \pourcent % d'augmentation. Il gagne maintenant \prix euros par mois.}
 \text{question=Combien gagnait-il, par mois, avant son augmentation&nbsp;}
 \real{rep=rint(\prix/(1+\pourcent/100)*100)/100}
 \text{unit=euros}
#endif

\statement{
\enonce
<p>
\question?
</p>
<label for="reply1"><b>Votre réponse</b>:</label> \embed{r1,5} \unit.
<div class="wims_instruction">Le résultat doit être arrondi au centième si nécessaire.</div>}

\answer{}{\rep}{type=numexp}
