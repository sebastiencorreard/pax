target=somvect
\title{Somme de deux vecteurs}
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
\keywords{vectors}
\text{donnees=slib(draw/repere 400,400,20,-6,6,-6,6,1,1,black,grey)}

\text{tmp=row(1,\donnees)}
#coordonnées de l'origine du repée
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
#éhelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}

\text{grille=wims(line 3 to -1 of \donnees)}
#on a maintenant les axes non nommé et la grille
#pour placer l'origine, il faut érire du texte
\integer{X=random(-1,1)*random(1..5)}
\integer{Y=random(-1,1)*random(1..5)}
#on ne veut pas X=0

#ensuite on place deux vecteurs (X,Y)
\integer{ax=\Ox+random(-2..3)*\ex}
\integer{bx=\ax+random(-2..2)*\ex}
\integer{cx=\Ox+random(-2..3)*\ex}
\integer{dx=\cx+random(-2..2)*\ex}
\integer{ay=\Oy+random(-2..3)*\ey}
\integer{by=\ay+random(-2..2)*\ey}
\integer{cy=\Oy+random(-2..3)*\ey}
\integer{dy=\cy+random(-2..2)*\ey}

controle des vecteurs
\integer{ay=(\by-\ay=0) and \ay=\Oy?\ay+2*\ey:\ay}
\integer{ax=(\bx-\ax=0) and \ax=\Ox?\ax+2*\ex:\ax}
\integer{ax=(\ax=\bx) and (\ay=\by)?2*\Ox-\ax:\ax}
\integer{cy=(\dy-\cy=0) and \cy=\Oy?\cy+2*\ey:\cy}
\integer{cx=(\dx-\cx=0) and \cx=\Ox?\cx+2*\ex:\cx}
\integer{cx=(\cx=\dx) and (\cy=\dy)?2*\Ox-\cx:\cx}



\text{vecAB=arrow \ax,\ay,\bx,\by,10,orange}
\text{vecCD=arrow \cx,\cy,\dx,\dy,10,blue}

calcul des pentes des vecteurs pour affichage des lettres
\integer{offax=\bx-\ax>=0?-10:10}
\integer{offay=\by-\ay>=0?-5:5}
\integer{offbx=\bx-\ax>=0?10:-10 }
\integer{offby=\by-\ay>=0?5:-5}
\integer{offcx=\dx-\cx>=0?-10:10}
\integer{offcy=\dy-\cy>=0?-5:5}
\integer{offdx=\dx-\cx>=0?10:-10 }
\integer{offdy=\dy-\cy>=0?5:-5}

calcul des coordonnés de M
\integer{fx=\Ox+(\bx-\ax)+(\dx-\cx)}
\integer{fy=\Oy+(\by-\ay)+(\dy-\cy)}

\function{trx=(x-(\Ox))/\ex}
\function{try=(y-(\Oy))/\ey}
\text{fxx=simplify(evalue(\trx,x=\fx))}
\text{fyy=simplify(evalue(\try,y=\fy))}

affichage du dessin
\text{image=draw(400,400
\grille
text black,\Ox-10,\Oy+5,medium,O
text black,390,205,medium,x
text black,185,5,medium,y
linewidth 2
arrow \Ox,\Oy,\Ox+\ex,\Oy,10,red
arrow \Ox,\Oy,\Ox,\Oy+\ey,10,red
\vecAB
text orange,\ax+\offax,\ay+\offay,medium,A
text orange,\bx+\offbx,\by+\offby,medium,B
\vecCD
text blue,\cx+\offcx,\cy+\offcy,medium,C
text blue,\dx+\offdx,\dy+\offdy,medium,D)}

réffichage du dessin
\text{vecCDtr=dasharrow \bx,\by,\bx+\dx-\cx,\by+\dy-\cy,10,blue}
\text{vecOMtr=dasharrow \ax,\ay,\bx+\dx-\cx,\by+\dy-\cy,10,green}
\text{repimage=\grille
text black,\Ox-10,\Oy+5,medium,O
text black,390,205,medium,x
text black,185,5,medium,y
linewidth 2
arrow \Ox,\Oy,\Ox+\ex,\Oy,10,red
arrow \Ox,\Oy,\Ox,\Oy+\ey,10,red
\vecAB
text orange,\ax+\offax,\ay+\offay,medium,A
text orange,\bx+\offbx,\by+\offby,medium,B
\vecCD
text blue,\cx+\offcx,\cy+\offcy,medium,C
text blue,\dx+\offdx,\dy+\offdy,medium,D
\vecCDtr
\vecOMtr
arrow \Ox,\Oy,\fx,\fy,10,green}

\statement{Le but de l'exercice est de construire l'extrémité \(M\) du représentant
\(\overrightarrow{O M}\)
d'origine \(0\) du vecteur
\(\overrightarrow{A B}+\overrightarrow{C D}\).
<br> Placer \(M\) en cliquant sur la figure.
<div class="wimscenter">
\embed{r1}
</div>
}

\answer{f(\X)}{\image;circle,\fx,\fy,\ex/3}{type=coord}

\solution{On commence par construire le représentant du vecteur
\(\overrightarrow{C D}) d'origine \(B\) (en pointillé bleu).
<br>
On en déduit le représentant du vecteur \(\overrightarrow{O M}) d'origine A
(en pointillé vert).
<br> Enfin on construit le vecteur \(\overrightarrow{O M}) (en vert).
<div class="wimscenter">
\draw{400,400}{\repimage}
</div>
Les coordonnées de \(M\) sont (\fxx;\fyy)}
