\text{name_empty=vide}
\text{name_and=et}
\text{name_statement1=On considère les ensembles}

#if defined TARGET_complementaire || defined TARGET_complementaire_h || defined TARGET_differences || defined TARGET_difference_symetrique || defined TARGET_difference_symetrique_h || defined TARGET_operations_combinees1 || defined TARGET_operations_combinees2 || defined TARGET_produit_cartesien1 || defined TARGET_produit_cartesien3 || defined TARGET_union_et_intersection
\text{name_statement2=Déterminer}
#endif
#if defined TARGET_produit_cartesien2
\text{name_statement3=Écrire cet ensemble sous la forme d'un produit cartésien de deux ensembles.}
#endif
#if defined TARGET_produit_cartesien1
\text{name_instruction=Écrire les couples sous la forme <span class="tt">(a,b)</span> sans utiliser d'espace. Les couples doivent également être séparés par des virgules.}
#endif
#if defined TARGET_produit_cartesien3
\text{name_instruction=Écrire les triplés sous la forme <span class="tt">(a,b,c)</span> sans utiliser d'espace. Les triplés doivent également être séparés par des virgules.}
#endif

#if defined TARGET_complementaire || defined TARGET_complementaire_h || defined TARGET_differences || defined TARGET_difference_symetrique || defined TARGET_difference_symetrique_h || defined TARGET_operations_combinees1 || defined TARGET_operations_combinees2 || defined TARGET_union_et_intersection
\text{name_instruction=Pour désigner l'ensemble vide, écrire le mot <span class="tt">\name_empty</span> dans le champ de réponse.}
#endif

#if defined TARGET_complementaire_h
\text{name_hint=La notation \(\complement_A B\) désigne l'ensemble complémentaire de \(B\) dans \(A\).}
#endif
#if defined TARGET_difference_symetrique_h
\text{name_hint=La notation \(A \Delta B \) désigne la différence symétrique des ensembles \(A\) et \(B\), c'est-à-dire la réunion de \(A \setminus B\) et \(B \setminus A\).}
#endif
