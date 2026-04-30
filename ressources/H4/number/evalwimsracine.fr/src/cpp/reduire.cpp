target= reduire1,reduire2,reduire3,reduire4,reduire5,reduire6,reduire7


\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=12}

\integer{base=randitem(2,3,5,6,7,10,11,13)}
\text{a=wims(values v for v=2 to 14)}
\text{a=shuffle(\a)}
\text{sg=shuffle(+,+,+,-,-,-)}

#if #TARGET(reduire1)
 \title{Réduire 1}
 \integer{b=\base*\a[1]^2}
 \integer{rep=\sg[2]\a[1]\sg[1] 1}
 \text{enonce=\sg[2]\sqrt{\b},\sg[1]\sqrt{\base}}
#endif

#if #TARGET(reduire2)
 \title{Réduire 2}
 \integer{b=\base*\a[1]^2}
 \integer{rep=\sg[2]\a[2]*\a[1]\sg[1] 1}
 \text{enonce=\sg[2]\a[2]\sqrt{\b},\sg[1]\sqrt{\base}}
#endif

#if #TARGET(reduire3)
 \title{Réduire 3}
 \integer{b=\base*\a[1]^2}
 \integer{rep=\sg[2]\a[1]\sg[1] \a[3]}
 \text{enonce=\sg[2]\sqrt{\b},\sg[1]\a[3]\sqrt{\base}}
#endif

#if #TARGET(reduire4)
 \title{Réduire 4}
 \integer{b=\base*\a[1]^2}
 \integer{rep=\sg[2]\a[2]*\a[1]\sg[1] \a[3]}
 \text{enonce=\sg[2]\a[2]\sqrt{\b},\sg[1]\a[3]\sqrt{\base}}
#endif

#if #TARGET(reduire5)
 \title{Réduire 5}
 \integer{b=\base*\a[1]^2}
 \integer{c=\base*\a[4]^2}
 \integer{rep=\sg[2]\a[1]\sg[1] \a[4]}
 \text{enonce=\sg[2]\sqrt{\b},\sg[1]\sqrt{\c}}
#endif

#if #TARGET(reduire6)
 \title{Réduire 6}
 \integer{b=\base*\a[1]^2}
 \integer{c=\base*\a[4]^2}
 \integer{rep=\sg[2]\a[2]*\a[1]\sg[1] \a[3]*\a[4]}
 \text{enonce=\sg[2]\a[2]\sqrt{\b},\sg[1]\a[3]\sqrt{\c}}
#endif

#if #TARGET(reduire7)
 \title{Réduire 7}
 \integer{b=\base*\a[1]^2}
 \integer{c=\base*\a[4]^2}
 \integer{d=\base*\a[5]^2}
 \integer{rep=\sg[4]\a[2]*\a[1]\sg[1] \a[3]*\a[4] \sg[2] 1 \sg[3] \a[5]}
 \text{enonce=\sg[4]\a[2]\sqrt{\b},\sg[1]\a[3]\sqrt{\c},\sg[2] \sqrt{\base},\sg[3]\sqrt{\d}}
#endif

\text{enonce=shuffle(\enonce)}
\text{enonce=wims(items2words \enonce)}
\text{ch=wims(char 1 of \enonce)}
\if{+=\ch}{
 \text{enonce=wims(char 2 to -1 of \enonce)}
}
\text{rep=\rep*sqrt(\base),sqrt(\base)*\rep}

\statement{
Ecrire l'expression suivante sous la forme \(a\sqrt{b}) où \(b) est un entier positif le plus petit possible.
<div class="center">
\(\enonce =) \embed{r1,\size}
</div>
<small>(Taper sqrt(2) pour \(\sqrt{2}).)</small>
}

\reply{Réponse 1}{\rep}{type=litexp}
