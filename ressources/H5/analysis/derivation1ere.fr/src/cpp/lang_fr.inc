#if defined TARGET_deriverComp || defined TARGET_deriverInvRac || defined TARGET_deriverPoly
\text{name_answer=Dérivée}
#endif
#if defined TARGET_deriverComp || defined TARGET_deriverInvRac
\text{name_write=Écrire}
\text{name_for=pour}
#endif
#if defined TARGET_varInvRac ||  defined TARGET_deriverInvRac || defined TARGET_deriverComp || defined TARGET_deriverComp
\text{name_feed=L'expression de la dérivée est}
#endif
#if defined TARGET_varInvRac
\text{name_answer=Sens de variation sur}
\text{name_choix=strictement croissante, strictement décroissante, non définie}
\text{name_enonce=La fonction \(f\) est définie sur,par}
\text{name_question=Sur l'intervalle,la fonction \(f\) est}
\text{name_hint1=La fonction racine \( sqrt(u)\) est dérivable sur tout intervalle \(I\)
  où la fonction \(u\) est strictement positive et dérivable.
<br> La fonction \(u\) et sa racine carrée \( sqrt(u)\) ont
  donc les mêmes sens de variation sur \(I\).}
\text{name_hint2=La fonction inverse \( 1 / u \) est dérivable sur tout intervalle \(I\)
  où la fonction \(u\) ne s'annule pas et est dérivable.
<br> La fonction \(u\) et son inverse \( 1/u\) ont
  donc des sens de variation contraires sur \(I\).}
\text{name_hint3=Les fonctions \(u^2\) et \(u\) ont les mêmes sens de variation
  sur tout intervalle \(I\) où la fonction \(u\) est positive.
<br> Les fonctions \(u^2\) et \(u\) ont des sens de variation
  contraires sur tout intervalle \(I\) où la fonction \(u\) est négative.}
#endif
#if defined TARGET_deriverComp
\text{name_question=Calculer la dérivée de la fonction \(f\) définie sur, par}
\text{name_hint=Soit \(f\) la composée de la fonction affine \(x\mapsto a x+b\)
  suivie de la fonction \(u\). <br> Si, lorsque \(x\) varie dans l'intervalle \(I\)
  les valeurs \(a x+b\) varient dans un intervalle \(J\) où la fonction \(u\) est dérivable, alors \(f\) est dérivable
  sur \(I\) et \(f'(x) = a u'(a x+b) \). }
#endif
#if defined TARGET_deriverInvRac
\text{name_hint1=La fonction racine \( sqrt(u)\) est dérivable sur tout intervalle \(I\)
  où la fonction \(u\) est strictement positive et dérivable.
  <br> Alors on a sur  l'intervalle \(I\) : \( ( \sqrt{u} )' = \frac{u' }{2 \sqrt{u}}\).
  <br> La fonction \(u\) et sa racine carrée \( sqrt(u)\) ont donc les mêmes
  sens de variation sur \(I\).}
\text{name_hint2=La fonction inverse \( 1 / u \) est dérivable sur tout intervalle \(I\)
  où la fonction \(u\) ne s'annule pas et est dérivable.
  <br> Alors on a sur l'intervalle \(I\) : \( ( 1 / u )' = - \frac{u' }{u^2} \).
  <br> La fonction \(u\) et son inverse \( 1/u\) ont donc des sens
  de variation contraires sur \(I\).}
\text{name_enonce=La fonction \(f\) définie par, est dérivable sur}
\text{name_onehas=On a}
#endif
#if defined TARGET_deriverPoly || defined TARGET_deriverPolys
\text{name_ifthen=Si,alors}
#endif
#if defined TARGET_deriverPolys
\text{name_hint=On utilise les règles de dérivation suivantes,
  Dérivée d'une somme, Dérivée d'un monôme,En particulier}
#endif
#if defined TARGET_deriverPoly
\text{name_enonce= Soit \(f\) la fonction polynôme définie sur \(\,\RR\) par,
  La fonction \(f\) est dérivable sur}
\text{name_question=Calculer sa fonction dérivée.}
\text{name_forall=Pour tout réel}
\text{name_hint=On utilise les règles de dérivation suivantes,
  Pour dériver un polynôme, on dérive donc terme à terme.,
  On remarquera&nbsp;}
#endif
#if defined TARGET_varTrinome
\text{name_enonce=Soit la fonction \(f\) définie sur \(\,\RR\) par}
\text{name_question=Étudier le sens de variation de \(f\).
  Déterminer le(s) extremum(s) de \(f\).}
\text{name_question1=La fonction \(f) est dérivable sur,
  Pour tout réel \(x\), La fonction dérivée \(f') s'annule en}
\text{name_answer=Nombre dérivé,s'annule en, Signe de,
  Nature de l'extremum,Valeur de l'extremum de,Dérivée de,
  Sens de variation de,Extremum de}
\text{name_hint=Si la fonction \(f\) change de sens de variation en,
  on dit que, est un extremum "local" de}
\text{name_question2=est strictement,sur l'intervalle}
\text{name_choix=croissante,décroissante}
\text{name_question3=atteint en, dont la valeur est}
\text{choix7=un minimum,un maximum}
#endif
#if defined TARGET_varPolydeg3
\text{name_enonce=Soit \(f\) la fonction définie par,sur l'intervalle}
\text{name_question1=Calculer,sous forme développée}
\text{name_repquest=Réponse à la question}
\matrix{name_question2=Le calcul de dérivée donne
  On admet que \(f'(x)\) s'écrit sous forme factorisée (produit) comme suit
  Compléter le tableau de signes de}
\text{name_inst=Sélectionner une icône dans la liste ci-dessous
  et la glisser-coller dans une case.}
\text{name_answer=Signe de,var. de, Extremum}
\matrix{name_question3=L'étude de signes de la dérivée, donne les résultats consignés dans le tableau ci-dessous.
  Complétez ce tableau pour indiquer le <b>sens de variation</b> de la fonction}
\text{name_quest=Question}
\text{name_question4=Le tableau complet des variations
  de la fonction \(f\) est rapporté ci-dessous.}
\text{name_question41=D'après ce tableau, le XXXX de la fonction \(f\) est,
  et ce XXXX est atteint pour}
#endif
#if defined TARGET_nbdergraph || defined TARGET_nbdergraph2
\text{name_enonce=Le plan est rapporté au repère,
La <span style="color:blue">courbe CCCC</span> représente la
<span style="color:blue">fonction \(f\)</span> définie sur,
<span style="color:green">La droite \(T\)</span> est la tangente à CCCC au point \(A\) de coordonnées}
\text{name_hint=Le nombre dérivé \(f'(a)\) est le coefficient directeur (la pente) de la tangente
  \(T_a\) à la courbe représentative de \(f\) au point d'abscisse \(a\).}
\text{name_answer=Nombre dérivé}
\text{name_feed1=Vous vous êtes trompé sur le signe du coefficient directeur
  de la tangente. Si la fonction est croissante au voisinage de
  , alors la tangente \(T\) "monte" et, est de signe positif.
  Si la fonction est décroissante au voisinage de,
  alors la tangente \(T) "descend" et, est de signe négatif.
}
\text{name_feed2=Le nombre dérivé, est le coefficient directeur \(m\) de la droite \(T\)
  et \(m\) est égal à l'accroissement moyen \(\frac{\Delta y}{\Delta x} = \frac{y_B - y_A}{
x_B - x_A} = MMMM\) (voir flèches rouges sur le graphique). L'arrondi au dixième est }
# if defined TARGET_nbdergraph
\text{name_question=Sachant que \(T\) passe aussi par le point \(B\) de coordonnées,
  calculer la valeur de, arrondie au dixième.}
# endif
# if defined TARGET_nbdergraph2
\text{name_question=On sait de plus que \(T\) passe aussi par le point \(B\) de coordonnées,
  Quelle valeur de la fonction dérivée \(f'\) peut-on en déduire&nbsp;,
  Donner cette valeur arrondie au dixième.}
# endif
#endif
#if defined TARGET_deriverProduit
\text{name_question=Calculez la dérivée de la fonction définie, sur,par,avec&nbsp;}
\text{name_question1=Les fonctions \(u) et \(v) sont dérivables sur \(\,\RR)}
\text{name_question2=On applique la formule de dérivation&nbsp;,
  La dérivée mise sous forme polynomiale développée est&nbsp;}
\text{name_answer=Nombre dérivé,Formule de dérivation}
\text{name_sol=Solution.,
  La forme développée de \(f'(x)\) est,
  La forme factorisée de \(f'(x)\) est}
#endif
#if defined TARGET_deriverQuotient
\text{name_answer=Le numérateur \(u\) est défini par,
  Le dénominateur \(v\) est défini par,
  Dérivée du numérateur,
  Dérivée du dénominateur,
  Ensemble de dérivation,
  Formule de dérivation,
  La dérivée \(f'\) est définie par}
\text{name_feed=Solution.,
  La fonction dérivée \(f'\) est définie pour tout réel \(x\),
  différent de, par,forme factorisée}
\text{name_enonce=On donne la fonction \(f\) définie sur,par,
  Nous allons calculer \(f'(x)\) par étapes.}
\text{name_question1=On peut écrire \(f) comme un quotient \(\frac{u}{v}),
  où les fonctions \(u\) et \(v\) sont définies sur \(\,\RR\) par}
\text{name_and=et}
\text{name_question2=Les fonctions \(u\) et \(v\) sont dérivables sur }
\text{name_with=avec}
\text{name_question3=La fonction quotient, est dérivable sur}
\text{name_question4=On applique la formule de dérivation&nbsp;}
\text{name_oneget=On obtient alors}
#endif
