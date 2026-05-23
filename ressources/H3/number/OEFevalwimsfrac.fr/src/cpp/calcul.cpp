target=calcul1 calcul2 calcul3 calcul4 calcul5

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=shuffle(2,3,4,5,6,7,8,9)}

#if defined TARGET_calcul1
 \title{Calcul 1}
 \text{ope=randitem(+,-)}
 \text{rep=simplify( ((\a[1])/(\a[2]))\ope((\a[3])/(\a[2]))*\a[4]/\a[5])}
 \text{enonce=\frac{\a[1]}{\a[2]}\ope\frac{\a[3]}{\a[2]}\times \frac{\a[4]}{\a[5]}}
#endif

#if defined TARGET_calcul2
 \title{Calcul 2}
 \text{ope=randitem(+,-)}
 \text{rep=simplify(( ((\a[1])/(\a[6]))\ope((\a[3])/(\a[2])))/\a[4]*\a[5])}
 \text{enonce=(\frac{\a[1]}{\a[6]}\ope\frac{\a[3]}{\a[2]}) : \frac{\a[4]}{\a[5]}}
#endif

#if defined TARGET_calcul3
 \title{Calcul 3}
 \text{ope=randitem(+,-)}
 \text{rep=simplify( ((\a[1])^2/(\a[6]))\ope((\a[3])/(\a[2])) )}
 \text{enonce=\frac{\a[1]}{\a[6]}^2\ope\frac{\a[3]}{\a[2]}}
#endif

#if defined TARGET_calcul4
 \title{Calcul 4}
 \text{ope=randitem(+,-)}
 \text{rep=simplify((((\a[1])/(\a[2]))\ope((\a[3])/(\a[4])))*(\a[5]/\a[6]\ope\a[7]/\a[8]))}
 \text{enonce=(\frac{\a[1]}{\a[2]}\ope\frac{\a[3]}{\a[4]}) \times (\frac{\a[5]}{\a[6]}\ope\frac{\a[7]}{\a[8]})}
#endif

#if defined TARGET_calcul5
 \title{Calcul 5}
 \text{rep=simplify( ((\a[1])/(\a[6]))/((\a[3])/(\a[2]))/(\a[4]/\a[5]))}
 \text{enonce=\frac{\a[1]}{\a[6]} : \frac{\a[3]}{\a[2]} : \frac{\a[4]}{\a[5]}}
#endif


\text{A=randitem(A,B,C,D,E,F)}

\statement{
Calculer l'expression suivante :
<div class="wimscenter"> \(\A = \enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp}{option=noreduction}
