target=simpquo1,simpquo2,simpquo3,simpquo4,simpquo5


\language{fr}
\range{-5..5}
\author{Fabrice,Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}
\text{size=6}

\integer{base=randitem(2,3,5,7,10,11,13)}
\text{a=wims(values v for v=2 to 20)}
\text{a=shuffle(\a)}

#if #TARGET(simpquo1)
 \title{Simplifier un quotient 1}
 \text{rep=1}
 \text{enonce=\frac{\base}{\sqrt{\base}}}
#endif

#if #TARGET(simpquo2)
 \title{Simplifier un quotient 2}
 \integer{b=\base*\a[1]}
 \text{rep=\a[1]}
 \text{enonce=\frac{\b}{\sqrt{\base}}}
#endif

#if #TARGET(simpquo3)
 \title{Simplifier un quotient 3}
 \integer{b=\base*\a[1]}
 \integer{c=\a[2]^2*\base}
 \text{rep=simplify(\a[1]/\a[2])}
 \text{enonce=\frac{\b}{\sqrt{\c}}}
#endif

#if #TARGET(simpquo4)
 \title{Simplifier un quotient 4}
 \integer{c=\a[2]^2-\base}
 \text{rep=simplify(-\a[1]/(\c)),simplify(\a[1]*\a[2]/\c)}
 \text{enonce=\frac{\a[1]}{\a[2]+\sqrt{\base}}}
#endif

#if #TARGET(simpquo5)
 \title{Simplifier un quotient 5}
 \integer{c=\a[2]^2-\base}
 \text{rep=simplify((\a[2]-\a[1])/\c),simplify((\a[1]*\a[2]-\base)/\c)}
 \text{enonce=\frac{\a[1]+\sqrt{\base}}{\a[2]+\sqrt{\base}}}
#endif

\integer{nb=items(\rep)}
\text{st=item(1 to \nb,r1,r2)}
\steps{\st}

\statement{
Ecrire \(\enonce) sous la forme \if{\nb=2}{\(a+c\sqrt{\base})}{\(a\sqrt{\base})}.
<div class="center">
\(\enonce =) \if{\nb=2}{\embed{r2,\size} +} \embed{r1,\size} \(\times \sqrt{\base}).
</div>}

\reply{Réponse 1}{\rep[1]}{type=numexp}
\reply{Réponse 2}{\rep[2]}{type=numexp}
