target=simplifier1 simplifier2 simplifier3 simplifier4 simplifier5

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\text{a=shuffle(2,3,5,7,11,13,17)}

#if defined TARGET_simplifier1
 \title{Simplifier une fraction 1}
 \integer{p=randitem(2,5)}
 \integer{s1=1}
 \integer{s2=1}
#endif

#if defined TARGET_simplifier2
 \title{Simplifier une fraction 2}
 \integer{p=randitem(3,9)}
 \integer{s1=-1}
 \integer{s2=1}
#endif

#if defined TARGET_simplifier3
 \title{Simplifier une fraction 3}
 \integer{p=-5}
 \integer{s1=1}
 \integer{s2=1}
#endif

#if defined TARGET_simplifier4
 \title{Simplifier une fraction 4}
 \integer{p=15}
 \integer{s1=-1}
 \integer{s2=1}
#endif

#if defined TARGET_simplifier5
 \title{Simplifier une fraction 5}
 \integer{p=45}
 \integer{s1=-1}
 \integer{s2=1}
#endif

\integer{n=\a[1]*\p*\s1}
\integer{d=\a[2]*\p*\s2}
\text{calc=\n/\d}
\text{enonce=texmath(\calc)}
\text{rep=simplify(\calc)}

\statement{
Utiliser les critères de divisibilité pour simplifier la fraction suivante :
<div class="wimscenter"> \(\enonce = ) \embed{r1,10}.</div>}

\answer{réponse}{\rep}{type=numexp}
