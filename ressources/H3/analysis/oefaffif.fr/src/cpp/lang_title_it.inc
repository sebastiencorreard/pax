#if defined TARGET_classer1 || defined TARGET_classer2 || defined TARGET_classer3 || defined TARGET_classer4
# define TITRE_it Classificare funzioni
# if defined TARGET_classer1
#  define TIT_it A (6 funzioni)
# endif
# if defined TARGET_classer2
#  define TIT_it A (9 funzioni)
# endif
# if defined TARGET_classer3
#  define TIT_it B (6 funzioni)
# endif
# if defined TARGET_classer4
#   define TIT_it B (9 funzioni)
# endif
#endif
#if defined TARGET_CORequa3 || defined TARGET_CORfonct3 || defined TARGET_CORequa4|| defined TARGET_CORfonct4 || defined TARGET_CORequa5 || defined TARGET_CORfonct5
# define TITRE_it Corrispondenza
# if defined TARGET_CORfonct3
#   define TIT_it funzione-rappresentazione
# endif
# if defined TARGET_CORfonct4
#  define TIT_it funzione-rappresentazione
# endif
# if defined TARGET_CORfonct5
#  define TIT_it funzione-rappresentazione
# endif
# if defined TARGET_CORequa3
#  define TIT_it equazione-retta
# endif
# if defined TARGET_CORequa4
#  define TIT_it equazione-retta
# endif
# if defined TARGET_CORequa5
#  define TIT_it equazione-retta
# endif
#endif
#if defined TARGET_eqdroite
# define TITRE_it Trova l'equazione esplicita
#endif
#if defined TARGET_imagecoord1
# define TITRE_it Cliquer sur l'ordonnée de l'image
#endif
#if defined TARGET_imagecoord2
# define TITRE_it Cliquer sur l'abscisse de l'antécédent
#endif
#if defined TARGET_qcmfonct
# define TITRE_it Qual è la funzione?
#endif
#if defined TARGET_qcmequa
# define TITRE_it Qual è l'equazione?
#endif
#if defined TARGET_graphima
# define TITRE_it Grafico -> immagine
#endif
#if defined TARGET_fnctaff1
# define TITRE_it Trova l'equazione
#endif
#if defined TARGET_fnctaff2
# define TITRE_it Funzione affine?
#endif
#if defined TARGET_fnctaff3
# define TITRE_it Trova l'equazione (guidato 1)
#endif
#if defined TARGET_fnctaff4
# define TITRE_it Trova l'equazione (guidato 2)
#endif
#if defined TARGET_graphant
# define TITRE_it Grafico -> preimmagine
#endif
#if defined TARGET_imagecoord1
# define TITRE_it Clicca sull'ordinata dell'immagine
#endif
#if defined TARGET_imagecoord2
# define TITRE_it Clicca sull'ascissa della preimmagine
#endif
