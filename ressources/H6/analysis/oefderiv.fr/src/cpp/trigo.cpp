target=trigo trigo2 trigo3
#if defined TARGET_trigo
# define NUM I
#endif
#if defined TARGET_trigo2
# define NUM II
#endif
#if defined TARGET_trigo3
# define NUM III
#endif
#include "xiao.inc"
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
#if defined TARGET_trigo || defined TARGET_trigo3
\function{p=random(
	sin(\a1*x+\b1),
	cos(\a1*x+\b1),
	sin(\a1*x)+cos(\a2*x),
	sin(\a1*x)+tan(\a2*x),
	cos(\a1*x)+tan(\a2*x),
	\a1*sin(\a2*x+\b1),
	\a1*cos(\a2*x+\b1),
	\a1*x*sin(\a2*x+\b1),
	\a1*x*cos(\a2*x+\b1),
	sin(\a1*x^\p1),
	cos(\a1*x^\p1),
	tan(\a1*x+\b1)
)}
#endif
#if defined TARGET_trigo2
\text{tfun1=random(cos,sin,tan)}
\text{tfun2=random(cos,sin,tan)}
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
#if defined TARGET_trigo3
\integer{x0=random(-4..4)}
\function{der=diff(\p,x)}
\real{sol=evalue(\der,x=\x0)}
#endif
\statement{\name_enonce[1]
\(f(x) = \hp\)
#if defined TARGET_trigo3
\name_enonce[2] \(x=\x0\)
#endif
.}
#if defined TARGET_trigo3
\answer{\(f '(\x0)\)}{\sol}
#endif
#if defined TARGET_trigo || defined TARGET_trigo2
\answer{\(f'(x)\)}{\der}{type=formal}
#endif
