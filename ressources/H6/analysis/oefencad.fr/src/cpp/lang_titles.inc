#include "lang_title_fr.inc"

#if defined TARGET_valeurabsolue1 || defined TARGET_encadproduit || defined TARGET_difference || defined TARGET_oefencad1 || defined TARGET_valeurabsolue1
# define NUM 1
#endif
#if defined TARGET_valeurabsolue2 || defined TARGET_encadproduit2 || defined TARGET_difference2 || defined TARGET_oefencad2 || defined TARGET_valeurabsolue2
# define NUM 2
#endif
#if defined TARGET_valeurabsolue3 || defined TARGET_oefencad3 || defined TARGET_valeurabsolue3 || defined TARGET_encadproduit3
# define NUM 3
#endif
#if !defined NUM
# define NUM
#endif

\title{TITRE NUM}
