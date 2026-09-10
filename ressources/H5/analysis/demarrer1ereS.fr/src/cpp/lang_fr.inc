#if defined TARGET_droite1
\text{NameCoul=rouge,orange,vert}
\text{name_enonce=Le plan \(\RR^2\) est muni d'un repère orthonormé}
\text{name_question=Quel est le coefficient directeur de la droite \(D\)
  dessinée en}
\text{name_question2=Le coefficient directeur de la droite \(D\) est&nbsp;}
#endif
#if defined TARGET_droite2
\text{name_and=et}
\text{choix=parallèles,non parallèles,colinéaires,non colinéaires}
\text{name_enonce1=Dans un repère \((O,\vec{i},\vec{j})\) donné du plan,
on considère les quatre points&nbsp;}
\text{name_enonce2=On se propose de déterminer <b>par calcul vectoriel</b>
  si les droites \((A B)\) et \((C D)\) sont parallèles.}
\text{name_question=Le vecteur,a pour coordonnées&nbsp;,
  Existe-t-il un réel \(k\) tel que}
\text{name_inst=Si <span style="color:green">oui,
  donnez la valeur exacte de \(k\)</span>,
  <span style="color:red">sinon, entrez la valeur 0</span>.}
\text{name_question2=Les droites \((A B)\) et \((C D)\) sont donc}
\text{name_answer=Abscisse,Ordonnée,Coefficient,Droites}
\text{name_hint1=Montrer que les droites \((A B)\) et \((C D)\) sont parallèles
  équivaut à montrer que les vecteurs \(\overrightarrow{A B}\) et
  \(\overrightarrow{C D}\) sont colinéaires.}
\text{name_hint2=Les vecteurs \(\overrightarrow{A B}\) et \(\overrightarrow{C D}\)
  sont colinéaires si et seulement si il existe un réel \(k\) tel que}
#endif
#if defined TARGET_droite3
\matrix{name_choix=verticale,non verticale
  égales,distinctes
  ne peut pas,peut
  l'une des droites est verticale mais l'autre non,les deux droites sont verticales,aucune droite n'est verticale et il faut calculer les coefficients directeurs
  les droites sont parallèles,les droites ne sont pas parallèles}
#endif
#if defined TARGET_expression1
\text{name_enonce=Cliquer sur les expressions affines,
  c'est-à-dire celles qui sont du premier degré.}
#endif
#if defined TARGET_expression2
\text{name_enonce=Cocher les expressions quadratiques,
  c'est-à-dire celles qui sont du second degré.}
#endif
#if defined TARGET_expression3
\text{name_enonce=Cocher les expressions qui se présentent
  comme des carrés d'autres expressions.}
#endif
#if defined TARGET_expression4
\text{name_enonce=Dans le plan muni d'un repère orthonormé \((O,i,j)\),
 associer chaque droite dessinée dans la colonne de gauche à son équation.}
\text{name_hint1=Faire un premier tri en regardant l'ordonnée
  à l'origine des droites de la colonne de gauche.
  L'ordonnée à l'origine d'une droite \(D\) correspond à la valeur
  que prend \(y\) lorsque l'on pose \(x=0\) dans l'équation de \(D\).}
\text{name_hint2=Si ce premier tri ne suffit pas à départager deux droites,
  considérer le coefficient directeur (la pente) de la droite,
  qui est le coefficient de la variable \(x\) dans l'équation de la droite.}
\text{name_answer=Correspondance droite/equation}
#endif
#if defined TARGET_expression5
\text{name_enonce=Cocher les expressions qui sont factorisées
<span style="color:red">au maximum</span> et dont les facteurs sont
<span style="color:red">au plus de degré deux</span>.}
#endif
#if defined TARGET_expression6
\text{name_statement=L'expression suivante est un polynôme de
  degré deux, écrit sous forme quelconque.}
\matrix{name_question=Soit, la forme développée réduite de
  Par <strong>calcul mental</strong> uniquement, calculer }
\text{name_coeff=le coefficient,de,le terme constant}
#endif
#if defined TARGET_expression7
\text{name_statement=On suppose que la variable \(x\) varie dans l'intervalle,
  Déterminer les intervalles dans lesquels varient respectivement
  les expressions suivantes.}
\text{name_variation=varie dans l'intervalle}
#endif
#if defined TARGET_signe1 || defined TARGET_signe2
\text{name_question=Compléter le tableau de signes de}
#endif
#if defined TARGET_signe1
\text{name_statement=En quelle valeur de \(x\) le binôme du premier degré,
  s'annule-t-il&nbsp;, pour}
\text{name_statement2=Le binôme du premier degré, s'annule pour}
\text{name_hint=Le binôme du premier degré \(a x+b\) s'annule en ,
  et change de signe,
  Il est du signe du coefficient \(a\) lorsque}
#endif
#if defined TARGET_signe3
\text{choix1=une constante, un carré multiplié par une constante,
  une somme de deux expressions positives, une somme de deux expressions négatives}
\text{choix2=strictement négative,négative ou nulle,strictement positive,
  positive ou nulle}
\text{name_enonce=L'expression, a un signe évident quel que soit le réel}
\text{name_enonce2=En effet \(f(x)\) s'écrit sous la forme,
  Par conséquent \(f(x)\) est toujours}
#endif
#if defined TARGET_signe4
\text{name_msg=les zéros du produit ne sont pas marqués,
  la valeur interdite du quotient n'est pas marquée}
\text{name_prod=produit,quotient}
\matrix{name_choix=Le tableau est correct
  Les valeurs qui annulent,et , sont mal ordonnées
  L'étude de signe de, est fausse,
  Les signes du \produit \(f(x)) sont faux}
\text{name_enonce=Un élève a dressé le tableau suivant pour étudier le signe
  de la fonction \(f\) définie par,
  Ce tableau est-il correct, Sinon quelle erreur a-t-elle été commise&nbsp;}
#endif
#if defined TARGET_signe5
\text{name_enonce=Un élève a dressé le tableau suivant pour étudier
  le signe de la fonction \(f\) définie par&nbsp;}
\text{name_choix=L'élève a correctement dressé le tableau de signe de \(f(x)\).,
  L'élève n'a pas factorisé complètement \(f(x)\).,
  L'élève a oublié qu'un facteur de \(f(x)\) est élevé au carré.,
  L'élève n'a pas vu qu'un facteur de \(f(x)\) a un signe évident constant.,
  L'expression \(VVVV\) du tableau n'est pas un facteur de \(f(x)\).,
  L'élève a oublié de marquer une valeur interdite.}
\text{name_choix2=\(WWWW\) n'est pas un facteur de \(f(x)\).}
\matrix{name_question=A-t-il raison
  Sinon, cochez toutes les erreurs qu'il a commises.}
\text{name_posneg=positif,négatif}
\text{name_retain=À retenir}
\text{name_feed2=on construit le tableau de signe correct
  en remarquant que, est toujours strictement, pour tout réel}
\text{name_feed3=on construit le tableau de signe correct
  en factorisant, grâce à l'identité remarquable}
#endif
#if defined TARGET_terminologie1

\text{name_enonce=Choisir le bon terme dans les énoncés suivants.}
\matrix{phrases= &#171; <span style="color:blue"> \(UUUU = (VVVV)^2\)</span> &#187; est une
 &#171; <span style="color:blue">il existe un seul réel \(x\), tel que \( UUUU = VVVV\)</span> &#187; est une
 Dans &#171; <span style="color:blue">\(VVVV\) est une somme</span> &#187;, le sujet est une
 Dans &#171; <span style="color:blue">calculer les racines de \(WWWW\)</span> &#187;, le complément du mot "racines" est une
 Dans &#171; <span style="color:blue">l'ensemble des solutions de \(E\) est vide</span> &#187;, la lettre E doit désigner une
 &#171; <span style="color:blue">\(w\) change de signe deux fois</span> &#187; est une
 &#171; <span style="color:blue"> \( UUUU = VVVV\) \(\Longleftrightarrow \)\( x = \sol\) </span> &#187; est une
 le premier membre de l'égalité &#171; <span style="color:blue"> \(f(x) = 0\)</span> &#187; est une
 écrire &#171; <span style="color:blue"> \(WWWW\) \(\Longleftrightarrow\) 0</span> &#187; est incorrect, car \(WWWW) est une
}
\text{liste=expression, équation, proposition }
#endif
#if defined TARGET_terminologie2 || defined TARGET_terminologie3
\text{name_instruction=Pour associer deux cases, cliquer sur l'une puis sur l'autre.}
\text{name_enonce=Associer chaque énoncé de la colonne de gauche à son
  écriture mathématique.}
#endif
#if defined TARGET_terminologie3
\text{name_and=et}
\text{name_enonce0= désignent des fonctions qu'on suppose définies
  sur un intervalle commun}
#endif
#if defined TARGET_terminologie2
\text{allenonces=\(x\) appartient à l'intervalle \(I\),
  \(x\) n'appartient pas à l'intervalle \(I\),
  L'ensemble \(E\) est vide,
  Les intervalles \(I\) et \(J\) sont disjoints,
  \(x\) appartient à \(I\) et à \(J\),
  \(I\) est inclus dans \(J\) ou égal à \(J\),
  \(I\) est strictement inclus dans \(J\),
  \(x\) appartient à \(I\) ou à \(J\),
  \(J\) ne contient pas \(I\),
  \(I\) est l'intervalle fermé de \(a\) à \(b\),
  \(x\) est strictement inférieur à \(a\),
  \(x\) est inférieur ou égal à \(a\),
  \(x\) est strictement supérieur à \(a\),
  \(x\) est supérieur ou égal à \(a\),
  \(x\) est compris entre \(a\) et \(b\),
  \(x\) est compris entre \(a\) et \(b\),
  \(I\) est l'intervalle ouvert de \(a\) à \(b\),
  \(x\) est positif ou nul,
  \(x\) est strictement positif,
  La fonction \(f\) s'annule en \(a\),
  Les zéros de la fonction \(f\) sont \(a\) et \(b\)}
#endif
#if defined TARGET_terminologie3
\text{allenonces= \(f\) est le produit de \(u\) et de \(v\),
\(f\) est \(k\) fois le produit de \(u\) et de \(v\),
\(f\) est la somme de \(u\) et de \(v\),
\(f\) est \(k\) fois la somme de \(u\) et de \(v\),
\(f\) est la différence de \(u\) par \(v\),
\(f\) est le quotient de \(u\) par \(v\),
\(f\) est le carré de \(u\),
\(f\) est le cube de \(u\),
\(f\) est la racine carrée de \(u\),
\(f\) est le double de \(u\) augmenté de \(v\),
\(f\) est le triple de \(v\) augmenté de \(u\),
\(f\) est la somme du carré de \(u\) et du tiers de \(v\),
\(f\) est \(k\) fois l'inverse de \(v\),
\(f\) est le carré de la somme de \(u\) et de \(v\),
\(f\) est l'inverse de la somme de \(u\) et de \(v\),
\(f\) est \(k\) fois \(u\) divisé par \(v\) au carré,
\(f\) est \(k\) fois \(u\) divisé par la racine carrée de \(v\),
\(f\) est le carré de la somme de \(u\) et de \(v\),
\(f\) est le carré du quotient de \(u\) par \(v\),
\(f\) est le cube de la différence de \(u\) et de \(v\)}
#endif
