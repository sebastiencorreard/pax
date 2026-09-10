\text{name_at=at}
\text{name_by=by}
\text{name_and=and}
\text{name_with=with}
\text{name_inst=<h3>Typing hints.</h3>
  Type <b>+inf</b> for \(+\infty\) and
  <b>-inf </b> for \(-\infty\).}
\text{name_prelim=This exercise includes NNNN steps.}
#if defined TARGET_indeterminateForm || defined TARGET_indformwithln || defined TARGET_indformwithexp
\text{name_enonce=Let \(f\) be the function defined over}
\text{name_enonce2=So we have, for any real \(x\) in}
\text{name_aim=he aim of the exercise is to evaluate step by step the limit of}
\text{name_question3=Evaluate the limit of}
\matrix{name_youranswer=Your answer is correct
  Attention, your answer is wrong, at least in part
  Your answer, is wrong}
\text{name_deduc2=By variable renaming,knowing that, it comes that}
\text{name_question2=The limit of, is}
\text{typeindet=Yes because there is no indeterminate form,
No because there is an indeterminate form 0 x inf,
No because there is an indeterminate form 0 / 0,
No because there is an indeterminate form inf / inf ,
No because there is an indeterminate form -inf + (+inf)}
\text{name_question5=Can we deduce the limit at, of, by applying the computational rules of limits}
\matrix{name_rule=The computational rules of limits are valid, because there is no indeterminate form.
  The computational rules of limits are <b>not</b> valid, because there is an indeterminate form
  We use instead the properties of "compared growth"}
\text{name_choix=the exponential function dominates any polynom function,any polynom function dominates the logarithm function}
\text{name_onobtient=Then it comes }
\text{name_answer=Limit of}
\text{name_answer2=Indeterminate form}
\text{name_feed=Remark, Indeterminacy can be overcome by writing}
#endif
#if defined TARGET_compln || defined TARGET_calcexp || defined TARGET_calcln
\text{name_valsupinf=from above,from below}
#endif
#if defined TARGET_compoexp || defined TARGET_compln
\text{name_enonce=Let \(f\) be the function defined over}
\text{name_answer2=Exponent,Coefficient}
\text{name_aim=The aim of the exercise is to evaluate step by step
  the limit of \(f\) at}
\matrix{name_youranswer=Your answer is correct
  Attention, your answer is wrong, at least in part}
\text{name_question3=Evaluate the limit of}
\text{name_deduc=By the results of the course, one obtains}
\text{name_deduc4=Eventually, by the computational rules of the limits, it comes that}
\text{name_question2sol=The limit of ,is}
\text{name_question1=The function \(f\) is of the form , with}
\text{name_question2=Evaluate the limit of}
# if defined TARGET_compoexp
\text{name_deduc2=By variable renaming, and knowing that XXXX, it comes that}
\text{name_deduc3=The limit of, at}
# endif
# if defined TARGET_compln
\text{name_deduc2=With,by the computational rules of the limit,it comes that}
\text{name_deduc3=By composition the limit, is}
# endif
#endif
#if defined TARGET_calcexp || defined TARGET_calcln
\text{name_enonce=We consider the function, defined over}
\text{name_aim=The aim of the exercise is to compute step by step
  the limits of \(f\), at XXXX and at YYYY respectivement.}
\text{name_question1=Let \(u\) be the function, defined over,
  Evaluate the limits of \(u\) at}
\text{name_question2=Now evaluate the limits of}
\text{name_and2=and at}
\text{name_are=are}
\text{name_answer=Limit of}
\text{name_deduc=From the preceding results, one can deduce the limit of \(f\) at}
\text{name_deduc2=one can deduce}
\text{name_andby=and by}
\text{name_choice=the rules of the limits of products,the compared growth properties}
\text{name_choice2=product,compared growth}
\matrix{name_youranswer=Your answer is correct
  Attention, your answer is wrong, at least in part
  The limits of \(u\) at}
\text{name_answer2=calculée par}
# if defined TARGET_calcexp
\text{name_youranswer4=The limits of the exponential function at}
\text{name_inst=\name_inst
 Rational numbers must be written as irreducible fractions}
# endif
# if defined TARGET_calcln
\text{name_youranswer4=The limits of the logarithm at}
\text{name_inst=\name_inst
  For \(\ln(X)\), write <b>ln(X)</b> and not ln X..}
# endif
#endif
#if defined TARGET_croisscomp
\text{name_emporte=dominates}
\text{name_aim=The exercise deals with the basic rules of "compared growth"
  between on one hand logarithms or exponentials of a given variable
  and on the other hand powers of this variable.}
\text{name_truefalse=true,false}
\text{name_question1=The sentence, is,
  The true sentence is}
\text{name_atneigh=at the neighbourhood of }
\text{name_question2=Formally, this means that }
#endif
#if defined TARGET_qcmref
\text{name_enonce=This exercise aims to test the knowledge of basic limits
  of logarithms and exponentials. Reply as quickly as possible}
#endif
