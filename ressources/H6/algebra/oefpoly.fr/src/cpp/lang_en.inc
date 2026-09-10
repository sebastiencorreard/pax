#if defined TARGET_mindeggcd2 || defined TARGET_rootcomp || defined TARGET_rerootdeg2 || defined TARGET_rootcnt
\text{comma=}
#endif

#if defined TARGET_relrtdeg2
\text{name_statement1=Let \(r_1), \(r_2) be the two roots of the polynomial}
\text{name_statement2=where \(a) is a real coefficient. What is the value of}
\text{name_hint1=We have}
\text{name_hint2=Now use the relation between the roots and the coefficients of a polynomial}
#endif

#if defined TARGET_relrtdeg3
\text{name_statement1=Let \(r_1\), \(r_2\), \(r_3\) be the 3 roots of the polynomial}
\text{name_statement2=where \(a\) is a non-zero real coefficient. What is the value of}
#endif

#if defined TARGET_relrtdeg2 || defined TARGET_relrtdeg3
\text{name_instruction=This value is a function of}
#endif

#if defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn
note for translators: in the following keep commas
\text{name_statement=Let,be a polynomial of degree,with,coefficients&#44; having,different real roots and,different complex roots (not counted with multiplicities),Let}
#endif

#if defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn || defined TARGET_rootcnt || defined TARGET_givderiv
\text{name_gcd=gcd}
#endif

#if defined TARGET_deggcd
\text{name_derivative=be the derivative of}
\text{name_question=What is the degree of}
\text{name_answer=Degree of}
\text{name_hint=The roots of gcd(\(P(x),P'(x))) are exactly the multiple
roots of \(P\).}
#endif

#if defined TARGET_mindeggcd2
\text{name_derivative=be the second derivative of}
\text{name_question=What is the minimum of degree of}
\text{name_answer=Minimum of}
\text{name_hint=The multiple roots of \(P\) with multiplicity \( >2 \) are among the roots of \(gcd(P(x),P''(x))\).}
#endif

#if defined TARGET_mindeggcdn
note for translators: in the following keep commas
\text{name_derivative=be the,-th derivative of}
\text{name_question=What is the minimum of degree of}
\text{name_answer=Minimum of}
#endif

#if defined TARGET_stadouble
\text{name_statement=What is the type of roots of the following degree 2 polynomial}
\text{name_choice=Type of roots}
\text{name_type_list=one real root and one complex non-real root,one real double root,one non-real double root,two simple real roots,two conjugate complex roots}
#endif

#if defined TARGET_parmdeg2
\text{name_type_list=two simple real roots,
	two conjugated complex roots,
	one double root}
note for translators: in the following keep commas
\text{name_statement=For which real values of the parameter,the polynomial,has}
\text{name_choice=The condition}
\text{name_answer=Where}
#endif

#if defined TARGET_parmdeg2b
note for translators: in the following keep commas
\text{name_statement=For which real value of the parameter,the polynomial,has a root equal to,Under the condition that}
#endif


#if defined TARGET_givderiv
note for translators: in the following keep commas
\text{name_statement=Find the polynomial,such that,where,is the derivative of,the degree of,is as small as possible}
note for translators: in the following keep commas
\text{name_instruction=You may enter your polynomial under any form, developed or factored,Type,for}
\text{name_andsoon=etc}
#endif

#if defined TARGET_diffeqn
note for translators: in the following keep commas
\text{name_statement=Find the polynomial,such that,and that}
note for translators: in the following keep commas
\text{name_instruction=Type,for}
\text{name_andsoon=etc}
#endif

#if defined TARGET_givrtdeg3
note for translators: in the following keep commas
\text{name_statement=Determine the polynomial,knowing that,are real&#44; and that,is one of its roots}
\text{name_answer=The real root}
#endif

#if defined TARGET_rootcomp
\text{name_item_list=is a root of,is a root of,is also a root of}
note for translators: in the following keep commas
\text{name_statement=Let,be a polynomial,another polynomial,Consider the composed polynomials,Complete}
note for translators: in the following keep commas
\text{name_question=If,is a root of,then}
\text{name_answer=The number to complete}
#endif


#if defined TARGET_rootmultsum || defined TARGET_rootcnt
\text{name_of=of}
#endif

#if defined TARGET_rootmultsum || defined TARGET_degsum
\text{name_statement1=Let \(P(X)\) and \(Q(X)\) be two polynomials. Complete}
#endif

#if defined TARGET_rootmultsum
\text{name_sup=greater than or equal to m}
\text{name_inf=less than or equal to m}
\text{name_equ=equal to m}
note for translators: in the following keep commas
\text{name_statement2=If,is a root of multiplicity,and also a root of multiplicity,then,is a root of multiplicity}
\text{name_choice=The multiplicity is}
\text{name_answer=Where}
#endif

#if defined TARGET_degsum
\text{\name_sup=greater than or equal to a number d}
\text{\name_inf=less than or equal to a number d}
\text{\name_equ=equal to a number d}
note for translators: in the following keep commas
\text{name_statement2=If,then,is a polynomial of degree}
\text{name_choice=The degree is}
\text{name_answer=Where}
#endif

#if defined TARGET_tripledeg3 || defined TARGET_tripledeg3b || defined TARGET_rootcomp || defined TARGET_quadpoly || defined TARGET_givrtdeg3 || defined TARGET_degsum
\text{name_and=and}
#endif

#if defined TARGET_tripledeg3 || defined TARGET_tripledeg3b
note for translators: in the following keep commas
\text{name_statement=For which real values of the parameters,the polynomial,has a triple root}
\text{name_answer=The triple root}
\text{name_condition=is a triple root}
#endif

#if defined TARGET_tripledeg3
\text{name_hint1=If \(r\) is a triple root of \(P\), then}
\text{name_hint2=is therefore a (real) root of the polynomial}
\text{name_where=where}
#endif

#if defined TARGET_tripledeg3b
\text{name_instruction=There may be several solutions.}
#endif

#if defined TARGET_trinomefact
\text{name_step=Step}
\text{name_statement1=Factor}
\text{name_statement2=We put the terms of \(x\) into a complete square}
\text{name_statement3=We have}
\text{name_statement4=Therefore}
\text{name_statement5=Now we apply the formula}
\text{name_result=Result}
\text{name_instruction=You should enter the simplified expressions.}
\text{name_answer1=Constant term of development of square}
\text{name_answer2=Constant term in the square}
\text{name_answer3=Compensation term}
#endif

#if defined TARGET_quadpoly
\text{name_statement=Compute the two roots of the polynomial}
\text{name_instruction=You may enter the two roots \(\r1\) \name_and \(\r2\) in any order.}
\text{name_condition1=is a root}
\text{name_condition2=is another root}
#endif

#if defined TARGET_rootdeg2
\text{name_statement1=Find the two roots}
\text{name_statement2=of the polynomial}
\text{name_instruction=The roots are real, and the order in which you give the roots has no importance.}
\text{name_condition1=is a root}
\text{name_condition2=There is no other root}
#endif

#if defined TARGET_rootcnt
note for translators: in the following keep commas
\text{name_statement=Let,be a polynomial of degree,with,coefficients&#44; and let,be the derivative of,We know that,is a polynomial of degree}
note for translators: in the following keep commas
\text{name_question=What is the number of,distinct,roots of}
\text{name_note=both real and complex roots}
\text{name_answer=Number of distinct roots}
\text{name_hint=The roots of \(gcd(P(x),P'(x))\) are exactly the multiple
roots of \(P(x)).}
#endif

#if defined TARGET_rerootdeg2
note for translators: in the following keep commas
\text{name_statement=Let,be a polynomial with real coefficients,having two conjugate complex roots,What is the real part of a root}
#endif

#if defined TARGET_degmult || defined TARGET_mindeggcd2 || defined TARGET_deggcd || defined TARGET_mindeggcdn || defined TARGET_rootcnt
\text{name_type_list=real,complex}
#endif

#if defined TARGET_degmult
note for translators: in the following keep commas
\text{name_statement=What is the minimum of the degree of a polynomial,with,coefficients such that}
\text{name_request1=is a root of multiplicity}
\text{name_request2=is a root of multiplicity}
note for translators: in the following keep commas
\text{name_instruction=Answer,if you think that such polynomial does not exist}
\text{name_answer=Minimum of degree}
#endif

#if defined TARGET_findmult3 || defined TARGET_findmult4 || defined TARGET_findmult5 || defined TARGET_findmult6
\text{name_statement=The following polynomial has a multiple root. Find this root}
\text{name_answer=The multiple root}
#endif

#if defined TARGET_multiplicity3 || defined TARGET_multiplicity4 || defined TARGET_multiplicity5 || defined TARGET_multiplicity6
note for translators: in the following keep commas
\text{name_statement=The number,is a root of the polynomial below}
\text{name_statement2=Compute its multiplicity}
\text{name_answer=The multiplicity of}
#endif

#if defined TARGET_multparm3 || defined TARGET_multparm4
\text{name_statement=Find a value of \(m\) so that the following polynomial has a multiple root, and find this multiple root.}
\text{name_warning=WARNING}
\text{name_instruction=This exercise does not accept approximative replies! There is always an integer solution. Find it.}
\text{name_answer=The multiple root}
\text{name_condition=is a multiple root of}
\text{name_feedback1=is not even a root of}
\text{name_feedback2=All wrong.}
\text{name_feedback3=is in fact a root of}
\text{name_feedback4=In order for it to be a multiple root, }
\text{name_feedback5=must also be a root of the derivative of}
\text{name_feedback6=which is unfortunately not the case. Verify your computation.}
#endif
