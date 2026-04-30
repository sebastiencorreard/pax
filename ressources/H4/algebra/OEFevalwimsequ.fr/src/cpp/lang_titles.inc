#include "lang_title_fr.inc"

#if defined TARGET_equaprod1 || defined TARGET_ineqequi1 || defined TARGET_equation1 || defined TARGET_inequation1 || defined TARGET_sysequi1 || defined TARGET_solvesys1 || defined TARGET_solution1 || defined TARGET_equatcar1 || defined TARGET_representation1
# define NUM 1
#endif
#if defined TARGET_equaprod2 || defined TARGET_ineqequi2 || defined TARGET_equation2 || defined TARGET_inequation2 || defined TARGET_sysequi2 || defined TARGET_solvesys2 || defined TARGET_solution2 || defined TARGET_equatcar2 || defined TARGET_representation2
# define NUM 2
#endif
#if defined TARGET_equaprod3 || defined TARGET_ineqequi3 || defined TARGET_equation3 || defined TARGET_inequation3 || defined TARGET_sysequi3 || defined TARGET_solvesys3 || defined TARGET_solution3 || defined TARGET_representation3
# define NUM 3
#endif
#if defined TARGET_equaprod4 || defined TARGET_ineqequi4 || defined TARGET_equation4 || defined TARGET_inequation4 || defined TARGET_sysequi4 || defined TARGET_solvesys4 || defined TARGET_solution4 || defined TARGET_representation4
# define NUM 4
#endif
#if defined TARGET_equaprod5 || defined TARGET_ineqequi5 || defined TARGET_equation5 || defined TARGET_inequation5 || defined TARGET_sysequi5 || defined TARGET_solvesys5 || defined TARGET_solution5 || defined TARGET_representation5
# define NUM 5
#endif
#if defined TARGET_equatcar3
# define NUM x^2=a 3
#endif
#if defined TARGET_equatcar4
# define NUM x^2=a 4
#endif
#if defined TARGET_equatcar5
# define NUM x^2=a 5
#endif

\title{TITRE NUM}
