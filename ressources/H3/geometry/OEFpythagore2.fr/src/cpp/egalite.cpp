target= egalite1 egalite2
#define TITRE Égalité de Pythagore
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{100000}
#if defined TARGET_egalite1
# define NUM 1
#endif
#if defined TARGET_egalite2
# define NUM 2
#endif
 \title{TITRE NUM}
\integer{confparm1=\confparm1 notitemof 0,1?1}

#if defined TARGET_egalite1
# include "triangle.inc"
 \integer{ch=1}
 \integer{type=1}
 \text{enonce2=En utilisant les étiquettes, reconstituez l'égalité
  que vous pouvez déduire du théorème de Pythagore.}
#endif
#if defined TARGET_egalite2
# include "2triangles.inc"
 \integer{type=2}
 \integer{ch=randitem(1,2)}
 \text{tri=\X1\X2\X3,\X1\X2\X4}
 \text{tri=item(\ch,\tri)}
 \text{enonce2=En utilisant les étiquettes, reconstituez l'égalité
  que vous pouvez déduire du théorème de Pythagore dans le triangle \(\tri\).}
#endif
\text{enonce1=randitem(Le triangle \(\X1\X2\X3) est rectangle en \(\X2),L'angle \(\widehat{\X1\X2\X3}) est droit)}

\text{listchoix=\(\X1\X2),\(\X1\X3),\(\X2\X3),\(\X1\X2^2),\(\X1\X3^2),\(\X2\X3^2),+}
\text{listchoix2=\(\X1\X4),\(\X1\X4^2),\(\X2\X4),\(\X2\X4^2)}

\if{\ch=1}{
\text{solg=item(5,\listchoix)}
\text{sold=item(4,\listchoix),item(7,\listchoix),item(6,\listchoix)|item(6,\listchoix),item(7,\listchoix),item(4,\listchoix)}
}{
\text{solg=item(2,\listchoix2)}
\text{sold=item(4,\listchoix),item(7,\listchoix),item(4,\listchoix2)|item(4,\listchoix2),item(7,\listchoix),item(4,\listchoix)}
}

\if{\type=2}{\text{listchoix=\listchoix,\listchoix2}}

\statement{
\if{\confparm1=1}{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{\xrange,\yrange}{\dessin}</div>
 <div class="medium_size text_col">
 \enonce1. \enonce2
 </div>
</div>
}{
<div> enonce1. \enonce2 ?</div>}
<div class="wimscenter">
\embed{r1,40x35x1} = \embed{r2,40x35x3}
</div>
}

\answer{Membre de gauche}{\solg;\listchoix}{type=clickfill}
\answer{Membre de droite}{\sold;\listchoix}{type=clickfill}
