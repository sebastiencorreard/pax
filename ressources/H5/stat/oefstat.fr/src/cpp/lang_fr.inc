#if defined TARGET_histo
  \text{name_header=Intervalles,Effectifs,Histogramme}
  \text{name_instruction0=Voici une série statistique&nbsp;}
  \text{name_instruction=Déterminer parmi les histogrammes ci-dessous l'histogramme
  représentant la série statistique.}
#endif
#if defined TARGET_ajustement
  \text{question=linéaire, parabolique,exponentielle,logarithmique}
  \text{name_instruction0=Soit le nuage de points suivant&nbsp;}
 %%% leave the comma
  \text{name_instruction=Un ajustement de \(y) en \(x) du type,semble être justifié}
  \text{name_feedback=Voici la courbe d'ajustement de type \question[\choix] en rouge}
  \text{name_prompt=Ajustement}
#endif
#if defined TARGET_repstat
  \text{name_header=Caractères}
  \text{\name_eff=Effectifs}
  \text{name_listechoix= de l'histogramme des effectifs,
  de l'histogramme des effectifs cumulés,
  de l'histogramme des effectifs cumulés décroissants,
  du polygone des effectifs,
  du polygone des effectifs cumulés,
  du polygone des effectifs cumulés décroissants}
  \text{name_instruction0=Voici les effectifs d'une série statistique prenant les
  caractères de 1 à \cnt et un diagramme statistique construit à partir de cette série.}
  \text{name_instruction=Duquel s'agit-il&nbsp;}
  \text{name_prompt=Il s'agit}
#endif
