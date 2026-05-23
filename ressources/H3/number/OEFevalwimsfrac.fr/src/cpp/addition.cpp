target=addition1 addition2 addition3 addition4 addition5 soustraction1 soustraction2 soustraction3 soustraction4 soustraction5

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

#if defined TARGET_addition1
 \title{Addition 1}
 \text{ope=+}
 \integer{N1=\v[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]}
 \integer{D2=\b}
#endif

#if defined TARGET_addition2
 \title{Addition 2}
 \text{ope=+}
 \integer{c=randitem(7,9)}
 \integer{N1=\v[1]}
 \integer{D1=\a*\c}
 \integer{N2=\v[2]}
 \integer{D2=\b*\c}
#endif

#if defined TARGET_addition3
 \title{Addition 3}
 \text{ope=+}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]*\sg[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]*\sg[2]}
 \integer{D2=\b}
#endif

#if defined TARGET_addition4
 \title{Addition 4}
 \text{ope=+}
 \text{sg=shuffle(1,-1)}
 \integer{c=randitem(2,3,5)}
 \real{N1=\v[1]*\sg[1]}
 \integer{D1=\a*\c}
 \real{N2=\v[2]*\sg[2]}
 \integer{D2=\b*\c}
#endif

#if defined TARGET_addition5
 \title{Addition 5}
 \text{ope=+}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]}
 \integer{D1=\a*\sg[1]}
 \integer{N2=\v[2]}
 \integer{D2=\b*\sg[2]}
#endif

#if defined TARGET_soustraction1
 \title{Soustraction 1}
 \text{ope=-}
 \integer{N1=\v[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]}
 \integer{D2=\b}
#endif


#if defined TARGET_soustraction2
 \title{Soustraction 2}
 \text{ope=-}
 \integer{c=randitem(7,9)}
 \integer{N1=\v[1]}
 \integer{D1=\a*\c}
 \integer{N2=\v[2]}
 \integer{D2=\b*\c}
#endif

#if defined TARGET_soustraction3
 \title{Soustraction 3}
 \text{ope=-}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]*\sg[1]}
 \integer{D1=\a}
 \integer{N2=\v[2]*\sg[2]}
 \integer{D2=\b}
#endif

#if defined TARGET_soustraction4
 \title{Soustraction 4}
 \text{ope=-}
 \text{sg=shuffle(1,-1)}
 \integer{c=randitem(2,3,5)}
 \real{N1=-\v[1]}
 \integer{D1=\a*\c}
 \real{N2=-\v[2]}
 \integer{D2=\b*\c}
#endif

#if defined TARGET_soustraction5
 \title{Soustraction 5}
 \text{ope=-}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\v[1]}
 \integer{D1=\a*\sg[1]}
 \integer{N2=\v[2]}
 \integer{D2=\b*\sg[2]}
#endif

\text{enonce=\frac{\N1}{\D1} \ope \frac{\N2}{\D2}}
\text{rep=simplify(((\N1)/(\D1))\ope((\N2)/(\D2)))}
\text{A=randitem(A,B,C,D,E,F)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp}{option=noreduction}
