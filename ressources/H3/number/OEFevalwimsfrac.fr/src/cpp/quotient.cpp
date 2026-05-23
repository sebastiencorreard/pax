target=quotient1 quotient2 quotient3 quotient4 quotient5

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

#if defined TARGET_quotient1
 \title{Division 1}
 \integer{N1=\v[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]}
 \integer{D2=\D1}
 \text{enonce=\frac{\N1}{\D1} : \frac{\N2}{\D2}}
#endif

#if defined TARGET_quotient2
 \title{Division 2}
 \integer{N1=\v[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]}
 \integer{D2=\b}
 \text{enonce=\frac{\N1}{\D1} : \frac{\N2}{\D2}}
#endif

#if defined TARGET_quotient3
 \title{Division 3}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]*\sg[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]*\sg[2]}
 \integer{D2=\b}
 \text{enonce=\frac{\N1}{\D1} : \frac{\N2}{\D2}}
#endif

#if defined TARGET_quotient4
 \title{Division 4}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]*\sg[1]}
 \integer{D1=1}
 \integer{N2=\v[2]*\sg[2]}
 \integer{D2=\b}
 \text{enonce=\N1 : \frac{\N2}{\D2}}
#endif

#if defined TARGET_quotient5
 \title{Division 5}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]*\sg[1]}
 \integer{D1=\b}
 \integer{N2=\v[2]*\sg[2]}
 \integer{D2=1}
 \text{aff2=\N2<0?(\N2):\N2}
 \text{enonce=\frac{\N1}{\D1} : \aff2}
#endif

\text{rep=simplify(((\N1)/(\D1))/((\N2)/(\D2)))}
\text{A=randitem(A,B,C,D,E,F)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp}{options=noreduction}
