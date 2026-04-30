target=reperpt1 reperpt2 reperpt3 reperpt4 reperpt5
\language{fr}
\range{-5..5}
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{no}
\format{html}
\precision{100}
#define TITLE Repérage simple d'un point

#if defined TARGET_reperpt1
 \title{TITLE I}
 \integer{choix=1}
#endif
#if defined TARGET_reperpt2
 \title{TITLE II}
 \integer{choix=2}
#endif
#if defined TARGET_reperpt3
 \title{TITLE III}
 \integer{choix=1}
#endif
#if defined TARGET_reperpt4
 \title{TITLE IV}
 \integer{choix=2}
#endif
#if defined TARGET_reperpt5
 \title{TITLE V}
\integer{choix=random(1,2)}
#endif

#if (defined TARGET_reperpt1 || defined TARGET_reperpt2)
\integer{b=random(1..5)}

\rational{c=\choix=1?random(-1,-2,2):random(-1,-2,-3,2,3)/\b}
On ne veut pas c=1
\rational{c=\c=1?2}
\text{tc=\c}
\text{tc=wims(replace internal / by , in \tc)}
\text{tc=items(\tc)>1?\frac{\tc[1]}{\tc[2]}}
\text{tc=\tc=1? }
\text{tc=\tc=-1?-}
\rational{ca=1-\c}


\integer{fx=\c*(\b)}
\integer{fy=0}
\integer{Ox=403}
\integer{ex=31}
\integer{\fxx=\Ox+\ex*\fx}
\integer{\fxxm=\fxx-0.3*\ex}
\integer{\fxxp=\fxx+0.3*\ex}
\text{image= draw(806,64
  xrange -13,13
  yrange -1,3
  hline 0,0,red
  parallel -12,-0.2,-12,0.2,1,0,2,blue
  parallel -10,-0.4,-10,0.4,5,0,5,blue
  parallel -9,-0.2,-9,0.2,1,0,4,blue
  parallel -4,-0.2,-4,0.2,1,0,4,blue
  parallel 1,-0.2,1,0.2,1,0,4,blue
  parallel 6,-0.2,6,0.2,1,0,4,blue
  parallel 11,-0.2,11,0.2,1,0,2,blue
  text red,-0.1,1.5,medium,A
  text red,\b-0.1,1.5,medium,B
  segment 0,-0.2,\a,0.2,red
  segment \b,-0.2,\b,0.2,red)
  }
\text{repimage=xrange -13,13
  yrange -1,3
  hline 0,0,red
  parallel -12,-0.2,-12,0.2,1,0,2,blue
  parallel -10,-0.4,-10,0.4,5,0,5,blue
  parallel -9,-0.2,-9,0.2,1,0,4,blue
  parallel -4,-0.2,-4,0.2,1,0,4,blue
  parallel 1,-0.2,1,0.2,1,0,4,blue
  parallel 6,-0.2,6,0.2,1,0,4,blue
  parallel 11,-0.2,11,0.2,1,0,2,blue
  text red,-0.1,1.5,medium,A
  text red,\b-0.1,1.5,medium,B
  text red,\fx-0.1,-0.5,medium,M
  segment 0,-0.2,\a,0.2,red
  segment \b,-0.2,\b,0.2,red
  segment \fx,-0.2,\fx,0.2,red
  }
\text{relation=texmath(\ca*x+\c*y)}

\text{relation=wims(replace internal x by \overrightarrow{A M} in \relation)}
\text{relation=wims(replace internal y by \overrightarrow{B M} in \relation)}

\statement{
Placer le point \(M\) défini par:
<div class="wimscenter">
\(\overrightarrow{A M}=\tc \overrightarrow{A B})
</div>
<div class="wimscenter">
\embed{r1}
</div>
  Cliquer à l'emplacement du point \(M\).
 }

\answer{f(\X)}{\image;rectangle,\fxxm,0,\fxxp,64}{type=coord}
\solution{
<div class="wimscenter">
\draw{800,64}{\repimage}
</div>
}
#endif
#if (defined TARGET_reperpt3 || defined TARGET_reperpt4 || defined TARGET_reperpt5)
\text{donnees=slib(draw/repere 400,400,20,-6,6,-6,6,1,1,black,grey)}

