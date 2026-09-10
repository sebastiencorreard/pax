target=controle

#include "header.inc"

\title{Contrôle}

\text{sh1=shuffle(8,9,10,11,12,13,14)}
\text{sh2=shuffle(18,20,22,24,25)}
\integer{tot=\sh2[1]+\sh2[2]}
\real{mean=(\sh1[1]*\sh2[1]+\sh1[2]*\sh2[2])/\tot}
\real{mean1=floor(\mean*10)/10}
\real{mean2=ceil(\mean*10)/10}
\real{mean3=round(\mean*10)/10}

\statement{
  Deux classes de troisième ont fait un contrôle commun. Les copies ont été
  corrigées par un même professeur. Dans la première classe, \sh2[1] élèves ont
  composé et la moyenne du contrôle est égale à \sh1[1]. Dans la seconde,
\sh2[2] élèves ont composé et la moyenne du contrôle est \sh1[2].
  Quelle est la moyenne au contrôle du groupe formé des \tot élèves ?
<div class="wims_instruction">
  Arrondir au dixième de point près.
</div>
}

\reply{La moyenne}{\mean1,\mean2,\round}{type=range}

