target=defecritscien

#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\integer{ n1 = randint(3..6)}
\integer{ p = randitem(randint(5..7),randint(1..3))}
\real{ a = randint(10^(\n1)..10^(\n1 + 1)-1)}
\real{ b = \a/10^(\p)}
\real{ result =\a/10^(\n1)}
\real{ expos=\n1-\p}

\statement{
\name_statement \( A = \b\):
<div class="wimscenter">
 <label for="reply1">\(A = \)</label>
  \embed{ reply1 ,8} <label for="reply2">\(\times 10\)</label>
  <sup>\embed{reply2,3}</sup>
 </div>
}
\answer{}{\result}
\answer{}{\expos}
\latex{
\begin{statement}
  \name_statement \( A = \b\):
\begin{center}
 \(A = \cdots \times 10^{\cdots}\)
\end{center}
\end{statement}
}
