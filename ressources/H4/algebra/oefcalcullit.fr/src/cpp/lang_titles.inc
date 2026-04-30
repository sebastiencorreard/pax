#if defined TARGET_factorisat1 || defined TARGET_dev2fact1
# define NUM I
#endif
#if defined TARGET_factorisat2 || defined TARGET_dev2fact2
# define NUM II
#endif

#include "lang_title_fr.inc"

#if defined NUM
\title{TITLE NUM}
#else
\title{TITLE}
#endif
