target=binome1 binome2
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\keywords{combinatorics,combination}
\description{Pour se familiariser avec  la formule du binôme de Newton}
#define TITRE Formule du binôme
#if defined TARGET_binome1
# define NUM 1
#endif
#if defined TARGET_binome2
# define NUM 2
#endif
\title{C. TITRE NUM}
\text{enonce= En utilisant la formule du binôme, développer l'expression}
#if defined TARGET_binome1
\integer{n=randint(3..7)}
\integer{i=randint(1,2)}
\text{quest=\i=1?(a+b)^\n:(a-b)^\n}
\text{rep=\i=1?maxima(expand((a+b)^\n)):maxima(expand((a-b)^\n))}
\text{texquest=texmath(\quest)}
\text{texrep=texmath(\rep)}
\statement{
  \enonce :
<div class="wimscenter"><label for="reply1">\(\quest=\)</label>\embed{reply1}</div>
<div class="wims_instruction">
  Ne pas oublier d'écrire le symbole * de la multiplication dans le produit \(a^n\times b^p\).
</div>
}
\answer{}{\rep}{type=formal}
#endif
#if defined TARGET_binome2
\integer{x=randint(1,2)*randint(1,-1)}
\integer{n=randint(3..7)}
\integer{i=randint(1,2)}
\text{quest=\i=1?maxima(1+\x*a):maxima(a+\x)}
\text{quest=(\quest)^\n}
\text{rep=\i=1?maxima(expand((1+\x*a)^\n)):maxima(expand((a+\x)^\n))}
\text{texquest=texmath(\quest)}
\text{texrep=texmath(\rep)}
\statement{
 \enonce :
<div class="wimscenter"><label for="reply1">\(\quest=\)</label>\embed{reply1}.</div>
}
\answer{}{\rep}{type=formal}
#endif
\latex{
\begin{statement}
\enonce \[\texquest.\]
\end{statement}
\begin{solution}
\(\texquest = \texrep.\)
\end{solution}
}
