#include "lang_title_fr.inc"
#include "lang_title_it.inc"
#if defined TARGET_CORequa3 || defined TARGET_CORfonct3 || defined TARGET_CORequa4 || defined TARGET_CORfonct4 || defined TARGET_CORequa5 || defined TARGET_CORfonct5
# if defined TARGET_CORfonct3
#   define NUMBER 3
# endif
# if defined TARGET_CORfonct4
#   define NUMBER 4
# endif
# if defined TARGET_CORfonct5
#   define NUMBER 5
# endif
# if defined TARGET_CORequa3
#   define NUMBER 3
# endif
# if defined TARGET_CORequa4
#   define NUMBER 4
# endif
# if defined TARGET_CORequa5
#   define NUMBER 5
# endif
#endif
#if !defined NUMBER
# define NUMBER
#endif
#if !defined TIT
# define TIT
#endif
#if !defined TIT_it
# define TIT_it
#endif
\title{TITRE TIT NUMBER}
\title_it{TITRE_it TIT_it NUMBER}
