target=regleadd
#define NUM
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}

\integer{a=randint(1..4)}
\integer{b=randint(\a+1..7)}
\integer{c=randint(\b+1..12)}
\integer{a=random(1,-1)*(\a)}
\integer{b=random(1,-1)*(\b)}
\integer{c=random(1,-1)*(\c)}
\text{signeb=random(+,-)}
\text{signea=random(+,-)}
\integer{ac=(\a) + (\c)}
\integer{bc=(\signeb 1)*(\b)+\c}

\text{aa=\a>0? +\a:\a}
\text{bb=\b>0? +\b:\b}
\text{cc=\c>0? +\c:\c}
\text{acc=\ac>0? +\ac:\ac}
\text{bcc=\bc>0? +\bc:\bc}
\text{A1= (\aa)+(\cc)\signeb (\bb)}
\text{signeb1=\signeb issametext +?-:+}
\integer{b1=(\signeb1 1)*(\signeb 1)*(\b)}
\text{bb1=\b1>0? +\b1:\b1}

\text{listeA=\signeb (\bb)+(\aa)+(\cc),(\cc)+(\aa)\signeb (\bb),(\aa)\signeb (\bb)+(\cc),(\cc)\signeb (\bb)+ (\aa)
(\acc)\signeb(\bb),(\aa)+(\bcc), ((\aa)+(\cc))\signeb (\bb), (\aa)+((\cc)\signeb (\bb))
(\aa)+(\cc)\signeb1 (\bb1)
}
\text{s=random(1,2,3)}
\text{A2=randitem(row(\s,\listeA))}
\text{sol=item(\s,\choix)}
\statement{\name_statement?
<div class="wimscenter">
\(\begin{array}{ccl}
A&=& \A1 \\\
A&=& \A2
\end{array}\)
</div>
}

\choice{}{\sol}{\choix}

\latex{
\begin{statement}
\name_statement?
\begin{center}
\(\begin{array}{ccl}
A&=& \A1 \\\
A&=& \A2
\end{array}\)
\end{center}
\begin{radio}
\item \choix[1]
\item \choix[2]
\item \choix[3]
\item \choix[4]
\end{radio}
\end{statement}
}
