#if defined TARGET_spheric0 || defined TARGET_spheric1 || defined TARGET_spheric2
# define TITRE Coordonnées sphériques
#endif
#if defined TARGET_cylindric0 || TARGET_cylindric1 || defined TARGET_cylindric2
# define TITRE Coordonnées cylindriques
#endif
#if defined TARGET_cylindric0 || TARGET_cylindric1 || defined TARGET_cylindric2
# define TITRE Coordonnées cylindriques
#endif
#if defined TARGET_spheric0 || defined TARGET_cylindric0
# define NUM
#endif
#if defined TARGET_spheric1 || defined TARGET_cylindric1
# define NUM I
#endif
#if defined TARGET_spheric2 ||  defined TARGET_cylindric2
# define NUM II
#endif
#if defined TARGET_sphericsym
# define TITRE Symétrie et coordonnées sphériques
# define NUM
#endif
\title{TITRE NUM}
