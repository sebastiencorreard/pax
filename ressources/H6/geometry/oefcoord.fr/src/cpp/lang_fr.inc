\text{name_choicecoord=coordonnées cylindriques,coordonnées sphériques}

#if defined TARGET_spheric0 || defined TARGET_cylindric0
\matrix{name_matrice= du, le, plan
du, le, demi-plan contenu dans le plan, avec
de la, la, droite
du,le, plan
de la, la, demi-droite,orientée vers le haut}
\matrix{name_question=L'ensemble des points de \(\RR^3) vérifiant en
  est
  L'équation, en COORD s'exprime en termes
  et est de la forme
  ou}
\text{name_instruction=Écrire la réponse sous forme exacte.
  Si une seule valeur est nécessaire, mettre
  deux fois la même, sinon, dans l'ordre croissant.}
\text{name_type=type de courbe}
#endif
#if defined TARGET_spheric1 || defined TARGET_cylindric1
\text{choix=un demi-cercle, un cercle, une demi-droite, une droite, deux droites, un point}
\text{name_coord=coordonnées cylindriques,coordonnées sphériques}
\text{name_question=On considère l'ensemble des points de \(\RR^3) vérifiant en}
\matrix{name_question2=De quel type de lieu s'agit-il
  Donner le vecteur directeur unitaire de la demi-droite dans le repère cartésien&nbsp;
  Donner un vecteur unitaire normal au plan du cercle dans le repère cartésien&nbsp;
  Donner les coordonnées du point dans le repère cartésien&nbsp;}
\matrix{name_cond=point sur la droite 0z
  vecteur colinéaire
  Point
  vecteur unitaire
  Le vecteur donné est-il unitaire&nbsp;}
\text{name_type=lieu}
\text{name_hint=Faites un dessin&nbsp;}
\matrix{name_feed=Le point que vous donnez n'est pas sur la droite Oz.
  Le vecteur que vous donnez n'est pas sur la droite normale
  Le vecteur que vous donnez n'est pas unitaire
  La,Une, solution est le vecteur
  Le point est le point}
#endif
#if defined TARGET_spheric2 || defined TARGET_cylindric2
\text{choix=un demi-plan,un cylindre,une sphère,un demi-cône,un plan,un cône,une demi-droite}
\text{choix2=vers le haut,vers le bas}
\text{name_coord=coordonnées cylindriques,coordonnées sphériques}
\matrix{name_question=On considère l'ensemble des points de \(\RR^3\) vérifiant en
  De quel type de lieu s'agit-il
  Le demi-cône est-il orienté vers le haut ou vers le bas&nbsp;
 	Donnez l'équation cartésienne du cône qui le contient&nbsp;
  La demi-droite est-elle orientée vers le haut ou vers le bas&nbsp;
  Donnez l'équation cartésienne (polynomiale en x, y et z)
  Donnez l'équation cartésienne (polynomiale en x, y et z) du plan qui le contient
  Donnez l'équation cartésienne (polynomiale en x, y et z) du cône qui le contient}
\text{name_answer=type de surface,équation cartésienne,orientation}
\matrix{name_hint=Faites un dessin&nbsp;
  Pour obtenir l'équation du cône, partez de l'équation}
#endif
#if defined TARGET_sphericsym
\text{name_question=Dans la symétrie par rapport au plan, les coordonnées cartésiennes
  sont transformées de la manière suivante}
\text{name_question1=et les coordonnées sphériques sont transformées de la manière suivante}
\text{name_hint=Écrire theta ou phi pour les angles, pi pour }
#endif
