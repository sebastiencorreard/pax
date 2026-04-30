\text{name_at=en}
\text{name_and=et}
\text{name_in=dans}
\text{name_by=par}
\text{name_name_has=a}
#if defined TARGET_antecedent
\text{name_choix=est, n'est pas}
\text{name_hint=<p>Le nombre \(x\) est un
  <span style="color:blue">antécédent</span> du nombre \(y\) par la fonction
  \(f\) si et seulement le point de coordonnées \((x, y)\) est situé sur
  la courbe représentative de \(f\).
  Autrement dit, \(x\) est un antécédent de \(y\) par \(f\) lorsque \(f(x) = y\).
  </p><p>
  S'il y a une <span style="color:blue">infinité d'antécédents</span>
  pour \(y\), écrire <span class="tt">infinité</span> dans le champ de réponse.</p>}
\text{name_answer=antécédent de,dans}
\text{name_enonce=Dans le plan muni du repère (0; I, J),
  la fonction \(f\) est représentée sur, l'intervalle, l'ensemble,
  par la courbe.}
\text{name_precision=On précise que \(C\) passe par
  le point de coordonnées}
\matrix{name_question=De l'énoncé et du graphique, on déduit les propriétés suivantes
  est un antécédent de , par la fonction
  un antécédent de , dans \(I) par la fonction
  admet, antécédent(s) dans \(I\) par la fonction
  L'équation, admet exactement, solution(s) dans l'intervalle }
\text{name_sol1=est, un antécédent de,car d'après l'énoncé}

\text{name_sol2=La droite d'équation,
  intersecte la courbe représentative de \(f\) en,
  un seul point,
  une infinité de,points,
  sur l'ensemble \(I\) où \(f\) est définie. Donc,
  a exactement,
  un seul antécédent,
  une infinité d'antécédents,
  antécédents,
  n'a aucun point d'intersection,
  a exactement,
  point(s) d'intersection,
  avec la courbe représentative de \(f) sur l'ensemble \(I\). Donc l'équation,
  n'a aucune solution,
  solution(s)}
\text{name_has=a}
\text{name_sol3=On effectue les constructions graphiques ci-contre
  pour justifier les réponses.}
\text{name_car=car}
\text{name_by=par}
\text{name_in=dans}
\text{name_has=a}
#endif
#if defined TARGET_image
\text{name_hint=L'image du nombre réel \(x\) par la fonction \(f\)
  est <i>l'ordonnée </i> du point d'abscisse \(x\) situé sur la
  courbe représentative de \(f\).}
\text{name_answer=Partie entière de,Entier plus grand}
#endif
#if defined TARGET_resoGraphEq1 || defined TARGET_resoGraphEq2
\text{name_hint=Résoudre graphiquement l'équation \(f(x) = g(x)\),
  c'est chercher les <span style="color:red">abscisses</span>
  des points d'intersection de la <span style="color:blue">
  courbe représentant \(f\)</span> avec la
  <span style="color:green">courbe représentant \(g\)</span>.}
\text{name_answer=Les solutions de l'équation sont}
\text{name_feed1=Les réponses doivent être entières.}
\text{name_feed2=Les solutions de l'équation \(f(x)=g(x)\) se lisent comme
  suit sur le graphique}
\text{name_arrondi=Erreur d'arrondi}
\text{name_cond=Vous avez trouvé au moins une solution}
#endif
#if defined TARGET_resoGraphEq1 || defined TARGET_resoGraphEq2
\text{name_enonce1=Le plan est rapporté au repère (O ; I, J).
  Dans ce repère, la <span style="color:blue">courbe bleue</span>
  représente une <span style="color:blue">fonction \(f\)</span>
  définie sur \(\,\RR\) et <span style="color:green">la courbe verte</span>
  représente <span style="color:green">une fonction \(g) </span> définie sur \(\RR\).}
\matrix{name_enonce2=Résolvez graphiquement l'équation \(f(x) = g(x)\) sur l'intervalle
  Déterminez les valeurs arrondies à l'unité des solutions.
  Entrez les valeurs ci-dessous, en séparant deux valeurs par une virgule.}
\text{name_question=L'ensemble des solutions est}
#endif
#if defined TARGET_resoGraphIn1
\text{name_hint=Pour résoudre graphiquement l'inéquation \(f(x) < k\)
(resp. \(f(x) \leq k\)\), on localise les points de la
<span style="color:blue">courbe représentant \(f\)</span>
situés strictement en-dessous de (resp. en dessous de ou sur)
<span style="color:green">droite horizontale d'équation \(y=\k\)</span>.
Les solutions sont les abscisses de ces points.}
\text{name_answer=L'ensemble des solutions est}
\text{name_sol=Solution.}
\matrix{name_feed=Comme l'inégalité est large les abscisses des points d'intersection sont aussi solution.
Comme l'inégalité est stricte les abscisses des points d'intersection ne sont pas solution.}

\text{name_feed1=Votre réponse contient une incohérence. }
\text{name_feed2=Si, était l'ensemble des solutions,
  alors la courbe bleue serait entièrement située <i>en-dessous</i>
  de la droite verte. Le graphique montre le contraire.}
\text{name_feed3=Si l'ensemble était vide (\(\,\emptyset\)),
  alors l'inégalité ne serait jamais vérifiée et
  la courbe bleue serait entièrement située <i>au-dessus</i>
  de la droite verte. Le graphique montre le contraire.}
#endif
#if defined TARGET_resoGraphIn1 || defined TARGET_resoGraphIn2 || defined TARGET_resoGraphIn3
\text{name_feed=D'après le graphique, l'ensemble des solutions de l'inéquation,
  est indiqué en rouge sur l'axe des abscisses}
\text{name_courbe=la courbe,la droite}
\text{name_set=On définit les ensembles suivants }
  a verifier
#endif
#if defined TARGET_resoGraphIn2 || defined TARGET_resoGraphIn3
\text{name_hint=Le nombre réel \(x\) est solution de l'inéquation
  \(f(x) < g(x)\) (resp. \(f(x)\) \le \(g(x)\)) si et seulement
  s'il est l'abscisse d'un point de la <span style="color:blue">courbe
  représentative de \(f\)</span> qui est situé strictement en dessous
  (resp. en dessous ou sur) la <span style="color:green">
courbe représentative de \(g\)</span>.}
\text{name_answer=Plus grand(s) intervalle(s) inclus}
\text{name_inst=Cocher toutes les réponses s'il y en a plusieurs.}
\text{name_question=D'après le graphique, quel(s) est(sont) le(s) plus grand(s)
  intervalle(s) inclus dans}
#endif
#if defined TARGET_resoGraphIn1
\text{name_enonce0=Soit \(f\) une fonction définie sur}
\text{name_enonce1=Dans le plan muni du repère (O; I, J), la
  <span style="color:blue">courbe bleue</span> d'équation \(y = f(x)\) croise
  <span style="color:green">la droite</span> d'équation}
\text{name_question=D'après le graphique, on a}
#endif
#if defined TARGET_resoGraphIn2
\text{name_enonce1=Dans le plan muni du repère (O; I, J),
  <span style="color:blue">
  FFFF</span> d'une <span style="color:blue">fonction \(f\)</span> et
  <span style="color:green">GGGG en vert</span>
  celle d'une <span style="color:green">fonction \(g\)</span>.
  <br> Les fonctions \(f\) et \(g\) sont définies sur}
#endif
#if defined TARGET_resoGraphIn1 || defined TARGET_resoGraphIn2
\text{name_enonce2=Leurs courbes se croisent,aux points d'abscisses,
  au point d'abscisse}
#endif
#if defined TARGET_resoGraphIn1 || defined TARGET_resoGraphIn3
\text{name_enonce3=Soit \(\mathcal{S}\) l'ensemble des solutions de l'inéquation}
#endif
#if defined TARGET_resoGraphIn3
\text{name_enonce0=La fonction <span style="color:blue">\(f\)</span> est définie sur}
\text{name_enonce1=Elle est représentée dans le repère (O ; I, J)
  par <span style="color:blue">FFFF en bleu</span> ;
  <span style="color:green">GGGG en vert</span> est la
  représentation graphique d'une fonction affine
  <span style="color:green">\(g\)</span>.}
\matrix{name_tangente=Ces courbes sont tangentes au point d'abscisse
  Ces courbes sont tangentes au point d'abscisse,et se croisent au point d'abscisse}
#endif
#if defined TARGET_signe
\text{name_answer=Nombre de zéro(s)}
\text{name_hint=<p>On recherche les plus grands intervalles sur lesquels la fonction \(f\) garde un signe constant.</p>
  <p>La fonction \(f\) est strictement positive sur l'intervalle \(I\) si et seulement si \(f(x)>0\) pour tout \(x\) de \(I\).
   Graphiquement cela signifie que, sur \(I\), la courbe de \(f\) est
   au-dessus de l'axe des abscisses sur \(I\).</p>
  <p>\(f\) est strictement négative sur l'intervalle \(I\) si et seulement si \(f(x)<0\) pour tout \(x\) de \(I\).
  Graphiquement cela signifie que, sur \(I\), la courbe de \(f\) est
  en-dessous de l'axe des abscisses sur \(I\).</p>
  <p>\(f(x)\) s'annule en \(x\) si et seulement si \(f(x)=0\).
  Graphiquement cela signifie que la courbe de \(f\) croise
  l'axe des abscisses au point d'abscisse \(x\).</p>}
\matrix{name_enonce=La représentation graphique d'une fonction \(f\) définie sur
  est donnée dans le repère (O ; I, J) ci-contre.}
\text{name_hyp=On admet que la fonction \(f\) ne change pas de sens de variation
  en dehors du graphique.}
\text{name_question=Répondre aux questions suivantes par lecture graphique.}
\matrix{name_question1=Combien l'équation \(f(x) = 0\) a-t-elle de solutions dans
  L'équation \(f(x) = 0) n'a aucune solution dans
  Compléter le tableau de signes de
  La fonction \(f\) n'est pas définie en
  L'équation \(f(x) = 0\) a une unique solution
  La valeur arrondie au dixième de \(x_0\) est
  L'équation \(f(x) = 0\) a deux solutions
  Les valeurs arrondies de \(x_1\) et \(x_2\) sont respectivement
  L'équation \(f(x) = 0) a trois solutions
  Les valeurs arrondies de \(x_1\), \(x_2\) et \(x_3\) sont respectivement}
  \text{name_inst=Choisir <span class="tt">X</span> si on ne peut pas conclure.}
#endif
