#if defined TARGET_simplify1
\text{name_enonce=Simplifier l'expression suivante sous forme d'un entier relatif.}
#endif
#if defined TARGET_signeexp1
\text{name_enonce=Étudier en fonction de \(x\) le signe de l'expression }
\matrix{name_hint=Commencer, si besoin, par mettre en facteur
Se souvenir qu'une exponentielle est toujours strictement positive.
On est alors ramené à l'étude du signe d'une expression de la forme}
#endif
#if defined TARGET_signeexp2
\text{liste =ne peut pas être déterminé sans calcul supplémentaire,est toujours le signe +,est toujours le signe -}
#endif
#if defined TARGET_signeexp2 || defined TARGET_ineqexp1 || defined TARGET_ineqexp2
\text{name_posneg=positif,négatif,nul}
#endif
#if defined TARGET_ln1 || defined TARGET_ln2
\text{name_enonce0=On donne, où ln désigne la fonction logarithme népérien.}
#endif
#if defined TARGET_ln1
\matrix{name_enonce=Réécrire \(A\) sous la forme ln(\(p\)), où \(p\) est un nombre rationnel.
  Réécrire \(A\) sous la forme \(n ln(\a) + m ln(\b)\) où \(n\) et \(m\) sont des entiers relatifs.}
#endif
#if defined TARGET_ln2
\matrix{name_enonce= Réécrire \(A\) comme le logarithme d'un produit
  Réécrire \(A\) comme une somme de logarithmes}
#endif
