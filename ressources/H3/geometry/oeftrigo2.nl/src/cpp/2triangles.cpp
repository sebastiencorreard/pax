target= long2tri

\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fguerima@tele2.fr}
\translator{Reinie Erne}
\computeanswer{no}
\format{html}
\precision{100000}

\text{size=70x30x1}
\integer{confparm1=\confparm1=?1}
\integer{confparm2=\confparm2=?1}

\integer{ch=random(1..2)}
#include "2triangles.inc"

#if #TARGET (long2tri)
\title{Drie driehoeken}
#endif

\integer{l1=random(25..150)}
\real{l1=\l1/10}
\integer{vangle1=random(20..50)}
\integer{tmp=70-\vangle1}
\integer{vangle2=random(20..\tmp)}
\text{anglerad1=\vangle1*pi/180}
\text{anglerad2=\vangle2*pi/180}

\text{langle=\(\widehat{\X2\X1\X3}),\(\widehat{\X4\X1\X3}),\(\widehat{\X2\X1\X4})}
\text{lfonct=\(\sin),\(\cos),\(\tan)}
\text{list=\(\X1\X2),\(\X2\X3),\(\X1\X3),\(\X4\X3),\(\X2\X4),\(\X1\X4)}
\text{ltriangle=\X1\X2\X3,\X1\X4\X3,\X1\X2\X4}
\matrix{donnees=1,5,3,3,5,1
1,2,1,3,2,1
1,3,1,2,1,3
1,6,3,2,1,6
5,1,3,3,5,1
5,6,3,1,5,6
2,1,1,3,2,1
2,3,1,1,2,3
3,1,1,2,1,3
3,2,1,1,2,3
6,1,3,2,1,6
6,5,3,1,5,6}
\text{donnees=randrow(\donnees)}
\text{incaff=item(item(1,\donnees),\list)}
\text{incte=wims(char 3 to -2 of  \incaff)}
\text{inc=\([\incte])}
\text{cote=item(item(2,\donnees),\list)}
\text{cote=wims(char 3 to -2 of \cote)}
\text{cote=\([\cote])}
\text{good1=item(item(3,\donnees),\ltriangle)}
\text{angle=item(item(3,\donnees),\langle)}
\text{fonct=item(item(4,\donnees),\lfonct)}
\text{num=item(item(5,\donnees),\list)}
\text{den=item(item(6,\donnees),\list)}
\text{lfonct2=sin,cos,tan}
\text{lfonct3=le sinus,le cosinus,la tangente}
\text{nom=item(item(4,\donnees),\lfonct3)}
\text{langle2=\anglerad1+\anglerad2,\anglerad2,\anglerad1}
\text{numte=wims(char 3 to -2 of  \num)}
\text{signe=\incte issametext \numte?*:/}
\text{tmp1=item(item(3,\donnees),\langle2)}
\text{tmp2=item(item(4,\donnees),\lfonct2)}
\text{formule=\l1\signe\tmp2(\tmp1)}

\integer{prec=random(1..3)}
\text{precision=tiende,honderdste,duizendste}
\text{precision=item(\prec,\precision)}
\integer{tmp1=\formule*10^\prec}
\real{sol=\tmp1/10^\prec}


\text{enonce=De driehoek \(\X1\X2\X3) heeft een rechte hoek in \(\X2). \(\X4) is een punt op de zijde \([\X2\X3]) van de driehoek, zodanig dat hoek \(\widehat{\X4\X1\X3})  \vangle2 graden is en hoek \(\widehat{\X2\X1\X4}) \vangle1 graden is. De zijde \cote van deze driehoek is \l1 cm. Wat is de lengte van zijde \inc op de \precision centimer precies}

\if{\confparm2=1}{
\matrix{test=c1,c2,r1,r2,r3,r4,r5}
}{
\matrix{test=r5}
}

\steps{\test}

\statement{\formule\if{\confparm1=1}{
<table>
<tr>
   <td>\enonce ?</td>
   <td>\draw{\xrange,\yrange}{\dessin}<center>(de figuur is niet op schaal getekend)<center></td>
</tr>
</table>
}{
\enonce ?<p>}
\if{\confparm2=1}{
Vul, om de oefening te maken, de volgende tekst in: <p>
In driehoek \embed{c1} met een rechte hoek in \embed{c2} hebben we: 
<center><table border=0 cellpadding=3>
  <tr>
  <td rowspan=3 align=center>\embed{reply1,\size}(\embed{reply2,\size})</td>
  <td rowspan=3> \big1=\big2 </td>
  <td align=center>\embed{reply3,\size}</td> 
  </tr>
  <tr><td><hr></td></tr>
  <tr>
  <td align=center>\embed{reply4,\size}</td>
  </tr>
 </table></center>
Er geldt dus: \incaff=\embed{reply5}.
}}

\choice{Driehoek}{\good1}{\X1\X2\X3,\X1\X4\X3,\X4\X2\X3}
\choice{Rechte hoek}{\X2}{\X1,\X2,\X3,\X4}
\answer{Functie}{\fonct|\lfonct}{type=clickfill}
\answer{Hoek}{\angle|\langle}{type=clickfill}
\answer{Teller}{\num|\list}{type=clickfill}
\answer{Noemer}{\den|\list}{type=clickfill}
\answer{Antwoord}{\sol cm}{type=units}

\if{\confparm2<>1}{\hint{Gebruik \nom van hoek \angle.}}
