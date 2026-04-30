#if defined TARGET_equcond1 || defined TARGET_equcond21 || defined TARGET_equcondbc1 || defined TARGET_equcondbc2 || defined TARGET_equcondbc21 || defined TARGET_equcondbc22
# define TITRE Équation parallèle
#endif
#if defined TARGET_equcond2 || defined TARGET_equcond22 || defined TARGET_equcondbc3 || defined TARGET_equcondbc4 || defined TARGET_equcondbc23 || defined TARGET_equcondbc24
# define TITRE Équation perpendiculaire
#endif
#if defined TARGET_sontelles1 || defined TARGET_sontelles2
# define TITRE Sont-elles parallèles
#endif
#if defined TARGET_sontelles3 || defined TARGET_sontelles4
# define TITRE Sont-elles sécantes
#endif
#if defined TARGET_sontelles5 || defined TARGET_sontelles6
# define TITRE Sont-elles perpendiculaires
#endif
#if defined TARGET_lectequ1 || defined TARGET_lectequ3 || defined TARGET_lectequ5
# define TITRE Quel est le coefficient directeur
#endif
#if defined TARGET_lectequ2 || defined TARGET_lectequ4 || defined TARGET_lectequ6
# define TITRE Quelle est l'ordonnée à l'origine
#endif
#if defined TARGET_point1 || defined TARGET_point2 || defined TARGET_point3 || defined TARGET_point4
# define TITRE Coordonnées d'un point
#endif
#if defined TARGET_mkequation
# define TITRE Reconstituer l'équation
#endif
