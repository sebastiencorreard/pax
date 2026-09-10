target=achat
#include "xiao.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{r1=randitem(1,2)}
\if{\r1=1}{
 \text{type=\name_vegetable[1]}
 \text{types=\name_vegetable[2]}
 \text{names=shuffle(\name_names_veg)}
}

\if{\r1=2}{
 \text{type=\name_fruit[1]}
 \text{types=\name_fruit[2]}
 \text{names=shuffle(\name_names_fruit)}
}

\integer{min=30}
\integer{max=70}

\text{prices=shuffle(\max-\min+1)}
\text{prices=wims(values (x+\min)/20 for x in \prices[1,2,3])}
\text{prices=(\prices[3]>\prices[1] and \prices[3]<\prices[2]) or
  (\prices[3]<\prices[1] and \prices[3]>\prices[2])
  ?\prices[1],\prices[3],\prices[2]}

\text{poids=randint(100)/5+4,randint(100)/5+4,randint(100)/5+4}
\text{poids=wims(values x for x in \poids)}
\text{poidt=wims(sum x for x in \poids)}
\real{s1=\prices[1]*\poids[1]}
\real{s2=\prices[2]*\poids[2]}
\real{s3=\prices[3]*\poids[3]}
\real{sum=\s1+\s2+\s3}
\if{\s1<\s2}{
 \real{diff=\s2-\s1}
 \text{ph=\diff \name_deplus[1] \names[2] \name_deplus[2] \names[1]}
}
\if{\s1>\s2}{
 \real{diff=\s1-\s2}
 \text{ph=\diff euros \name_deplus[1] \names[1] \name_deplus[2] \names[2]}
}
\if{\s1=\s2}{
 \text{ph=\name_deplus[3] \names[1] \name_deplus[2] \names[2]}
}

\statement{\name_instruction[1] \poidt \name_instruction[2] \types (\names[1]
\name_instruction[3] \prices[1] \name_instruction[4],
\names[2] \name_instruction[3] \prices[2] \name_instruction[4],
\names[3] \name_instruction[3] \prices[3] \name_instruction[4])
\name_instruction[5] \sum \name_instruction[6].
<p>
\name_question[1] \ph, \name_question[2] \types?
</p>
}

\answer{\names[1] \name_prompt}{\poids[1]}
\answer{\names[2] \name_prompt}{\poids[2]}
\answer{\names[3] \name_prompt}{\poids[3]}
