#if defined TARGET_dev1exp
#define TITLE Développer une expression
#endif
#if defined TARGET_dev2exp
#define TITLE Développer deux expressions
#endif
#if defined TARGET_dev2fact1 || defined TARGET_dev2fact2
#define TITLE Développer un produit de 2 facteurs
#endif
#if defined TARGET_dev2fact2
#define TITLE Développer un produit de 2 facteurs
# define NUM II
#endif
#if defined TARGET_factorisat1 || defined TARGET_factorisat2
# define TITLE Factorisation à étapes
#endif
#if defined TARGET_factdir1
# define TITLE Factorisation
#endif
#if defined TARGET_quizz
# define TITLE Course calcul littéral
#endif
