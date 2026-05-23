#if defined TARGET_adpoA || defined TARGET_adpoB || defined TARGET_adpoC || defined TARGET_adpoD
# define TITRE Addition
#endif
#if defined TARGET_sopoA || defined TARGET_sopoB || defined TARGET_sopoC || defined TARGET_sopoD
# define TITRE Soustraction
#endif
#if defined TARGET_mupoA || defined TARGET_mupoB || defined TARGET_mupoC || defined TARGET_mupoD
# define TITRE Multiplication
#endif
#if defined TARGET_dipoA || defined TARGET_dipoB || defined TARGET_dipoC || defined TARGET_dipoD
# define TITRE Division
#endif
#if defined TARGET_adnbfr
# define TITRE Addition entier et fraction
#endif
#if defined TARGET_sonbfr
# define TITRE Soustraction entier et fraction
#endif
#if defined TARGET_munbfr
# define TITRE Multiplication entier et fraction
#endif
#if defined TARGET_dinbfr
# define TITRE Division entier et fraction
#endif
#if defined TARGET_denomcom
# define TITRE Dénominateur commun
#endif
