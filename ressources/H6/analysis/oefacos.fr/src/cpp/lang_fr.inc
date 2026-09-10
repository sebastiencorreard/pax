#if defined TARGET_defim || defined TARGET_defim2 || defined TARGET_defim3
\text{name_enonce=Choisissez les intervalles les plus pertinents dans les énoncés suivants.}
\text{name_question1=La fonction, est définie sur l'intervalle}
\text{name_question2=Son image est}
# if defined TARGET_defim
\text{name_question3=Cette fonction est dérivable sur}
# endif
# if defined TARGET_defim2
\text{name_question3=On a \(f(x) = x\) pour \(x \in\)}
# endif
\text{name_answer=Intervalle de définition,Image}
# if defined TARGET_defim
\text{name_answer=\name_answer,Intervalle de dérivabilité}
# endif
# if defined TARGET_defim2
\text{name_answer=\name_answer,Intervalle d'identité}
# endif
#endif
#if defined TARGET_acoscos || defined TARGET_acossin || defined TARGET_atantan
\text{name_enonce=Écrire,sous la forme,avec \(a\) et \(b\) des nombres rationnels. }
\text{name_hint=Attention, on demande que \(a\) et \(b\)
  soient des nombres rationnels, ils sont en fait décimaux.
  Vérifier qu'il n'y a alors qu'une seule solution.}
#endif
#if defined TARGET_compderiv
\text{name_ouinon=Oui,Non}
\text{name_enonce=La fonction \(f\) définie par, est-elle dérivable dans l'intervalle}
\text{name_answer=Réponse}
#endif
#if defined TARGET_comprange
\text{name_enonce=Considérons la fonction \(f\) définie par,
  Déterminer l'intervalle (maximal) de définition \(I) et l'intervalle d'image \(J) de \(f\).}
\text{name_instruction=Pour donner la réponse, soit \(I =\ [a,b]\) (ouvert ou fermé),
  \(J =\ [c,d]\) (ouvert ou fermé). Écrire "<span class="tt">pi</span>",
  "<span class="tt">F</span>" ou "<span class="tt">-F</span>" pour désigner}
\text{name_or=ou}
#endif
#if defined TARGET_acoscoslin
\text{name_enonce1=Pour \(x\) dans l'intervalle, on peut
  simplifier la fonction \(f\) définie par }
\text{name_enonce2=en une fonction affine de la forme \(a x + b\).
  Quelle est cette fonction affine&nbsp;}
\text{name_instruction=Écrivez, pour}
#endif
#if defined TARGET_derivarc
\text{name_answer=Domaine de définition,Domaine de dérivabilité ,Dérivée }
\text{name_of=de}
\matrix{name_enonce=Soit la fonction, définie par&nbsp;
  Son domaine de définition est
  Son domaine de dérivabilité est
  La dérivée de la fonction, sur son domaine de dérivabilité est&nbsp;}
#endif
#if defined TARGET_acosfrac
\text{name_enonce=Soit \(f\) la fonction définie par}
\matrix{name_question=Le domaine de définition de, est formé de,intervalle(s) disjoint(s).,
  Le domaine de définition est la réunion de,intervalle,intervalles
  donnez-en les extrémités dans l'ordre croissant}
\text{name_instruction=Si une des bornes est l'infini, écrire +inf ou -inf.}
\text{name_answer=Nombre d'intervalles}
\matrix{name_hint=Quel est le domaine de définition de la fonction
  N'hésitez pas à tracer le graphe de la fonction, et vérifiez par le calcul.}
#endif

