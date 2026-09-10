#if defined TARGET_cubrt
/* note for translators: keep commas */
\text{name_statement=Trouver une racine cubique \(w\) du nombre complexe,en donnant sa partie réelle et partie imaginaire}
#endif
#if defined TARGET_tworoots || defined TARGET_tworoots2
\text{impur=imaginaire pur}
\text{real=réel}
\text{zero=égal à zéro}
\text{nor=ni réel ni imaginaire pur}
#endif
#if defined TARGET_tworoots
/* note for translators: keep commas */
\text{name_statement=Soient,les deux racines d'un polynôme,où \(p \) est,et \(q\) réel. Supposons que \(z_1\) et \(z_2\) ne sont ni réels ni imaginaires purs. Alors \(z_1 - z_2\) est un nombre} /*'*/
#endif
#if defined TARGET_tworoots2
/* note for translators: keep commas */
\text{name_statement=Soient,les deux racines d'un polynôme,où,est un nombre réel. Alors \(z_1 - z_2\) est un nombre} /*'*/
#endif
#if defined TARGET_eqmod
\text{name_statement=Résoudre dans \(\mathbb{C}\) l'équation} /*'*/
/* note for translators: keep commas */
\text{name_instruction=Tapez,si vous pensez que l'équation n'a pas de solution} /*'*/
/* note for translators: keep commas */
\text{name_hint=Dans le plan complexe,l'origine et les points d'affixe,doivent former un losange (pourquoi?)} /*'*/
#endif
#if defined TARGET_modsum
\text{name_yesno=Oui,Non}
\text{name_statement=Existe-t-il deux nombres complexes \(z_1\) et \(z_2\) tels que}
\text{name_hint=Quelles sont des conditions sur les longueurs des
  3 côtés d'un triangle&nbsp;?} /*'*/
\text{name_answer=Votre réponse}
#endif
#if defined TARGET_modsum2
\text{name_and=et}
/* note for translators: keep commas */
\text{name_statement=Soient,deux nombres complexes avec,degrés,Calculer le module de}
\text{name_hint=Rappelez-vous du théorème de cosinus&nbsp;: si un triangle a
trois côtés de longueurs \(a\), \(b\), \(c\) et si l'on note par
\(A\) l'angle opposé au côté \(a\), alors}
#endif
#if defined TARGET_sumofj
/* note for translators: keep commas */
\text{name_statement=Soit,Calculez la somme}
#endif
#if defined TARGET_cbrt
\text{name_style=un nombre complexe tel que,une racine (complexe) du polynôme}
/* note for translators: keep commas */
\text{name_statement=Soit, Quel est le nombre}
#endif
#if defined TARGET_arggiven
/* note for translators: keep commas */
\text{name_statement=Calculer la partie réelle et la partie imaginaire du nombre
complexe \(z\) ayant,comme module et,comme argument}
#endif
#if defined TARGET_pentaroot
/* note for translators: keep commas */
\text{name_statement=Soient,les 4 racines (complexes) du polynôme,Quel est le nombre}
#endif
#if defined TARGET_argask
\text{name_statement=Donner le module et un argument du nombre complexe}
\text{name_condition=est un argument de}
#endif
#if defined TARGET_quadouble
/* note for translators: keep commas */
\text{name_statement=Pour quelle valeur complexe \(w\) le polynôme,a-t-il une racine double (complexe)&nbsp;}
\text{name_answer=La racine double}
#endif
#if defined TARGET_quadouble2
\text{name_and=et}
/* note for translators: keep commas */
\text{name_statement=Pour quelles valeurs réelles de,le polynôme,a-t-il une racine double (complexe)&nbsp;}
\text{name_answer=La racine double}
#endif
#if defined TARGET_argsum
/* note for translators: keep commas */
\text{name_statement=Soient,Donner le module et un argument de}
\text{name_condition=est un argument de}
#endif
#if defined TARGET_pythagorus || defined TARGET_pythagorus2
\text{name_and=et}
/* note for translators: keep commas */
\text{name_statement=Soient,deux nombres complexes avec,Quelle est la valeur de}
\text{name_answer=Votre réponse}
\text{name_hint=Pensez au théorème de Pythagore&nbsp;! Quelle est la différence entre}
#endif
#if defined TARGET_fraction || defined TARGET_fraction2
\text{name_statement=Calculer la partie réelle et la partie imaginaire du nombre
complexe suivant&nbsp;}
\text{name_answer1=Partie réelle}
\text{name_answer2=Partie imaginaire}
#endif
#if defined TARGET_rootcoef
\text{name_statement1=Soit \(P(X)=X^2 + p X + q\) un polynôme où les coefficients
\(p\) et \( q\) sont réels. On sait que \(P\) a une racine complexe \( z\) dont la
partie imaginaire est égale à}
\text{name_statement2=Dans ce cas, il y a une relation entre les coefficients
\( p\) et \(q\). Déterminez cette relation en donnant \( q\) comme
une fonction de \(p\).}
/* note for translators: keep commas */
\text{name_solution=Si,l'autre racine de \(P\) est,Donc,ou,Et} /*'*/
#endif
#if defined TARGET_sqrt
/* note for translators: keep commas */
\text{name_statement=Trouver une racine carrée \(w\) du nombre complexe,
en donnant sa partie réelle et partie imaginaire}
#endif
#if defined TARGET_modmax
/* note for translators: keep commas */
\text{name_statement=Parmi tous les nombres complexes \(z\) de module,
trouver celui pour qui le module de,est maximal}
#endif
#if defined TARGET_maxmod
\text{name_list_maxmin=maximum,minimum}
/* note for translators: keep commas */
\text{name_statement=Quel est le,du module,où \(z\) est un nombre complexe de module}
\text{name_answer=du module}
#endif
#if defined TARGET_Trianglequilat
\text{name_and=et}
/* note for translators: keep commas */
\text{name_statement=Si \(A\) et \(B\) sont des points du plan d'affixe,
trouver l'affixe d'un point \(M\) tel que le triangle \(ABM\) soit équilatéral}
\text{name_hint=\(AM\) est l'image de \(AB\) par une rotation. Laquelle ?} /*'*/
#endif
#if defined TARGET_quadpoly
\text{name_statement=Calculer les deux racines du polynôme}
\text{name_instruction=Vous pouvez entrer les deux racines \(r1\) et \(r2\) dans n'importe quel ordre.} /*'*/
\text{name_condition1=est une racine}
\text{name_condition2=est l'autre racine} /*'*/
#endif
#if defined TARGET_sumofi
\text{name_statement=Calculer la somme}
#endif
#if defined TARGET_suminv
/* note for translators: keep commas */
\text{name_statement=Soit \(z\) un nombre complexe avec,Calculez}
#endif
#if defined TARGET_sumroot
/* note for translators: keep commas */
\text{name_statement=Soit,Quelle est la valeur de}
\text{name_hint=est une racine du polynôme}
#endif
#if defined TARGET_powerconj
/* note for translators: keep commas */
\text{name_statement=Combien y a-t-il de nombres complexes \(z\) tels que,égale le conjugué de \(z\)&nbsp;}
\text{name_answer=Le nombre}
/* note for translators: keep commas */
\text{name_solution=Soit \(w\) le conjugué de \(z\). On constate d'abord que,
implique \(|z|=1\) ou 0. Quand \(|z|=1\) on a,
donc les nombres complexes \(z\) qui vérifient la condition du problème sont exactement les racines du polynôme}
\text{name_or=ou}
#endif
