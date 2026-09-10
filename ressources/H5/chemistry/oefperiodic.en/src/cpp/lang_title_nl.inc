#if defined TARGET_order3 || defined TARGET_order4 || defined TARGET_order5 || defined TARGET_order6
# define TIT_nl Volgorde
#endif
#if defined TARGET_one
# define TIT_nl Een element
#endif
#if defined TARGET_prec
# define TIT_nl Het voorafgaande element
#endif
#if defined TARGET_next
# define TIT_nl Het volgende element
#endif
#if defined TARGET_metals4 || defined TARGET_metals6 || defined TARGET_metals8 || defined TARGET_metals10
#define TIT_nl Metalen en niet-metalen
#endif
#if defined TARGET_blackbox || defined TARGET_blackbox2
# define TIT_nl Black box
#endif
#if defined TARGET_corr3 || defined TARGET_corr4 || defined TARGET_corr5 || defined TARGET_corr6 || defined TARGET_corr7
# define TIT_nl Overeenkomst
#endif
#if defined TARGET_click1
# define TIT_nl Klik op de tabel
#endif
#if defined TARGET_fill3 || defined TARGET_fill4 || defined TARGET_fill5 || defined TARGET_fill6 || defined TARGET_fill8 || defined TARGET_fill10 || defined TARGET_fill14 || defined TARGET_fill20 || defined TARGET_fill33 || defined TARGET_fill54 || defined TARGET_fill62 || defined TARGET_fill103 || defined TARGET_fill108
# define TIT_nl Fill
#endif
