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
\text{last11=La simulation donne les résultats en comptant le nombre d'apparitions d'une face.
 Serait-il plus pertinent de déterminer la fréquence observée ?}

\text{gr=jsxbox,600 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "[]";
JXG.Options.point.withLabel=true;
color_liste=['red','yellow','blue','green','orange','purple'];
JXG.Options.point.size =2;
var brd = JXG.JSXGraph.initBoard('jsxbox', {axis:false, boundingbox: [-1,\ntt/6+200,7,-100],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,showFullscreen: true});
xaxis = brd.create('axis', [[0,0], [1,0]],
      {name:'Issues possibles',
      withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [-60, 30]   /*(in pixels)*/},Color:'red'});
      yaxis = brd.create('axis', [[0, 0], [0,1]],
      {name:'Nombre d\'apparitions d\'une face',withLabel: true,
      label: {position: 'rt',/* possible values are 'lft', 'rt', 'top', 'bot'*/
      offset: [10, 0]   /*(in pixels)*/},Color:'red'});}
\text{B=slib(geo2D/jsxgraph \gr)}


\text{code=\code
vi=??
vf=??
nt=??
n1=n2=n3=n4=n5=n6=0
\#################
for i in range(nt):
  issue = rand\pp(vi,vf)
  if issue==??:
    n1=n1+1
  if issue==??:
    n2=n2+1
  if issue==??:
    n3=n3+1
  if issue==??:
    n4=n4+1
  if issue==??:
    n5=n5+1
  if issue==??:
    n6=n6+1
print(n1,n2,n3,n4,n5,n6)
}

\text{variable=[vi,1],[vf,\nf],[nt,\ntt]}

\text{instruction3=<li>Déterminer les conditions à remplir pour compter le nombre
d'apparitions de chacune des faces.</li>}

\text{sscr=<script>
var tp=[];
var ch;
function graph(){brd.removeObject(ch);
brd.removeObject(tp);
n1=Sk.ffi.remapToJs(Sk.globals["n1"]);
n2=Sk.ffi.remapToJs(Sk.globals["n2"]);
n3=Sk.ffi.remapToJs(Sk.globals["n3"]);
n4=Sk.ffi.remapToJs(Sk.globals["n4"]);
n5=Sk.ffi.remapToJs(Sk.globals["n5"]);
n6=Sk.ffi.remapToJs(Sk.globals["n6"]);
nn=[n1,n2,n3,n4,n5,n6];
const xlen=nn.length;
var liii=brd.create('line',[[0,\ntt/6],[1,\ntt/6]],{Color:'red'});
brd.suspendUpdate();
ch = brd.create('chart', [nn], {
         chartStyle:'bar',
         width:0.5,
         labels:nn,
         colors: color_liste,
         shadow:true
});
for(var jj = 0; jj < xlen; jj=jj+1) {
tp[jj]=brd.create('point', [jj+1,nn[jj]],{name:nn[jj],label:{offset:[-10, 10]},color:color_liste[jj]});}
brd.unsuspendUpdate();
}
execidtest2.addEventListener('click',graph);
</script>}

\text{dec=0}
