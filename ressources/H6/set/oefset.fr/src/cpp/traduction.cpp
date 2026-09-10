target=traduction1 traduction2 traduction3

#include "css.inc"
#include "common.inc"
#if defined TARGET_traduction1
# define GGG D2 -
#elif defined TARGET_traduction2
# define GGG A2 -
#elif defined TARGET_traduction3
# define GGG A1 -
#endif
#include "lang_traduction_fr.inc"
\if{\lang=it}{
#include "lang_traduction_it.inc"
}
\if{\lang=es}{
#include "lang_traduction_es.inc"
}
#if defined TARGET_traduction1
\title{GGG Associer événements et ensembles}
\text{M=1}
#elif defined TARGET_traduction2
\title{GGG Ensembles : description mathématique}
\text{M=3}
#elif defined TARGET_traduction3
\title{GGG Description des éléments d'un ensemble}
\text{M=3}
#endif
#if defined TARGET_traduction1
\description{exercice permettant de se familiariser avec la description ensembliste d'un événement.}
\observation{Les événements sont décrits à partir d'opérations sur au plus 3 ensembles.}
\keywords{set_theory,events}
#else
\description{exercice permettant de se familiariser avec les notations ensemblistes.}
\keywords{set_theory}
#endif
\language{fr}
\computeanswer{no}
\format{html}
\author{Sophie, Lemaire; Bernadette, Perrin-Riou}
\email{sophie.lemaire@universite-paris-saclay.fr,bernadette.m.riou@orange.fr}

\matrix{a = wims(record \M of tableau.\lang)}
\matrix{b = wims(record 2 of tableau.\lang)}

\text{cnt= rows(\a)}
\text{n=4}

\text{mix=item(1..\n, shuffle(\cnt))}
\text{ABC = shuffle(A,B,C)}

\text{U=\a[\mix;1] }
\text{V=\b[\mix;1] }
\text{U = wims(replace internal XXX by \(\ABC[1]\) in \U)}
\text{U = wims(replace internal YYY by \(\ABC[2]\) in \U)}
\text{U = wims(replace internal ZZZ by \(\ABC[3]\) in \U)}

\text{V = wims(replace internal XXX by \ABC[1] in \V)}
\text{V = wims(replace internal YYY by \ABC[2] in \V)}
\text{V = wims(replace internal ZZZ by \ABC[3] in \V)}

#if defined TARGET_traduction2 || defined TARGET_traduction3
\text{U = wims(replace internal uuu by \(x\) in \U)}
#endif

#if defined TARGET_traduction3
\text{V = wims(makelist x \in S for S in \V)}
#endif

\for{i = 1 to \n}{
\text{V = wims(replace internal item number \i by \(\V[\i]\) in \V)}
}
\text{NB=wims(record 1 of notations.\lang)}
\text{instruction1=wims(record 3 of notations.\lang) wims(record 4 of notations.\lang) wims(record 5 of notations.\lang)}
\statement{
#if defined TARGET_traduction1
<div class="color1">
\instruction1
</div>
<div class="wims_question">
\name_question
#else
\instruction
<div class="wims_question">
# if defined TARGET_traduction2
\name_question?<br>
\name_instruction
# else
\name_question
# endif
#endif

<div class="wimscenter">\embed{reply 1,90 x 230 x 320}</div>
</div>}

\answer{}{\U;\V}{type=correspond}{option=split}
\help{\NB}
