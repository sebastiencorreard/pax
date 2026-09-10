#if defined TARGET_inversion
\text{name_enonce=Voici un arbre de probabilités. Compléter son arbre inverse&nbsp;}
#endif
#if defined TARGET_tirage1 || defined TARGET_tirage2 || defined TARGET_remise1
\text{deux=deux}
\text{avecsans=avec, sans}
\text{couleurs=bleues,rouges,orange,noires,violette,grises,blanches}
\text{couleur=bleue,rouge,orange,noire,violette,grise,blanche}
#endif
#if defined TARGET_tirage2
\text{deuxieme=deuxième}
#endif
#if defined TARGET_chemin || defined TARGET_ensemble
\text{name_enonce=Voici un arbre pondéré de probabilités.}
# if defined TARGET_chemin
\text{name_question=Calculer la probabilité de l'événement,}
\text{name_answer=Probabilité de}
# endif
# if defined TARGET_ensemble
\text{name_question=Parcourir tous les chemins tracés en rouge partant de la racine
  de l'arbre aide à déterminer la probabilité d'un événement.
  Décrire cet événement en utilisant les étiquettes proposées.}
# endif
#endif
#if defined TARGET_binarytree || defined TARGET_tree1
\text{name_enonce= Voici un arbre de probabilité}
# if defined TARGET_binarytree
\text{name_enonce1=dans lequel interviennent deux événements \(A\) et \(B\) et
   leurs contraires \(A^c\) et \(B^c\) et}
\text{name_question=Calculer}
\text{name_answer=Probabilité}
# endif
\text{name_enonce2=qu'il s'agit de compléter&nbsp;}
#endif
