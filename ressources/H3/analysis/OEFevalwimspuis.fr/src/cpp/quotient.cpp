target=quotient1 quotient2 quotient3 quotient4 quotient5
#define TITRE Quotient de puissance
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}
\integer{pui=randint(2..7)}

#if defined TARGET_quotient1
 \title{TITRE 1}
 \integer{M=max(\a[1],\a[2])}
 \integer{m=min(\a[1],\a[2])}
 \text{enonce=\frac{\pui^{\M}}{\pui^{\m}}}
 \integer{rep=\M-\m}
#endif

#if defined TARGET_quotient2
 \title{TITRE 2}
 \integer{M=max(\a[1],\a[2])}
 \integer{m=min(\a[1],\a[2])}
 \text{enonce=\frac{\pui^{-\M}}{\pui^{-\m}}}
 \integer{rep=-\M+\m}
#endif

#if defined TARGET_quotient3
 \title{TITRE 3}
 \integer{m=randitem(1,-1)*\a[1]}
 \text{enonce=\frac{1}{\pui^{\m}}}
 \integer{rep=-\m}
#endif

#if defined TARGET_quotient4
 \title{TITRE 4}
 \text{enonce=\frac{\pui^{-\a[1]}}{\pui^{\a[2]}}}
 \integer{rep=-\a[1]-\a[2]}
#endif

#if defined TARGET_quotient5
 \title{TITRE 5}
 \text{enonce=\frac{\pui^{\a[1]}}{\pui^{-\a[2]}}}
 \integer{rep=\a[1]+\a[2]}
#endif

\statement{
Effectuer le calcul suivant :
<div class="wimscenter"> \(\enonce = \pui)<sup>\embed{r1,3}</sup>.</div>}

\answer{réponse}{\rep}{type=numexp}
