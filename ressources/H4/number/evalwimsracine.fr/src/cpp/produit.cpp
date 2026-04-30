target= produit2,produit3,produit4,produit5,produit6,produit7


\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=5}

 \text{a=wims(values v for v=2 to 10)}
 \text{a=shuffle(\a)}

#if #TARGET(produit2)
 \title{Produit 2}
 \text{rep=sqrt(\a[1])*sqrt(\a[1])}
 \text{enonce=\sqrt{\a[1]}\times\sqrt{\a[1]}}
#endif

#if #TARGET(produit3)
 \title{Produit 3}
 \integer{rep=\a[2]*\a[1]}
 \integer{b=-\a[1]^2}
 \integer{c=-\a[2]^2}
 \text{enonce=\sqrt{\b\times(\c)}}
#endif

#if #TARGET(produit4)
 \title{Produit 4}
 \text{a=shuffle(2,3,5,6,7,8,10)}
 \text{rep=sqrt(\a[1]^2*\a[2]^2)}
 \integer{b=\a[1]^2*\a[2]}
 \integer{c=\a[2]}
 \text{b=shuffle(\b,\c)}
 \text{enonce=\sqrt{\b[1]}\times \sqrt{\b[2]}}
#endif

#if #TARGET(produit5)
 \title{Produit 5}
 \text{a=shuffle(2,3,5,6,7,8)}
 \real{b=\a[1]^2*\a[2]/100}
 \real{c=\a[2]}
 \text{rep=sqrt(\b*\c)}
 \text{b=shuffle(\b,\c)}
 \text{enonce=\sqrt{\b[1]}\times \sqrt{\b[2]}}
#endif

#if #TARGET(produit6)
 \title{Produit 6}
 \integer{base=10}
 \text{p=wims(values 2*v+1,-(2*v+1) for v=2 to 8)}
 \text{p=shuffle(\p)}
 \integer{rep=(\p[1]+(\p[2]))/2}
 \text{enonce=\sqrt{\base^{\p[1]}} \times \sqrt{\base^{\p[2]}}}
 \integer{affichage=1}
#endif

#if #TARGET(produit7)
 \title{Produit 7}
 \integer{base=randint(2..9)}
 \text{p=wims(values 2*v+1,-(2*v+1) for v=2 to 8)}
 \text{p=shuffle(\p)}
 \integer{rep=(\p[1]+(\p[2]))/2}
 \text{enonce=\sqrt{\base^{\p[1]}} \times \sqrt{\base^{\p[2]}}}
 \integer{affichage=1}
#endif

\text{rep=simplify(\rep)}


\statement{
Calculer l'expression suivante sans utiliser la calculette.
<div class="center"> \(\enonce =) 
\if{\affichage=1}{
 \base<sup>\embed{r1,\size}</sup>
}{
 \embed{r1,\size}
}</div>} 

\reply{Réponse 1}{\rep}{type=numexp}
