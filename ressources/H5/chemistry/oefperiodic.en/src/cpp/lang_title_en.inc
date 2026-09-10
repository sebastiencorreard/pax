#if defined TARGET_order3 || defined TARGET_order4 || defined TARGET_order5 || defined TARGET_order6
# define TIT Order
#endif
#if defined TARGET_one
# define TIT One element
#endif
#if defined TARGET_prec
# define TIT Previous element
#endif
#if defined TARGET_next
# define TIT Next element
#endif
#if defined TARGET_metals4 || defined TARGET_metals6 || defined TARGET_metals8 || defined TARGET_metals10
#define TIT Metals and non-metals
#endif
#if defined TARGET_blackbox || defined TARGET_blackbox2
# define TIT Black box
#endif
#if defined TARGET_corr3 || defined TARGET_corr4 || defined TARGET_corr5 || defined TARGET_corr6 || defined TARGET_corr7
# define TIT Correspondance
#endif
#if defined TARGET_click1
# define TIT Click on table
#endif
#if defined TARGET_fill3 || defined TARGET_fill4 || defined TARGET_fill5 || defined TARGET_fill6 || defined TARGET_fill8 || defined TARGET_fill10 || defined TARGET_fill14 || defined TARGET_fill20 || defined TARGET_fill33 || defined TARGET_fill54 || defined TARGET_fill62 || defined TARGET_fill103 || defined TARGET_fill108
# define TIT Fill
#endif
