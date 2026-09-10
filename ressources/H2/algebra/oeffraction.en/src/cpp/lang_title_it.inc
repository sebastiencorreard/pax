#if defined EQCONST
#define TIT_it Costruisci l'eguaglianza
#define TITLE_it TIT_it CNT
#endif

#if defined CORRESP
#define TIT_it Corrispondenza
#if defined INVERSE
#define TIT2_it tra inverse
#else
#define TIT2_it tra equivalenti
#endif
#define TITLE_it TIT_it TIT2_it CNT
#endif

#if defined FRACEQ
#define TIT_it Frazioni equivalenti
#if defined TARGET_fracteq1a 
#define TIT2_it Ia
#endif
#if defined TARGET_fracteq1b 
#define TIT2_it Ib
#endif
#if defined TARGET_fracteq1c 
#define TIT2_it Ic
#endif
#if defined TARGET_fracteq2a 
#define TIT2_it IIa
#endif
#if defined TARGET_fracteq2b 
#define TIT2_it IIb
#endif
#if defined TARGET_fracteq3a 
#define TIT2_it IIIa
#endif
#if defined TARGET_fracteq3b 
#define TIT2_it IIIb
#endif
#define TITLE_it TIT_it TIT2_it
#endif

#if defined TARGET_guidadd
#define TITLE_it Addizione guidata
#endif

#if defined MISSING
#define TIT_it Completa
#if defined TARGET_missden
#define TIT2_it denominatore
#endif
#if defined TARGET_missnum
#define TIT2_it numeratore
#endif
#if defined TARGET_missdeninv
#define TIT2_it denominatore inversa
#endif
#if defined TARGET_missnuminv
#define TIT2_it numeratore inversa
#endif
#if defined TARGET_missdensum
#define TIT2_it denominatore somma
#endif
#if defined TARGET_missnumsum
#define TIT2_it numeratore somma
#endif
#define TITLE_it TIT_it TIT2_it
#endif