target=repgraph1 repgraph2 repgraph3 repgraph4 repgraph5
\precision{100}
\computanswer{no}

#if defined TARGET_repgraph1
\title{ Représentation graphique 1}
\integer{typerep=random(1..3)}
\integer{typerep=3}
#endif
#if defined TARGET_repgraph2
\title{ Représentation graphique 2}
\integer{typerep=1}
\text{typequest=fréquences (en pourcentage)}
#endif
#if defined TARGET_repgraph3
\title{ Représentation graphique 3}
\integer{typerep=2}
\text{typequest=effectifs}
#endif
#if defined TARGET_repgraph4
\title{ Représentation graphique 4}
\integer{typerep=3}
\text{typequest=effectifs}
#endif
#if defined TARGET_repgraph5
\title{ Représentation graphique 5}
\integer{typerep=3}
\text{typequest=effectifs}
#endif

\integer{range=random(20..100)}
\integer{xmin=random(0..50)}
\integer{parite=random(1,2)}
\integer{parite=2}
\integer{nbval=2*randint(3,4)+\parite}
#if defined TARGET_repgraph4
\integer{nbval=4}
#endif
\text{listval=}
\if{\typerep=3}
{
 \integer{val=\xmin}
 \integer{efftotal=0}
 \text{xlistval=}
 \text{lsteff=}
 \text{lsth=}
 \text{xlistval=wims(append item \val to \xlistval)}
 \for{i=1 to \nbval}
 {
  \integer{largeur=random(1,2,4)}
  \integer{val = \val+\largeur*10}
  \text{xlistval=wims(append item \val to \xlistval)}
  \integer{eff=random(0..20)}
  \integer{efftotal=\efftotal+\eff}
  \text{lsteff=wims(append item \eff to \lsteff)}
  \real{high=\eff / \largeur}
  \text{lsth=wims(append item \high to \lsth)}
 }
\text{slsth=wims(sort numeric list \lsth)}
\integer{effmax=\slsth[\nbval]}

}
{
\for{i=1 to \nbval+1}
 {
 \integer{val=random(\xmin..\xmin+\range)}
 \text{listval=wims(append item \val to \listval)}
 }
\text{xlistval=wims(sort numeric list \listval)}
\text{xlistval=wims(listuniq \xlistval)}
\integer{nbval=items(\xlistval)-1}

 ## génération des effectifs
\text{lsteff=}
\integer{efftotal=0}
\for{i=1 to \nbval}
  {
   \integer{eff=random(0..20)}
   \integer{efftotal=\efftotal+\eff}
   \text{lsteff=wims(append item \eff to \lsteff)}
  }
\text{slsteff=wims(sort numeric list \lsteff)}
\integer{effmax=\slsteff[\nbval]}

}

\integer{xmin=\xlistval[1]}
\integer{xmax=\xlistval[\nbval+1]}
\integer{ecc=0}
\integer{ecd=\efftotal}
\text{lstecc=}
\text{lstecd=}
\text{lstecd=wims(append item \ecd to \lstecd)}
\text{lstfreq=}
\for{i=1 to \nbval}
 {
 \integer{ecc=\ecc+\lsteff[\i]}
 \integer{ecd=\ecd-\lsteff[\i]}
 \text{lstecc=wims(append item \ecc to \lstecc)}
 \text{lstecd=wims(append item \ecd to \lstecd)}
 \integer{freq=\lsteff[\i]* 1000 / \efftotal}
 \real{freq=\freq / 10}
 \text{lstfreq= wims(append item \freq to \lstfreq)}
}

\text{mstep=wims(makelist r x for x=1 to \nbval)}
\text{mstep=wims(nospace \mstep)}
\text{lstrep=Diagramme circulaire, Diagramme en bâtons, Histogramme}

#if defined TARGET_repgraph2
\steps{\mstep}
\text{lstval=\lstfreq}
#endif

#if defined TARGET_repgraph3
\steps{\mstep}
\text{lstval=\lsteff}
#endif

