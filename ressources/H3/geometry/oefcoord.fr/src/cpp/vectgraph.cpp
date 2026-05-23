target=vectgraph
\title{Représenter un vecteur}
\language{fr}
\keywords{vectors}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "css.inc"

\integer{xrange=400}
\integer{yrange=400}

\matrix{listlet=A,B
C,D
E,F
G,H}

\text{list=randrow(\listlet)}
\text{list=shuffle(\list)}
\text{A=item(1,\list)}
\text{B=item(2,\list)}
\text{u=randitem(u,v,w)}

\integer{xu=random(1,-1)*random(2..4)}
\integer{yu=random(1,-1)*random(2..4)}

\integer{xa=random(-2..2)}
\integer{ya=random(-2..2)}
\integer{xb=\xa+(\xu)}
\integer{yb=\ya+(\yu)}

\text{graph=slib(draw/repere \xrange,\yrange,20,-7,7,-7,7,1,1,black,grey)}
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


\integer{Ax=\ex*(\xa)+(\x0)}
\integer{Ay=\ey*(\ya)+(\y0)}
\integer{Bx=\ex*(\xb)+(\x0)}
\integer{By=\ey*(\yb)+(\y0)}

\text{color=red}
\matrix{don=\A,\B,\Ax,\Ay,\Bx,\By
\B,\A,\Bx,\By,\Ax,\Ay}
\text{don=randrow(\don)}
\text{pt1=item(1,\don)}
\text{pt2=item(2,\don)}
\integer{X1=item(3,\don)}
\integer{Y1=item(4,\don)}
\integer{X2=item(5,\don)}
\integer{Y2=item(6,\don)}

\text{dessin1=\repere
fcircle \X1,\Y1,4,\color
text \color,\X1+4,\Y1+4,medium,\pt1}
\text{dessin1=draw(\xrange,\yrange,
\dessin1)}


\statement{<p>
Le plan est muni d'un repère orthonormé \((O,I,J)).<br>
Le vecteur \(\overrightarrow{\u}) a pour coordonnées \((\xu ; \yu)).
En cliquant sur la figure, placer le point \(\pt2) vérifiant
\(\overrightarrow{\u} = \overrightarrow{\A \B}).</p>
<div class="wimscenter">
\embed{r1}
</div>
}

\answer{Point \(\pt2)}{\dessin1;circle,\X2,\Y2,\ex/2}{type=coord}
