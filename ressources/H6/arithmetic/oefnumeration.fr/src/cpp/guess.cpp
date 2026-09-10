target=guess

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}
\text{ carte = pari(A = matrix(6,32) ; B =vector(6) ;
for(i = 1, 63, u = binary(i) ;
  for (j = 1 , 6,
    if ( j <= #u && u[#u + 1 - j] !=0,
      B[j] ++ ; A[j,B[j]] = i )
  )
) ;
for( j = 1, 6 , B[j] = matrix(4,8,n,m,A[j, 8*(n-1) + m])) ;print(B)
)}

\text{N =randint(1..63)}
\text{bin = pari(u = binary(\N) ; B =vector(6) ;
  for (j = 1 , 6,
    if ( j <= #u && u[#u + 1 - j] == 1, B[j] = 1 )
  ) ;
  B
 )}
 &#10003;
\text{color=skyblue,yellow}
\matrix{CARTE =}
\for{j = 1 to 6 }{
  \text{Carte= \carte[\j]}
  \matrix{Carte= wims(declosing \Carte)}
  \text{B=<table><tr><th colspan="8">}
  \text{B=\bin[\j]+1=2?\B \(X\):\B\(\phantom{X}\)}
  \text{B=\B</th></tr>}
  \for{h = 1 to 4}{
    \text{B =\B<tr>}
    \for{l = 1 to 8}{
      \text{B = \B<td style="background-color:\color[\bin[\j]+1]"> \Carte[\h;\l]</td>}
    }
    \text{B = \B </tr>}
  }
  \matrix{CARTE = \CARTE
  \B</table>}
}
\text{a = shuffle(6)}

#include "lang.inc"

\statement{\name_statement
<table class="wimscenter wimsborder">
  <tr>\for{r = 1 to 3}{<td>\CARTE[\a[\r];]</td>}
  </tr><tr>
  \for{r = 4 to 6}{<td>\CARTE[\a[\r];]</td>}
  </tr></table>
}
\answer{\name_answer}{\N}
\hint{\name_hint}
