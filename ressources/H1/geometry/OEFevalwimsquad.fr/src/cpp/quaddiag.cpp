target=oefquaddiag2 oefquaddiag3
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}


\integer{r=randint(1..4)}
#if defined TARGET_oefquaddiag2
\text{quad=\nat[\r]}
#endif
#if defined TARGET_oefquaddiag3
\text{quad=\name_quad}
#endif
\text{prop=wims(replace internal XXXX by \quad in \prop)}
#if defined TARGET_oefquaddiag2
\matrix{pp= 1
1,2,5
1,2,3,5
1,3,5}
\text{enonc=\nat[\r]&nbsp;:}
\text{nb=5}
#endif
#if defined TARGET_oefquaddiag3
\matrix{pp= 1,2,3,4
2,3
3,4
2,3,4}
\text{enonc=<p>\prop[\r]</p>}
\text{nb=4}
#endif
\text{rep=row(\r,\pp)}

#if defined TARGET_oefquaddiag2
\text{liste=\prop}
#endif
#if defined TARGET_oefquaddiag3
\text{liste=\nat}
#endif
\text{latextext=}
\for{k=1 to \nb}{
  \text{latextext=\latextext
\item \liste[\k]}
}

\statement{
\name_question \enonc
<ul>\for{h=1 to \nb}{<li>\embed{r1,\h}</li>}</ul>
}
#if defined TARGET_oefquaddiag2
\answer{}{\rep;\prop}{type=checkbox}
#endif
#if defined TARGET_oefquaddiag3
\answer{}{\rep;\nat}{type=checkbox}
#endif

\latex{
\begin{statement}
\name_question \par
\enonc
\par
\begin{checkbox}
\latextext
\end{checkbox}
\end{statement}
}
