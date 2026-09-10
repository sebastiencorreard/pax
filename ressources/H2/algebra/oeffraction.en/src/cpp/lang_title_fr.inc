#if defined EQCONST
# define TIT_fr Egalité constituée
# define TITLE_fr TIT_fr CNT
#endif

#if defined CORRESP
# define TIT_fr Correspondance
# if defined INVERSE
#   define TIT2_fr inverse
# else
#   define TIT2_fr égalité
# endif
# define TITLE_fr TIT_fr TIT2_fr CNT
#endif

#if defined FRACEQ
# define TIT_fr Fractions égales
# if defined TARGET_fracteq1a
#   define TIT2_fr Ia
# endif
# if defined TARGET_fracteq1b
#   define TIT2_fr Ib
# endif
# if defined TARGET_fracteq1c
#   define TIT2_fr Ic
# endif
# if defined TARGET_fracteq2a
#   define TIT2_fr IIa
# endif
# if defined TARGET_fracteq2b
#   define TIT2_fr IIb
# endif
# if defined TARGET_fracteq3a
#   define TIT2_fr IIIa
# endif
# if defined TARGET_fracteq3b
#   define TIT2_fr IIIb
# endif
# define TITLE_fr TIT_fr TIT2_fr
#endif

#if defined TARGET_guidadd
# define TITLE_fr Addition guidée
#endif

#if defined MISSING
# define TIT_fr manquant
# if defined TARGET_missden
#   define TITLE_fr Dénominateur TIT_fr
# endif
# if defined TARGET_missnum
#   define TITLE_fr Numérateur TIT_fr
#  endif
#if defined TARGET_missdeninv
#   define TITLE_fr Dénominateur TIT_fr inverse
#endif
# if defined TARGET_missnuminv
#   define TITLE_fr Numérateur TIT_fr inverse
# endif
# if defined TARGET_missdensum
#   define TITLE_fr Dénominateur TIT_fr somme
# endif
# if defined TARGET_missnumsum
#   define TITLE_fr Numérateur TIT_fr somme
# endif
#endif
