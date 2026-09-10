#include "lang_title_fr.inc"
#if defined TARGET_assocfct || defined TARGET_extremum1
# define NUM 1
#endif
#if defined TARGET_assocfct2 || defined TARGET_extremum2
# define NUM 2
#endif
#if defined TARGET_assocfct3
# define NUM 3
#endif
#ifndef NUM
# define NUM
#endif
\title{TITRE NUM}
