#if defined TARGET_CDRom
\text{name_statement=I have bought a CD rom driver. I have paid,
  dollars with, CD roms which cost, dollars each.}
\text{name_question=What is the price of the CD rom driver}
\text{name_answer=Price (in dollars)}
#endif
#if defined TARGET_Tourdumonde
\text{name_statement1=Le périmètre de la terre est d'environ 40 000 \(\textrm{km}\). Pour simuler
  un tour du globe en automobile, un pilote roule sur un circuit de}
\text{name_statement2=à une vitesse moyenne de, (repos et entretien
  compris).}
\text{name_question=Quelle sera la durée de sa performance en heures&nbsp;}
\text{name_answer=Durée (en heures)}
#endif
#if defined TARGET_Tempsdeparcour
\matrix{name_statement=En voiture, j'ai parcouru
  en roulant à la vitesse moyenne de}
\text{name_question=Pendant combien de minutes ai-je roulé&nbsp;}
\text{name_answer=Temps en}
#endif
#if defined TARGET_Solde
\matrix{name_statement=Avec,de remise
  j'économise, euros sur une paire de bottines}
\text{name_question=Quel était le prix avant les soldes&nbsp;}
\text{name_answer=Prix (en euros)}
#endif
#if defined TARGET_Pyramide
\text{name_statement=Une pyramide a une base carrée de,
  de côté. Sa hauteur est,
  Je veux réaliser une maquette en bois à l'échelle
}
\text{name_question=Quelle est la longueur du côté de la base (en \(\textrm{cm}\))}
\text{name_answer=Côté de la base en \(\textrm{cm}\)}
#endif
#if defined TARGET_chelle
\text{name_statement=Une carte routière est à l'échelle}
\text{name_question=Quelle distance réelle (en \(\textrm{km}\)) représente, sur la carte&nbsp;}
\text{name_answer=Distance réelle (en \(\textrm{km}\))}
#endif
#if defined TARGET_Courses
\matrix{name_statement=Maman m'envoie chez l'épicier acheter du
  Je prends un paquet de,bouteilles.
  La caissière me dit alors qu'il me manque
  Je repose une bouteille et repasse à la caisse.La caissière me rend alors}
\text{name_product=jus d'orange, jus de pomme, Coca cola, jus de raisin}
\matrix{name_question=Quel est le prix d'une bouteille de
  Combien d'argent avais-je sur moi}
\text{name_instruction=Les réponses seront données en}
\text{name_euro=euros}
\text{name_answer1=Prix d'une bouteille}
\text{name_answer2=Mon argent}
#endif
#if defined TARGET_Densit
\matrix{name_statement=The population density of a country is ,inhabitants
  Its population is,millions }
\text{name_question=What is its area (in thousands of \(\mathrm{km}^2\))}
\text{name_answer=Area (in thousands of \(\mathrm{km}^2\))}
#endif
#if defined TARGET_DensitII
\text{name_statement=La superficie d'un pays est de,
  et sa population est de}
\text{name_question=Quelle est sa densité&nbsp;}
\text{name_answer=densité (\(hab{/}\textrm{km}^2\))}
#endif
#if defined TARGET_DensitII2
\text{name_statement=La superficie d'un pays est de,
  et sa densité est de,habitants}
\text{name_question=Quelle est sa population (en millions)&nbsp;}
\text{name_answer=Population (en millions)}
#endif
#if defined TARGET_Molire
\text{name_statement=Le professeur de français a acheté,exemplaires de l'Avare.,
  Le libraire lui a fait une remise de, par livre. Il a payé}
\text{name_question=Quel est le prix d'un livre sans la remise}
\text{name_answer=Prix en}
#endif
#if defined TARGET_Poids
\text{name_statement=A truck is,times heavier than a car while
  the truck is, lighter than a tank. Knowing that the truck
  weighs, tons, compute the weights of a car and of a tank (in tons).}
\text{name_answer1=Weight of a car (in tons)}
\text{name_answer2=Weight of a tank (in tons)}
#endif
#if defined TARGET_Pourcentages
\matrix{name_statement=Parmi les,élèves du collège
font de l'allemand
font de l'espagnol}
\text{name_question1=Combien sont-ils}
\text{name_question2=Quel pourcentage cela représente-t-il}
\text{name_answer1=Nombre d'élèves}
\text{name_answer2=Pourcentage}
#endif
#if defined TARGET_Tapis
\text{name_incdec=monte,baisse}
\matrix{name_statement=Le prix d'un tapis était de,euros en novembre
  il,de, en décembre
  puis,de, en janvier}
\text{name_question=Quel est son nouveau prix&nbsp;}
\text{name_answer=Le nouveau prix est}
\text{name_rep= moins de, plus de,même prix}
\text{name_euro=euros}
#endif
#if defined TARGET_DensitII2
\text{name_statement=La superficie d'un pays est de,
  et sa densité est de,habitants}
\text{name_question=Quelle est sa population (en millions)&nbsp;}
\text{name_answer=Population (en millions)}
#endif
#if defined TARGET_Essence
\text{name_statement=Une voiture consomme,litres d'essence aux 100,
  Son réservoir peut contenir,litres d'essence}
\text{name_question=Quelle est son autonomie}
\text{name_answer=Autonomie (en \(\textrm{km}\))}
#endif
#if defined TARGET_EchelleII
\text{name_statement=Une carte routière est à l'échelle}
\text{name_question=Pour une distance réelle de ,quelle est la distance sur la carte&nbsp;}
\text{name_answer=Distance sur la carte (en \(\textrm{cm}\))}
#endif
#if defined TARGET_echelcarte1
\text{name_enonce=Nous avons un plan à l'échelle ,La longueur réelle est de}
\text{name_question2=L'échelle du plan est}
#endif
#if defined TARGET_echelle1
\matrix{name_enonce=Sur un plan, une longueur de
  est représentée par une longueur de
  sur la carte}
\text{name_question2=La longueur sur la carte sera de}
#endif
#if defined TARGET_duree1 || defined TARGET_vitesse1 || defined TARGET_distance1 || defined TARGET_echelle1 || defined TARGET_echelcarte1 || defined TARGET_duree1 || defined TARGET_echellereelle1
\matrix{name_question=Remplir le tableau de proportionalité
  l'une des cases doit contenir le résultat final}
#endif
#if defined TARGET_echelle1 || defined TARGET_echelcarte1
\text{name_head=Longueurs sur la carte en ,
  Longueurs réelles en}
#endif
#if defined TARGET_duree1
\text{name_enonce=Une voiture roule à une vitesse moyenne de,
  Elle a parcouru une distance de}
\text{name_head=Durée en,Distance en}
\text{name_question2=La durée du parcours est de}
\text{name_question3=Si je convertis en heures et minutes}
#endif
#if defined TARGET_vitesse1
\text{name_enonce=Une voiture a parcouru une distance de,en}
\text{name_header=Durée en,Distance en}
\text{name_question2=La vitesse moyenne est de}
#endif
#if defined TARGET_echellereelle1
\text{name_enonce=Nous avons un plan à l'échelle,
  Nous avons mesuré sur ce plan une longueur de}
\text{name_question2=La longueur réelle correspondante est de}
#endif
#if defined TARGET_distance1
\text{name_enonce=Une voiture roule à une vitesse moyenne de,
  Le voyage a duré }
\text{name_head=Durée en min,Distance en km}
\text{name_question2=La distance parcourue est de}
#endif
