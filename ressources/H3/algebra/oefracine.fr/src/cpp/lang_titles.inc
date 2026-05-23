#include "lang_title_fr.inc"

#if defined TARGET_corres3 || defined TARGET_liaison3 || defined TARGET_reduitsom3
# define NUM 3
#endif
#if defined TARGET_reduitsom2
# define NUM 2
#endif
#if defined TARGET_liaison4 || defined TARGET_corres4 || defined TARGET_reduitsom4
# define NUM 4
#endif
#if defined TARGET_liaison5 || defined TARGET_corres5
# define NUM 5
#endif
#if defined TARGET_entier || defined TARGET_rationnel || defined TARGET_decimal || defined TARGET_puissance1 || defined TARGET_puissance2
# define NUM
#endif
\title{TITRE NUM}

