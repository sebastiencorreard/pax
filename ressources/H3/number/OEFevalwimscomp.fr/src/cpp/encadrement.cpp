target=encadrement1 encadrement2 encadrement3 encadrement4 encadrement5
\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_encadrement1
 \title{Encadrement 1}
 \real{N=randint(11..99)+randint(111..999)/1000}
 \text{eN=\N}
 \text{enonce=Donner un encadrement par deux entiers consécutifs du nombre \N.}
 \integer{rep1=floor(\N)}
 \integer{rep2=\rep1+1}
#endif

#if defined TARGET_encadrement2
 \title{Encadrement 2}
 \text{N=randint(11..99)+randint(1..9)/randint(11..19)}
 \text{N=simplify(\N)}
 \text{eN=texmath(\N)}
 \text{enonce=Donner un encadrement par deux entiers consécutifs du nombre \(\eN).}
 \integer{rep1=floor(\N)}
 \integer{rep2=\rep1+1}
#endif

#if defined TARGET_encadrement3
 \title{Encadrement 3}
 \real{N=randint(11..99)+randint(111..999)/1000}
 \real{N=-\N}
 \text{eN=\N}
 \text{enonce=Donner un encadrement par deux entiers consécutifs du nombre \N.}
 \integer{rep1=floor(\N)}
 \integer{rep2=\rep1+1}
#endif

#if defined TARGET_encadrement4
 \title{Encadrement 4}
 \integer{a=randint(11111..99999)}
 \integer{b=randint(1111..9999)}
 \text{N=simplify(\a/\b)}
 \text{N=/ notin \N?12485/4482}
 \text{eN=texmath(\N)}
 \integer{ch=randint(1..2)}
 \text{arr=item(\ch,un dixième,un centième)}
 \real{amplitude=10^(-\ch)}
 \text{enonce=Donner un encadrement d'amplitude \arr de \(\eN).}
#endif

#if defined TARGET_encadrement5
 \title{Encadrement 5}
 \integer{a=randint(11111..99999)}
 \integer{b=randint(1111..9999)}
 \text{N=simplify(-\a/\b)}
 \text{N=/ notin \N?-12485/4482}
 \text{eN=texmath(\N)}
 \integer{ch=randint(1..2)}
 \text{arr=item(\ch,un dixième,un centième)}
 \real{amplitude=10^(-\ch)}
 \text{enonce=Donner un encadrement d'amplitude \arr de \(\eN).}
#endif

\statement{
\enonce
<div class="wimscenter">\embed{r1,5} \(< \eN < ) \embed{r2,5}</div>}

\answer{Borne inférieure}{\rep1}{type=numexp}
\answer{Borne supérieure}{\rep2}{type=numexp}

#if defined TARGET_encadrement4  || defined TARGET_encadrement5

\condition{Condition sur la borne inférieure}{\rep1<=\N}
\condition{Condition sur la borne supérieure}{\rep2>=\N}
\condition{Amplitude d'\arr}{\rep2-\rep1=\amplitude or \rep1-\rep2=\amplitude}
#endif
