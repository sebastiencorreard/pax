\text{enonce2=<p>Soit la fonction \(f\) continue et définie sur l'intervalle \(\left[0;1\right]\) par
 \(f(x)=\fct_ecr\).</p>
<div class="wims_instruction">Déplacer le point \(M(x;y)\) et analyser les conditions
 permettant le changement de couleur.</div>}

\text{grr=box,400 x 400,JXG.Options.point.fixed = true;
JXG.Options.point.highlight=false;
JXG.Options.point.showInfobox=false;
JXG.Options.point.name = "";
JXG.Options.point.face = "+";
JXG.Options.point.withLabel=true;
JXG.Options.point.size =3;
var board = JXG.JSXGraph.initBoard('box', {axis:true, boundingbox: [\xmin,\ymax,\xmax,\ymin],
shownavigation:false,showCopyright : false,
showZoom : true,keepaspectratio : false,showFullscreen: true});
var ff = function(x){ return \fct_js;};
var pol1= board.create('point', [0,0],{name:"A",strokeColor: "blue",fixed:true});
var pol2= board.create('point', [0,\coordyB],{name:"B",strokeColor: "blue",fixed:true});
var pol3= board.create('point', [1,\coordyC],{name:"C",strokeColor: "blue",fixed:true});
var pol4= board.create('point', [1,0],{name:"D",strokeColor: "blue",fixed:true});
var pol = board.create('polygon', [pol1, pol2, pol3,pol4],
            {strokeColor: 'blue', fillColor: 'red', fillOpacity: 0.3});           
var pp = board.create('point', [\coordxM,\coordyM],{name:'\(M(x;y)\)',strokeColor: "blue",fillColor:"blue",fixed:false,size:"12",face:"[]"});
board.on('move', function() {
board.suspendUpdate();
pp.moveTo([Math.min(1,pp.X()), Math.min(1,pp.Y())]);
pp.moveTo([Math.max(pp.X(), 0), Math.max(0, pp.Y())]);
let aa=pp.Y();
let bb=ff(pp.X());
if(aa-bb>0){pp.setAttribute({strokeColor: "red",fillColor:"red",trace:false});}
if(aa-bb<0){pp.setAttribute({strokeColor: "blue",fillColor:"blue",trace:false});}
board.unsuspendUpdate();
});
var pp1 = board.create('point', [function(){return pp.X();},0],{visible: false});
var pp2 = board.create('point', [0,function(){return pp.Y();}],{visible: false});
var sg1 = board.create('segment', [pp,pp1],{dash:1});
var sg2 = board.create('segment', [pp,pp2],{dash:1});
var c1 = board.create('functiongraph', [ff,0,1]);
var i1 = board.create('integral', [[0, 1], c1],{fixed: true, withLabel:false, Color:"blue"});
}

\text{graphique=slib(geo2D/jsxgraph \grr)}

\text{tre1=sous la courbe de la fonction \(f\)}

\integer{nll=randint(500..1000)}

\integer{jal=randint(1..2)}
\text{tjal1=(\jal==1)?npi=??:}
\text{tjal2=(\jal==1)?:npi=??}
\text{adad=(\jal=1)?au-dessous:au-dessus}

\text{tvide=}

\text{code=\code
nt=?? \#Nombre de points
npi= 0 \#Nombre de points dans le domaine violet
\#initialisation des listes\#
x_list_b = []
y_list_b = []
x_list_r = []
y_list_r = []
\#################
\#définition de la fonction\#
def f(x):
  return ??
\#################
for i in range(nt):
    a=\ppp()
    b=\ppp()
    x = a
    y = b \coeff
    if ?? :
        x_list_b.append(x)
        y_list_b.append(y)
        \tjal1     
    else:
        x_list_r.append(x)
        y_list_r.append(y)
        \tjal2
A_violette=npi/nt \coeff
\tvide    
  
print('Le rapport des aires de l intégrale et du carré est égal à environ ', npi/nt)}


Pas de var ni de let car elle passe en global
\text{jsss3_1= x_liste_b=Sk.ffi.remapToJs(Sk.globals["x_list_b"]);
y_liste_b=Sk.ffi.remapToJs(Sk.globals["y_list_b"]);
x_liste_r=Sk.ffi.remapToJs(Sk.globals["x_list_r"]);
y_liste_r=Sk.ffi.remapToJs(Sk.globals["y_list_r"]);
l_liste_b=x_liste_b.length;
l_liste_r=x_liste_r.length;
rnpi=Sk.ffi.remapToJs(Sk.globals["npi"]);
rA_v=Sk.ffi.remapToJs(Sk.globals["A_violette"]);
}
\text{donne=}


\text{embb=reply7,[python,[\code]];[idtest7,theme=\theme canvas init \instruction_code,Jouer le code !]}
\text{variable=[nt,\nll]}
