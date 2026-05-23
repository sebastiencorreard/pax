target=completer1 completer2 completer3
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

#if defined TARGET_completer3
\text{listnombres=wims(values v for v=2 to 20)}
#else
\text{listnombres=wims(values v,-v for v=2 to 20)}
#endif
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
#if defined TARGET_completer1
\matrix{donnees=\a*\x[1]+\a*\x[2],\a,\x[1]+\x[2],\x[2]+\x[1]
\a*\x[1]+\a,\a,\x[1]+1
\a*\x[1]+\b*\x[1]^2,\x[1],\a+\b*\x[1]
\a*\x[1]^2+\b*\x[1],\x[1],\a*\x[1]+\b
\e*(\a*\x[1]+\b)\sg(\c*\x[1]+\d)*(\a*\x[1]+\b),(\a*\x[1]+\b),\e\sg(\c*\x[1]+\d)
(\c*\x[1]+\d)*(\a*\x[1]+\b)\sg\e*(\a*\x[1]+\b),(\a*\x[1]+\b),\c*\x[1]+\d\sg\e
\e*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)*(\c*\x[1]+\d),(\a*\x[1]+\b),\e\sg(\c*\x[1]+\d)
\e*(\a*\x[1]+\b)\sg(\a*\x[1]+\b),(\a*\x[1]+\b),\e\sg 1
(\a*\x[1]+\b)*(\c*\x[1]+\d)\sg\e*(\a*\x[1]+\b),(\a*\x[1]+\b),\c*\x[1]+\d\sg\e
(\a*\x[1]+\b)^2\sg\e*(\a*\x[1]+\b),(\a*\x[1]+\b),\a*\x[1]+\b\sg\e
\e*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)^2,(\a*\x[1]+\b),\e\sg(\a*\x[1]+\b)
(\a*\x[1]+\b)^2\sg(\c*\x[1]+\d)*(\a*\x[1]+\b),(\a*\x[1]+\b),(\a*\x[1]+\b)\sg(\c*\x[1]+\d)
(\c*\x[1]+\d)*(\a*\x[1]+\b)\sg(\a*\x[1]+\b)^2,(\a*\x[1]+\b),(\c*\x[1]+\d)\sg(\a*\x[1]+\b)}
#endif
#if defined TARGET_completer2
 \integer{ab=\a*\b}
 \integer{ac=\a*\c}
 \integer{bc=\b*\c}
 \matrix{donnees=\ab*\x[1]+\b,\b,\a*\x[1]+1
\b+\ab*\x[1],\b,1+\a*\x[1]
\ac*\x[1]+\bc,\c,\a*\x[1]+\b
\bc+\ac*\x[1],\c,\a*\x[1]+\b}
#endif
#if defined TARGET_completer3
\integer{ab=\a*\b}
\integer{ac=\a*\c}
\integer{bc=\b*\c}
\matrix{donnees=\ab*\x[1]+\b,\b,\a*\x[1]+1
\b+\ab*\x[1],\b,1+\a*\x[1]
\ac*\x[1]+\bc,\c,\a*\x[1]+\b
\bc+\ac*\x[1],\c,\a*\x[1]+\b}
#endif
\integer{doncnt=rows(\donnees)}
\text{number=randint(1..\doncnt)}
\text{don=row(\number,\donnees)}
\text{enonce=item(1,\don)}
\text{facteur=item(2,\don)}
\text{rep=item(3,\don)}
\text{rep=maxima(expand(\rep);)}
\text{enonce=texmath(\enonce)}
\text{facteur=texmath(\facteur)}

\text{tmp=()}
\text{po=wims(char 1 of \tmp)}
\text{pf=wims(char 2 of \tmp)}
#if defined TARGET_completer1
\text{option=\number!=1?polexpand}
#else
\text{option=polexpand}
#endif
\statement{\name_enonce:
<div class="wimscenter"><label for="reply1">\(\enonce = \facteur \po\)</label>\embed{r1,20} \(\pf)</div>
<div class="wims_instruction">\name_instruction</div>}

\answer{\name_answer}{\rep}{type=litexp}{option=\option}
