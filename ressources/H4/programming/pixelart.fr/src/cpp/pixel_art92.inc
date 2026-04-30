\title{Traitement d'image : le négatif}

\text{prob=Transformer une image en son négatif}
\text{lii=charles.jpg}
\text{nomi=Photo et son négatif}

\text{enonce=Une image négative est une image dont les couleurs ont été inversées
  par rapport à l'original.
  On passe donc d'un pixel de valeur 1 à un pixel de valeur 0 et inversement.
  <a href="https://fr.wikipedia.org/wiki/Film_n%C3%A9gatif" target="_blank" >Source Wikipedia</a>}
\text{enoncep=}

\integer{tpari=1}

# include "pixel_art92_93.inc"

\text{enoncep=<p>Modifier cet algorithme afin d'afficher le négatif de la représentation
 donnée à droite ou ci-dessous. La matrice intitulée "mat" contient les données
 de l'image originale.</p>}

\text{pblu=pari(mmm=matrix(\nc,\nc,i,j,1-mm[j,i]);)}

\text{SDD=pari(print(mmm);)}
\text{DD=wims(replace internal ; by , in \SDD )}


###########################################
##############Correction###################
###########################################
if  mat[i][j]==1:
  mat[i][j]=0
else :
  mat[i][j]=1
###########################################
mat[i][j]=1-mat[i][j]
###########################################
