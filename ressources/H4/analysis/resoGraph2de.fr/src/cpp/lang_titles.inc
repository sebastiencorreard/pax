\text{lang=slib(oef/env lang)}
#include "lang_title_fr.inc"

#if defined TARGET_resoGraphEq1 || defined TARGET_resoGraphIn1 || defined TARGET_resoGraphEq2 || defined TARGET_resoGraphIn2 || defined TARGET_resoGraphIn3
# if defined TARGET_resoGraphEq1 || defined TARGET_resoGraphIn1
#   define NUM 1
# endif
# if defined TARGET_resoGraphEq2 || defined TARGET_resoGraphIn2
#   define NUM 2
# endif
# if defined TARGET_resoGraphIn3
#   define NUM 3
# endif
#else
# define NUM
#endif

\title{TITRE NUM}
