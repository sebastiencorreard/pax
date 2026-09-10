target=oefecrit105
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\langage{fr}
\format{html}

\integer{n1=randint(1..3)}
\integer{n2=randint(1..2)}
\integer{n3=randint(1..2)}
\text{chiffre=shuffle(9)}

\text{\nb1=}
\for{a=1 to \n1}
     {\text{nb1=wims(append item \chiffre[\a] to \nb1)}}
\text{\nb2=}
\for{a=1 to \n2}
     {\text{nb2=wims(append item \chiffre[\n1+\a] to \nb2)}}

\integer{res1=0}
\for{i=1 to \n1}{\integer{res1=\res1+\nb1[\i]*10^(\n1-\i)}}

\integer{res2=0}
\for{i=1 to \n2}
{\integer{res2=\res2+\nb2[\i]*10^(\n2-\i)}}

\integer{rep=\res1*10^(\n3+\n2)+\res2}

\text{ord=shuffle(\n+1)}
\text{dix=1,10,100,1 000,10 000,100 000}
\integer{large=5}

\statement{\name_statement:
  <div class="wimscenter">
  (\res1 x \dix[\n2+\n3 + 1]) + (\res2 x  1) = \embed{r1,\large}
  </div>
}

\answer{}{\rep}{type=numeric}

\latex{
\begin{statement}
\name_statement:
  (\res1 x \dix[\n2+\n3 + 1]) + (\res2 x  1)
\end{statement}
}

