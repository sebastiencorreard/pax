target=factor1 factor2 factor3 factor4 factor5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "confparm.inc"
\precision{10000}
\integer{a=random(2..15)}
\integer{b=random(2..15)}
\integer{c=random(2..15)}
\integer{g=maxima(gcd(\b,\c);)}
\integer{b=\b/\g}
\integer{c=\c/\g}
\if{\b=\c}{
  \integer{b=2}
  \integer{c=3}
}
\integer{d=random(2..15)}
\integer{e=random(2..15)}
\integer{f=random(2..15)}
\text{x=randitem(x,y,a,b)}

#if defined TARGET_factor1
\integer{B=random(1,-1)*\a*\c}
\integer{A=random(1,-1)*\a*\b}
\text{pui=\confparm1=1?1,\x:1,\x,\x^2,\x^3,\x^4}
\text{pui=shuffle(\pui)}
\text{v1=item(1,\pui)}
\text{v2=item(2,\pui)}
\matrix{donnees=\A*\v1+\B*\v2}
#endif
#if defined TARGET_factor2
\integer{g=maxima(gcd(\d,\a);)}
\integer{d=\d/\g}
\integer{a=\a/\g}
\text{sg1=randitem(,-)}
\text{sg2=randitem(+,-)}
\text{sg3=randitem(,-)}
\text{sg4=randitem(+,-)}
\text{sg6=randitem(,-)}
\text{sg5=randitem(+,-)}
\integer{g=maxima(gcd(\e,\f);)}
\integer{f=\f/\g}
\integer{e=\e/\g}
\text{sg7=randitem(+,-)}
\matrix{donnees=\sg1\d*\x*(\sg3\b*\x\sg2\c)\sg4\a*(\sg3\b*\x\sg2\c)
\sg1\e*\x*(\sg3\b*\x\sg2\c)\sg4(\sg6\a*\x\sg5\d)*(\sg3\b*\x\sg2\c)
(\sg1\e*\x+\sg7\f)*(\sg3\b*\x\sg2\c)\sg4(\sg6\a*\x\sg5\d)*(\sg3\b*\x\sg2\c)}
#endif
#if defined TARGET_factor3
\integer{g=maxima(gcd(\d,\a);)}
\integer{d=\d/\g}
\integer{a=\a/\g}
\text{pui=0,1}
\text{pui=shuffle(\pui)}
\integer{p1=item(1,\pui)}
\integer{p2=item(2,\pui)}
\text{sg1=randitem(,-)}
\text{sg2=randitem(+,-)}
\text{sg3=randitem(,-)}
\text{sg4=randitem(+,-)}
\text{tmp1=simplify((\d *\x^(\p1))^2)}
\text{tmp2=simplify((\a *\x^(\p2))^2)}
\matrix{donnees=\tmp1-\tmp2
(\sg1\b*\x\sg2\c)^2-(\sg3\d*\x\sg4\a)^2
(\sg1\b*\x\sg2\c)^2-\tmp1
\tmp1-(\sg1\b*\x\sg2\c)^2}
#endif
#if defined TARGET_factor4
\integer{d=random(2,4)}
\integer{a=random(5,3,7,9,11,13,15)}
\text{sg2=randitem(+,-)}
\matrix{donnees=simplify(\x^2\sg2 2*\a*\x+\a^2)
simplify((\d*\x)^2\sg2 2*\a*\d*\x+\a^2)}
#endif
#if defined TARGET_factor5
\text{pui=\confparm1=1?1,1,1,1:wims(values v for v=1 to \confparm1)}
\text{pui=shuffle(\pui)}
\integer{p1=item(1,\pui)}
\integer{p2=item(2,\pui)}
\text{v1=\p1=1?\x:\x^\p1}
\text{v2=\p2=1?\x:\x^\p2}
\text{sg1=randitem(,-)}
\text{sg2=randitem(+,-)}
\text{sg3=randitem(,-)}
\text{sg4=randitem(+,-)}
\text{sg5=randitem(+,-)}
\matrix{donnees=\sg1\d*\v2*(\sg3\b*\x\sg2\c)\sg4\a*\v1*(\sg3\b*\x\sg2\c)
\sg1\d*\x*(\sg3\b*\x\sg2\c)\sg4\a*(\sg3\b*\x\sg2\c)\sg5\e*\x*(\sg3\b*\x\sg2\c)
\sg1\d*\v1*(\sg3\b*\x\sg2\c)\sg4\a*(\sg3\b*\x\sg2\c)\sg5\e*\x*(\sg3\b*\x\sg2\c)
\sg1\d*\v1*(\sg3\b*\x\sg2\c)\sg4\a*\v2*(\sg3\b*\x\sg2\c)\sg5\e*\x*(\sg3\b*\x\sg2\c)}
#endif

\text{enonce=randrow(\donnees)}
\text{rep=maxima(factor(\enonce);)}
\text{enonce=texmath(\enonce)}

\statement{
\name_enonce \(\enonce).
<div class="wimscenter">
<label for="reply1"> \(\enonce = )</label>\embed{r1,20}.
</div>
}

\answer{\(\enonce)}{\rep}{type=litexp}{option=polfactor}
