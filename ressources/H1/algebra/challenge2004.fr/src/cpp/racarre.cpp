target=racarre1 racarre2

#include "header.inc"
\precision{10000000}
#define TIT Racine et carré

#if defined TARGET_racarre1
 \title{TIT - a}
 \integer{r=random(10,11,12,13,14,15,17,18,19,20,21,22,23,24,26,27,28,29,30,31,32,33,34,35)}
 \integer{c=random(8..30)*random(1,-1)}
 \integer{n=ceil(-(\c*sqrt(\r)))}
 \function{exp=n + \c*sqrt(\r)}
#endif
#if defined TARGET_racarre2
 \title{TIT - b}
 \integer{n=random(10,11,12,13,14,15,17,18,19,20,21,22,23,24,26,27,
	28,29,30,31,32,33,34,35,
	37,38,39,40,41,42,43,44,45,46,47,48,
	50,51,52,53,54,55,56,57,58,59,60,61,62,63)}
 \integer{c=random(8..20)*random(1,-1)}
 \integer{t=ceil(-(\c*sqrt(\n)))}
 \function{exp=\t + \c*sqrt(n)}
#endif

\statement{
  Trouver un entier \(n) tel que
<div class="wimscenter">
    \((\exp)^2 < \exp) .
</div>
}

\reply{\(n)}{\nn}{type=number}

\real{isinteger=\nn-floor(\nn)}
#if defined TARGET_racarre1
 \real{test=\nn + \c*sqrt(\r)}
#endif
#if defined TARGET_racarre2
 \real{test=\t + \c*sqrt(\nn)}
#endif
\real{sqr=(\test)^2}
\condition{\((\exp)^2 < \exp)}{\isinteger=0 and \sqr < \test}
\feedback{\isinteger!=0}{
 \nn n'est pas un entier ! Réponse invalide.
}
\feedback{\isinteger=0 and \sqr >= \test}{
 Si \(n = \nn) : alors \(\exp = \test), et
 <div class="wimscenter">
   \( (\exp)^2 = \sqr >= \exp) !
 </div>
}

