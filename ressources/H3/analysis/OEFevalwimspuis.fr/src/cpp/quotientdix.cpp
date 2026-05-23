target=quotientdix1 quotientdix2 quotientdix3 quotientdix4 quotientdix5
#define TITRE Quotient de puissance de dix
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}

#if defined TARGET_quotientdix1
 \title{TITRE 1}
 \integer{M=max(\a[1],\a[2])}
 \integer{m=min(\a[1],\a[2])}
 \text{enonce=\frac{10^{\M}}{10^{\m}}}
 \integer{rep=\M-\m}
#endif

#if defined TARGET_quotientdix2
 \title{TITRE 2}
 \integer{M=max(\a[1],\a[2])}
 \integer{m=min(\a[1],\a[2])}
 \text{enonce=\frac{10^{-\M}}{10^{-\m}}}
 \integer{rep=-\M+\m}
#endif

#if defined TARGET_quotientdix3
 \title{TITRE 3}
 \integer{m=randitem(1,-1)*\a[1]}
 \text{enonce=\frac{1}{10^{\m}}}
 \integer{rep=-\m}
#endif

#if defined TARGET_quotientdix4
 \title{TITRE 4}
 \text{enonce=\frac{10^{-\a[1]}}{10^{\a[2]}}}
 \integer{rep=-\a[1]-\a[2]}
#endif

#if defined TARGET_quotientdix5
 \title{TITRE 5}
 \text{enonce=\frac{10^{\a[1]}}{10^{-\a[2]}}}
 \integer{rep=\a[1]+\a[2]}
#endif

\statement{
Effectuer le calcul suivant :
<div class="wimscenter"> \(\enonce = 10)<sup>\embed{r1,3}</sup>.</div>}

\answer{réponse}{\rep}{type=numexp}
