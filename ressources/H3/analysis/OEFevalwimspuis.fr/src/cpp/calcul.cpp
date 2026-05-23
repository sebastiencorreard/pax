target=calcul1 calcul2 calcul3 calcul4 calcul5
#define TITRE Calcul et priorités
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=wims(values v for v=3 to 5)}
\text{a=shuffle(\a)}

#if defined TARGET_calcul1
 \title{TITRE 1}
 \integer{p=randitem(2,3,4)}
 \text{calc=\a[1]+\a[2]^\p}
#endif

#if defined TARGET_calcul2
 \title{TITRE 2}
 \integer{p1=randitem(2,3,4)}
 \integer{p2=\p1+randitem(1,-1)}
 \text{calc=\a[1]*10^\p1+\a[2]*10^\p2}
#endif

#if defined TARGET_calcul3
 \title{TITRE 3}
 \integer{p=randitem(2,3,4)}
 \text{b=randrow(2,5
0.5,2
0.2,5
0.25,4)}
 \text{b=shuffle(\b)}
 \text{calc=\b[1]^\p*\b[2]^\p*\a[3]}
#endif

#if defined TARGET_calcul4
 \title{TITRE 4}
 \integer{p=randitem(2,3,4)}
 \text{calc=-\a[2]^\p+\a[1]}
#endif

#if defined TARGET_calcul5
 \title{TITRE 5}
 \integer{p=randitem(2,3,4)}
 \text{calc=\a[2]^\p+\a[1]^\p}
#endif

\text{enonce=texmath(\calc)}
\real{rep=simplify(\calc)}

\statement{
Effectuer le calcul suivant :
<div class="wimscenter"> \(\enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp}
