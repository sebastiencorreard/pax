target=dessineratio

#include "avant_header.inc"
#include "css.inc"

\title{Dessiner un ratio dans un damier}

dimensions du rectangle
\integer{x=random(2..5)}
\integer{y=random(2..5)}
agrandissement
\integer{agr=randint(1..2)}
\integer{x=\x*\agr}
\integer{y=\y*\agr}
\integer{X=20*\x}
\integer{Y=20*\y}
%%définition du nombre de cases à colorier
\integer{nbrecase=\x*\y}
\integer{color=randint(1..\nbrecase-1)}
%%Eviter le 1:1
\real{moit=\nbrecase/2}
\if{\color=\moit}{\integer{col1=randint(1..\color-1)}
\integer{col2=randint(\color+1..\nbrecase-1)}
\text{liste=\col1,\col2}
\text{color=randomitem(\liste)}}
%%Fin du éviter le 1:1
\integer{nocolor=\nbrecase-\color}
\integer{pgcd=gcd(\color,\nocolor)}
\integer{newratio1=\color/\pgcd}
\integer{newratio2=\nocolor/\pgcd}
\integer{nbrefois=\nbrecase/(\newratio1+\newratio2)}

\text{name_statement=Colorier des cases en rouge afin que le nombre de cases rouges et le nombre de cases jaunes soient dans le ratio}
\text{name_instruction=Commencer par sélectionner la couleur rouge en cliquant sur le petit rectangle jaune.}
\text{name_condition=Votre réponse est-elle juste&nbsp;?&nbsp;}

\text{tableau=<table class="wimsborder unstriped">}
\integer{t=0}
\for {i=1 to \y}{
  \text{tableau=\tableau <tr>}
  \for {j=1 to \x}{
    \integer{t=\t+1}
    \if {\t<=\color}
      {\text{tableau=\tableau <td class="damier col2"></td>}}
      {\text {tableau=\tableau <td class="damier col1"></td>}}
  }
  \text{tableau=\tableau</tr>}
}
\text{tableau=\tableau </table>}

\statement{
\name_statement[1] <span class="nowrap" style="font-weight:bold">
\(\newratio1 : \newratio2 \) </span> ( lire \(\newratio1\) pour \(\newratio2\)&nbsp;).
<div class="wimscenter">
\embed{r1, \X x \Y
[xrange 0,\x
yrange 0,\y
background_color yellow
colors red]}
</div>
<div class="wims_instruction">
\name_instruction
</div>
}

#include "help.inc"

\answer{ }{\rep }{type= clicktile}
\text{analyse=wims(listuniq \rep)}
\integer{analyse=items(\analyse)-1}
\condition{\name_condition}{\color = \analyse}

\solution{Une réponse possible est
<div class="unbreakable">\tableau</div>}

\feedback{\nocolor=\analyse}{ <div class="macss">Attention, vous avez inversé les couleurs, il doit y avoir \color \if{\color>1}{cases rouges.}{case rouge.}</div>}
