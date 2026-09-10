#if defined TARGET_ppower11 || defined TARGET_ppower12 || defined TARGET_ppower13 || defined TARGET_ppower01 || defined TARGET_ppower02
\text{name_statement=Calculer sans calculatrice}
#endif
#if defined TARGET_powerneg
\matrix{name_statement=Le nombre,est
  Écris-le sous forme de produits de puissances}
\text{name_choix=positif, négatif}
\matrix{name_feed=Avez-vous bien regardé si,l'exposant,les exposants
du nombre négatif,est pair ou impair
des nombres négatifs,sont pairs ou impairs
Le signe de cet exposant n'a,Les signes de ces exposants n'ont,par contre pas d'importance.
Le produit de nombres positifs, les puissances de nombres positifs sont toujours positifs.}
#endif
#if defined TARGET_defecritscien
\text{name_statement=Donner l'écriture scientifique du nombre}
#endif
#if defined TARGET_defpuisdix
\text{name_statement=Déterminer la valeur du nombre }
\text{name_instruction=On écrira la réponse sous la forme d'un nombre entier ou décimal.}
#endif
#if defined TARGET_defpuisnb
\text{name_statement=Déterminer la valeur du nombre}
#endif
#if defined TARGET_defpuisnb2
\text{name_statement=Déterminer la valeur du nombre}
\text{name_instruction=Donner le résultat sous la forme d'un entier ou d'une fraction irréductible.}
#endif
#if defined TARGET_encadr
\text{name_statement=Donner un encadrement du nombre,par des puissances de 10 consécutives.}
\text{name_answer1=Exposant inférieur}
\text{name_answer2=Exposant supérieur}
\text{name_hint=Vous pouvez d'abord écrire le nombre en utilisant la notation scientifique.}
#endif
#if defined TARGET_operation1 || defined TARGET_operation2
\text{name_statement=Compléter l'égalité afin qu'elle soit vérifiée&nbsp;}
\text{name_instruction=Donner le résultat sous la forme}
#endif
#if defined TARGET_ordregrandeur
\text{name_statement=Déterminer un ordre de grandeur du nombre }
\text{name_instruction=Si besoin est, l'exposant de la puissance de 10 peut être zéro.}
#endif
#if defined TARGET_tabpuis
\text{name_statement=Compléter le tableau&nbsp;}
\text{name_feed=Attention. On a toujours}
#endif
#if defined TARGET_tabpuis2
\text{name_statement=Compléter le tableau&nbsp;}
\text{name_feed=Attention. en général \(a^m*a^n\) est différent de \(a^{m n}\).}
\text{name_warning=Attention.}
#endif
#if defined TARGET_decimal
\matrix{name_statement=Écrire le nombre, de deux manières
  en notation scientifique
  sous la forme,avec \(a\) un entier non multiple de 10}
\text{name_answer=notation scientifique,exposant,\(a\), exposant}
#endif
#if defined TARGET_power
\text{name_statement1=Écrire}
\text{name_statement2=sous la forme d'une puissance
  d'un entier (avec la plus grande puissance possible)}
\text{name_hint=Simplifiez d'abord la fraction.}
\text{name_feedback1=Avez-vous bien appliqué la règle&nbsp;}
\text{name_feedback2=Il ne faut pas confondre}
\text{name_and=et}
#endif
#if defined TARGET_power10
\text{name_statement=Écrire le nombre suivant sous la forme}
\text{name_answer=exposant}
#endif