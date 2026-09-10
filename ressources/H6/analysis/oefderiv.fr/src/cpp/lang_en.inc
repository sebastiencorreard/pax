#if defined TARGET_rectangle1 || defined TARGET_rectangle2 || defined TARGET_rectangle3 || defined TARGET_rectangle4 || defined TARGET_rectangle5 || defined TARGET_rectangle6
\text{name_direction=increases,decreases}
\text{name_long=length,width}
\text{name_larg=the width,the length}
\text{name_la=the}
\text{name_sa=its}
\text{name_constante=constante}
\text{name_constant=constant}
\text{name_cm=centimeters}
\text{name_cm2=square centimeters}
\text{name_area=its area}
\text{name_area0=the area}
\text{name_sarea=its areae}
\text{name_peri=the perimeter}
\text{name_speri=its perimeter}
\text{name_answer=Speed}
\matrix{name_statement=We have a rectangle whose
  at a constant speed of
  centimeters per second, but whose
  stays constant
  at
  At the moment when
  equals
  what is the speed
  en}
!!!!at which \second changes?

#endif
#if defined TARGET_hyper || defined TARGET_hyper2 || defined TARGET_trigo || defined TARGET_trigo2 || defined TARGET_rat || defined TARGET_rat2 || defined TARGET_poly || defined TARGET_poly2
\text{name_enonce=Compute the derivative of the function \(f\) defined by}
#endif
#if defined TARGET_trigo3
\text{name_enonce=Compute the derivative of the function \(f\) defined by, at the point}
#endif
#if defined TARGET_poly || defined TARGET_poly2
# if defined TARGET_poly
\text{name_sol=We have, hence}
\text{name_at=for}
# endif
#endif
#if defined TARGET_mult1 || defined TARGET_mult2 || defined TARGET_multmixt
# if defined TARGET_mult1
\text{name_question=Let,Compute the derivative}
# endif
# if defined TARGET_multmixt
\text{name_question=Let \(h\) defined by ,Compute the derivative}
# endif
# if defined TARGET_mult2
\text{name_question=Let,Compute the second derivative}
# endif
# if defined TARGET_mult1 || defined TARGET_mult2
\text{name_enonce=We have two differentiable functions \(f\) and \(g\),
  with values and derivatives shown in the following table}
# endif
# if defined TARGET_multmixt
\text{name_enonce=We have a differentiable function \(f\)
  with values and derivatives shown in the following table}
\text{name_hint=First compute the value and derivative of the function,
  at the point, then apply the formula of multiplication.}
\text{name_sol=Let,We have, hence}
# endif
#endif
#if defined TARGET_comp1 || defined TARGET_comp2
# if defined TARGET_comp1
\text{name_enonce=We have two differentiable functions \(f\) and \(g\)
  with values and derivatives shown in the following table.}
\text{name_sol=Let , hence,}
# endif
# if defined TARGET_comp2
\text{name_enonce=We have 3 differentiable functions\(f\), \(g\) and \(h\),
  with values and derivatives shown in the following table.}
# endif
\text{name_question=Let \(s\) be the function defined by,,
  Compute the derivative }
#endif
#if defined TARGET_compmixt
\text{name_enonce=We have a differentiable function \(f\)
  with values and derivatives shown in the following table}
\text{name_question=Let \(g\) be the function defined on \(\,\RR\) by,
  and let \(s) be the composite of \(g) and \(f) defined on \(\mathbb{R}\) by,
  Compute the derivative }
