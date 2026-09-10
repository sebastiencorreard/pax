\text{lang=slib(oef/env lang)}
#include "lang_title_fr.inc"
#include "lang_title_nl.inc"
#if defined TARGET_angle1 || defined TARGET_oeftrouvangltriang1
# define NUM 1
#endif
#if defined TARGET_angle2 || defined TARGET_oeftrouvangltriang2
# define NUM 2
#endif
#if defined TARGET_angle3
# define NUM 3
#endif
#if defined TARGET_oefmesangltriang || defined TARGET_vocangle1
# define NUM
#endif
\title{TITRE NUM}
\title_nl{TITRE_nl NUM}
