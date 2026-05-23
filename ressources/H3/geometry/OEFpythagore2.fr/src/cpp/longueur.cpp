target=longueur1 longueur2
#define TITRE Calculer une longueur
#if defined TARGET_longueur1
# define NUM 1
#endif
#if defined TARGET_longueur2
# define NUM 2
#endif
\title{TITRE NUM}
\language{fr}
\range{-5..5}
#include "author.inc"
\author{Fabrice,Guerimand;Thomas,Wareth}
La correction a été ajoutée par Thomas Wareth
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{1000}

\integer{confparm1=\confparm1 notitemof 0,1?1}
\integer{confparm2=\confparm2=?1}

#include "triangle.inc"

\integer{u=random(2..6)}
\integer{v=random(1..\u-1)}
\integer{sm=max(\u^2-\v^2,2*\u*\v)}
\integer{mn=min(\u^2-\v^2,2*\u*\v)}
\integer{sn=(\mn^2+\sm^2)^(1/2)}
\real{k=randint(15..25)/10}
\real{l2=\sm*\k}
\real{l1=\sn*\k}
\real{l3=\mn*\k}

#if defined TARGET_longueur1
 \title{TITRE 1}
 \text{inc=\X1\X3}
 \text{values=\(\X1\X2 = \l2),\(\X2\X3 = \l3)}
 \integer{type=1}
 \real{rep5=\l1}
#endif

#if defined TARGET_longueur2
 \title{TITRE 2}
 \integer{type=2}
 \integer{ch=randint(1,2)}
 \if{\ch=1}{
  \text{inc=\X2\X3}
  \text{values=\(\X1\X2 = \l2),\(\X1\X3 = \l1)}
  \real{rep5=\l3}
 }{
  \text{inc=\X1\X2}
  \text{values=\(\X2\X3 = \l3),\(\X1\X3 = \l1)}
  \real{rep5=\l2}
 }
#endif

\real{rep4=\rep5^2}
\text{values=shuffle(\values)}
\text{longueur=wims(replace internal , by &nbsp;&nbsp; in \values)}
\text{enonce1=randitem(Le triangle \(\X1\X2\X3) est rectangle en \(\X2),L'angle \(\widehat{\X1\X2\X3}) est droit)}
\text{enonce=\enonce1.<br> Les longueurs suivantes sont connues : <div class="wimscenter">\longueur</div> Calculer la longueur du segment \([\inc]).}

\text{choix1=la réciproque du théorème de Pythagore,le théorème de Pythagore}
\text{rep1=item(2,\choix1)}

\text{listchoix=\(\X1\X2),\(\X1\X3),\(\X2\X3),\(\X1\X2^2),\(\X1\X3^2),\(\X2\X3^2),+}
\text{solg=item(5,\listchoix)}
\text{sold=item(4,\listchoix),item(7,\listchoix),item(6,\listchoix)|item(6,\listchoix),item(7,\listchoix),item(4,\listchoix)}

\if{\confparm2=1}{
 \text{tmp=c1,r1,r2,r3,r4}
}{
 \text{tmp=r4}
}
\steps{\tmp}

\statement{\if{\confparm1=1}{
\enonce
<div class="wimscenter">
\draw{\xrange,\yrange}{\dessin}</div>
<div class="wims_instruction">Le dessin n'est pas à l'échelle.</div>
}{
\enonce}
<div><b>Votre réponse</b> :
\if{\confparm2=1}{
   Dans le triangle \(\X1\X2\X3) rectangle en \(\X2), d'après \embed{c1} on obtient :
<div class="wimscenter">\embed{r1,40x35x1} = \embed{r2,40x35x3}</div>
   Donc : <label for="reply3">\(\inc^2 = )</label>\embed{r3,7}<br>
   Donc : <label for="reply4">\(\inc = )</label>\embed{r4,7}
}{
  <label for="reply4">\(\inc = )</label>\embed{r4,7}.
}
</div>
}

\choice{Théorème}{\rep1}{\choix1}{weight=2}
\answer{Membre de gauche}{\solg;\listchoix}{type=clickfill}{weight=1.5}
\answer{Membre de droite}{\sold;\listchoix}{type=clickfill}{weight=1.5}
\answer{\(\inc^2 = )}{\rep4}{type=numexp}{weight=2}
\answer{\(\inc = )}{\rep5}{type=numexp}{weight=3}

#if defined TARGET_longueur1
\solution{
   Le triangle \(\X1\X2\X3) est rectangle en \(\X2). On a donc selon <strong>\rep1</strong> :
<div class="wimscenter">\(\X1\X3^2 = \X1\X2^2 + \X2\X3^2)</div>
<p>On sait que \(\X1\X2 = \l2) et que \(\X2\X3 = \l3).</p>
   On a donc :
<div class="wimscenter"> \(\inc^2 = \l2^2 + \l3^2 = \rep4)</div>
<div class="wimscenter"> \(\inc = \sqrt{\rep4} = \rep5)</div>
}
#else
\solution{
   Le triangle \(\X1\X2\X3) est rectangle en \(\X2). On a donc selon <strong>\rep1</strong> :
<div class="wimscenter">\(\X1\X3^2 = \X1\X2^2 + \X2\X3^2)</div>
\if{\ch=1}{
   On sait que \(\X1\X2 = \l2) et que \(\X1\X3 = \l1).<p>
   On a donc : </p>
<div class="wimscenter"> \(\inc^2 = \l1^2 - \l2^2 = \rep4)</div>
<div class="wimscenter"> \(\inc = \sqrt{\rep4} = \rep5)</div>
}{
   On sait que \(\X2\X3 = \l3) et que \(\X1\X3 = \l1).<p>
   On a donc : </p>
<div class="wimscenter"> \(\inc^2 = \l1^2 - \l3^2 = \rep4)</div>
<div class="wimscenter"> \(\inc = \sqrt{\rep4} = \rep5)</div>
}}
#endif
