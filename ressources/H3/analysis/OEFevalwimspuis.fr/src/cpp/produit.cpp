target=produit1 produit2 produit3 produit4
#define TITRE Produit de puissance
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=wims(values v for v=2 to 9)}
\text{a=shuffle(\a)}
\integer{pui=randint(2..7)}

#if defined TARGET_produit1
 \title{TITRE 1}
 \text{enonce=\pui^{\a[1]} \times \pui^{\a[2]}}
 \integer{rep=\a[1]+\a[2]}
#endif

#if defined TARGET_produit2
 \title{TITRE 2}
 \text{enonce=randitem(\pui^{-\a[1]}\times \pui^{\a[2]},\pui^{\a[2]}\times \pui^{-\a[1]})}
 \integer{rep=-\a[1]+\a[2]}
#endif

#if defined TARGET_produit3
 \title{TITRE 3}
 \text{enonce=\pui^{-\a[1]}\times \pui^{-\a[2]}}
 \integer{rep=-\a[1]-\a[2]}
#endif

#if defined TARGET_produit4
 \title{TITRE 4}
 \text{sg=randrow(shuffle(,,-,-)
shuffle(,,,-))}
 \integer{b=\sg[4]\a[4]}
 \integer{rep=\sg[1]\a[1]+\sg[2]\a[2]+\sg[3]\a[3]+\b}
 \if{\rep=0}{
  \integer{b=\b+1}
  \integer{rep=1}
 }
 \text{enonce=\pui^{\sg[1]\a[1]}\times \pui^{\sg[2]\a[2]} \times \pui^{\sg[3]\a[3]} \times \pui^{\b}}
#endif

\statement{
Effectuer le calcul suivant :
<div class="wimscenter"> \(\enonce = \pui)<sup>\embed{r1,3}</sup>.</div>}

\answer{réponse}{\rep}{type=numexp}
