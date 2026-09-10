#if defined TARGET_oefecrit101 || defined TARGET_oefecrit102 || defined TARGET_oefecrit103 || defined TARGET_oefecrit104 || defined TARGET_oefecrit105
\text{name_statement=Compléter&nbsp;}
#endif
#if defined TARGET_oefecrit1 || defined TARGET_oefecrit2 || defined TARGET_oefecrit3 || defined TARGET_oefecrit4 || defined TARGET_oefecrit5
\text{chiffres=zero,un,deux,trois,quatre,cinq,six,sept,huit,neuf}
\text{apresdix=dix,onze,douze,treize,quatorze,quinze,seize,dix-sept,dix-huit,dix-neuf}
\text{dizaines=,vingt,trente,quarante,cinquante,soixante,soixante,quatre-vingt,quatre-vingt}
\text{name_answer=Réponse}
# if defined TARGET_oefecrit2 || defined TARGET_oefecrit4
\text{name_enonc=Écrire en lettres le nombre}
# endif
# if defined TARGET_oefecrit1 || defined TARGET_oefecrit3 || defined TARGET_oefecrit5
\text{name_enonc=Écrire en chiffres le nombre}
# endif
#endif
#if defined TARGET_oefencadr1 || defined TARGET_oefencadr3
\text{name_enonc1=Choisir les deux nombres les plus proches}
#endif
#if defined TARGET_oefencadr2
\text{name_enonc1=Choisir les deux nombres entiers les plus proches}
#endif
#if defined TARGET_oefencadr4
\text{name_enonc1=Encadrer le nombre à l'unité près}
#endif
#if defined TARGET_oefencadr5
\text{rang=dixième,centième}
\text{name_enonc1=Encadrer le nombre au, près}
#endif
#if defined TARGET_oeffractdix1 || defined TARGET_oeffractdix2 || defined TARGET_oeffractdix3 || defined TARGET_oeffractdix4 || defined TARGET_oeffractdix5
\text{enonc=Trouver le nombre décimal}
#endif
#if defined TARGET_oefinterc1 || defined TARGET_oefinterc2 || defined TARGET_oefinterc3 || defined TARGET_oefinterc4 || defined TARGET_oefinterc5
\text{name_enonc=Trouver un nombre à intercaler&nbsp;}
#endif
#if defined TARGET_oefordre1 || defined TARGET_oefordre2 || defined TARGET_oefordre3 || defined TARGET_oefordre4 || defined TARGET_oefordre5
\text{rang=centaines,dizaines,unités,dixièmes,centièmes,millièmes}
\text{pl=supérieur,inférieur}
\text{name_enonc1=Cocher le nombre}
\text{enonc2=Pour choisir, la décision se fait grâce au chiffre des }
#endif
#if defined TARGET_oefrang1 || defined TARGET_oefrang2 || defined TARGET_oefrang3 || defined TARGET_oefrang4 || defined TARGET_oefrang5
\text{rangdec=unités,dixièmes,centièmes,millièmes,dix millièmes,cent millièmes}
\text{rangent=unités,dizaines,centaines,milliers,dix milliers,cent milliers}
# if defined TARGET_oefrang1 || defined TARGET_oefrang3
\matrix{name_enonc=Voici un nombre
  Quel est son chiffre des}
# endif
# if defined TARGET_oefrang2 || defined TARGET_oefrang4
\matrix{name_enonc=Voici un nombre
  Dans ce nombre, le chiffre, est le chiffre des }
# endif
# if defined TARGET_oefrang5
\text{name_enonc=Réécrire,
  en plaçant correctement la virgule pour que le chiffre,soit le chiffre des }
# endif
#endif
#if defined TARGET_oefranger1 || defined TARGET_oefranger2 || defined TARGET_oefranger3 || defined TARGET_oefranger4 || defined TARGET_oefranger5
\text{voc=croissant,décroissant}
\text{name_enonc4=}
# if defined TARGET_oefranger1
\text{name_enonc1=Choisir le symbole correct&nbsp;}
\text{name_enonc4=Les nombres sont rangés en ordre }
# endif
# if defined TARGET_oefranger2
\text{name_enonc1=Ranger les nombres, en ordre}
# endif
# if defined TARGET_oefranger3 || defined TARGET_oefranger4 || defined TARGET_oefranger5
\text{name_enonc1=Ranger les nombres}
# endif
#endif
#if defined TARGET_oeffractdix1 || defined TARGET_oeffractdix2 || defined TARGET_oeffractdix3 || defined TARGET_oeffractdix4 || defined TARGET_oeffractdix5
\text{name_enonc=Trouver le nombre décimal&nbsp;}
#endif
#if defined TARGET_oeffractdec1
\text{rangdec=unités,dixièmes,centièmes,millièmes,dix millièmes}
#endif
#if defined TARGET_oeffractdec5 || defined TARGET_oeffractdec4
\text{name_enonc=Trouver le nombre décimal&nbsp;}
#endif
#if defined TARGET_oeffractdec1 || defined TARGET_oeffractdec2 || defined TARGET_oeffractdec3
\text{name_enonc=Compléter l'égalité&nbsp;}
#endif
#if defined TARGET_oefecritvoc1 || defined TARGET_oefecritvoc2 || defined TARGET_oefecritvoc3 || defined TARGET_oefecritvoc4 || defined TARGET_oefecritvoc5
\text{ord=unités,dizaines,centaines,milliers,dizaines de milliers,centaines de milliers,millions,dizaines de millions,centaines de millions,milliards}
\text{name_complete=Compléter&nbsp;}
# if defined TARGET_oefecritvoc1
\text{name_enonc=Dans le nombre, le chiffre des,est }
# endif
# if defined TARGET_oefecritvoc2
\text{name_enonc=Dans le nombre,est le chiffre des }
# endif
# if defined TARGET_oefecritvoc3
\text{name_enonc=Dans le nombre, le chiffre des, est }
# endif
# if defined TARGET_oefecritvoc4
\text{name_enonc=Dans le nombre, le nombre de, est}
# endif
# if defined TARGET_oefecritvoc5
\text{name_enonc=Dans le nombre, est le nombre de }
# endif
#endif
#if defined TARGET_oefecritlong1 || defined TARGET_oefecritlong2 || defined TARGET_oefecritlong3
\text{name_enonc=Donner l'écriture décimale de la longueur suivante sans zéro inutile&nbsp;}
#endif
#if defined TARGET_oefecritlong4 || defined TARGET_oefecritlong5
\text{name_enonc=Compléter l'égalité&nbsp;}
#endif
#if defined TARGET_oefecritdeclitt1 || defined TARGET_oefecritdeclitt2 || defined TARGET_oefecritdeclitt3 || defined TARGET_oefecritdeclitt4 || defined TARGET_oefecritdeclitt5
\text{rangdec=unités,dixièmes,centièmes,millièmes,dix millièmes}
# if defined TARGET_oefecritdeclitt4 || defined TARGET_oefecritdeclitt5
\text{name_enonc=Compléter avec le vocabulaire correct&nbsp;}
# else
\text{name_enonc=Écrire le nombre décimal suivant sans zéro inutile&nbsp;}
# endif
#endif
#if defined TARGET_oefecritdec1 || defined TARGET_oefecritdec2 || defined TARGET_oefecritdec3 || defined TARGET_oefecritdec4 || defined TARGET_oefecritdec5
\text{rangdec=unités,dixièmes,centièmes,millièmes,dix millièmes,cent millièmes}
\text{rangent=unités,dizaines,centaines,milliers,dix milliers,cent milliers}
# if defined TARGET_oefecritdec1
\matrix{name_enonc=Voici un nombre
  Dans ce nombre, quelle est la partie entière&nbsp;?}
# endif
# if defined TARGET_oefecritdec2
\matrix{name_enonc=Voici un nombre
  Dans ce nombre, quelle est la partie décimale&nbsp;?}
# endif
# if defined TARGET_oefecritdec3
\text{name_enonc=Recopier, en plaçant la virgule pour que le nombre soit compris entre}
\text{name_and=et}
# endif
# if defined TARGET_oefecritdec4 || defined TARGET_oefecritdec5
\text{name_enonc=Recopier le nombre,sans les zéros inutiles&nbsp;}
# endif
#endif
#if defined TARGET_oefrecfractdec1 || defined TARGET_oefrecfractdec2 || defined TARGET_oefrecfractdec3 || defined TARGET_oefrecfractdec4 || defined TARGET_oefrecfractdec5
\matrix{name_statement=Le carré représente l'unité, c'est-à-dire 1.
  La partie coloriée correspond à un nombre. Donner ce nombre}
\text{name_use2=en utilisant l'écriture d'un nombre décimal&nbsp;}
\text{name_instruction=Vous utiliserez la virgule comme séparateur décimal
  et éviterez les zéros inutiles.}
# if defined TARGET_oefrecfractdec1 || defined TARGET_oefrecfractdec2 || defined TARGET_oefrecfractdec3
\text{name_use1=en utilisant l'écriture d'une fraction décimale (utilisez la fraction la plus simple)&nbsp;}
# endif
# if defined TARGET_oefrecfractdec4
\text{name_use1=en utilisant une somme de fractions décimales&nbsp;}
# endif
# if defined TARGET_oefrecfractdec5
\text{name_use1=en utilisant la somme d'un nombre entier et de fractions décimales}
# endif
#endif
#if defined TARGET_plusproche
\text{name_enonce=Le nombre , est placé sur la droite graduée ci-dessous&nbsp;}
\text{name_question=Ce nombre est-il plus proche de, ou de ,
  (cliquer sur la bonne réponse)&nbsp;}
\text{name_feed=On dit que,est la valeur approchée,par,défaut,excès,de}
\text{name_feed1=Comme, est, plus proche, de, que de, on dit aussi que, est,l'arrondi,de}
#endif
#if defined TARGET_arrondiunit || defined TARGET_arrondiunitguide || defined TARGET_arrondix || defined TARGET_arrondixguide || defined TARGET_arrondixrelie
\text{name_enonce=On considère le nombre,On veut déterminer son arrondi }
\text{name_precdix=à l'unité,au dixième,au centième}
\text{name_precdix2=unités,dixièmes,centièmes}
\text{liste=par défaut,par excès}
# if defined TARGET_arrondiunitguide || defined TARGET_arrondixguide
\text{name_question=Compléter les phrases suivantes&nbsp;}
# endif
# if defined TARGET_arrondiunit || defined TARGET_arrondix
\text{name_question=Compléter la phrase suivante&nbsp;}
# endif
# if defined TARGET_arrondiunit || defined TARGET_arrondiunitguide || defined TARGET_arrondix || defined TARGET_arrondixguide
\text{name_feed=Vous semblez confondre les valeurs par défaut et par excès
  (par défaut...il en manque et par excès...il y en a trop).}
\matrix{name_statement=Le chiffre des,du nombre,est
  Donc l'arrondi,du nombre,est la valeur approchée, qui est égale à}
\text{name_answer=chiffre des,arrondi}
\text{name_note=On note}
# endif
# if defined TARGET_arrondiunit || defined TARGET_arrondix
\text{name_statement0=L'arrondi ,du nombre ,vaut}
# endif
# if defined TARGET_arrondixrelie
\text{name_question=Relier un nombre avec son arrondi au dixième}
#endif
# if defined TARGET_arrondix || defined TARGET_arrondixguide || defined TARGET_arrondixrelie
\text{name_list=a pour arrondi au dixième}
# endif
# if defined TARGET_arrondix || defined TARGET_arrondixguide || defined TARGET_arrondixrelie || defined TARGET_arrondiunit || defined TARGET_arrondiunitguide
\text{name_hint=L'<b>arrondi</b> XXXX d'un nombre est la valeur approchée XXXX
  (par défaut ou par excès)<b> la plus proche</b> de ce nombre.</p>
  <p>En pratique, comment trouver l'arrondi XXXX&nbsp;:</p>
  <ul><li>Lorsque le chiffre des YYYY du nombre est 0, 1, 2, 3 ou 4,
  l'arrondi XXXX est la valeur approchée XXXX par défaut.</li>
  <li>Lorsque le chiffre des YYYY du nombre est 5, 6, 7, 8 ou 9,
  l'arrondi XXXX est la valeur approchée XXXX par excès.</li></ul>}
# endif
#endif
#if defined TARGET_oefapproch1
\text{name_statement=Relier un nombre avec sa valeur approchée au dixième près&nbsp;}
#endif
#if defined TARGET_oefapproch2 || defined TARGET_oefapproch3
\text{name_statement=Le nombre, est la valeur approchée,près, du nombre}
\text{mot=à l'unité,au dixième,au centième,au millième,à la dizaine,à la centaine}
#endif
#if defined TARGET_oefapproch3
\text{comp=par défaut,par excès}
#endif
#if defined TARGET_oefapproch4
\text{mot=à l'unité par défaut,au dixième par défaut,au centième par défaut,
  à l'unité par excès,au dixième par excès,au centième par excès}
\text{name_statement=Nous avons le nombre,Relier les valeurs approchées&nbsp;}
#endif
#if defined TARGET_oefapproch5
\text{mot=à l'unité par défaut,au dixième par défaut,au centième par défaut,
à l'unité par excès,au dixième par excès,au centième par excès}
\text{name_statement=Nous avons le nombre,Donner la valeur approchée}
\text{name_inst=Vous utiliserez la virgule comme séparateur décimal.}
#endif

