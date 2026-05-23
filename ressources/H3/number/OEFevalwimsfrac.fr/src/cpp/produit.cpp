target=produit1 produit2 produit3 produit4 produit5

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\integer{a=randint(1..15)}
\integer{b=randint(1..15)}
\integer{g=gcd(\a,\b)}
\integer{a=\a/\g}
\integer{b=\b/\g}
\if{\a=1 or \b=1}{
 \integer{a=2}
 \integer{b=3}
}
\text{v=wims(values \a*v,\b*v for v=1 to 10)}
\text{v2=wims(values v for v=6 to 30)}
\text{v=wims(listcomplement \v in \v2)}
\text{v=shuffle(\v)}

#if defined TARGET_produit2
 \title{Multiplication 2}
 \integer{N1=\v[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]}
 \integer{D2=\b}
#endif

#if defined TARGET_produit1
 \title{Multiplication 1}
 \integer{N1=\v[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]}
 \integer{D2=\D1}
#endif

#if defined TARGET_produit3
 \title{Multiplication 3}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]*\sg[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]*\sg[2]}
 \integer{D2=\b}
#endif

#if defined TARGET_produit5
 \title{Multiplication 5}
 \integer{c=randitem(2,3,5)}
 \real{N1=-\v[1]}
 \integer{D1=\a*\c}
 \real{N2=-\v[2]}
 \integer{D2=\b*\c}
#endif

#if defined TARGET_produit4
 \title{Multiplication 4}
 \text{sg=shuffle(1,1,-1,-1)}
 \integer{N1=\v[1]*\sg[1]}
 \integer{N2=\v[2]*\sg[2]}
 \integer{D2=\b}
 \integer{D1=1}
 \text{aff1=\N1<0?(\N1):\N1}
 \text{enonce=randitem(\N1 \times \frac{\N2}{\D2},\frac{\N2}{\D2} \times \aff1)}
#else
 \text{enonce=\frac{\N1}{\D1} \times \frac{\N2}{\D2}}
#endif


\text{rep=simplify(((\N1)/(\D1))*((\N2)/(\D2)))}
\text{A=randitem(A,B,C,D,E,F)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp}{option=noreduction}
