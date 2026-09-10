\text{name_ou=ou}
\text{name_et=et}
\text{si1=s'}
\text{si2=si}
\text{Si1=S'}
\text{Si2=Si}
\text{ssi=si et seulement si}
\text{seulement=seulement}
\text{alors=alors}
\text{Alors=Alors}
\text{oui=oui}
\text{non=non}
\text{non2=non}
\text{spacebeforecolon=&nbsp;}
\text{Remarque=Remarque}
\text{Soient=Soient}
\text{glossaire=data/glossaire_fr}

#if defined TARGET_connecteursLN
\text{Alist =
il y a grève de bus,
il pleut ce matin,
il fait froid,
il y a du soleil,
il pleut,
je  mange beaucoup de gâteaux,
je suis joyeux,
j'écoute  Radio Latina,
je veux progresser en maths,
je veux perfectionner mon anglais,
je suis enrhumé(e),
elle danse,
tu joues de la guitare,
elle  ne veut pas devenir ingénieur,
vous êtes nuls en maths,
on est triste,
le travail est motivant
}

\text{Blist =
j'arrive en retard au lycée,
je prends mon parapluie,
je mets un pull,
je porte des lunettes noires,
il fait froid,
je grossis,
je ris,
je  danse  la salsa,
je m'entraîne sous WIMS,
je ne vais voir que des films en VO,
ma voix est cassée,
elle court,
tu chantes,
elle veut partir à l'étranger,
vous êtes forts français,
on est amoureux,
la satisfaction est totale
}

\text{nonAlist=
il n'y a pas grève de bus,
il ne pleut pas ce matin,
il ne fait pas froid,
il n'y a pas de soleil,
il ne pleut pas,
je mange peu de gâteaux,
je suis triste,
je n'écoute pas Radio Latina,
je ne veux pas progresser  en maths,
je ne veux pas améliorer mon anglais,
je ne suis pas enrhumé(e),
elle ne danse pas,
tu ne joues pas de la guitare,
elle  veut devenir ingénieur,
vous êtes forts en maths,
on est joyeux,
le travail n'est pas motivant
}

\text{nonBlist=
je n'arrive pas en retard au lycée,
je ne prends pas mon parapluie,
je n'ai pas mis de pull,
je ne porte pas de lunettes noires,
il fait chaud,
je ne grossis pas,
je ne ris pas,
je ne danse pas la salsa,
je ne m'entraîne pas  sous WIMS,
je regarde Lost In Translation en VF,
je parle normalement,
elle ne court pas,
tu ne chantes pas,
elle veut rester en France,
vous êtes nuls en français,
on n'est pas amoureux,
la satisfaction est partielle
}

\text{name_statement1=Pour chacune des propositions  suivantes, à gauche, déterminer sa structure logique.}
\text{name_statement2=les propositions peuvent être vraies ou fausses ...}
\text{name_statement3=Cliquer sur les élements qui se correspondent deux à deux.}
#endif


#if defined TARGET_deduction
\text{Alist =
il y a grève de bus,
il pleut le matin,
il fait froid,
il y a du soleil,
je  mange beaucoup de gâteaux,
je suis joyeux,
je danse la salsa,
je veux progresser,
je veux améliorer mon anglais,
je suis enrhumé(e)
}

\text{Blist =
j'arrive en retard au lycée,
je prends mon parapluie,
je mets un pull,
je porte des lunettes noires,
je grossis,
je ris,
je n'écoute que Radio Latina,
je m'entraîne sous WIMS ,
je  vois tous les films en VO,
ma voix est cassée
}

\text{nonAlist=
les bus ne sont pas grève,
il ne pleut pas le matin,
il ne faisait pas froid,
il n'y a pas de soleil aujourd'hui,
j'ai mangé peu de gâteaux,
je suis triste,
je n'aime pas la salsa,
je ne veux pas progresser,
je ne veux pas améliorer mon anglais,
je ne suis pas enrhumé(e)
}

\text{nonBlist=
je n'arrive pas en retard au lycée,
je ne prend pas mon  parapluie,
je n'ai pas mis de pull,
je ne porte pas de lunettes noires,
je n'ai pas grossi,
je ne ris pas,
j'ai écouté Fun Radio,
je ne me suis pas entraîné(e) sous WIMS,
je regarde Lost In Translation en VF,
je parle normalement
}

\text{name_statement1=On suppose que l'implication suivante est vraie&nbsp;:}
\text{name_statement2=Quelqu'un me rencontre et constate que&nbsp;:}
\text{name_statement3=Cette personne en déduit que&nbsp;:}
\text{name_statement4=Son raisonnement est-il valide&nbsp;?}
\text{name_answer=Raisonnement juste}
#endif

#if defined TARGET_implication
\text{Quand=Quand}
\text{Chaque=Chaque fois que}
\text{Question=Question}

\text{prem=
Mr Alex s'installe devant la télé,
Mme Alice sort se promener dans le parc,
Fred  est dans le parc,
Suzy grimpe sur l'arbre,
Nestor  vire-volte dans le parc,
Bubu s'enfouit sous  terre,
Fred  farfouille dans la terre,
Mme Alice est très fâchée}

\text{conc=
Mme Alice sort se promener dans le parc,
son chien Fred l'accompagne,
Suzy grimpe sur l'arbre,
Nestor quitte l'arbre pour vire-volter dans le parc,
Bubu  s'enfouit sous  terre,
Fred farfouille dans la terre,
Mme Alice se fâche,
Mr Alex s'installe devant la télé
}

\text{nonPr=
Mr Alex ne s'installe pas devant la télé,
Mme Alice ne sort pas se promener dans le parc,
Fred  n'est pas dans le parc,
Suzy ne grimpe pas sur l'arbre,
Nestor  ne  vire-volte pas dans le parc,
Bubu  ne s'enfouit pas sous  terre,
Fred  ne farfouille pas dans la terre,
Mme Alice ne se  fâche pas}

\text{nonCo=
Mme Alice ne sort pas se promener dans le parc,
Fred n'accompagne pas Mme Alice,
Suzy ne grimpe pas sur l'arbre,
Nestor ne quitte pas l'arbre pour vire-volter dans le parc,
Bubu ne s'enfouit pas sous  terre,
Fred  ne farfouille pas dans la terre,
Mme Alice ne se fâche pas,
Mr Alex ne s'installe pas devant la télé
}

\text{sujPr=Mr Alex, Mme Alice, Fred le chien, Suzy la chatte, Nestor le moineau, Bubu le ver de terre, Fred le chien, Mme Alice}
\text{sujCo=Mme Alice, Fred le chien, Suzy la chatte, Nestor le moineau, Bubu le ver de terre, Fred le chien, Mme Alice, Mr Alex}
\text{none=on ne peut rien conclure}

\text{name_citation=Cet exercice s'inspire d'un exemple donné par Alan Selby, dans "Elements of Reason&nbsp;: understanding and explaining
 reason and math" Volume 1, Printed in Canada ISBN 0-9697564-1-0. http://whyslopes.com/volume1a/}

\text{name_characters=Nos personnages sont}
\text{name_statement1a=On donne l'implication suivante, qu'on suppose vraie&nbsp;:}
\text{name_statement1b=On donne les implications suivantes, qu'on suppose toutes deux vraies&nbsp;:}
\text{name_statement2=Sans faire aucune autre hypothèse, que peut-on dire qu'il se passe lorsque}

#endif

#if defined TARGET_incoherence
\text{Contradiction=Contradiction}
\text{Exemple=Exemple}

\text{Alist=il est suédois,il est écossais,il est australien,elle est allemande,elle est cubaine, elle est japonaise}
\text{Blist=il joue au tennis, il joue du biniou, il surfe, elle joue du piano , elle danse la salsa, elle fait du Kendo}
\text{Clist=il est blond, il porte une jupe, il ne porte pas de cravate,  elle ne se maquille pas , elle est brune, elle  porte des kimonos}
\text{Dlist=il fait du ski, il joue du rugby, il passe ses vacances à Bali, elle roule en vélo ,elle adore les maths, elle fait de l'origami}
\text{Elist=il est végétarien, il est marié, il aime la bière, elle aime la Bratwurst , elle boit de la tequila, elle est célibataire}

\text{nonAlist= il n'est pas suédois, il n'est pas écossais, il n'est pas australien, elle n'est pas allemande , elle n'est pas cubaine, elle n'est pas japonaise}
\text{nonBlist =il ne joue pas au tennis, il ne joue pas du biniou , il ne  surfe pas , elle ne joue pas du piano , elle ne danse pas la salsa, elle ne fait pas Kendo}
\text{nonClist= il n'est pas blond, il ne porte pas de jupe, il porte  une cravate, elle se maquille , elle n'est pas brune, elle ne porte pas de kimono }
\text{nonDlist= il ne fait pas de ski, il ne joue pas du rugby, il ne passe pas ses vacances à Bali, elle ne roule pas en vélo , elle déteste les maths, elle ne fait pas de l'origami}
\text{nonElist=il n'est pas végétarien, il est célibataire, il n'aime pas la bière, elle n'aime pas la Bratwurst, elle ne boit pas de tequila, elle est mariée}

\text{name_statement1=Pour adhérer à un club de loisir}
\text{name_statement2=masculin, tout candidat est censé}
\text{name_statement3=féminin, toute candidate est censée}
\text{name_statement4=remplir chacune des conditions suivantes}

\text{name_question1=Cochez dans la liste suivante une proposition \(A\), qui devrait être}
\text{name_question2=à la fois vraie et fausse}
\text{name_question3= et ce,}
\text{name_question4=dans toute interprétation}
\text{name_question5=où les conditions du règlement seraient simultanément vraies}
\text{name_question6=Cela prouve par l'absurde que les conditions du règlement sont incompatibles.}

\text{name_remark=Remarque&nbsp;: vous devez, tel Sherlock Holmes, savoir envisager tous les cas et pister toutes les déductions ...}

\text{name_hint1=Faire une analyse de cas}
\text{name_hint2=considerez  les interprétations dans laquelleles conditions du règlement soient toutes vraies&nbsp;;}
\text{name_hint3=envisagez les différents cas, et pour chacun affectez les valeurs de vérité aux différentes propositions élémentaires&nbsp;;}
\text{name_hint4=trouvez \(A) telle que, dans toute interprétation,   \(A) devrait être vraie et fausse à la fois&nbsp;;}
\text{name_hint5=Ceci prouve par l'absurde qu'il n'existe aucune interprétation rendant simultanément vraies  toutes les conditions du règlement.}

\text{name_example1=Supposons que les conditions suivantes soient simultanément vraies&nbsp;:}
\text{name_example2=\(P_1) donne à distinguer deux cas&nbsp;: ou bien \(A) est vrai ou bien \(B) est vrai.}
\text{name_example3=Si \(A) est vrai et \(B) quelconque&nbsp;:  par \(P_2) et \(P_4) on déduit que  C est nécessairement vrai&nbsp;; par \(P_3)
on déduit alors que \(A) est faux.}
\text{name_example4=Si \(A) est faux et donc \(B) est vrai&nbsp;:  par \(P_4) on déduit que \(A) est vrai.}
\text{name_example5=Dans tous les cas, \(A) devrait donc être à la fois vrai et faux. Ceci est  absurde.  Il n'existe donc
aucune interprétation dans laquelle \(P_1), \(P_2) et \(P_3) soient simultanément vraies.  On dit que \(P_1), \(P_2) et \(P_3) sont incompatibles.}
#endif


#if defined TARGET_negationLN
\text{Ilexiste=Il existe un}
\text{qui=qui}
\text{Tous1=Tous les}
\text{Tous2=Tous les}
\text{Aucun=Aucun}
\text{nest=n'est}
\text{Certains=Certains}

\text{name_subjects=grec,grecs,logicien,logiciens, devoir de maths,devoirs de maths,film,films,sage,sages,élève,élèves,adulte,adultes}
\text{name_verbs=est menteur,sont menteurs,est fou, sont fous, est facile, sont faciles, est comique, sont comiques,est âgé, sont âgés, est heureux,
sont heureux,est responsable,sont responsables}
\text{name_nonverbs=est franc,sont francs, est sain d'esprit, sont sains d'esprit, est difficile, sont difficiles, est tragique, sont tragiques, est jeune, sont jeunes,
est malheureux, sont malheureux,est irresponsable,sont irresponsables}
\text{name_adj=menteur, fou, facile, comique, âgé, heureux, responsable}
\text{name_nonadj=franc,sain d'esprit, difficile, tragique, jeune, malheureux, irresponsable}

\text{name_Alist=Il pleut,
Elle danse,
Il joue de la guitare,
Elle sera ingénieur,
Je suis nul en maths,
On est triste,
Les poissons ne volent pas}

\text{name_Blist=
il fait froid,
elle court,
il chante,
travaillera à l'étranger,
je suis fort en français,
malheureux,
les poules nagent
}

\text{name_nonAlist=
Il ne pleut pas,
Elle ne danse pas,
Il ne joue pas de la guitare,
Elle ne sera pas ingénieur,
Je suis fort en maths,
On est joyeux,
Les poissons volent
}

\text{name_nonBlist=
il fait chaud,
elle ne court pas,
il ne chante pas,
restera en France,
je suis nul en français,
heureux,
les poules ne nagent pas
}

\text{name_statement1=On donne la proposition \(P) suivante&nbsp;:}
\text{name_statement2=Quelle est  la négation de \(P)&nbsp;?}
\text{name_question=La négation de \(P) est}
\text{name_remark1=Votre réponse}
\text{name_remark2=n'est pas la négation de}
\text{name_remark3=&#32; au contraire c'est un synonyme}
#endif

#if defined TARGET_negationMath
\text{ilexiste=il existe un}
\text{telque=tel que}
\text{pourtout=pour tout}
\text{reel=réel}
\text{linequation=l'inéquation}
\text{aaumoins=a au moins}
\text{aauplus=a au plus}
\text{solutions=solutions}
\text{solution=solution}
\text{strictementpositif=strictement positif}
\text{negatif=négatif}
\text{amoinsde=a moins de}
\text{aplusde=a plus de}
\text{naaucune=n'a aucune}
\text{auneinfinite=a une infinité de}

\text{name_statement1=Soit la proposition}
\text{name_statement2=Parmi les propositions suivantes, quelle est la négation de}
#endif

#if defined TARGET_reciproque
\text{Puis=Puis}
\text{Laproposition=La proposition}
\text{formuleepar=formulée par}
\text{enonceepar=énoncée par}
\text{delaproposition=de la proposition}
\text{sa=sa}
\text{reciproque=réciproque}
\text{contraposee=contraposée}
\text{estlaproposition=est la proposition}
\text{Laconjonction=La conjonction}
\text{Ladisjonction=La disjonction}
\text{apournegation=a pour négation}

\text{Alist=il est suédois,il est écossais,il est australien,elle est allemande,elle est cubaine, elle est japonaise}
\text{Blist=il joue au tennis, il joue du biniou, il surfe, elle joue du piano , elle danse la salsa, elle fait du Kendo}
\text{Clist=il est blond, il porte une jupe, il ne porte pas de cravate,  elle ne se maquille pas , elle est brune, elle  porte des kimonos}
\text{Dlist=il a des enfants, il sort le dimanche, il passe ses vacances à Bali, elle roule en vélo ,elle adore les maths, elle fait de l'origami}
\text{Elist=il est végétarien, il est marié, il aime la bière, elle aime la Bratwurst , elle boit de la tequila, elle est célibataire}
\text{nonAlist=il n'est pas suédois, il n'est pas écossais, il n'est pas australien, elle n'est pas allemande , elle n'est pas cubaine, elle n'est pas japonaise}
\text{nonBlist=il ne joue pas au tennis, il ne joue pas du biniou , il ne  surfe pas , elle ne joue pas du piano , elle ne danse pas la salsa, elle ne fait pas Kendo}
\text{nonClist=il n'est pas blond, il ne porte pas de jupe, il porte  une cravate, elle se maquille , elle n'est pas brune, elle ne porte pas de kimono }
\text{nonDlist=il n'a pas d'enfant, il ne sort pas le dimanche, il ne passe pas ses vacances à Bali, elle ne roule pas en vélo , elle déteste les maths, elle ne fait pas de l'origami}
\text{nonElist=il n'est pas végétarien, il n'est pas marié, il n'aime pas la bière, elle n'aime pas la Bratwurst, elle ne boit pas de tequila, elle est mariée}

\text{name_statement1=énonce l'implication suivante}
\text{name_statement2=énonce la proposition}

\text{name_answers=est la réciproque, est la contraposée, n'est ni la réciproque ni la contraposée}
\text{name_hint=Considérons l'implication}
#endif

#if defined TARGET_tautologie
\text{Alist =
il y a grève de bus,
il pleut le matin,
il fait froid,
il y a du soleil,
il pleut,
je  mange beaucoup de gâteaux,
je suis joyeux,
j'écoute  Radio Latina,
je progresse en maths,
j'aime l'anglais,
je suis enrhumé(e),
elle danse,
tu joues de la guitare,
tu veux être ingénieur,
vous êtes nuls en maths,
on est triste,
les poissons ne volent pas,
le travail est motivant,
}

\text{Blist =
j'arrive en retard au lycée,
je prends mon parapluie,
je mets un pull,
je porte des lunettes noires,
il fait froid,
je grossis,
je ris,
je  danse  la salsa,
je m'entraîne sous WIMS ,
je vois tous les films  en VO,
ma voix est cassée,
elle court,
tu chantes,
tu pars  à l'étranger,
vous êtes forts français,
on est amoureux,
les poules nagent,
la satisfaction est totale ,
}

\text{nonAlist=
il n'y a pas grève de bus,
il ne pleut pas le matin,
il ne fait pas froid,
il n'y a pas de soleil ,
il ne pleut pas,
je mange peu de gâteaux,
je suis triste,
je n'écoute pas Radio Latina,
je ne progresse pas  en maths,
je n'aime pas l'anglais,
je ne suis pas enrhumé(e),
elle ne danse pas,
tu ne joues pas de la guitare,
tu ne veux pas être  ingénieur,
vous êtes forts en maths,
on est joyeux,
les poissons volent,
le travail n'est pas motivant
}

\text{nonBlist=
je suis arrivé(e) à l'heure au lycée,
je ne prends pas mon parapluie,
je n'ai pas mis de pull,
je ne porte pas de lunettes noires,
il fait chaud,
je n'ai pas grossi,
je ne ris pas,
je ne danse pas la salsa,
je ne m'entraîne pas sous WIMS,
je ne vois aucun film en VO,
je parle normalement,
elle ne court pas,
tu ne chantes pas,
tu ne pars à l'étranger,
vous êtes nuls en français,
on n'est pas amoureux,
les poules ne nagent pas,
la satisfaction est partielle
}

\text{name_statement1=On considère la proposition}
\text{name_statement2=suivante}
\text{name_question1=Quelle formule logique correspond à}
\text{name_question2=est-elle une tautologie}
\text{name_hint=Une tautologie est une proposition logique toujours vraie (quelle que soient les valeurs de vérité de ses propositions élémentaires).}
#endif

#if defined TARGET_valeursVerite
\text{V=V}
\text{F=F}

\text{name_statement1=quatre propositions}
\text{name_statement2=On définit une <i>interprétation</i> ou un <i>modèle</i> logique de ces propositions en leur affectant les valeurs de vérité, Vrai (V) ou Faux (F), suivantes.}
\text{name_statement3=Pour tout rappel sur les règles de la logique booléenne, cliquer sur le lien <span class="wims_button_help disabled">Aide</span> ci-dessous ou consulter le <span class="wims_emph">glossaire</span>.}
\text{name_question1=Sous cette interprétation, calculer les valeurs de vérité des formules suivantes&nbsp;:}
#endif

#if defined TARGET_validite
\text{masculin=masculin}
\text{feminin=féminin}
\text{vrai=vrai}
\text{faux=faux}

\text{Alist=il est suédois,il est écossais,il est australien,elle est allemande,elle est cubaine, elle est japonaise}
\text{Blist=il joue au tennis, il joue du biniou, il surfe, elle joue du piano , elle danse la salsa, elle fait du Kendo}
\text{Clist=il est blond, il porte une jupe, il ne porte pas de cravate,  elle ne se maquille pas , elle est brune, elle  porte des kimonos}
\text{Dlist=il fait du ski, il fait du rugby, il passe ses vacances à Bali, elle roule en vélo ,elle adore les maths, elle apprend l'ikebana}

\text{nonAlist=il n'est pas suédois, il n'est pas écossais, il n'est pas australien, elle n'est pas allemande , elle n'est pas cubaine, elle n'est pas japonaise}
\text{nonBlist=il ne joue pas au tennis, il ne joue pas du biniou , il ne  surfe pas , elle ne joue pas du piano , elle ne danse pas la salsa, elle ne fait pas Kendo}
\text{nonClist=il n'est pas blond, il ne porte pas de jupe, il porte des cravates, elle se maquille , elle n'est pas brune, elle ne porte pas de kimono}
\text{nonDlist=il ne fait pas de ski, il ne fait pas de rugby, il ne passe pas ses vacances à Bali, elle ne roule pas en vélo , elle déteste les maths, elle n'apprend pas l'ikebana}

\text{name_statement1=possède les  caractéristiques suivantes}
\text{name_statement2=Pour adhérer à  un club de loisir}
\text{name_statement3=devrait remplir toutes les conditions ci-dessous}
\text{name_statement4=Pour chacune d'entre elles, indiquez si}
\text{name_statement5=la vérifie ou pas}
\text{name_hint1=Il s'agit de calculer les valeurs de vérité des assertions (formules) proposées, connaissant les valeurs de vérité des propositions élémentaires.}
\text{name_hint2=Pour tout rappel sur le calcul des valeurs de vérité, voir l'aide ou l'exercice "Tables de vérité".}
#endif