#if defined TARGET_repgraph4
\steps{\mstep}
\text{lstval=\lsteff}
#endif

#if defined TARGET_repgraph5
\steps{\mstep}
\text{lstval=\lsth}
#endif

## préparation du dessin
\if{\typerep=1}
{
\text{listecouleur=red,skyblue,orange,grey,green,purple,pink,magenta,yellow,cyan}
\text{listecouleurf=rouge,bleu ciel,orange,gris,vert,violet,rose,magenta,jaune,cyan}
\text{image=
xrange -1.5,1.5
yrange -1.5,1.5
ellipse 0,0,2,2,black
segment 0,0,1,0,black
  }
\text{anglet=0}
\text{lstangle=}
\for{i=1 to \nbval}
   {
   \real{angle=\lstfreq[\i]*2*pi/100}
  \real{point=\anglet+\angle/2}
  \text{couleur=\listecouleur[\i]}
  \real{anglet=\anglet+\angle}
  \text{lstangle=wims(append item \anglet to \lstangle)}
  \text{image=\image
  segment 0,0,cos(\anglet),sin(\anglet),black
  fill  cos(\point)/2,sin(\point)/2, \couleur
  text \couleur,  1.2*cos(\point),1.2*sin(\point),medium, \lstfreq[\i]%}
 }
}
## diagramme en batons
\if{\typerep=2}
{
\text{image=
 xrange \xmin-15,\xmax+5
 yrange -10,\effmax+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\effmax+5,10,black
 segment \xlistval[1],0,\xlistval[1],\lsteff[1],blue
dsegment \xmin-5,\lsteff[1],\xlistval[1],\lsteff[1],orange
text black,\xlistval[1],-5,medium,\xlistval[1]
text black,\xmin-12,\lsteff[1],medium,\lsteff[1]
}
\integer{xoff=12}
\integer{yoff=3}
\for{i=2 to \nbval}
 {
 \integer{xoff=\xoff=12?7:12}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 segment \xlistval[\i],0,\xlistval[\i],\lsteff[\i],blue
 dsegment \xmin-5,\lsteff[\i],\xlistval[\i],\lsteff[\i],orange
 text black,\xlistval[\i],-\yoff,medium,\xlistval[\i]
 text black,\xmin-\xoff,\lsteff[\i],medium,\lsteff[\i]
 }
 }
}
## histogramme
\if{\typerep=3}
{
\real{xoff1=(\xmax-\xmin)/5}
\text{image=
 xrange \xmin-\xoff1,\xmax+5
 yrange -10,\effmax+5
 arrow \xmin-5,0,\xmax+5,0,10,black
 arrow \xmin-5,-5,\xmin-5,\effmax+5,10,black
 polyline blue,\xlistval[1],0,\xlistval[1],\lsth[1],\xlistval[2],\lsth[1],\xlistval[2],0
dsegment \xmin-5,\lsth[1],\xlistval[1],\lsth[1],orange
text black,\xlistval[1],-5,medium,\xlistval[1]
text black,\xmin-\xoff1,\lsth[1],medium,\lsth[1]
}
\integer{yoff=3}
\for{i=2 to \nbval}
 {
 \real{xoff=\xoff=\xoff1?\xoff1/2:\xoff1}
 \integer{yoff=\yoff=3?5:3}
 \text{image=\image
 polyline blue,\xlistval[\i],0,\xlistval[\i],\lsth[\i],\xlistval[\i+1],\lsth[\i],\xlistval[\i+1],0
 dsegment \xmin-5,\lsth[\i],\xlistval[\i],\lsth[\i],orange
 text black,\xlistval[\i],-\yoff,medium,\xlistval[\i]
 text black,\xmin-\xoff,\lsth[\i],medium,\lsth[\i]
 }
 }
}
#if (defined TARGET_repgraph2  || defined TARGET_repgraph3  || defined TARGET_repgraph4 )
\text{nomgraph=\lstrep[\typerep]}
\statement{
<div class="float_left">\draw{400,400}{\image}</div>
On a représenté le \nomgraph d'une série statistique d'effectif total \efftotal:
#if defined TARGET_repgraph2
<table class="wimscenter wimsborder"><tr><th>Couleur</th><th>Classe</th><th>Fréquences</th></tr>
\for{kk=1 to \nbval}
 {
<tr><td>\listecouleurf[\kk]</td><td>&#91; \xlistval[\kk]; \xlistval[\kk+1] &#91;</td>
<td>\embed{reply\kk,4}</td></tr>
 }
</table>
#endif
#if defined TARGET_repgraph3
<table class="wimscenter wimsborder"><tr><th>Valeurs</th><th>Effectifs</th></tr>
\for{kk=1 to \nbval}
 {
<tr><td> \xlistval[\kk]</td>
<td>\embed{reply\kk,4}</td></tr>
 }
</table>
#endif
#if defined TARGET_repgraph4
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Effectifs</th></tr>
\for{kk=1 to \nbval}
 {
<tr><td>&#91; \xlistval[\kk]; \xlistval[\kk+1] &#91;</td>
<td>\embed{reply\kk,4}</td></tr>
 }
</table>
#endif

<p>Remplir le tableau des \typequest de cette série:</p>
}
\answer{valeur 1}{\lstval[1]}{type=numeric}
\answer{valeur 2}{\lstval[2]}{type=numeric}
\answer{valeur 3}{\lstval[3]}{type=numeric}
\answer{valeur 4}{\lstval[4]}{type=numeric}
\answer{valeur 5}{\lstval[5]}{type=numeric}
\answer{valeur 6}{\lstval[6]}{type=numeric}
\answer{valeur 7}{\lstval[7]}{type=numeric}
\answer{valeur 8}{\lstval[8]}{type=numeric}
\answer{valeur 9}{\lstval[9]}{type=numeric}
\answer{valeur 10}{\lstval[10]}{type=numeric}
#endif

