target=enchainement
\title{Enchaînement}
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100000}
\integer{confparm1=\confparm1 notitemof 0,1?1}

\matrix{lettre=A,B,C,D
T,I,R,J
E,F,G,H
D,E,F,G}
\text{lettre=randrow(\lettre)}
\text{lettre=shuffle(\lettre)}
\text{X1=item(1,\lettre)}
\text{X2=item(2,\lettre)}
\text{X3=item(3,\lettre)}
\text{X4=item(4,\lettre)}

\integer{xrange=240}
\integer{yrange=140}

\integer{des_a=random(80..160)}

\text{dessin=segment 20,20,20,120,black
segment 20,120,220,120,black
segment 20,20,220,120,black
segment 20,20,\des_a,120,black
text black,10,125,medium,\X2
text black,10,10,medium,\X1
text black,225,125,medium,\X3
text black,\des_a,125,medium,\X4}

\integer{rect=randitem(1,2)}
\integer{type=randitem(1,2)}
\integer{choix=randitem(1,2)}

\integer{u=random(2..6)}
\integer{v=random(1..\u-1)}
\integer{sm=max(\u^2-\v^2,2*\u*\v)}
\integer{mn=min(\u^2-\v^2,2*\u*\v)}
\integer{sn=(\mn^2+\sm^2)^(1/2)}
\real{k=randint(15..25)}
\real{l2=\sm*\k}
\real{l1=\sn*\k}
\real{l3=\mn*\k}
\text{listchoix==,\(\neq)}

\if{\rect!=1}{
 \real{l1=\l1+randint(5..15)}
 \text{listchoix=\(\neq),=}
}
\real{l1=\l1/10}
\real{l2=\l2/10}
\real{l3=\l3/10}
\text{listp=\(\X1\X4^2),\(\X2\X4^2)}
\text{listg=\(\X1\X3^2),\(\X2\X3^2)}
\if{\type=1}{
 \text{longueur=\(\X1\X4 = \l1),\(\X2\X4 = \l2),\(\X1\X2 = \l3)}
 \text{triname=\(\X1\X2\X4)}
 \text{listchoix=\listchoix,\(\X1\X2^2),\listp,\listg}
 \if{\choix=1}{
  \text{inc=\X1\X3}
  \real{l4=randint(10*\l2+1..15*\l2)/10}
  \text{longueur=\longueur,\(\X2\X3 = \l4)}
  \text{rep3=(\l3^2+\l4^2)^(1/2)}
 }{
  \text{inc=\X2\X3}
  \real{l4=randint(20*\l1..25*\l1)/10}
  \text{longueur=\longueur,\(\X1\X3 = \l4)}
  \text{rep3=(\l4^2-\l3^2)^(1/2)}
 }
}{
 \text{longueur=\(\X1\X3 = \l1),\(\X2\X3 = \l2),\(\X1\X2 = \l3)}
 \text{triname=\(\X1\X2\X3)}
 \text{listchoix=\listchoix,\(\X1\X2^2),\listg,\listp}
 \if{\choix=1}{
  \text{inc=\X1\X4}
  \real{l4=randint(10..10*\l2-10)/10}
  \text{longueur=\longueur,\(\X2\X4 = \l4)}
  \text{rep3=(\l3^2+\l4^2)^(1/2)}
 }{
  \text{inc=\X2\X4}
  \real{l4=randint(10*\l3+1..10*\l1-10)/10}
  \text{longueur=\longueur,\(\X1\X4 = \l4)}
  \text{rep3=(\l4^2-\l3^2)^(1/2)}
 }
}
\text{listchoix=\listchoix,+,\(\X1\X2),\(\X1\X3),\(\X2\X3),\(\X2\X4),\(\X1\X4)}
\text{solegal=wims(item 4,1,3,8,5 of \listchoix)|wims(item 4,1,5,8,3 of \listchoix)|wims(item 3,8,5,1,4 of \listchoix)|wims(item 5,8,3,1,4 of \listchoix)}
\text{longueur=shuffle(\longueur)}
\text{longueur=wims(replace internal , by &nbsp;&nbsp; in \longueur)}
\text{choix1=est rectangle,n'est pas rectangle}
\text{choix2=la réciproque du théorème de Pythagore,le théorème de Pythagore}
\text{rep1=item(\rect,\choix1)}
\text{rep2=item(\rect,\choix2)}
\text{unit=randitem(cm,m,dm,dam)}
\text{listpreci=dixième,centième,millième}
\text{tmp=\rep3}
\integer{chprec=randint(1..3)}
\integer{rep3=\rep3*10^\chprec}
\real{rep3=\rep3/10^\chprec}
\text{precision=item(\chprec,\listpreci)}
\text{mstep=c1,c2,r1}
\nextstep{\mstep}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{\xrange,\yrange}{\dessin}
  <div class="wims_instruction">Ce dessin est un croquis, il ne respecte aucune proportion.</div>
</div>
 <div class="medium_size text_col">
\(\X1\X2\X3) est un triangle et \(\X4) est un point du segment \([\X2\X3]).
Les longueurs suivantes (en \unit) sont connues :
<div class="wimscenter">\longueur</div>

\if{\step=1}{
 <p>Le triangle \triname est-il rectangle en \X2 ?</p>
 <b>Votre réponse</b> : \embed{r1,40x35x5}<br>
  Donc, d'après \embed{c2}, le triangle \triname \embed{c1}.
}{
\if{\rect=1}{
<ol>
 <li> <p>Le triangle \triname est-il rectangle en \X2 ?</p>
 <b>Votre réponse</b> : D'après \rep2, le triangle \triname \rep1.</li>
 <li> Quelle est la longueur du segment \([\inc]) ?
 <div class="wims_instruction">Vous donnerez votre résultat arrondi au \precision.</div>
 <b>Votre réponse</b> \(\inc =) \embed{r2,5} \unit.</li>
 </ol>
}{
 Le triangle \triname est-il rectangle en \X2 ?
}
}
</div>
</div>
}
\text{mstep=\rect=1 and \step=2?r2}
\answer{Formule}{\solegal;\listchoix}{type=clickfill}{weight=3}
\choice{Nature}{\rep1}{\choix1}{weight=1}
\choice{Théorème}{\rep2}{\choix2}{weight=2}
\answer{\(\inc)}{\rep3}{type=numexp}{weight=4}
