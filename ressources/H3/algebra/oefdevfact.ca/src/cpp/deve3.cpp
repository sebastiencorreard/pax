target= deve3 deve4

#if #TARGET(deve3)
   \title{Développer (a+b)^2 #}
   \text{signe=+}
#endif

#if #TARGET(deve4)
   \title{Développer (a-b)^2 #}
   \text{signe=-}
#endif

\language{fr}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}


\integer{confparm1=\confparm1}
\integer{confparm2=\confparm2}
\integer{confparm2=\confparm2= or NaN isin \confparm2?2}
\integer{confparm1=NaN isin \confparm1 or \confparm1=?1}

\integer{size=8}
\text{size2=40x25x1}

\text{a=random(1,-1)*randint(2..15)}
\text{a=simplify(\a)}
\text{b=randint(2..15)}
\text{x=random(x,y,z,a,b)}

\text{lt=wims(values v for v=0 to \confparm1)}
\text{lt=shuffle(\lt)}
\integer{p1=item(1,\lt)}
\integer{p2=item(2,\lt)}
\text{m1=\a*\x^\p1}
\text{m1=simplify(\m1)}
\text{rep1=texmath(\m1)}
\text{m2=\b*\x^\p2}
\text{m2=simplify(\m2)}
\text{rep2=texmath(\m2)}

\text{rep=(\m1 \signe \m2)^2}
\text{rep8=slib(commutesom \rep,\x)}

\text{tmp1=texmath(\m1)}
\text{tmp2=texmath(\m2)}
\text{A=\tmp1,\tmp2}
\text{enonce=(\A[1] \signe \A[2])^2}

\text{coul=red,green,blue,purple}
\text{coul=shuffle(\coul)}
\text{t1={\special{color=\coul[1]}}}
\text{t0={\special{color=black}}}
\text{t2={\special{color=\coul[2]}}}
\text{po=\char40}
\text{pf=\char41}

\text{enonce1=(\t1 \A[1] \t0 \signe \t2 \A[2] \t0)^2}

\text{tmp=(\m1)^2,2*(\m1)*(\m2),(\m2)^2}

\text{rep=}
\text{repco=}
\for{i=1 to 3}{
 \text{tmp7=simplify(\tmp[\i])}
 \text{rep=wims(append item \tmp7 to \rep)}
 \text{tmp7=texmath(\tmp7)}
 \text{repco=wims(append item \tmp7 to \repco)}
}

\text{ligne1=<td>\(\enonce1)</td>
<td>=</td>
<td>\((\t1\A[1]\t0)^2) </td>
<td>\signe</td>
<td>\(2\times \t1\A[1]\t0\times\t2\A[2]\t0) </td>
<td>+</td>
<td>\((\t2\A[2]\t0)^2) </td>}

\text{tmp1=\repco[2]<0?(\repco[2]):\repco[2]}
\text{tmp2=\repco[3]<0?(\repco[3]):\repco[3]}
\text{ligne2=<td></td>
<td>=</td>
<td> \(\repco[1])</td> 
<td>\signe</td>
<td> \(\tmp1) </td>
<td>+</td>
<td> \(\tmp2) </td>}

\if{\confparm2=1}{
\matrix{type=r1,r2,r3,r4
r5,r6,r7
r8}
}{
\matrix{type=r8}
}

\steps{\type}
\text{repf=texmath(item(1,\rep8))}

\statement{<br>
Développer et r&eacute;duire l'expression \(\enonce).
<br>
<center><hr width=50%></center>
<table class=reply>
<tr><td>
<u><b>Votre réponse :</b></u><br>
\if{\confparm2=1}{
On vous propose de résoudre l'exercice en vous guidant. Complétez les différentes étapes de calcul qui vous sont proposées en vous aidant des couleurs et en utilisant l'identité \((a\signe b)^2=a^2\signe 2ab+b^2) : <p>
\if{\step=1}{<small>Utiliser les étiquettes pour compléter le calcul.</small> <p>
   \(\enonce1= \t1\po\t0) \embed{r1,\size2} \(\t1\pf\t0^2 \signe 2\times \t1\po\t0) \embed{r2,\size2} \(\t1\pf\t0 \times \t2\po\t0) \embed{r3,\size2} \(\t2\pf\t0 + \t2\po\t0 ) \embed{r4,\size2} \(\t2\pf\t0^2) 
}{
<table border=0>
<tr>\ligne1</tr>
<tr>
\if{\step=2}{
<td></td>
<td>=</td>
<td> \embed{r5,\size}</td> 
<td>\signe</td>
<td> \embed{r6,\size} </td>
<td>+</td>
<td> \embed{r7,\size} </td>
</tr>
}{
\ligne2
</tr>
<tr>
<td></td>
<td>=</td>
<td colspan=5> \embed{r8,4*\size} </td>
</tr>
}
</table>
}
}
{
\(\enonce = )\embed{r8,4*\size}.
}</td></tr>
</table>
}
\answer{Réponse 1}{\rep1;\rep1;\rep2}{type=clickfill}
\answer{Réponse 2}{\rep1;\rep1;\rep2}{type=clickfill}
\answer{Réponse 3}{\rep2;\rep1;\rep2}{type=clickfill}
\answer{Réponse 4}{\rep2;\rep1;\rep2}{type=clickfill}
\answer{Réponse 5}{\rep[1]}{type=litexp}
\answer{Réponse 6}{\rep[2]}{type=litexp}
\answer{Réponse 7}{\rep[3]}{type=litexp}
\answer{Réponse}{\rep8}{type=litexp}

\solution{
<table border=0>
<tr>\ligne1</tr>
<tr>\ligne2</tr>
<tr>
   <td></td>
   <td>=</td>
   <td colspan=5> \(\repf)</td>
</tr>
</table>}