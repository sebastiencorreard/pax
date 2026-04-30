\text{name_answer=Votre réponse&nbsp;}
#if defined TARGET_resolva1 || defined TARGET_equava ||  defined TARGET_deducencad2
\text{name_or=ou}
#endif
#if defined TARGET_corrdistva || defined TARGET_distva
\text{name_enonce= Soit \(\mathrm{M}\) le point d'abscisse \(x\)
  sur la droite graduée d'origine}
# if defined TARGET_corrdistva
\text{name_question=Associer les valeurs absolues aux distances
  auxquelles elles correspondent.}
# endif
# if defined TARGET_distva
\text{name_question=Donner l'expression de la distance de \(\mathrm{M}\)
  à \(\mathrm{B}\) puis de \(\mathrm{C}\) à <span class="nowrap">\(\mathrm{M}\),</span>
  à l'aide d'une valeur absolue.}
\text{name_answer2=Vous avez répondu&nbsp;}
# endif
#endif
#if defined TARGET_deducencad1 || defined TARGET_deducencad2
\text{name_question=Si \(x\) vérifie l'inégalité ,
  que pouvez-vous dire précisément de l'expression}
#endif
#if defined TARGET_deducencad1
\text{name_expliqb1=On peut multiplier par un même réel strictement positif,
  On peut multiplier par un même réel strictement négatif}
\text{name_expliqb2=les trois membres d'un encadrement,
  les trois membres d'un encadrement <span style="color:red"> en
    changeant les symboles de l'encadrement</span>}
#endif
#if defined TARGET_encadinter
\text{name_question=Lorsque \(x\) vérifie,
      à quel intervalle appartient-il&nbsp;}
\text{name_typeeq=l'encadrement}
#endif
#if defined TARGET_equava
\text{name_question=Résoudre&nbsp;}
\text{name_instruction=Indiquer en premier la plus petite des deux solutions.}
\text{name_hint=Résoudre cette équation à valeurs
  absolues revient à résoudre deux équations du premier degré.}

#endif
#if defined TARGET_intuninter
\text{name_question=Simplifier si possible&nbsp;}
\text{name_instruction=S'il n'y a pas de simplification possible, réécrivez en ordonnant
  les intervalles dans l'ordre croissant.}
#endif

#if defined TARGET_repgraphint
\text{name_question=Indiquer l'intervalle ou la réunion d'intervalles
  \(J\) représenté(e) en rouge (et en gras).}
#endif
#if defined TARGET_repgraphint || defined TARGET_vabsinter
\text{name_instruction=S'il s'agit d'une réunion d'intervalles,
  indiquez en premier l'intervalle ayant les plus petites bornes.}
#endif
#if defined TARGET_resolva1 || defined TARGET_resolva2
\text{name_question=Résoudre&nbsp;}
#endif
#if defined TARGET_resolva1
\text{name_instruction=Indiquer en premier la plus petite des deux solutions.}
#endif
#if defined TARGET_resolva2
\text{name_hint= représente la distance de \(x\) à \(a\).}
#endif
#if defined TARGET_transfencad1 || defined TARGET_transfineg1
\text{name_question=Si \(x\) vérifie l'inégalité,
  que pouvez-vous dire de l'expression }
#endif
#if defined TARGET_transfencad1 || defined TARGET_transfineg1
\text{name_expliq1=positif,négatif}
# if defined TARGET_transfencad1
\text{name_expliq2=on conserve le sens de l'encadrement,
  on inverse le sens de l'encadrement}
# endif
# if defined TARGET_transfineg1
\text{name_expliq2=on conserve le sens de l'inégalité, on inverse le sens de l'inégalité}
# endif
#endif
#if defined TARGET_vabsinter
\text{name_question=Traduire&nbsp;,
  par l'appartenance de \(x\) à un intervalle ou à une réunion d'intervalles
    aussi grands que possible.}
#endif
#if defined TARGET_vacalcul
\text{name_question=Simplifier la valeur absolue suivante}
#endif
