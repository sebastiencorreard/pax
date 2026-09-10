#include "lang_title_fr.inc"

#if defined TARGET_chgtva1 || defined TARGET_sommedouble || defined TARGET_sumg || defined TARGET_sommation
# define NUM 1
#endif
#if defined TARGET_chgtva2 || defined TARGET_sommedouble2 || defined TARGET_suml || defined TARGET_sommation2
# define NUM 2
#endif
#if defined NUM

#else
# define NUM
#endif

\title{TITRE NUM}
