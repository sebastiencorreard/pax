target=develA1,develA2,develA3,develA4,develA5,develB1,develB2,develB3,develB4,develB5,develC1,develC2,develC3,develC4,develC5,develD1,develD2,develD3,develD4,develD5

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITRE Développer
\text{list=wims(values v for v=2 to 12)}
\text{list=shuffle(\list)}
\integer{a=item(1,\list)}
\integer{b=item(2,\list)}
\integer{c=item(3,\list)}
\integer{d=item(4,\list)}
\text{x=randitem(x,y,z,t,u,v)}
\text{A=randitem(A,B,C,D,V)}

#if defined TARGET_develA1
 \title{TITRE k(a+b) 1}
 \text{enonce=\a*(\x+\b)}
#endif

#if defined TARGET_develA2
 \title{TITRE k(a+b) 2}
 \text{enonce=randitem(\a*(\x-\b),\a*(\b-\x))}
#endif

#if defined TARGET_develA3
 \title{TITRE k(a+b) 3}
 \text{enonce=randitem(\x*(\a*\x+\b),\x*(\b+\a*\x))}
#endif

#if defined TARGET_develA4
 \title{TITRE k(a+b) 4}
 \text{enonce=randitem(\x*(\a*\x-\b),\x*(\b-\a*\x))}
#endif

#if defined TARGET_develA5
 \title{TITRE k(a+b) 5}
 \text{enonce=randitem(\a*\x*(-\b*\x-\c),\a*\x*(-\c-\b*\x))}
#endif

#if defined TARGET_develB1
 \title{TITRE (a+b)(c+d) 1}
 \text{enonce=randitem((\x+\b),(\b+\x))*randitem((\x+\d),(\d+\x))}
#endif

#if defined TARGET_develB2
 \title{TITRE (a+b)(c+d) 2}
 \text{enonce=randitem((\a*\x+\b),(\b+\a*\x))*randitem((\c*\x+\d),(\d+\c*\x))}
#endif

#if defined TARGET_develB3
 \title{TITRE (a+b)(c+d) 3}
 \text{sg=shuffle(+,-)}
 \text{enonce=randitem((\a*\x\sg[1]\b),(\b\sg[1]\a*\x))*randitem((\c*\x\sg[2]\d),(\d\sg[2]\c*\x))}
#endif

#if defined TARGET_develB4
 \title{TITRE (a+b)(c+d) 4}
 \text{enonce=randitem((\a*\x-\b),(\b-\a*\x))*randitem((\c*\x-\d),(\d-\c*\x))}
#endif

#if defined TARGET_develB5
 \title{TITRE (a+b)(c+d) 5}
 \text{sg=shuffle(+,-)}
 \text{enonce=randitem((\sg[1]\b-\a*\x),(\sg[1]\a*\x-\b))*randitem((\sg[2]\c*\x-\d),(\sg[2]\d-\c*\x))}
#endif

#if defined TARGET_develC1
 \title{TITRE (a+b)^2 1}
 \text{enonce=randitem((\x+\b)^2,(\b+\x)^2)}
#endif

#if defined TARGET_develC2
 \title{TITRE (a+b)^2 2}
 \text{enonce=randitem((\x-\b)^2,(\b-\x)^2)}
#endif

#if defined TARGET_develC3
 \title{TITRE (a+b)^2 3}
 \text{enonce=randitem((\a*\x+\b)^2,(\b+\a*\x)^2)}
#endif

#if defined TARGET_develC4
 \title{TITRE (a+b)^2 4}
 \text{enonce=randitem((\a*\x-\b)^2,(\b-\a*\x)^2)}
#endif

#if defined TARGET_develC5
 \title{TITRE (a+b)^2 5}
 \text{enonce=randitem((-\a*\x-\b)^2,(-\b-\a*\x)^2)}
#endif

#if defined TARGET_develD1
 \title{TITRE (a+b)(a-b) 1}
 \text{enonce=randitem((\a+\x)*(\a-\x),(\x+\a)*(\x-\a))}
#endif

#if defined TARGET_develD2
 \title{TITRE (a+b)(a-b) 2}
 \text{enonce=randitem((\a+\b*\x)*(\a-\b*\x),(\b*\x+\a)*(\b*\x-\a))}
#endif

#if defined TARGET_develD3
 \title{TITRE (a+b)(a-b) 3}
 \text{enonce=randitem((-\a-\b*\x)*(\a-\b*\x),(\b*\x+\a)*(-\b*\x-\a))}
#endif

#if defined TARGET_develD4
 \title{TITRE (a+b)(a-b) 4}
 \text{enonce=randitem((\x+\a)*(\a-\x),(\a+\x)*(\x-\a))}
#endif

#if defined TARGET_develD5
 \title{TITRE (a+b)(a-b) 5}
 \text{enonce=randitem((\b*\x+\a)*(\a-\b*\x),(\a+\b*\x)*(\b*\x-\a))}
#endif

\text{affichage=texmath(\enonce)}
\text{rep=wims(rawmath \enonce)}
\text{rep=slib(commutesom \rep,\x)}

\statement{
  Développer et réduire l'expression suivante :
<div class="wimscenter"> \(\A = \affichage)</div>
<p><b>Votre réponse :</b></p>
<div class="wimscenter">\(\A =) \embed{r1,20}.</div>
}

\reply{réponse}{\rep}{type=litexp}