#endif
#if defined TARGET_compvert1a || defined TARGET_compvert1b
\text{name_enonce=Let \(f\) be a differentiable function, with derivative \(f'\).
  Compute the derivative of the function \(g\) defined by}
\text{name_answer=Derivative}
#endif
We have a circle whose area increases at a constant speed of
\a square centimeters per second. At the moment when its radius equals \r
cm, what is the speed at which the radius increases (in cm/s)?

#if defined TARGET_circle || defined TARGET_circle2
\text{name_enonce=We have a circle whose area increases at a constant speed of,
  centimeters per second.}
\text{name_answer=Area speed}
#endif
#if defined TARGET_circle3 || defined TARGET_circle4
\text{name_enonce=We have a circle whose area increases at a constant speed of,
  square centimeters per second.}
\text{name_answer=Radius speed}
#endif
#if defined TARGET_circle
\text{name_question= At the moment when its radius equals,centimeters,
  what is the speed at which its area increases}
#endif
#if defined TARGET_circle2
\text{name_question=At the moment when its aera equals,square centimeters,
  qwhat is the speed at which its area increases}
#endif
#if defined TARGET_circle3
\text{name_question=At the moment when its aera equals,square centimeters,
   what is the speed at which the radius increases}
#endif
#if defined TARGET_circle4
\text{name_question=At the moment when its radius equals,centimeters,
   what is the speed at which the radius increases}
#endif
#if defined TARGET_multvert1
\text{name_enonce=Let \(f\) be a differentiable function, with derivative \(f'\).
  Compute the derivative de la fonction \(g\) définie par}
\text{name_answer=Derivative }
#endif
#if defined TARGET_div1
\text{name_enonce=We have two differentiable functions \(f\) and \(g\),
  with values and derivatives shown in the following table.}
\text{name_question=Let \(h\) be defined by, Compute the derivative}
#endif
#if defined TARGET_arcarg
\text{name_enonce=Establish the correspondence between the fucntions and their derivatives
in the following table.}
#endif
#if defined TARGET_divmixt
\text{name_enonce=We have a differentiable function \(f\),
  with values and derivatives shown in the following table.}
\text{name_question=Let, be the function defined by, Compute the derivative}
\text{name_hint=First compute the value and derivative of the function ,
  at the point, then apply the formula of division.}
\text{name_feed=Let, We have, hence}
#endif
#if defined TARGET_righttriangle
\text{name_enonce=We have a right triangle as follows, where,
and, at a constant speed of}
\text{name_question=At the moment when, what is the change speed of,
  in}
\text{name_answer=Speed of BC in}
\text{name_direction=increases,decreases}
#endif
#if defined TARGET_tower
\text{name_enonce=Somebody walks towards a tower at a constant speed of,
  meters per second.}
\text{name_question= If the height of the tower is,meters,
  at what speed (in m/s) does the distance between the man and the top of the tower
  decrease when the distance between him and the foot of the tower is, meters}
\text{name_answer=Speed rate}
#endif
#if defined TARGET_signenombre
\text{name_enonce=Construct a study of the sign of,
  by choosing four of the sentences given below.}
\text{name_posneg=positive,negative}
\text{name_p1=First,To get started}
\text{name_p23=Then,Next}
\text{name_p4=Finally,Hence,As a result,Lastly,In conclusion}
\matrix{name_step1=let's consider the, we define a, let the
function}
\matrix{name_step2=let's compute,we compute
the derivative}
\text{name_step3=it can be seen that,for}
\matrix{name_step4=hence,whence,therefore
is}
\matrix{name_bad1=let's consider the, we define a, let the
 function}
\matrix{name_bad2=let's compute,we compute
the derivative}
\text{name_bad3=it can be seen that, for}
\matrix{name_bad4=hence,whence,therefore
is}
\text{name_answer=Step}
\text{name_cond=The reasoning is well-constructed}
\text{name_feed1=Disordered logic:
  how did you manage to compute  \(f'(x)) before you had even defined}
\text{name_feed2=Error: to get,you have to take, instead of}
\text{name_feed3=Error: Did you calculate the derivative of}
\text{name_feed4=Your second step is premature.}
\text{name_feed5=You made a mistake in calculating the sign of, Check it out.}
\text{name_feed6=You misunderstood the sign in the last step. Think about it:
  if \(f '(x) XXXX 0\) for \(x \in [a,b]\), is \(f\) increasing or
  decreasing? So do we have \(f(a) XXXX f(b)\) or}
\text{name_feed7=Wrong conclusion: the last step does not even give the sign of}
#endif
#if defined TARGET_reciproc
\text{name_enonce=Let, be the function defined by}.
\text{name_enonce2=Verify that \(f\) is bijective, therefore we have an inverse function}
\text{name_question=Calculate the value, of its derivative at}
\text{name_instruction=You must reply with a precision of at least 4 significant digits.}
#endif
