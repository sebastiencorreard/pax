target=coordpt ptcoord

\language{fr}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
\keywords{coordinates}
#include "css.inc"

\integer{xrange=400}
\integer{yrange=400}

\text{A=randitem(A,B,C,D,E)}

\integer{xa=randint(-5..5)}
\integer{ya=randint(-5..5)}

\text{graph=slib(draw/repere \xrange,\yrange,20,-6,6,-6,6,1,1,black,grey)}
\text{ligne=row(1,\graph)}
\integer{x0=item(1,\ligne)}
\integer{y0=item(2,\ligne)}
\text{ligne=row(2,\graph)}
\real{ex=item(1,\ligne)}
\real{ey=item(2,\ligne)}
\text{repere=wims(line 3 to -1 of \graph)}
\text{repere=\repere
text black,\x0-10,\y0+4,small,O
text black,\x0+\ex-4,\y0+4,small,I
text black,\x0-12,\y0+\ey-4,small,J}

\integer{Ax=\x0+(\ex)*(\xa)}
\integer{Ay=\y0+(\ey)*(\ya)}
#if defined TARGET_coordpt
\title{Placer un point}
\text{dessin1=draw(\xrange,\yrange,
\repere)}

%%%% MB pour solution %%%%%
\text{dessincorr=\xrange,\yrange,
\repere
crosshairsize 5
linewidth 2
crosshair \Ax,\Ay,green}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\statement{
  Le plan est muni d'un repère orthonormal \((O,I,J)).
  Cliquez dans le repère pour placer le point de coordonnées \((\xa;\ya)).
<hr class="wimscenter" style="width:50%">
<span class="ans">Votre réponse</span>:
<div class="wimscenter">\embed{r1}</div>}

\answer{Point \(\A)}{\dessin1;point,\Ax,\Ay}{type=coord}

%%%% MB %%%%%
\solution{Ci-dessous la bonne réponse :
<div class="wimscenter">
\draw{\xrange,\yrange}{\dessincorr}
</div>}
#endif
#if defined TARGET_ptcoord
\title{Lire les coordonnées d'un point}
\text{dessin2=\repere
linewidth 1
segment \Ax-4,\Ay+4,\Ax+4,\Ay-4,red
segment \Ax-4,\Ay-4,\Ax+4,\Ay+4,red
text red,\Ax-10,\Ay+4,medium,\A}

\statement{
Le plan est muni d'un repère orthonormal \((O,I,J)).
Quelles sont les coordonnées du point \(\A) ci-dessous ?
<div class="wimscenter">
\draw{\xrange,\yrange}{\dessin2}
</div>
<hr class="wimscenter" style="width:50%">
<span class="ans">Votre réponse</span>:
<br>
<label for="reply1">\(\A) a pour coordonnées</label> (\embed{r1,3} ; \embed{r2,3}).}

\answer{Abscisse de \(\A)}{\xa}{type=numexp}
\answer{Ordonnée de \(\A)}{\ya}{type=numexp}
#endif
