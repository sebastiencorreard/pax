#if defined EQCONST
#define TIT Egalité constituée
#define TITLE TIT CNT
#endif

#if defined CORRESP
#define TIT Correspondance
#if defined INVERSE
#define TIT2 inverse
#else
#define TIT2 égalité
#endif
#define TITLE TIT TIT2 CNT
#endif

#if defined FRACEQ
#define TIT Fractions égales
#if defined TARGET_fracteq1a 
#define TIT2 Ia
#endif
#if defined TARGET_fracteq1b 
#define TIT2 Ib
#endif
#if defined TARGET_fracteq1c 
#define TIT2 Ic
#endif
#if defined TARGET_fracteq2a 
#define TIT2 IIa
#endif
#if defined TARGET_fracteq2b 
#define TIT2 IIb
#endif
#if defined TARGET_fracteq3a 
#define TIT2 IIIa
#endif
#if defined TARGET_fracteq3b 
#define TIT2 IIIb
#endif
#define TITLE TIT TIT2
#endif

#if defined TARGET_guidadd
#define TITLE Addition guidée
#endif

#if defined MISSING
#define TIT manquant
#if defined TARGET_missden
#define TITLE Dénominateur TIT
#endif
#if defined TARGET_missnum
#define TITLE Numérateur TIT
#endif
#if defined TARGET_missdeninv
#define TITLE Dénominateur TIT inverse
#endif
#if defined TARGET_missnuminv
#define TITLE Numérateur TIT inverse
#endif
#if defined TARGET_missdensum
#define TITLE Dénominateur TIT somme
#endif
#if defined TARGET_missnumsum
#define TITLE Numérateur TIT somme
#endif
#endif