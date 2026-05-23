\text{lang=slib(oef/env lang)}

#include "lang_title_fr.inc"

#if defined TARGET_parallel1 || defined TARGET_longueur1 || defined TARGET_patron1 || defined TARGET_formulevolume1 || defined TARGET_formuleaire1 || defined TARGET_volume1 || defined TARGET_perpendiculaire1 || defined TARGET_airelaterale1
# define NUM 1
#endif
#if defined TARGET_parallel2 || defined TARGET_longueur2 || defined TARGET_patron2 || defined TARGET_formulevolume2 || defined TARGET_formuleaire2 || defined TARGET_volume2 || defined TARGET_perpendiculaire2 || defined TARGET_airelaterale2
# define NUM 2
#endif
#if defined TARGET_parallel3 || defined TARGET_longueur3 || defined TARGET_patron3 || defined TARGET_formulevolume3 || defined TARGET_formuleaire3 || defined TARGET_volume3 || defined TARGET_perpendiculaire3 || defined TARGET_airelaterale3
# define NUM 3
#endif
#if defined TARGET_parallel4 || defined TARGET_longueur4 || defined TARGET_patron4 || defined TARGET_formulevolume4 || defined TARGET_formuleaire4 || defined TARGET_volume4 || defined TARGET_perpendiculaire4 || defined TARGET_airelaterale4
# define NUM 4
#endif
#if defined TARGET_parallel5 || defined TARGET_longueur5 || defined TARGET_patron5 || defined TARGET_formulevolume5 || defined TARGET_formuleaire5 || defined TARGET_volume5 || defined TARGET_perpendiculaire5 || defined TARGET_airelaterale5
# define NUM 5
#endif

\title{TITRE NUM}
