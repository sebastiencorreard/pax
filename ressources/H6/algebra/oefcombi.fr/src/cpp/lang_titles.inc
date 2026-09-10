\text{lang=slib(oef/env lang)}
#include "lang_title_fr.inc"
#include "lang_title_en.inc"
#include "lang_title_nl.inc"
#if defined TARGET_monom3 || defined TARGET_intersection || defined TARGET_n || defined TARGET_Ordinat1 || defined TARGET_tablediner1
# define NUM 1
#endif
#if defined TARGET_monom4 || defined TARGET_intersection2 || defined TARGET_nn || defined TARGET_Ordinat2 || defined TARGET_tablediner2
# define NUM 2
#endif
#if defined TARGET_intersection3 || defined TARGET_tablediner3
# define NUM 3
#endif
#if defined TARGET_tablediner4
# define NUM 4
#endif
#if defined NUM
\title{TITRE NUM}
\title_en{TITRE_en NUM}
\title_nl{TITRE_nl NUM}
#else
\title{TITRE}
\title_en{TITRE_en}
\title_nl{TITRE_nl}
#endif
