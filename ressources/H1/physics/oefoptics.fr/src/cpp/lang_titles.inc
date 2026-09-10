#include "lang_title_fr.inc"
#if defined TARGET_qcm1 || defined TARGET_ecran1 || defined TARGET_ombre1 || defined TARGET_date1
# define NUM 1
#endif
#if defined TARGET_qcm2 || defined TARGET_ecran2 || defined TARGET_ombre2 || defined TARGET_date2
# define NUM 2
#endif
#if defined TARGET_ecran3
# define NUM 3
#endif
#if defined TARGET_ecran4
# define NUM 4
#endif
#if defined TARGET_ordphase1
# define NUM (Nord)
#endif
#if defined TARGET_ordphase1P
# define NUM Nord (P)
#endif
#if defined TARGET_ordphase2
# define NUM Sud
#endif
#if defined TARGET_trajet1 || defined TARGET_tabouret || defined TARGET_poslune || defined TARGET_eclipse1 || defined TARGET_eclipse2
# define NUM
#endif
#if defined TARGET_date1P || defined TARGET_phase1P
# define NUM 1 (P)
#endif
#if defined TARGET_date2P || defined TARGET_phase2P
# define NUM 2 (P)
#endif
#if defined TARGET_ordphase1
# define NUM Nord
#endif
#if defined TARGET_ordphase1P
# define NUM Nord (P)
#endif
#if defined TARGET_date1T || defined TARGET_phase1T
# define NUM 1 (B)
#endif
#if defined TARGET_date2T || defined TARGET_phase2T
# define NUM 2 (B)
#endif
#if defined TARGET_phase3T
# define NUM 3 (B)
#endif
#if defined TARGET_phase4T
# define NUM 4 (B)
#endif
#if defined TARGET_ordphase1T
# define NUM 5 (B)
#endif
\title{TITRE NUM}
