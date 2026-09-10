target=TGVvsAvion1 TGVvsAvion2
\language{fr}
\range{-5..5}
\author{Julien LYOTARD}
\email{Julien.Lyotard@ac-dijon.fr}

\computeanswer{no}
\format{html}
\precision{1000}

\css{<style>
  .jxgbox {margin-left:auto;margin-right:auto;}
</style>}
  
\matrix{Cap=
Lisbonne,-17.7,-13
Madrid,-13.9,-12.6
Rome,-3.9,-12.9
Athènes,3.2,-16.5
Tirana,0.6,-13.6
Sofia,2.6,-12.2
Belgrade,0.8,-10.7
Bucarest,4,-10.4
Budapest,-0.2,-8.4
Bratislava,-1,-7.7
Vienne,-1.7,-7.7
Prague,-2.7,-5.9
Berlin,-3,-4
Bruxelles,-7.7,-5
Amesterdan,-7.3,-4.1
Londres,-9.8,-3.9
Dublin,-12.5,-1.5
Copenhague,-3.5,-1.5
Oslo,-4,2.4
Stokholm,-1.4,1.8
Helsinki,1.9,2.9
Tallinn,2,2
Riga,2,0
Vilnius,2.2,-2
Minsk,3.5,-2.5
Moscou,8,0.2
Varsovie,0.65,-4.1
Kiev,5.3,-5.1}
\integer{n=randint(1..28)}
\integer{nn=randint(1 ..28)}
\while{\n = \nn}{\integer{nn=randint(1 ..28)}}
\matrix{rep=}
\integer{Dc=sqrt((\Cap[\n;2]-\Cap[\nn;2])^2+(\Cap[\n;3]-\Cap[\nn;3])^2)*100}
\real{Dcc=\Dc/100}
\real{Dccr=\Dcc*150}
\real{Dccrmin=(\Dcc-0.4)*150}
\real{Dccrmax=(\Dcc+0.4)*150}
\real{t=\Dccr/250}
\real{tmin=\Dccrmin/250}
\real{tmax=\Dccrmax/250}
\real{tt=\Dccr/750}
\real{ttmin=\Dccrmin/750}
\real{ttmax=\Dccrmax/750}
\integer{ttt= \t<(\tt+2) ?1:2}

\text{script= var brd = JXG.JSXGraph.initBoard('jxgbox', { 
axis:true,boundingbox: [-20, 20, 20, -20], grid:true, shownavigation:true,showFullscreen: true});
var urlImg = "\imagedir/Capital.png";
var carte = brd.create('image',[urlImg,[-24,-22], [48,38] ],{fixed:true});
var dfp = brd.create('text',[-16,16,"Placer les capitales suivantes :" ],{fontSize:30});
jxgbox_rep1 = brd.create('point',jxgbox_var1 , {face:'+', name:'\Cap[\n;1]', size:6, showInfobox: false});
jxgbox_rep2 = brd.create('point',jxgbox_var2, {face:'+', name:'\Cap[\nn;1]', size:6, showInfobox: false});}
  
\text{B=slib(geo2D/jsxgraph box,800 x 800, var brd = JXG.JSXGraph.initBoard('box', { 
  axis:true,boundingbox: [-20, 20, 20, -20], grid:true, shownavigation:true,showFullscreen: true});
        var urlImg = "\imagedir/Capital.png";
        var carte = brd.create('image',[urlImg,[-24,-22], [48,38] ],{fixed:true});
        var sos = brd.create('point',[3.5,15] , {face:'+', size:8,fixed:false, showInfobox: false,Color:'black'});
        var soss = brd.create('point',[15,15] , {face:'+', size:8,fixed:false, showInfobox: false,Color:'black'});
        brd.create('text',[-16,17,function(){
return 'Utiliser le segment [AB] pour effectuer des mesures: AB =' + sos.Dist(soss).toFixed(2) +' unités';}],{fontSize:20});
        brd.create('point',[\Cap[\n;2],\Cap[\n;3]] , {face:'o',fixed:true, size:1, showInfobox: false,name:'\Cap[\n;1]',Color:'green'});
        brd.create('point',[\Cap[\nn;2],\Cap[\nn;3]] , {face:'o',fixed:true, size:1, showInfobox: false,name:'\Cap[\nn;1]',Color:'green'});
        var sss= brd.create('line',[sos,soss],{straightFirst:false, straightLast:false});
              )}

