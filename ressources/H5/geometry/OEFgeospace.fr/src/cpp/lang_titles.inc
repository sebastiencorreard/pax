#include "lang_title_fr.inc"
#if defined TARGET_vectcoplan || defined TARGET_interobjplan || defined TARGET_alignpts || defined TARGET_colinvect1 || defined TARGET_coplanvect1
# define NUM I
#endif
#if defined TARGET_vectcoplan2 || defined TARGET_interobjplan1 || defined TARGET_alignpts2 || defined TARGET_colinvect2 || defined TARGET_coplanvect2
# define NUM II
#endif
#if defined TARGET_objspaequa || defined TARGET_dteplanesp || defined TARGET_vectcube || defined TARGET_vectcolin || defined TARGET_correspobjspace || defined TARGET_dteaffesp || defined TARGET_dteaffesp || defined TARGET_ptscoplan1 || defined TARGET_nattriangle
# define NUM
#endif
\title{TITRE NUM}
