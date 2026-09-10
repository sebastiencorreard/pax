\text{name_answer=Votre réponse}
\text{name_yesno=Oui,Non}
\text{bad=\name_yesno[2],\name_yesno[1]}
#if defined TARGET_quatrprop3 || defined TARGET_quatrprop4
\text{lieu=au marché, à la superette, chez l'épicier, sur internet}
\text{action=j'achète,je prends,je monnaye,je paye en ligne }
\text{personne=Mon voisin, Mon oncle, Mon collègue}
\text{name_enonce=Je vais, et, pour, euros.,en prend,Combien paye-t-il&nbsp;}
# if defined TARGET_quatrprop3
\text{objet=melons,kit kat,dorades}
# endif
# if defined TARGET_quatrprop4
\text{objet=timbres,kg de pommes,sacs de bonbons}
# endif
#endif
#if defined TARGET_quatrprop1 || defined TARGET_quatrprop2 || defined TARGET_quatrprop5
\text{name_enonce=Compléter ce tableau de proportionnalité.}
#endif
#if defined TARGET_tableau1 || defined TARGET_tableau2 || defined TARGET_tableau3 || defined TARGET_tableau4 || defined TARGET_tableau5
\text{enonce=Ce tableau est-il un tableau de proportionnalité &#63;}
#endif
#if defined TARGET_tableau5
 \text{enonce1=Sur la vitrine d'une boulangerie,voit afficher :}
#endif
#if defined TARGET_comparer1
\text{name_bad=Le premier,Le deuxième}
\text{name_type2=grande,petite}
\text{name_type=à la campagne,en ville}
\text{name_enonce1=Un géographe étudie le lieu d'habitation dans différents pays.}
\text{name_enonce2=Dans un premier pays, Dans un deuxième pays, il trouve que,
  des personnes habitent}
\text{name_question=Dans quel pays la proportion de personnes vivant ,
  est-elle la plus }
#endif
#if defined TARGET_comparer2
\text{name_bad=La première,La deuxième}
\text{name_type=de femmes,d'hommes}
\text{name_type2=grande,petite}
\text{name_enonce1=Deux patrons comparent la proportion,
  dans leur entreprise respective.}
\text{name_enonce2=Le premier trouve qu'il y a , et le deuxième}
\text{name_question=Dans quelle entreprise la proportion,est-elle la plus}
#endif
#if defined TARGET_comparer3
\text{name_gout=pomme,poire,grenadine,pêche,menthe,citron}
\text{name_bad=La carafe contenant,litres}
\text{name_type=grande,petite}
\text{name_enonce1=prépare des boissons pour ses amis.
  Il possède deux carafes. La première peut contenir,
 litres et la deuxième, litres}
\text{name_enonce2=Dans chacune d'entre elles, il met, de sirop de}
\text{name_enonce3=Ensuite il les remplit complètement d'eau.}
\text{name_question=Dans quelle carafe la proportion de sirop
  est-elle la plus}
#endif
#if defined TARGET_comparer4
\text{name_bad=Le premier,Le deuxième, On ne peut pas savoir}
\text{name_enonce=Deux réservoirs sont remplis d'eau. Le premier est rempli aux,
  et le second aux}
\text{name_question=Quel est le réservoir qui contient le plus d'eau&nbsp;}
#endif
#if defined TARGET_comparer5
\text{name_bad=Ils ont tous les deux le même score}
\text{name_enonce1=dans la même classe et comparent
  leurs résultats aux évaluations sixième.}
\text{name_enonce2=J'ai réussi,J'ai réussi les, des questions}
\text{name_and=et}
\text{name_say=dit&nbsp;}
\text{name_question=Qui a fait le meilleur score&nbsp;}
#endif
#if defined TARGET_pourcentageA1 || defined TARGET_pourcentageA2
\text{name_question=Calculer les pourcentages suivants&nbsp;}
\text{name_answer=Votre réponse}
\text{name_of=de}
#endif
#if defined TARGET_pourcentageA3 || defined TARGET_pourcentageA4 || defined TARGET_pourcentageA5
\text{name_inst=Le résultat doit être arrondi au centième si nécessaire.}
#endif
#if defined TARGET_pourcentageA3
 \text{name_enonce=a acheté,à,Le vendeur lui a fait une remise de}
 \text{name_question=Quel est le montant de son économie,Quel prix a-t-il finalement payé}
\text{name_unit=euros}
#endif
#if defined TARGET_pourcentageA4
\text{name_enonce=a acheté une action à, Il lit dans le journal que sa valeur a augmenté de}
\text{name_question=Quel est le prix actuel de cette action,Combien a-t-il gagné}
\text{name_unit=euros}
#endif
#if defined TARGET_pourcentageA5
\text{name_enonce=Sur une tablette de chocolat pesant, il est écrit,de cacao}
\text{name_question=Quel est le poids de cacao dans la tablette}
\text{name_unit=grammes}
#endif
#if defined TARGET_calcechelle1
\text{name_bad=Une réduction,Un agrandissement}
\text{name_enonce=dans la réalité sont représentés par,sur un dessin.}
\text{name_question=Le dessin est-il un agrandissement ou une
  réduction de la réalité&nbsp;}
#endif
#if defined TARGET_calcechelle2 || defined TARGET_calcechelle3 || defined TARGET_calcechelle4 || defined TARGET_calcechelle5
\text{name_enonce=dans la réalité sont représentés par,sur un dessin.}
\text{name_question=Quel est le rapport d'échelle&nbsp;}
\text{name_answer=Rapport}
#endif
#if defined TARGET_mouvement1
\text{name_enonce=La position occupée par une bille bleue
  est notée à intervalles réguliers et reportée sur le graphique ci-dessous&nbsp;}
\text{name_question=La bille bleue suit-elle un déplacement uniforme}
#endif
#if defined TARGET_mouvement2
\text{name_enonce1=La position occupée par une bille
  est notée à intervalles réguliers et reportée sur le graphique ci-dessous&nbsp;}
\text{name_enonce2=Le point vert marque la position initiale et le point rouge la
  position finale de la bille.}
 \text{name_question=La bille suit-elle un déplacement uniforme}
#endif
#if defined TARGET_mouvement3
\text{name_question=La vitesse de,est-elle uniforme sur son parcours}
\matrix{name_enonce=Sur le graphique ci-dessous, on a noté la distance parcourue par
 en ordonnée en fonction du temps en abscisse.}
#endif
#if defined TARGET_mouvement4
\matrix{name_enonce=Dans le tableau ci-dessous, on a noté la distance parcourue par
  en kilomètres en fonction du temps en heures.}
\text{name_head=Temps (en H),Distance parcourue (en Km) }
\text{name_question=suit-il un mouvement uniforme sur son parcours&nbsp;}
#endif
#if defined TARGET_mouvement5
\text{name_enonce=remplit un récipient gradué d'eau.,
  Elle ouvre le robinet et note le temps mis pour atteindre chaque graduation
  dans le tableau ci-dessous&nbsp;}
\text{name_head=Graduation (en mL),Temps (en s)}
\text{name_question=Le débit du robinet est-il constant pendant la durée de l'expérience}
#endif
#if defined TARGET_utilechelle1
\text{name_bad=Une réduction,Un agrandissement}
\text{name_enonce=possède un dessin à l'échelle}
\text{name_question=Est-ce un agrandissement ou une réduction
  de la réalité&nbsp;}
#endif
#if defined TARGET_utilechelle2 || defined TARGET_utilechelle3 || defined TARGET_utilechelle4 || defined TARGET_utilechelle5
\text{name_answer=Largeur,Votre réponse}
#endif
#if defined TARGET_utilechelle2 || defined TARGET_utilechelle3
\text{name_question=Compléter la phrase suivante&nbsp;}
#endif
#if defined TARGET_utilechelle2
\text{name_enonce=Sur un plan à l'échelle,
  représentent, mètres dans la réalité.}
#endif
#if defined TARGET_utilechelle3
\text{name_enonce=Sur un plan à l'échelle,
  kilomètres dans la réalité sont représentés par ,  centimètres sur le plan.}
#endif
#if defined TARGET_utilechelle4
\text{name_enonce=veut réaliser un plan à l'échelle ,de sa chambre.
  La largeur de sa chambre est de,centimètres.}
\text{name_question=Quelle doit être, en centimètres,
  la largeur de sa chambre sur le plan&nbsp;}
#endif
#if defined TARGET_utilechelle5
\text{name_enonce=étudie sur une carte un parcours à réaliser.
  L'échelle de la carte est de}
\text{name_enonce2=Sur la carte, il trouve que la distance à parcourir est de,
  centimètres.}
\text{name_question=Quelle est la longueur réelle, en kilomètres,
  du parcours qu'il est en train de prépareré&nbsp;}
#endif
#if defined TARGET_reconnaitre1 || defined TARGET_reconnaitre2 || defined TARGET_reconnaitre3 || defined TARGET_reconnaitre4 || defined TARGET_reconnaitre5
\text{name_yesno=Oui,Non}
#endif
#if defined TARGET_reconnaitre1
\text{name_enonce=Pour faire une pâte à crêpes, on met, oeufs pour ,de farine.}
\text{name_question=Combien faudra-t-il de farine pour,oeufs&nbsp;}
#endif
#if defined TARGET_reconnaitre2
\text{name_enonce=réalise des escaliers, comme ci-dessous, avec des cubes en bois.}
\text{name_enonce2=pense que lorsqu'elle, la hauteur de son escalier,
il lui faut,fois plus de cubes.}
\text{name_question=a-t-elle raison&nbsp;}
\text{name_mat=double,deux,triple, trois}
#endif
#if defined TARGET_reconnaitre3
\text{name_enonce=réalise des circuits électriques selon les schémas suivants,
  dans lesquels un fil est représenté par un trait qui va d'un point à un autre.}
\text{name_question=Le nombre de fils utilisés est-il proportionnel au nombre de lampes du circuit&nbsp;}
#endif
#if defined TARGET_reconnaitre4 || defined TARGET_reconnaitre5
\text{name_question=La phrase suivante est-elle vraie&nbsp;}
# if defined TARGET_reconnaitre4
\text{rep=randrow(Le nombre d'habitants d'un village est proportionnel au nombre de maisons,2
  Le prix payé est proportionnel au nombre de personnes allant au cinéma,1
  La quantité d'essence consommée est proportionnelle au nombre de personnes assises dans la voiture,2
  La taille d'une personne est proportionnelle à son âge,2
  Le nombre d'habitants d'un immeuble est proportionnel à sa hauteur,2
  À la station service&#44; le prix à payer est propotionnel au nombre de litres d'essence achétés,1)}
# endif
# if defined TARGET_reconnaitre5
\text{rep=randrow(Le périmètre d'un carré est propotionnel à la longueur d'un de ses côtés,1
L'aire d'un carré est proportionnelle à la longueur d'un de ses côtés,2
Le périmètre d'un cercle est proportionnel à son rayon,1
L'aire d'un disque est proportionnelle à son rayon,2
L'aire d'un disque est proportionnelle au carré de son rayon,1)}
# endif
#endif
#if defined TARGET_coef1 || defined TARGET_coef2 || defined TARGET_coef3 || defined TARGET_coef4 || defined TARGET_coef5
\text{name_question=Trouver le coefficient de proportionnalité du tableau.}
# if defined TARGET_coef3
\text{name_head=kg de cerises,prix à payer (euros)}
# endif
# if defined TARGET_coef5
\text{name_inst=Vous donnerez une écriture fractionnaire du coefficient.}
# endif
#endif
