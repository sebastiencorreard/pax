#if defined TARGET_alignpts || defined TARGET_alignpts2
\text{name_hint=L'alignement des points \(A\), \(B\), \(C\) équivaut
  à la colinéarité des vecteurs}
\text{name_and=et}
\text{liste=alignés,non alignés}
\text{name_calcul=Composantes de }
\text{name_solution=Calculons les composantes des vecteurs}
#endif
#if defined TARGET_interobjplan || defined TARGET_interobjplan1 || defined TARGET_objspaequa
\matrix{oliste=sphère, cylindre de révolution, cône de révolution}
#endif
#if defined TARGET_interobjplan1
\matrix{natliste=ensemble vide, point, cercle, 1 droite, 2 droites}
# endif
#if defined TARGET_interobjplan1
\matrix{name_question=Donner les coordonnées de ce point.
Donner l'équation de ce cercle dans le plan (P).
Donner l'équation de cette droite dans le plan (P).
Donner l'équation de chacune des droites dans le plan (P).}
\text{name_answer=nature de l'intersection,
  abscisse, ordonnée, côte,cercle,droite,
  première droite,deuxième droite  }
#endif
#if defined TARGET_vectcoplan
\text{liste=coplanaires,non coplanaires}
#endif
#if defined TARGET_vectcoplan || defined TARGET_alignpts || defined TARGET_alignpts2
\text{name_textsol=Les composantes des vecteurs sont proportionnelles,
  donc les points sont alignés.,
  Les composantes des vecteurs ne sont pas proportionnelles,
 donc les points ne sont pas alignés.}
#endif
#if defined TARGET_vectcoplan2
\text{name_enonce=On considère les vecteurs \(\overrightarrow{u}\), \(\overrightarrow{v}\)
  et \(\overrightarrow{w}\) dont les composantes dans un repère donné sont respectivement}
\text{name_question=Déterminer le réel \(t\) tel que les vecteurs soient coplanaires.}
#endif
#if defined TARGET_correspobjspace
\matrix{oliste= sphère, cylindre de révolution, cône de révolution}
\text{name_enonce=Dans l'espace muni d'un repère orthonormé
  \((O,\overrightarrow{i},\overrightarrow{j},\overrightarrow{k})\), associez à chacun
  des objets ci-dessous son équation.}
\text{name_answer=Correspondance objet/equation}
#endif
#if defined TARGET_dteaffesp
\text{liste=strictement parallèles, confondues, non coplanaires, sécantes}
#endif
#if defined TARGET_dteplanesp
\text{liste=incluse dans le plan, strictement parallèle au plan, sécante avec le plan}
#endif
#if defined TARGET_ptscoplan1
\text{name_choix=coplanaires,non coplanaires}
#endif
#if defined TARGET_nattriangle
\text{name_liste=isocèle,équilatéral,rectangle,isocèle rectangle,quelconque}
\text{name_instruction=On considère les points \(A\), \(B\) et \(C\)
  dont les coordonnées dans un repère donné sont respectivement}
\text{name_question=Déterminer la nature du triangle}
\text{name_answer=Votre réponse : le triangle est}
\text{name_solution=Calculons les composantes des vecteurs}
\text{textsol=Le triangle est}
\text{name_calcul=Composantes de }
#endif
#if defined TARGET_vectcube
\text{name_enonce=Les vecteurs, sont-ils coplanaires}
\text{name_and=et}
\text{replist=oui, non}
#endif
#if defined TARGET_vectcolin
\text{liste=colinéaires,non colinéaires}
\text{name_hint=La colinéarité est assurée si les composantes des vecteurs
  sont proportionnelles.}
\text{name_textsol1=Les composantes des vecteurs
  \(\overrightarrow{u}\) et \(\overrightarrow{v}\) sont proportionnelles&nbsp;,
  donc les vecteurs sont colinéaires.}
\text{name_textsol2=Les composantes des vecteurs
  \(\overrightarrow{u}\) et \(\overrightarrow{v}\) ne sont pas proportionnelles.
  Donc les vecteurs ne sont pas colinéaires.}
\text{name_enonce=Les vecteurs \(\overrightarrow{u}\) et \(\overrightarrow{v}\)
 dont les composantes dans un repère donné sont respectivement,
 sont-ils colinéaires&nbsp;}
\text{name_answer=Votre réponse&nbsp;: les vecteurs sont}

#endif
