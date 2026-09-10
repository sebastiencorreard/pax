#if defined TARGET_triangular
\text{name_question=Determine the value of \(x_1\) in the solution of the
following linear system with \(n\) equations and \n variables, for \(n \ge 3\).}
#endif

#if defined TARGET_typesol
\text{yes=Yes}
\text{no=No}
\matrix{name_question=We have a system of,in
  Among the following propositions, which are true}
\text{name_choice=The system may have no solution.,
  The system may have a unique solution.,
  The system may have infinitely many solutions.}
\text{name_instruction=At least one variable is in each equation.}
\text{name_gene=homogeneous,homogeneous}
\text{name_nonnul=non zero,non zero}
\text{name_not=non}
\text{name_Equ=linear equations,linear equation}
\text{name_Var=variables,variable}
\text{name_prompt=is true}
#endif
#if defined TARGET_Sommetstriangl
\text{name_instruction=We have a triangle \(A B C\) in the cartesian plane, such that}
\text{name_question=What are the coordinates of the 3 vertices \(A\), \(B\), \(C\) of the triangle}
\text{name_hint=In order to give your reply, we suppose}
\text{name_text=The middle of the side,is}
#endif
#if defined TARGET_quadrilat
\text{name_question=We have a quadrilateral in the cartesian plane with
  4 vertices \(A\), \(B\), \(C\), \(D\) such that}
\text{name_question2=The middle of the side,is}
\text{name_question3=What is the middle \((x,y)) of the side\(D A\)}
#endif
#if defined TARGET_Quatreentier3 || defined TARGET_Quatreentiers || defined TARGET_Quatreentier2 || defined TARGET_Troisentiers || defined TARGET_sixentiers
\text{name_instruction=We have \N integers,such that}
\text{name_mean=The average of, and of, is}
# if defined TARGET_Quatreentiers || defined TARGET_Troisentiers || defined TARGET_Quatreentier3
\text{name_question=What are these \N integers}
# endif
# if defined TARGET_Quatreentier2 || defined TARGET_sixentiers
\text{name_question=What is the average of}
#   if defined TARGET_Quatreentier2
\text{name_hint=For which value of \(t\) the following linear system has a solution}
#   endif
# endif
#endif
#if defined TARGET_Intersectiondr
\text{name_instruction=Consider two lines in the cartesian plan, defined respectively
  by the equations}
\text{name_question=Determine the point \(p=(x,y)\) where the two lines meet.}
#endif
#if defined TARGET_Distancesgales
\text{name_question=Find the coordinates of the point \(p = (x,y)\)
  in the cartesian plane, such that}
\text{name_question2=The distance between,ean,d, equals that between}
\text{name_hint=The set of points with equal distance towards two points
  \(q_1\) and \(q_2\) form a straight line.
  Find first the equation of this line in function of the
  coordinates of \(q_1) and \(q_2).}
#endif
#if defined TARGET_circleeq
\text{name_instruction=Any circle in the cartesian plane can be described by an equation
  of the form}
\text{name_instruction1=where \(a\), \(\b\), \(\c\) are real numbers.
  Find the equation of the circle \(C\) passing through the 3 points}
\text{name_instruction2=by giving the values for}
\text{name_condition=contains}
#endif
#if defined TARGET_centercircle
\text{name_question=Find the center, of the circle passing through the three points}
\text{name_hint1=The center of the circle is the point at equal distance towards the
  three given points.}
\text{name_hint2=A point M is at equal distance towards two points A and B if and only if the
  vectorial sum AM + BM is perpendicular to the vector AB, which can be
  translated into a linear equation on the coordinates of M.}
\text{name_condition=is at equal distance towards the 3 points}
#endif
#if defined TARGET_almostdiag
\text{name_instruction=Determine the value of \(x_1\) is the solution of the
following linear system with \(n\) equations and \(n\) variables, for \(n\ge 3\).}
\text{name_hint=The solution is a function of \(n\), which depends on the parity of \(n\).}
\text{name_parite=odd,even,if}
#endif
#if defined TARGET_alloy3
\text{name_instruction=A factory produces alloy from 3 types of recovered metals. The
  compositions of the 3 recovered metals are as follows.}
