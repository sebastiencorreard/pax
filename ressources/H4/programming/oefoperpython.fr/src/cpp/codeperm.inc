\text{Affprint=print(a)
print(b)}
\text{consignepl=}
#if defined TARGET_perm3 || defined TARGET_perm4
\text{Affprint=\Affprint
print(c)}
#endif
#if defined TARGET_perm4
\text{Affprint=\Affprint
print(d)}
#endif
#if defined TARGET_permlist
\text{Affprint=print(liste)}
\text{consignepl=Le dernier bouton permet l'indentation du texte si nécessaire.}
#endif
\text{code=
\#Initialisation des variables#
\###
\###
\###
\###
\#Permutation des variables#
\###
\###
\###
\###
\###
\#Fin de la permutation des variables#
\#Affichage du résultat#
\Affprint
\#Fin Affichage#}