#if #TARGET(TGVvsAvion1)
\title{Placement de points simples}
\statement{
<div class="encadre">
<div class="problematique">
Quel est le moyen de transport le plus rapide pour aller de \Cap[\n;1] à \Cap[\nn;1] ? 
</div>
<div class="enonce">
Le TGV roule à la vitesse moyenne de 250 km/h.
<br> L'avion vole à la vitesse de 750 km/h mais il faut arriver 2H à l'avance pour
 compléter les modalités d'enregistrement.
</div>
<div class="question">
Sur le graphique, placer les 2 capitales suivantes :
<ul><li>\Cap[\n;1] de coordonnées ( \Cap[\n;2] , \Cap[\n;3] )</li><li>\Cap[\nn;1] dont la valeur en abscisse
est de \Cap[\nn;2] et en ordonnée de \Cap[\nn;3] </li></ul>
</div>


\embed{r1,800x800
jxgbox
\script
jxgbox_var1=[5,16.5] ; jxgbox_var2=[10,16.5]}


</div>}
\answer{}{\Cap[\n;2],\Cap[\n;3];\Cap[\nn;2],\Cap[\nn;3]}{type=jsxgraph}{option= precision=5 noanalyzeprint}
\matrix{rep=\reply1}
\text{A=slib(geo2D/jsxgraph box,800 x 800, var brd = JXG.JSXGraph.initBoard('box', { 
  axis:true,boundingbox: [-20, 20, 20, -20], grid:true, shownavigation:true});
        var urlImg = "\imagedir/Capital.png";
        var carte = brd.create('image',[urlImg,[-24,-22], [48,38] ],{fixed:true});
        brd.create('text',[-16,16,"Les points que vous avez placé sont représenté par une croix rouge:" ],{fontSize:20});
        brd.create('point',[14.5,16.2] , {face:'+',fixed:true, size:6, showInfobox: false,name:''});
  brd.create('text',[-16,14,"Les bonnes réponses sont les ronds verts :" ],{fontSize:20});
        brd.create('point',[3.5,14.2] , {face:'o',fixed:true, size:6, showInfobox: false,name:'',strokeColor:'green',fillColor:'none'});
        brd.create('point',[\Cap[\n;2],\Cap[\n;3]] , {face:'o',fixed:true, size:6, showInfobox: false,name:'\Cap[\n;1]', strokeColor:'green',fillColor:'none'});
        brd.create('point',[\Cap[\nn;2],\Cap[\nn;3]] , {face:'o',fixed:true, size:6, showInfobox: false,name:'\Cap[\nn;1]', strokeColor:'green',fillColor:'none'});
        brd.create('point',[\rep[1;1],\rep[1;2]] , {face:'+',fixed:true, size:6, showInfobox: false,name:'\Cap[\n;1]'});
        brd.create('point',[\rep[2;1],\rep[2;2]] , {face:'+',fixed:true, size:6, showInfobox: false,name:'\Cap[\nn;1]'});
       )
}
\feedback{abs(\rep[1;1] -\Cap[\n;2])>0.2 or abs(\rep[1;2] -\Cap[\n;3])>0.2 or abs(\rep[2;1] -\Cap[\nn;2])>0.2 or abs(\rep[2;2] -\Cap[\nn;3])>0.2}{\A}
#endif

#if #TARGET(TGVvsAvion2)
\title{Echelle-Mesure de distance-Temps}
\statement{
<div class="encadre">
<div class="problematique">
Quel est le moyen de transport le plus rapide pour aller de \Cap[\n;1] à \Cap[\nn;1] ? 
</div>
<p class="special_letter">
Le TGV roule à la vitesse moyenne de 250 km/h.
<br> L'avion vole à la vitesse de 750 km/h mais il faut arriver 2H à l'avance pour
 compléter les modalités d'enregistrement.
</p>
<div class="question">

\B

<br>
Quelle est la distance entre les 2 capitales ?
<ul><li> \embed{reply1, 6} en unité du graphique.</li>
<li>
<table class="float_left wimsborder"><tr><td> 900 km représente</td><td> 6 unités graphique.</td></tr>
<tr><td>\embed{reply2, 6} km représente</td><td> \Dcc unités graphique.</td></tr>
</table>
</li></ul>
<br>
<div class="float_left">
La distance entre les deux capitales est de : \embed{reply3, 6} km.
</div>
<br>
<br>
<div class="float_left">
Quel est le temps en heure du trajet entre les 2 capitales ?
</div>
<br>
<ul><li> En TGV le temps est de \embed{reply4, 6}.</li>
<li>En avion le temps de parcours est de \embed{reply5, 6} sans compter l'embarquement.</li></ul>
<br>
Le moyen de transport le plus rapide est donc :
<ul>
\for{h = 1 to 2}{<li>\embed{reply6,\h}</li>}
</ul>
</div>
</div>
}
\answer{}{\Dcc-0.4,\Dcc+0.4,\Dcc}{type=range}{option= nonstop noanalyzeprint}
\answer{}{\Dccrmin,\Dccrmax,\Dccr}{type=range}{option= nonstop noanalyzeprint}
\answer{}{\Dccrmin,\Dccrmax,\Dccr}{type=range}{option= nonstop noanalyzeprint}
\answer{Temps en TGV}{\tmin,\tmax,\t}{type=range}{option= nonstop noanalyzeprint}
\answer{Temps en avion}{\ttmin,\ttmax,\tt}{type=range}{option= nonstop noanalyzeprint}

\answer{Le plus rapide}{\ttt;Le TGV,L'avion}{type=radio}{option=shuffle split nonstop}
#endif
