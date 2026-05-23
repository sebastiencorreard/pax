%%%%%% ENONCES %%%%%%%%%%%%


\text{enonce1=
Une unité de longueur est donnée.
<br class="spacer">
\A\B\C est un triangle rectangle en \Sommet tel que <span class="nowrap">\donnee[1;]</span> et <span class="nowrap">\donnee[2;].</span>}

\text{long=longueur}

#if !defined TARGET_10DeuxMesures
\text{SolDetails1=
L'énoncé donne la longueur <span class="oef_indgood">\DEN[5]</span> et la longueur <span class="oef_indgood">\NUM[5]</span>
à l'angle dont on cherche une mesure.}

\text{SolDetails2=
On exprime alors la ligne trigonométrique qui fait intervenir ces deux longueurs&nbsp;:
c'est <span class="oef_indgood">\trigo[1;\typeLigne]</span> de l'angle dont on cherche une mesure.}
#endif

#if defined TARGET_09DonnerLigneTrigo || defined TARGET_11LigneTrigoUniteEtape || defined TARGET_10DeuxMesures

\text{etap1=Étape 1}
\text{etap2=Étape 2}

# if defined TARGET_09DonnerLigneTrigo || defined TARGET_11LigneTrigoUniteEtape
\text{enonce0=Cet exercice comporte deux étapes.}
# endif

# if defined TARGET_10DeuxMesures
\text{enonce0=Cet exercice comporte trois étapes.}
\text{enonce2=On cherche à calculer une mesure de l'angle \(\widehat{\NomAngle}\)
et de l'angle <span class="nowrap">\(\widehat{\NomAngle2}\).</span>}
\text{enonce3= Sélectionner la ou les propositions qui conviennent.}
\text{etap3=Étape 3}
\text{quest1=Les égalités \donnee1 et \donnee2 permettent d'évaluer directement}
\text{enonce4=Pour chaque question, sélectionner la proposition qui convient.}
\text{quest2=Le nombre \ListeLignesTrigo2[\NumSol1] est égal à}
\text{quest3=Le nombre \ListeLignesTrigo2[\NumSol2] est égal à}
\text{enonce5=Compléter les phrases.}
\text{quest4=La mesure en degrés de l'angle \(\widehat{\NomAngle}\) arrondie à l'unité est&nbsp;:}
\text{quest5=La mesure en degrés de l'angle \(\widehat{\NomAngle2}\) arrondie à l'unité est&nbsp;:}
# endif
#endif

#if defined TARGET_11LigneTrigoUniteEtape
\text{delangle=de l'angle}
\text{enonce2=On cherche à calculer une mesure de l'angle <span class="nowrap">\(\widehat{\NomAngle}\).</span>}
\text{enonce3= Sélectionner la proposition qui convient.}
\text{quest1=Le quotient \(\frac{\NomNum}{\NomDen}\) est }
#endif

#if defined TARGET_11LigneTrigoUniteEtape  || defined TARGET_12LigneTrigoUnite || defined TARGET_10DeuxMesures
# if !defined TARGET_10DeuxMesures
\text{enonce4=Compléter la phrase.}
\text{quest2=La mesure en degrés de l'angle \(\widehat{\NomAngle}\) arrondie à l'unité est}
\text{enonceSol2=En déduire la mesure en degrés de l'angle \(\widehat{\NomAngle}\) arrondie à l'unité.}
# endif

\text{SolDetails3=On en déduit, selon le modèle de la calculatrice bien configurée en <strong>mode degré</strong>, à l'aide d'une des touches \calculatrice}
\text{SolDetails4=la mesure de l'angle \(\widehat{\NomAngle}\) arrondie à l'unité est }

\text{pre_arr=à l'unité,au dixième,au centième,au millième,au dix-millème,au cent-millième,au millionième,au dix-millionième,au cent-millionième,au milliardième,au dix-milliardième}
\text{pre_tronc=à l'unité,au dixième,au centième,au millième,au dix-millème,au cent-millième,au millionième,au dix-millionième,au cent-millionième,au milliardième,au dix-milliardième}

\text{text_cond1=Le raisonnement semble correct&nbsp;}
\text{text_cond2a=est la mesure de}
\text{text_cond2b=arrondie au degré&nbsp;}

\text{feed1a=On demandait une valeur de }
\text{feed1b=<strong>arrondie à l'unité</strong>.}
\text{feed2=Vous avez donné}
\text{feed3=son arrondi}
\text{feed4=sa troncature}

\text{feed8=La mesure en degrés d'un angle aigu est <strong>strictement</strong>
 supérieure à \(0\) et <strong>strictement</strong> inférieure à <span class="nowrap">\(90\).</span>}
\text{feed10=Vérifiez que votre calculatrice est bien configurée en mode degré}
%%%text{feed9=ou que vous ne confondez pas la mesure de l'angle}
\text{feed11a=Vérifiez que vous ne confondez pas la mesure de l'angle}
\text{feed11b=avec la valeur de}
\text{feed12=Une valeur arrondie à l'unité est un nombre entier.}

# if !defined TARGET_10DeuxMesures
\text{feed6=Vérifiez que vous n'avez pas confondu l'angle \(\widehat{\NomAngle_compl}\) avec l'angle \(\widehat{\NomAngle}\) ou que vous ne vous êtes pas trompé·e de ligne trigonométrique ou que vous n'avez pas confondu, selon le modèle de votre
   calculatrice, la touche <span class="calculator nowrap">Arcsin</span> avec <span class="calculator nowrap">Arccos</span>
    ou <span class="calculator nowrap">sin<sup>-1</sup></span> avec <span class="calculator nowrap">cos<sup>-1</sup></span>.}
\text{feed7=Vérifiez que vous n'avez pas confondu l'angle \(\widehat{\NomAngle_compl}\) avec l'angle \(\widehat{\NomAngle}\) ou que vous n'avez pas inversé le quotient \(\frac{\NomNum}{\NomDen}\) lors de l'utilisation de la calculatrice.}
\text{feed11=Vérifiez que vous ne confondez pas la mesure de l'angle \(\widehat{\NomAngle}\) avec la valeur de
<span class="nowrap">\(\trigo[2;\typeLigne](\widehat{\NomAngle})\).</span>}

# endif


# if defined TARGET_10DeuxMesures
\text{feed13=Vous avez confondu les angles \(\widehat{\NomAngle}\) et <span class="nowrap">\(\widehat{\NomAngle2}\).</span>}
\text{feed14=Les angles \(\widehat{\NomAngle}\) et \(\widehat{\NomAngle2}\) sont complémentaires, leur somme est égale à <span class="nowrap">90°.</span>}


\text{enonceSol1=Quelles relations trigonométriques font intervenir ces deux égalités&nbsp;?}
\text{enonceSol2=Écrire les deux relations.}
\text{enonceSol3=En déduire une mesure en degrés, arrondie à l'unité, de chacun des deux angles aigus du triangle.}
\text{SolDetails1a=L'énoncé donne les longueurs \elem[1] et \elem[2].}
\text{SolDetails1b=Or \elem[1] est la longueur \NUM[6] \(\widehat{\NomAngle}\) et \NUM_suiv[6] \(\widehat{\NomAngle2}\)}
\text{SolDetails1c=et \elem[2] est la longueur <span class="nowrap">\DEN[6].</span>}
\text{SolDetails1d=et \elem[2] est la longueur \NUM_suiv[6] \(\widehat{\NomAngle}\) et \NUM[6] <span class="nowrap">\(\widehat{\NomAngle2}\).</span>}
\text{SolDetails1e=Les égalités \donnee1 et \donnee2 permettent donc d'évaluer directement
 <span class"oef_indgood">\ListeLignesTrigo[\NumSol1]</span> et
 <span class"oef_indgood"> \ListeLignesTrigo[\NumSol2]</span>.}
\text{SolDetails2=Par définition, le nombre \ListeLignesTrigo2[\NumSol1] est égal au quotient
 \(\frac{\ListePairesLongueurs[\NumeroLigne;10]}{\ListePairesLongueurs[\NumeroLigne;11]}\) soit ici
 <span class"oef_indgood nowrap">\ListePairesLongueurs[\NumeroLigne;3],</span> et le nombre \ListeLignesTrigo2[\NumSol2] est égal au quotient
 \(\frac{\ListePairesLongueurs[\NumeroLigne;12]}{\ListePairesLongueurs[\NumeroLigne;13]}\) soit ici
 <span class"oef_indgood nowrap">\ListePairesLongueurs[\NumeroLigne;7].</span>}
\text{SolDetails5=la mesure de l'angle \(\widehat{\NomAngle2}\) arrondie à l'unité est }
\text{SolDetails3b= et \calculatrice_suiv}
# endif

#endif




#if defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2 || defined TARGET_09DonnerLigneTrigo

\text{enonce2=
On considère l'angle <span class="nowrap">\(\widehat{\NomAngle}\).</span>}

\text{quest2=Pour évaluer une mesure de l'angle <span class="nowrap">\(\widehat{\NomAngle}\),</span> la méthode la plus directe consiste à utiliser }
\text{quest3=de l'angle <span class="nowrap">\(\widehat{\NomAngle}\).</span>}


# if defined TARGET_07IdentifierLigneTrigo1
\text{enonce3=Sélectionner la ou les propositions qui conviennent dans chacun des DEUX cadres.}
\text{quest1=Les deux longueurs données par l'énoncé sont celles&nbsp;:}
\text{enonceSol2=Quelles sont les longueurs données par l'énoncé&nbsp;?}
\text{enonceSol3=Quelle relation trigonométrique fait intervenir les deux longueurs données par l'énoncé&nbsp;?}
# endif

# if defined TARGET_08IdentifierLigneTrigo2
\text{enonce3=Sélectionner la proposition qui convient.}
\text{enonceSol2=Quelle est la méthode la plus directe pour évaluer une mesure de l'angle \(\widehat{\NomAngle}\)&nbsp;?}
# endif

# if defined TARGET_09DonnerLigneTrigo

\text{enonce3= Sélectionner la proposition qui convient.}
\text{enonce4= Sélectionner l'expression qui convient.}
\text{enonce5=Nous utilisons}
\text{quest4=Le nombre}
\text{quest5=est égal à&nbsp;:}
\text{enonceSol2=On cherche à évaluer une mesure de l'angle \(\widehat{\NomAngle}\).}
\text{enonceSol3=Est-il préférable d'utiliser le sinus, le cosinus ou la tangente de l'angle \(\widehat{\NomAngle}\)&nbsp;?
<br>Quelle égalité écrire&nbsp;?}
# endif

#endif
