#include "lang_title_fr.inc"

#if defined TARGET_facteur1 || defined TARGET_completer1 || defined TARGET_correspondance1 || defined TARGET_reduire || defined TARGET_simplifier
# define NUM 1
#endif
#if defined TARGET_facteur2 || defined TARGET_completer3|| defined TARGET_completer2 || defined TARGET_correspondance2 || defined TARGET_reduire2 || defined TARGET_simplifier2
# define NUM 2
#endif
#if defined TARGET_simplifier3
#  define NUM 3
#endif
#if defined TARGET_connaissance1 || defined TARGET_connaissance2 || defined TARGET_connaissance3  || defined TARGET_connaissance4
# if defined TARGET_connaissance1
#  define NUM k(a+b)
# endif
# if defined TARGET_connaissance2
#  define NUM (a+b)(c+d)
# endif
# if defined TARGET_connaissance3
#  define NUM (a+b)^2
# endif
# if defined TARGET_connaissance4
#  define NUM (a+b)(a-b)
# endif
#endif
#if defined TARGET_deve1
# define NUM k(a+b)#
#endif
#if defined TARGET_deve2
# define NUM (a+b)(c+d)#
#endif
#if defined TARGET_deve3
# define NUM (a+b)^2#
#endif
#if defined TARGET_deve4
# define NUM (a-b)^2#
#endif
#if defined TARGET_deve6
# define NUM (a-b)(a+b)#
#endif
#if defined TARGET_deve7
# define NUM (a+b)^2
#endif
#if defined TARGET_deve8
# define NUM (a-b)^2
#endif
#if defined TARGET_deve5 || defined TARGET_completer
# define NUM
#endif
#if defined TARGET_CORreduction || defined TARGET_CORdistribution || defined TARGET_distrired
# define NUM
#endif
#if defined TARGET_factor1 || defined TARGET_factor2 || defined TARGET_factor3 || defined TARGET_factor4 || defined TARGET_factor5
# if defined TARGET_factor1
#  define NUM ka+kb 1
# endif
# if defined TARGET_factor2
#  define NUM ka+kb 2
# endif
# if defined TARGET_factor3
#  define NUM a^2-b^2
# endif
# if defined TARGET_factor4
#  define NUM a^2+2ab+b^2
# endif
# if defined TARGET_factor5
#  define NUM
# endif
#endif
#if defined TARGET_tabdeve1
# define NUM k(a+b)
#endif
#if defined TARGET_tabdeve2 || defined TARGET_etapedev1
# define NUM (a+b)(c+d)
#endif

\title{TITRE NUM}
