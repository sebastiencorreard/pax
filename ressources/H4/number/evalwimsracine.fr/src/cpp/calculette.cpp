target= calculette1,calculette2,calculette3,calculette4,calculette5


#if #TARGET(calculette1)
 \title{Calculette 1}
 \integer{a=randint(11..99)}
 \integer{t=sqrt(\a)}
 \integer{a=sqrt(\a)=\t?\a+1}
 \text{enonce=sqrt(\a)}
#endif

#if #TARGET(calculette2)
 \title{Calculette 2}
 \text{a=wims(values v for v=11 to 99)}
 \text{a=shuffle(\a)}
 \integer{t=sqrt(\a[1])+sqrt(\a[2])}
 \integer{b=sqrt(\a[1])+sqrt(\a[2])=\t?\a[1]+1:\a[1]}
 \text{enonce=sqrt(\b+\a[2])}
#endif

#if #TARGET(calculette3)
 \title{Calculette 3}
 \text{a=wims(values v for v=11 to 99)}
 \text{a=shuffle(\a)}
 \integer{t=sqrt(\a[1])*sqrt(\a[2])}
 \integer{b=sqrt(\a[1])*sqrt(\a[2])=\t?\a[1]+1:\a[1]}
 \text{enonce=sqrt(\b*\a[2])}
#endif

#if #TARGET(calculette4)
 \title{Calculette 4}
 \text{a=wims(values v for v=11 to 99)}
 \text{a=shuffle(\a)}
 \integer{t=sqrt(\a[1])/sqrt(\a[2])}
 \integer{b=sqrt(\a[1])/sqrt(\a[2])=\t?\a[1]+1:\a[1]}
 \text{enonce=sqrt(\b/\a[2])}
#endif

#if #TARGET(calculette5)
 \title{Calculette 5}
 \text{a=wims(values v for v=11 to 99)}
 \text{a=shuffle(\a)}
 \integer{t=sqrt(\a[1]+\a[2])/sqrt(\a[3])}
 \integer{b=sqrt(\a[1]+\a[2])/sqrt(\a[3])=\t?\a[1]+1:\a[1]}
 \text{enonce=sqrt(\b+\a[2])/sqrt(\a[3])}
#endif

\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{prec=random(1..3)}
\integer{rep=(\enonce)*10^(\prec)}
\real{rep=\rep/10^(\prec)}
\text{enonce=texmath(\enonce)}

\text{listprec=dixième,centième,millième}
\text{precision1=item(\prec,\listprec)}
\text{precision1= au \precision1}
\real{precision2=10^(-\prec)}
\text{precision2=à \(\precision2) près}
\text{precision=random(\precision1,\precision2)}

\statement{Quel est l'arrondi \precision de \(\enonce) ? }

\reply{Réponse}{\rep}{type=litexp}
