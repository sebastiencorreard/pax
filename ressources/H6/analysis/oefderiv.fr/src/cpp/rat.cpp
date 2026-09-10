target=rat rat2
#if defined TARGET_rat
# define NUM I
#endif
#if defined TARGET_rat2
# define NUM II
#endif
\language{fr}
\range{-5..5}
#include "xiao.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}
\format{html}
\precision{10000}

\integer{a1=randint(2..9)*random(-1,1)}
\integer{a2=randint(2..9)*random(-1,1)}
\integer{a3=randint(2..9)*random(-1,1)}
\integer{b1=randint(1..9)*random(-1,1)}
\integer{b2=randint(1..9)*random(-1,1)}
\integer{b3=randint(1..9)*random(-1,1)}
\integer{p1=randint(2..5)}
\integer{p2=randint(2..5)}
#if defined TARGET_rat
\function{p=random(
	\b1/x+\b2/x^2+\b3/x^3,
	(x+\b1)/(x+\b2),
	\b1/(\a1*x+\b2),
	(\a1*x+2)/(\a2*x+5),
	(\a1*x^2+\a2*x+\b1)/(x+\b2),
	\a1*x/(\a2*x+1)^\p1,
	\b1/(x+\b2)^\p1,
	x^\p1/(\a1*x+\b1)
)}
#endif
#if defined TARGET_rat2
\function{p=random(
	\a1*x/(\a2*x^2+\a3*x+\b1),
	(x^2+\a1*x+1)/(x^2+\a2*x-1),
	\a1*x/((x+\b1)*(x+\b2)*(x+\b3)),
	(2*x+\b1)^\p1/(7*x+\b2)^\p2,
	(x^2+\a2*x+\b1)/(\a3*x^3+\b2)
)}
#endif
\
\text{hp=simplify(\p)}
\function{der=diff(\p,x)}
\statement{\name_enonce \( f(x) = \hp\).}

\answer{\(f '(x)\)}{\der}{type=formal}

