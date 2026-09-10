target=epuiss

#include "header.inc"

\title{Equation avec puissance}

\integer{a=random(1..30)*random(1,-1)}
\integer{b=random(2,4,5,8,10,20)*random(1,-1)}
\function{base=\a+\b*x}
\integer{p=random(5,7,9)}
\real{r=-(\a+1)/(\b)}

\statement{
  Résoudre l'équation \((\base)^\p = -1).
<div class="wims_instruction">
  Taper <span class="tt">non</span> si vous pensez qu'il n'y a pas de solution.
</div>
}

\reply{\(x)}{\r,non}{type=default}

