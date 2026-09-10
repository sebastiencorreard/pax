target=mult
#define NUM
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\precision{10000}

\integer{n=random(2..10)*random(1,-1)}
\text{n=\n >0 ? +\n}
\integer{m=random(2..10)*random(1,-1)}
\text{m=\m >0 ? +\m}
\integer{p=random(2..10)*random(1,-1)}
\text{p=\p >0 ? +\p}
\integer{sol= \n*(\m)*(\p)}
\text{sol = \sol>0 ? +\sol}

\statement{<p>\name_statement: </p>
<div class="wimscenter"><label for="reply1">
\((\n)\times (\m)\times (\p)\)</label> = \embed{reply 1, 12}
</div>}
\answer{}{\sol}{type=numeric}

\latex{
\begin{statement}
\name_statement:
\begin{center}
\((\n)\times (\m)\times (\p)\) = \(\dots\dots\)
\end{center}
\end{statement}
}
