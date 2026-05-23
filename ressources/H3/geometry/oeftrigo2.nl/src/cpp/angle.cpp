target= anglesin anglecos angletan

\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fguerima@tele2.fr}
\translator{Reinie Erne}
\computeanswer{no}
\format{html}
\precision{100000}

\text{size=90x35x1}
\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}


#include "triangle.inc"

\integer{l1=random(25..100)}
\real{l1=\l1/10}
\integer{l2=random(25..100)}
\integer{l2=\l2=\l1?112}
\real{l2=\l2/10}

\text{angle=\widehat{\X2\X1\X3}}
\text{neq=\(\cos(\angle)),\(\sin(\angle)),\(\tan(\angle)),\(\X1\X2),\(\X1\X3),\(\X2\X3)}
\text{angle=\(\angle)}

#if #TARGET (anglesin) || #TARGET (anglecos) 
\if{\l1>\l2}{\real{tmp=\l1}\real{l1=\l2}\real{l2=\tmp}}
#endif

#if #TARGET (anglesin)
\title{Bepaal een hoek 1}
\text{fonct=sin}
\text{nom=de sinus}
\text{rfonct=arcsin}
\text{num=\(\X2\X3)}
\text{den=\(\X1\X3)}
\text{eq1=item(2,\neq)}
#endif

#if #TARGET (anglecos)
\title{Bepaak een hoek 2}
\text{fonct=cos}
\text{fonct=de cosinus}
\text{rfonct=arccos}
\text{num=\(\X1\X2)}
\text{den=\(\X1\X3)}
\text{eq1=item(1,\neq)}
#endif

#if #TARGET (angletan)
\title{Bepaal een hoek 3}
\text{fonct=tan}
\text{nom=de tangens}
\text{rfonct=arctan}
\text{num=\(\X2\X3)}
\text{den=\(\X1\X2)}
\text{eq1=item(3,\neq)}
#endif

\text{res=\rfonct(\l1/\l2)*180/pi}

\text{val=\eq1,\den,\num,\l2,\l1}

\integer{prec=random(1..3)}
\text{precision=graad,tiende graad,honderdste graad}
\text{precision=item(\prec,\precision)}
\integer{tmp=\res*10^(\prec-1)}
\real{sol=\tmp/10^(\prec-1)}

\text{enonce=Driehoek \(\X1\X2\X3) heeft een rechte hoek in \(\X2). Zijde \num is \l1 cm en zijde \den is \l2 cm. Hoe groot is hoek \angle op de \precision precies}

\if{\confparm2=1}{
\matrix{test=r1,r2,r3
r4,r5,r6
r7}
}{
\matrix{test=r7}
}
\steps{\test}

\statement{\if{\confparm1=1}{
<table>
<tr>
   <td>\enonce ?</td>
   <td>\draw{\xrange,\yrange}{\dessin}<center>(de figuur is niet op schaal getekend)<center></td>
</tr>
</table>
}{
\enonce ?<p>}
\if{\confparm2=1}{
Beantwoord eerst de volgende vragen: <p>
<u>Vraag 1 :</u> Vindt in driehoek \(\X1\X2\X3) een relatie tussen hoek \angle, en de lengtes van de zijden \den en \num.
\if{\step=1}{
<center><table border=0 cellpadding=3>
  <tr>
  <td rowspan=3 align=center>\embed{reply1,\size}</td>
  <td rowspan=3> \big1=\big2 </td>
  <td align=center>\embed{reply2,\size}</td> 
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td align=center>\embed{reply3,\size}</td>
  </tr>
 </table></center>}
{<center><table border=0 cellpadding=3>
  <tr>
  <td rowspan=3 align=center>\eq1</td>
  <td rowspan=3> \big1=\big2 </td>
  <td align=center>\num</td> 
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td align=center>\den</td>
  </tr>
 </table></center>
<u>Vraag 2 :</u> 
  <tr> Vul in de relatie van vraag 1 de waarden in die bekend zijn. 
\if{\step=2}{
<center><table border=0 cellpadding=3>
  <tr>
  <td rowspan=3 align=center>\embed{reply 4,\size}</td>
  <td rowspan=3> \big1=\big2 </td>
  <td align=center>\embed{reply 5,\size}</td> 
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td align=center>\embed{reply 6,\size}</td>
  </tr>
 </table></center>}
{<center><table border=0 cellpadding=3>
  <tr>
  <td rowspan=3 align=center>\eq1</td>
  <td rowspan=3> \big1=\big2 </td>
  <td align=center>\l1</td> 
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td align=center>\l2</td>
  </tr>
 </table></center>
<u>Vraag 3 :</u> Beantwoord de vraag van de oefening. 
}}
}}

\answer{Relatie}{\eq1|\neq}{type=clickfill}
\answer{Teller}{\num|\neq}{type=clickfill}
\answer{Noemer}{\den|\neq}{type=clickfill}
\answer{Relatie}{\eq1|\val}{type=clickfill}
\answer{Teller}{\l1|\val}{type=clickfill}
\answer{Noemer}{\l2|\val}{type=clickfill}
\answer{Antwoord}{\sol}{type=auto}

\if{\confparm2<>1}{\hint{Gebruik \nom van hoek \angle.}}
