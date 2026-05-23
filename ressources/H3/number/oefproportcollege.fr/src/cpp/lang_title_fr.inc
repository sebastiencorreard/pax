#define PBP Tableau de proportionnalité
#define NUM
#if defined TARGET_oeftablprop2 || defined TARGET_oeftablprop6 || defined TARGET_oeftablprop0 || defined TARGET_oeftablprop4 || defined TARGET_oeftablprop1 || defined TARGET_oeftablprop5
# define NUM (francs)
#endif
#if defined TARGET_oefprobprop1
# define NUM bis
#endif
#if defined TARGET_oefvitesse1
# define TITRE Vitesse
#endif
#if defined TARGET_oefduree1
# define TITRE Durée 1
#endif
#if defined TARGET_tabproportion
# define TITRE Tableau de proportion 1
#endif
#if defined TARGET_tabprop0
# define TITRE Tableau de proportion 2
#endif
#if defined TARGET_tabprop
# define TITRE Tableau de proportion 3
#endif
#if defined TARGET_oefechellereelle1
# define TITRE Échelle réelle
#endif
#if defined TARGET_distance
# define TITRE Distance
#endif
#if defined TARGET_oefdistance1
# define TITRE Distance 2
#endif
#if defined TARGET_oefechelcarte1
# define TITRE Échelle sur une carte
#endif
#if defined TARGET_oefechelle1
# define TITRE Échelle
#endif
#if defined TARGET_oefprobprop1 || defined TARGET_oefprobprop1euro
# define TITRE Problème de proportionnalité 1 NUM
#endif
#if defined TARGET_oefprobprop2 || defined TARGET_oefprobprop2euro
# define TITRE Problème de proportionnalité 2 NUM
#endif
#if defined TARGET_oefprobprop3 || defined TARGET_oefprobprop3euro
# define TITRE Problème de proportionnalité 3 NUM
#endif
#if defined TARGET_oeftablprop0 || defined TARGET_oeftablprop0euro
# define TITRE PBP 0 NUM
#endif
#if defined TARGET_oeftablprop1 || defined TARGET_oeftablprop1euro
# define TITRE PBP 1 NUM
#endif
#if defined TARGET_oeftablprop2 || defined TARGET_oeftablprop2euro
# define TITRE PBP 2 NUM
#endif
#if defined TARGET_oeftablprop3 || defined TARGET_oeftablprop3euro
# define TITRE PBP 3 NUM
#endif
#if defined TARGET_oeftablprop4 || defined TARGET_oeftablprop4euro
# define TITRE PBP 4 NUM
#endif
#if defined TARGET_oeftablprop5 || defined TARGET_oeftablprop5euro
# define TITRE PBP 5 NUM
#endif
#if defined TARGET_oeftablprop6 || defined TARGET_oeftablprop6euro
# define TITRE PBP 6 NUM
#endif