\text{name_question=The factory has received an order of \ton tons of an alloy with
  \x0% of iron, \y0% of nickel and \z0% of copper. How many tons of each type
  of recovered metal should be taken in order to satisfy this order}
\text{name_table=type,iron,nickel,copper,metal}
\text{name_help=Give the values keeping 4 significant digits.}
\matrix{name_feed0=You need a total of
  tonnes of metals, not
  tonnes}
\matrix{name_feed=Using
  of metal A
  of metal B and
  of metal C, one obtains
  of an alloy in which the proportions of iron, nickel and copper are not as desired
  The result is an alloy consisting of
  iron
  nickel and
  copper}
\text{name_solution1=Note \(a\), \(b\) and \(c\) respectively the quantities of
  metals A, B and C (expressed in tonnes) required to satisfy the order.
  These quantities are solutions of the following linear system}
\text{name_solution2=This system has a unique solution}
\matrix{name_solution3=In conclusion, with
  of metal A
  of metal B and
  of metal C
  one can obtained
  of an alloy consisting of
  iron
  nickel and
  copper
}
#endif
#if defined TARGET_3bottles
\text{name_instruction=We have 3 bottles, each containing a certain amount of water.}
\text{name_text=If we pour,of water from bottle, to bottle,would have,
  times of water as in, would have the same amount of water as}
\text{name_question=How much water there is in each bottle (in centiliters)}
\text{name_bottle=Bottle}
#endif
#if defined TARGET_solution
\matrix{name_choix=cations,of cations
  anions,of anions}
\matrix{name_choix=calcium,magnesium,sodium,potassium
  chlorure,sulfate,nitrate,nitrite,carbonate}
\text{name_header=Type,Solution}
\text{name_instruction=Three solutions have ppm content (part per million),
  given by the table below.}
\text{name_question=We want to form,
  centilitres of a solution with,
  ppm of,
  by mixing the 3 solutions. How many centilitres should we take of each}
#endif
#if defined TARGET_homo3x4 || defined TARGET_homo2x3
\text{name_instruction=Find a non-zero solution of the following homogeneous linear system.}
\text{name_hint=The values of \list in your solution should be integers}
\text{name_cond= non-zero integers,Equation,satisfied}
#endif
#if defined TARGET_solve3x3 || defined TARGET_solve2x2
  \text{name_question=Find the solution of the following syste.}
#endif
#if defined TARGET_achat
\text{name_vegetable=vegetable,vegetables}
\text{name_names_veg=beans, cucumbers, tomatoes, peppers, eggplants, cabbage}
\text{name_fruit=fruit,fruits}
 \text{name_names_fruit=apples, pears, oranges, clementines, bananas, melons}
\text{name_deplus=euros more on the,than on the,so much money on the}

\text{name_instruction=A restaurateur supplies himself at the market. He bought,
  kilograms of, at ,euros per kilo,for,euros in total}
\text{name_question=Knowing that he spent, how many kilograms did he buy from each type of,
  how much did he spend on each type of}
\text{name_prompt= in kilogram}
#endif
#if defined TARGET_ages
\text{name_party=a party, a meeting, a lunch}
\text{name_discover=discovers, says, knows}
\text{name_mean=the average of the ages,the sum of the ages}
\text{name_plusmoins1=that he is XXXXX years older than YYYYY,
	that YYYYY is XXXXX years younger than him,
	that YYYYY was born XXXXX years after him,
	that he was born XXXXX years before YYYYY,
	that he was XXXXX years old when YYYYY was born}
\text{name_plusmoins2=that he is XXXXX years younger than YYYYY,
	that YYYYY is XXXXX years older that him,
	that YYYYY was born XXXXX years before him,
	that he was born XXXXX years after YYYYY,
	that YYYYY was XXXXX years old when he was born
}
\text{name_instruction=Three gentlemen having the same birthday discuss their ages
 during}
\text{name_question=When, reaches the age of,,of,and of, will be}
\text{name_instruction1=The sum of the three ages is,When,was born,was,
  What is the age of each}
\text{name_age=Age of}
#endif
