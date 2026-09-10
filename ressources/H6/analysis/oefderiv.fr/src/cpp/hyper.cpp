target=hyper hyper2
#include "xiao.inc"
#if defined TARGET_hyper
# define NUM I
#endif
#if defined TARGET_hyper2
# define NUM II
#endif
\computeanswer{yes}
\format{html}
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\integer{a1=randint(2..9)*random(-1,1)}
\integer{a2=randint(2..9)*random(-1,1)}
\integer{a3=randint(2..9)*random(-1,1)}
\integer{b1=randint(1..9)*random(-1,1)}
\integer{b2=randint(1..9)*random(-1,1)}
\integer{b3=randint(1..9)*random(-1,1)}
\integer{p1=randint(2..5)}
\integer{p2=randint(2..5)}
#if defined TARGET_hyper
\function{p=random(
	sh(\a1*x+\b1),
	ch(\a1*x+\b1),
	sh(\a1*x)+ch(\a2*x),
	sh(\a1*x)+th(\a2*x),
	ch(\a1*x)+th(\a2*x),
	\a1*sh(\a2*x+\b1),
	\a1*ch(\a2*x+\b1),
	\a1*x*sh(\a2*x+\b1),
	\a1*x*ch(\a2*x+\b1),
	sh(\a1*x^\p1),
	ch(\a1*x^\p1),
	th(\a1*x+\b1)
)}
#endif
#if defined TARGET_hyper2
\text{tfun1=random(ch,sh,th)}
\text{tfun2=random(ch,sh,th)}
\function{p=random(
	\tfun1(\tfun2(\a1*x)+\b1),
	\tfun1(\a1*x)^\p1,
	\a1/\tfun1(\a2*x+\b1),
	\a1*x/\tfun1(\a2*x+\b1),
	\a1*x^\p1*\tfun1(\a2*x),
	(\a1*\tfun1(x)+\b1)/(\a2*\tfun2(x)+\b2),
	\tfun1(\tfun2(\a1*x)^\p1)^\p2,
	x/\tfun1(\a1*x)^\p1
)}
#endif
\text{p=simplify(\p)}
\text{hp=texmath(\p)}
\function{der=diff(\p,x)}

\statement{\name_enonce \(f(x) = \hp\).}

\answer{\(f '(x)\)}{\der}{type=formal}

