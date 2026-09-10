#if defined TARGET_concret1
\text{name_instruction=Écrire la formule,
  donnant la mesure de l'aire de la figure ci-dessous en fonction de }
#endif
#if defined TARGET_concret2
\text{metre=mètre,mètres}
\text{metre=\a=1?\metre[1]:\metre[2]}
\text{name_dessin=Jardin,Chemin}
\text{name_instruction=Un jardinier réalise des chemins de largeur \a \metre
  autour de jardins carrés.
  Sur les bords des chemins (des deux côtés), il place des petites barrières en bois.}
\text{name_question= Exprimer la longueur de barrière \(\A\) dont il a besoin
  en fonction de la longueur \(\x\) du côté du jardin.}
#endif
#if defined TARGET_concret3
\text{metre=mètre,mètres}
\text{metre=\a=1?\metre[1]:\metre[2]}
\text{name_instruction=Un maçon construit des murs en utilisant des briques de hauteur
  20 centimètres et de longueur 50 centimètres.}
\text{name_question=Quelle est la formule \(\A\) qui permet de déterminer le nombre
  de briques qu'il doit acheter pour construire un mur de \(\a\) \metre de haut
  et de \(\x\) mètres de long&nbsp;}
#endif
#if defined TARGET_concret4
\text{name_instruction=Un jardinier plante des arbres des deux côtés d'un chemin de
  \(\a m\) de long. Il plante un arbre tous les \(\x\) mètres.}
\text{name_question= Quelle est la formule,
  qui permet de déterminer le nombre d'arbres que le jardinier doit acheter&nbsp;}
#endif
#if defined TARGET_concret5
\text{name_instruction=Un restaurateur dispose de tables de \a[1] places et
  de tables de \a[2] places. Dans sa salle, il met en place \(\x[1]\) tables de
  \a[1] places et \(\x[2]\) tables de \a[2] places.
}
\text{name_question= Exprimer le nombre \(\A\) de chaises
  dont il a besoin en fonction de \(\x[1]\) et de \(\x[2]\).
}
#endif
#if defined TARGET_evaluer1 || defined TARGET_evaluer2 || defined TARGET_evaluer3 || defined TARGET_evaluer4 || defined TARGET_evaluer5
\text{name_instruction=Combien vaut l'expression, pour}
\text{name_youranswer=Votre réponse}
#endif
#if defined TARGET_factoriser1 || defined TARGET_factoriser2 || defined TARGET_factoriser3 || defined TARGET_factoriser4 || defined TARGET_factoriser5
\text{name_instruction=Factoriser l'expression suivante&nbsp;}
#endif
#if defined TARGET_developper1 || defined TARGET_developper2 || defined TARGET_developper3 || defined TARGET_developper4 || defined TARGET_developper5
\text{name_instruction=Développer l'expression suivante&nbsp;}
#endif
#if defined TARGET_simplifier1 || defined TARGET_simplifier2 || defined TARGET_simplifier3 || defined TARGET_simplifier4
\text{name_instruction=Simplifier l'expression suivante&nbsp;}
\text{name_warning=Vous ne devez écrire que les symboles indispensables.}
\text{name_answer=Réponse}
\text{name_cond=Bonne réponse}
\text{name_goodanswer=La bonne réponse est }
\text{name_goodanswerremark=Aucun symbole mutiplié n'est nécessaire}
#endif
#if defined TARGET_tester1 || defined TARGET_tester2 || defined TARGET_tester3 || defined TARGET_tester4 || defined TARGET_tester5
\text{bad=Oui,Non}
\text{name_instruction=L'égalité suivante est-elle vraie pour}
#endif
#if defined TARGET_formule1 || defined TARGET_formule2 || defined TARGET_formule3 || defined TARGET_formule4 || defined TARGET_formule5
# if defined TARGET_formule1
 \text{enonce=la somme de, et de}
# endif
# if defined TARGET_formule2
 \text{enonce=la différence entre, et}
# endif
# if defined TARGET_formule3
 \text{enonce=le produit de, et de}
# endif
# if defined TARGET_formule4
 \text{enonce=la somme de, et du produit de,}
# endif
# if defined TARGET_formule5
 \text{enonce=le produit de, par la somme de , et de}
# endif
\text{name_instruction=Pour un nombre, comment s'écrit}
\text{name_answer=Votre réponse}
#endif
