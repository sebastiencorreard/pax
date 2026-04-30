target=name formule
#include "author.inc"
#if defined TARGET_name
\title{Associer molécules et noms}
nom
\text{champ = 1}
image
\text{imag = 2}
\text{formule=nom}
#endif
#if defined TARGET_formule
\title{Associer  molécules et formules}
image
\text{imag = 2}
formule
\text{champ = 4}
\text{formule=formules chimiques}
#endif
\text{width=130}
\text{size=130x60}
\text{cnt= 3}
\text{redundant=3}
\text{category=image}
===== Choisir les objets dans la catégorie désirée
\text{all=wims(lookup \category in ind.cles)}
\text{objs=item(1..\cnt+10,shuffle(\all))}
#include "images.inc"
#include "comment.inc"
\text{STEPS=item(1..\cnt,r1,r2,r3,r4,r5,r6,r7,r8)}
\steps{\STEPS}
\statement{
<div class="wims_instruction">On trouvera en indication le code des couleurs.</div>
<div class="wims_question">Voici une série d'images de modèles éclatés de molécules.
  Associer molécules et \formule :<br>

<ul class="inline wims_nopuce wimscenter">
 \for{c=1 to \cnt}{
  <li>
  \img{\imagedir/\images[\c] width=\width}
  <br> \embed{reply \c,\size}
  </li>
 }
 </ul></div>
}
\answer{Le premier nom}{\names[1];\badnames[1..\redundant]}{type=clickfill}
\answer{Le second nom}{\names[2]}{type=clickfill}
\answer{Le troisième nom}{\names[3]}{type=clickfill}
\answer{Le quatrième nom}{\names[4]}{type=clickfill}
\answer{Le cinquième nom}{\names[5]}{type=clickfill}
\answer{Le sixième nom}{\names[6]}{type=clickfill}
\answer{Le septième nom}{\names[7]}{type=clickfill}
\answer{Le huitième nom}{\names[8]}{type=clickfill}
#include "help.inc"
