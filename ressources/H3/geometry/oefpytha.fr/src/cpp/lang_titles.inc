\text{lang=slib(oef/env lang)}
#include "lang_title_fr.inc"
#include "lang_title_it.inc"
#include "lang_title_nl.inc"
#if defined TARGET_etagere1 || defined TARGET_horizon1
# define NUM 1
#endif
#if defined TARGET_etagere2 || defined TARGET_horizon2
# define NUM 2
#endif
#if defined TARGET_moho0
# define NUM A
#endif
#if defined TARGET_moho1
# define NUM B
#endif
#if defined TARGET_horizon3
# define NUM 3
#endif
#if !defined NUM
# define NUM
#endif
\title{TITRE NUM}
\title_it{TITRE_it NUM}
\title_nl{TITRE_nl NUM}
