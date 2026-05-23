target=noentier1 noentier2 noentier3 noentier4 noentier5

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
\text{v=wims(values \a*v,\b*v,10*v for v=1 to 10)}
\text{v2=wims(values v for v=6 to 30)}
\text{v=wims(listcomplement \v in \v2)}
\text{v=shuffle(\v)}
\integer{N1=\v[1]}
\integer{D1=\a}
\integer{N2=\v[2]}
\integer{D2=\b}

#if defined TARGET_noentier1
 \title{Fractions et décimaux 1}
 \text{ope=+}
 \text{div=10,10}
 \text{rep=simplify(((\N1)/(\div[1]*\D1))\ope((\N2)/(\div[2]*\D2)))}
 \real{N1=\N1/\div[1]}
 \real{N2=\N2/\div[2]}
 \text{enonce=\frac{\N1}{\D1} \ope \frac{\N2}{\D2}}
#endif

#if defined TARGET_noentier2
 \title{Fractions et décimaux 2}
 \text{ope=+}
 \text{div=10,10}
 \text{rep=simplify(((\N1)/(\D1))\ope((\N2)/(\D2)))}
 \real{D1=\D1/\div[1]}
 \real{N1=\N1/\div[2]}
 \text{enonce=\frac{\N1}{\D1} \ope \frac{\N2}{\D2}}
#endif

#if defined TARGET_noentier3
 \title{Fractions et décimaux 3}
 \text{ope=-}
 \text{div=10,100}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\sg[1]*\N1}
 \integer{N2=\sg[2]*\N2}
 \text{rep=simplify(((\N1)/(\D1))\ope ((\div[2]*\N2)/(\div[1]*\D2)))}
 \real{D2=\D2/\div[2]}
 \real{N2=\N2/\div[1]}
 \text{enonce=\frac{\N1}{\D1} \ope \frac{\N2}{\D2}}
#endif

#if defined TARGET_noentier4
 \title{Fractions et décimaux 4}
 \text{ope=*}
 \text{div=10,10}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\sg[1]*\N1}
 \integer{N2=\sg[2]*\N2}
 \text{rep=simplify(((\N1)/(\D1))\ope((\N2)/(\D2)))}
 \integer{ch=randitem(1,2)}
 \if{\ch=1}{
  \real{D2=\D2/\div[1]}
  \real{N1=\N1/\div[2]}
 }{
  \real{D1=\D1/\div[1]}
  \real{N2=\N2/\div[2]}
 }
 \text{enonce=\frac{\N1}{\D1} \times \frac{\N2}{\D2}}
#endif

#if defined TARGET_noentier5
 \title{Fractions et décimaux 5}
 \text{ope=/}
 \text{div=10,10}
 \text{sg=shuffle(1,-1)}
 \integer{N1=\sg[1]*\N1}
 \integer{N2=\sg[2]*\N2}
 \text{rep=simplify(((\N1)/(\D1))\ope((\N2)/(\D2)))}
 \integer{ch=randitem(1,2)}
 \if{\ch=1}{
  \real{D2=\D2/\div[1]}
  \real{D1=\D1/\div[2]}
 }{
  \real{N1=\N1/\div[1]}
  \real{N2=\N2/\div[2]}
 }
 \text{enonce=\frac{\N1}{\D1} : \frac{\N2}{\D2}}
#endif

\text{A=randitem(A,B,C,D,E,F)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp2}
