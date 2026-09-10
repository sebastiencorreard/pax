#if defined TARGET_solide1 || defined TARGET_solide2 || defined TARGET_solide3 || defined TARGET_solide4
\text{name_solide=cylindre,prisme,autre}
# if defined TARGET_solide1 || defined TARGET_solide3
\text{name_enonce= Choisissez la bonne étiquette pour chacun des solides suivants}
# endif
# if defined TARGET_solide2
\text{name_enonce=Mettre en relation.}
# endif
# if defined TARGET_solide4
\matrix{name_enonce=Pour le solide ci-contre, donner
  le nombre de faces
  le nombre de sommets
  le nombre d'arêtes}
# endif
#endif
#if defined TARGET_solide5 || defined TARGET_solide6
\text{name_figure=triangulaire,rectangulaire,hexagonale,carrée,
  dodécagonale,pentagonale,octogonale}
\text{name_enonce=Pour ce prisme droit, nous avons une base}
#endif
#if defined TARGET_solide10 || defined TARGET_solide11 || defined TARGET_solide12
\matrix{name_enonce=Donner une face parallèle à la face
  Donner une face perpendiculaire à la face
  Donner toutes les faces perpendiculaires à la face}
#endif
#if defined TARGET_solide7 || defined TARGET_solide8 || defined TARGET_solide9
\matrix{name_enonce=Donner un côté, au côté,au côté
  Donner les côtés, au côté, au côté}
# if defined TARGET_solide7 || defined TARGET_solide8
\text{name_prop=parallèle,parallèles}
\text{name_prop2=perpendiculaire,perpendiculaires}
# endif
# if defined TARGET_solide9
\text{name_prop=perpendiculaire,perpendiculaires}
# endif
#endif
