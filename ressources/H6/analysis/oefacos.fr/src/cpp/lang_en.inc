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
\text{name_enonce=Compute,writing it under the form,where \(a\) and \(b\) are rational numbers.}
\text{name_hint=Attention, on demande que \(a\) et \(b\)
  soient des nombres rationnels, ils sont en fait décimaux.
  Vérifier qu'il n'y a alors qu'une seule solution.}
#endif
#if defined TARGET_compderiv
\text{name_ouinon=Yes,No}
\text{name_enonce=Is the function \(f\) defined by, differentiable in the interval}
\text{name_answer=Answer}
#endif
#if defined TARGET_comprange
\text{name_enonce=Consider the function \(f\) defined byr,
  Determine the (maximal) interval of definition \(I) and the image interval \(J) of \(f\).}
\text{name_instruction=To give your reply, Let \(I =\ [a,b]\) (open or closed),
  \(J =\ [c,d]\) (open or closed). Write "<span class="tt">pi</span>",
  "<span class="tt">F</span>" or "<span class="tt">-F</span>" to designate }
\text{name_or=or}
#endif
#if defined TARGET_acoscoslin
\text{name_enonce1=For \(x\) within the interval, one can
  simplify the function \(f\) defined by  }
\text{name_enonce2=to a linear function of the form \(a x + b\).
  What is this linear function}
\text{name_instruction=Write, for}
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
\text{name_enonce=Let \(f\) be the function defined by}
\matrix{name_question=The definition domain of, is composed of,disjoint intervals.
  The definition domain is the reunion of,interval,intervals
  What are their bounds in increasing order}
\text{name_instruction=If a bound is infinity, write  +inf or  -inf}
\text{name_answer=Number of intervals}
\matrix{name_hint=What is the definition domain of the function
  You can draw the graph of \(x\rightarrow \f_t) et check by computation.}
#endif