\text{tmp=row(1,\donnees)}
%%coordonnées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}

\text{grille=wims(line 3 to -1 of \donnees)}
%%on a maintenant les axes non nommés et la grille

%%ensuite on place deux vecteurs (X,Y)
\integer{ax=\Ox+random(-2..3)*\ex}
\integer{bx=\ax+random(-2..2)*\ex}
\integer{cx=\Ox+random(-2..3)*\ex}
\integer{dx=\cx+random(-2..2)*\ex}
\integer{ay=\Oy+random(-2..3)*\ey}
\integer{by=\ay+random(-2..2)*\ey}
\integer{cy=\Oy+random(-2..3)*\ey}
\integer{dy=\cy+random(-2..2)*\ey}
\integer{mx=\Ox+random(-2..3)*\ex}
\integer{nx=\mx+random(-2..2)*\ex}
\integer{my=\Oy+random(-2..3)*\ey}
\integer{ny=\my+random(-2..2)*\ey}

controle des vecteurs
\integer{ay=(\by-\ay=0) and \ay=\Oy?\ay+2*\ey:\ay}
\integer{ax=(\bx-\ax=0) and \ax=\Ox?\ax+2*\ex:\ax}
\integer{ax=(\ax=\bx) and (\ay=\by)?\ax+\ex:\ax}
\integer{cy=(\dy-\cy=0) and \cy=\Oy?\cy+2*\ey:\cy}
\integer{cx=(\dx-\cx=0) and \cx=\Ox?\cx+2*\ex:\cx}
\integer{cx=(\cx=\dx) and (\cy=\dy)?\cx+\ex:\cx}

\integer{my=(\ny-\my=0) and \my=\Oy?\my-2*\ey:\my}
\integer{mx=(\nx-\mx=0) and \mx=\Ox?\mx-2*\ex:\mx}
\integer{mx=(\mx=\nx) and (\my=\ny)?\mx-\ex:\mx}


\text{vecAB=arrow \ax,\ay,\bx,\by,10,orange}
\text{vecCD=arrow \cx,\cy,\dx,\dy,10,blue}
\text{vecEF=arrow \mx,\my,\nx,\ny,10,purple}

calcul des pentes des vecteurs pour affichage des lettres
\integer{offax=\bx-\ax>=0?-10:10}
\integer{offay=\by-\ay>=0?-5:5}
\integer{offbx=\bx-\ax>=0?10:-10 }
\integer{offby=\by-\ay>=0?5:-5}
\integer{offcx=\dx-\cx>=0?-10:10}
\integer{offcy=\dy-\cy>=0?-5:5}
\integer{offdx=\dx-\cx>=0?10:-10 }
\integer{offdy=\dy-\cy>=0?5:-5}

\integer{offmx=\nx-\mx>=0?-10:10}
\integer{offmy=\ny-\my>=0?-5:5}
\integer{offnx=\nx-\mx>=0?10:-10 }
\integer{offny=\ny-\my>=0?5:-5}

#if defined TARGET_reperpt3
\rational{c1=1}
\rational{c2=1}
\rational{c3=0}
calcul des coordonnées de M
\integer{fx=\Ox+(\bx-\ax)+(\dx-\cx)}
\integer{fy=\Oy+(\by-\ay)+(\dy-\cy)}
\text{lineEF=}
\text{vecteurs=\(\overrightarrow{A B}+\overrightarrow{C D})}
#endif
#if defined TARGET_reperpt4
\rational{c1=random(-2,-1,-1/2,1/2,1,2)}
\rational{c2=random(-2,-1,-1/2,1/2,1,2)}
\rational{c3=0}

