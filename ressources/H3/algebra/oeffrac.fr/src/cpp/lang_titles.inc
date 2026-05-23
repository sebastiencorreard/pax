\text{lang=slib(oef/env lang)}
#include "lang_title_fr.inc"
#if defined TARGET_adpoA || defined TARGET_sopoA || defined TARGET_mupoA || defined TARGET_dipoA
# define NUM A
#endif
#if defined TARGET_adpoB || defined TARGET_sopoB || defined TARGET_mupoB || defined TARGET_dipoB
# define NUM B
#endif
#if defined TARGET_adpoC || defined TARGET_sopoC || defined TARGET_mupoC || defined TARGET_dipoC
# define NUM C
#endif
#if defined TARGET_adpoD || defined TARGET_sopoD || defined TARGET_mupoD || defined TARGET_dipoD
# define NUM D
#endif
#if defined NUM
\title{TITRE NUM}
#else
\title{TITRE}
#endif
