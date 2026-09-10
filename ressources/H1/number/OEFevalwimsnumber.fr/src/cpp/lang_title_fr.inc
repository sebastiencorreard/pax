#if defined TARGET_oefecrit101 || defined TARGET_oefecrit102 || defined TARGET_oefecrit103 || defined TARGET_oefecrit104 || defined TARGET_oefecrit105
# define TITRE Écriture décimale
#endif
#if defined TARGET_oefecrit1 || defined TARGET_oefecrit2 || defined TARGET_oefecrit3 || defined TARGET_oefecrit4 || defined TARGET_oefecrit5
# define TITRE Écriture d'un nombre
#endif
#if defined TARGET_oefecrit101 || defined TARGET_oefecrit102
# define TITRE Écriture décimale
#endif
#if defined TARGET_oefecritdec1 || defined TARGET_oefecritdec2 || defined TARGET_oefecritdec3 || defined TARGET_oefecritdec4 || defined TARGET_oefecritdec5
# define TITRE Écriture d'un nombre décimal
#endif
#if defined TARGET_oefecritdeclitt1 || defined TARGET_oefecritdeclitt2 || defined TARGET_oefecritdeclitt3 || defined TARGET_oefecritdeclitt4 || defined TARGET_oefecritdeclitt5
# define TITRE Écriture décimale suite
#endif
#if defined TARGET_oefecritlong1 || defined TARGET_oefecritlong2 || defined TARGET_oefecritlong3 || defined TARGET_oefecritlong4 || defined TARGET_oefecritlong5
# define TITRE Mesure de longueur
#endif
#if defined TARGET_oefecritvoc1 || defined TARGET_oefecritvoc2 || defined TARGET_oefecritvoc3 || defined TARGET_oefecritvoc4 || defined TARGET_oefecritvoc5
# define TITRE Vocabulaire sur le rang
#endif
#if defined TARGET_oefencadr1 || defined TARGET_oefencadr2 || defined TARGET_oefencadr3 || defined TARGET_oefencadr4 || defined TARGET_oefencadr5
# define TITRE Encadrer
#endif
#if defined TARGET_oeffractdec1 || defined TARGET_oeffractdec2 || defined TARGET_oeffractdec3 || defined TARGET_oeffractdec4 || defined TARGET_oeffractdec5
# define TITRE Fraction décimale
#endif
#if defined TARGET_oeffractdix1 || defined TARGET_oeffractdix2 || defined TARGET_oeffractdix3 || defined TARGET_oeffractdix4 || defined TARGET_oeffractdix5
# define TITRE Fraction décimale suite
#endif
#if defined TARGET_oefinterc1 || defined TARGET_oefinterc2 || defined TARGET_oefinterc3 || defined TARGET_oefinterc4 || defined TARGET_oefinterc5
# define TITRE Intercaler
#endif
#if defined TARGET_oefordre1 || defined TARGET_oefordre2 || defined TARGET_oefordre3 || defined TARGET_oefordre4 || defined TARGET_oefordre5
# define TITRE Ordre
#endif
#if defined TARGET_oefrang1 || defined TARGET_oefrang2 || defined TARGET_oefrang3 || defined TARGET_oefrang4 || defined TARGET_oefrang5
# define TITRE Rang
#endif
#if defined TARGET_oefranger1 || defined TARGET_oefranger2 || defined TARGET_oefranger3 || defined TARGET_oefranger4 || defined TARGET_oefranger5
# define TITRE Ranger
#endif
#if defined TARGET_oefrecfractdec1 || defined TARGET_oefrecfractdec2 || defined TARGET_oefrecfractdec3 || defined TARGET_oefrecfractdec4 || defined TARGET_oefrecfractdec5
# define TITRE Relation fraction et écriture décimale
#endif
#if defined TARGET_plusproche
# define TITRE Valeurs approchées et arrondi
#endif
#if defined TARGET_oefapproch1 || defined TARGET_oefapproch2 || defined TARGET_oefapproch3 || defined TARGET_oefapproch4 || defined TARGET_oefapproch5
# define TITRE Valeur approchée
#endif
#if defined TARGET_arrondiunit || defined TARGET_arrondiunitguide
# define TITRE Arrondi à l'unité
#endif
#if defined TARGET_arrondix || defined TARGET_arrondixguide || defined TARGET_arrondixrelie
# define TITRE Arrondi au dixième
#endif
#if defined TARGET_arrondiunitguide || defined TARGET_arrondixguide
# define NUM (guidé)
#endif
#if defined TARGET_arrondixrelie
# define NUM (à relier)
#endif
