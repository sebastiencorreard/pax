#if defined TARGET_ineqexpo1 || defined TARGET_ineqexpo2 || defined TARGET_ineqexpo3 || defined TARGET_ineqexpo4 || defined TARGET_ineqexpo5
\text{name_statement=Résoudre dans \(\,\RR ) l'inéquation }
\text{name_answer=Ensemble de solutions}
#endif
#if defined TARGET_sumprod4
\text{name_statement=Compléter&nbsp;,Pour tout réel}
\text{name_answer=Exposant}
#endif
#if defined TARGET_sumprod1 || defined TARGET_sumprod2
\text{name_statement=Mettre en correspondance les différentes écritures d'une même expression&nbsp;}
#endif
#if defined TARGET_sumprod3
\text{name_statement=Parmi les expressions suivantes, cochez celles qui sont, pour tout réel \(x) non nul, égales à}
#endif
#if defined TARGET_sumprod5
\text{name_statement=Compléter}
#endif
#if defined TARGET_eqexpo1
\text{name_tsol=Il n'y a pas de solution, car la fonction exponentielle
  prend des valeurs strictement positives sur \(\,\RR).}
#endif
#if defined TARGET_eqexpo1 || defined TARGET_eqexpo2 || defined TARGET_eqexpo3 || defined TARGET_eqexpo4 || defined TARGET_eqexpo5 || defined TARGET_eqexpo6
\text{name_statement=Résoudre dans \(\,\RR\) l'équation}
\text{name_instruction=Pour écrire votre réponse,
  <ul><li>écrire <span class="tt">vide</span> s'il n'y a pas de solution.
  </li><li>s'il y a plusieurs solutions, les séparer par une virgule.
  </li></ul>
}
\text{name_answer=Ensemble de solutions}
#endif
#if defined TARGET_eqexpo4 || defined TARGET_eqexpo3
\matrix{name_tsol=Le dénominateur à gauche ne s'annule pas, l'équation est donc équivalente à
  Après simplification, on obtient l'équation
  qui est équivalente à}
\text{name_answer=Ensemble de solutions}
#endif
#if defined TARGET_eqexpo2
\text{name_tsol=On utilise l'équivalence}
#endif
