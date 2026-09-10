#if defined TARGET_coord
\text{warning1=Il y a une erreur de signe pour}
\text{warning2=Vous avez confondu l'abscisse et l'ordonnée de}
\text{name_instruction=Donner les coordonnées des points}
\text{name_and=et}
#endif
#if defined TARGET_croissant || defined TARGET_croissant2
\text{name_choix=croissant,décroissant}
\text{instruction=En s'aidant de la règle graduée, ranger dans
  l'ordre, les nombres suivants.}
#endif
#if defined TARGET_itineraire
\text{instruction=On désire aller du point \(\A\) au point \(\B\), en passant par tous les points
  du dessin une fois et de manière que deux points consécutifs aient une coordonnée égale.
  Donner un itinéraire en donnant dans l'ordre la liste des points par lesquels on passe.}
\text{name_question=L'itinéraire est }
\text{name_consigne=On écrira le nom des points séparés par des virgules.}
\text{name_answer=Itinéraire}
#endif
#if defined TARGET_ordre
\text{instruction=En s'aidant de la règle graduée, compléter les expressions par
  les symboles &lt;, &gt; ou = }
#endif
#if defined TARGET_ordrerelatif
\text{instruction=Donner le meilleur encadrement possible de \u en prenant
  les nombres dans la liste suivante}
#endif
#if defined TARGET_placer
\text{instruction=Mettre le point \(A\) en}
#endif
#if defined TARGET_position
\text{liste=droite, gauche}
\text{name_inst=Le point \(B\) est d'abscisse +BBBB ou -BBBB. Or il est à, de \(A\)
  qui est d'abscisse AAAA. Quelle est son abscisse&nbsp;}
\text{name_answer=Son abscisse est}
#endif
#if defined TARGET_position0
\text{liste=droite, gauche}
\text{name_inst=Le point \(A\) est d'abscisse +AAAA ou -AAAA. Or il est à, de 0.
  Quelle est son abscisse&nbsp;}
\text{name_answer=Son abscisse est}
#endif
#if defined TARGET_relatifdist
\text{instruction=En s'aidant de la règle graduée, déterminer la distance entre les
deux points \(A (\A)\) et \(B (\B)\).}
\text{name_answer=Distance entre}
\text{name_and=et}
#endif
#if defined TARGET_relatrule
\text{instruction=Voici la droite graduée. Donner la valeur des points notés
  sur cette droite graduée.}
#endif
#if defined TARGET_rulefrac0
\text{consigne=La flèche pointe sur une graduation.}
#endif
#if defined TARGET_rulefrac
\text{consigne=La flèche pointe sur une graduation ou une demi-graduation.}
#endif
#if defined TARGET_rulefracirr || defined TARGET_rulefracrelirr
\text{consigne=La fraction doit être présentée sous forme irréductible.
  La flèche pointe sur une graduation ou une demi-graduation.}
#endif
#if defined TARGET_rulefracrel
\text{consigne=La flèche pointe sur une graduation ou une demi-graduation.}
#endif
#if defined TARGET_rulefrac0 || defined TARGET_rulefrac || defined TARGET_rulefracirr || defined TARGET_rulefracrel || defined TARGET_rulefracrelirr
\text{instruction=Voici la droite graduée. Le point indiqué par la flèche sur la droite graduée
  a comme abscisse le quotient de deux entiers. Il s'agit de}
\text{name_numden=Numérateur,dénominateur}
\text{name_warning=Vous n'avez pas simplifié la fraction.}
\text{name_solution=Une solution est}
\text{name_consigne=Consigne}
#endif
