\title{Question 0420 Tracer un segment}
\keywords{length,lines}
\integer{unite=randint(4..5)}
\real{xlegende=\unite/2}
\integer{num=\unite+randint(1..3)}
\text{quest=\(\frac{\num}{\unite}\)}
\integer{sol0420=\num}
%%%%%%%%%%%%%%% graphique %%%%%
\text{jsxscript=
JXG.Options.point.snapToGrid = true;
JXG.Options.point.snapSizeX = 1;
JXG.Options.elements.tabindex = -1;
const brd = JXG.JSXGraph.initBoard('id1', {   boundingbox:  [-2, 4, 18, -2],
  axis:false,
  grid:true,
  showCopyright : false,
  showNavigation:false,
  showZoom : false,
  keepaspectratio : true,
  zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: true,eps: 0.001},
  pan: {needShift: true,enabled: true,needTwoFingers: true,pinchHorizontal: true,pinchVertical: true,pinchSensitivity: 7}
   }  );
brd.create('text', [\xlegende, 3, "1 unité"], {fontSize: 15, fixed:true,anchorX:'middle', cssClass:'mytext'});
let p1 = brd.create('point', [0,0],{name:'A',size:4,color:'green',fixed:true,face:'cross',showInfobox:false,label:{fixed:true,offset:[-15,-10]}});
let l1 = brd.create('segment',[[0,0],[18,0]],{strokeColor: 'transparent',highlight: false,fixed:true});
let l2 = brd.create('segment',[[0,2],[\unite,2]],{strokeColor: 'red',highlight: false,fixed:true});
let p2_rep1=brd.create('glider', [p2_var1,0,l1],{name:'B',tabindex:10,size:4,color:'green',fixed:false,showInfobox:false,layer: 15,label:{fixed:false,offset:[0,-10]}});
let seg=brd.create('segment',[p1,p2_rep1],{name:'s',strokeColor: 'green',strokeWidth: 2,highlight: false});
p2_var1=1;
}


\text{enonce=Déplacer le point B pour tracer un segment [AB] de longueur \quest unités.}
%%%%%%%%% ci dessous le code à ajouter au statement %%%%
\text{code_statement=<div>
\embed{r1,400x200
id1 brd [responsive center min=250px max=400px scroll]
\jsxscript

 }</div>}






\text{feedback=Une unité vaut \(\unite\) carreaux. Le segment doit donc mesurer \(\num\) carreaux.}
