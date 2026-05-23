target=addmult1 addmult2 addmult3 addmult4 addmult5

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{enonce=}
\text{sg=randitem(+,-)}
#if defined TARGET_addmult1
 \title{Addition/soustraction 1}
 \text{v=wims(values v for v=15 to 49)}
 \text{v=shuffle(\v)}
 \text{calc=\v[1]/\v[2] \sg \v[3]/\v[2]}
#endif

#if defined TARGET_addmult3
 \title{Addition/soustraction 3}
 \text{v=wims(values v for v=15 to 49)}
 \text{v=shuffle(\v)}
 \text{calc=-\v[1]/\v[2] \sg \v[3]/\v[2]}
#endif

#if defined TARGET_addmult2
 \title{Addition/soustraction 2}
 \text{v=wims(values v for v=15 to 49)}
 \text{v=shuffle(\v)}
 \text{calc=\v[1]/\v[2] - (-\v[3])/\v[2]}
 \text{enonce=\frac{\v[1]}{\v[2]} - \frac{-\v[3]}{\v[2]}}
#endif

#if defined TARGET_addmult4
 \title{Addition/soustraction 4}
 \text{v=wims(values v for v=15 to 49)}
 \text{v=shuffle(\v)}
 \text{a=randint(2,3,5,9)}
 \integer{A=\a*\v[2]}
 \text{calc=randitem(\v[1]/\v[2] \sg \v[3]/\A,\v[1]/\A \sg \v[3]/\v[2])}
#endif

#if defined TARGET_addmult5
 \title{Addition/soustraction 5}
 \text{v=wims(values v for v=15 to 49)}
 \text{v=shuffle(\v)}
 \text{a=randint(2,3,5,9)}
 \text{calc=randitem(\v[1]/\v[2] \sg \a,\a \sg \v[3]/\v[2])}
#endif

\text{enonce=\enonce=?texmath(\calc)}
\text{rep=simplify(\calc)}
\text{A=randitem(A,B,C,D,E,F)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp}{option=noreduction}
