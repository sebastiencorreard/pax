#if defined TARGET_signeQuot3 || defined TARGET_signeProdQuot2 || defined TARGET_signeProdQuotient
\text{name_error=Erreur}
\text{name_feed0=Vous avez marqué YYYY comme valeur interdite du quotient \(f(x)\).
  Rappelons qu'une valeur interdite est un nombre qui annule le <strong>dénominateur</strong>
du quotient. Or ici YYYY annule le <strong>numérateur</strong> de \(f(x)\).}
\matrix{name_feed1=On réécrit, sous forme d'un quotient pour en étudier le signe
 Vous avez mal ordonné les valeurs dans la première ligne du tableau.}
\text{name_feed2=Vous avez fait une erreur sur la valeur interdite VVVV :
  toute valeur qui annule le dénominateur de \(f(x)\)
  est une "valeur interdite" ; dans la ligne du quotient
  on la signale par une double-barre.}
\text{name_feed3=Vous avez marqué XXXX comme valeur interdite du quotient \(f(x)\).
  Rappelons qu'une valeur interdite est un nombre qui annule le
  <strong>dénominateur</strong> du quotient. Or ici XXXX annule
  le <strong>numérateur</strong> de \(f(x)\).}
\text{name_feed4=Vous avez marqué YYYY comme valeur interdite du quotient \(f(x)\).
  Rappelons qu'une valeur interdite est un nombre qui annule le
  <strong>dénominateur</strong> du quotient. Or ici YYYY annule le
  <strong>numérateur</strong> de \(f(x)\).}
#endif
#if defined TARGET_signeProdQuot2 || defined TARGET_signeProdQuotient
\text{name_hint1=Le binôme \(a x + b\) s'annule en \(x_0=-\frac{b}{a}\) et change de signe en \(x_0\).
  Il est du signe de \(a\) lorsque \(x > x_0\).}
\text{name_hint2=Lorsque \(a x + b\) est en facteur au dénominateur de \(f(x)\)
  alors \(-\frac{b}{a}) est une valeur interdite de \(f(x)\)}
#endif
#if defined TARGET_signeProdQuotient
\text{name_question=Construire le tableau de signes de la fonction \(f\) définie}
\text{name_forall=pour tout \(x\) réel tel que}
\text{name_by=par}
\text{name_on=sur}
#endif
#if defined TARGET_signeProdQuot2
\text{name_question=Étudier en fonction de \(x\) le signe}
\text{name_produit=du produit,du quotient}
#endif
#if defined TARGET_signeQuot3
\text{name_enonce=Étudier en fonction de \(x\) le signe de l'expression,
  Compléter le tableau ci-dessous}
\text{name_hint=Commencer par écrire , en un seul quotient de dénominateur}
#endif
#if defined TARGET_signeGraphique
\text{name_enonce=La représentation graphique d'une fonction \(f\) définie sur,
  est donnée dans le repère (O ; I, J).
  On admet que la fonction \(f) ne change pas de sens de variation
  en dehors du graphique.}
