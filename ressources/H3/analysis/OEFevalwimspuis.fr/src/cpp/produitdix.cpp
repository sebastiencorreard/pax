target=produitdix1 produitdix2 produitdix3 produitdix4 produitdix5
#define TITRE Produit de puissance de dix
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}

#if defined TARGET_produitdix1
 \title{TITRE 1}
 \text{enonce=10^{\a[1]} \times 10^{\a[2]}}
 \integer{rep=\a[1]+\a[2]}
#endif

#if defined TARGET_produitdix2
 \title{TITRE 2}
 \text{enonce=randitem(10^{-\a[1]}\times 10^{\a[2]},10^{\a[2]}\times 10^{-\a[1]})}
 \integer{rep=-\a[1]+\a[2]}
#endif

#if defined TARGET_produitdix3
 \title{TITRE 3}
 \text{enonce=10^{-\a[1]}\times 10^{-\a[2]}}
 \integer{rep=-\a[1]-\a[2]}
#endif

#if defined TARGET_produitdix4
 \title{TITRE 4}
 \text{enonce=10^{\a[1]}\times 10^{\a[2]} \times 10^{\a[3]}}
 \integer{rep=\a[1]+\a[2]+\a[3]}
#endif

#if defined TARGET_produitdix5
 \title{TITRE 5}
 \text{sg=randrow(shuffle(,,-,-)
shuffle(,,,-))}
 \integer{b=\sg[4]\a[4]}
 \integer{rep=\sg[1]\a[1]+\sg[2]\a[2]+\sg[3]\a[3]+\b}
 \if{\rep=0}{
  \integer{b=\b+1}
  \integer{rep=1}
 }
 \text{enonce=10^{\sg[1]\a[1]}\times 10^{\sg[2]\a[2]} \times 10^{\sg[3]\a[3]} \times 10^{\b}}
#endif

\statement{
Effectuer le calcul suivant :
<div class="wimscenter"> \(\enonce = 10)<sup>\embed{r1,3}</sup>.</div>}

\answer{réponse}{\rep}{type=numexp}
