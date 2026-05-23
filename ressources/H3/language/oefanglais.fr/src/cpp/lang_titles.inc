\text{lang=slib(oef/env lang)}

#include "lang_title_fr.inc"
#include "lang_title_nl.inc"
#if defined TARGET_Verbesirrgulie2
# define NUM I-1
#endif
#if defined TARGET_Verbesirrgulie
# define NUM I-2
#endif
#if defined TARGET_Verbesirrgulie3
# define NUM II-2
#endif
#if defined TARGET_Verbesirrgulie4
# define NUM II-1
#endif
#if defined NUM
\title{TITRE NUM}
\title_nl{TITRE_nl NUM}
#else
\title{TITRE}
\title_nl{TITRE_nl}
#endif
