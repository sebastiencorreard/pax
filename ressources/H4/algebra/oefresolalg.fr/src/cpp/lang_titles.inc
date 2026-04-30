#include "lang_title_fr.inc"

#if defined TARGET_factor1 || defined TARGET_devel1
# define NUM 1
#endif
#if defined TARGET_factor2 || defined TARGET_devel2
# define NUM 2
#endif
#if defined TARGET_factor3 || defined TARGET_devel3
# define NUM 3
#endif
#if defined TARGET_factor4
# define NUM 4
#endif
#if defined TARGET_factor5
# define NUM 5
#endif
#if defined NUM
\title{TITRE NUM}
#else
\title{TITRE}
#endif
