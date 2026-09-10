#if defined TARGET_formulas
\text{propsname=formules}
\text{name_statement=Soient \(f) et \(g) deux fonctions dérivables.}
\text{name_ask=ne sont pas correctes,sont correctes}
\text{name_cond=mauvaises,bonnes}
\text{name_answer=Les \cond \propsname sont}
\text{name_question=Parmi les \propsname suivantes,
  lesquelles }
#endif
#if defined TARGET_compvert1b || defined TARGET_compvert1a || defined TARGET_multvert1
\text{name_statement=Soit \(f) une fonction dérivable, de dérivée \(f').
  Calculez la dérivée de la fonction \(g) définie par}
#endif
#if defined TARGET_simple1 || defined TARGET_frac1 || defined TARGET_frac2 || defined TARGET_basic1 || defined TARGET_poly
\text{name_statement=Calculez la dérivée de la fonction \(f) définie par}
#endif

#if defined TARGET_growpos
\text{inc=est croissante}
\text{dec=est décroissante}
\text{sinc=est strictement croissante}
\text{sdec=est strictement décroissante}
\text{pos=a des valeurs positives ou nulles}
\text{neg=a des valeurs négatives ou nulles}
\text{spos=a des valeurs strictement positives}
\text{sneg=a des valeurs strictement négatives}
\text{noth=on ne peut rien dire}
\text{name_statement=Soit \(f) une fonction continue et dérivable
  sur un intervalle [a,b] et \(f') sa dérivée. Remplissez}
\text{name_if=Si}
\text{name_instruction=Il faut choisir la réponse la plus pertinente.}
\text{name_choice=La case à remplir}
#endif
