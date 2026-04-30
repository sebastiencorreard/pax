#include "lang_title_fr.inc"

#if defined TARGET_sontelles1 || defined TARGET_sontelles3 || defined TARGET_sontelles5 || defined TARGET_lectequ1 || defined TARGET_lectequ2
# define NUM 1
#endif
#if defined TARGET_sontelles2 || defined TARGET_sontelles4 || defined TARGET_sontelles6 || defined TARGET_lectequ3 || defined TARGET_lectequ4
# define NUM 2
#endif
#if defined TARGET_lectequ5 || defined TARGET_lectequ6
# define NUM 3
#endif
#if defined TARGET_equcond1 || defined TARGET_equcond2 || defined TARGET_point1
# define NUM 1A
#endif
#if defined TARGET_equcond21 || defined TARGET_equcond22 || defined TARGET_point3
# define NUM 2A
#endif
#if defined TARGET_equcondbc1 || defined TARGET_equcondbc3 || defined TARGET_point2
# define NUM 1B
#endif
#if defined TARGET_equcondbc21 || defined TARGET_equcondbc23 || defined TARGET_point4
# define NUM 2B
#endif
#if defined TARGET_equcondbc2 || defined TARGET_equcondbc4
# define NUM 1C
#endif
#if defined TARGET_equcondbc22 || defined TARGET_equcondbc24
# define NUM 2C
#endif
#if defined TARGET_mkequation
# define NUM
#endif

\title{TITRE NUM}
