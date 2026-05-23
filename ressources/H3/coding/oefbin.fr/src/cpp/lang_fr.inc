#if defined TARGET_binary || defined TARGET_binary2 || defined TARGET_binary3
\text{name_puissance=Puissances de }
#endif
#if defined TARGET_binary || defined TARGET_binary3
\text{name_enonce=Écrire le nombre,en binaire.}
\text{name_feed=L'écriture de,en binaire est}
#endif
#if defined TARGET_binary2 || defined TARGET_binary4
\text{name_enonce=La décomposition en binaire de l'entier, est}
#endif
#if defined TARGET_binary2
\text{name_question=Remplir les cases.}
#endif
#if defined TARGET_binary3
\text{name_feed2=L'entier, est, pair,impair,
  or le nombre en binaire que vous donnez se termine par un,
  ce n'est vraiment pas possible.}
#endif
#if defined TARGET_binary4
\text{name_question=Donner toutes les possibilités pour l'entier,
  écrit en notation décimale}
#endif
#if defined TARGET_calcbase
\text{name_enonce=Écrivons les entiers en base,
  Un entier \(n\) s'écrit,
  Comment s'écrit}
#endif
#if defined TARGET_dessin
\text{name_question=Codez le dessin suivant}
\text{name_inst=Chaque ligne lue de gauche à droite correspond à 8 bits,
  on lit les lignes de haut en bas,
  vous devez donc rentrer 8 nombres de 8 bits, séparés par des virgules.}
\text{name_answer=Codage du dessin}
#endif
#if defined TARGET_texte
\text{name_question=Quel est le mot codé en binaire dans ce dessin,
  il y a une lettre par ligne ; on doit donc lire le mot verticalement}
\text{name_help=Chaque lettre a un code appelé code ASCII qui est
  un nombre décimal compris entre 0 et 256. On écrit ensuite ce nombre en
  binaire et on le représente par une case noire pour 1 et une case blanche
  pour un 0. Pour les lettres majuscules qui sont utilisées ici,
  les codes sont donnés par le tableau suivant
}
#endif
