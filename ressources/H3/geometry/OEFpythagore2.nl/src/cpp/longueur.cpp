target= longueur1 longueur2

\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{1000}

\integer{confparm1=\confparm1 notitemof 0,1?1}
\integer{confparm2=\confparm2=?1}

#include "triangle.inc"

\integer{u=random(2..6)}
\integer{v=random(1..\u-1)}
\integer{sm=max(\u^2-\v^2,2*\u*\v)}
\integer{mn=min(\u^2-\v^2,2*\u*\v)}
\integer{sn=(\mn^2+\sm^2)^(1/2)}
\real{k=randint(15..25)/10}
\real{l2=\sm*\k}
\real{l1=\sn*\k}
\real{l3=\mn*\k}

#if #TARGET(longueur1)
 \title{Bereken een lengte 1}
 \text{inc=\X1\X3}
 \text{values=\(\X1\X2 = \l2),\(\X2\X3 = \l3)}
 \integer{type=1}
 \real{rep5=\l1}
#endif

#if #TARGET(longueur2)
 \title{Bereken een lengte 2}
 \integer{type=2}
 \integer{ch=randint(1,2)}
 \if{\ch=1}{
  \text{inc=\X2\X3}
  \text{values=\(\X1\X2 = \l2),\(\X1\X3 = \l1)}
  \real{rep5=\l3}
 }{
  \text{inc=\X1\X2}
  \text{values=\(\X2\X3 = \l3),\(\X1\X3 = \l1)}
  \real{rep5=\l2}
 }
#endif

\real{rep4=\rep5^2}
\text{values=shuffle(\values)}
\text{longueur=wims(replace internal , by &nbsp;&nbsp; in \values)}
\text{enonce1=randitem(De driehoek \(\X1\X2\X3) is rechthoekig in \(\X2), \(\angle{\X1\X2\X3}) is recht)}
\text{enonce=\enonce1.<br> De lengtes van de volgende zijden zijn bekend : <center>\longueur</center> Bereken de lengte van de zijde \(\inc).}

\text{choix1=het omgekeerde van de stelling van Pythagoras,de stelling van Pythagoras}
\text{rep1=item(2,\choix1)}

\text{listchoix=\(\X1\X2),\(\X1\X3),\(\X2\X3),\(\X1\X2^2),\(\X1\X3^2),\(\X2\X3^2),+}
\text{solg=item(5,\listchoix)}
\text{sold=item(4,\listchoix),item(7,\listchoix),item(6,\listchoix)|item(6,\listchoix),item(7,\listchoix),item(4,\listchoix)}

\if{\confparm2=1}{
 \text{tmp=c1,r1,r2,r3,r4}
}{
 \text{tmp=r4}
}
\steps{\tmp}

\statement{\if{\confparm1=1}{
<table>
<tr>
   <td>\enonce</td>
   <td><p>\draw{\xrange,\yrange}{\dessin}<center>(de driehoek is niet op schaal getekend)<center></p></td>
</tr>
</table width=90%>
}{
\enonce}
<p><b>Jouw antwoord</b> :
\if{\confparm2=1}{
In driehoek \(\X1\X2\X3), rechthoekig in \(\X2), krijg je volgens \embed{c1}:
<center>\embed{r1,40x35x1} = \embed{r2,40x35x3}</center>
<br>
Dus : \(\inc^2 = )\embed{r3,7}<br>
Dus : \(\inc = )\embed{r4,7}<br>
}{
\(\inc = )\embed{r4,7}.
}
}


\choice{Stelling}{\rep1}{\choix1}{weight=2}
\answer{links}{\solg;\listchoix}{type=clickfill}{weight=1.5}
\answer{rechts}{\sold;\listchoix}{type=clickfill}{weight=1.5}
\answer{\(\inc^2 = )}{\rep4}{type=numexp}{weight=2}
\answer{\(\inc = )}{\rep5}{type=numexp}{weight=3}