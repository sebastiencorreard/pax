target= longsin longcos longtan

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

\integer{l1=random(25..100)}
\real{l1=\l1/10}
\integer{vangle=random(30..60)}
\text{anglerad=\vangle*pi/180}

\integer{ch=random(1..2)}
#include "triangle.inc"

\text{angle=\widehat{\X2\X1\X3}}
\text{neq=\(\cos(\angle)),\(\sin(\angle)),\(\tan(\angle)),\(\X1\X2),\(\X1\X3),\(\X2\X3)}
\text{angle=\(\angle)}

#if #TARGET (longsin)
\title{Bepaal een lengte 1}
\if{\ch=1}{
\text{cote=\(\X2\X3)}
\text{inc=\X1\X3}
}{
\text{cote=\(\X1\X3)}
\text{inc=\X2\X3}
}
\text{fonct=sin}
\text{nom=de sinus}
\text{eq1=item(2,\neq)}
\text{eq2=item(6,\neq)}
\text{eq3=item(5,\neq)}
\text{val1=\(\sin(\vangle))}
#endif

#if #TARGET (longcos)
\title{Bepaal een lengte 2}
\if{\ch=1}{
\text{cote=\(\X1\X2)}
\text{inc=\X1\X3}
}{
\text{cote=\(\X1\X3)}
\text{inc=\X1\X2}
}
\text{fonct=cos}
\text{eq1=item(1,\neq)}
\text{eq2=item(4,\neq)}
\text{eq3=item(5,\neq)}
\text{val1=\(\cos(\vangle))}
\text{nom=de cosinus}
#endif

#if #TARGET (longtan)
\title{Bepaal een lengte 3}
\if{\ch=1}{
\text{cote=\(\X2\X3)}
\text{inc=\X1\X2}
}{
\text{cote=\(\X1\X2)}
\text{inc=\X2\X3}
}
\text{fonct=tan}
\text{eq1=item(3,\neq)}
\text{eq2=item(6,\neq)}
\text{eq3=item(4,\neq)}
\text{val1=\(\tan(\vangle))}
\text{nom=de tangens}
#endif

\if{\ch=1}{
\real{res=\l1/\fonct(\anglerad)}
\text{sol3=\l1/\fonct(\vangle)}
\text{asol3=\frac{\l1}{\fonct(\vangle)}}
}{
\real{res=\fonct(\anglerad)*\l1}
\text{sol3=\l1*\fonct(\vangle)}
\text{asol3=\l1\times \fonct(\vangle)}
}

\integer{prec=random(1..3)}
\text{precision=tiende,honderdste,duizendste}
\text{precision=item(\prec,\precision)}
\integer{tmp=\res*10^\prec}
\real{sol=\tmp/10^\prec}

\if{\ch=1}{
\text{val2=\l1}
\text{val3=\(\inc)}
}{
\text{val3=\l1}
\text{val2=\(\inc)}}
\text{val=\eq1,\eq2,\eq3,\val1,\l1}

\text{enonce=Driehoek \(\X1\X2\X3) heeft een rechte hoek in \(\X2). Hoek \angle is \vangle graden en zijde \cote is \l1 cm. Wat is de lengte van zijde\(\inc) op de \precision centimeter precies}

\if{\confparm2=1}{
\matrix{test=r1,r2,r3
r4,r5,r6
r7
r8}
}{
\matrix{test=r8}
}
\steps{\test}

\statement{\if{\confparm1=1}{
<table>
<tr>
   <td>\enonce ?</td>
   <td>\draw{\xrange,\yrange}{\dessin}<center>(de tekening is niet op schaal getekend)<center></td>
</tr>
</table>
}{
\enonce ?<p>}
\if{\confparm2=1}{
Beantwoord eerst de volgende vragen:<p>
<u>Question 1 :</u> Vindt in driehoek \(\X1\X2\X3) een relatie tussen hoek \angl en de lengtes van zijden \(\inc) en \cote.
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
  <td align=center>\eq2</td> 
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td align=center>\eq3</td>
  </tr>
 </table></center>
<u>Vraag 2 :</u> Vul in de relatie van vraag 1 de waarden in die bekend zijn. 
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
  <td rowspan=3 align=center>\val1</td>
  <td rowspan=3> \big1=\big2 </td>
  <td align=center>\val2</td> 
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td align=center>\val3</td>
  </tr>
 </table></center>
<u>Vraag 3 :</u> Schrijf de lengte van \(\inc) op zonder berekeningen.
\if{\step=3}{<p>
\(\inc =) \embed{reply 7}}
{<center>\(\inc=\asol3) </center>
<u>Vraag 4 :</u> Beantwoord de vraag van de oefening.
}}}
}}

\answer{Relatie}{\eq1|\neq}{type=clickfill}
\answer{Teller}{\eq2|\neq}{type=clickfill}
\answer{Noemer}{\eq3|\neq}{type=clickfill}
\answer{Relatie}{\val1|\val}{type=clickfill}
\answer{Teller}{\val2|\val}{type=clickfill}
\answer{Noemer}{\val3|\val}{type=clickfill}
\answer{\inc}{\sol3}{type=algexp}
\answer{Antwoord}{\sol cm}{type=units}

\if{\confparm2<>1}{\hint{Gebruik de \nom van hoek \angle.}}
