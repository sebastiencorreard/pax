#if defined TARGET_majunion
\text{name_maj1=bounded from above, bounded from below}
\text{name_maj2=upper bounder, lower bounder}
\text{bad=It is never true}
\text{yes=It is always true}
\text{no=sometimes true and sometimes false}
\text{name_enonce=Let \(A\) and \(B\) be two subsets of  \(\displaystyle{\RR}\).
  Suppose that \(A\) (resp. \(B\)) is ,
  by \(a\) (resp. by \(b\)). Are the following two statements true}
\text{name_isby=is, by}
\text{name_answer=Intersection,Union}
#endif
#if defined TARGET_imfunc
\text{name_choix=bounded,lower-bounded,upper-bounded,not necessarily bounded from either side}
\matrix{name_data=a bijective,
a continuous, \strong,
a continuous and bijective,
a continuous and differentiable,
a continuous and periodic,
an increasing,
an increasing and periodic,
an increasing and surjective,
a decreasing,
a decreasing and periodic,
a decreasing and surjective,
an odd,
an odd and increasing,
an odd and decreasing,
an injective,
an even,
an even and increasing,
an even and decreasing,
a periodic,
a strictly increasing,
a strictly decreasing
}
\text{name_enonce=Le,be a function, and let \(A\) be a set, of,
  Consider the image, and the inverse image,of}
\text{name_question=What can be said about \(B\) and \(C\)}
\text{name_instruction=You must choose the most precise replies.}
\text{name_is=is}
#endif
#if defined TARGET_bornesup1 || defined TARGET_bornesup2
# if defined TARGET_bornesup1
\text{name_rep=the statement does not make it possible to know if,exists}
# endif
# if defined TARGET_bornesup2
\text{name_rep=is bounded below by,is bounded above by,none of the above is correct}
# endif
\text{name_enonce=Let \(A) be a non-empty set,
  we denote \(\sup(A)) its supremum (least upper bound) and \(\inf(A)) its infimum (greatest lower bound)
  if they exist.}
\text{name_know= We know that}
\text{name_answer=The answer}
#endif
#if defined TARGET_bornesup3
\text{name_rep=is an upper bound of,is a lower bound of}
\text{name_cond=above,below,above,below}
\text{name_enonce=Let \(A) and \(B) be two not-empty sets and,
  We denote respectively by, and, their bounds, We know that}
#endif
#if defined TARGET_bornesup1 || defined TARGET_bornesup2 || defined TARGET_bornesup3
\text{name_question=We can deduce (there can be one or several good answers)}
#endif
#if defined TARGET_bornesup4
\text{name_rep=
  There is nothing more to do &#59; it is a consequence of the definition of the least upper bound,
  There is nothing more to do &#59; it is a consequence of the definition of the least lower bound,
  this case cannot occur,
  it remains to show that}
\text{name_mhyp=is bounded above by,is bounded below by,and we want to show that}
\text{name_enonce=Let \(A\) be a non-empty set that is bounded and,
  We denote by,its bound, We know that}
\text{name_question=Choose among the following proposals (only one correct answer)}
\text{name_answer=The answer}
#endif
