\title{Traitement d'image : Rotation d'une image 1}

\text{prob=Effectuer la rotation d'une image par la méthode naïve}
\text{lii=rotation.png}
\text{nomi=Rotation de 90° vers la gauche}

\text{enonce=<p>On cherche à réaliser une rotation de 90° vers la gauche d'une image
 de dimensions carrées. lors d’une rotation de 90° vers la gauche d’une image
 de taille \(n \times n\) pixels, un pixel initialement aux coordonnées \((x, y)\)
 doit être déplacé aux coordonnées \((y, n - 1 - x)\).</p>
 <ul><li>Le point jaune passe des coordonnées \((x=1, y=1)\) à \((x\prime=1, y\prime=4)\).
Le détail des calculs est le suivant : \(x\prime = y\) et \(y\prime = n - 1 - x = 6 - 1 - x = 5 - x = 5 - 1 = 4\)</li>
<li>Le point rouge passe de \((x=3, y=4)\) à \((x\prime=4, y\prime=2)\).
Le détail des calculs est le suivant : \(x\prime = y\) et \(y\prime = n - 1 - x = 6 - 1 - x = 5 - x = 5 - 3 = 2\)</li></ul>}
\text{enoncep=}

\integer{tpari=2}

# include "pixel_art92_93.inc"

\text{pblu=pari(mmm=matrix(\nc,\nc,i,j,mm[i,j]);)}

\text{SDD=pari(print(mmm);)}
\text{DD=wims(replace internal ; by , in \SDD )}

\text{enoncep=<ul><li>Exécuter ce script.</li>
<li>Modifier cet algorithme afin d'afficher l'image par la rotation d'angle 90°
vers la gauche de la représentation donnée à droite ou ci-dessous.</li</ul>}

###########################################
##############Correction###################
###########################################
mat=[[1] * nombre_colonne for _ in range(nombre_ligne)]
for i in range(nombre_ligne):
  for j in range(nombre_colonne):
      mat[i][j]=img[\nombre_line-1-j][i]
###########################
##Affichage de la matrice##
###########################
for i in range(nombre_ligne):
  print(mat[i])
###########################
