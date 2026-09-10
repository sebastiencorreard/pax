#if defined TARGET_1
#define TITRE Dessiner un diagramme en boîte
#endif
#if defined TARGET_2
#define TITRE Dessiner un diagramme à moustache
#endif
#if defined TARGET_3
#define TITRE Lire un diagramme en boîte
#endif
#if defined TARGET_4
#define TITRE Lire un diagramme à moustache
#endif

\text{entete=Premier Décile,Premier Quartile,Médiane,Troisième Quartile,Neuvième Décile}

#if defined TARGET_1 || defined TARGET_2
\text{name_instruction1=On considère une série statistique dont on connait les indicateurs suivants.}
\text{name_instruction2=A l'aide de la souris, déplacer les points sur le graphique pour dessiner le
  diagramme correspondant à la série.}
#endif

#if defined TARGET_3 || defined TARGET_4
\text{name_instruction2=Par lecture graphique, déterminer les indicateurs de cette série.}
# if defined TARGET_3
\text{name_instruction1=On considère une série statistique dont voici le diagramme à moustaches.}
# else
\text{name_instruction1=On considère une série statistique dont voici le diagramme en boîte.}
# endif
#endif
