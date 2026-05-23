\text{lang=slib(oef/env lang)}
#include "lang_title_fr.inc"
#include "lang_title_en.inc"
\title{TITLE}
\title_en{TITLE_en}
#if defined TARGET_flageu  || defined TARGET_mapeu
# define PP eu
#endif
#if defined TARGET_flagas  || defined TARGET_mapas
# define PP as
#endif
#if defined TARGET_flagaf  || defined TARGET_mapaf
# define PP af
#endif
#if defined TARGET_flagam  || defined TARGET_mapam
# define PP am
#endif
#if defined TARGET_flagoc  || defined TARGET_mapoc
# define PP oc
#endif
#if defined TARGET_flagall || defined TARGET_mapall
# define PP all
#endif
#if defined TARGET_flagbig || defined TARGET_mapbig
# define PP big
#endif
