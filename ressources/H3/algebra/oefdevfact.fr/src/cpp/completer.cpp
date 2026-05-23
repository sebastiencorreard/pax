target=completer
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}

#include "confparm.inc"
\text{size=7}
\text{x=randitem(x,y,z,a,b,c)}

\text{list=wims(values v for v=1 to 15)}
\text{list=shuffle(\list)}
\integer{a=item(1,\list)}
\integer{b=item(2,\list)}
\text{pui=\confparm1=1?1,\x:1,\x,\x^2,\x^3,\x^4}
\text{pui=shuffle(\pui)}
\text{v1=item(1,\pui)}
\text{v2=item(2,\pui)}
\text{listmon=\a*\v1,\b*\v2}
\text{listmon=shuffle(\listmon)}
\text{m1=simplify(item(1,\listmon))}
\text{m2=simplify(item(2,\listmon))}
\text{r1=simplify((\m1)^2)}
\text{r2=simplify(2*(\m1)*(\m2))}
\text{r3=simplify((\m2)^2)}
\text{M1=texmath(\m1)}
\text{M2=texmath(\m2)}
\text{R1=texmath(\r1)}
\text{R2=texmath(\r2)}
\text{R3=texmath(\r3)}
\text{sg=randitem(-,+)}

\matrix{donnees=r2,r3,r4
r2,r3,r5
r1,r4,r5
r1,r3,r5}
\integer{chtype=randint(1..4)}
\text{type=row(\chtype,\donnees)}
\steps{\type}

\statement{
\name_enonce:
<div class="wimscenter">
\if{\chtype=1}{&#40; \M1 \sg \embed{\type[1],\size/2} &#41;<sup>2</sup> = \embed{\type[2],\size} \sg \embed{\type[3],\size} + \(\R3)}
\if{\chtype=2}{&#40; \M1 \sg \embed{\type[1],\size/2} &#41;<sup>2</sup> = \embed{\type[2],\size} \sg \R2 + \embed{\type[3],\size}}
\if{\chtype=3}{&#40; \embed{\type[1],\size/2} \sg \M2 &#41;<sup>2</sup> = \(\R1) \sg \embed{\type[2],\size} + \embed{\type[3],\size}}
\if{\chtype=4}{&#40; \embed{\type[1],\size/2} \sg \M2 &#41;<sup>2</sup> = \embed{\type[2],\size} \sg \R2 + \embed{\type[3],\size}}
</div>
}

\answer{Réponse}{\m1}{type=litexp}{option=polexpand}
\answer{Réponse}{\m2}{type=litexp}{option=polexpand}
\answer{Réponse}{\r1}{type=litexp}{option=polexpand}
\answer{Réponse}{\r2}{type=litexp}{option=polexpand}
\answer{Réponse}{\r3}{type=litexp}{option=polexpand}
