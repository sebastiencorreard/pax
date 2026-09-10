target=mouvement1 mouvement2 mouvement3 mouvement4 mouvement5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_mouvement1
 \integer{ch=randint(1..2)}
 \integer{f=randint(6..12)}
 \integer{nb=\ch=1?floor(98/\f):13}
 \text{formule=\ch=1?\f*s:(s)^2/2}
 \text{dessin=xrange -51,50
yrange -3,3
arrow -51,0,50,0,20,black}
 \for{k=0 to \nb}{
  \text{v=evalue(-49+\formule,s=\k)}
  \text{dessin=\dessin
fcircle \v,0,10,blue}
 \text{figure=draw(1000,100
\dessin)}
 }
 \text{enonce=\name_enonce:
<div class="wimscenter"><img src="\figure" alt=""></div>}
 \text{question=\name_question}
 \text{good=\bad[\ch]}
#endif
#if defined TARGET_mouvement2
 \integer{ch=randint(1..2)}
 \if{\ch=1}{
  \integer{p=randint(10..15)}
  \integer{nb=floor(300/\p)}
  \text{p=wims(values \p*v for v=0 to \nb-1)}
 }{
  \text{p=0,10,30,60,100,150,210,280}
  \text{nb=8}
 }
 \text{dessin=circle 150,150,260,black}
 \for{k=1 to \nb}{
  \real{x1=150+130*cos(\p[\k]/180*pi)}
  \real{y1=150+130*sin(\p[\k]/180*pi)}
  \text{color=\k=1?green:blue}
  \text{color=\k=\nb?red:\color}
  \text{dessin=\dessin
fcircle \x1,\y1,10,\color}
 \text{figure=draw(300,300
\dessin)}
 }
 \text{enonce=\name_enonce1:
  <div class="wimscenter"><img src="\figure" alt=""></div>
  \name_enonce2}
 \text{question=\name_question}
 \text{good=\bad[\ch]}
#endif
#if defined TARGET_mouvement3
 \integer{ch=randint(1..2)}
 \text{dessin=slib(draw/repere 400,400,20,0,10,0,10,1,1,black,grey)}
 \text{dessin=\dessin
text black,385,385,medium,T
text black,5,5,medium,D}
 \if{\ch=1}{
  \text{l=randint(3..7)}
  \text{dessin=\dessin
linewidth 2
segment 20,380,380,20+36*\l,blue}
 }{
  \text{l1=randint(4..9)}
  \text{l2=randint(1..2)}
  \text{l3=randint(2..4)}
  \text{l4=randint(5..6)}
  \text{l5=randint(8..9)}
  \text{dessin=\dessin
linewidth 2
segment 20,380,20+36*\l3,20+36*\l1,blue
segment 20+36*\l3,20+36*\l1,20+36*\l4,20+36*\l1,blue
segment 20+36*\l4,20+36*\l1,20+36*\l5,20+36*\l2,blue}
 }
 \text{figure=draw(400,400
\dessin)}
 \text{name=slib(lang/fname fr,boy)}
 \text{enonce=\name_enonce[1;] \name \name_enonce[2;]
  <div class="wimscenter"><img src="\figure" alt=""></div>}
 \text{question=\name_question[1] \name \name_question[2]}
 \text{good=\bad[\ch]}
#endif
#if defined TARGET_mouvement4
 \integer{ch=randint(1..2)}
 \text{t=0,randitem(1,1.5),randitem(2,2.5),randitem(3,4),randitem(4.5,5.5),randitem(6,7)}
 \if{\ch=1}{
  \text{v=randint(5..10)*10}
  \text{v=wims(values \v for v=1 to 5)}
 }{
  \text{v=shuffle(50,60,70,80,90,100)}
 }
 \text{d=0}
 \for{k=1 to 5}{
  \integer{tmp=\d[\k]+\v[\k]*(\t[\k+1]-\t[\k])}
  \text{d=wims(append item \tmp to \d)}
 }
 \text{d=item(2 to -1,\d)}
 \text{t=item(2 to -1,\t)}
 \text{name=slib(lang/fname fr,boy)}
 \text{enonce=\name_enonce[1;] \name \name_enonce[2;]
<table class="wimscenter wimsborder">
<tr><th>\name_head[1]</th><td>\t[1]</td><td>\t[2]</td><td>\t[3]</td><td>\t[4]</td><td>\t[5]</td></tr>
<tr><th>\name_head[2]</th><td>\d[1]</td><td>\d[2]</td><td>\d[3]</td><td>\d[4]</td><td>\d[5]</td></tr>
</table>}
 \text{question=\name \name_question}
 \text{good=\bad[\ch]}
#endif
#if defined TARGET_mouvement5
 \integer{ch=randint(1..2)}
 \integer{t=randitem(1,2.5,5)*100}
 \text{t=wims(values \t*t for t=0 to 5)}
 \if{\ch=1}{
  \text{v=randint(2..7)}
  \text{v=wims(values \v for v=1 to 5)}
 }{
  \text{v=shuffle(2,3,4,5,6,7)}
 }
 \text{d=0}
 \for{k=1 to 5}{
  \integer{tmp=\d[\k]+\v[\k]}
  \text{d=wims(append item \tmp to \d)}
 }
 \text{d=item(2 to -1,\d)}
 \text{t=item(2 to -1,\t)}
 \text{name=slib(lang/fname fr,girl)}
 \text{enonce=\name \name_enonce[1]<br>\name_enonce[2]:
<table class="wimscenter wimsborder">
<tr><th>Graduation (en mL)</th><td>\t[1]</td><td>\t[2]</td><td>\t[3]</td><td>\t[4]</td><td>\t[5]</td></tr>
<tr><th>Temps (en s)</th><td>\d[1]</td><td>\d[2]</td><td>\d[3]</td><td>\d[4]</td><td>\d[5]</td></tr>
</table>}
 \text{question=\name_question}
 \text{good=\bad[\ch]}
#endif
\statement{\enonce
<p>
\question ?
</p>}

\choice{}{\good}{\bad}
