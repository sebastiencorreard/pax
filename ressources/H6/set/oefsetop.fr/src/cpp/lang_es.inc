\text{name_empty=vacío}
\text{name_and=y}
\text{name_statement1=Considere los conjuntos}

#if defined TARGET_complementaire || defined TARGET_complementaire_h || defined TARGET_differences || defined TARGET_difference_symetrique || defined TARGET_difference_symetrique_h || defined TARGET_operations_combinees1 || defined TARGET_operations_combinees2 || defined TARGET_produit_cartesien1 || defined TARGET_produit_cartesien3 || defined TARGET_union_et_intersection
\text{name_statement2=Determine}
#endif
#if defined TARGET_produit_cartesien2
\text{name_statement1=Considere el conjunto}
\text{name_statement3=Escriba este conjunto como el producto cartesiano de dos conjuntos.}
#endif
#if defined TARGET_produit_cartesien1
\text{name_instruction=Al ingresar su respuesta, no inserte espacios en pares
de elementos: por ejemplo, escriba <span class="tt">(a,b)</span> y no <span
class="tt">(a, b)</span>}
#endif
#if defined TARGET_produit_cartesien3
\text{name_instruction=Al ingresar su respuesta, no inserte espacios en una
tupla de elementos: por ejemplo, escriba <span class="tt">(a,b,c)</span> y no
<span class="tt">(a, b, c)</span>}
#endif

#if defined TARGET_complementaire || defined TARGET_complementaire_h || defined TARGET_differences || defined TARGET_difference_symetrique || defined TARGET_difference_symetrique_h || defined TARGET_operations_combinees1 || defined TARGET_operations_combinees2 || defined TARGET_union_et_intersection
\text{name_instruction=Para denotar el conjunto vacío, escriba la palabra <span class="tt">\name_empty</span> en el campo de respuesta.}
#endif

#if defined TARGET_complementaire_h
\text{name_hint=Con \(\complement_A B\) denotamos el complemento de \(B\) relativo al conjunto universo \(A\).}
#endif
#if defined TARGET_difference_symetrique_h
\text{name_hint=Con \(A\ \Delta B\) denotamos la diferencia simétrica de los conjuntos \(A\) y \(B\), es decir la unión de \(A\setminus B\) y \(B\setminus A\).}
#endif
