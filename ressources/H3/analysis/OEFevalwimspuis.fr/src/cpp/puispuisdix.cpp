target=puispuisdix1 puispuisdix2 puispuisdix3 puispuisdix4 puispuisdix5
#define TITRE Puissance de puissance de dix
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}

#if defined TARGET_puispuisdix1
 \title{TITRE 1}
 \text{enonce=(10^{\a[1]})^\a[2]}
 \integer{rep=\a[1]*\a[2]}
#endif

#if defined TARGET_puispuisdix2
 \title{TITRE 2}
 \text{enonce=(10^{-\a[1]})^\a[2]}
 \integer{rep=-\a[1]*\a[2]}
#endif

#if defined TARGET_puispuisdix3
 \title{TITRE 3}
 \text{enonce=(10^{-\a[1]})^{-\a[2]}}
 \integer{rep=\a[1]*\a[2]}
#endif

#if defined TARGET_puispuisdix4
 \title{TITRE 4}
 \text{enonce=\frac{1}{(10^{\a[2]})^{\a[1]}}}
 \integer{rep=-\a[1]*\a[2]}
#endif

#if defined TARGET_puispuisdix5
 \title{TITRE 5}
 \text{enonce=(\frac{1}{10^{-\a[2]}})^{\a[1]}}
 \integer{rep=\a[1]*\a[2]}
#endif

\statement{
Effectuer le calcul suivant :
<div class="wimscenter"> \(\enonce = 10)<sup>\embed{r1,3}</sup>.</div>}

\answer{réponse}{\rep}{type=numexp}
