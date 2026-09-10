#if defined TARGET_sommedouble
# define TITRE Sommation double
#endif
#if defined TARGET_suml || defined TARGET_sumg
# define TITRE Somme classique
#endif
#if defined TARGET_sommation || defined TARGET_sommation2
# define TITRE Sommation
#endif
#if defined TARGET_interversion
# define TITRE Interversion de sommes
#endif
#if defined TARGET_sommedouble2 || defined TARGET_sommegraphe
# define TITRE Sommation double
#endif
#if defined TARGET_sommegraphe
# define TITRE Sommation graphique
#endif
#if defined TARGET_indsom
# define TITRE Indices et sommation
#endif
#if defined TARGET_chgtva1 || defined TARGET_chgtva2
# define TITRE Changement de variable dans une somme
#endif
