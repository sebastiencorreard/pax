target= pap pap2 triangle triangle2

\language{it}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{1000}
\integer{size=50}

\integer{confparm2=\confparm2=?2}
\integer{confparm3=\confparm3=?1}

\integer{ch=random(1..2)}
\if{\confparm3=1}{
\integer{l1=random(2..9)}
\integer{l2=random(10..15)}
\integer{tmpl=random(7..19)}
}{
\integer{l1=random(20..90)}
\integer{l2=random(100..150)}
\integer{tmpl=random(70..190)}
\real{l2=\l2/10}
\real{l1=\l1/10}
\real{tmpl=\tmpl/10}
}

#if defined TARGET_pap
\title{Lunghezza nodo}
\integer{calcul=1}
#include "papillon.inc"
\real{l5=\l1+\l2}
#endif

#if defined TARGET_pap2
\title{Lunghezza nodo 2}
\integer{calcul=2}
#include "papillon.inc"
\real{l5=\l1+\l2}
#endif

#if defined TARGET_triangle
\title{Lunghezza triangolo}
\integer{calcul=1}
#include "triangle.inc"
\real{l5=\l2-\l1}
#endif

#if defined TARGET_triangle2
\title{Lunghezza triangolo 2}
\integer{calcul=2}
#include "triangle.inc"
\real{l5=\l2-\l1}
#endif

\integer{ch2=random(1..2)}
\text{laffl3=\X1\X4,\X4\X5}
\text{laffl4=\X1\X2,\X2\X3}
\text{affl3=item(\ch2,\laffl3)}
\text{affl4=item(\ch2,\laffl4)}

\if{\ch=1}{
\real{l3=\tmpl}
\real{l4=\l2/\l1*\l3}
\real{calc=\l4}
\text{r1=\affl3}
\text{mes=\r1 = \l3}
\text{quest=\affl4}
\text{r2=\X1\X3}
\text{r3=\X1\X5}}
{\real{l4=\tmpl}
\real{l3=\l1/\l2*\l4}
\real{calc=\l3}
\text{r1=\affl4}
\text{mes=\r1 = \l4}
\text{quest=\affl3}
\text{r2=\X1\X5}
\text{r3=\X1\X3}}

\integer{tmp=\calc*10}
\real{calc=\tmp/10}

\text{rep=\X1\X5,\X1\X3,\laffl3,\laffl4,\X4\X2,\X5\X3}

\text{mes2=\calcul=1?\X1\X5 = \l1 :\X3\X5 = \l5 }

\if{\confparm2=1}{
\matrix{stepdon=r1,r2,r3,r4}
}{
\matrix{stepdon=r4}}
\steps{\stepdon}

\statement{
<table>
<tr><td>
Le rette \((\X5\X3)) e \((\X4\X2)) si intersecano nel punto \(\X1). Le rette \((\X2\X3)) e \((\X4\X5)) sono parallele. Lo scopo è calcolare la lunghezza del segmento [\quest] conoscendo le seguenti lunghezze: 
<ul>
<li>\mes2 cm </li>
<li>\X1\X3 = \l2 cm </li> 
<li>\mes cm </li>
</ul>
</td>
<td><div class="wimscenter">\draw{\xrange,\yrange}{\dessin}</div>
<div class="wims_instruction">
Il disegno è indicativo e non rispetta la lunghezza dell'enunciato-
</div>
</td></tr></table>
\if{\confparm2=1}{
<b>Domanda 1</b>: Utilizzando il teorema di Talete, scrivere la proporzione che permette di trovare la lunghezza di \([\quest]). 
<table class="wimscenter wimsnoborder">
<tr><td>\quest</td><td></td><td>\embed{reply 2,\size}</td>
</tr><tr>
<td><hr /></td><td>=</td>
<td><hr /></td>
</tr><tr>
<td>\embed{reply 1,\size}</td><td></td><td> \embed{reply 3,\size}</td>
</tr></table>
<b>Domanda 2</b>: Qual è la lunghezza, a meno di un millimetro, di [\quest]? <br/>
Risposta: \embed{reply 4, 10}}
{Qual è la lunghezza, a meno di un millimetro, di [\quest]?}
<br/>
<div class="wims_instruction">
Come separatore per i decimali utilizza il punto.
</div>}

\answer{den1}{\r1;\rep}{type=clickfill}
\answer{num1}{\r2;\rep}{type=clickfill}
\answer{den2}{\r3;\rep}{type=clickfill}
\answer{lunghezza}{\calc cm}{type=units}
