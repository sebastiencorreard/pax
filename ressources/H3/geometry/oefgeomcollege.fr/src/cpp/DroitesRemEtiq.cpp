target=DroitesRemEtiq

type=image
textarea="data"

Attention, ce modèle ne fonctionnera bien que si vous chargez les images sur wims.
<p>
Pour construire un exercice avec ce modèle, il suffit de taper la liste des images et
des étiquettes correspondantes
</p>

<p>
Auteur du modèle : Bernadette Perrin-Riou <bpr@math.u-psud.fr>
</p>

Sinon l'exercice risque de ne pas pouvoir repasser sous Createxo.

:%%%%%%%% Paramètres d'exemples à redéfinir %%%%%%%%%%%%%%%%%

:\author{Marie-Claude, David}
:\email{marie-claude.david@math.u-psud.fr}
:\credits{}

\text{data=bissectrice.png,bissectrice
mediane.png,médiane
mediatrice.png,médiatrice
hauteur.png, hauteur}
:Nombre de perturbateurs.
\integer{cntpertub=3}
:La taille verticale des cases en pixels.
\text{sizev=40}
:La taille horizontale des cases en pixels
\text{sizeh=200}
:%%%%%%%%%%%%% Maintenant l'énoncé en code html. %%%%%%%%%%%%%%%%%%%%
#include "author.inc"
#include "lang_DroitesRemEtiq.inc"
\title{TITLE}
\title_en{TITLE_en}

\if{\name_data!=}{
\text{data=bissectrice.png,\name_data[1]
mediane.png,\name_data[2]
mediatrice.png,\name_data[3]
hauteur.png,\name_data[4]}
}
\text{mot = randrow(\data)}
\text{image=\mot[1]}
\text{ext=item(2,wims(replace internal . by , in wims(lowercase \image)))}
\text{mot =\mot[2]}
\text{liste=column(2, \data)}
\text{perturb=wims(listcomplement \mot in \liste)}
\text{perturb=shuffle(\perturb)}
\text{perturb=\perturb[1..\cntpertub]}


\statement{
\instruction
<p class="wimscenter">
\if{\ext isitemof png,gif,jpg,jpeg}{
  \img{\imagedir/\image}
  }
  {\image}</p>

<p class="wimscenter">
\embed{r1,\sizeh x \sizev}
</p>
}
\answer{}{\mot;\perturb}{type=clickfill}
