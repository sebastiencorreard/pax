\integer{zz=randint(0..20)}
\integer{ntt=1500+100*\zz}
\integer{nf=6}
\text{instructionf=Jouer le code plusieurs fois et envoyer la réponse.}
\integer{nnfe=randint(1..\nf)}
\text{lr=wims(makelist r x for x = 3 to 11)}
\text{de=wims(makelist x for x=1 to 6)}
\matrix{nstep=r1,r2}
\nextstep{\nstep}
\text{A=}
\text{AA=}
\integer{AA1=}
\text{BB=}
\text{grr=}
\text{instruction4=<li>Déterminer les formules permettant de calculer la fréquence
 pour l'ensemble des faces. La formule qui calcule la fréquence pour la face 1
 est donnée dans le code.</li>}
\text{last11=La simulation donne les résultats en fréquence d'apparition d'une face.
 Serait-il plus pertinent de déterminer le nombre d'apparitions d'une face ?}


\text{gr=jsxbox,600 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.withLabel=true;
color_liste=['red','yellow','blue','green','orange','purple'];
JXG.Options.point.size =2;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:false, boundingbox: [-1,0.5,7,-0.1],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,showFullscreen: true});
xaxis = brd.create('axis', [[0,0], [1,0]],
      {name:'Issues possibles',
      withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [-60, 30]   /*(in pixels)*/},Color:'red'});
      yaxis = brd.create('axis', [[0, 0], [0,1]],
      {name:'Fréquence d\'apparition d\'une face',withLabel: true,
      label: {position: 'rt', /*possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [10, 0]   /*(in pixels)*/},Color:'red'});}
\text{B=slib(geo2D/jsxgraph \gr)}


\text{code=\code
vi=??
vf=??
nt=??
f1=f2=f3=f4=f5=f6=0
\#################
for i in range(nt):
  issue = rand\pp(vi,vf)
  if issue==1:
    f1=f1+1/nt
  if issue==??:
    f2=??
  if issue==??:
    f3=??
  if issue==??:
    f4=??
  if issue==??:
    f5=??
  if issue==??:
    f6=??
print(f1,f2,f3,f4,f5,f6)
}

\text{variable=[vi,1],[vf,\nf],[nt,\ntt]}

\text{instruction3=<li>Déterminer les conditions à remplir pour compter le nombre
d'apparitions de chacune des faces.</li>}

\text{sscr=<script>
var tp=[];
var ch;
function graph(){if (ch) { brd.removeObject(ch); ch = null; };
if (liii) { brd.removeObject(liii); liii = null; };
if (tp.length) {for (var i = 0; i < tp.length; i++) {brd.removeObject(tp[i]);}tp = [];};
f1=Sk.ffi.remapToJs(Sk.globals["f1"]);
f2=Sk.ffi.remapToJs(Sk.globals["f2"]);
f3=Sk.ffi.remapToJs(Sk.globals["f3"]);
f4=Sk.ffi.remapToJs(Sk.globals["f4"]);
f5=Sk.ffi.remapToJs(Sk.globals["f5"]);
f6=Sk.ffi.remapToJs(Sk.globals["f6"]);
nn=[f1,f2,f3,f4,f5,f6];
const xlen=nn.length;
var liii=brd.create('line',[[0,1/6],[1,1/6]],{Color:'red'});
brd.suspendUpdate();
ch = brd.create('chart', [nn], {
         chartStyle:'bar',
         width:0.5,
         /*labels:nn,*/
         colors: color_liste,
         shadow:true
});
for(var jj = 0; jj < xlen; jj=jj+1) {
var tt=nn[jj].toFixed(3);
tp[jj]=brd.create('point', [jj+1,nn[jj]],{name:tt,label:{offset:[-10, 10]},color:color_liste[jj]});}
brd.unsuspendUpdate();
}
execidtest2.addEventListener('click',graph);
</script>}
\text{dec=3}
