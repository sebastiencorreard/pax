#if defined TARGET_prinj || defined TARGET_prcroiss
\text{name_increasing=croissante,décroissante}
\text{name_increasing2=croissance,décroissance}
#endif
#if defined TARGET_prinj
\text{name_imant=a une image, a un antécédent}
\text{name_g4=Par définition de la fonction réciproque}
\text{name_because=Parce que,Puisque,Comme}
\text{name_isfunction=est une fonction}
\text{name_donc=J'en déduis,Donc}
\matrix{name_prop=l'injectivité,la surjectivité,la bijectivité
  injective,surjective,bijective}
\text{name_statement=Soient \(\I,\J) deux intervalles, \(\f : \I \to \J)
  une fonction bijective, et soit \(\g : \J \to \I) sa réciproque.
  Composez une démonstration de l'injectivité de \(\g) à l'aide des
  phrases données plus bas.}
\text{name_step=Première étape,}
\text{name_sentence1=Soient ,tels que,Je dois montrer que }
#endif
#if defined TARGET_bijquad
\text{name_notf=n'est même pas définie sur }
\text{name_noj=est bien définie mais ni surjective ni injective}
\text{name_surj=est surjective mais pas injective}
\text{name_inj=est injective mais pas surjective}
\text{name_bij=est bijective}
\text{name_instruction=Considérons la "fonction", définie par,
  Quelle est la nature de}
#endif
#if defined TARGET_quadratic
\matrix{name_instruction=Soit,la fonction définie par
  Vérifiez que \(f\) est bijective et calculez la fonction réciproque
}
#endif
#if defined TARGET_fraction
\matrix{name_instruction=Soit,la fonction définie par
  Vérifiez que \(f\) est bijective et calculez la fonction réciproque
}
#endif
#if defined TARGET_quadratic || defined TARGET_fraction
\text{name_hint=Vous pouvez taper <span class="tt">sqrt(2)</span> pour
  la racine carrée de 2 par exemple.}
#endif

#if defined TARGET_Imagerciproque || defined TARGET_Imagerciproque2  || defined TARGET_Imagedelimager
\matrix{name_instruction=Soit la fonction \(f) définie sur \(\displaystyle{\RR}\) par
  Soit, Que peut-on dire de}
\matrix{name_question=est-il égal à l'intervalle \(I\)
  est-il strictement contenu dans \(I\)
  contient-il strictement \(I\)
  aucune de ces possibilités}
\text{name_feed= est toujours contenu dans \(I\). Votre réponse est donc impossible.}
# if defined TARGET_Imagerciproque2 || defined TARGET_Imagedelimager
\text{eg = est égal à \(I\)}
\text{cont=contient strictement \(I\)}
\text{contenu=est strictement contenu dans \(I\)}
\text{autre=aucune de ces possibilités}
# endif
# if defined TARGET_Imagerciproque || defined TARGET_Imagerciproque2
\text{vi =l'ensemble vide}
\text{int=un intervalle non vide}
\text{deuxint=la réunion de deux intervalles disjoints et maximaux}
# endif
#endif
#if defined TARGET_nonderrecip
\matrix{name_instruction=La fonction, définie par
  est bijective, mais il y a un point
  tel que la fonction réciproque
  n'est pas dérivable en
  Trouvez}
#endif
#if defined TARGET_invval || defined TARGET_reciproc
\text{name_hint=Vous devez répondre avec une précision d'au moins 4 chiffres significatifs.}
\matrix{name_instruction=Soit, la fonction définie par
  Vérifiez que \(f\) est bijective, elle a donc une fonction réciproque}
#endif
#if defined TARGET_invval
\matrix{name_instruction=\name_instruction
  Calculer sa valeur en}
#endif
#if defined TARGET_reciproc
\matrix{name_instruction=\name_instruction
  Calculez la valeur,de la dérivée en}
#endif
