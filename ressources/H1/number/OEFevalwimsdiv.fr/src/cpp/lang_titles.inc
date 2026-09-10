#include "lang_title_fr.inc"

#if defined TARGET_oefdivision1 || defined TARGET_oefvocabdiv1 || defined TARGET_oefmentaldiv1 || defined TARGET_oefmachprob1 || defined TARGET_oefdiv101 || defined TARGET_oefmachdiv1 || defined TARGET_oefvocabmult1 || defined TARGET_oefmachprob1 || defined TARGET_oefcriterediv1 || defined TARGET_oefcriteredivs1 
# define NUM 1
#endif
#if defined TARGET_oefdivision2 || defined TARGET_oefvocabdiv2 || defined TARGET_oefmentaldiv2 || defined TARGET_oefmachprob2 || defined TARGET_oefdiv102 || defined TARGET_oefmachdiv2 || defined TARGET_oefvocabmult2 || defined TARGET_oefmachprob2 || defined TARGET_oefcriterediv2 || defined TARGET_oefcriteredivs2
# define NUM 2
#endif
#if defined TARGET_oefdivision3 || defined TARGET_oefvocabdiv3 || defined TARGET_oefmentaldiv3 || defined TARGET_oefmachprob3 || defined TARGET_oefdiv103 || defined TARGET_oefmachdiv3 || defined TARGET_oefvocabmult3 || defined TARGET_oefmachprob3 || defined TARGET_oefcriterediv3 || defined TARGET_oefcriteredivs3
# define NUM 3
#endif
#if defined TARGET_oefdivision4 || defined TARGET_oefvocabdiv4 || defined TARGET_oefmentaldiv4 || defined TARGET_oefmachprob4 || defined TARGET_oefdiv104 || defined TARGET_oefmachdiv4 || defined TARGET_oefvocabmult4 || defined TARGET_oefmachprob4 || defined TARGET_oefcriterediv4 || defined TARGET_oefcriteredivs4 
# define NUM 4
#endif
#if defined TARGET_oefdivision5 || defined TARGET_oefvocabdiv5 || defined TARGET_oefmentaldiv5 || defined TARGET_oefmachprob5 || defined TARGET_oefdiv105 || defined TARGET_oefmachdiv5 || defined TARGET_oefvocabmult5 || defined TARGET_oefmachprob5 || defined TARGET_oefcriterediv5 || defined TARGET_oefcriteredivs5 
# define NUM 5
#endif

#if defined TARGET_oefcriteredivs1 || defined TARGET_oefcriteredivs2 || defined TARGET_oefcriteredivs3 || defined TARGET_oefcriteredivs4 || defined TARGET_oefcriteredivs5 
\title{TITRE NUM s}
#else
\title{TITRE NUM}
#endif
