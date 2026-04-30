target= simplifier1,simplifier2,simplifier3,simplifier4,simplifier5,simplifier6


\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=4}

\integer{base=randitem(2,3,5,6,7,10,11,13)}
\text{a=wims(values v for v=2 to 20)}
\text{a=shuffle(\a)}

#if #TARGET(simplifier1)
 \title{Simplifier 1}
 \integer{affichage=1}
 \integer{b=\base*\a[2]^2}
 \text{rep=\a[2]}
 \text{enonce=\sqrt{\b}}
#endif

#if #TARGET(simplifier2)
 \title{Simplifier 2}
 \integer{affichage=1}
 \integer{b=\base*\a[2]^2*\a[3]^2}
 \integer{rep=\a[2]*\a[3]}
 \text{enonce=\sqrt{\b}}
#endif

#if #TARGET(simplifier3)
 \title{Simplifier 3}
 \integer{affichage=1}
 \integer{b=\base*\a[2]^2}
 \integer{rep=\a[2]*\a[3]}
 \text{enonce=\a[3]\times\sqrt{\b}}
#endif

#if #TARGET(simplifier4)
 \title{Simplifier 4}
 \integer{affichage=0}
 \integer{b=\base*\a[2]^2}
 \text{rep=\a[2]*sqrt(\base),sqrt(\base)*\a[2]}
 \text{enonce=\sqrt{\b}}
#endif

#if #TARGET(simplifier5)
 \title{Simplifier 5}
 \integer{affichage=0}
 \integer{b=\base*\a[2]^2*\a[3]^2}
 \integer{rep=\a[2]*\a[3]}
 \text{rep=\rep*sqrt(\base),sqrt(\base)*\rep}
 \text{enonce=\sqrt{\b}}
#endif

#if #TARGET(simplifier6)
 \title{Simplifier 6}
 \integer{affichage=0}
 \integer{b=\base*\a[2]^2}
 \integer{rep=\a[2]*\a[3]}
 \text{rep=\rep*sqrt(\base),sqrt(\base)*\rep}
 \text{enonce=\a[3]\times\sqrt{\b}}
#endif

\statement{
Ecrire \(\enonce) sous la forme \(a\sqrt{b}) où \(b) est un entier positif le plus petit possible.
<div class="center">
\if{\affichage=1}{
\(\enonce =) \embed{r1,\size} \(\times \sqrt{\base}).
</div>
}{
\(\enonce =) \embed{r1,3*\size}
</div>
<small>(Taper sqrt(2) pour \(\sqrt{2}).)</small>}
}

\reply{Réponse 1}{\rep}{type=litexp}
