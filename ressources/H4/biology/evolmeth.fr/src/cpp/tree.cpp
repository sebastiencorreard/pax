target=evolmeth4

#include "lang_fr.inc"
\author{Bernadette, Perrin-Riou}
\email{bpr@math.u-psud.fr}
\title{F - TITRE}

#include "lang_fr.inc"
\integer{N=5}
\integer{M=4}
\integer{N=\confparm1=1 ? randint(3..4)}
\integer{M=\confparm1=1 ? randint(3..4)}
\integer{N=\confparm1=2 ? 4}
\integer{M=\confparm1=2 ? randint(4..5)}
\integer{N=\confparm1=3 ? randint(5..6)}
\integer{M=\confparm1=3 ? randint(5..5)}
\text{liste=A,B,C,D,E,F,F,G,H,I,J}
\text{list_orga=\liste[1..\N]}
\text{list_char=wims(values x for x=1 to \N)}
\text{bat0=shuffle(factorial(\N))}

\text{perm=pari(bat0=[\bat0]; vector(\M,i,numtoperm(\N,bat0[i])))}

\text{bat=wims(declosing \perm[1])}
\text{size=200,200}
\text{matrice=pari(matrix(\N,\N,i,j,if(i<= j,1)))}
\text{matrice=\matrice[\bat;]}
\text{tableauphyl=,\list_orga}

\for{j=1 to \N}{
  \text{tableauphyl=\tableauphyl
\name_car \list_char[\j],\matrice[\j;]}
}
\matrix{tableauphyl=\tableauphyl}
\text{tableauphyl=slib(text/matrixhtml [\tableauphyl], wimscenter wimsborder, TH=[1;1])}
\text{Dessincanvas=}
\for{j=1 to \M}{
  \text{perminv=}
  \text{bat1=wims(declosing \perm[\j])}
  \for{t=1 to \N}{
    \text{k=position(\t, \bat1)}
    \text{perminv=wims(append item \k to \perminv)}
  }
  \matrix{data=wims(makelist \name_orga x for x in \list_orga)
wims(makelist \name_car x for x in \list_char[\perminv])}
#include "tree.inc"
\text{Dessincanvas=wims(append item canvasdraw(\size
\dessin) to \Dessincanvas)}
}
\text{b=shuffle(\M)}
\text{rep=position(1,\b)}
\text{choix=wims(makelist x for x=1 to \M)}

\statement{
<div class="float_right">
\tableauphyl
</div>
\instruction
<div class="wimscenter">
<ul class="inline">
\for{i=1 to \M}{<li>\embed{r1,\i} \Dessincanvas[\b[\i]]</li>}
</ul>
</div>}

\answer{}{\rep;\choix}{type=radio}
