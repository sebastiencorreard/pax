#if defined TARGET_formulas
\text{propsname=formulas}
\text{name_statement=Let \(f\) and \(g\) be two differentiable functions.}
\text{name_ask=are not correct,are correct}
\text{name_cond=bad,good}
\text{name_answer=The \cond \propsname are}
\text{name_question=Among the following \propsname, which ones}
#endif
#if defined TARGET_compvert1b || defined TARGET_compvert1a || defined TARGET_multvert1
\text{name_statement=Let \(f\) be a differentiable function, with derivative \(f'\).
  Compute the derivative of}
#endif
#if defined TARGET_simple1 || defined TARGET_frac1 || defined TARGET_frac2 || defined TARGET_basic1 || defined TARGET_poly
\text{name_statement=Compute the derivative of}
#endif

#if defined TARGET_growpos
\text{inc=is increasing}
\text{dec=is decreasing}
\text{sinc=is strictly increasing}
\text{sdec=is strictly decreasing}
\text{pos=has positives or zero values}
\text{neg=has negative or zero values}
\text{spos=has strictly positive values}
\text{sneg=has strictly negative values}
\text{noth=nothing can be said}
\text{name_statement=Let \(f\) be a continuous and differentiable function on an interval
  [a,b], with \(f'\) its derivative. Fill in}
\text{name_if=If}
\text{name_instruction=You must choose the most relevant reply.}
\text{name_choice=The good sentence}
#endif
