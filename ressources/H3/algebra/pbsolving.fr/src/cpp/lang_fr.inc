#if defined TARGET_traduction
\matrix{nombres=1, un, unième
2, deux, demi
3, trois, tiers
4, quatre, quart
5, cinq, cinquième
6, six, sixième
7, sept, septième
8, huit, huitième
9, neuf, neuvième
10,dix, dixième
11,onze, onzième
12,douze, douzième
13,treize, treizième
14,quatorze, quatorzième
15,quinze, quinzième
16,seize, seizième
17,dix-sept, dix-septième
18,dix-huit, dix-huitième
19,dix-neuf ,dix-neuvième
20,vingt, vingtième
21,vingt-et-un, vingt-et-unième}
\text{enonce1=\operationmix[1;1] de \nombresmix[1;2] \nombresmix[2;3] par \nombresmix[3;2] \nombresmix[4;3]}
\text{enonce2=\operationmix[2;1] de \nombresmix[5;2] \nombresmix[6;3] par \nombresmix[7;2] \nombresmix[8;3]}
\text{enonce3=\operationmix[3;1] de \nombresmix[9;2] \nombresmix[10;3] par \nombresmix[11;2] \nombresmix[12;3]}
\text{enonce4=\operationmix[4;1] de \nombresmix[13;2] \nombresmix[14;3] par \nombresmix[15;2] \nombresmix[16;3]}
\text{enonce=Traduire les expressions données par un calcul puis déterminer le résultat :}
\text{solution1=On a \( \Expression1 \) qui vaut \( \Solution1 \)}
\text{solution2=On a \( \Expression2 \) qui vaut \( \Solution2 \)}
\text{solution3=On a \( \Expression3 \) qui vaut \( \Solution3 \)}
\text{solution4=On a \( \Expression4 \) qui vaut \( \Solution4 \)}
\text{expression=Expression}
\text{resultat=Résultat}
\text{quotient=Le quotient}
\text{somme=La somme}
\text{produit=Le produit}
\text{difference=La différence}
#endif
#if defined TARGET_resistances
\text{enonce=Dans un circuit électrique, on a deux résistances \( R_{1}= \R1 \) \(\Omega\) et \( R_{2}=\R2  \) \(\Omega\)  montées en dérivation. On veut remplacer ces deux résistances par une résistance équivalente \( R \). Quelle est la valeur de \( R \) ?}
\text{monaide=On rappelle que dans ce cas, la valeur de la résistance équivalente est donnée par la formule : \( \dfrac{1}{R}=\dfrac{1}{R_1}+\dfrac{1}{R_2}\)}
#endif
#if defined TARGET_moyenne
\if{\genre=boy}{\text{pronom=Il}}{\text{pronom=Elle}}
\text{enonce=\prenom a déjà \m notes en mathématiques, qui sont : \liste.  Quelle devra être sa prochaine note pour que sa moyenne soit de \moyenne ?}
\text{lastnote=Dernière note}
\text{solution=La prochaine note devra être \notes[\n].}
#endif
#if defined TARGET_depenses
\if{\genre=boy}{\text{pronom=Il}}{\text{pronom=Elle}}
\text{rest=Reste}
\text{enonce=\prenom a \argent euros. \pronom en dépense \(\frac1\) dans un premier achat et \(\frac2\) de ce qui lui reste dans un deuxième achat. Calculer la somme qui reste à \prenom.}
\text{solution=Il reste \( \reste \) euros à \prenom.}
#endif
#if defined TARGET_rebond
\if{\genre=boy}{\text{si=S'il}}{\text{si=Si elle}}
\text{hauteur=hauteur}
\text{enonce=\prenom lance une balle sur le sol ; elle rebondit aux \(\rebond \) pour-cent de la hauteur de lancée. \si la lance d'une hauteur de \(\hauteurini\) centimètres, à quelle hauteur rebondit-elle après le rebond numéro \nombrerebond ? On arrondira à l'unité la plus proche.}
\text{solution=La balle rebondit de \(\hf\) centimètres après \( \nombrerebond \) rebonds. Valeur non arrondie \hauteurfinale}
#endif
#if defined TARGET_proprietaire
\text{rest=Reste}
\text{hectares=en hectares}
\text{enonce=Un propriétaire terrien a vendu \(\fraction1\) de sa propriété une année, et \(\fraction2\) de ce qui lui restait l'année suivante.}
\text{question1=Quelle fraction de sa propriété lui reste-t-il aujourd'hui ?}
\text{question2=Quelle est la superficie actuelle de sa propriété sachant qu'au départ elle était de \(\taille\) hectares ? Précision attendue : deux chiffres après la virgule.}
\text{solution=Il reste \reste, soit \terrain hectares.}
#endif
