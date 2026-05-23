#if defined TARGET_classer1 || defined TARGET_classer2 || defined TARGET_classer3 || defined TARGET_classer4
# define TITRE Classer des fonctions
# if defined TARGET_classer1
#  define TIT A (6 fonctions)
# endif
# if defined TARGET_classer2
#  define TIT A (9 fonctions)
# endif
# if defined TARGET_classer3
#  define TIT B (6 fonctions)
# endif
# if defined TARGET_classer4
#   define TIT B (9 fonctions)
# endif
#endif
#if defined TARGET_CORequa3 || defined TARGET_CORfonct3 || defined TARGET_CORequa4|| defined TARGET_CORfonct4 || defined TARGET_CORequa5 || defined TARGET_CORfonct5
# define TITRE Correspondance
# if defined TARGET_CORfonct3
#   define TIT fonction-représentation
# endif
# if defined TARGET_CORfonct4
#  define TIT fonction-représentation
# endif
# if defined TARGET_CORfonct5
#  define TIT fonction-représentation
# endif
# if defined TARGET_CORequa3
#  define TIT équation-droite
# endif
# if defined TARGET_CORequa4
#  define TIT équation-droite
# endif
# if defined TARGET_CORequa5
#  define TIT équation-droite
# endif
#endif
#if defined TARGET_eqdroite
# define TITRE Trouver l'équation réduite
#endif
#if defined TARGET_imagecoord1
# define TITRE Cliquer sur l'ordonnée de l'image
#endif
#if defined TARGET_imagecoord2
# define TITRE Cliquer sur l'abscisse de l'antécédent
#endif
#if defined TARGET_qcmfonct
# define TITRE Quelle est la fonction ?
#endif
#if defined TARGET_qcmequa
# define TITRE Quelle est l'équation ?
#endif
#if defined TARGET_graphima
# define TITRE Graphique -> image
#endif
#if defined TARGET_fnctaff1
# define TITRE Trouver la formule
#endif
#if defined TARGET_fnctaff2
# define TITRE Fonction affine ?
#endif
#if defined TARGET_fnctaff3
# define TITRE Trouver la formule (guidé 1)
#endif
#if defined TARGET_fnctaff4
# define TITRE Trouver la formule (guidé 2)
#endif
#if defined TARGET_graphant
# define TITRE Graphique -> antécédent
#endif
#if defined TARGET_imagecoord1
# define TITRE Cliquer sur l'ordonnée de l'image
#endif
#if defined TARGET_imagecoord2
# define TITRE Cliquer sur l'abscisse de l'antécédent
#endif
