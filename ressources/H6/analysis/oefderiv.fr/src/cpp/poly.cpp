target=poly poly2
#if defined TARGET_poly
# define NUM I
#endif
#if defined TARGET_poly2
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
\real{b=randint(20..200)/10*random(-1,1)}
\real{c=randint(20..200)/10*random(-1,1)}
#if defined TARGET_poly
\real{a=randint(2..6)*random(-1,1)}
\real{d=randint(20..200)/10*random(-1,1)}
\integer{x0=random(-10..10)}
\function{p=\a*x^3+\b*x^2+\c*x+\d}
#endif
#if defined TARGET_poly2
\real{a=randint(20..200)/10*random(-1,1)}
\function{p=(x+\a)*(x+\b)*(x+\c)}
#endif
\text{hp=texmath(\p)}
\function{der=diff(\p,x)}
#if defined TARGET_poly
\real{sol=evalue(\der,x=\x0)}
#endif

\statement{\name_enonce
\(f(x) = \hp\)
#if defined TARGET_poly
\name_at \(x=\x0\)
#endif
.}

#if defined TARGET_poly
\answer{\(f '(\x0)\)}{\sol}{type=numeric}
\solution{\name_sol[1] \(f '(x)=\der\),
\name_sol[2] \(f '(\x0)=\sol\).}
#endif
#if defined TARGET_poly2
\answer{\(f '(x)\)}{\der}{type=formal}
#endif
