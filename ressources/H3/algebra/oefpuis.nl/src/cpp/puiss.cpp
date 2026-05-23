target=puis1,puis2,puis3

#if #TARGET(puis1)
   \title{Machten 1}
   \text{type=puissance1}
#endif

#if #TARGET(puis2)
   \title{Machten 2}
   \text{type=puissance2}
#endif

#if #TARGET(puis3)
   \title{Machten 3}
   \text{type=puissance3}
#endif

\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\translator{Reinie Erne}
\computeanswer{no}
\format{html}
\precision{10000}

\text{enonce=slib(expnumeric \type)}
\text{rep=maxima(\enonce;)}
\integer{confparm1=\confparm1=?1}

#if #TARGET(puis3)
 \text{rep=wims(replace internal / by , in \enonce)}
 \text{den=item(2,\rep)}
 \text{den=texmath(\den)}
 \text{num=item(1,\rep)}
 \text{num=texmath(\num)}
 \text{num=wims(replace internal \left by \times\left in \num)}
 \text{rep=maxima(\enonce;)}
 \text{enonce=\frac{\num}{\den}}
#endif


\statement{<br>
Bereken de volgende uitdrukking: \(\enonce)
<br>
<center><hr width=50%></center>
<table class=reply>
<tr><td>
<u><b>Antwoord:</b></u>
<br>
\(\enonce) = \embed{r1,10} .
</td></tr></table>}


\answer{\(\enonce)}{\rep}{type=numexp}
