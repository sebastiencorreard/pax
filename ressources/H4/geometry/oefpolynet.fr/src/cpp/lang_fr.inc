\text{name_nom=Le nom du polyèdre est}
#if defined TARGET_11 || defined TARGET_12
\text{name_feed=On voit ici les patrons des polyèdres suivants}
# if defined TARGET_11
\text{name_instruction=Sélectionner le patron du polyèdre convexe}
# endif
#if defined TARGET_12
\text{name_instruction=Sélectionner le polyèdre convexe dont le patron est le suivant}
# endif
#endif
#if defined TARGET_21
\text{name_instruction=Donner le nombre d'arêtes du polyèdre convexe dont le patron est le suivant}
\text{name_rep=Le nombre d'arêtes est}
#endif
#if defined TARGET_22
\text{name_instruction=Donner le nombre de sommets du polyèdre convexe dont le patron est le suivant}
\text{name_rep=Le nombre de sommets est}
#endif

#if defined TARGET_31 || defined TARGET_32
\text{name_instruction=Voici le patron d'un polyèdre convexe.
  Sélectionner les sommets qui se projettent sur le même sommet du polyèdre
  que le sommet marqué par une croix.}
#endif
