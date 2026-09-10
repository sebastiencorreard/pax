#if defined EQCONST
#define TIT Equality construct
#define TITLE TIT CNT
#endif

#if defined CORRESP
#define TIT Correspondance
#if defined INVERSE
#define TIT2 inverse
#else
#define TIT2 equality
#endif
#define TITLE TIT TIT2 CNT
#endif

#if defined FRACEQ
#define TIT Equal fractions
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
#define TITLE Guided addition
#endif

#if defined MISSING
#define TIT Missing
#if defined TARGET_missden
#define TIT2 denominator
#endif
#if defined TARGET_missnum
#define TIT2 numerator
#endif
#if defined TARGET_missdeninv
#define TIT2 denominator inverse
#endif
#if defined TARGET_missnuminv
#define TIT2 numerator inverse
#endif
#if defined TARGET_missdensum
#define TIT2 denominator sum
#endif
#if defined TARGET_missnumsum
#define TIT2 numerator sum
#endif
#define TITLE TIT TIT2
#endif