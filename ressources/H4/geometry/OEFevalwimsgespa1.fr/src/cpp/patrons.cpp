target=patrons1 patrons2 patrons3 patrons4 patrons5
#include "author.inc"
#include "lang_titles.inc"
#if defined TARGET_patrons1
\text{data=D,C,G,H,A,B,F,E
A,B,F,E,D,C,G,H
H,G,C,D,E,F,B,A
E,F,B,A,H,G,C,D
D,H,G,C,A,E,F,B
H,D,C,G,E,A,B,F
H,G,C,D,E,F,B,A
A,E,F,B,D,H,G,C
}
\text{cedata=randomrow(\data)}
\text{dataori=A,B,C,D,E,F,G,H}
\text{lstpt1=\cedata[2],\cedata[3],\cedata[5],\cedata[7]}
\text{lstpt2=T,U,V,W}
%%%%% dessin de l'objet
\text{cube=linewidth 3
polyline black,0,0,0,10,10,10,10,0,0,0
polyline black,0,10,2,13,12,13,10,10
dpolyline black,0,0,2,3,12,3
dsegment 2,3,2,13,black
polyline black,10,0,12,3,12,13
polyline red,0,-15,0,-5,10,-5,10,-15,0,-15
polyline red,0,-5,2,-2,12,-2,10,-5
dpolyline red,0,-15,2,-12,12,-12
dsegment 2,-12,2,-2,red
polyline red,10,-15,12,-12,12,-2
}

\text{cadre=
xrange -5,15
yrange -20,15
\cube
text black,-0.4,-0.5,medium,A
text black,10.1,-0.5,medium,B
text black,2.6,3,medium,D
text black,12.1,3,medium,C
text black,-1,11,medium,E
text black,10.7,10.8,medium,F
text black,2.6,14.2,medium,H
text black,12.1,14.2,medium,G
text black,-0.4,-15.5,medium,\cedata[1]
text black,10.1,-15.5,medium,T
text black,2.6,-12,medium,\cedata[4]
text black,12.1,-12,medium,U
text black,-1,-4,medium,V
text black,10.7,-4.2,medium,\cedata[6]
text black,2.6,-0.8,medium,\cedata[8]
text black,12.1,-0.8,medium,W
linewidth 5
points blue,0,0,0,10,10,10,10,0,2,13,12,13,2,3,12,3
points blue,0,-15,0,-5,10,-5,10,-15,2,-2,12,-2,2,-12,12,-12
linewidth 3
\dessin
}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{400,600}{\cadre}</div>
 <div class="medium_size text_col">
 On a représenté un cube vu de face, ainsi qu'une autre vue du même cube.
<p>
  Indiquer la correspondance des sommets entre les deux vues :
</p>
<div class="wimscenter">
\embed{reply1}
</div>
 </div>
 </div>
}
\answer{correspondance}{\lstpt1;\lstpt2}{type=correspond}
#endif
#if defined TARGET_patrons2
\text{data=(segment 0,5,5,0,red),(segment 10,5,15,0,red),2
(segment 0,5,5,0,red),(segment 10,0,15,5,red),1
(segment 0,5,5,0,red),(segment 15,5,20,0,red),2
(segment 0,5,5,0,red),(segment 15,0,20,5,red),2
(segment 5,5,10,0,red),(segment 15,5,20,0,red),2
(segment 5,5,10,0,red),(segment 15,0,20,5,red),1
(segment 5,10,10,5,red),(segment 10,5,15,0,red),2
}
\text{cedata=randomrow(\data)}
\text{ligne1=wims(declosing \cedata[1])}
\text{ligne2=wims(declosing \cedata[2])}
\integer{rep=\cedata[3]}

\text{cadre=xrange -10,25
yrange -10,25
linewidth 2
poly blue,0,0,20,0,20,5,0,5
poly blue,5,10,10,10,10,-5,5,-5
segment 15,0,15,5,blue
\ligne1
\ligne2
}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{400,400}{\cadre}</div>
 <div class="medium_size text_col">
  On a représenté un patron de cube sur lequel on a dessiné deux droites en rouge.