calcul des coordonnées de M
\integer{fx=\Ox+\c1*(\bx-\ax)+\c2*(\dx-\cx)}
\integer{fy=\Oy+\c1*(\by-\ay)+\c2*(\dy-\cy)}
test pour l'affichage de la combinaison
\if{\fx>800 or \fx<-400 or \fy>800 or \fy<-400}{\real{c1=\c1/4}
\real{c2=\c2/4}
\integer{fx=\Ox+\c1*(\bx-\ax)+\c2*(\dx-\cx)}
\integer{fy=\Oy+\c1*(\by-\ay)+\c2*(\dy-\cy)}
}
\if{\fx>400 or \fx<0 or \fy>400 or \fy<0}{\real{c1=\c1/2}
\real{c2=\c2/2}
\integer{fx=\Ox+\c1*(\bx-\ax)+\c2*(\dx-\cx)}
\integer{fy=\Oy+\c1*(\by-\ay)+\c2*(\dy-\cy)}
}
\text{lineEF=}
\text{vecteurs=\(\c1\overrightarrow{A B}\c2\overrightarrow{C D})}
#endif
#if defined TARGET_reperpt5
\rational{c1=random(-2,-1,-1/2,1/2,1,2)}
\rational{c2=random(-2,-1,-1/2,1/2,1,2)}
\rational{c3=random(-2,-1,-1/2,1/2,1,2)}
calcul des coordonnées de M
\integer{fx=\Ox+\c1*(\bx-\ax)+\c2*(\dx-\cx)+\c3*(\nx-\mx)}
\integer{fy=\Oy+\c1*(\by-\ay)+\c2*(\dy-\cy)+\c3*(\ny-\my)}

test pour l'affichage de la combinaison
\if{\fx>800 or \fx<-400 or \fy>800 or \fy<-400}
{
\rational{c1=\c1/4}
\rational{c2=\c2/4}
\rational{c3=\c3/4}
\integer{fx=\Ox+\c1*(\bx-\ax)+\c2*(\dx-\cx)+\c3*(\nx-\mx)}
\integer{fy=\Oy+\c1*(\by-\ay)+\c2*(\dy-\cy)+\c3*(\ny-\my)}
}
\if{\fx>400 or \fx<0 or \fy>400 or \fy<0}
{
\rational{c1=\c1/2}
\rational{c2=\c2/2}
\rational{c3=\c3/2}
\integer{fx=\Ox+\c1*(\bx-\ax)+\c2*(\dx-\cx)+\c3*(\nx-\mx)}
\integer{fy=\Oy+\c1*(\by-\ay)+\c2*(\dy-\cy)+\c3*(\ny-\my)}
}
\text{lineEF=\vecEF
text blue,\mx+\offmx,\my+\offmy,medium,E
text blue,\nx+\offnx,\ny+\offny,medium,F
}
#endif

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
text blue,\dx+\offdx,\dy+\offdy,medium,D
\lineEF)}

réaffichage du dessin
#if defined TARGET_reperpt3
\text{vecABtr=}
\text{vecCDtr=dasharrow \ax+(\c1)*(\bx-\ax),\ay+(\c1)*(\by-\ay),\ax+(\c1)*(\bx-\ax)+(\c2)*(\dx-\cx),\ay+(\c1)*(\by-\ay)+(\c2)*(\dy-\cy),10,blue}
\text{vecEFtr=}
\text{vecOMtr=dasharrow \ax,\ay,\ax+(\c1)*(\bx-\ax)+(\c2)*(\dx-\cx)+(\c3)*(\nx-\mx),\ay+(\c1)*(\by-\ay)+(\c2)*(\dy-\cy)+(\c3)*(\ny-\my),10,green}
#endif
#if defined TARGET_reperpt4
\text{vecABtr=dasharrow \Ox,\Oy,\Ox+(\c1)*(\bx-\ax),\Oy+(\c1)*(\by-\ay),10,blue}
\text{vecCDtr=dasharrow \Ox+(\c1)*(\bx-\ax),\Oy+(\c1)*(\by-\ay),\Ox+(\c1)*(\bx-\ax)+(\c2)*(\dx-\cx),\Oy+(\c1)*(\by-\ay)+(\c2)*(\dy-\cy),10,blue}
\text{vecEFtr=}
\text{vecOMtr=}
#endif
#if defined TARGET_reperpt5
\text{vecABtr=dasharrow \Ox,\Oy,\Ox+(\c1)*(\bx-\ax),\Oy+(\c1)*(\by-\ay),10,blue}
\text{vecCDtr=dasharrow \Ox+(\c1)*(\bx-\ax),\Oy+(\c1)*(\by-\ay),\Ox+(\c1)*(\bx-\ax)+(\c2)*(\dx-\cx),\Oy+(\c1)*(\by-\ay)+(\c2)*(\dy-\cy),10,blue}
\text{vecEFtr=dasharrow \Ox+(\c1)*(\bx-\ax)+(\c2)*(\dx-\cx),\Oy+(\c1)*(\by-\ay)+(\c2)*(\dy-\cy),\Ox+(\c1)*(\bx-\ax)+(\c2)*(\dx-\cx)+(\c3)*(\nx-\mx),\Oy+(\c1)*(\by-\ay)+(\c2)*(\dy-\cy)+(\c3)*(\ny-\my),10,blue}
\text{vecOMtr=dasharrow \Ox,\Oy,\Ox+(\c1)*(\bx-\ax)+(\c2)*(\dx-\cx)+(\c3)*(\nx-\mx),\Oy+(\c1)*(\by-\ay)+(\c2)*(\dy-\cy)+(\c3)*(\ny-\my),10,green}
#endif
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
\lineEF
\vecABtr
\vecCDtr
\vecEFtr
\vecOMtr
arrow \Ox,\Oy,\fx,\fy,10,green}

