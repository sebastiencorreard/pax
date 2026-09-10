#if defined TARGET_lceb1a || defined TARGET_lceb1b || defined TARGET_lceb2a || defined TARGET_lceb2b
\text{instruction1=Using numbers from the first row and the four arithmetic operations,
you must arrive to \N ; write your first operation and its result,
for example}
\text{instruction2=send the result, then continue.}
\matrix{conditiontext=You used the given numbers
Te calculations are correct
You found the target number or the nearest result
Your number lies between \M1 and \M2}
\matrix{instruction0=Choose a number between \M1 and \M2.
You didn't play the game ... }
\matrix{feedtext=Your answer
 One possible answer}
#endif

#if defined TARGET_graphe3
\text{instruction1=On target or near}
\text{instruction2=complete the tree with the operations used
  for the solution you found}
#endif

#if defined TARGET_graphe0 || defined TARGET_graphe1 || defined TARGET_graphe2
\text{instruction=Here is a tree that can be use to obtain the target in this
  <i>le compte est bon</i> game, or to arrive near the target.
  Write down the corresponding equations}
\text{name_condition=The equalities are correct,
  These are the required equalities}
\text{name_feed=The operation sequence is,
  You missed some calculations.}
#endif