\text{name_enonce2=Répondre aux questions suivantes par lecture graphique.}
\text{name_question1=Combien l'équation \(f(x) = 0\) a-t-elle de solutions dans}
\text{name_question2=L'équation \(f(x) = 0\) n'a aucune solution dans}
\text{name_complete=Compléter le tableau de signes de \(f\)&nbsp;}
\text{name_question3=L'équation \(f(x) = 0\) n'admet aucune solution dans,
  La fonction \(f\) n'est pas définie en}
\text{name_answer=Nombre de zéro(s)}
\text{name_hint1=Le nombre \(f(x)\) est strictement positif (resp. strictement négatif)
  pour tout réel \(x\) de l'intervalle \(I\) si et seulement, sur cet intervalle,
  la courbe représentative de \(f\) est située au-dessus (resp. en-dessous)
  de l'axe des abscisses.}
\text{name_hint2=\(f(x)\) est nul si et seulement si \(x\) est l'abscisse d'un point d'intersection
 de la courbe représentative de \(f\) avec l'axe des abscisses.}
\text{name_enonce3=L'équation \(f(x) = 0\) a une unique solution \(x_1\)
  dans \(\mathcal{D}\).}
\text{name_enonce4=La valeur arrondie au dixième de \(x_1\) est}
\text{name_enonce5=L'équation \(f(x) = 0\) a une unique solution \(x_1\)
  dans \(\mathcal{D}\).}
\text{name_enonce6=La fonction \(f\) n'est pas définie en}
\text{name_enonce7=L'équation \(f(x) = 0\) a trois solutions}
\text{name_enonce9=L'équation \(f(x) = 0\) a deux solutions}
\text{name_enonce8=Les valeurs arrondies au dixième de,
  sont respectivement}
\text{name_in=dans}
#endif
#if defined TARGET_assTabExp
\text{name_aucun=aucune}
\text{name_question=De quelle(s) expression(s) le tableau suivant
  est-il le tableau de signes&nbsp;}
\text{name_inst=Il peut y avoir plusieurs réponses ou aucune.}
\text{name_hint1=Le binôme \(a x +b\) s'annule en \(-\frac{b}{a}\)
  et change de signe en \(-\frac{b}{a}\).
  Il est du signe de \(a\) lorsque \(x > -\frac{b}{a}\).}
\text{name_hint2=Si une double barre est présente sous une valeur \(x_0\),
  cela indique que \(f\) n'est pas définie en \(x_0\).
  Dans ce cas, \(f\) est un quotient dont le dénominateur s'annule en \(x_0\).}
#endif
#if defined TARGET_signeBinome
\text{name_question=Complétez le tableau de signes du binôme du premier degré}
\text{name_hint=Le binôme du premier degré \(a x + b\) s'annule en \(-\frac{b}{a}\)
  et change de signe en \(-\frac{b}{a}\).
  Il est du signe du coefficient \(a\) lorsque \(x > -\frac{b}{a}\).}
#endif
#if defined TARGET_signeEvident
\text{name_question=L'expression XXXX a un signe évident quel que soit le réel \(x\),
  est toujours}
\text{name_choix=strictement négative,négative ou nulle,
  strictement positive,positive ou nulle}
\matrix{name_feed1=On a, pour tout réel
  donc, est toujours du signe de,et ne s'annule jamais.
  est toujours positif ou nul si
  ou nul en
  Le nombre,est strictement positif,donc la somme,est strictement positive
  est toujours négatif ou nul
  est strictement négatif et on peut écrire
  est strictement négatif}
\text{name_now=Or}
#endif
#if defined TARGET_inequationEvidente || defined TARGET_ineqParticuliere
\matrix{name_question=On peut résoudre l'inéquation (I)
  sans tableau de signe car le signe de , est évident.
  L'ensemble \(S\) des solutions de (I) est }
\text{name_explanation=Explications}
\text{name_question1=On a, pour tout réel \(x\).
  Donc en multipliant par,
  qui est strictement positif,
  qui est strictement négatif}
\text{name_so=Donc}
\text{name_as=Comme}
\text{name_onehas=on a}
\text{name_conclusion=Ainsi tout réel \(x\) est solution de,
  Ainsi aucun réel \(x\) n'est solution de}
#endif
#if defined TARGET_inequationParticuliere
\text{name_feed=Pour,
  donc tout réel différent de, est solution de,
  donc seul}
#endif
#if defined TARGET_methodologie || defined TARGET_methodologie2
\text{name_enonce=Un élève a dressé le tableau suivant pour étudier le signe de
  la fonction \(f\) définie par}
\text{name_question=A-t-il raison, Sinon, cochez toutes les erreurs qu'il a commises.,
  quelle erreur a été commise&nbsp;}
# if defined TARGET_methodologie
\text{name_produit=du produit,du quotient}
\text{name_msg5=les zéros du produit ne sont pas marqués,
  la valeur interdite du quotient n'est pas marquée}
\text{name_choix=le tableau est correct,
  les valeurs qui annulent \(\u\) et \(\v\) sont mal ordonnées,
  l'étude de signe de \(\u\) est fausse,
  l'étude de signe de \(\v\) est fausse}
\text{name_choix2=les signes, sont faux}
# endif
# if defined TARGET_methodologie2
\text{name_choix=l'élève a correctement dressé le tableau de signe de \(f(x)\),
  l'élève n'a pas factorisé complètement \(f(x)\),
  l'élève a oublié qu'un facteur de \(f(x)\) était élevé au carré,
  l'élève n'a pas vu qu'un facteur de \(f(x)\) était de signe évident constant,
  l'expression \(\V) du tableau n'est pas un facteur de \(f(x)\),
  l'élève a oublié de marquer une valeur interdite}
\text{name_choixp=n'est pas un facteur de \(f(x)\)}
\text{name_posneg=positif,négatif}
\text{name_forall=pour tout réel}
\text{name_feed1=on construit le tableau de signe correct,
  en remarquant que,
  est toujours strictement,
  en factorisant,grâce à l'identité remarquable}
\text{name_remember=A retenir}
# endif
#endif
#if defined TARGET_signeProdQuotient
\text{name_question=Construire le tableau de signes de la fonction \(f\) définie}
\text{name_forall=pour tout \(x\) réel tel que}
\text{name_by=par}
\text{name_on=sur}
#endif
#if defined TARGET_signeProdQuot2
\text{name_question=Étudier en fonction de \(x\) le signe}
\text{name_produit=du produit,du quotient}
#endif
#if defined TARGET_ineqQuotient || defined TARGET_ineqQuotient2 || defined TARGET_ineqQuotient3
\text{name_question=Résoudre algébriquement sur \(\RR\;\) l'inéquation (1)}
\text{name_with=avec}
\text{name_question2=L'inéquation (1) équivaut à l'inéquation suivante }
\text{name_enonce1=On a montré que résoudre (1) équivaut à résoudre l'inéquation (2)}
#endif
#if defined TARGET_ineqQuotient
\text{name_and=et}
\text{sujquest1=Numérateur dans l'inéquation (2)}
\text{name_binome=les binômes du premier degré suivants}
\text{name_question3=On étudie le signe du quotient XXXX en fonction de \(x\).
  On obtient le tableau suivant}
\text{name_question4=D'après le tableau de signe, l'ensemble des solutions de (1) et (2) est}
\text{name_def=On définit les ensembles suivants}
\text{name_feed1=Vous vous êtes trompés dans l'expression du numérateur de l'inéquation (2).}
\text{name_feed2=Reprenez attentivement les calculs et cherchez votre erreur.
 Avez-vous travaillé avec une inégalité dans le même sens que celui imposé par l'énoncé ;
  avez-vous correctement réduit au même dénominateur, avez-vous correctement distribué
  les signes dans une somme, etc}
#endif
#if defined TARGET_ineqQuotient2 || defined TARGET_ineqQuotient3
\text{name_form=forme développée,forme factorisée}
\text{name_brouillon=Faire <span class="enrouge">sur papier libre</span> l'étude des signes du quotient}
\text{name_question3=Ensuite, dans la liste suivante, cocher tous les intervalles
  dont la réunion est l'ensemble des solutions de l'inéquation (1)}
# if defined TARGET_ineqQuotient2
\text{expl1 = Forme développée du numérateur dans (2)}
\text{expl2 = Forme factorisée du numérateur dans (2)}
# endif
# if defined TARGET_ineqQuotient3
\text{name_numerateur=On peut réécrire le numérateur \(u(x)\) sous forme canonique }
\text{name_question4=Que peut-on dire du numérateur}
\matrix{name_enonce2=On constate que le numérateur,ne se factorise pas et garde un signe constant.
  On constate que le numérateur se factorise en}
# endif
#endif
