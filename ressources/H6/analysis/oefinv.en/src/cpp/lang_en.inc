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
\text{name_statement=Soient \(\I,\J\) deux intervalles, \(\f : \I \to \J\)
  une fonction bijective, et soit \(\g : \J \to \I\) sa réciproque.
  Composez une démonstration de l'injectivité de \(\g\) à l'aide des
  phrases données plus bas.}
\text{name_step=Première étape,}
\text{name_sentence1=Soient ,tels que,Je dois montrer que }
#endif
#if defined TARGET_bijquad
\text{name_notf=is not even defined on}
\text{name_noj=is well-defined but neither surjective nor injective}
\text{name_surj=is surjective but not injective}
\text{name_inj=is injective but not surjective}
\text{name_bij=is a bijective function}
\text{name_instruction=Consider the ``function'', defined by,
  What is the nature of}
#endif
#if defined TARGET_quadratic
\matrix{name_instruction=Let,be the function defined by
  Verify that \(f\) is bijective, and compute the inverse function
}
#endif
#if defined TARGET_fraction
\matrix{name_instruction=Let,be the function defined by
  Verify that \(f\) is bijective, and compute the inverse function
}
#endif
#if defined TARGET_quadratic || defined TARGET_fraction
\text{name_hint=You may type <span class="tt">sqrt(2)</span>
  for the square root of 2 for example.}
#endif

#if defined TARGET_Imagerciproque || defined TARGET_Imagerciproque2  || defined TARGET_Imagedelimager
\matrix{name_instruction=Let \(f\) be the function defined on \(\displaystyle{\RR}\) by
  Let, What can be said of }
\matrix{name_question=is it equal to the interval \(I\)
  is it strictly contained in \(I\)
  does it contain strictly \(I\)
  none of these possibilities}
\text{name_feed=is always contained in \(I\). Your answer is not possible.}
#  if defined TARGET_Imagerciproque2 || defined TARGET_Imagedelimager
\text{eg = est égal à \(I\)}
\text{cont=strictly contains\(I\)}
\text{contenu=is strictly contained in \(I\)}
\text{autre=none of these possibilities}
#endif
# if defined TARGET_Imagerciproque || defined TARGET_Imagerciproque2
\text{vi =the emtpy set}
\text{int=an non-empty interval}
\text{deuxint=the union of two disjoint maximal intervals}
# endif
#endif
#if defined TARGET_nonderrecip
\matrix{name_instruction=The function, defined by
  is bijective, but there is a point
  such that the inverse function
  is not differentiable on
  Find}
#endif
#if defined TARGET_invval || defined TARGET_reciproc
\text{name_hint=You must reply with a precision of at least 4 significant digits.}
\matrix{name_instruction=Let, be the function defined by
  Verify that \(f\) is bijective, therefore we have an inverse function}
#endif
#if defined TARGET_invval
\matrix{name_instruction=\name_instruction
    Calculate the value at }
#endif
#if defined TARGET_
\matrix{name_instruction=\name_instruction
  Calculate the value,of the derivative at}
#endif
