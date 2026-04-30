target=ConnexionInt1 ConnexionInt2 ConnexionInt3 ConnexionInt4 ConnexionInt5 C1
\language{fr}
\range{-5..5}
\author{Julien LYOTARD}
\email{Julien.Lyotard@ac-dijon.fr}

\computeanswer{no}
\format{html}
\precision{100000}

debug
tttt=\tttt<br>
ttt=\ttt<br>
nnnnnn= \nnnnnn nnnnn=\nnnnn
ntdp=\ntdp<br>
moyc= \moyc<br>
ooo=\ooo<br>
x=\xy[1;]<br>
y=\xy[2;]<br>
co=\co<br>
coxy =\co[3;2]<br>
xmoy = \xmoy<br>
ymoy = \ymoy<br>
a=\a <br>
b= \b<br>

\matrix{xy=1,2,3,4,5,6,7,8
205,252,327,349,412,423,441,472
3700,1240,435,150,43,18,7,2
54,110,198,420,780,1640,3160,5960
310,396,425,480,612,704,830,946
3540,3260,3120,2890,2710,2570,2280,2090
509,925,1348,1678,2087,2506,2898,3323}

\text{ooo=}
\for{q=1 to 8}{\integer{oo=slib(stat/sum [\xy[;\q]])-\q}
\text{ooo=wims(append item \oo to \ooo)}}

\text{moyc=}
\for{q=1 to 7}{\real{oo=slib(stat/sum [\xy[\q;]])/8}
\text{moyc=wims(append item \oo to \moyc)}}

\text{prenom=slib(oef/env fn)}
\text{prenom=\prenom isin Lucas,Louis,Mathilde,Christine,Léa?Norbert}
\text{pre=Lucas,Louis,Mathilde,\prenom,Christine,Léa}

