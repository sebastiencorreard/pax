target=oefmentprop1 oefmentprop2 oefmentprop3 oefmentprop4 oefmentprop5

\keywords{proportionality}
#include "author.inc"
\precision{100000}
#if defined TARGET_oefmentprop1
# define NUM 1
#endif
#if defined TARGET_oefmentprop2
# define NUM 2
#endif
#if defined TARGET_oefmentprop3
# define NUM 3
#endif
#if defined TARGET_oefmentprop4
# define NUM 4
#endif
#if defined TARGET_oefmentprop5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"

\integer{a=randint(1..10)}
\text{f=\name_f[\a]}

#if defined TARGET_oefmentprop1
# define NUM 1
\integer{op=randint(2..8)}
\integer{q=1}
\integer{p=\op*\q}
\integer{tmp=randint(2..9)}
\integer{qf=\q*\tmp}
\integer{rep=\op*\qf}
\text{sol=\(\q \ \kg \times \tmp = \qf \ \kg\) et \(\p \ \euro \times \tmp = \rep \ \euro\).}
#endif
#if defined TARGET_oefmentprop2
# define NUM 2
\integer{op=randint(2..8)}
\integer{qf=1}
\integer{q=randint(2..9)}
\integer{p=\op*\q}
\integer{rep=\op}
\text{sol=\(\q \ \kg \div \q = \qf \ \kg\) et \(\p \ \euro \div \q = \rep \ \euro\).}
#endif
#if defined TARGET_oefmentprop3
# define NUM 3
\integer{op=randint(2..8)}
\integer{q=randint(2..5)}
\integer{tmp=randint(2..5)}
\integer{qf=\q*\tmp}
\integer{p=\op*\q}
\integer{rep=\op*\qf}
\text{sol=\(\q \ \kg \times \tmp = \qf \ \kg\) et \(\p \ \euro \times \tmp = \rep \ \euro\).}
#endif
#if defined TARGET_oefmentprop4
# define NUM 4
\integer{op=randint(2..8)}
\text{q=shuffle(2,3,5,7,11,13,17,19)}
\integer{qf=\q[1]}
\integer{q=\q[2]}
\integer{p=\op*\q}
\integer{rep=\op*\qf}
\text{sol=\(\q \ \kg\) coûtent \(\p \ \euro\) donc \(1 \ \kg\) coûte \(\frac{\p}{\q}=\op \ \euro\).
<p>Ainsi, \(\qf \ \kg\) coûtent \(\qf \times \op = \rep \ \euro\).</p>}
#endif
#if defined TARGET_oefmentprop5
# define NUM 5
\real{op=randint(2..5)+ randint(1..9)/10}
\integer{q=randint(2..5)}
\integer{tmp=randint(2..5)}
\integer{qf=\q*\tmp}
\real{p=\op*\q}
\real{rep=\op*\qf}
\text{sol=\(\q \ \kg \times \tmp = \qf \ \kg\) et \(\p \ \euro \times \tmp = \rep \ \euro\).}
#endif
#include "lang_titles.inc"
#include "lang.inc"

\real{repsol=\p*\qf/\q}

\statement{
<div class="wims_question">
\name_instruction[1] \q kg \f \name_instruction[2] \p &euro;.
\name_instruction[3] \qf kg ?
</div>
<div class="spacer">
<label for="reply1">\name_instruction[4] \qf kg \f \name_instruction[2]</label>
  \embed{r1,5} &euro;.</div>
}
\answer{}{\rep}{type=numeric}

\solution{C'est une situation de proportionnalité.
<p>\sol</p>
\name_instruction[4] \qf kg \f \name_instruction[2] \repsol &euro;.}

\latex{
\begin{statement}
\name_instruction[1] \q kg \f \name_instruction[2] \p &euro;. \name_instruction[3] \qf kg ?\par
\qf kg \f \name_instruction[2] \dotfill &euro;
\end{statement}

\begin{solution}
\name_instruction[4] \qf kg \f \name_instruction[2] \rep &euro;.
\end{solution}
}
