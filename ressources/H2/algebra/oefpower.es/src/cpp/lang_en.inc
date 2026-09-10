#if defined TARGET_ppower11 || defined TARGET_ppower12 || defined TARGET_ppower13 || defined TARGET_ppower01 || defined TARGET_ppower02
\text{name_statement=Compute without calculator}
#endif
#if defined TARGET_powerneg
\matrix{name_statement=The number,is
  Write it as a product of powers}
\text{name_choix=positive, negative}
\matrix{name_feed=Did you look at whether,the exponent,the exponents
  of the  negative number,is even or odd
  of the negative numbers,are even or odd
  The sign of this exponent does,signs of these exponents do,not matter in this question.
  The product of positive numbers, the powers of positive numbers are always positive.}
#endif
#if defined TARGET_defecritscien
\text{name_statement=Write the following number \(A\) using scientific notation:}
#endif
#if defined TARGET_defpuisdix
\text{name_statement=Determine the value of the number }
\text{name_instruction=You will write the answer as an integer or decimal number.}
#endif
#if defined TARGET_defpuisnb
\text{name_statement=Determine the value of the number}
#endif
#if defined TARGET_defpuisnb2
\text{name_statement=Determine the value of the number}
\text{name_instruction=Give the result as an integer or an irreducible fraction.}
#endif
#if defined TARGET_encadr
\text{name_statement=Give bounds of the number, by consecutive powers of 10.}
\text{name_answer1=Exponent}
\text{name_answer2=Exponent}
\text{name_hint=You can first write \(A) using scientific notation.}
#endif
#if defined TARGET_operation1 || defined TARGET_operation2
\text{name_statement=Complete the equality so that it becomes true}
\text{name_instruction=Give the result in the form}
#endif
#if defined TARGET_ordregrandeur
\text{name_statement=Determine an order of magnitude for the number}
\text{name_instruction=If necessary, the exponent in the power of 10 can be zero.}
#endif
#if defined TARGET_tabpuis
\text{name_statement=Complete the table}
\text{name_feed=Be careful ! We have always}
#endif
#if defined TARGET_tabpuis2
\text{name_statement=Complete the table}
\text{name_feed=Be careful! In general \(a^m*a^n\) is different from \(a^{m n}\).}
\text{name_warning=Be careful}
#endif
#if defined TARGET_decimal
\matrix{name_statement=Write the number, in two ways
  scientific notation
  as,with \(a\) an integer and not multiple of 10}
\text{name_answer=scientific notation,exponent,\(a\), exponent}
#endif
#if defined TARGET_power
\text{name_statement1=Write}
\text{name_statement2=as a power of an integer
 (with the largest possible power)}
\text{name_hint=First simplify the fraction.}
\text{name_feedback1=Did you apply the rule}
\text{name_feedback2=Don't confuse}
\text{name_and=and}
#endif
#if defined TARGET_power10
\text{name_statement=Write the number asS}
\text{name_answer=exponent}
#endif