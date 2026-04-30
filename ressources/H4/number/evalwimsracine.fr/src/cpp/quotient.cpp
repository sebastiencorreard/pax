target= quotient2,quotient3,quotient4,quotient5,quotient6,quotient7


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

#if #TARGET(quotient2)
 \title{Quotient 2}
 \integer{b=\a[1]*\a[2]^2}
 \integer{c=\a[1]}
 \text{b=shuffle(\b,\c)}
 \text{rep=simplify(sqrt(\b[1]/\b[2]))}
 \text{enonce=\frac{\sqrt{\b[1]}}{\sqrt{\b[2]}}}
#endif

#if #TARGET(quotient3)
 \title{Quotient 3}
 \text{a=shuffle(2,3,5,7,8,11,13)}
 \real{b=\a[1]*\a[2]^2/100}
 \integer{c=\a[1]}
 \text{b=\b,\c}
 \text{rep=simplify(sqrt(\b[1]/\b[2]))}
 \text{enonce=\frac{\sqrt{\b[1]}}{\sqrt{\b[2]}}}
#endif


#if #TARGET(quotient4)
 \title{Quotient 4}
 \text{a=shuffle(2,3,5,7,8,11,13)}
 \real{b=-\a[1]*\a[2]^2/100}
 \integer{c=-\a[1]}
 \text{b=\b,\c}
 \text{rep=simplify(sqrt(\b[1]/\b[2]))}
 \text{enonce=\sqrt{\frac{\b[1]}{\b[2]}}}
#endif

#if #TARGET(quotient5)
 \title{Quotient 5}
 \text{a=shuffle(3,5,7,8,11,13)}
 \real{b=\a[1]^2}
 \integer{c=\a[2]^2}
 \text{b=\b,\c}
 \text{rep=simplify(sqrt(\b[1]/\b[2]))}
 \text{enonce=\sqrt{\frac{\b[1]}{\b[2]}}}
#endif

#if #TARGET(quotient6)
 \title{Quotient 6}
 \integer{base=10}
 \text{p=wims(values 2*v+1,-(2*v+1) for v=2 to 8)}
 \text{p=shuffle(\p)}
 \integer{rep=(\p[1]-(\p[2]))/2}
 \text{enonce=\frac{\sqrt{\base^{\p[1]}}}{\sqrt{\base^{\p[2]}}}}
 \integer{affichage=1}
#endif

#if #TARGET(quotient7)
 \title{Quotient 7}
 \integer{base=randint(2..9)}
 \text{p=wims(values 2*v+1,-(2*v+1) for v=2 to 8)}
 \text{p=shuffle(\p)}
 \integer{rep=(\p[1]-(\p[2]))/2}
 \text{enonce=\frac{\sqrt{\base^{\p[1]}}}{\sqrt{\base^{\p[2]}}}}
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