#if defined TARGET_repgraph5
\integer{ix1=randint(2..\nbval-1)}
\integer{x1=\xlistval[\ix1]}
\integer{ix2=randint(2..\nbval-1)}
\integer{x2=\xlistval[\ix2]}
\statement{
On considère la série statistique suivante représentant le nombre de livres lus par an dans une population:
<table class="wimscenter wimsborder"><tr><th>Classe</th><th>Effectif</th><th> Hauteur de colonne</th></tr>
\for{kk=1 to \nbval}
 {
<tr><td>&#91; \xlistval[\kk]; \xlistval[\kk+1] &#91;</td>
<td>\lsteff[\kk]</td>
    <td>\embed{reply\kk,4}</td>
</tr>

 }
</table>
<p>Remplir les hauteurs des colonnes correspondants à l'histogramme associé à la série statistique,
pour lequel un carré de 10 par 10 représente un effectif de 10:</p>
}
\answer{valeur 1}{\lsth[1]}{type=numeric}
\answer{valeur 2}{\lsth[2]}{type=numeric}
\answer{valeur 3}{\lsth[3]}{type=numeric}
\answer{valeur 4}{\lsth[4]}{type=numeric}
\answer{valeur 5}{\lsth[5]}{type=numeric}
\answer{valeur 6}{\lsth[6]}{type=numeric}
\answer{valeur 7}{\lsth[7]}{type=numeric}
\answer{valeur 8}{\lsth[8]}{type=numeric}
\answer{valeur 9}{\lsth[9]}{type=numeric}
\answer{valeur 10}{\lsth[10]}{type=numeric}
#endif

#if defined TARGET_repgraph1
\statement{
Voici une représentation graphique d'une série statistique :
<div class="wimscenter">
\draw{400,400}{\image}</div>
 De quelle représentation graphique s'agit-il ?
}

\answer{Il s'agit}{\typerep ;\lstrep}{type=radio}
#endif
