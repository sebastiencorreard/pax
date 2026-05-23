target=liaison3 liaison4 liaison5
#include "lang_titles.inc"
#include "author.inc"
\precision{10000}
\text{size=50x50x50}

#if defined TARGET_liaison3
\integer{nombre=3}
#endif
#if defined TARGET_liaison4
\integer{nombre=4}
#endif

#if defined TARGET_liaison5
\integer{nombre=5}
#endif

\integer{N1=randitem(5,6,7,8,10,11,12,13,14,15,17,18,18,20)}
\text{R1=\(\sqrt{\N1})}

\text{list=wims(values v for v=2 to 13)}
\text{list=shuffle(\list)}
\integer{R3=\list[1]}
\integer{N3=\R3^2}
\integer{R4=\list[2]}
\text{N4=\(\R4^2)}

\integer{R2=random(1..9)}
\real{R2=\R2/10}
\real{N2=\R2^2}
\integer{R5=random(3..13)}
\integer{N5=\R5^2}
\text{R5=\(\frac{1}{\R5})}
\text{N5=\(\frac{1}{\N5})}

\integer{a=random(2,4,8,10,11)}
\integer{b=random(3,9,7,13)}
\integer{A=\a^2}
\integer{B=\b^2}
\text{R6=\(\frac{\a}{\b})}
\text{N6=\(\frac{\A}{\B})}

\integer{R7=random(1,-1)*random(2..9)}
\integer{N7=2*\R7}
\text{R7=\(10^{\R7})}
\text{N7=\(10^{\N7})}

\integer{a=random(2..9)}
\integer{R8=random(1,-1)*random(2..9)}
\integer{N8=2*\R8}
\text{R8=\(\a^{\R8})}
\text{N8=\(\a^{\N8})}

\matrix{don=\N1,\N2,\N3,\N4,\N5,\N6,\N7,\N8
\R1,\R2,\R3,\R4,\R5,\R6,\R7,\R8}
\text{choix=shuffle(8)}
\matrix{rep=column([\choix[1..\nombre]],\don)}

\statement{
Mettez en relation les nombres de la première colonne avec leur
racine carrée dans la deuxième.
<div class="wimscenter">
\embed{reply 1,\size}
</div>
}

\reply{La correspondance}{\rep}{type=correspond}
