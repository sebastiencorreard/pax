target=denombrable
#define GGG E1 -
\title{GGG Dénombrabilité}
\description{exercice de type QCM sur la définition d'ensembles dénombrables.}
\observation{La question porte sur un ensemble simple choisi parmi 13 ensembles.}
\keywords{set_theory}
\language{fr}
\range{1..5}
\author{Mounir, Mensi}
\email{mounirmensi@yahoo.fr}
\computeanswer{no}
\format{html}
\precision{10000}
#include "common.inc"

\matrix{Ed=\NN,\NN^\ast,\QQ,\ZZ,\{1/n; n\in\NN^\ast \},\{\frac{1}{n m}; (n,m)\in\NN^\ast\times\NN^\ast\},\NN^2,\ZZ^2
\displaystyle{\lbrack 0, 1 \rbrack}, \RR,\{0, 1\}^{\NN},\RR_{+},\displaystyle{\lbrack 0, 1 \rbrack^2}
}
\text{n=randint(1..2)}
\text{E= randitem(\Ed[\n;])}
#include "lang_denombrable_fr.inc"
\if{\lang=it}{
#include "lang_denombrable_it.inc"
}
\if{\lang=es}{
#include "lang_denombrable_es.inc"
}
\statement{\instruction?
<div class="wimscenter"> \embed{reply1}</div>
}

\answer{}{\n;\poss}{type=radio}
