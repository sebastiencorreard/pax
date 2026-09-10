####### FEEDBACK #######
#if defined TARGET_01a || defined TARGET_01b
\text{retour_sommet_hyp=Le point \Sommet est le sommet de l'angle droit et \liste_cotes[\reply1] est un côté de l'angle droit. 
Par définition, l'hypoténuse est le côté <em>opposé</em> à l'angle droit&nbsp;!}
#endif

#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b ||  defined TARGET_04a || defined TARGET_04b ||  defined TARGET_05a || defined TARGET_05b
\text{err_rac=Vous ne pouvez pas extraire la racine carrée d'un nombre négatif !}
\text{grand_pos=Une 
  #if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b
   aire 
  #else 
   longueur  
  #endif
 non nulle est une grandeur strictement positive.}
#endif 

#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b
\text{confusion_long=Vous semblez avoir calculé la longueur 
 #if defined TARGET_02a || defined TARGET_02b
  de l'hypoténuse [\Hyp[1]\Hyp[2]]
 #else
  du côté [\Sommet\Hyp[2]]
 #endif
 du triangle \A\B\C rectangle en \Sommet.}
#endif 

#if defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
\text{confusion_aire=Vous semblez avoir calculé l'aire du carré construit sur  
 #if defined TARGET_04a || defined TARGET_04b
  l'hypoténuse [\Hyp[1]\Hyp[2]]
 #else
  le côté [\Sommet\Hyp[2]]
 #endif
 du triangle \A\B\C rectangle en \Sommet.}
#endif 

#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b
\text{retour_aire=L'hypoténuse d'un triangle rectangle étant le côté le plus long du triangle, l'aire du carré construit sur 
  #if defined TARGET_02a || defined TARGET_02b
    l'hypoténuse [\Hyp[1]\Hyp[2]] ne peut pas être inférieure  
  #else
    le côté [\Sommet\Hyp[2]] ne peut pas être supérieure 
  #endif
  ou égale
  #if defined TARGET_02a || defined TARGET_02b
   aux aires des carrés construits sur les côtés [\Sommet\Hyp[1]] et [\Sommet\Hyp[2]] de l'angle droit 
  #else
   à l'aire du carré construit sur l'hypoténuse [\Hyp[1]\Hyp[2]]
  #endif
  du triangle \A\B\C.}
#endif

#if defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
\text{retour_long=L'hypoténuse d'un triangle rectangle étant le côté le plus long du triangle, la longueur 
  #if defined TARGET_04a || defined TARGET_04b
    de l'hypoténuse [\Hyp[1]\Hyp[2]] ne peut pas être inférieure  
  #else
    du côté [\Sommet\Hyp[2]] ne peut pas être supérieure 
  #endif
  ou égale
  #if defined TARGET_04a || defined TARGET_04b
   aux longueurs des côtés [\Sommet\Hyp[1]] et [\Sommet\Hyp[2]] de l'angle droit 
  #else
   à la longueur de l'hypoténuse [\Hyp[1]\Hyp[2]]
  #endif
  du triangle \A\B\C.}
#endif
