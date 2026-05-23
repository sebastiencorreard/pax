#if defined TARGET_seriestat
\text{name_human=garçons,garçons}
\text{name_enonce=Les tailles arrondies à un nombre entier de centimètres des,
   d'un club de football sont les suivantes&nbsp;}
\text{name_question=Compléter le tableau correspondant&nbsp;}
\text{name_head=Tailles,Effectif,Fréquence}
\text{name_inst=On donnera les fréquences en arrondissant par excès à 0.1 près.}
\text{name_hint=Voici l'histogramme}
#endif
#if defined TARGET_repartition || defined TARGET_repartition2
\text{name_enonce1=Compléter le tableau ci-dessous qui
  représente la répartition des notes obtenues par,
  élèves.}
\text{name_head=Classe des notes,Effectif,Effectif cumulé, Fréquence}
#endif
#if defined TARGET_repartition
\text{name_inst=On donnera le résultat pour les
  fréquences en approchant les valeurs à une décimale par défaut.}
#endif
#if defined TARGET_repartition2
\text{name_enonce2=Voici le tableau complété&nbsp;,
  On regroupe maintenant les notes en classes d'amplitude différente.
  Compléter de nouveau le tableau correspondant&nbsp;}
\text{name_inst=On demande une précision pour les fréquences de 0.1 par défaut.}
#endif
#if defined TARGET_effpourcent || defined TARGET_pourcentstat || defined TARGET_pourcentcirc || defined TARGET_pourcentangle
\text{listefr=rouge, bleu,orange,gris, vert, violet}
\text{name_effectif=Effectifs}
\text{name_enonce=Voici la représentation graphique (diagramme circulaire) de,
  caractères sur une population de,individus&nbsp;}
#endif
#if defined TARGET_effpourcent
\text{name_question=Remplir le tableau des effectifs correspondant
  (en arrondissant à l'entier le plus proche)}
#endif
#if defined TARGET_pourcentstat
\text{name_question=Donner le nombre d'individus possédant le caractère}
\text{name_inst=On arrondira à l'entier le plus proche.}
\text{name_answer=Nombre d'individus}
#endif
#if defined TARGET_pourcentcirc
\text{name_question=Quel est le pourcentage des individus possédant le caractère}
\text{name_answer=Pourcentage}
#endif
#if defined TARGET_pourcentangle
\text{name_question= Quel est l'angle en degrés correspondant aux individus possédant
  le caractère}
\text{name_inst=On arrondira au degré le plus proche.}
\text{name_answer=Angle}
#endif
#if defined TARGET_Moyennesetcoef
\text{name_enonce=NNNN a eu,
  de moyenne en mathématique (coefficient XXXX),
  de moyenne en français (coefficient YYYY) et,
  de moyenne en physique (coefficient ZZZZ). Quelle est sa moyenne totale (arrondie
  au premier chiffre après la virgule)&nbsp;}
\text{name_answer=Moyenne totale}
#endif
#if defined TARGET_mediane
\text{name_enonce=Les tailles arrondies à un nombre entier de centimètres de,
  garçons d'un club de football sont les suivantes&nbsp;}
\text{name_question=Calculer la médiane de cette série statistique.}
\text{name_answer=La médiane est égale à,Médiane}
\matrix{name_hint=Attention : ne pas oublier de ranger les tailles par ordre croissant.,
  Ensuite, la médiane est la valeur centrale (ou la moyenne des deux valeurs centrales).}
\text{name_feed1=Attention : ne pas oublier de ranger les tailles
  par ordre croissant.}
\text{name_feed2=Attention : vous confondez la moyenne et la médiane.}
\text{name_feed3=Attention : La médiane se trouve parmi un des
  nombres de la série, ou de la moyenne de deux d'entre eux.}
#endif
#if defined TARGET_meanw || defined TARGET_mean
\text{name_question=Calculer pour cette série statistique,
  la moyenne,la valeur maximale,la valeur minimale,
  l'étendue statistique}
\text{name_answer=Moyenne,Maximum,Minimum,Etendue}
\text{name_feed=L'étendue statistique est égale au maximum moins le minimum.}
\text{name_head=Valeurs, Coeff.}
#endif
#if defined TARGET_meanw
\text{name_enonce=Soit la série statistique suivante pondérée par des coefficients}
#endif
#if defined TARGET_mean
\text{name_enonce=Soit la série statistique suivante&nbsp;}
#endif
#if defined TARGET_baton
\text{matiere=randitem(mathématiques,français,physique,chimie,géographie,histoire,anglais,biologie)}
\text{name_enonce=Après un contrôle de,
  le professeur dresse un tableau des notes obtenues par les élèves de la classe&nbsp;}
\matrix{name_head=Note,sur 20
  Nombre d'élèves,ayant la note, indiquée au-dessus}
\text{name_question=Représenter la série des notes par un diagramme en bâtons,
  en glissant/déposant les bâtons dans le dessin.}
\text{name_cond=Le diagramme est correct}
\text{name_feed=La hauteur du bâton pour,la note,les notes,n'est pas correcte.}
#endif
#if defined TARGET_Moyenne
\text{name_enonce=a eu XXXX de moyenne au premier trimestre, YYYY de
moyenne au deuxième trimestre et ZZZZ de moyenne au troisième
trimestre. Quelle est sa moyenne annuelle (arrondie au premier
chiffre après la virgule)&nbsp;}
\text{name_answer=Moyenne annuelle}
#endif