\text{ccc=blue,yellow,red,green,orange,#8B00FF}

\integer{nnn=randint(1..6)}
\integer{nnnn=randint(1..6)}
\integer{nnnnn=randint(1..6)}
\integer{nnnnnn= randint(1..6)}
\while{\nnnnnn=\nnnnn}{\integer{nnnnnn=randint(1..6)}} 

\integer{ren=random(1,4,5,6)}
\integer{renn=random(1,4,5,6)}
\while{\ren=\renn}{\integer{renn=random(1,4,5,6)}} 

\integer{xx=\ren=5?randint(13..17):randint(13..40)}
\integer{xxx=\renn=5?randint(13..17):randint(13..40)}

\integer{moych=\moyc[\nnnn+1]}

\integer{sss=randint(1..8)}
\integer{ssss=randint(1..8)}

\integer{sssss=randint(3..7)}

\integer{g=randint(1..2)}
\text{dp=\g=1?premières:dernières}

\if{\g=1}{\matrix{ttt=column(1..\sssss,\xy)}}{\matrix{ttt=column(8-\sssss+1..8,\xy)}}
\matrix{tttt=row([\nnnnn+1,\nnnnnn+1],\ttt)}
\integer{qq=slib(stat/sum [\tttt[1;]])}
\integer{qqq=slib(stat/sum [\tttt[2;]])}
\integer{ntdp=\qq+\qqq}

\integer{ps=10+(\g-1)*5}
\integer{pss=\ps=10?15:10}

\real{gxmoy=slib(stat/sum [\xy[1;]])/8}
\matrix{gco=slib(stat/covariance [\xy[1;]];[\xy[\ren+1;]])}
\real{gymoy=slib(stat/sum [\xy[\ren+1;]])/8}
\integer{gaa=\gco[3;2]/\gco[3;1]*100}
\real{ga=\gaa/100}
\integer{gbb=(\gymoy-\gco[3;2]/\gco[3;1]*\gxmoy)*100}
\real{gb=\gbb/100}

\matrix{gcoo=slib(stat/covariance [\xy[1;]];[\xy[\renn+1;]])}
\real{gymoyy=slib(stat/sum [\xy[\renn+1;]])/8}
\integer{gaaaa=\gcoo[3;2]/\gcoo[3;1]*100}
\real{gaaa=\gaaaa/100}
\integer{gbbbb=(\gymoyy-\gcoo[3;2]/\gcoo[3;1]*\gxmoy)*100}
\real{gbbb=\gbbbb/100}

\integer{es=\ga*\ps+\gb}
\integer{ess=\gaaa*\pss+\gbbb}

\real{xmoy=slib(stat/sum [\ttt[1;]])/\sssss}

\matrix{co=slib(stat/covariance [\ttt[1;]];[\ttt[\ren+1;]])}
\real{ymoy=slib(stat/sum [\ttt[\ren+1;]])/\sssss}
\integer{aa=\co[3;2]/\co[3;1]*100}
\real{a=\aa/100}
\integer{bb=(\ymoy-\co[3;2]/\co[3;1]*\xmoy)*100}
\real{b=\bb/100}

\matrix{coo=slib(stat/covariance [\ttt[1;]];[\ttt[\renn+1;]])}
\real{ymoyy=slib(stat/sum [\ttt[\renn+1;]])/\sssss}
\integer{aaaa=\coo[3;2]/\coo[3;1]*100}
\real{aaa=\aaaa/100}
\integer{bbbb=(\ymoyy-\coo[3;2]/\coo[3;1]*\xmoy)*100}
\real{bbb=\bbbb/100}

\integer{res=\a*\xx+\b}
\integer{ress=\aaa*\xxx+\bbb}

\text{pro=Quelle est l'évolution des connexions sur le serveur ?}

\text{enonce=L'ensemble des élèves d'une classe ont loué pour l'année un serveur dédié. Cet ordinateur installé
 dans les data center a une connexion ultra rapide. Ils peuvent donc mutualiser l'hébergement de leur blog
  et utiliser d'autres services. Dernièrement ils ont installé un compteur sur leur site pour connaître le nombre
 de connexions par semaine.Ils pourront ainsi prévoir la monté en charge du serveur et envisager son
 remplacement éventuel. La répartition des connexions est donnée dans  le tableau ci-desous :}
  
\text{A=slib(geo2D/jsxgraph jsxbox,1000 x 600,var brd = JXG.JSXGraph.initBoard('jsxbox',{axis:true,boundingbox: [-1,4000,9,-100],
shownavigation:true,showCopyright : false,
showZoom : true,keepaspectratio : false,
zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: false,eps: 0.001},
pan: {needShift: false,enabled: true,needTwoFingers: true,pinchHorizontal: true, pinchVertical: true,pinchSensitivity: 7},
showFullscreen: true}
);
colors = ['blue','yellow','red','green','orange','#8B00FF'];
var poi = brd.create('point', [4, 3600], {name:'A'});
var pui = brd.create('point', [8, 3600], {name:'B'});
var li = brd.create('line',[poi,pui]);
brd.create('glider',[9,30,li],{name:'Bouge moi', strokeColor:'black'});
function nuage(rr) {
  if (chart) {brd.removeObject(chart);};
chart = brd.create('chart', ['mytable'], {chartStyle: 'point,line', face:'+',size:'8',fixed:true,
                                                withHeaders: true, rows: [rr], strokeWidth:2,strokeColor:[colors[rr]]});}                                          
function nuage7() { 
if (chart) {brd.removeObject(chart);};
chart = brd.create('chart', ['mytable'], {chartStyle: 'point,line', face:'+',size:'8',fixed:true,
                                                withHeaders: true, colorArray: colors, strokeColor: colors, 
                                                fillColor: colors, highlightFillColor: colors, highlightStrokeColor: colors});}
var chart;
brd.highlightInfobox = function(x,y,el) {
            this.infobox.setText('<span style="color:black;font-weight:bold">( ' + x + ' ; ' + Math.round(y) + ' )</span>');
            this.infobox.rendNode.style.border = 'groove ' + el.visProp['strokeColor'];
            this.infobox.rendNode.style.backgroundColor = 'white';};
var txt = brd.create('text', [7,3400,function(){
return 'Équation de la droite (AB) :<br> y='+ ((pui.Y()-poi.Y())/(pui.X()-poi.X())).toFixed(2)+'x+'+(-((pui.Y()-poi.Y())/(pui.X()-poi.X()))*poi.X()+poi.Y()).toFixed(2);
}],{anchorX:'right', anchorY:'top',cssClass:'jsx',fontSize:20}); 
)}

#if #TARGET(ConnexionInt1)
\title{4.1 (C1) Quelle est l'évolution des connexions sur le serveur ?}
\statement{
# include "intro_connexion_serveur.inc"
# include "intro_connexion_serveur2.inc"
<div class="question">
<ul class="wims_nopuce"><li>Combien de visiteurs ont parcouru le site de \pre[\nnn] la \sss<sup>\if{\sss=1}{er}{e}</sup>
 semaine ? \embed{reply1,4}</li>
<li>Le serveur héberge la totalité des sites. Quel est le nombre total de connexions
 la \ssss<sup>\if{\ssss=1}{er}{e}</sup> semaine ? \embed{reply2,5}</li>
<li>Quelle est la moyenne des connexions hebdomadaires sur le site de \pre[\nnnn] ? Arrondir le résultat à l'unité. \embed{reply3,5}
</li>
<li>Quel est le nombre de connexions totales sur les blog de \pre[\nnnnn] et \pre[\nnnnnn] les \sssss \dp semaines ? \embed{reply4,5}</li>
</ul>
</div>

</div>}

\answer{Nombre de visiteurs semaine \sss}{\xy[\nnn+1;\sss]}{type=numeric}
\answer{Nombre total semaine \ssss}{\ooo[\ssss]}{type=numeric}
\answer{Moyenneconnexions hebdomadaire}{\moych}{type=numeric}
\answer{connexions totales}{\ntdp}{type=numeric}
#endif

#if #TARGET(ConnexionInt2)
\title{4.2 (C2) Quelle est l'évolution des connexions sur le serveur ?}
\statement{
# include "intro_connexion_serveur.inc"
# include "intro_connexion_serveur2.inc"
<div class="question">
Déplacer les points A et B et émettre des conjectures sur les valeurs des connexions lors des semaines à venir.
<ul class="wims_nopuce"><li>
Le nombre de visiteurs sur le blog de \pre[\ren] la \ps<sup>e</sup> semaine est donc d'environ : \embed{reply1,5}</li>
<li>
Le nombre de visiteurs sur le blog de \pre[\renn] la \pss<sup>e</sup> semaine est donc d'environ : \embed{reply2,5}</li>
</div>
</div>}
\answer{Nombre de visiteurs semaine \ps}{\es-200,\es+200,\es}{type=range}
\answer{Nombre total visiteurs semaine \pss}{\ess-200,\ess+200,\ess}{type=range}
#endif
#if #TARGET(ConnexionInt3)
\title{4.3 (C2) Quelle est l'évolution des connexions sur le serveur ?}
\statement{
# include "intro.inc"
<div class="question">
<br>
Choisir l'ajustement approprié pour prévoir l'évolution future des connexions aux différents
 blog :
<ul>
\for{nm=1 to 6}{<li>Le nombre de connexions au site de \pre[\nm] peut être modélisé par une courbe d'ajustement : \embed{reply\nm}</li>}
</ul>
<br>
</div>
</div>}

\answer{Modèle de Lucas}{1;affine, parabolique, exponentielle}{type=checkbox}{option= sort}
\answer{Modèle de Louis}{3;affine, parabolique, exponentielle}{type=checkbox}{option=  sort}
\answer{Modèle de Mathilde}{3;affine, parabolique, exponentielle}{type=checkbox}{option=  sort}
\answer{Ton modèle}{1;affine, parabolique, exponentielle}{type=checkbox}{option=  sort}
\answer{Modèle de Christine}{1;affine, parabolique, exponentielle}{type=checkbox}{option=  sort}
\answer{Modèle de Léa}{1;affine, parabolique, exponentielle}{type=checkbox}{option=  sort}
#endif

#if #TARGET(ConnexionInt4)
\title{4.4 (C2 et C3) Quelle est l'évolution des connexions sur le serveur ?}
\statement{
# include "intro_connexion_serveur.inc"
# include "intro_connexion_serveur2.inc"

<div class="question">
Après étude du code source, les élèves constatent que seul les relevés effectués les \sssss \dp semaines sont justes.
<ul class="wims_nopuce"><li>
Déterminer une équation de la droite de tendance pour le blog de \pre[\ren] avec les coefficients arrondis à 0.01 :
<div class="wimscenter">\embed{reply1,20}</div>
</li><li>
Déterminer une équation de la droite de tendance pour le blog de \pre[\renn] avec les coefficients arrondis à 0.01 :
<div class="wimscenter">\embed{reply2,20}</div>
</li>
</div>
</div>}
\answer{Equation de la droite pour Lucas}{y=\a x+ \b}{type=equation}
\answer{Equation de la droite pour Lucas}{y=\aaa x+ \bbb}{type=equation}
#endif

#if #TARGET(ConnexionInt5)
\title{4.5 (C4 et C5) Quelle est l'évolution des connexions sur le serveur ?}
\statement{
# include "intro_connexion_serveur.inc"
# include "intro_connexion_serveur2.inc"
<div class="question">
Après étude du code source, les élèves constatent que seul les relevés effectués les \sssss \dp semaines sont justes.
<br>
À l'aide de ses données, ils déterminent les 2 droites de tendances :
<ul><li style="color:\ccc[\ren];font-weight:bold">\pre[\ren] :    y = \a x + \b</li>
<li style="color:\ccc[\renn];font-weight:bold">\pre[\renn] :     y = \aaa x + \bbb</li></ul>
Si la tendance se confirme, déterminer le nombre de connexions sur le blog de \pre[\ren] la \xx<sup>e</sup> semaine :  \embed{reply1,6}
<br>
Valider ou invalider la valeur trouvée précédemment :  \embed{reply2}
<br>
Si la tendance se confirme, déterminer le nombre de connexions sur le blog de \pre[\renn] la \xxx<sup>e</sup> semaine :  \embed{reply3,6}
<br>
le résultat trouvé précédemment, est-il pertinent :  \embed{reply4}
<br>
Réaliser une ou plusieurs phrases qui expliquent la démarche réalisée pour valider vos résultats : 
<div class="wimscenter">\embed{reply5}</div>
</div>
</div>
}
À l'aide du graphique, on place la droite dans le nuage de points et on réalise une lecture graphique;graphique,nuage de points,droite
\answer{Nombre de connexions la \xx semaine}{\res}{type=numeric}
\answer{}{1;Valider,Invalider}{type=radio}
\answer{Nombre de connexions la \xxx semaine}{\ress}{type=numeric}
\answer{}{1;Oui,Non}{type=radio}
\answer{}{\kgkgg}{type=symtext}{option= nopunct nocs nomath noparentheses noquote}
\condition{Pour vérifier la cohérence du résultat, la droite (AB) doit être placée dans le
 nuage de points. En déplaçant le point "Bouge moi" sur l'abscisse \xx, on lit en ordonnée le nombre de connexions}{point isin \kgkgg and nuage de points isin \kgkgg and (lecture graphique isin \kgkgg or ordonnée isin \kgkgg or abscisse isin \kgkgg) and droite isin \kgkgg and nombre de connexions isin \kgkgg}
#endif

#if #TARGET(C1)
\title{4.4 (C1) AideQuestion 4.4}
\integer{newsssss=randint(3..7)}
\text{newdp=\g=1?dernières:premières}
\if{\g=1}{\matrix{ttt=column(1..\sssss,\xy)}
\matrix{newttt=column(8-\newsssss+1..8,\xy)}
\integer{newsema=10-\newsssss}
\text{rnewll=wims(makelist x for x=\newsema to 9)}
}{\matrix{ttt=column(8-\sssss+1..8,\xy)}
\matrix{newttt=column(1..\newsssss,\xy)}
\text{rnewll=wims(makelist x for x=2 to \newsssss+1)}}

\matrix{newtttt=row([\nnnn+1],\newttt)}
\text{newll=semaine,\xy[1;],Lucas,\xy[2;],Louis,\xy[3;],Mathilde,\xy[4;],\prenom,\xy[5;],Christine,\xy[6;],Léa,\xy[7;]}
\integer{pos=position(\newtttt[1],\newll)}
\integer{poss=position(\pre[\nnnn],\newll)}
\text{rrnewll=wims(makelist x for x=\pos to \pos+\newsssss-1)}
\css{<style>
.ans_multipleclick1 {margin-left:auto;margin-right:auto;
  border: medium solid #0001;
  border-collapse: separate;
  text-align:center;}
td, th {
  border: thin solid #0001;
  background-color: #0001;}
  </style>}

debug
rrnewll=\rrnewll <br>
rnewll=\rnewll <br>
pos=\pos <br>
newtttt=\newtttt<br>
tttt=\tttt<br>
ttt=\ttt<br>
nnnnnn= \nnnnnn nnnnn=\nnnnn
ntdp=\ntdp<br>
moyc= \moyc<br>
ooo=\ooo<br>
x=\xy[1;]<br>
y=\xy[2;]<br>
co=\co<br>
coxy =\co[3;2]<br>
xmoy = \xmoy<br>
ymoy = \ymoy<br>
a=\a <br>
b= \b<br>

\statement{
# include "intro_connexion_serveur.inc"
<div class="question">
Après étude du code source, les élèves constatent que seul les relevés effectués les \newsssss \newdp semaines sont justes.
 Cliquer sur les données du tableau que l'on doit conserver pour réaliser des prévisions correctes sur le site de \pre[\nnnn] ? 
<br/>
 \embed{r1, 600x400
9 x 7}
</div>

</div>}

À l'aide du graphique, on place la droite dans le nuage de points et on réalise une lecture graphique;graphique,nuage de points,droite
\answer{}{1,\rnewll,\poss,\rrnewll;\newll}{type=multipleclick}
#endif
