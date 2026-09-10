target=encadr
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang.inc"
\integer{n=randint(3..6)}
\integer{p=randitem(randint(5..7),randint(1..3))}
\real{a=randint(10^(\n)..10^(\n+1)-1)}
\real{A=\a/10^(\p)}

\real{sol1= \n-(\p)}
\real{sol2=\n-(\p)+1}

\statement{\name_statement[1] \(\A\) \name_statement[2]
 <div class="wimscenter">
 <label for="reply1">10</label><sup><sup>\embed{reply 1,4}</sup></sup>\(\leq) \A
 \(\lt\) <label for="reply1">10</label><sup><sup>\embed{reply 2,4}</sup></sup>
</div>
}
\answer{\name_answer1}{\sol1}{type=numeric}
\answer{\name_answer2}{\sol2}{type=numeric}
\hint{\name_hint}
\latex{
\begin{statement}
\name_statement[1] \(\A\) \name_statement[2].
\begin{center}\(10^{\cdots} \leq \A < 10^{\cdots}\)\end{center}
\end{statement}
}
