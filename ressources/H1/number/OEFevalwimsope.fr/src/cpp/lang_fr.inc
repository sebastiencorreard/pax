#if defined TARGET_division
\text{name_enonce=Effectuer la division posée suivante&nbsp;}
\text{name_warning=Vous devez remplir toutes les étiquettes avec des chiffres.}
#endif
#if defined TARGET_multipli || defined TARGET_oefmultiplication5 || defined TARGET_oefmultiplication1 || defined TARGET_oefmultiplication2 || defined TARGET_oefmultiplication3 || defined TARGET_oefmultiplication4
\text{name_enonce=Effectuer la multiplication posée suivante&nbsp;}
\text{name_warning=Vous devez remplir toutes les étiquettes avec des chiffres.}
#endif
#if defined TARGET_oefaddition1 || defined TARGET_oefaddition2 || defined TARGET_oefaddition3 || defined TARGET_oefaddition4 || defined TARGET_oefaddition5
\text{name_enonce=Effectuer l'addition posée suivante&nbsp;}
\text{name_warning=Vous devez remplir toutes les étiquettes avec des chiffres.}
#endif
#if defined TARGET_oefmachop1 || defined TARGET_oefmachop2 || defined TARGET_oefmachop3 || defined TARGET_oefmachop4 || defined TARGET_oefmachop5
\text{name_enonce=Trouver le résultat avec la calculatrice&nbsp;}
\text{name_warning=Attention : il faut respecter l'espace tous les trois chiffres
  et utiliser la virgule comme séparateur décimal.}
#endif
#if defined TARGET_oefmentaladd1 || defined TARGET_oefmentaladd2 || defined TARGET_oefmentaladd3 || defined TARGET_oefmentaladd4 || defined TARGET_oefmentaladd5
\text{name_enonce=Donnez le résultat de l'addition&nbsp;}
#endif
#if defined TARGET_oefmentalsoust1 || defined TARGET_oefmentalsoust2 || defined TARGET_oefmentalsoust3 || defined TARGET_oefmentalsoust4 || defined TARGET_oefmentalsoust5
\text{name_enonce=Donnez le résultat de la soustraction&nbsp;}
#endif
#if defined TARGET_oefposer1 || defined TARGET_oefposer2 || defined TARGET_oefposer3 || defined TARGET_oefposer4 || defined TARGET_oefposer5
\text{name_enonce=Nous avons l'opération suivante&nbsp;,Poser l'opération}
# if defined TARGET_oefposer1
\text{name_warning=Vous devez remplir toutes les étiquettes avec des chiffres.}
# endif
# if defined TARGET_oefposer2 || defined TARGET_oefposer4 || defined TARGET_oefposer3 || defined TARGET_oefposer5
\text{name_warning=Vous devez remplir toutes les étiquettes avec des chiffres ou la virgule.}
# endif
\text{name_warning=\sg issametext +?\name_warning
  Vous placerez le premier nombre sur la première ligne et le deuxième sur la deuxième ligne.}
#endif
#if defined TARGET_oefsoustract1 || defined TARGET_oefsoustract2 || defined TARGET_oefsoustract3 || defined TARGET_oefsoustract4 || defined TARGET_oefsoustract5
\text{name_enonce=Effectuer la soustraction posée suivante&nbsp;}
\text{name_warning=Vous devez remplir toutes les étiquettes avec des chiffres.}
#endif
#if defined TARGET_oeftable1 || defined TARGET_oeftable2 || defined TARGET_oeftable3 || defined TARGET_oeftable4 || defined TARGET_oeftable5
\text{name_enonce=Compléter la table&nbsp;}
# if defined TARGET_oeftable1 || defined TARGET_oeftable2
\text{enonc=d'addition,+}
# else
\text{enonc=de multiplication,X}
# endif
#endif
#if defined TARGET_oefmult011 || defined TARGET_oefmult012 || defined TARGET_oefmult013 || defined TARGET_oefmult014 || defined TARGET_oefmult015 || defined TARGET_oefmult101 || defined TARGET_oefmult102 || defined TARGET_oefmult103 || defined TARGET_oefmult104 || defined TARGET_oefmult105
\text{name_enonce=Donnez le résultat de la multiplication&nbsp;}
#endif
#if defined TARGET_table
\text{name_enonce=Compléter la table de multiplication&nbsp;}
#endif
#if defined TARGET_oefgrandeurprod1 || defined TARGET_oefgrandeurprod2 || defined TARGET_oefgrandeurprod3 || defined TARGET_oefgrandeurprod4 || defined TARGET_oefgrandeurprod5
\text{name_enonce=Trouver l'ordre de grandeur des nombres&nbsp;}
\text{name_enonce2=Ordre de grandeur,Donc l'ordre de grandeur du résultat est}
# if defined TARGET_oefgrandeurprod1 || defined TARGET_oefgrandeurprod2 || defined TARGET_oefgrandeurprod3
\text{name_warning=Vous utiliserez les étiquettes.}
# endif
# if defined TARGET_oefgrandeurprod3
\text{name_warning=Vous respecterez l'espace tous les trois chiffres.}
# endif
# if defined TARGET_oefgrandeurprod4 || defined TARGET_oefgrandeurprod5
\text{name_warning=Vous utiliserez la virgule comme séparateur décimal,
  respecterez l'espace tous les trois chiffres et éviterez les zéros inutiles.}
# endif
# if defined TARGET_oefgrandeurprod5
text{name_warning=Vous utiliserez un seul chiffre différent de zéro.}
# endif
#endif
#if defined TARGET_oefgrandeurdiff1 || defined TARGET_oefgrandeurdiff2 || defined TARGET_oefgrandeurdiff3 || defined TARGET_oefgrandeurdiff4 || defined TARGET_oefgrandeurdiff5
\text{name_enonce=Trouver l'ordre de grandeur du résultat&nbsp;}
\text{name_enonce2=Ordre de grandeur,Donc l'ordre de grandeur du résultat est}
\text{name_warning=Vous utiliserez les étiquettes.}
#endif
#if defined TARGET_oefgrandeuradd1 || defined TARGET_oefgrandeuradd2 || defined TARGET_oefgrandeuradd3 || defined TARGET_oefgrandeuradd4 || defined TARGET_oefgrandeuradd5
\text{name_enonce=Trouver l'ordre de grandeur du résultat&nbsp;}
\text{name_enonce2=Ordre de grandeur,Donc l'ordre de grandeur du résultat est}
\text{name_warning=Vous utiliserez les étiquettes.}
#endif
#if defined TARGET_decomp
\text{name_enonce=Pour chaque nombre, trouver une multiplication.}
\text{name_warning=Chaque facteur doit être strictement inférieur à 10.}
#endif
#if defined TARGET_oefvocaboper1
\text{quest= le produit, la somme, la différence}
\text{rep=\res1,\res2,\res3}
\text{deb=Le nombre}
\text{fin= est \quest[\a] des nombres \nb1 et \nb2.}
#endif
#if defined TARGET_oefvocaboper2
\text{rep= Le produit, La somme, La différence}
\text{deb=Le nombre \quest[\a] est }
\text{fin= des nombres \nb1 et \nb2.}
#endif
#if defined TARGET_oefvocaboper3
\text{quest1= facteur, terme, terme}
\text{quest2= du produit,de la somme,de la différence}
\text{quest3=deuxième,premier}
\text{deb=Le nombre }
\text{fin=est le \quest3[\c] \quest1[\b] \quest2[\b] qui donne \res.}
#endif
#if defined TARGET_oefvocaboper4
\text{quest1= facteur, terme, terme}
\text{quest2= du produit,de la somme,de la différence}
\text{quest3=deuxième,premier}
\text{rep=facteur,facteur,terme,terme,terme,terme}
\text{deb=Le nombre \nb[\a] est le \quest3[\c]}
\text{fin=\quest2[\b] qui donne \res.}
#endif
#if defined TARGET_oefvocaboper5
\text{rep=un facteur,un facteur,un terme,un terme,un terme,un terme,un produit,une somme,une différence}
\text{deb=Le nombre \nb[\a] est }
\text{fin=.}
#endif
