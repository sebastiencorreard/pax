target=oefecrit103
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}

\integer{n=randint(2..3)}
\text{chiffre=shuffle(9)}
\text{\chiff=}
\for{a=2 to \n}
     {\text{chiff=wims(append item \chiffre[\a] to \chiff)}}
\text{chiff=wims(append item 0 to \chiff)}
\text{chiff=shuffle(\chiff)}

\text{chiff=\chiffre[1],\chiff}
\text{chiff=wims(append item \chiffre[\n + 1] to \chiff)}
\integer{nb=0}
\for{i=1 to \n + 2}
{\integer{nb=\nb+\chiff[\i]*10^(\i-1)}}
\text{ord=}
   \for{a=1 to \n + 2}
     {\text{ord=position(0,\chiff)}}

\integer{nb1=0}
\for{i=1 to \ord - 1}
{\integer{nb1=\nb1+\chiff[\i]*10^(\i-1)}}

\integer{nb2=0}
\for{i=\ord + 1  to \n + 2}
{\integer{nb2=\nb2+\chiff[\i]*10^(\i-1-\ord)}}

\text{dix=1,10,100,1 000,10 000,100 000}
\integer{large=5}
\text{rep1=\dix[\ord + 1]}
\text{rep2=1}

\statement{
\name_statement: <div class="wimscenter">\(\nb =\)
(\nb2 x \embed{r1,\large}) + (\nb1 x \embed{r2,\large})
</div>}


\answer{}{\rep1}{type=numeric}
\answer{}{\rep2}{type=numeric}

\latex{
\begin{statement}
\name_statement:
  \(\nb = (\nb2 x \cdots\cdots) + (\nb1 x \cdots)\)
\end{statement}
}
