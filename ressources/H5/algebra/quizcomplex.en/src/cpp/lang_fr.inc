#if defined TARGET_arg || defined TARGET_conj || defined TARGET_module
\text{name_ask=sont vraies,ne sont pas vraies}
\text{name_cond=bonnes,mauvaises}
\matrix{name_amongst=Parmi les
suivantes, lesquelles}
\text{name_answer=Les,sont}
\text{propsname=formules}
#endif
#if defined TARGET_arg
\text{name_instruction=Soient \(z_1\) et \(z_2\) deux nombres complexes non nuls.}
#endif
#if defined TARGET_conj
\text{name_instruction=Soient \(z_1\), \(z_2\) et \(z_3\) des nombres complexes.}
#endif
#if defined TARGET_module
\text{name_instruction=Soient \(z_1\) et \(z_2\) deux nombres complexes.}
#endif
#if defined TARGET_reim
\text{name_instruction=Soient \(z = x + i y\) un nombre complexe, où \(x\) et \(y\) sont des réels.
  Quelles sont les parties réelle et imaginaire de }
\text{name_answer=Partie réelle,Partie imaginaire}
#endif
#if defined TARGET_arggiven
\matrix{name_instruction=Calculer la partie réelle et la partie imaginaire du nombre complexe \(z\) ayant
  comme module et ayant
  comme un argument}
#endif
#if defined TARGET_arg0
\text{name_instruction=Soient \(z_1\) et \(z_2\) deux nombres complexes non nuls.
 Parmi les égalités suivantes, lesquelles sont vraies}
#endif
#if defined TARGET_argask
\text{name_instruction=Donner le module et un argument du nombre complexe}
\text{name_feed=est un argument de}
#endif
