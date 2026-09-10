\text{name_rappel=Rappel: la fonction partie entière, notée \(E(x)\), est la fonction
  qui à tout \(x \in \RR\) associe l'entier relatif \(z\) tel que:
  <div class="wimscenter"> \(z \leq x < z+1\).</div>}
\text{lstrep=Oui,Non}

#if defined TARGET_trouvecont3
\text{instruct=On attend une valeur exacte.}
\text{name_enonce=Peut-on trouver une valeur de \(k\) telle que la fonction \(f\) définie sur,
  par,soit continue&nbsp;}
\text{name_answer=La valeur de \(k\) est&nbsp;}
#endif
#if defined TARGET_trouvecont4
\text{instruct=On attend des valeurs exactes pour les bornes.}
\text{name_enonce=On considère la fonction \(f\) définie par,
  Déterminer le plus grand intervalle contenant,
  sur lequel la fonction \(f\) est continue.}
\text{name_answer=Borne gauche,Borne droite}
#endif
#if defined TARGET_trouvecont1 || defined TARGET_trouvecont2
\text{name_enonce=Trouver les valeurs de,pour que la fonction définie par&nbsp;,soit continue sur}
\text{name_value=Valeur(s) de}
#endif
#if defined TARGET_trouvecont1 || defined TARGET_trouvecont2 || defined TARGET_trouvecont3
\text{name_ifand=si,et}
#endif
#if defined TARGET_tvidicho || defined TARGET_tviscan
\text{sensvar=croissante, décroissante}
# if defined TARGET_tvidicho
\text{name_feed=la valeur proposée ne convient pas car }
# endif
#endif
#if defined TARGET_racinen1
\text{name_enonce=Comparer les nombres suivants, <strong>sans l'aide d'une calculatrice</strong>&nbsp;}
#endif
#if defined TARGET_racinen2
\text{name_enonce=Soit,Mettre,sous la forme,et calculer}
\text{name_answer=Puissance,Coeff,Puissance dérivée}
#endif
#if defined TARGET_questcont1 || defined TARGET_questcont2 || defined TARGET_questcont3 || defined TARGET_questcont4
\text{name_enonce=On considère la fonction \(f\) définie sur,par&nbsp;,
  La fonction \(f\) est-elle continue&nbsp;}
#endif
#if defined TARGET_contdef1 || defined TARGET_contdef2
\text{name_operation=la somme,le produit,le quotient,la composée}
\text{name_enonce=La fonction, est continue (sur son domaine de définition) parce que c'est&nbsp;,
  des deux fonctions continues}
\text{name_instruction=Cocher la bonne réponse et compléter les expressions de
  \(u\) et \(v\) en déplaçant les bonnes étiquettes.}
#endif
