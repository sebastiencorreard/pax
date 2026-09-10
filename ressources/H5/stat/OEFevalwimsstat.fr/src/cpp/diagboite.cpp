target=diagboite1 diagboite2 diagboite3 diagboite4 diagboite5
\author{Régine, Mangeard; Julien, Lyotard}
\email{regine@mangeard.fr,jlyotard@free.fr}
\format{html}
#include "lang_titles.inc"
\text{jsopt=}
\integer{xmin=randint(5..20)}
\integer{xmax=\xmin+randint(10..20)}
\integer{xmaxx=\xmax+randint(5..7)}
\text{lstval=wims(makelist x for x=\xmin to \xmax)}
\text{ind=shuffle(\xmax-\xmin)}
\text{ind=item(1..7,\ind)}
\text{ind=wims(sort numeric list \ind)}
\integer{xmin=\lstval[\ind[1]]}
\integer{D1=\lstval[\ind[2]]}
\integer{Q1=\lstval[\ind[3]]}
\integer{med=\lstval[\ind[4]]}
\integer{Q3=\lstval[\ind[5]]}
\integer{D9=\lstval[\ind[6]]}
\integer{xmax=\lstval[\ind[7]]}
\integer{intQ=\Q3-\Q1}
\integer{intD=\D9-\D1}
\integer{etendue=\xmax-\xmin}
\text{sizex=\xmaxx < 20 ? 500 : 600}
\text{sizex=\xmaxx > 40 ? 800}
#if defined TARGET_diagboite1
\integer{k=randint(1..2)}
\if{\k=1}{
  \matrix{STEP= reply1}
  \text{typediag=en boîte}
  \text{script= var brd = JXG.JSXGraph.initBoard('jxgbox', {
axis:false,boundingbox: [1, 20, \xmaxx, -2], grid:true, shownavigation:false});
 xaxis = brd.create('axis', [[0, 0], [1, 0]], {
 ticks: { ticksDistance: 1, insertTicks: false}});
yaxis = brd.create('axis', [[0, 0], [0, 3]],{
 ticks: { ticksDistance:2, insertTicks: false,visible:false},visible:false});
brd.create('text',[10,17,"Diagramme \typediag" ],{fontSize:30});
jxgbox_rep2 = brd.create('point',jxgbox_var2, {face:'o', name:'', size:2, showInfobox: true});
jxgbox_rep3 = brd.create('point',jxgbox_var3, {face:'o', name:'', size:2, showInfobox: true});
jxgbox_rep4 = brd.create('point',jxgbox_var4, {face:'o', name:'', size:2, showInfobox: true});
brd.on('move', function(){
jxgbox_rep2.moveTo([Math.min(jxgbox_rep2.X(),jxgbox_rep3.X()), 8]);
jxgbox_rep3.moveTo([Math.min(jxgbox_rep3.X(),jxgbox_rep4.X()), 8]);
jxgbox_rep4.moveTo([jxgbox_rep4.X(), 8]);
});
jxgbox_rep22 = brd.create('point',[function(){return jxgbox_rep2.X()},10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep222 = brd.create('point',[function(){return jxgbox_rep2.X()},6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep33 = brd.create('point',[function(){return jxgbox_rep3.X()},10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep333 = brd.create('point',[function(){return jxgbox_rep3.X()},6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep44 = brd.create('point',[function(){return jxgbox_rep4.X()},10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep444 = brd.create('point',[function(){return jxgbox_rep4.X()},6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
brd.create('line',[jxgbox_rep22,jxgbox_rep222],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep33,jxgbox_rep333],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep44,jxgbox_rep444],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep22,jxgbox_rep44],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep222,jxgbox_rep444],{straightFirst:false, straightLast:false});
}
\text{var=jxgbox_var2=[2,8] ; jxgbox_var3=[3,8] ; jxgbox_var4=[5,8]}
}{
\matrix{STEP= reply2}
\text{typediag=à moustaches}
\text{script= var brd = JXG.JSXGraph.initBoard('jxgbox', {
axis:false,boundingbox: [1, 20, \xmaxx, -2], grid:true, shownavigation:false});
 xaxis = brd.create('axis', [[0, 0], [1, 0]], {
 ticks: { ticksDistance: 1, insertTicks: false}});
yaxis = brd.create('axis', [[0, 0], [0, 3]],{
 ticks: { ticksDistance:2, insertTicks: false,visible:false},visible:false});
brd.create('text',[8,17,"Diagramme \typediag" ],{fontSize:30});
jxgbox_rep1 = brd.create('point',jxgbox_var1, {face:'o', name:'Déplace moi', size:2, showInfobox: true});
jxgbox_rep2 = brd.create('point',jxgbox_var2, {face:'o', name:'', size:2, showInfobox: true});
jxgbox_rep3 = brd.create('point',jxgbox_var3, {face:'o', name:'', size:2, showInfobox: true});
jxgbox_rep4 = brd.create('point',jxgbox_var4, {face:'o', name:'', size:2, showInfobox: true});
jxgbox_rep5 = brd.create('point',jxgbox_var5, {face:'o', name:'', size:2, showInfobox: true});
brd.on('move', function(){
jxgbox_rep1.moveTo([ Math.min(jxgbox_rep1.X(),jxgbox_rep2.X()), 8]);
jxgbox_rep2.moveTo([Math.min(jxgbox_rep2.X(),jxgbox_rep3.X()), 8]);
jxgbox_rep3.moveTo([Math.min(jxgbox_rep3.X(),jxgbox_rep4.X()), 8]);
jxgbox_rep4.moveTo([Math.min(jxgbox_rep4.X(),jxgbox_rep5.X()), 8]);
jxgbox_rep5.moveTo([Math.max(jxgbox_rep4.X(),jxgbox_rep5.X()), 8]);
});
jxgbox_rep11 = brd.create('point',[function(){return jxgbox_rep1.X()},9], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep111 = brd.create('point',[function(){return jxgbox_rep1.X()},7], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep55 = brd.create('point',[function(){return jxgbox_rep5.X()},9], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep555 = brd.create('point',[function(){return jxgbox_rep5.X()},7], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep22 = brd.create('point',[function(){return jxgbox_rep2.X()},10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep222 = brd.create('point',[function(){return jxgbox_rep2.X()},6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep33 = brd.create('point',[function(){return jxgbox_rep3.X()},10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep333 = brd.create('point',[function(){return jxgbox_rep3.X()},6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep44 = brd.create('point',[function(){return jxgbox_rep4.X()},10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep444 = brd.create('point',[function(){return jxgbox_rep4.X()},6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
brd.create('line',[jxgbox_rep1,jxgbox_rep2],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep4,jxgbox_rep5],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep11,jxgbox_rep111],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep55,jxgbox_rep555],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep22,jxgbox_rep222],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep33,jxgbox_rep333],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep44,jxgbox_rep444],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep22,jxgbox_rep44],{straightFirst:false, straightLast:false});
brd.create('line',[jxgbox_rep222,jxgbox_rep444],{straightFirst:false, straightLast:false});
}
\text{var=jxgbox_var1=[1,8] ; jxgbox_var2=[2,8] ; jxgbox_var3=[3,8] ; jxgbox_var4=[5,8] ; jxgbox_var5=[6,8]}
}
\steps{\STEP}
#endif
#if defined TARGET_diagboite2
\integer{k=randint(1..2)}
\if{\k=1}{
  \text{typediag=en boîte}
  \text{graph=slib(geo2D/jsxgraph jsxbox,\sizex x300, var brd = JXG.JSXGraph.initBoard('jsxbox', {
axis:false,boundingbox: [1, 20, \xmaxx, -2], grid:true, shownavigation:false});
 xaxis = brd.create('axis', [[0, 0], [1, 0]], {
 ticks: { ticksDistance: 1, insertTicks: false}});
yaxis = brd.create('axis', [[0, 0], [0, 3]],{
 ticks: { ticksDistance:2, insertTicks: false,visible:false},visible:false});
brd.create('text',[10,17,"Diagramme \typediag" ],{fontSize:30});
jxgbox_rep2 = brd.create('point',[\Q1,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep3 = brd.create('point',[\med,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep4 = brd.create('point',[\Q3,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep22 = brd.create('point',[\Q1,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep222 = brd.create('point',[\Q1,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep33 = brd.create('point',[\med,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep333 = brd.create('point',[\med,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep44 = brd.create('point',[\Q3,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep444 = brd.create('point',[\Q3,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
brd.create('line',[jxgbox_rep22,jxgbox_rep222],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep33,jxgbox_rep333],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep44,jxgbox_rep444],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep22,jxgbox_rep44],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep222,jxgbox_rep444],{straightFirst:false, straightLast:false,fixed:true});
)}
  \text{mstep=r1,r2,r3}
}{
\text{typediag=à moustaches}
\text{graph=slib(geo2D/jsxgraph jsxbox,\sizex x300, var brd = JXG.JSXGraph.initBoard('jsxbox', {
axis:false,boundingbox: [1, 20, \xmaxx, -2], grid:true, shownavigation:false});
 xaxis = brd.create('axis', [[0, 0], [1, 0]], {
 ticks: { ticksDistance: 1, insertTicks: false}});
yaxis = brd.create('axis', [[0, 0], [0, 3]],{
 ticks: { ticksDistance:2, insertTicks: false,visible:false},visible:false});
brd.create('text',[12,17,"Diagramme \typediag" ],{fontSize:30});
jxgbox_rep1 = brd.create('point',[\D1,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep2 = brd.create('point',[\Q1,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep3 = brd.create('point',[\med,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep4 = brd.create('point',[\Q3,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep5 = brd.create('point',[\D9,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep11 = brd.create('point',[\D1,9], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep111 = brd.create('point',[\D1,7], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep55 = brd.create('point',[\D9,9], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep555 = brd.create('point',[\D9,7], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep22 = brd.create('point',[\Q1,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep222 = brd.create('point',[\Q1,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep33 = brd.create('point',[\med,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep333 = brd.create('point',[\med,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep44 = brd.create('point',[\Q3,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep444 = brd.create('point',[\Q3,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
brd.create('line',[jxgbox_rep1,jxgbox_rep2],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep4,jxgbox_rep5],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep11,jxgbox_rep111],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep55,jxgbox_rep555],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep22,jxgbox_rep222],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep33,jxgbox_rep333],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep44,jxgbox_rep444],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep22,jxgbox_rep44],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep222,jxgbox_rep444],{straightFirst:false, straightLast:false,fixed:true});
)}
\text{mstep=r1,r2,r3,r4,r5}
}
\steps{\mstep}
#endif
#if (defined TARGET_diagboite3 || defined TARGET_diagboite4 )
\integer{xmin=randint(5..20)+randitem(50,100,200)}
\integer{xmax=\xmin+randint(30..50)}
\integer{xmin1=\xmin}
\integer{xmax1=\xmax}
\integer{q11=\xmin1+randint(5..10)}
\integer{q31=\xmin1+randint(20..25)}
\integer{med1=\xmin1+randint(13..17)}

\integer{k=randint(1..3)}
\integer{k=3}
\if{\k=1}{
 \integer{xmin2=\xmin1+randint(-1..1)}
 \integer{xmax2=\xmax1+randint(-1..1)}
 \integer{rep1=1}
 \integer{med2=\med1+randint(-1..1)}
 \integer{rep2=1}
 \integer{rep3=randint(1..2)}
 \integer{q12=\rep3=1?\q11+randint(1..3):\q11-randint(1..3)}
 \integer{q32=\rep3=1?\q31-randint(1..3):\q31+randint(1..3)}
}
\if{\k=2}{
 \integer{xmin2=\xmin1+randint(-10..-5)}
 \integer{xmax2=\xmax1+randint(5..10)}
 \integer{rep1=2}
 \integer{med2=\med1+randint(-1..1)}
 \integer{rep2=1}
 \integer{rep3=randint(1..2)}
 \integer{q12=\rep3=1?\q11+randint(1..3):\q11-randint(1..3)}
 \integer{q32=\rep3=1?\q31-randint(1..3):\q31+randint(1..3)}
}
\if{\k=3}{
 \integer{xmin2=\xmin1+randint(-10..-5)}
 \integer{xmax2=\xmax1+randint(5..10)}
 \integer{rep1=2}
 \integer{rep3=randint(1..2)}
 \integer{q12=\rep3=1?\q11+randint(1..3):\q11-randint(1..3)}
 \integer{q32=\rep3=1?\q31-randint(1..3):\q31+randint(1..3)}
 \integer{med2=\med1+randitem(-5,5)}
 \real{med2=\med2>\q32?\q32-0.5}
 \real{med2=\med2<\q12?\q12+0.5}
 \integer{rep2=abs(\med2-\med1)>3?2:1}
}

\integer{xmin=\xmin1<\xmin2?\xmin1:\xmin2}
\integer{xmax=\xmax1<\xmax2?\xmax2:\xmax1}
\text{dessin=
 xrange \xmin-5,\xmax+5
 yrange 0,10
 segment \xmin1,2.5,\xmin1,3.5,black
 segment \xmax1,2.5,\xmax1,3.5,black
 frect \q11,2,\q31,4,yellow
 segment \med1,2,\med1,4,red
 segment \xmin1,3,\q11,3,black
 segment \q31,3,\xmax1,3,black

 segment \xmin2,6.5,\xmin2,7.5,black
 segment \xmax2,6.5,\xmax2,7.5,black
 frect \q12,6,\q32,8,yellow
 segment \med2,6,\med2,8,red
 segment \xmin2,7,\q12,7,black
 segment \q32,7,\xmax2,7,black

 text black,\xmax+1,3,large,A
 text black,\xmax+1,7,large,B
 text black,\xmin,0.5,medium,\xmin
 text black,\xmax,0.5,medium,\xmax

}
\integer{repa=\xmax1-\xmin1>\xmax2-\xmin2?1:2}
\integer{repb=\q31-\q11>\q32-\q12?1:2}
\integer{repc=3-\repb}

\statement{<p>
Voici les diagrammes en boîte à moustaches de deux séries \(A) et \(B).
Pour chaque série, ces diagrammes représentent les 5 nombres Min, \(Q_1), Med, \(Q_3) et Max.
</p>
<div class="wimscenter">\draw{500,300}{\dessin} </div>
#if defined TARGET_diagboite3
<ol>
<li> Les étendues de ces deux séries sont: \embed{reply1}.</li>
<li> Les médianes de ces deux séries sont: \embed{reply2}.</li>
<li> La dispersion des données est plus grande pour: \embed{reply3}.</li>
</ol>
}
\answer{étendues}{\rep1;sensiblement les mêmes,très différentes}{type=radio}
\answer{médianes}{\rep2;sensiblement les mêmes,très différentes}{type=radio}
\answer{dispersion plus grande}{\rep3;série A,série B}{type=radio}
#else
<ol>
<li>L'étendue de la série \(A\) est \embed{reply1} à celle de la série \(B\).</li>
<li>L'écart interquartile de la série \(A\) est \embed{reply2} à celui de la série \(B\).</li>
<li>Les données sont plus concentrées autour de la médiane pour: \embed{reply3}.</li>
</ol>
}
\answer{étendues}{\repa;supérieure,inférieure}{type=radio}
\answer{écart}{\repb;supérieur,inférieur}{type=radio}
\answer{concentration}{\repc;série \(A\),série \(B\)}{type=radio}

# endif
#endif

#if defined TARGET_diagboite5
\text{typediag=à moustaches}
\text{graph=slib(geo2D/jsxgraph jsxbox,\sizex x300, var brd = JXG.JSXGraph.initBoard('jsxbox', {
axis:false,boundingbox: [1, 20, \xmaxx, -2], grid:true, shownavigation:false});
 xaxis = brd.create('axis', [[0, 0], [1, 0]], {
 ticks: { ticksDistance: 1, insertTicks: false}});
yaxis = brd.create('axis', [[0, 0], [0, 3]],{
 ticks: { ticksDistance:2, insertTicks: false,visible:false},visible:false});
brd.create('text',[12,17,"Diagramme \typediag" ],{fontSize:30});
jxgbox_rep1 = brd.create('point',[\D1,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep2 = brd.create('point',[\Q1,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep3 = brd.create('point',[\med,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep4 = brd.create('point',[\Q3,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep5 = brd.create('point',[\D9,8], {face:'o', name:'', size:2, showInfobox: true,fixed:true});
jxgbox_rep11 = brd.create('point',[\D1,9], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep111 = brd.create('point',[\D1,7], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep55 = brd.create('point',[\D9,9], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep555 = brd.create('point',[\D9,7], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep22 = brd.create('point',[\Q1,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep222 = brd.create('point',[\Q1,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep33 = brd.create('point',[\med,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep333 = brd.create('point',[\med,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep44 = brd.create('point',[\Q3,10], {face:'o', name:'', size:2, showInfobox: true,visible:false});
jxgbox_rep444 = brd.create('point',[\Q3,6], {face:'o', name:'', size:2, showInfobox: true,visible:false});
brd.create('line',[jxgbox_rep1,jxgbox_rep2],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep4,jxgbox_rep5],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep11,jxgbox_rep111],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep55,jxgbox_rep555],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep22,jxgbox_rep222],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep33,jxgbox_rep333],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep44,jxgbox_rep444],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep22,jxgbox_rep44],{straightFirst:false, straightLast:false,fixed:true});
brd.create('line',[jxgbox_rep222,jxgbox_rep444],{straightFirst:false, straightLast:false,fixed:true});
)}
\text{q11=moins,plus}
\text{q12=inférieures ou égales,strictement supérieures}
\text{q21=plus,moins}
\text{q22=strictement supérieures,inférieures ou égales}
\integer{k1=randint(1..2)}
\integer{k2=randint(1..2)}
\text{rep4=25,75}
#endif

#if defined TARGET_diagboite1
\statement{<p>
 On considère une série statistique dont on connaît les indicateurs suivants :
 </p>
 <ul>
  <li>Médiane = \med </li>
  <li>Premier quartile = \Q1 </li>
  <li>Troisième quartile = \Q3</li>
  <li>Premier décile = \D1 </li>
  <li>Neuvième décile = \D9</li>
 </ul>
 <p>
 A l'aide de la souris, déplacer les points sur le graphique pour dessiner le
diagramme \typediag de la série.
</p>
\embed{reply\k,\sizex x300
jxgbox
\script
\var
}
}

\answer{}{\jsq1;\jsme;\jsq3}{type=jsxgraph}{option= absolue precision=0.1}
\matrix{rep=\k=1?\reply1:\reply2}
\answer{}{\jsmin;\jsq1;\jsme;\jsq3;\jsmax}{type=jsxgraph}{option= absolute precision=0.1}
\condition{Votre diagramme en boîte \typediag est correct }{(\k=2 and (abs(\rep[1;1]-\D1)<0.2) and (abs(\rep[2;1]-\Q1)<0.2) and (abs(\rep[3;1]-\med)<0.2) and (abs(\rep[4;1]-\Q3)<0.2) and (abs(\rep[5;1]-\D9)<0.2)) or (\k=1 and (abs(\rep[1;1]-\Q1)<0.2) and (abs(\rep[2;1]-\med)<0.2) and (abs(\rep[3;1]-\Q3)<0.2))}
\feedback{\k=1}{<ul>
<li>\if{(abs(\rep[1;1]-\Q1)<0.2)}{Le premier quartile est bien placé en Q<sub>1</sub> = <span class="oef_indgood">\Q1</span>}{Le premier quartile est mal placé et on a : Q<sub>1</sub> = <span class="oef_indbad">\rep[1;1]</span><span class="oef_indgood">\Q1</span>}</li>
<li>\if{(abs(\rep[2;1]-\med)<0.2)}{La médiane est bien placée en M<sub>e</sub> = <span class="oef_indgood">\med</span>}{La médiane est mal placée et on a : M<sub>e</sub> = <span class="oef_indbad">\rep[2;1]</span><span class="oef_indgood">\med</span>}</li>
<li>\if{(abs(\rep[3;1]-\Q3)<0.2)}{Le troisième quartile est bien placé en Q<sub>3</sub> = <span class="oef_indgood">\Q3</span>}{Le troisième quartile est mal placé et on a : Q<sub>3</sub> = <span class="oef_indbad">\rep[3;1]</span><span class="oef_indgood">\Q3</span>}</li>
</ul>
<script>
brd.suspendUpdate();
brd.create('point',[\Q1,8], {face:'o', name:'Q<sub>1</sub>', size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
brd.create('point',[\med,8], {face:'o', name:'M<sub>e</sub>', size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
brd.create('point',[\Q3,8], {face:'o', name:'Q<sub>3</sub>', size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
</script>}
\feedback{\k=2}{<ul>
<li>\if{(abs(\rep[1;1]-\D1)<0.2)}{Le minimum est bien placé en xmin = <span class="oef_indgood">\D1</span>}{Le minimum est mal placé et on a : xmin = <span class="oef_indbad">\rep[1;1]</span><span class="oef_indgood">\D1</span>}</li>
<li>\if{(abs(\rep[2;1]-\Q1)<0.2)}{Le premier quartile est bien placé en Q<sub>1</sub> = <span class="oef_indgood">\Q1</span>}{Le premier quartile est mal placé et on a : Q<sub>1</sub> = <span class="oef_indbad">\rep[2;1]</span><span class="oef_indgood">\Q1</span>}</li>
<li>\if{(abs(\rep[3;1]-\med)<0.2)}{La médiane est bien placée en M<sub>e</sub> = <span class="oef_indgood">\med</span>}{La médiane est mal placée et on a : M<sub>e</sub> = <span class="oef_indbad">\rep[3;1]</span><span class="oef_indgood">\med</span>}</li>
<li>\if{(abs(\rep[4;1]-\Q3)<0.2)}{Le troisième quartile est bien placé en Q<sub>3</sub> = <span class="oef_indgood">\Q3</span>}{Le troisième quartile est mal placé et on a : Q<sub>3</sub> = <span class="oef_indbad">\rep[4;1]</span><span class="oef_indgood">\Q3</span>}</li>
<li>\if{(abs(\rep[5;1]-\D9)<0.2)}{Le maximum est bien placé en xmax = <span class="oef_indgood">\D9</span>}{Le maximum est mal placé et on a : xmax = <span class="oef_indbad">\rep[5;1]</span><span class="oef_indgood">\D9</span>}</li>
</ul>
<script>
brd.removeObject(jxgbox_rep1);
var jxgbox_rep1=brd.create('point',[\rep[1;1],8], {face:'o', name:'', size:2, showInfobox: true});
brd.create('line',[jxgbox_rep1,jxgbox_rep2],{straightFirst:false, straightLast:false});
/*jxgbox_rep1.setAttribute({name:'Ah!green'});Fonctionne avec la v0.98*/
brd.suspendUpdate();
brd.create('point',[\D1,8], {face:'o', name:'Min', size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
brd.create('point',[\Q1,8], {face:'o', name:'Q<sub>1</sub>', size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
brd.create('point',[\med,8], {face:'o', name:'M<sub>e</sub>', size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
brd.create('point',[\Q3,8], {face:'o', name:'Q<sub>3</sub>', size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
brd.create('point',[\D9,8], {face:'o', name:'Max',size:'8',fixed:true,strokeColor:'green',fillColor:'none'});
</script>}

#endif

#if defined TARGET_diagboite5
\statement{<p>
On considère une série statistique résumée par les nombres \(D_1 ; Q_1 ; Med ; Q_3 ; D_9).</p>
\graph
<p>Compléter les phrases suivantes à partir du diagramme \typediag dessiné ci-contre:
</p>
<ol>
<li> <label for="reply1">Au \q11[\k1]</label> \embed{reply1,3} % des valeurs sont \q12[\k1] à \med.</li>
<li> <label for="reply2">Environ la moitié des valeurs se situe entre</label> \embed{reply2,3} et \embed{reply3,3}.</li>
<li> <label for="reply3">Au \q21[\k2]</label> \embed{reply4,3} % des valeurs se situent \q22[\k2] de \Q3.</li>
</ol>
}
\answer{med}{50}{type=numeric}
\answer{moitié inf}{\Q1}{type=numeric}
\answer{moitié sup}{\Q3}{type=numeric}
\answer{Q3}{\rep4[\k2]}{type=numeric}
#endif
#if defined TARGET_diagboite2
\statement{
<div class="wimscenter">\graph</div>
Lire les valeurs des indicateurs de la série statistique dont le diagramme
  \typediag est dessiné ci-contre:
<ul><li><label for="reply1">Médiane =</label> \embed{reply1,3} </li>
<li><label for="reply2">Premier quartile =</label> \embed{reply2,3} </li>
<li><label for="reply3">Troisième quartile =</label> \embed{reply3,3}</li>
\if{\k=2}{
<li><label for="reply4">Premier décile =</label> \embed{reply4,3} </li>
<li><label for="reply5">Neuvième décile =</label> \embed{reply5,3}</li>
}
</ul>
}
\answer{Médiane}{\med}{type=numeric}
\answer{Q1}{\Q1}{type=numeric}
\answer{Q3}{\Q3}{type=numeric}
\answer{D1}{\D1}{type=numeric}
\answer{D9}{\D9}{type=numeric}
#endif
