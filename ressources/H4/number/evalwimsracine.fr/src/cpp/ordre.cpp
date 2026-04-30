target= ordre1,ordre2,ordre3



\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=50x30x1}

\integer{a=randint(2..10)}
\integer{b=\a+1}
\integer{a2=\a^2}
\integer{b2=\b^2}

#if #TARGET(ordre1)
 \title{Ordre 1}
 \integer{x=randint(\a2+1..\b2-1)}
 \text{x2=\(\sqrt{\x})}
 \text{gch=\a2}
 \text{drt=\b2}
 \text{rep1=\a}
 \text{rep2=\b}
#endif

#if #TARGET(ordre2)
 \title{Ordre 2}
 \text{x=randitem(x,a,b,y)}
 \text{x2=\(\sqrt{\x})}
 \text{gch=\a2}
 \text{drt=\b2}
 \text{rep1=\a}
 \text{rep2=\b}
#endif

#if #TARGET(ordre3)
 \title{Ordre 3}
 \text{x2=randitem(x,a,b,y)}
 \text{x=\(\sqrt{\x2})}
 \text{gch=\a}
 \text{drt=\b}
 \text{rep1=\a2}
 \text{rep2=\b2}
#endif

\text{liste=\a,\b,\x2,\x,\(\sqrt{\a}),\(\sqrt{\b})}

\statement{Compléter la phrase suivante en utilisant les étiquettes proposées.
<div class="center">
 \(\gch < ) \x \( < \drt) &nbsp; donc &nbsp; \embed{r1,\size} \( < ) \x2 \( < ) \embed{r2,\size}.
</div>} 

\reply{Réponse 1}{\rep1;\liste}{type=clickfill}
\reply{Réponse 2}{\rep2;\liste}{type=clickfill}
