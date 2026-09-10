#include "lang_title_fr.inc"

#if defined TARGET_trouvecont1 || defined TARGET_questcont1 || defined TARGET_contdef1 || defined TARGET_racinen1
# define NUM 1
#endif
#if defined TARGET_trouvecont2 || defined TARGET_questcont2 || defined TARGET_contdef2 || defined TARGET_racinen2
# define NUM 2
#endif
#if defined TARGET_trouvecont3 || defined TARGET_questcont3
# define NUM 3
#endif
#if defined TARGET_trouvecont4 || defined TARGET_questcont4
# define NUM 4
#endif
#if defined TARGET_tvidicho || defined TARGET_tviscan
# define NUM
#endif
\title{TITLE NUM}
