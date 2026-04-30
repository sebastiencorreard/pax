target=clickimage clickimageform
#include "author.inc"
#if defined TARGET_clickimage
\title{Click : Molécules et noms}
nom
\text{champ = 1}
image
\text{imag = 2}
\text{formule=le nom}
#endif
#if defined TARGET_clickimageform
\title{Click : Molécules et formules}
image
\text{imag = 2}
formule
\text{champ = 4}
\text{formule=la formule chimique}
#endif
==== Choisir le nombre d'objets
 \text{cnt = 3}
 ====paramètre de taille d'image
 \text{width=130}
 ==== Choisir la liste de clés (category).
 Cette liste doit etre la même que celle qui apparait dans le menu intro. Aussi,
 on peut la mettre dans un fichier séparé qui est appelé à la fois du menu intro
 et de l'exercice. (all par défaut)
 \text{category=image}
===== Choisir les objets dans la catégorie désirée
\text{all=wims(lookup \category in ind.cles)}
\text{objs=item(1..\cnt+10,shuffle(\all))}
====listes des images
#include "images.inc"
===== Choix d'une image
\integer{good=randint(1..\cnt)}
#include "comment.inc"
\statement{
<div class="wims_instruction">On peut consulter le code des couleurs en aide.</div>
<div class="wims_question">
Voici une série d'images représentant les modèles éclatés de différentes molécules,
cliquez sur la molécule dont
\formule est <b>\names[\good]</b>.

<ul class="inline wimscenter wims_nopuce">
 \for{c=1 to \cnt}{<li>\embed{r1,\c}</li>}
 </ul></div>
}
\answer{Bonne réponse}{\good;\imglist}{type=click}
#include "help.inc"
