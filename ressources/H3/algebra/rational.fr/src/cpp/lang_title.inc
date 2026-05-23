#if defined TARGET_sommesimple1 || defined TARGET_sommedouble1 || defined TARGET_sommepriorite1 || defined TARGET_sommeproduit1 || defined TARGET_produit1 || defined TARGET_quotient1 || defined TARGET_quotientfrac1
# define LEVEL (a. facile)
#endif

#if defined TARGET_sommesimple2 || defined TARGET_sommedouble2 || defined TARGET_sommepriorite2 || defined TARGET_sommeproduit2 || defined TARGET_produit2 || defined TARGET_quotient2 || defined TARGET_quotientfrac2
# define LEVEL (b. normal)
#endif

#if defined TARGET_sommesimple3 || defined TARGET_sommedouble3 || defined TARGET_sommepriorite3 || defined TARGET_sommeproduit3 || defined TARGET_produit3 || defined TARGET_quotient3 || defined TARGET_quotientfrac3
# define LEVEL (c. expert)
#endif


#if defined TARGET_sommesimple1 || defined TARGET_sommesimple2 || defined TARGET_sommesimple3
# define TIT Somme simple pour le calcul fractionnaire
# define TITRE 01- TIT LEVEL
#endif

#if defined TARGET_sommedouble1 || defined TARGET_sommedouble2 || defined TARGET_sommedouble3
# define TIT Somme pour le calcul fractionnaire
# define TITRE 02- TIT LEVEL
#endif

#if defined TARGET_sommepriorite1 || defined TARGET_sommepriorite2 || defined TARGET_sommepriorite3
# define TIT Somme et priorité pour le calcul fractionnaire
# define TITRE 03- TIT LEVEL
#endif

#if defined TARGET_produit1 || defined TARGET_produit2 || defined TARGET_produit3
# define TIT Produit pour le calcul fractionnaire
# define TITRE 04- TIT LEVEL
#endif

#if defined TARGET_quotient1 || defined TARGET_quotient2 || defined TARGET_quotient3
# define TIT Quotient pour le calcul fractionnaire
# define TITRE 05- TIT LEVEL
#endif

#if defined TARGET_sommeproduit1 || defined TARGET_sommeproduit2 || defined TARGET_sommeproduit3
# define TIT Somme et produit ou quotient pour le calcul fractionnaire
# define TITRE 06- TIT LEVEL
#endif

#if defined TARGET_quotientfrac1 || defined TARGET_quotientfrac2 || defined TARGET_quotientfrac3
# define TIT Quotient de fractions
# define TITRE 07- TIT LEVEL
#endif
