target= egalite1 egalite2

\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100000}

\integer{confparm1=\confparm1 notitemof 0,1?1}

#if #TARGET(egalite1)
 \title{De stelling van Pythagoras 1}
 #include "triangle.inc"
 \integer{ch=1}
 \integer{type=1}
 \text{enonce2=<br>Geef de stelling van Pythagoras met behulp van deze driehoek en de blauwe vakjes hieronder.}
#endif

#if #TARGET(egalite2)
 \title{De stelling van Pythagoras 2}
 #include "2triangles.inc"
 \integer{type=2}
 \integer{ch=randitem(1,2)}
 \text{tri=\X1\X2\X3,\X1\X2\X4}
 \text{tri=item(\ch,\tri)}
 \text{enonce2=<br>Geef de stelling van Pythagoras met behulp van de driehoek \(\tri) en de blauwe vakjes hieronder.}
#endif

\text{enonce1=randitem(De driehoek \(\X1\X2\X3) is rechthoekig in \(\X2), \(\angle{\X1\X2\X3}) is recht)}

\text{listchoix=\(\X1\X2),\(\X1\X3),\(\X2\X3),\(\X1\X2^2),\(\X1\X3^2),\(\X2\X3^2),+}
\text{listchoix2=\(\X1\X4),\(\X1\X4^2),\(\X2\X4),\(\X2\X4^2)}

\if{\ch=1}{
\text{solg=item(5,\listchoix)}
\text{sold=item(4,\listchoix),item(7,\listchoix),item(6,\listchoix)|item(6,\listchoix),item(7,\listchoix),item(4,\listchoix)}
}{
\text{solg=item(2,\listchoix2)}
\text{sold=item(4,\listchoix),item(7,\listchoix),item(4,\listchoix2)|item(4,\listchoix2),item(7,\listchoix),item(4,\listchoix)}
}

\if{\type=2}{\text{listchoix=\listchoix,\listchoix2}}

\statement{\if{\confparm1=1}{
<table>
<tr>
   <td>\enonce1. \enonce2 ?</td>
   <td>\draw{\xrange,\yrange}{\dessin}<center>(de driehoek is niet op schaal getekend)<center></td>
</tr>
</table>
}{
\enonce1. \enonce2 ?<p>}
<br>
\embed{r1,40x35x1} = \embed{r2,40x35x3}
}

\answer{Membre de gauche}{\solg;\listchoix}{type=clickfill}
\answer{Membre de droite}{\sold;\listchoix}{type=clickfill}