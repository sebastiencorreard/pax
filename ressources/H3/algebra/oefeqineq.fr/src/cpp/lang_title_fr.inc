#if defined TARGET_Equation || defined TARGET_Equation2 || defined TARGET_Equation3 || defined TARGET_Equation4 || defined TARGET_resoudre2 || defined TARGET_resoudre3
# define TITRE Équation
#endif
#if defined TARGET_optrou3
# define TITRE Multiplication à trou
#endif
#if defined TARGET_optrou4
# define TITRE Addition à trou
#endif
#if defined TARGET_optrou5
# define TITRE Soustraction à trou
#endif
#if defined TARGET_resoudre1
# define TITRE Équation produit
#endif
#if defined TARGET_CORequ3 || defined TARGET_CORequ4 || defined TARGET_CORequ5
# define TITRE Correspondance équations
#endif
#if defined TARGET_CORinequ3 || defined TARGET_CORinequ4 || defined TARGET_CORinequ5
# define TITRE Correspondance inéquations
#endif
#if defined TARGET_probsys || defined TARGET_probsys2
# define TITRE Problème et système d'équations
#endif
#if defined TARGET_equadiv
# define TITRE Équation avec division
#endif
#if defined TARGET_solvesys
# define TITRE Résoudre un système d'équations
#endif
#if defined TARGET_solution
# define TITRE Solution(s) d'équations
#endif
#if defined TARGET_systeme
# define TITRE Solution d'un système d'équations
#endif
#if defined TARGET_produit
# define TITRE Résolution équation produit
#endif
