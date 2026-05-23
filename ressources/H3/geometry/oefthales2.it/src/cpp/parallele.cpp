target= parat1 parat2 parap1 parap2

\language{it}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{1000}
\integer{size=50}

\integer{confparm2=1}
\integer{confparm3=\confparm3=?1}

#if defined TARGET_parat1
\title{Parallele (triangoli)}
\integer{ch=1}
#include "triangle.inc"
#endif

#if defined TARGET_parap1
\title{Parallele (nodo)}
\integer{ch=1}
#include "papillon.inc"
#endif

#if defined TARGET_parat2
\title{Parallele (triangoli) 2}
\integer{ch=2}
#include "triangle.inc"
#endif

#if defined TARGET_parap2
\title{Parallele (nodo) 2}
\integer{ch=2}
#include "papillon.inc"
#endif

\integer{type=randint(1..2)}

\if{\confparm3=1}{
\integer{l1=random(2..11)}
\integer{l2=random(2..11)}
\if{\type=1}{
\integer{coef=random(2,3,4)}
\integer{l3=\coef*\l1}
\integer{l4=\coef*\l2}
}{
\integer{l3=random(4..44)}
\integer{l4=random(4..44)}
\integer{l4=\l3/\l4=\l1/\l2?\l4+1}
}}{
\integer{l1=random(15..50)}
\integer{l2=random(15..50)}
\if{\type=1}{
\integer{coef=random(2..10)}
\integer{l3=\coef*\l1}
\integer{l4=\coef*\l2}
}{
\integer{l3=random(30..500)}
\integer{l4=random(30..500)}
\integer{l4=\l3/\l4=\l1/\l2?\l4+1}
}
\real{l1=\l1/10}
\real{l2=\l2/10}
\real{l3=\l3/10}
\real{l4=\l4/10}
}
\real{l5=\l1+\l2}
\real{l6=\l3+\l4}

\text{bad1=sono uguali e i due insiemi di punti \(\X1, \X4, \X2) e \(\X1, \X5, \X3) sono disposti nello stesso ordine,non sono uguali, sono uguali}
\if{\type=1}{
 \text{bad1=\bad1,non sono uguali e i due insiemi di punti \(\X1, \X4, \X2) e \(\X1, \X5, \X3) sono disposti nello stesso ordine}
}
\text{bad2=l'inverso del teorema di Talete,il teorema di Talete,il teorema di Pitagora,l'inverso del teorema di Pitagora}
\text{bad3=sono parallele,non sono parallele}
\text{good1=item(\type,\bad1)}
\text{good2=item(\type,\bad2)}
\text{good3=item(\type,\bad3)}

\text{rap1=\X1\X4/\X1\X2,\X1\X5/\X1\X3}
\text{rap2=\X1\X2/\X1\X4,\X1\X3/\X1\X5}

#if defined TARGET_parap2  | defined TARGET_parap1
\text{rep=\X1\X5,\X1\X3,\X1\X4,\X1\X2,\X4\X2,\X5\X3}
\text{valrep=\l3,\l4,\l1,\l2,\l5,\l6}
\text{donnees=<li>\(\X1\X4 = \l1) cm</li> <li> \(\X1\X5 = \l3) cm</li>}
\text{donnees=\ch=1?\donnees <li>\(\X1\X2 = \l2) cm </li><li> \(\X1\X3 = \l4) cm</li>:\donnees <li>\(\X2\X4 = \l5) cm </li><li> \(\X3\X5 = \l6) cm</li>}
#endif

#if defined TARGET_parat2  | defined TARGET_parat1
\text{rep=\X1\X5,\X1\X3,\X1\X4,\X1\X2,\X4\X2,\X5\X3}
\text{valrep=\l3,\l6,\l1,\l5,\l2,\l4}
\text{donnees=<li>\(\X1\X4 = \l1) cm</li> <li> \(\X1\X5 = \l3) cm</li>}
\text{donnees=\ch=1?\donnees <li>\(\X1\X2 = \l5) cm </li><li> \(\X1\X3 = \l6) cm</li>:\donnees <li>\(\X2\X4 = \l2) cm </li><li> \(\X3\X5 = \l4) cm</li>}
#endif

\if{\confparm2=1}{
\matrix{stepdon=r1,r2,r3,r4,r5,r6,r7,r8,c1,c2,c3}
}{
\matrix{stepdon=c2,c3}}
\steps{\stepdon}

