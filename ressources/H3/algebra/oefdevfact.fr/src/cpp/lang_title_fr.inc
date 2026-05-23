#if defined TARGET_etapedev1
# define TITRE Développer par étapes
#endif
#if defined TARGET_completer
# define TITRE Compléter
#endif
#if defined TARGET_completer1 || defined TARGET_completer2
# define TITRE Compléter une factorisation
#endif
#if defined TARGET_completer3
# define TITRE Compléter une factorisation (positif)
#endif
#if defined TARGET_connaissance1 || defined TARGET_connaissance2 || defined TARGET_connaissance3  || defined TARGET_connaissance4
# define TITRE Connaissance de
#endif
#if defined TARGET_deve1 || defined TARGET_deve2 || defined TARGET_deve3 || defined TARGET_deve4 || defined TARGET_deve5 || defined TARGET_deve6
# define TITRE Développer
#endif
#if defined TARGET_deve7 || defined TARGET_deve8
# define TITRE Développer guidé
#endif
#if defined TARGET_CORreduction
#  define TITRE Correspondance distribution-réduction
#endif
#if defined TARGET_CORdistribution
#  define TITRE Correspondance distribution
#endif
#if defined TARGET_distrired
#  define TITRE Distribution-réduction
#endif
#if defined TARGET_facteur1 || defined TARGET_facteur2
# define TITRE Trouver un facteur commun
#endif
#if defined TARGET_factor1 || defined TARGET_factor2 || defined TARGET_factor3 || defined TARGET_factor4 || defined TARGET_factor5
# define TITRE Factoriser
#endif
#if defined TARGET_simplifier || defined TARGET_simplifier2 || defined TARGET_simplifier3
# define TITRE Simplifier
#endif
#if defined TARGET_tabdeve1 || defined TARGET_tabdeve2
# define TITRE Développer avec tableau
#endif
#if defined TARGET_correspondance1
# define TITRE Correspondance (a+b)(c+d)
#endif
#if defined TARGET_correspondance2
# define TITRE Correspondance (a+b)(c+d)
#endif
#if defined TARGET_reduire || defined TARGET_reduire2
# define TITRE Réduire
#endif

