#if defined TARGET_oefutigraph5
\text{name_instruction=Nous avons interrogé les élèves d'un collège sur leur préférence de couleur.
  Le diagramme circulaire donne leur préférence entre
  le rouge, le bleu, le jaune et le vert.
  Dans le collège, nous avons}
\text{listefr=bleu,rouge,jaune, vert}
\text{listeabr=B,R,J,V}
\text{name_choixcouleur=Choix des couleurs}
\text{name_pupil=élèves}
\text{name_question=Combien d'élèves préfèrent le}
#endif
#if defined TARGET_oefutigraph2 || defined TARGET_oefutigraph3 || defined TARGET_oefutigraph4 || defined TARGET_oefutitableau1 || defined TARGET_oefutitableau2 || defined TARGET_oefutitableau3 || defined TARGET_oefutitableau4 || defined TARGET_oefutitableau5 || defined TARGET_oefliretableau1 || defined TARGET_oefliretableau2 || defined TARGET_oefliretableau3 || defined TARGET_oefliretableau4 || defined TARGET_oefliretableau5
\text{mois=Janvier,Février,Mars,Avril,Mai,Juin,Juillet,Août,Septembre,Octobre,Novembre,Décembre}
\text{ms=de janvier,de février,de mars,d'avril,de mai,de juin,
  de juillet,d'août,de septembre,d'octobre,de novembre,de décembre}
\text{ville=Toulouse,Nice,Paris,Marseille,Strasbourg,Lille}
#endif
#if defined TARGET_oefutigraph1
\text{name_instruction=Après un contrôle de mathématiques, le professeur dresse un tableau
  des notes obtenues par les élèves de sa classe.}
\text{name_instruction1=En utilisant le graphique, répondre à la question suivante&nbsp;}
\text{name_question=Quel est le nombre d'élèves dans la classe&nbsp;}
\text{name_header=Notes,Nbre}
#endif
#if defined TARGET_oefutigraph2 || defined TARGET_oefutigraph3 || defined TARGET_oefutigraph4
\text{name_question=Voici le total des précipitations en mm
  par mois pour la ville de}
\text{name_header=Mois,Precipitations en mm}
#endif
#if defined TARGET_oefutigraph2
\text{enonc1=Cliquer sur le(s) mois qui a (ont) le maximum de précipitations}
#endif
#if defined TARGET_oefutigraph3
\text{name_choix=inférieur}
#endif
#if defined TARGET_oefutigraph4
\text{name_choix=supérieur}
#endif
#if defined TARGET_oefutigraph3 || defined TARGET_oefutigraph4
\text{enonc1=Cliquer sur le(s) mois dont le total des précipitations
  est strictement \name_choix à \mm mm}
#endif
#if defined TARGET_oefutitableau1 || defined TARGET_oefutitableau2 || defined TARGET_oefutitableau3 || defined TARGET_oefutitableau4 || defined TARGET_oefutitableau5
\text{name_enonce=Nous avons le total des précipitations en mm par mois pour la ville de}
#endif
#if defined TARGET_oefgraph3 || defined TARGET_oefgraph4
\text{name_instruction=Après un contrôle de mathématiques,
  le professeur dresse un tableau des notes obtenues
  par les élèves de sa classe. En utilisant le graphique,
  répondre&nbsp;
}
# if defined TARGET_oefgraph3
\text{name_instr= aux questions suivantes&nbsp;}
\text{name_question=Quel est le nombre d'élèves qui ont pour note}
# endif
# if defined TARGET_oefgraph4
\text{name_instr= à la question suivante&nbsp;}
\matrix{name_question=Quel est le nombre d'élèves qui ont
  de 10 pour note&nbsp;}
\text{name_pm=plus,moins}
# endif
#endif
#if defined TARGET_oefutitableau1
\text{enonc1=Cliquer sur le(s) mois dont le total des précipitations est inférieur à 50 mm}
#endif
#if defined TARGET_oefutitableau2
\text{enonc1=Cliquer sur le(s) mois dont le total des précipitations est supérieur ou égal à 50 mm}
#endif
#if defined TARGET_oefutitableau3
\matrix{name_enonc1=Cliquer sur le(s) mois dont le total des précipitations est compris entre
  mm et
  mm
  strictement supérieur à
  mm et strictement inférieur à
  mm}
#endif
#if defined TARGET_oefutitableau4 || defined TARGET_oefutitableau5
\text{name_instruction=Vous n'oublierez pas de préciser l'unité à votre résultat.}
#endif
#if defined TARGET_oefutitableau4
\text{name_ch=premiers mois,derniers mois}
\text{name_enonc1=Donner la somme des précipitations pour les six}
#endif
#if defined TARGET_oefutitableau5
\text{enonc1=Donner la somme des précipitations pour l'année.}
#endif
#if defined TARGET_oefplacfrasimpl1 || defined TARGET_oefplacfrasimpl2 || defined TARGET_oefplacfrasimpl3 || defined TARGET_oefplacfrasimpl4 || defined TARGET_oefplacfrasimpl5
garder retour de ligne
\matrix{name_question=Nous avons une demi-droite graduée. Placer la fraction
en cliquant sur la demi-droite graduée.}
#endif
#if defined TARGET_oefliretableau1 || defined TARGET_oefliretableau2 || defined TARGET_oefliretableau3 ||  defined TARGET_oefliretableau4 || defined TARGET_oefliretableau5
\text{name_instruction=Nous avons les moyennes des températures par mois pour la ville de}
#endif
#if defined TARGET_oefliretableau1
\text{name_enonc1=Donner la température moyenne du mois \ms[\b]}
#endif
#if defined TARGET_oefliretableau2
\text{name_enonc1=Donner la température moyenne la plus basse}
#endif
#if defined TARGET_oefliretableau3
\text{name_enonc1=Donner la température moyenne la plus haute}
#endif
#if defined TARGET_oefliretableau4 || defined TARGET_oefliretableau5
\text{name_hint=Si nécessaire, séparer les mois par une virgule.}
# if defined TARGET_oefliretableau4
\text{name_enonc1=Donner le(s) mois le(s) plus froid(s) en moyenne.}
# endif
# if defined TARGET_oefliretableau5
\text{name_enonc1=Donner le(s) mois le(s) plus chaud(s) en moyenne.}
# endif
#endif
#if defined TARGET_oefgraph1 || defined TARGET_oefgraph2
\text{name_reps=oiseaux,mammifères,insectes,fruits,été,hiver,ete}
\text{name_instruction1=Le renard mange des mammifères,
  des oiseaux, des insectes et des fruits.}
\text{name_instruction2=Les deux diagrammes circulaires donnent la composition
  de l'alimentation du renard selon les saisons.}
\text{name_liste=Rouge : Mammifères, Bleu : Oiseaux,
  Jaune : Insectes, Vert : Fruits}
\text{listeabr=Ois.,Mamm.,Insec.,Fruits} skyblue,red,yellow,lightgreen
# if defined TARGET_oefgraph1
\text{name_question=Quel pourcentage les,
  représentent-ils dans l'alimentation du renard en}
# endif
# if defined TARGET_oefgraph2
\text{name_question=Quel est l'aliment principal mangé par
  le renard à chacune des saisons,en été, en hiver}
# endif
#endif
#if defined TARGET_oefcompltabl1 || defined TARGET_oefcompltabl2 || defined TARGET_oefcompltabl3 || defined TARGET_oefcompltabl4
\text{name_instruction=Nous avons fait une enquête dans le collège sur }
\text{name_question=Compléter le tableau suivant&nbsp;}
\text{name_total=Total}
\matrix{col=Niveaux,6<sup>e</sup>,5<sup>e</sup>,4<sup>e</sup>,3<sup>e</sup>
  Niveaux,6<sup>e</sup>,5<sup>e</sup>,4<sup>e</sup>,3<sup>e</sup>
  Transports,en bus,à pied,en voiture,à vélo
  Durées,0 à 15 min,16 à 30 min,31 min à 60 min, + plus 1 h
  Couleurs,Bleu, Rouge, Jaune, Vert
  Couleurs,Bleu, Rouge, Jaune, Vert}
\matrix{lig=Sexe,filles,garçons, la répartition filles/garçons
  Qualité,Externes, Demi-pensionnaires, la qualité
  Niveaux,6<sup>e</sup>-5<sup>e</sup>,4<sup>e</sup>-3<sup>e</sup>, les moyens de transport
  Niveaux,6<sup>e</sup>-5<sup>e</sup>,4<sup>e</sup>-3<sup>e</sup>, les durées de transport
  Sexe,filles,garçons, les préférences de couleur
  Sexe,filles,garçons, les préférences de couleur}
#endif
#if defined TARGET_oefcompltabl5
\text{name_instruction=Après un contrôle de mathématiques,
  le professeur dresse un tableau des notes obtenues
  par les élèves de ses classes&nbsp;
}
\matrix{name_header=Note sur 20
  Nombre d'élèves ayant la note indiquée au-dessus}
\text{name_condition=Le diagramme est correct}
\text{name_answer=Bâton}
\text{name_question=Représenter les notes obtenues par un diagramme en bâtons, en
  tirant les bâtons en bas dans le dessin.}
\text{your_answer=Votre réponse&nbsp;}
\text{solution_exercise=Solution de l'exercice&nbsp;}
#endif
#if defined TARGET_oeffairetabl1
 \text{name_instruction=Les élèves d'un collège ont donné leurs préférences de couleur.
  Les résultats sont en pourcentages et nous avons fait un diagramme circulaire}
\text{name_question=Compléter le tableau&nbsp;}
\text{name_header=rouge,bleu,jaune,vert,Total, Pourcentages}
#endif
#if defined TARGET_oefutitabl1 || defined TARGET_oefutitabl2 || defined TARGET_oefutitabl3 || defined TARGET_oefutitabl4 || defined TARGET_oefutitabl5
\text{niv=6ème,5ème,4ème,3ème,Total}
\text{qual=externes, demi-pensionnaires, externes, demi-pensionnaires}
\text{sex=filles,garçons}
\text{name_instruction=Nous avons fait une enquête dans le collège sur la qualité des élèves.}
# if defined TARGET_oefutitabl1
\integer{b=randint(1..4)}
\text{name_enonc1=Donner le nombre d'élèves de}
\text{enonc1=\name_enonc1 \niv[\b]}
\integer{rp1=\totc[\b]}
# endif
# if defined TARGET_oefutitabl2 || defined TARGET_oefutitabl3 || defined TARGET_oefutitabl4
\text{name_enonc1=Donner le nombre de}
\text{name_header=Notes,Nbre}
# endif
# if defined TARGET_oefutitabl5
\text{name_enonc1=Donner le nombre d'élèves dans le collège}
# endif
#endif
#if defined TARGET_oefliretabl1 || defined TARGET_oefliretabl2 || defined TARGET_oefliretabl3 || defined TARGET_oefliretabl4 || defined TARGET_oefliretabl5
\text{niv=6ème,5ème,4ème,3ème,Total}
\text{qual=externes, demi-pensionnaires, externes, demi-pensionnaires}
\text{sex=filles,garçons}
\text{name_instruction=Nous avons fait une enquête dans le collège sur la qualité des élèves.}
\text{name_total=Total}
\text{name_question=Répondre aux questions suivantes&nbsp;}
#if defined TARGET_oefliretabl1
\text{enonc1=L'effectif des \sex[floor((\b+1)/2)] \qual[\b] en \niv[\a[1]] est}
\text{enonc2=L'effectif des \sex[floor((\d+1)/2)] \qual[\d] en \niv[\a[2]] est}
# endif
#if defined TARGET_oefliretabl2
\text{enonc1=L'effectif des élèves en \niv[\a[1]] est}
\text{enonc2=L'effectif des élèves en \niv[\a[2]] est}
# endif
# if defined TARGET_oefliretabl3
\text{enonc1=L'effectif des \sex[floor((\a[1]+1)/2)] \qual[\a[1]] est}
\text{enonc2=L'effectif des \sex[floor((\a[2]+1)/2)] \qual[\a[2]] est}
# endif
# if defined TARGET_oefliretabl4
\text{enonc1=L'effectif des \sex[\b] en \niv[\a] est}
\text{enonc2=L'effectif des élèves du collège est}
# endif
# if defined TARGET_oefliretabl5
\text{enonc1=L'effectif des \qual[\b] en \niv[\a[1]] est}
\text{enonc2=L'effectif des \qual[\b] en \niv[\a[2]] est}
# endif
#endif
#if defined TARGET_oefgraph5
\matrix{name_instruction=Nous avons fait un relevé de températures tous les trois jours.
  En utilisant le graphique, répondre aux questions suivantes&nbsp;
  La température la plus basse est de
  La température la plus élevée est de}
#endif
#if defined TARGET_oeffairetabl5
\text{enonc=On a demandé aux élèves d'un collège le nombre de frères et soeurs qu'ils avaient.
<ul><li>\effs[1] élèves ont dit qu'ils avaient aucune soeur et aucun frère,
</li><li>\effs[2] élèves une soeur et aucun frère, \effs[3] élèves une soeur et un frère,
</li><li>\effs[4] élèves deux soeurs et aucun frère, \effs[5] élèves deux soeurs et un frère,
</li><li>\effs[6] élèves deux soeurs et deux frères, \effs[7] élèves aucune soeur et un frère,
</li><li>\effs[8] élèves aucune soeur et deux frères, \effs[9] une soeur et deux frères.
</li></ul>}
\text{name_header=soeur,soeurs,frère,frères}
\text{name_question=Avec les informations contenues dans ce texte, compléter le tableau suivant&nbsp;}
#endif
#if defined TARGET_oeffairetabl4
\text{name_instruction=Nous avons fait un relevé de températures tous les trois jours.
  En utilisant le graphique, remplir le tableau&nbsp;}
\text{name_temp=Température en}
\text{name_day=Jours}
#endif
#if defined TARGET_oeffairetabl3
\text{name_instruction=Voici les âges dans une population à la suite d'une enquête&nbsp;}
\text{name_question=Compléter le tableau suivant,Nbre de personnes,
  Nombre total de personnes (Effectif total), Effectif,Nbre total de personnes,Ages}
#endif
#if defined TARGET_oeffairetabl2
\text{name_instruction=Après un contrôle de mathématiques, le professeur dresse un tableau
  des notes obtenues par les élèves de sa classe}
\text{name_question=En utilisant le graphique, remplir le tableau}
\text{name_header=Note sur ,Nombre d'élèves,Notes,Nbr}
#endif
#if defined TARGET_oeflirefrasimpl1 || defined TARGET_oeflirefrasimpl2 || defined TARGET_oeflirefrasimpl3 || defined TARGET_oeflirefrasimpl4 || defined TARGET_oeflirefrasimpl5
\text{name_instruction=Nous avons une demi-droite graduée. Le point indiqué par la flèche
  correspond à une fraction <strong>simple</strong>.
  Donner cette fraction&nbsp;}
\text{name_answer=Numérateur,Dénominateur}
#endif

