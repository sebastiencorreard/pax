#if defined TARGET_interpret || defined TARGET_arbre1 || defined TARGET_arbre2 || defined TARGET_tableau1 || defined TARGET_tableau2 || defined TARGET_tableau3 || defined TARGET_tableau4 || defined TARGET_tableau5 || defined TARGET_tableau6
\text{name_classeA1=Filles,Externes,Fumeurs,Français,de&nbsp;,d',de&nbsp;,de&nbsp;}
\text{name_classeA2=Garçons,Demi-pensionnaires,Non fumeurs,Etrangers,de&nbsp;,de&nbsp;,de&nbsp;,d'}
\text{name_classeB1=Adolescents,Scientifiques,Sportifs,Travailleurs,d',de&nbsp;,de&nbsp;,de&nbsp;}
\text{name_classeB2=Enfants,Littéraires,Non sportifs,Chômeurs,d',de&nbsp;,de&nbsp;,de&nbsp;}
\text{name_caption=Tableau en nombre de personnes}
\text{name_reply=Réponse}
\text{name_total=Total}
#endif
#if defined TARGET_interpret || defined TARGET_arbre1 || defined TARGET_arbre2
\text{name_groupe=Un établissement,Un lycée,Un groupe,Un groupe}
\text{name_individu=élèves,élèves,adultes,adultes}
note for translators: in the following keep commas
\text{name_statement=compte,répartis de la manière suivante&nbsp;}
#endif
#if defined TARGET_interpret || defined TARGET_tableau1 || defined TARGET_tableau2 || defined TARGET_tableau4 || defined TARGET_tableau3 || defined TARGET_tableau5 || defined TARGET_tableau6
\text{name_approx=aproximativement}
\text{name_consig=Écrire les pourcentages en gardant trois décimales.}
#endif
#if defined TARGET_interpret
\text{name_consigne=Compléter les phrases suivantes (par des valeurs arrondies à l'entier)&nbsp;}
\text{name_of=des}
\text{name_cond1=sont des}
\text{name_cond2=Parmi les}
note for translators: in the following keep commas
\text{name_feedback=Pour la question,le total de référence est,et la partie est,donc la réponse est}
#endif
#if defined TARGET_arbre1 || defined TARGET_arbre2
\text{name_consigne=Compléter l'arbre par des valeurs en % arrondies à l'entier.}
#endif
#if defined TARGET_tableau1 || defined TARGET_tableau2 || defined TARGET_tableau3 || defined TARGET_tableau4 || defined TARGET_tableau5 || defined TARGET_tableau6 || defined TARGET_loibinom1
\text{name_and=et}
#endif

#if defined TARGET_tableau1 || defined TARGET_tableau2 || defined TARGET_tableau3
\text{name_intro1=On étudie un groupe de}
\text{name_intro2=personnes composé}
\text{name_intro3=Parmi les}
\text{name_intro4=on compte}
\text{name_intro5=,personne dans le groupe des}
\text{name_intro6=personnes sont des,personne est dans le groupe des}
#endif
#if defined TARGET_tableau4 || defined TARGET_tableau5 || defined TARGET_tableau6
\text{name_intro1=On étudie un groupe de personnes composé}
\text{name_intro2=Parmi les}
\text{name_intro3=on compte}
\text{name_intro4=et parmi les}
\text{name_intro5=,personne dans le groupe des}
\text{name_of=de}
#endif

#if defined TARGET_tableau1
\text{name_statement=Compléter le tableau ci-dessous.}
#endif

#if defined TARGET_tableau2 || defined TARGET_tableau4 || defined TARGET_tableau3 || defined TARGET_tableau5 || defined TARGET_tableau6
\text{name_statement=Compléter les tableaux ci-dessous.}
\text{name_caption1=Tableau marginal en pourcentage}
#endif
#if defined TARGET_tableau2 || defined TARGET_tableau4
#endif

#if defined TARGET_tableau6
\text{name_intro6=quel est le pourcentage des}
\text{name_intro7=Quel est le pourcentage des}
#endif

#if defined TARGET_equiproba1
\text{name_statement1=sprinters participent à la finale du 100 mètres}
\text{name_statement2=Combien de podium sont possibles\(\,\)}
\text{name_statement3=On se place dans un cas d'équiprobabilité}
\text{name_statement4=Quelle est la probabilité de chaque podium\(\,\)}
\text{name_answer1=nombre de podiums}
\text{name_answer2=probabilité}
\text{name_consig=Si vous donnez une valeur approchée de la probabilité, gardez au moins cinq décimales.}
#endif

#if defined TARGET_equiproba2
\text{name_g=Guillaume,Pierre,Alain,Sofiane,Kevin}
\text{name_f=Claire,Alizée,Fadia,Jennifer,Lola}
\text{name_and=et}
\text{name_people=personnes}
\text{name_statement1=font partie d'une assemblée de}
\text{name_statement2=On choisit au hasard dans l'assemblée, un président et un secrétaire}
note for translators: in the following keep commas
\text{name_statement3=Quelle est la probabilité que,soit président et,secrétaire\(\;\)}
\text{name_statement4=On choisit au hasard dans l'assemblée deux secrétaires}
note for translators: in the following keep commas
\text{name_question=Quelle est la probabilité que,soient désignés\(\;\)}
\text{name_answer=probabilité}
\text{name_solution1=Dans le premier cas, il y a}
\text{name_solution2=issues possibles}
\text{name_solution3=Dans le second cas, il y a}
\text{name_solution4=issues possibles puisque l'ordre du tirage n'intervient pas}
#endif

#if defined TARGET_equiproba3
\text{name_statement1=Un jardinier mélange}
\text{name_statement2=oignons de tulipes rouges avec}
\text{name_statement3=oignons de tulipes jaunes}
\text{name_statement4=Il réalise une bordure en plantant en ligne au hasard les}
\text{name_statement5=oignons}
\text{name_statement6=Calculer la probabilité des événements suivants\(\;\)}
\text{name_cond1=les}
\text{name_cond2=tulipes rouges sont les unes à côté des autres}
\text{name_cond3=les tulipes rouges et jaunes sont alternées sur la bordure}
\text{name_cond4=tulipes situées à droite de la bordures sont rouges}
\text{name_solution1=Si toutes les tulipes étaient différentes, il y aurait}
\text{name_solution2=bordures différentes possibles}
\text{name_solution3=Comme les}
\text{name_solution4=tulipes rouges sont identiques, il faut diviser ce nombre par}
\text{name_solution5=De même, les}
\text{name_solution6=tulipes jaunes sont identiques, il faut donc encore diviser par}
\text{name_solution7=Donc, il y a}
\text{name_solution8=bordures différentes possibles}
\text{name_solution9=Combien peut-il y avoir de tulipes jaunes à gauche des tulipes rouges\(\;\)}
\text{name_solution10=Donc}
\text{name_solution11=Soit la rangée commence par un tulipe rouge, soit elle commence par une tulipe jaune}
\text{name_solution12=Où peut-on placer la dernière tulipe rouge\(\;\)}
\text{name_solution13=Il y a}
\text{name_solution14=possibilités}
\text{name_or=ou}
#endif

#if defined TARGET_equiproba2|| defined TARGET_equiproba3 || defined TARGET_loibinom1 || defined TARGET_loivar3
\text{name_consig=Donner les valeurs exactes des probabilités en utilisant si besoin des fractions.}
#endif

#if defined TARGET_loibinom1
\text{name_statement1=On a acheté un dé équilibré ayant}
\text{name_statement_list=une face blanche,faces blanches,une face noire,faces noires}
note for translators: in the following keep commas
\text{name_statement2=On lance le dé,fois de suite,les lancers étant indépendants,et on désigne par,la variable aléatoire}
\text{name_variable=nombre de faces blanches obtenues}
\text{name_question=Donner la loi de probabilité de}
#endif

#if defined TARGET_loibinom1 || defined TARGET_loivar3
\text{name_solution1=A chaque lancer, la probabilité d'avoir une face blanche est de}
\text{name_solution2=et celle d'avoir une face noire est de}
\text{name_solution4=une probabilité de}
#endif
#if defined TARGET_loibinom1
\text{name_solution3=Par exemple si on lance le dé 2 fois, le principe multiplicatif donne&nbsp;}
\text{name_solution5=d'avoir 0 face blanche&nbsp;}
\text{name_solution6=d'avoir 2 faces blanches&nbsp;}
\text{name_solution7=d'avoir 1 face blanche}
#endif
#if defined TARGET_loivar3
\text{name_solution3=Le principe multlplicatif donne donc&nbsp;}
\text{name_solution5=d'avoir 0 face noire&nbsp;}
\text{name_solution6=d'avoir 2 faces noires&nbsp;}
\text{name_solution7=d'avoir 1 face noire}
#endif

#if defined TARGET_loivar1
note for translators: in the following keep commas
\text{name_statement1=Soit un univers,et une probabilité,sur,définie par&nbsp;}
\text{name_statement2=On définit une variable aléatoire réelle \(X\) par le tableau de valeurs suivant&nbsp;}
\text{name_statement3=Déterminer la loi de probabilité \(P_X\) de \(X\) en complétant le tableau suivant&nbsp;}
note for translators: in the following keep commas
\text{name_hint=Dans le premier tableau,pour tout}
#endif

#if defined TARGET_loivar2
\text{name_list_rep=un jeu équilibré, un jeu avantageux, un jeu désavantageux}
note for translators: in the following keep commas
\text{name_statement=Soit un univers,muni d'une probabilité,une variable aléatoire réelle,dont la loi de probabilité est définie par le tableau suivant&nbsp;}
\text{name_question1=Calculer l'espérance mathématique de}
\text{name_question2=Calculer la variance de}
\text{name_question3=La variable aléatoire réelle}
\text{name_question4=correspond à}
#endif

#if defined TARGET_loivar3
\text{name_variable=nombre de faces noires obtenues}
text{name_comma=&#44;}
\text{name_comma=,}
note for translators: in the following keep commas
\text{name_statement=On a acheté un dé équilibré à,faces blanches et,faces noires,On lance le dé,fois de suite,les lancers étant indépendants,et l'on désigne par,la variable aléatoire réelle,Compléter le tableau pour qu'il décrive la loi de probabilité de}
#endif

#if defined TARGET_proba1 || defined TARGET_proba2 || defined TARGET_proba3
\text{name_and=et}
note for translators: in the following keep commas
\text{name_statement=Soit une probabilité,sur un univers,et deux événements,tels que\(\;\)}
\text{name_question=Calculer}
#endif
#if defined TARGET_proba1
\text{name_incomp=incompatibles}
#endif