\statement{<table><tr>
<td>
I punti \(\X1), \(\X4) e \(\X2) sono allineati e i punti \(\X1), \(\X5) e \(\X3) sono come in figura. Conosciamo le seguenti lunghezze: 
<ul> 
\donnees
</ul>
<b>Domanda:</b> Le rette \((\X4\X5)) e \((\X3\X2)) sono parallele?
</td><td>
<div class="wimscenter">\draw{\xrange,\yrange}{\dessin}</div>
<div class="wims_instruction">Il disegno è indicativo e non rispetta le lunghezze dell'enunciato.</div>
</td>
</tr></table>
\if{\confparm2=1}{
Scrivere (trascinando col mouse le etichette in basso) due rapporti di lunghezze utili per rispondere alla domanda:
<table class="wimscenter">
<tr><td>
<table class="wimscenter">
<tr>
<td rowspan="3">\(R_1)</td>
<td rowspan="3">=</td>
<td>\embed{reply 1,50x20x1}</td>
</tr><tr>
<td><hr /></td>
</tr><tr>
<td> \embed{reply 2,50x20x1}</td>
</tr></table>
</td><td>e</td><td>
<table class="wimscenter">
<tr>
<td rowspan="3">\(R_2)</td>
<td rowspan="3">=</td>
<td>\embed{reply 3,50x20x1}</td>
</tr><tr>
<td><hr /></td>
</tr><tr>
<td> \embed{reply 4,50x20x1}</td>
</tr></table>
</td></tr></table>
Sostituire le lunghezze con i loro valori e ridurre le due frazioni a denominatore comune per confrontarle:
<table class="wimscenter">
<tr><td>
<table>
<tr>
<td rowspan="3">\(R_1)</td>
<td rowspan="3"> =  </td>
<td>\embed{reply 5,5}</td>
</tr><tr>
<td><hr /></td>
</tr><tr>
<td> \embed{reply 6,5}</td>
</tr></table>
</td><td>e</td><td>
<table>
<tr>
<td rowspan="3">\(R_2)</td>
<td rowspan="3">=</td>
<td>\embed{reply 7,5}</td>
</tr><tr>
<td><hr /></td>
</tr><tr>
<td> \embed{reply 8,5}</td>
</tr></table>
</td></tr></table>
I rapporti \(R_1) e \(R_2) \embed{choice 1}. Si deduce quindi, per \embed{choice 2}, che le rette \((\X4\X5)) e \((\X3\X2)) \embed{choice 3}.}{
Risposta : Utilizzando \embed{choice 2}, si deduce che le rette \((\X4\X5)) e \((\X3\X2)) \embed{choice 3}.}
}

\answer{Numérateur 1}{\r1;\rep}{type=clickfill}
\answer{Dénominateur 1}{\r2;\rep}{type=clickfill}
\answer{Numérateur 2}{\r4;\rep}{type=clickfill}
\answer{Dénominateur 2}{\r5;\rep}{type=clickfill}
\answer{Valeur numérateur 1}{\r7}{type=auto}
\answer{Valeur dénominateur 1}{\r8}{type=auto}
\answer{Valeur numérateur 2}{\r9}{type=auto}
\answer{Valeur dénominateur 2}{\r10}{type=auto}
\choice{Ordre}{\good1}{\bad1}
\choice{Théorème}{\good2}{\bad2}
\choice{Conclusion}{\good3}{\bad3}

\text{rap1b=\rap1,\r1/\r2,\r4/\r5}
\text{rap1b=wims(listuniq \rap1b)}
\integer{rap1b=items(\rap1b)}
\text{rap2b=\rap2,\r1/\r2,\r4/\r5}
\text{rap2b=wims(listuniq \rap2b)}
\integer{rap2b=items(\rap2b)}
\condition{Rapporti corretti}{((\rap1b=2 or \rap2b=2) and \r1/\r2 notsametext \r4/\r5)}

\real{r1p=item(positionof(\r1,\rep),\valrep)}
\real{r2p=item(positionof(\r2,\rep),\valrep)}
\real{r4p=item(positionof(\r4,\rep),\valrep)}
\real{r5p=item(positionof(\r5,\rep),\valrep)}

\condition{Stessi denominatori}{\r8==\r10}
\condition{Verifica del primo rapporto}{(\r7)/(\r8)==(\r1p)/(\r2p)}
\condition{Verifica del secondo rapporto}{(\r9)/(\r10)==(\r4p)/(\r5p)}
