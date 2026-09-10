\text{name_empty=vuoto}
\text{name_and=e}
\text{name_statement1=Si considerino gli insiemi}

#if defined TARGET_complementaire || defined TARGET_complementaire_h || defined TARGET_differences || defined TARGET_difference_symetrique || defined TARGET_difference_symetrique_h || defined TARGET_operations_combinees1 || defined TARGET_operations_combinees2 || defined TARGET_produit_cartesien1 || defined TARGET_produit_cartesien3 || defined TARGET_union_et_intersection
\text{name_statement2=Determinare}
#endif
#if defined TARGET_produit_cartesien2
\text{name_statement3=Scrivere questo insieme sotto forma di prodotto cartesiano tra due insiemi.}
#endif
#if defined TARGET_produit_cartesien1
\text{name_instruction=Non inserire spazi nelle coppie di elementi: per esempio scrivere <span class="tt">(a,b)</span> e non <span class="tt">(a, b)</span>. Le diverse coppie devono essere separate da virgole.}
#endif
#if defined TARGET_produit_cartesien3
\text{name_instruction=Non inserire spazi nelle terne di elementi: per esempio scrivere <span class="tt">(a,b,c)</span> e non <span class="tt">(a, b, c)</span>. Le diverse terne devono essere separate da virgole.}
#endif

#if defined TARGET_complementaire || defined TARGET_complementaire_h || defined TARGET_differences || defined TARGET_difference_symetrique || defined TARGET_difference_symetrique_h || defined TARGET_operations_combinees1 || defined TARGET_operations_combinees2 || defined TARGET_union_et_intersection
\text{name_instruction=Se si desidera inserire l'insieme vuoto, scrivere la parola <span class="tt">\name_empty</span> nello spazio designato per la risposta.}
#endif

#if defined TARGET_complementaire_h
\text{name_hint=Con \(\complement_A B\) indichiamo l'insieme complementare a \(B\) con insieme universo \(A\).}
#endif
#if defined TARGET_difference_symetrique_h
\text{name_hint=Con \(A\ \Delta B\) indichiamo l'insieme che si ottiene unendo \(A\setminus B\) e \(B\setminus A\).}
#endif
