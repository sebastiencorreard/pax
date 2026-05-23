#define DEC décimal
#if defined TARGET_optrou1
# define TITRE Soustraction à trou 2
#endif
#if defined TARGET_optrou2
# define TITRE Division à trou 2
#endif
#if defined TARGET_optrou3
# define TITRE Multiplication à trou
#endif
#if defined TARGET_optrou4
# define TITRE Addition à trou
#endif
#if defined TARGET_optrou5
# define TITRE Soustraction à trou 1
#endif
#if defined TARGET_optrou6
# define TITRE Division à trou 1
#endif
#if defined TARGET_Equation3 || defined TARGET_Equation4 || defined TARGET_Equation5 || defined TARGET_Equation6 || defined TARGET_Equation1 || defined TARGET_Equation2 || defined TARGET_Equation10 || defined TARGET_Equation11 || defined TARGET_Equation12 || defined TARGET_Equation13 || defined TARGET_Equation14
# define TITRE Équation du type
#endif
#if defined TARGET_correquat1
# define TITRE Correspondance d'équations
#endif
#if defined TARGET_oefsysequa1 || defined TARGET_oefsysequa2 || defined TARGET_oefsysequa2 || defined TARGET_oefsysequa3  || defined TARGET_oefsysequa4 || defined TARGET_oefsysequa5  || defined TARGET_oefsysequa6 || defined TARGET_oefsysequa7 || defined TARGET_oefsysequa8
# define TITRE Système d'équations
#endif
