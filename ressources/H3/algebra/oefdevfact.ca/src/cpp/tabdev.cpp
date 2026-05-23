target= tabdeve1 tabdeve2

#if #TARGET(tabdeve1)
 \title{Développer avec tableau k(a+b)}
 \integer{typedev=1}
#endif

#if #TARGET(tabdeve2)
 \title{Développer avec tableau (a+b)(c+d)}
 \integer{typedev=2}
#endif

\language{fr}
\range{-5..5}
\author{Guerimand Fabrice}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{10000}

\integer{confparm2=\confparm2=?2}
\integer{confparm1=\confparm1=?1}

\integer{size=8}
\text{size2=40x25x1}
\text{lt=wims(values v,-v for v=2 to 15)}
\text{lt=shuffle(\lt)}
\integer{a=item(1,\lt)}
\integer{b=item(2,\lt)}
\integer{c=item(3,\lt)}
\integer{d=item(4,\lt)}
\text{x=random(x,y,z,a,b)}
\text{fab=\lt}

\text{lt=wims(values v for v=0 to \confparm1)}
\text{lt=shuffle(\lt)}
\text{p1=item(1,\lt)}
\text{p2=item(2,\lt)}
\text{lt=shuffle(\lt)}
\text{p3=item(1,\lt)}
\text{p4=item(2,\lt)}

\text{m1=simplify(\a*\x^\p1)}
\text{m2=simplify(\b*\x^\p2)}
\text{m3=simplify(\c*\x^\p3)}
\text{m4=simplify(\d*\x^\p4)}
\text{A1=texmath(\m1)}
\text{A2=texmath(\m2)}
\text{A3=texmath(\m3)}
\text{A4=texmath(\m4)}
\text{A=\A1,\A2,\A3,\A4}

\text{rep=\typedev=1?\m3*(\m1+\m2):(\m1+\m2)*(\m3+\m4)}
\text{rep=wims(rawmath \rep)}
\text{rep13=slib(commutesom \rep,\x)}
\text{enonce=texmath(\rep)}

\text{tmp=\A[1]*(\A[3]),\A[1]*(\A[4]),\A[2]*(\A[3]),\A[2]*(\A[4]),\A[1]*(\A[3])+(\A[1]*(\A[4]))+(\A[2]*(\A[3]))+(\A[2]*(\A[4]))}
\text{tmp=wims(replace internal \x by *\x in \tmp)}
\text{repco=}
\text{affco=}
\for{i=1 to 4}{
\text{tmp7=simplify(\tmp[\i])}
\text{tmp8=texmath(\tmp7)}
\text{repco=wims(append item \tmp7 to \repco)}
\text{affco=wims(append item \tmp8 to \affco)}}


\if{\typedev=2}{
 \matrix{tmp=r1,r2,r3,r4
r5}
}{
 \matrix{tmp=r1,r2
r5}
}

\steps{\tmp}

\statement{<br><ol>
\if{\step=1}{<li>Compléter le tableau suivant :  
<center><table border=1>
 <tr height=40>
  <td valign=center align=center width=70>\(\times)</td>
  <td valign=center align=center width=70>\(\A1)</td>
  <td valign=center align=center width=70>\(\A2)</td>
 </tr>
 <tr height=40>
  <td valign=center align=center width=70>\(\A3)</td>
  <td valign=center align=center width=70>\embed{r1,\size}</td>
  <td valign=center align=center width=70>\embed{r2,\size}</td>
 </tr>
\if{\typedev=2}{
 <tr height=40>
  <td valign=center align=center width=70>\(\A4)</td>
  <td valign=center align=center width=70>\embed{r3,\size}</td>
  <td valign=center align=center width=70>\embed{r4,\size}</td>
 </tr>}
</table><small>Chaque résultat doit être simplifier.</small></center></li>
}{<li>Complèter le tableau suivant :  
<center><table border=1>
 <tr height=40>
  <td valign=center align=center>\(\times)</td>
  <td valign=center align=center width=70>\(\A1)</td>
  <td valign=center align=center width=70>\(\A2)</td>
 </tr>
 <tr height=40>
  <td valign=center align=center width=70>\(\A3)</td>
  <td valign=center align=center width=70>\(\affco[1])</td>
  <td valign=center align=center width=70>\(\affco[3])</td>
 </tr>
\if{\typedev=2}{
 <tr height=40>
  <td valign=center align=center width=70>\(\A4)</td>
  <td valign=center align=center width=70>\(\affco[2])</td>
  <td valign=center align=center width=70>\(\affco[4])</td>
 </tr>}
</table></center></li>
<li>En vous aidant du tableau précédent, développer et r&eacute;duire l'expression suivante : <center>\(\enonce)</center></li>
}
</ol>}

\answer{Réponse 1}{\repco[1]}{type=litexp}{weight=1.5}
\answer{Réponse 2}{\repco[3]}{type=litexp}{weight=1.5}
\answer{Réponse 3}{\repco[2]}{type=litexp}{weight=1.5}
\answer{Réponse 4}{\repco[4]}{type=litexp}{weight=1.5}
\answer{\(\enonce)}{\rep13}{type=litexp}{weight=4}