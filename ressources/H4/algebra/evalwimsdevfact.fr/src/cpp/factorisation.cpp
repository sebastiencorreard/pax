target=factorA1,factorA2,factorA3,factorA4,factorA5,factorB1,factorB2,factorB3,factorB4,factorB5

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Factoriser simple
\text{list=wims(values v for v=2 to 12)}
\text{list=shuffle(\list)}
\integer{a=item(1,\list)}
\integer{b=item(2,\list)}
\integer{g=gcd(\a,\b)}
\if{\g!=1}{
 \integer{a=3}
 \integer{b=7}
}
\integer{c=item(3,\list)}
\integer{d=item(4,\list)}
\integer{g=gcd(\c,\d)}
\if{\g!=1}{
 \integer{c=4}
 \integer{d=9}
}
\integer{e=item(5,\list)}
\integer{f=item(6,\list)}
\integer{g=gcd(\e,\f)}
\if{\g!=1}{
 \integer{e=11}
 \integer{f=3}
}
\text{x=randitem(x,y,z,t,u,v)}
\text{A=randitem(A,B,C,D,V)}
\text{sg=randitem(-,+)}
\text{sg1=shuffle(-,+)}
\text{sg2=item(1,\sg1)}
\text{sg1=item(2,\sg1)}

#if defined TARGET_factorA1
 \title{TITRE 1}
 \text{enonce=randrow(\a*\b+\a*\x,\a*(\b+\x);\a*\x+\a*\b,\a*(\x+\b))}
 \text{rep=item(2 to -1,\enonce)}
 \text{enonce=item(1,\enonce)}
#endif

#if defined TARGET_factorA2
 \title{TITRE 2}
 \integer{ab=\a*\b}
 \text{enonce=randitem(\ab\sg\a*\x,\a*\x\sg\ab)}
 \text{rep=maxima(factor(\enonce);)}
#endif

#if defined TARGET_factorA3
 \title{TITRE 3}
 \text{enonce=randrow(\a*\x^2\sg\b*\x,\x*(\a*\x\sg\b);\a*\x\sg\b*\x^2,\x*(\a\sg\b*\x),-\x*(-\a-(\sg 1)*\b*\x))}
 \text{rep=item(2 to -1,\enonce)}
 \text{enonce=item(1,\enonce)}
#endif

#if defined TARGET_factorA4
 \title{TITRE 4}
 \integer{ac=\a*\c}
 \integer{bc=\b*\c}
 \text{enonce=randitem(\ac*\x\sg\bc,\ac\sg\bc*\x)}
 \text{rep=maxima(factor(\enonce);)}
#endif

#if defined TARGET_factorA5
 \title{TITRE 5}
 \integer{ac=\a*\c}
 \integer{bc=\b*\c}
 \text{enonce=randrow(\ac*\x^2\sg\bc*\x,\c*\x*(\a*\x\sg\b);\ac*\x\sg\bc*\x^2,\c*\x*(\a\sg\b*\x),-\c*\x*(-\a-(\sg 1)*\b*\x))}
 \text{rep=item(2 to -1,\enonce)}
 \text{enonce=item(1,\enonce)}
#endif

#if defined TARGET_factorB1
 \title{Factoriser 1}
 \text{enonce=randitem((\a*\x+\b)*(\c*\x+\d)+\e*(\a*\x+\b), \e*(\a*\x+\b)+(\a*\x+\b)*(\c*\x+\d), (\c*\x+\d)*(\a*\x+\b)+\e*(\a*\x+\b), \e*(\a*\x+\b)+(\c*\x+\d)*(\a*\x+\b))}
 \text{rep=maxima(factor(\enonce);)}
#endif

#if defined TARGET_factorB2
 \title{Factoriser 2}
 \text{enonce=randitem((\a*\x+\b)*(\c*\x+\d)\sg\e*(\a*\x+\b), \e*(\a*\x+\b)\sg(\c*\x+\d)*(\a*\x+\b))}
 \text{rep=maxima(factor(\enonce);)}
#endif

#if defined TARGET_factorB3
 \title{Factoriser 3}
 \text{enonce=randitem(\e*(\a*\x\sg1\b)\sg(\a*\x\sg1\b)*(\c*\x\sg2\d), \e*(\a*\x\sg1\b)\sg(\c*\x\sg2\d)*(\a*\x\sg1\b))}
 \text{rep=maxima(factor(\enonce);)}
#endif

#if defined TARGET_factorB4
 \title{Factoriser 4}
 \text{enonce=randitem((\a*\x+\b)*(\c*\x\sg\d)+\a*\x+\b, \a*\x+\b+(\a*\x+\b)*(\c*\x\sg\d), (\c*\x\sg\d)*(\a*\x+\b)+\a*\x+\b, \a*\x+\b+(\c*\x\sg\d)*(\a*\x+\b))}
 \text{rep=maxima(factor(\enonce);)}
#endif

#if defined TARGET_factorB5
 \title{Factoriser 5}
 \text{enonce=randitem((\a*\x+\b)*(\c*\x\sg1\d)\sg(\e*\x\sg2\f)*(\a*\x+\b), (\e*\x\sg2\f)*(\a*\x+\b)\sg(\a*\x+\b)*(\c*\x\sg1\d), (\c*\x\sg1\d)*(\a*\x+\b)\sg(\e*\x\sg2\f)*(\a*\x+\b), (\e*\x\sg2\f)*(\a*\x+\b)\sg(\c*\x\sg1\d)*(\a*\x+\b))}
 \text{rep=maxima(factor(\enonce);)}
#endif

\text{affichage=texmath(\enonce)}


\statement{
  Factoriser au maximum l'expression suivante :
<div class="wimscenter"> \(\A = \affichage)</div>
<p>
<b>Votre réponse :</b>
</p>
<div class="wimscenter">
\(\A =) \embed{r1,20}.
</div>
<div class="wims_instruction">Attention, dans la mesure du possible, le coefficient dominant de chaque facteur doit être positif.</div>}

\reply{réponse}{\rep}{type=algexp}
