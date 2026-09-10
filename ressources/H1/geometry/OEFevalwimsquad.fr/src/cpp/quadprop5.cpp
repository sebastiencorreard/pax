target=oefquadprop5
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\format{html}

\matrix{pp= 1,2
1,2,4,5,6,7,9
1,2,3,4,5,6,7,8,9
1,2,3,4,5,6,8,9}

\matrix{ch=2,1
3,1
4,1
3,2
3,4
2,4
4,2}

\integer{a=randint(1..7)}
\text{ch=row(\a,\ch)}
\text{list1=row(\ch[1],\pp)}
\text{list2=row(\ch[2],\pp)}
\text{rep=wims(listcomplement \list2 in \list1)}
\text{latextext=}
\for{j=1 to 9}{
  \text{latextext=\latextext
  \item \prop[\j]}
}
\statement{\name_question[1] \nat[\ch[1]] \name_question[2] \nat[\ch[2]]:
<ul>\for{h=1 to 9}{<li>\embed{r1,\h}</li>}</ul>
}
\answer{}{\rep;\prop}{type=checkbox}

\latex{
\begin{statement}
\name_question[1] \nat[\ch[1]], \name_question[2] \nat[\ch[2]]:

\begin{checkbox}
\latextext
\end{checkbox}
\end{statement}
}
