%%%%%%%%%%%%%% HINT %%%%%%%%%%%%%%
#if defined TARGET_06 || defined TARGET_07 || defined TARGET_08 || defined TARGET_09
\text{titre_indic1=Indication 1 - Hypoténuse}
\text{titre_indic2=Indication 2 - Théorème de Pythagore}
#endif
#if defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
\text{titre_indic2=Indication 1 - Théorème de Pythagore}
\text{titre_indic3=Indication 2 }
#endif
#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b
\text{titre_indic2=<strong>Théorème de Pythagore</strong>}
#endif
#if defined TARGET_03a || defined TARGET_03b || defined TARGET_05a || defined TARGET_05b
\text{titre_rem=Remarque}
#endif
#if defined TARGET_01a || defined TARGET_01b || defined TARGET_06 || defined TARGET_07 || defined TARGET_08 || defined TARGET_09
\text{indic1=Par définition, l'hypoténuse d'un triangle rectangle est le côté opposé à son angle droit.}
#endif

\text{indic2=Dans un triangle rectangle, le carré de la longueur de l'hypoténuse est égal à la somme des carrés des
 longueurs des deux côtés de l'angle droit.}


#if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b || defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
\text{indic2=\indic2
<br class="spacer">Dit autrement : "l'aire du carré construit sur l'hypoténuse est égale à la somme des aires des carrés
 construits sur les côtés de l'angle droit."}
#endif

#if defined TARGET_03a || defined TARGET_03b
\text{indic2=\indic2
<br class="spacer">Ici, connaisssant l'aire du carré construit sur l'hypoténuse et l'aire d'un carré construit sur un côté de l'angle droit, 
on peut calculer l'aire du carré construit sur l'autre côté de l'angle droit grâce au théorème de Pythagore.}
#endif

#if defined TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
\text{indic3=<br>L'aire d'un carré de côté de longueur \(\mathbf{c}\) est égale au produit <span class="nowrap">\(\mathbf{c \times c}\).</span>}
#endif
#if defined TARGET_04a || defined TARGET_04b
\text{indic3=\indic3
<br class="spacer">
Ici, on pourra donc calculer l'aire du carré construit sur l'hypoténuse (indication 1), puis en déduire la longueur de l'hypoténuse (indication 2).}
#endif
#if defined TARGET_05a || defined TARGET_05b
\text{indic3=\indic3
<br class="spacer">
Ici, connaisssant l'aire du carré construit sur l'hypoténuse et l'aire d'un carré construit sur un côté de l'angle droit, on peut calculer l'aire du carré construit
 sur l'autre côté de l'angle droit grâce au théorème de Pythagore (indication 1), puis en déduire la longueur de son côté (indication 2).}
#endif
#if defined TARGET_03a || defined TARGET_03b || defined TARGET_05a || defined TARGET_05b
\text{rem=Dans un triangle rectangle, un côté adjacent à l'angle droit est appelé cathète.}
#endif