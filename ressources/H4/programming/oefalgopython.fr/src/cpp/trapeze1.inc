\title{Méthode des trapèzes}

\text{prob=Cacul d'une intégrale d'une fonction \(f\) sur un intervalle
 \(\lbracket a;b \rbracket\) par la méthode des trapèzes}

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
var nn2 = bard.create('slider',[[1,-0.2],[5,-0.2],[2,4,10]],{face:"[]",name:'nombre de sous-intervalles',snapWidth:1,fixed:false});
f=function (x){return 1/(1 +x);};
bard.create('functiongraph', [f, 1, 8], {strokeWidth: 2 });
var dynObj = [];
var lastNN = -1;

function clearAll() {
  for (var i = 0; i < dynObj.length; i++) {bard.removeObject(dynObj[i]);}
  dynObj = [];
}

function intt() {
  var nzz = Math.round(nn2.Value());
  if (nzz === lastNN) return;
  lastNN = nzz;
  var azz = p11.X();
  var bzz = p22.X();
   var hzz = (bzz - azz) / nzz;
   bard.suspendUpdate();
   clearAll();
   for (var i = 0; i <= nzz; i++) {
     var xi = azz + hzz * i;
     var ptAxe = bard.create('point', [xi, 0], {name: 'x_{' + i + '}', strokeColor: 'green', face: '+', size: 10, fixed: true, showInfobox: false, label: { offset: [0, -15] }});
     dynObj.push(ptAxe);
     var ptCourbe = bard.create('point', [xi, f(xi)], {strokeColor: 'red', fillColor: 'red', size: 3, face: 'o', fixed: true, name: '', showInfobox: true});
     dynObj.push(ptCourbe);
     dynObj.push(bard.create('segment', [ptAxe, ptCourbe], {strokeColor: 'purple', strokeWidth: 1, dash: 2}));
     if (i < nzz) {dynObj.push(bard.create('text', [xi + hzz / 2, -0.08, 'h'], {anchorX: 'middle', fixed: true}));
       var xi1 = xi + hzz;
       var p1t = bard.create('point', [xi, 0], { visible: false });
       var p2t = bard.create('point', [xi, f(xi)], { visible: false });
       var p3t = bard.create('point', [xi1, f(xi1)], { visible: false });
       var p4t = bard.create('point', [xi1, 0], { visible: false });
       dynObj.push(p1t, p2t, p3t, p4t);
       dynObj.push(bard.create('polygon', [p1t, p2t, p3t, p4t], {borders: { strokeColor: 'purple', strokeWidth: 1 }, fillColor: 'purple', fillOpacity: 0.15, vertices: { visible: false }}));
       }
    }
    dynObj.push(bard.create('line', [[azz, -0.02], [bzz, -0.02]], {straightFirst: false, straightLast: false, strokeColor: 'green', fixed: true}));
    bard.unsuspendUpdate();
}
intt();
nn2.on('drag', function() { intt(); });
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
aire_trapeze=0;
forstep(x=vd,va,ph,xxli=concat(xxli,x*1.00);
yyli=concat(yyli,f(x)*1.0);
aire_trapeze=aire_trapeze+ph*(f(x)+f(x+ph))*0.50;
);
)}

\text{code=\#Initialisation des variables\#
a=??
b=??
n=??
h=??
x=??
aire_trapeze=0
\#Initialisation des listes\#
x_list=[]
y_list=[]
\#Définition d'une fonction\#
def f(x):
  return \fpyth
\#Coeur du programme\#
for i in range(n+1):
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  aire_trapeze=??
  x=??
\#Affichage des listes\#
print('La valeur approchée de l intégrale par la méthode des trapèzes est',aire_trapeze,'.')
}

\text{coefi=aire_trap=Sk.ffi.remapToJs(Sk.globals["aire_trapeze"]);
hh=Sk.ffi.remapToJs(Sk.globals["h"]);}

\text{coefr=var c1=brd.create('functiongraph', [function(x){ return \fjs;}, \xmin, \xmax], {strokeWidth: 2});
for(var jj = 0; jj < xlen; jj=jj+1) {
var t=brd.create('point', [x_liste[jj],y_liste[jj]],{color:'red',fixed:true,name:""});
var ttg=brd.create('point', [x_liste[jj],0],{fixed:true,name:"",visible:false});
var tttg=brd.create('point', [x_liste[jj+1],y_liste[jj+1]],{fixed:true,name:"",visible:false});
var ttttg=brd.create('point', [x_liste[jj+1],0],{fixed:true,name:"",visible:false});
var tpg=brd.create('polygon',[ttg,t,tttg,ttttg],{borders:{Color:'purple'},Color:'purple'});}
}
\text{instruction_code=instruction=[print(f(??))]}
