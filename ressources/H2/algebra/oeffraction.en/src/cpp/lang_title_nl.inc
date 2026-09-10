#if defined EQCONST
#define TIT_nl Gelijkwaardigheid
#define TITLE_nl TIT_nl CNT
#endif

#if defined CORRESP
#define TIT_nl Overeenkomstig
#if defined INVERSE
#define TIT2_nl invers
#else
#define TIT2_nl gelijkwaardig
#endif
#define TITLE_nl TIT_nl TIT2_nl CNT
#endif

#if defined FRACEQ
#define TIT_nl Gelijke breuken
#if defined TARGET_fracteq1a 
#define TIT2_nl Ia
#endif
#if defined TARGET_fracteq1b 
#define TIT2_nl Ib
#endif
#if defined TARGET_fracteq1c 
#define TIT2_nl Ic
#endif
#if defined TARGET_fracteq2a 
#define TIT2_nl IIa
#endif
#if defined TARGET_fracteq2b 
#define TIT2_nl IIb
#endif
#if defined TARGET_fracteq3a 
#define TIT2_nl IIIa
#endif
#if defined TARGET_fracteq3b 
#define TIT2_nl IIIb
#endif
#define TITLE_nl TIT_nl TIT2_nl
#endif

#if defined TARGET_guidadd
#define TITLE_nl Optellen
#endif

#if defined MISSING
#define TIT_nl Aanvullen
#if defined TARGET_missden
#define TIT2_nl noemer
#endif
#if defined TARGET_missnum
#define TIT2_nl teller
#endif
#if defined TARGET_missdeninv
#define TIT2_nl inverse noemer
#endif
#if defined TARGET_missnuminv
#define TIT2_nl inverse teller
#endif
#if defined TARGET_missdensum
#define TIT2_nl noemers optellen
#endif
#if defined TARGET_missnumsum
#define TIT2_nl tellers optellen
#endif
#define TITLE_nl TIT_nl TIT2_nl
#endif
