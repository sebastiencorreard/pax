\title{Méthode des milieux}

\text{prob=Cacul d'une intégrale d'une fonction \(f\) sur un intervalle
 \(\lbracket a;b \rbracket\) par la méthode des milieux}

\text{B2=slib(geo2D/jsxgraph jsxbox2,600 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.showInfobox=true;
JXG.Options.point.highlight=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "+";
JXG.Options.point.size = 2;
JXG.Options.point.withLabel=true;
const bard = JXG.JSXGraph.initBoard('jsxbox2', {axis:true, boundingbox: [-1,0.6,10,-0.3],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,
  zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: false,eps: 0.001},
  pan: {needShift: false,enabled: true,needTwoFingers: true,pinchHorizontal: true, pinchVertical: true,pinchSensitivity: 7}});
var p11=bard.create('point',[1,0],{name:'a', strokeColor:'black',fixed:true,label: {Color:'blue',offset:[-15,10]}});
var p22=bard.create('point',[8,0],{name:'b', strokeColor:'black',fixed:true,label: {Color:'blue'}});
bard.create('line',[p11,p22],{straightFirst:false, straightLast:false});
var nn2 = bard.create('slider',[[1,-0.2],[5,-0.2],[2,4,10]],{face:"[]",name:'nombre d\'intervalles',snapWidth:1,fixed:false});
f=function (x){return 1/(1 +x);};
bard.create('functiongraph', [f, 1, 8],{strokeWidth: 2 });

var dynObjects = [];
var lastNN = -1;

function clearAll() {
  for (var i = 0; i < dynObjects.length; i++){bard.removeObject(dynObjects[i]);}
  dynObjects = [];
}

function rrebuild() {
  var n = Math.round(nn2.Value());
  if (n === lastNN) return;
  lastNN = n;
  var a = p11.X();
  var b = p22.X();
  var h = (b - a) / n;
  bard.suspendUpdate();
  clearAll();
  for (var i = 0; i <= n; i++) {
    var xi = a + h * i;
    dynObjects.push(bard.create('point', [xi, 0], {name: 'x_{' + i + '}', strokeColor: 'green', face: '+', size: 10, fixed: true, showInfobox: false, label: { offset: [0, -15] }}));
    if (i < n) {
      dynObjects.push(bard.create('text', [xi + h / 2, -0.08, 'h'], {anchorX: 'middle', fixed: true}));
      var mil = xi + h / 2;
      var fmil = f(mil);
      var ptMilieu = bard.create('point', [mil, fmil], {strokeColor: 'red', fillColor: 'red', size: 3, face: 'o', fixed: true, name: '', showInfobox: true});
      dynObjects.push(ptMilieu);
      var ptMilieuAxe = bard.create('point', [mil, 0], { visible: false });
      dynObjects.push(ptMilieuAxe);
      dynObjects.push(bard.create('segment', [ptMilieuAxe, ptMilieu], {strokeColor: 'orange', strokeWidth: 1, dash: 2}));
      var xi1 = xi + h;
      var p1r = bard.create('point', [xi, 0], { visible: false });
      var p2r = bard.create('point', [xi, fmil], { visible: false });
      var p3r = bard.create('point', [xi1, fmil], { visible: false });
      var p4r = bard.create('point', [xi1, 0], { visible: false });
      dynObjects.push(p1r, p2r, p3r, p4r);
      dynObjects.push(bard.create('polygon', [p1r, p2r, p3r, p4r], {borders: { strokeColor: 'orange', strokeWidth: 1 },fillColor: 'orange', fillOpacity: 0.15, vertices: { visible: false }}));
      }
    }
  bard.unsuspendUpdate();
}

rrebuild();
nn2.on('drag', function() { rrebuild(); });

)}



\text{enonce=<p>Soit \(f\) une fonction définie par \(f(x)=\ft\) et continue sur l'intervalle \(\lbracket\xmin;\xmax\rbracket\).</p>
<p>On souhaite calculer l'intégrale de la fonction \(f\) entre les bornes \(\xmin\)
 et \(\xmax\) : \( \int_{\xmin}^{\xmax} (\ft) \, \mathrm{d}x \)</p>}


\text{DD=pari(default(format, "f.8");
vd=\xmin;
va=\xmax;
pn=\nn;
ph=(va-vd)/pn;
xxli=[];
yyli=[];
aire_milieu=0;
forstep(x=vd,va-ph,ph,xxli=concat(xxli,(x+ph/2)*1.00);
yyli=concat(yyli,f(x+ph/2)*1.0);
aire_milieu=aire_milieu+ph*f(x+ph/2)*1.00;
);
)}

\text{code=\#Initialisation des variables\#
a=??
b=??
n=??
h=??
x=??
aire_milieu=0
\#Initialisation des listes\#
x_list=[]
y_list=[]
\#Définition d'une fonction\#
def f(x):
  return \fpyth
\#Coeur du programme\#
for i in range(n):
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  aire_milieu=??
  x=??
\#Affichage des listes\#
print('La valeur approchée de l intégrale par la méthode des milieux est',aire_milieu,'ua.')
}

\text{coefi=aire_mil=Sk.ffi.remapToJs(Sk.globals["aire_milieu"]);
hh=Sk.ffi.remapToJs(Sk.globals["h"]);}

\text{coefr=var c1=brd.create('functiongraph', [function(x){ return \fjs;}, \xmin, \xmax], {strokeWidth: 2}); 
for(var jj = 0; jj < xlen; jj=jj+1){var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});
var ttg=brd.create('point', [x_liste[jj]-hh/2,0],{fixed:true,name:"",visible:false});
var tttg=brd.create('point', [x_liste[jj]-hh/2,y_liste[jj]],{fixed:true,name:"",visible:false});
var ttgg=brd.create('point', [x_liste[jj]+hh/2,y_liste[jj]],{fixed:true,name:"",visible:false});
var ttttg=brd.create('point', [x_liste[jj]+hh/2,0],{fixed:true,name:"",visible:false});
var tpg=brd.create('polygon',[ttg,tttg,ttgg,ttttg],{borders:{Color:'orange'},Color:'orange'});}
}
\text{instruction_code=instruction=[print(f(??))]}
