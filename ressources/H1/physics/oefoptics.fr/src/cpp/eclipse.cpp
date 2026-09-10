target=eclipse1 eclipse2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_eclipse1
# define HELP 1
#endif
#if defined TARGET_eclipse2
# define HELP 2
#endif
Si la lune passe entre le soleil et la terre, c'est une éclipse de soleil:
le soleil est caché par la lune. L'ombre de la lune sur la terre donne l'impression
qu'il fait nuit en plein jour.
Si la lune traverse l'ombre de la terre, c'est une éclipse de lune;
la lune n'est plus éclairée par le soleil, elle semble disparaitre.
distance soleil-terre=23400*rT
distance terre-lune=60*rT en moyenne
rayon soleil=109*rT
rayon lune=0.27*rT
cone d'ombre: longueur= TS*rT/(rS-rT)
\text{choix=randitem(1,2)}
\text{STEP=r1}
\text{choixe=\choix}
\if{\choix=1}{
#include "choix1.inc"
}
\if{\choix=2}{
#include "choix2.inc"
}
\text{dessin_circles=fcircles yellow,0,0,\rS
fcircles lightblue,\La,\rL
circles red,\T,0,\rT}
\text{size=pari([(\l+1)/2*400,400])}
\text{dessin_prel=xrange -\range,\l*\range
yrange -\range,\range
hline 0,0,black
text black,0,0,giant,S
text black,\La,giant, L
text black,\T,0,giant, T}
\if{\choix=1}{
  \text{tmp1=\slx1*(\limx1-(\P[1]))+(\P[2])>0?acos(\limx1/\rS):-acos(\limx1/\rS)}
  \text{tmp2=\slx2*(\limx2-(\P[1]))+(\P[2])>0?acos(\limx2/\rS):-acos(\limx2/\rS)}
  \text{tmp=\tmp1>\tmp2 ?pari(180/pi*[\tmp2,\tmp1]): pari(180/pi*[\tmp1,\tmp2])}
  \text{dessin_hidden=arc 0,0,2*\rS,2*\rS,\tmp,black}
  \text{dessinout1=\dessin_prel
\dessin_circles}
  \text{dessinout10=\dessinout1
\dessin_tangente}
  \text{dessinout2=\dessin_prel
\dessin_circles
linewidth 2
\dessin_zone}
\text{dessinout20=\dessinout2
\dessin_coneombre
  linewidth 5
\dessin_hidden}
}
\if{\choix=2}{
  \text{dessinout1=\dessin_prel
  \dessin_circles}
\text{dessinout10=\dessinout1
  \dessin_tangente}
  circles red \orbite
\text{dessinout2=\dessinout1}
\text{dessinout20=\dessinout10}
}
\text{name_choix2=\name_choix2[\choix;]}
\text{STEP=\choixe!=3? \STEP
  r2}
\steps{\STEP}

\statement{
\if{\step=1}{<div class="wims_question">
\name_question1
<ul><li>\embed{r1,1}</li>
<li>\embed{r1,2}</li>
<li>\embed{r1,3}</li>
</ul>
</div>
}
\if{\step>=2}{
  <p>\name_question1 \name_choix1[\choixe].</p>
  <div class="wims_question">
\if{\choix=1}{\name_question3}{\name_question2}
<ul>
<li>\embed{r2,1}</li>
<li>\embed{r2,2}</li>
<li>\embed{r2,3}</li>
</ul>
</div>}
<div class="wimscenter">
#if HELP==1
\if{\step=1}{
  \draw{\size}{\dessinout10}}{
  \draw{\size}{\dessinout20}}
#else
\if{\step=1}{
  \draw{\size}{\dessinout1}}{
  \draw{\size}{\dessinout2}}
#endif
</div>
<div class="wims_warning">\name_warning</div>
}
\answer{}{\choixe;\name_choix1}{type=radio}
\answer{}{\choixp;\name_choix2}{type=radio}
#if HELP==2
\feedback{1=1}{
\draw{\size}{\dessinout20}
}
#endif
\draw{\size}{\dessin
\dessincircle
\dessin1
\dessin3}
