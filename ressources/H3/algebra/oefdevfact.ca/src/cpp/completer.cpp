target=completer1,completer2

\language{fr}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\text{listnombres=wims(values v,-v for v=2 to 20)}
\text{listnombres=shuffle(\listnombres)}
\integer{a=item(1,\listnombres)}
\integer{b=item(2,\listnombres)}
\integer{c=item(3,\listnombres)}
\integer{d=item(4,\listnombres)}
\integer{e=item(5,\listnombres)}
\integer{g=maxima(gcd(\a,\b);)}
\if{\g!=1}{
 \integer{a=2}
 \integer{b=3}
}
\integer{g=maxima(gcd(\c,\d);)}
\if{\g!=1}{
 \integer{c=5}
 \integer{d=-3}
}
\text{sg=randitem(+,-)}
\text{x=shuffle(x,y,a,b,z)}

#if #TARGET (completer1)
 \title{Compléter une factorisation 1}
 \matrix{donnees=\a*\x[1]+\a*\x[2],\a,\x[1]+\x[2]
\a*\x[1]+\a*\x[2],\a,\x[1]+\x[2]
\a*\x[1]+\b*\x[1]^2,\x[1],\a+\b*\x[1]
\a*\x[1]^2+\b*\x[1],\x[1],\a*\x[1]+\b
\e*(\a*\x[1]+\b)\sg(\c*\x[1]+\d)*(\a*\x[1]+\b),(\a*\x[1]+\b),\e\sg(\c*\x[1]+\d)
(\c*\x[1]+\d)*(\a*\x[1]+\b)\sg\e*(\a*\x[1]+\b),(\a*\x[1]+\b),\c*\x[1]+\d\sg\e
\e*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)(\c*\x[1]+\d),(\a*\x[1]+\b),\e\sg(\c*\x[1]+\d)
(\a*\x[1]+\b)*(\c*\x[1]+\d)\sg\e*(\a*\x[1]+\b),(\a*\x[1]+\b),\c*\x[1]+\d\sg\e
(\a*\x[1]+\b)^2\sg\e*(\a*\x[1]+\b),(\a*\x[1]+\b),\a*\x[1]+\b\sg\e
\e*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)^2,(\a*\x[1]+\b),\e\sg(\a*\x[1]+\b)
(\a*\x[1]+\b)^2\sg(\c*\x[1]+\d)*(\a*\x[1]+\b),(\a*\x[1]+\b),(\a*\x[1]+\b)\sg(\c*\x[1]+\d)
(\c*\x[1]+\d)*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)^2,(\a*\x[1]+\b),(\c*\x[1]+\d)\sg(\a*\x[1]+\b)}
#endif

#if #TARGET (completer2)
 \title{Compléter une factorisation 2}
 \integer{ab=\a*\b}
 \integer{ac=\a*\c}
 \integer{bc=\b*\c}
 \matrix{donnees=\ab*\x[1]+\b,\b,\a+\x[1]
\b+\ab*\x[1],\b,\a+\x[1]
\ac*\x[1]+\bc,\c,\a*\x[1]+\b
\bc+\ac*\x[1],\c,\a*\x[1]+\b}
#endif

\text{don=randrow(\donnees)}
\text{enonce=item(1,\don)}
\text{facteur=item(2,\don)}
\text{rep=simplify(item(3,\don))}
\text{rep=maxima(expand(\rep);)}
\text{enonce=texmath(\enonce)}
\text{facteur=texmath(\facteur)}

\statement{<br>
Compléter la factorisation ci-dessous : 
<center>\(\enonce = \facteur \char40)\embed{r1,20} \(\char41)</center>
<small>Vous devez écrire un résultat simplifié et réduit.</small>}

\answer{Réponse}{\rep}{type=algexp}