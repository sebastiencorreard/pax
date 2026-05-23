target = raplong2-mod,raplong1-mod,rapara-mod,raplong3-mod,raplong4-mod

backward compatibility: cannot change file name with dash

\language{it}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{1000}
\text{size=35x25x1}
\integer{size2=50}

#if #TARGET(raplong1-mod)
 \title{Rapporti di Talete +} 
 \integer{nbrap=3}
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \integer{recnt=wims(recordcnt data/raptriangle-mod.don)}
  \integer{recnt=random(1..\recnt)}
  \matrix{don=wims(record \recnt of data/raptriangle-mod.don)}
 }{
  \integer{recnt=wims(recordcnt data/rappapillon-mod.don)}
  \integer{recnt=random(1..\recnt)}
  \matrix{don=wims(record \recnt of data/rappapillon-mod.don)}
 }
#endif

#if #TARGET(raplong2-mod)
 \title{Rapporti di Talete e triangoli +} 
 \integer{recnt=wims(recordcnt data/raptriangle-mod.don)}
 \integer{recnt=random(1..\recnt)}
 \matrix{don=wims(record \recnt of data/raptriangle-mod.don)}
 \integer{nbrap=3}
#endif

#if #TARGET(raplong3-mod)
 \title{Rapporti di Talete 3 e triangoli +} 
 \matrix{don=wims(record 1 of data/raptriangle-mod.don)}
 \integer{nbrap=3}
#endif

#if #TARGET(raplong4-mod)
 \title{Rapporti di Talete 4 e triangoli +} 
 \integer{nbrap=3}
 \matrix{don=wims(record 1 of data/rappapillon-mod.don)}
#endif

#if #TARGET(rapara-mod)
\title{Rette parallele +} 
\integer{ch=1}
\integer{type=2}
\integer{nbrap=2}
#endif


\text{S=A,B,C,D,E,F,G,H,I,J,K,L,M,N}
\text{S=shuffle(\S)}

#if #TARGET(rapara-mod)
 \integer{recnt=wims(recordcnt data/parallele-mod.don)}
 \integer{recnt=random(1..\recnt)}
 \matrix{don=wims(record \recnt of data/parallele-mod.don)}
#else

#endif

\integer{nbsom=row(1,\don)}
\for{i=1 to \nbsom}{
 \matrix{don=wims(replace X\i by \S[\i] in \don)}
}

\text{hypo=row(2,\don)}
\text{tri=row(3,\don)}
\text{rapports=row(4,\don)}

#if #TARGET(rapara-mod)
 \text{droites=item(3,\rapports)}
 \text{droites=wims(replace internal / by , in \droites)}
#else
 \text{rapports=shuffle(\rapports)}
#endif

\text{ltmp=wims(replace internal / by , in \rapports)}
\text{num=item(1,\ltmp)}
\text{liste=row(5,\don)}
\text{liste=\liste,\ltmp}
\text{tmp=row(6,\don)}
\text{xrange=item(1,\tmp)}
\text{yrange=item(2,\tmp)}
\matrix{dessin=row(7 to -1,\don)}
\text{dessin=wims(rows2lines \dessin)}

\text{rapports1=\rapports}
\text{rapports2=\ltmp[2]/\ltmp[1],\ltmp[4]/\ltmp[3],\ltmp[6]/\ltmp[5]}
\text{affrapports1=wims(replace internal , by = in \rapports1)}
\text{affrapports1=texmath(\affrapports1)}
\text{affrapports2=wims(replace internal , by = in \rapports2)}
\text{affrapports2=texmath(\affrapports2)}

#if #TARGET(rapara-mod)
\integer{choixtheo=random(1..2)}
\statement{
<table>
 <tr>
  <td>Scrivere due rapporti per mostrare che le rette \(\droites[1]) e \(\droites[2]) \if{choixtheo=1}{sono parallele utilizzando l'inverso del teorema di Talete.}{non sono parallele utilizzando il teorema di Talete.}
  <br />
<b>Risposta:</b>
<table class="wimscenter">
<tr>
<td>\embed{reply 1,\size}</td>
<td rowspan="3"> e </td>
<td> \embed{reply 3,\size}</td>
</tr><tr>
<td><hr/></td>
<td><hr/></td>
</tr><tr>
<td> \embed{reply 2,\size}</td>
<td> \embed{reply 4,\size}</td>
</tr></table>
<div class="wims_instruction">Trascinare col mouse le etichette in basso per completare l'uguaglianza.</div>
  </td>
  <td>
   <div class="wimscenter">\draw{\xrange,\yrange}{\dessin}</div>
  </td>
 </tr>
</table>

}
\reply{numérateur1}{\num1;\liste}{type=clickfill}
\reply{dénominateur1}{\den1;\liste}{type=clickfill}
\reply{numérateur2}{\num2;\liste}{type=clickfill}
\reply{dénominateur1}{\den2;\liste}{type=clickfill}

\text{tmplin=\num1/\den1,\num2/\den2}

#else
\statement{
<table>
 <tr>
  <td>\hypo<br />
  Quale eguaglianza di rapporti si può dedurre utilizzando il teorema di Talete 
  <b>sui triangoli \(\tri[1]) e \(\tri[2])</b>?<br />

<b>Risposta:</b>
<table border=0 class="wimscenter">
<tr>
<td>\embed{reply 1,\size}</td>
<td rowspan="3"> =</td>
<td> \embed{reply 3,\size}</td>
<td rowspan="3"> =  </td>
<td> \embed{reply 5,\size}</td>
</tr><tr>
<td><hr/></td>
<td><hr/></td>
<td><hr/></td>
</tr><tr>
<td> \embed{reply 2,\size}</td>
<td> \embed{reply 4,\size}</td>
<td> \embed{reply 6,\size}</td>
</tr></table>
<div class="wims_instruction">Trascinare col mouse le etichette in basso per completare le uguaglianze.</div>
  </td>
  <td>
   <div class="wimscenter">\draw{\xrange,\yrange}{\dessin}</div>
  </td>
 </tr>
</table>

}
\reply{numérateur1}{\num1;\liste}{type=clickfill}
\reply{dénominateur1}{\den1;\liste}{type=clickfill}
\reply{numérateur2}{\num2;\liste}{type=clickfill}
\reply{dénominateur1}{\den2;\liste}{type=clickfill}
\reply{numérateur3}{\num3;\liste}{type=clickfill}
\reply{dénominateur3}{\den3;\liste}{type=clickfill}

\text{tmplin=\num1/\den1,\num2/\den2,\num3/\den3}
#endif

\text{tmplin=wims(listuniq \tmplin)}
\text{set1=wims(listintersect \rapports1 and \tmplin)}
\text{set2=wims(listintersect \rapports2 and \tmplin)}
\integer{lin1=items(\tmplin)}
\integer{lin2=items(\set1)}
\integer{lin3=items(\set2)}
\condition{Rapporti corretti}{\lin1=\nbrap and (\lin2=\nbrap or \lin3=\nbrap)}

\solution{I rapporti corretti sono: \(\affrapports1) oppure  \(\affrapports2)}
