target=pourcentageB1 pourcentageB2 pourcentageB3 pourcentageB4
#if defined TARGET_pourcentageB1
# define NUM 1
#endif
#if defined TARGET_pourcentageB2
# define NUM 2
#endif
#if defined TARGET_pourcentageB3
# define NUM 3
#endif
#if defined TARGET_pourcentageB4
# define NUM 4
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\keywords{percents, pbsolving}

\text{name=slib(lang/fname fr,girl)}
 \integer{ch=randitem(1,2)}
#if defined TARGET_pourcentageB1
 \text{pourcent=randitem(5,10,15,20,25)}
 \integer{prix=randint(20..500)}
 \integer{mprix=0.75*\prix}
 \integer{Mprix=1.25*\prix}
 \text{objet=slib(life/frcommodity \mprix,\Mprix)}
 \text{art=item(1,\objet)}
 \text{objet=item(2,\objet)}
 \if{\ch=1}{
  \integer{prix2=(1+\pourcent/100)*\prix}
  \integer{diff=\prix2-\prix}
  \text{question=Quel est le pourcentage d'augmentation de cet article}
  \text{enonce=Dans une boutique, \art \objet coûtait \prix euros. Son prix a augmenté de \diff euros.}
 }{
  \integer{prix2=(1-\pourcent/100)*\prix}
  \integer{diff=\prix-\prix2}
  \text{question=Quel est le pourcentage de baisse de cet article}
  \text{enonce=Dans une boutique, \art \objet coûtait \prix euros. Son prix a baissé de \diff euros.}
 }
 \integer{rep=\diff/\prix*100}
#endif

#if defined TARGET_pourcentageB2
 \text{pourcent=randitem(5,10,15,20,25)}
 \integer{prix=randint(20..500)}
 \integer{mprix=0.75*\prix}
 \integer{Mprix=1.25*\prix}
 \text{objet=slib(life/frcommodity \mprix,\Mprix)}
 \text{art=item(1,\objet)}
 \text{objet=item(2,\objet)}
 \if{\ch=1}{
  \integer{prix2=(1+\pourcent/100)*\prix}
  \text{question=Quel est le pourcentage d'augmentation de cet article}
 }{
  \integer{prix2=(1-\pourcent/100)*\prix}
  \text{question=Quel est le pourcentage de baisse de cet article}
 }
 \integer{diff=abs(\prix2-\prix)}
 \integer{rep=\diff/\prix*100}
 \text{enonce=Dans une boutique, \art \objet coûtait \prix euros. Maintenant son prix est de \prix2 euros.}
#endif
#if defined TARGET_pourcentageB3
 \integer{tot=randint(25..35)}
 \integer{f=randint(5..20)}
 \integer{g=\tot-\f}
 \if{\ch=1}{
  \text{enonce=Dans une classe il y a \tot élèves. \g sont des garçons.}
  \text{question=Quel est le pourcentage de garçons}
  \integer{rep=\g/\tot*100}
 }{
  \text{enonce=Dans une classe il y a \tot élèves. \f sont des filles.}
  \text{question=Quel est le pourcentage de filles}
  \integer{rep=\f/\tot*100}
 }
#endif
#if defined TARGET_pourcentageB4
 \integer{tot=randint(25..35)}
 \integer{f=randint(5..20)}
 \integer{g=\tot-\f}
 \text{enonce=Dans une classe il y a \f filles et \g garçons.}
 \if{\ch=1}{
  \text{question=Quel est le pourcentage de garçons}
  \integer{rep=\g/\tot*100}
 }{
  \text{question=Quel est le pourcentage de filles}
  \integer{rep=\f/\tot*100}
 }
#endif

\statement{
\enonce<p>
\question ?
</p>
<label for="reply1"><b>Votre réponse</b></label>\embed{r1,5} %.
<div class="wims_instruction">Le résultat doit être arrondi à l'unité.</div>}

\answer{}{\rep}{type=numexp}
