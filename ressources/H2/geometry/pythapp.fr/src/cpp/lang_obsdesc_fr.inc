%%%%%%%%%%%%% DESCRIPTION - OBSERVATION %%%%%%%%%%%%%%%
#if defined TARGET_01a || defined TARGET_01b
\description{Déterminer l'hypoténuse du triangle rectangle donné.}
\observation{Déterminer l'hypoténuse d'un triangle rectangle donné.
Une figure accompagne 
  #if defined TARGET_01a
    l'énoncé et la solution.
  #else
    la solution seulement.
  #endif
}
#endif

#if defined TARGET_02a || defined TARGET_02b
\description{Calculer l'aire du carré construit sur l'hypoténuse du triangle rectangle donné connaissant les aires des carrés construits sur les côtés de l'angle droit.}
\observation{Calculer l'aire du carré construit sur l'hypoténuse d'un triangle rectangle, les aires des carrés construits sur les côtés de l'angle droit étant données.
Une figure accompagne
  #if defined TARGET_02a
    l'énoncé et la solution.
  #else
    la solution seulement.
  #endif
}
#endif

#if defined TARGET_03a || defined TARGET_03b
\description{Calculer l'aire du carré construit sur un côté de l'angle droit du triangle rectangle donné connaissant les aires des carrés construits sur l'hypoténuse et l'autre côté de l'angle droit.}
\observation{Calculer l'aire d'un carré construit sur une cathète d'un triangle rectangle, les aires des carrés construits sur l'hypoténuse et l'autre côté de l'angle droit étant données.
 Une figure accompagne
  #if defined TARGET_03a
    l'énoncé et la solution.
  #else
    la solution seulement.
  #endif
}
#endif

#if defined TARGET_04a || defined TARGET_04b
\description{Calculer la longueur de l'hypoténuse du triangle rectangle donné connaissant les aires des carrés construits sur les 2 côtés de l'angle droit.}
\observation{Calculer la longueur de l'hypoténuse d'un triangle rectangle connaissant les aires des carrés construits sur les 2 côtés de l'angle droit. 
 Une figure accompagne
  #if defined TARGET_04a
    l'énoncé et la solution.
  #else
    la solution seulement.
  #endif
}
#endif

#if defined TARGET_05a || defined TARGET_05b
\description{Calculer la longueur d'un côté de l'angle droit du triangle rectangle donné connaissant les aires des carrés construits sur l'hypoténuse et l'autre côté de l'angle droit.}
\observation{Calculer la longueur d'un côté de l'angle droit d'un triangle rectangle connaissant les aires des carrés construits sur l'hypoténuse et l'autre côté de l'angle droit. 
 Une figure accompagne
  #if defined TARGET_05a
    l'énoncé et la solution.
  #else
    la solution seulement.
  #endif
}
#endif

#if defined TARGET_06 || defined TARGET_07 || defined TARGET_08
\description{Associer chaque égalité de Pythagore donnée au triangle rectangle correspondant.}
  #if defined TARGET_06
\observation{Dans ce QCM, 3 égalités de Pythagore simples sont à associer à chacun des 3 triangles rectangles.}
  #endif
   #if defined TARGET_07
\observation{Dans ce QCM, 3 égalités de Pythagore simples ou plus complexes sont à associer à chacun des 3 triangles rectangles.}
  #endif
  #if defined TARGET_08
\observation{Dans ce QCM, chacune des 3 égalités de Pythagore simples ou plus complexes données est à associer au triangle rectangle correspondant.}
  #endif
#endif

#if defined TARGET_09
\description{Cocher les affirmations qui sont vraies dans le triangle rectangle donné.}
\observation{Cocher les affirmations qui sont vraies dans le triangle rectangle donné. Il est possible de choisir le nombre d'affirmations à proposer&nbsp;: 3 (par défaut), 4 ou 5. 
Il est aussi possible d'accompagner ou non l'énoncé d'une figure.}
#endif
