target= somme1,somme2,somme3,somme4


\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=50x30x1}

\text{list=wims(values v for v=2 to 11)}
\text{list=shuffle(\list)}
\text{a=wims(sort numeric items \list[1..2])}
\text{a=\a[2],\a[1]}
\integer{b=\a[1]^2}
\integer{c=\a[2]^2}

#if #TARGET(somme1)
 \title{Somme 1}
 \text{enonce=\sqrt{\a[1]^2+\a[2]^2}}
 \text{sg=+}
#endif

#if #TARGET(somme2)
 \title{Somme 2}
 \text{enonce=\sqrt{\b+\c}}
 \text{sg=+}
#endif

#if #TARGET(somme3)
 \title{Somme 3}
 \text{enonce=\sqrt{\a[1]^2-\a[2]^2}}
 \text{sg=-}
#endif

#if #TARGET(somme4)
 \title{Somme 4}
 \text{enonce=\sqrt{\b-\c}}
 \text{sg=-}
#endif

\integer{somme2=\b\sg\c}
\integer{somme=\a[1]\sg\a[2]}
\integer{somme3=2*\somme}
\integer{test=sqrt(\somme2)}
\text{rep=\test=sqrt(\somme2)?\test:\(\sqrt{\somme2})}
\integer{somme4=\a[1]\sg \c}
\text{liste=\somme2,\(\sqrt{\somme3}),\somme,\(\sqrt{\somme}),\somme4}


\statement{
Sans utiliser la calculette, compléter l'égalité en utilisant l'une des étiquettes proposées.
<div class="center">
 \(\enonce =) \embed{r1,\size} </div>} 

\reply{Réponse 1}{\rep;\liste}{type=clickfill}