\text{s1=\c1>0?:-}
\rational{c1=\c1<0?\c1*(-1)}
\text{tc1=\c1}
\text{tc1=wims(replace internal / by , in \tc1)}
\text{tc1=items(\tc1)=1?\tc1:\frac{\tc1[1]}{\tc1[2]}}
\text{tc1=\tc1=1?\s1:\s1 \tc1}

\text{s2=\c2>0?+:-}
\rational{c2=\c2<0?\c2*(-1)}
\text{tc2=\c2}
\text{tc2=wims(replace internal / by , in \tc2)}
\text{tc2=items(\tc2)=1?\tc2:\frac{\tc2[1]}{\tc2[2]}}
\text{tc2=\tc2=1?\s2:\s2 \tc2}

\text{s3=\c3>0?+:-}
\rational{c3=\c3<0?\c3*(-1)}
\text{tc3=\c3}
\text{tc3=wims(replace internal / by , in \tc3)}
\text{tc3=items(\tc3)=1?\tc3:\frac{\tc3[1]}{\tc3[2]}}
\text{tc3=\tc3=1?\s3:\s3 \tc3}


#if defined TARGET_reperpt3
\text{vecteurs=\overrightarrow{A B}+\overrightarrow{C D}}
#endif
#if defined TARGET_reperpt4
\text{vecteurs=\tc1\overrightarrow{A B}\tc2\overrightarrow{C D}}
#endif
#if defined TARGET_reperpt5
\text{vecteurs=\tc1\overrightarrow{A B}\tc2\overrightarrow{C D}\tc3\overrightarrow{E F}}
#endif
\statement{
  Le but de l'exercice est de construire un représentant d'origine \(O\)
  du vecteur \(\vecteurs). Cliquer à l'emplacement de l'extrémité \(M\) du vecteur
  \(\overrightarrow{O M}=\vecteurs).
<div class="wimscenter">
\embed{r1}
</div>

}
\answer{f(\X)}{\image;circle,\fx,\fy,\ex/3}{type=coord}
#if defined TARGET_reperpt3
\solution{On commence par construire le représentant du vecteur \(\overrightarrow{C D}) d'origine \(B\) (en pointillé bleu).
<br>
  On en déduit le représentant du vecteur \(\overrightarrow{O M}) d'origine \(A\) (en pointillé vert).
<br> Enfin on construit le vecteur \(\overrightarrow{O M}) (en vert). <div class="wimscenter">
\draw{400,400}{\repimage}
</div>
  Les coordonnées de \(M\) sont (\fxx;\fyy)}
#endif
#if (defined TARGET_reperpt4 || defined TARGET_reperpt5)
\solution{
\draw{400,400}{\repimage}
}
#endif
#endif
