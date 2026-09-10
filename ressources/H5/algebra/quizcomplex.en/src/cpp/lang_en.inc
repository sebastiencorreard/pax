#if defined TARGET_arg || defined TARGET_conj || defined TARGET_module
\text{name_ask=are true,are not true}
\text{name_cond=good,bad}
\matrix{name_amongst=Among the following
which ones are}
\text{name_answer=The,are}
\text{propsname=formulas}
#endif
#if defined TARGET_arg
\text{name_instruction=Let \(z_1,z_2\) be two non-zero complex numbers.}
#endif
#if defined TARGET_conj
\text{name_instruction=Let \(z_1\), \(z_2\) and \(z_3\) be complex numbers.}
#endif
#if defined TARGET_module
\text{name_instruction=Let \(z_1,z_2\) be two complex numbers.}
#endif
#if defined TARGET_reim
\text{name_instruction=Let \(z = x + i y\) be a complex number, where \(x\) and \(y\) are real.
  What are the real and imaginary parts of}
\text{name_answer=The real part,The imaginary part}
#endif
#if defined TARGET_arggiven
\matrix{name_instruction=Compute the real part and imaginary part of the complex number \(z\) having
  and having
  as an argument}
#endif
#if defined TARGET_arg0
\text{name_instruction=Let \(z_1,z_2\) two non-zero complex numbers.
 Amongst the following equalities, which one are true}
#endif
#if defined TARGET_argask
\text{name_instruction=Give the module and argument of the complex number}
\text{name_feed=is an argument of}
#endif
