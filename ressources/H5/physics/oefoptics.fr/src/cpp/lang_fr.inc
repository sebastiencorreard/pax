\text{Conv= \confparm1=1 ? convergente:}
\text{Conv= \confparm1=2 ? divergente}
\text{name_warning=Il s'agit d'un entier.}
#if defined TARGET_optique1
\text{question=convergente,divergente}
\text{name_instruction=Dans le système optique suivant formé d'une lentille
  mince de centre optique \(O), la lentille est}
\text{name_answertext=Convergence}
#endif
#if defined TARGET_optique2
\text{question=objet réel, objet virtuel,image réelle, image virtuelle}
\text{name_instruction= Dans le système optique suivant formé d'une
  lentille mince \Conv de centre optique \(O), le bâton de couleur \coul est un}
\text{name_answertext=Nature}
#endif
#if defined TARGET_optique3
\text{question=réelle droite,réelle renversée, virtuelle droite, virtuelle renversée}
\text{name_instruction= Dans le système optique suivant formé d'une
  lentille mince \Conv de centre optique \(O), l'image du bâton de couleur \coul est}
\text{name_answertext=Image}
#endif
#if defined TARGET_optique3cv2
\text{name_instruction= Dans le système optique suivant formé d'une
  lentille mince \Conv de centre optique \(O), tracer l'\question de l'objet}
#endif
#if defined TARGET_optique3cv
\text{name_instruction= Dans le système optique suivant formé d'une
  lentille mince \Conv de centre optique \(O), cliquer sur
  l'\question du point}
#endif
#if defined TARGET_foyer
\text{name_instruction=Quelle est la distance focale du système optique suivant
  formé d'une lentille mince \Conv de centre optique \(O)&nbsp;}
\text{name_answertext=Distance focale}
#endif
#if defined TARGET_foyercalcul
\text{name_instruction=On considère une lentille mince \Conv de centre optique \(O). Un objet \(A B)
  perpendiculaire à l'axe optique a comme image \(A'B') où }
\text{name_instruction2=Calculer \(\overline{O A'}), \(\overline{O A}) et la distance focale.}
\text{name_answertext=Distance focale}
\text{\name_length=est de longueur}
#endif
#if defined TARGET_foyercv
\text{name_instruction=Cliquer sur le foyer \question du système optique suivant formé
  d'une lentille mince \Conv de centre optique \(O).}
#endif
#if defined TARGET_optique4
\text{name_instruction=Voici un objet \(A B) et son image \(A'B') par un système
  optique formé d'une lentille mince \Conv.}
\text{name_instruction1=Donner l'abscisse du centre optique de la lentille&nbsp;}
\text{name_instruction2=La lentille a été placée dans le dessin suivant.
  Calculer sa distance focale.}
\text{name_answertext=Centre optique,Distance focale}
#endif
#if defined TARGET_optique2cv
a supprimer
text{name_instruction=Voici un système optique suivant formé
  d'une lentille mince \Conv de centre optique \(O).}
text{name_instruction1=Le rayon va bifurquer et prendre une autre direction
  portée par une droite. Cliquer sur le point de la droite verticale x=\b
  qu'il va croiser.}
#endif

#if defined TARGET_optique2cv
\text{question=objet réel, objet virtuel,image réelle, image virtuelle}
\text{name_instruction=Dans le système optique suivant formé d'une lentille
  mince convergente de centre optique \(O), le bâton de couleur \coul est un}
\text{name_answertext=Nature}
#endif
#if defined TARGET_optique4cv
\text{name_instruction=Voici un objet \(A B) et son image \(A'B') par un
  système optique formé d'une lentille mince convergente.}
\text{name_instruction1=Donner l'abscisse du centre optique de la lentille&nbsp;}
\text{name_instruction2=La lentille a été placée dans le dessin suivant.
  Calculer sa distance focale.}
\text{name_answertext=Centre optique,Distance focale}
#endif
