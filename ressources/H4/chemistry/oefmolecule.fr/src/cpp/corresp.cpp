target=corresnom corresform
#include "author.inc"
#if defined TARGET_corresform
\title{Correspondance image-formule chimique}
image
\text{imag = 2}
formule
\text{champ = 4}
\text{formule=formules chimiques}
#endif
#if defined TARGET_corresnom
\title{Correspondance images-noms}
nom
\text{champ = 1}
image
\text{imag = 2}
\text{formule=nom}
#endif
==== Choisir le nombre d'objets par défaut 3 , les confparm sont définis dans le fichier
introhook.phtml
 \text{cnt= 3}
====paramètre de taille d'image
\text{width=150}
 \text{size=130x130x130}
==== Choisir la liste de clés (category).
\text{category=image}
===== Choisir les objets dans la catégorie désirée
\text{all=wims(lookup \category in ind.cles)}
\text{objs=item(1..\cnt+10,shuffle(\all))}
#include "comment.inc"
==== definition de imglist
#include "images.inc"
\statement{
<div class="wims_instruction">Le code des couleurs se trouve en indication.</div>
<div class="wims_question">Mettre en correspondance les images des modèles
moléculaires avec leur \formule.

<div class="wimscenter">\embed{r1,\size}</div></div>
}
\answer{Correspondance}{\imglist;\names}{type=correspond}{option=split}

#include "help.inc"
