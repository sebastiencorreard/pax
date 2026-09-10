\text{name_prove=Prove}
\text{name_and=and}
#if defined TARGET_boundedsqr1 || defined TARGET_boundedsqr2
\text{name_enonce=Let \(\x\) be a real number with}
\text{name_hint=A proof by contradiction is necessary.}
#endif
#if defined TARGET_crossfrac || defined TARGET_crossfrac2
\text{name_posneg=positive,negative}
# if defined TARGET_crossfrac
\text{name_kind=integers, rational numbers, real numbers}
\text{name_enonce=Let \(\x\) and \(\y\) two, with}
# endif
# if defined TARGET_crossfrac2
\text{name_enonce=Let \(\x) a, strictly}
\text{name_kind=integer, rational number, real number}
# endif
#endif
#if defined TARGET_fracx1
\text{name_enonce=Solve the inequality, under the condition }
\text{name_aim=The goal of the exercise is to transform the given
  inequality into an equivalent one whose left side is, and whose right side
  is a constant.}
#endif
#if defined TARGET_fracx2
\text{name_enonce=Prove that the inequality,has no solution when}
#endif
#if defined TARGET_fracx3
\text{name_enonce=Solve the inequality,The solution is}
#endif
#if defined TARGET_majsqr1b || defined TARGET_majsqr2 || defined TARGET_majsqr2b
\text{name_enonce=Let \(\x\) be a real number with}
#endif
#if defined TARGET_majsqr3
\text{name_enonce=Find the best upper bound for, when}
#endif
#if defined TARGET_possqr1 || defined TARGET_possqr2
\text{name_for=for}
#endif
#if defined TARGET_sollin
\text{name_enonce=Solve for,the inequality}
\text{name_aim=The goal of the exercise is to transform the given inequality into an
  equivalent one where the left part is , and the right part
  is an expression of}
#endif
#if defined TARGET_sumprod2
\text{name_kind=rational numbers, real numbers}
\text{name_enonce=Let, two,positive,,such that}
#endif
#if defined TARGET_sumprod || defined TARGET_sumprodb
\text{name_enonce=Let \(a\) and \(b\) be two integers such that}
#endif
#if defined TARGET_sumprod3a
\text{name_enonce=Let, three , non negative,, tels que}
\text{name_range=rational numbers, real numbers}
#endif
#if defined TARGET_sumprod3b || defined TARGET_sumprod3b2
\text{name_enonce=Let, three, such that}
\text{name_range=integers, rational numbers, real numbers}
#endif
#if defined TARGET_sumprod3b
\text{name_hint=One should prove, And for this, you should start}
#endif
#if defined TARGET_twoprod
\text{name_enonce=Let, four real numbers,with}
\text{name_posneg=positive, negative}
#endif
#if defined TARGET_twosqr || defined TARGET_twosqrgiv
\text{name_enonce=Let, two real numbers, with}
#endif
