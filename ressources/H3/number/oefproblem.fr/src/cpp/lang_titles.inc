#include "lang_title_fr.inc"
#if defined TARGET_groupe1 || defined TARGET_groupe2
# if defined TARGET_groupe1
#   define NUM I
# endif
# if defined TARGET_groupe2
#   define NUM II
# endif
\title{TITRE NUM}
#else
\title{TITRE OEFFILE}
#endif
