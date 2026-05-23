target=arret
#include "lang_titles.inc"
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100}
#include "lang.inc"
\text{vitesse=shuffle(10,20,30,40,50,60,70,80,90,100,110,120,130,140)}
\text{distfreinage=1.8,3.6,6.9,10.3,16.1,23.2,31.4,41.0,52.0,64.6,78.1,93.0,108.5,123.0}

\integer{v1=item(1,\vitesse)}
\integer{v2=item(2,\vitesse)}
\integer{v3=item(3,\vitesse)}
\integer{react=randint(1,2,3)}
\integer{pourcent=randint(30,40,50)}
\real{dr1=ceil(\v1*100/36*\react)/10}
\real{dr2=ceil(\v2*100/36*\react)/10}
\real{dr3=ceil(\v3*100/36*\react)/10}
\text{distfr1=item(\v1/10,\distfreinage)}
\text{distfr2=item(\v2/10,\distfreinage)}
\text{distfr3=item(\v3/10,\distfreinage)}
\real{distarret1=\dr1+\distfr1}
\real{distarret2=\dr2+\distfr2}
\real{distarret3=\dr3+\distfr3}
\real{distfrm1=ceil(\distfr1*(100+\pourcent)/10)/10}
\real{distfrm2=ceil(\distfr2*(100+\pourcent)/10)/10}
\real{distfrm3=ceil(\distfr3*(100+\pourcent)/10)/10}
\real{distarretm1=\dr1+\distfrm1}
\real{distarretm2=\dr2+\distfrm2}
\real{distarretm3=\dr3+\distfrm3}
\statement{\name_enonce[1;]
\react \if{\react=1}{\name_seconde[1]}{\name_seconde[2]}. \name_enonce[2;] \pourcent %.
\name_enonce[3;]
\name_enonce[4;]

<table class="wimscenter wimsborder">
<tr><th>\name_header[1]</th><td>\v1</td><td>\v2</td><td>\v3</td></tr>
<tr><th>\name_header[2] \react s</th>
<td>\embed{reply 1,6}</td><td>\embed{reply 2,6}</td><td>\embed{reply 3,6}</td></tr>
<tr><th>\name_header[3]
</th><td>\distfr1</td><td>\distfr2</td><td>\distfr3</td></tr>
<tr><th>\name_header[4]
</th><td>\embed{reply 4,6}</td><td>\embed{reply 5,6}</td><td>\embed{reply 6,6}</td></tr>
<tr><th>\name_header[5]</th><td>\embed{reply 7,6}</td>
<td>\embed{reply 8,6}</td><td>\embed{reply 9,6}</td></tr>
<tr><th>\name_header[6]</th><td>\embed{reply 10,6}</td>
<td>\embed{reply 11,6}</td><td>\embed{reply 12,6}</td></tr>
</table>}

\help{
<p>\name_help1</p>
<p>\name_help2</p>
<p>\name_help3</p>
<p>\name_help4</p>}
\answer{}{\dr1}{numeric}
\answer{}{\dr2}{numeric}
\answer{}{\dr3}{numeric}
\answer{}{\distarret1}{numeric}
\answer{}{\distarret2}{numeric}
\answer{}{\distarret3}{numeric}
\answer{}{\distfrm1}{numeric}
\answer{}{\distfrm2}{numeric}
\answer{}{\distfrm3}{numeric}
\answer{}{\distarretm1}{numeric}
\answer{}{\distarretm2}{numeric}
\answer{}{\distarretm3}{numeric}
