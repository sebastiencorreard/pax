\text{intro= Soit une fonction \(f: \RR \to \RR\) continue et dérivable ayant
  le tableau de variation suivant.}
#if defined TARGET_imagerestr || defined TARGET_minmaxrestr
\text{name_non=Aucun}

# if defined TARGET_imagerestr
\text{name_answer=Crochet à gauche,Crochet à droite}
\text{name_question=Quelle est l'image de }
# endif
# if defined TARGET_minmaxrestr
\text{name_question=Remplissez&nbsp;}
# endif

#endif
#if defined TARGET_intnoninj
\text{name_reasons=randitem(\(f_I\) envoie plusieurs valeurs à la même image,
  Certaines valeurs ont plusieurs antécédents),
  Certaines valeurs ont plusieurs images,
  Certaines valeurs ne sont pas dans l'image de \(f_I\),
  \(f_I\) n'est pas définie sur certaines valeurs,
  \(f_I\) est randitem(croissante,décroissante),
  \(f_I\) n'est pas randitem(continue,dérivable)}
\text{name_answer=Début de \(I\) vaut,
  Fin de \(I\) vaut,
  Raison de non-injectivité,
  Valeur ayant plusieurs antécédents}
#endif
#if defined TARGET_intminmax

#endif
#if defined TARGET_intmax

#endif
#if defined TARGET_intmax2

#endif

#if defined TARGET_intminmax

#endif
#if defined TARGETintinj
\text{name_creasing=croissante:décroissante}
\text{name_question1=Utilisez les valeurs proposées ci-dessous pour construire un intervalle
  ouvert \(I\) tel que la restriction de \(f\) sur \(I\) soit injective.}
\text{name_answer=Début de,Fin de}
#endif
#if defined TARGET_image || defined TARGET_minmax || defined TARGET_image3 || defined TARGET_minmax3
\text{non=Aucun}
# if defined TARGET_image || defined TARGET_image3
 \text{name_question=Quelle est l'image de}
# endif
# if defined TARGET_minmax || defined TARGET_minmax3
\text{name_question=Remplissez}
# endif
#endif
#if defined TARGET_antdonne
\text{name_ant=antécédent,antécédents}
\text{name_statement=Trouvez une valeur \(y_0\) de \(f\) ayant exactement}
#endif
#if defined TARGET_ant
\text{name_statement=Combien la valeur, possède-t-elle d'antécédents par}
\text{name_answer=Le nombre d'antécédents de }
#endif