<p>
  Une fois le cube refermé, ces droites sont-elles parallèles?
</p><div>\embed{reply1}</div>
</div>
</div>
}
\answer{paralèles dans le cube}{\rep;Oui,Non}{type=radio}
#endif
#if defined TARGET_patrons3
\text{cube=linewidth 3
polyline black,0,0,0,10,10,10,10,0,0,0
polyline black,0,10,2,13,12,13,10,10
polyline black,10,0,12,3,12,13
polyline red,0,-15,0,-5,10,-5,10,-15,0,-15
polyline red,0,-5,2,-2,12,-2,10,-5
polyline red,10,-15,12,-12,12,-2
}
#include "patrons3.inc"

\text{clicList=\chiffreun,\chiffredeux,\chiffretrois,\chiffrequatre,\chiffrecinq,\chiffresix}
\text{cadre=
xrange -5,15
yrange -20,15
\cube
fcircle 5,5,8,red
fcircle 3,12,8,red
fcircle 8,11,8,red
fcircle 10.8,2.5,8,red
fcircle 11.3,6.5,8,red
fcircle 11.6,10.5,8,red
\cote
\dessus
linewidth 5
}
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{200,400}{\cadre}</div>
 <div class="medium_size text_col">
  Choisissez le dessin apparaissant sur la face de devant, sachant que les deux dessins
  sont des vues différentes du même dé, et que la somme des chiffres marqués
  sur des faces parallèles est 7.
<div>
\embed{reply1,60x60x1}
</div>
 </div>
</div>
}
\answer{dessin}{\chiffre;\clicList}{type=clickfill}
#endif
#if defined TARGET_patrons4
#include "patrons4.inc"
\text{cadreini=
xrange -10,50
yrange -20,30
linewidth 2
poly blue,0,0,40,0,40,10,0,10
poly blue,10,20,20,20,20,-10,10,-10
segment 30,0,30,10,blue
\faceun
\facedeux
\facetrois
\facequatre
\facecinq
\facesix
}
\text{graphList=\graph1,\graph2,\graph3,\graph4}
\text{lstrep1=\graph1,\graph3}
\text{lstrep2=\graph3,\graph1}
\statement{
Choisissez les cubes pouvant correspondre au patron ci-dessous.
<div class="wimscenter">\draw{300,250}{\cadreini}</div>
<div class="wimscenter">\embed{reply1,100x100x2}</div>
}
%%%%% soumission de réponse %%%%%
\answer{}{\lstrep;\graphList}{type=clickfill}
\condition{}{\lstrep issametext\lstrep1 or \lstrep issametext \lstrep2}
\solution{\lstrep1<p>
\lstrep2}
#endif
#if defined TARGET_patrons5
%%%%% dessin de l'objet
\text{cube=linewidth 3
polyline black,0,0,0,10,10,10,10,0,0,0
polyline black,0,10,2,13,12,13,10,10
polyline black,10,0,12,3,12,13
}

\text{cadre=
xrange -5,15
yrange -5,15
\cube
linewidth 2
poly blue,12,13,0,10,10,0
}
#include "patrons5.inc"
\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{200,200}{\cadre}</div>
 <div class="medium_size text_col">
  On a tracé une diagonale sur trois faces d'un cube. Puis on a développé
   le patron du cube, mais il y manque une diagonale.
<div class="wimscenter">\draw{350,250}{\patron}</div>
  Nommer la diagonale manquante.
<div class="wimscenter">
  diagonale : \embed{reply1,3}
  </div>
</div>
</div>
<div class="wims_instruction">
 On respectera l'ordre alphabétique des lettres, par exemple (AE).</div>
}
\answer{diagonale manquante}{\rep}{type=raw}{option=nocase}
#endif
