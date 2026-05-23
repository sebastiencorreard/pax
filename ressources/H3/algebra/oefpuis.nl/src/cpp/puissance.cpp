target=quotientdiv,produitdiv,inversediv,quprindiv

#if #TARGET(quotientdiv)
 \title{Quotient van machten}
 \text{type=quotient}
#endif

#if #TARGET(quprindiv)
 \title{Bewerkingen en machten}
 \text{type=quotient,inverse,produit}
#endif

#if #TARGET(produitdiv)
 \title{Product van machten}
 \text{type=produit}
#endif

#if #TARGET(inversediv)
 \title{Inverse van machten}
 \text{type=inverse}
#endif

\language{nl}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\translator{Reinie Erne}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{confparm1=\confparm1=?1}
\integer{confparm1>5?5}

\text{listbase=wims(values v,-v for v=2 to 9)}
\text{listbase=shuffle(\listbase)}

\text{lteno=}
\text{ltsol=}
\text{ltbase=}
\text{st=}
\for{i=1 to \confparm1}{
 \text{choix=randitem(\type)}
 \integer{base=item(\i,\listbase)}
 \text{don=slib(calcpuis \choix,8,\base)}
 \text{enonce=item(1,\don)}
 \text{rep=item(2,\don)}
 \text{lteno=wims(append item \enonce to \lteno)}
 \text{ltsol=wims(append item \rep to \ltsol)}
 \text{base=\base<0?(\base)}
 \text{ltbase=wims(append item \base to \ltbase)}
 \text{st=wims(append item r\i to \st)} 
}

\steps{\st}

\statement{<br>
\if{\confparm1=1}
{Bereken de volgende uitdrukking: <br>
<center>\(\lteno = \ltbase)<sup><sup>\embed{r1,3}</sup></sup>.</center>}
{Bereken de volgende uitdrukkingen: 
<center><table><tr><td width=300><ul>
 \for{k=1 to \confparm1}{
  <li>\(\lteno[\k] = \ltbase[\k])<sup><sup>\embed{r\k,3}</sup></sup>.</li>
  }
</ul></td></tr></table></center>}
}


\answer{\(\lteno[1])}{\ltsol[1]}{type=numexp}
\answer{\(\lteno[2])}{\ltsol[2]}{type=numexp}
\answer{\(\lteno[3])}{\ltsol[3]}{type=numexp}
\answer{\(\lteno[4])}{\ltsol[4]}{type=numexp}
\answer{\(\lteno[5])}{\ltsol[5]}{type=numexp}
