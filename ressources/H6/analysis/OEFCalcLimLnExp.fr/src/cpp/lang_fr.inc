\text{name_at=en}
\text{name_by=par}
\text{name_and=et}
\text{name_with=avec}
\text{name_inst=<h3>Consignes de saisie.</h3>
  Écrire <b>+inf</b> pour désigner \(+\infty\) et
  <b>-inf </b> pour désigner \(-\infty\).}
\text{name_prelim=Cet exercice comporte NNNN étapes.}
#if defined TARGET_indeterminateForm || defined TARGET_indformwithln || defined TARGET_indformwithexp
\text{name_enonce=Soit \(f\) la fonction définie sur}
\text{name_enonce2=La fonction s'écrit donc, pour tout réel \(x\) de}
\text{name_aim=Le but de cet exercice est de calculer la limite de}
\text{name_question3=Donner la limite de}
\matrix{name_youranswer=Votre réponse est juste
  Attention, votre réponse est fausse, au moins en partie
  Votre réponse, est erronée}
\text{name_deduc2=En posant,sachant que , on déduit l'égalité}
\text{name_question2=La limite de, est}
\text{typeindet=Oui car on n'a aucune forme indéterminée,
Non car on a une forme indéterminée de type 0 x inf,
Non car on a une forme indéterminée de type 0 / 0,
Non car on a une forme indéterminée de type inf / inf ,
Non car on a une forme indéterminée de type -inf + (+inf)}
\text{name_question5=Peut-on déduire la limite en, de, en appliquant les règles opératoires sur les limites}
\matrix{name_rule=Les règles opératoires des limites sont valables ici, car il n'y a aucune forme indéterminée.
  On ne peut pas appliquer les règles opératoires des limites, car il y a une forme indéterminée du type
  On applique alors les règles de croissance comparée}
\text{name_choix=l'exponentielle l'emporte sur les polynômes,les polynômes l'emportent sur le logarithme}
\text{name_onobtient=On obtient donc }
\text{name_answer=Limite de}
\text{name_answer2=Forme indéterminée}
\text{name_feed=Remarque,On peut lever l'indétermination en écrivant}
#endif
#if defined TARGET_compln || defined TARGET_calcexp || defined TARGET_calcln
\text{name_valsupinf=par valeurs supérieures,par valeurs inférieures}
#endif
#if defined TARGET_compoexp || defined TARGET_compln
\text{name_enonce=Soit \(f\) la fonction définie sur}
\text{name_answer2=Exposant,Coefficient}
\text{name_aim=Le but de cet exercice est de calculer par étapes
  la limite de \(f\) en}
\matrix{name_youranswer=Votre réponse est juste
  Attention, votre réponse est fausse, au moins en partie}
\text{name_question3=Donner la limite de}
\text{name_deduc=Par les résultats du cours, on obtient}
\text{name_deduc4=Finalement, par les règles opératoires des limites, on obtient l'égalité }
\text{name_question2sol=La limite de,est}
\text{name_question1=La fonction \(f\) est de la forme, avec}
\text{name_question2=Donner la limite de}
# if defined TARGET_compoexp
\text{name_deduc2=En posant,sachant que XXXX, on déduit l'égalité}
\text{name_deduc3=La limite de, en}
# endif
# if defined TARGET_compln
\text{name_deduc2=En posant,par composition de limites, on déduit l'égalité}
\text{name_deduc3=Par composition la limite de, est}
# endif
#endif
#if defined TARGET_calcexp || defined TARGET_calcln
\text{name_enonce=On considère la fonction, définie sur}
\text{name_aim=Le but de cet exercice est de calculer par étapes
  les limites de \(f\), en XXXX et en YYYY respectivement.}
\text{name_question1=On nomme \(u\) la fonction, définie sur,
  Donner les limites de \(u\) en}
\text{name_question2=Donner maintenant les limites de}
\text{name_and2=et en}
\text{name_are=sont}
\text{name_answer=Limite de}
\text{name_deduc=Des résultats précédents, on déduit la limite de \(f\) en}
\text{name_deduc2=on déduit l'égalité}
\text{name_andby=et par}
\text{name_choice=les règles opératoires sur les produits,les règles de croissance comparée}
\text{name_choice2=produit,croissance comparée}
\matrix{name_youranswer=Votre réponse est juste
  Attention, votre réponse est fausse, au moins en partie
  Les limites de \(u\) en}
\text{name_answer2=calculée par}
# if defined TARGET_calcexp
\text{name_youranswer4=Les limites de l'exponentielle en}
\text{name_inst=\name_inst
  Écrire les nombres rationnels sous forme de fractions irréductibles.}
# endif
# if defined TARGET_calcln
\text{name_youranswer4=Les limites du logarithme en}
\text{name_inst=\name_inst
  Pour désigner \(\ln(X)\), écrire <b>ln(X)</b> et non ln X..}
# endif
#endif
#if defined TARGET_croisscomp
\text{name_emporte=l'emporte sur}
\text{name_aim=Il permet de revoir les limites de référence exprimant
  les croissances comparées entre exponentielle ou logarithme d'une variable
  et puissances de cette même variable.}
\text{name_truefalse=vraie,fausse}
\text{name_question1=L'affirmation, est,
  L'affirmation juste est}
\text{name_atneigh=au voisinage de}
\text{name_question2=Formellement, cela signifie qu'on a }
#endif
#if defined TARGET_qcmref
\text{name_enonce=Dans cet exercice on exerce le calcul mental sur les limites de référence
  au programme de Terminale. Il faut répondre rapidement.}
#endif
