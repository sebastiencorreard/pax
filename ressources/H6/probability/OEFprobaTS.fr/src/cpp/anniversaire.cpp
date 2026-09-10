target=anniversaire
\title{F4. Anniversaires}
\language{fr}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\keywords{events,modelling,probability}
\description{Exercice de modélisation}
\observation{Seul le nombre de personnes choisies peut varier lorsqu'on recommence l'exercice}
\computeanswer{no}
\format{html}
\precision{9000}

\integer{people=random(20..60)}
\real{sol=item(\people-19,
0.4114383835,
0.4436883351,
0.4756953076,
0.5072972343,
0.5383442579,
0.5686997039,
0.5982408201,
0.6268592822,
0.6544614723,
0.6809685374,
0.7063162427,
0.7304546337,
0.7533475278,
0.7749718541,
0.7953168646,
0.8143832388,
0.8321821063,
0.8487340082,
0.8640678210,
0.8782196643,
0.8912318098,
0.9031516114,
0.9140304715,
0.9239228556,
0.9328853685,
0.9409758994,
0.9482528433,
0.9547744028,
0.9605979728,
0.9657796093,
0.9703735795,
0.9744319933,
0.9780045093,
0.9811381134,
0.9838769627,
0.9862622888,
0.9883323548,
0.9901224593,
0.9916649794,
0.9929894484,
0.9941226608)}
\real{solbar=1-\sol}
\text{name_enonce=Si l'on suppose que les jours d'anniversaire sont
 répartis équitablement parmi les 365 jours de l'année et si l'on
 choisit \people personnes au hasard dans l'annuaire, quelle est la probabilité
 pour que deux au moins de ces \people personnes aient leur anniversaire le même jour&nbsp;}
\text{name_consigne=La réponse est demandée avec au moins 4 chiffres significatifs.}
\text{name_hint=Calculer plutôt la probabilité pour que ces \people personnes
 aient toutes leur anniversaire un jour différent.}
\text{name_prob=La probabilité est égale à}
\text{name_sol1=Soit \(A\) l'événement&nbsp; <span class="wims_emph">"les \people personnes ont toutes leur anniversaire un jour différent".
</span>}
\text{name_or=où}
\text{name_sol2= désigne le nombre d'arrangements de \people éléments parmi 365 soit}
\text{name_sol3=Donc la probabilité cherchée est}

\statement{\name_enonce?
<div class="wimscenter"><label for="reply1">\name_prob</label> \embed{reply1,7}</div>
<div class="wims_instruction">\name_consigne</div>
}

\answer{\name_prob}{\sol}{type=numeric}
\hint{\name_hint}
\solution{\name_sol1<p>
\(P(A)=\frac{A_{365}^{\people}}{365^{\people}}=\solbar\)
\name_or \(A_{365}^{\people}\) \name_sol2 \(\frac{365!}{(365-\people)!}\).
</p><p>
\name_sol3 \(1-P(A)\simeq\sol\).
</p>
}
\latex{
\begin{statement}
\name_enonce
(\emph{\small \name_consigne})
\end{statement}
\begin{solution}
\name_sol1\newline
\(P(A)=\frac{A_{365}^{\people}}{365^{\people}}=\solbar\)
\name_or \(A_{365}^{\people}\) \name_sol2 \(\frac{365!}{(365-\people)!}\).
\newline
\name_sol3 \(1-P(A)\simeq\sol\).
\end{solution}
}
