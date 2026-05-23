%%%%%%%%%%%%%%%%% FIGURE ENONCE - SOLUTION %%%%%%%%%%%%%%%%%%%
#if defined TARGET_01CliquerHypotenuse || defined TARGET_05ReconTrRect3 || defined TARGET_10DeuxMesures
#define ANGLE 1
#else
#define ANGLE 2
#endif

#if defined TARGET_01CliquerHypotenuse || defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
#define IDEM 1
#else
#define IDEM 2
#endif

#if defined TARGET_01CliquerHypotenuse || defined TARGET_12LigneTrigoUnite
#define INDIC 1
#else
#define INDIC 2
#endif

\text{board_enonce=
var brd = JXG.JSXGraph.initBoard('jsxenonce', {showCopyright : false,axis:false,boundingbox: [\xMin,\yMax,\xMax,\yMin],grid:false});}

\text{board_sol=
var brd = JXG.JSXGraph.initBoard('jsxsol', {showCopyright : false,axis:false, boundingbox: [\xMin,\yMax,\xMax,\yMin],grid:false});}

\text{scriptComjs=
A=brd.create('point',[0,0],{name:'\Sommet',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{fixed: false}});
B=brd.create('point',[\x_B2,\y_B2],{name:'\Hyp[1]',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{fixed: false}});
C=brd.create('point',[\x_C2,\y_C2],{name:'\Hyp[2]',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{fixed: false}});
brd.create('angle',[B,A,C],{name:' ',radius:\radiusAngle,strokeColor:'black',fillColor:'red',fillOpacity:0.8});
brd.create('polygon',[A,B,C],{strokeColor: 'black',fillColor: '\couleur',highlightfillColor:'\couleur'});
hypo=brd.create('segment',[B,C]);
cat1=brd.create('segment',[A,B]);
cat2=brd.create('segment',[A,C]);
#if ANGLE==2
brd.create('angle',[C,B,A],{name:' ',radius:\radiusAngle,strokeColor:'black',fillColor:'\couleur',fillOpacity:1});
#endif
}


#if defined TARGET_01CliquerHypotenuse
\text{scriptSoljs=hypo.setAttribute({strokeWidth:5,color:'green'})}
#endif

#if defined TARGET_02CliquerAdjacent
\text{scriptSoljs=cat1.setAttribute({strokeWidth:5,color:'green'})}
#endif

#if defined TARGET_03CliquerOppose
\text{scriptSoljs=cat2.setAttribute({strokeWidth:5,color:'green'})}
# endif


#if IDEM==1
\text{FigSol=slib(geo2D/jsxgraph jsxsol,\LCadre x \hCadre,\board_sol \scriptComjs \scriptSoljs)}
#else
\text{FigEnonce=slib(geo2D/jsxgraph jsxenonce,\LCadre x \hCadre,\board_enonce \scriptComjs)}
\text{FigSol=slib(geo2D/jsxgraph jsxsol,\LCadre x \hCadre,\board_sol \scriptComjs)}
#endif 




#if INDIC==2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURE HINT %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{FigIndic=slib(geo2D/jsxgraph jsxhint,\cCadreMax x \cCadreMax,
var brd500 = JXG.JSXGraph.initBoard('jsxhint', {showCopyright:false,showNavigation:false,axis:false,
 boundingbox: [-6,8,4,-2],grid:false});
A=brd500.create('point',[0,0],{name:'A',face:'x',size:3,color:'red',fixed:true,showInfobox:false,
label:{offset:[4,-8],color:'red'}});
B=brd500.create('point',[1.1557766,6.7010582],{name:'B',face:'x',size:3,color:'#0000FF',fixed:true,showInfobox:false,
label:{offset:[4,4],color:'#0000FF'}});
C=brd500.create('point',[-4.9272486,0.84983571],{name:'C',face:'x',size:3,color:'#993300',fixed:true,showInfobox:false,
label:{offset:[-12,-10],color:'#993300'}});
Hyp=brd500.create('point',[-3.2,5],{name:'\legend1',face:'x',size:0,color:'white',fixed:true,showInfobox:false,
label:{offset:[-15,-15],color:'#FF0000'}});
AdjB1=brd500.create('point',[1.5,5.1],{name:'\legend2',face:'x',size:0,color:'white',fixed:true,showInfobox:false,
label:{offset:[-15,-15],color:'#0000FF'}});
AdjB2=brd500.create('point',[1.5,4.4],{name:'\legend4 \(\widehat{ABC}\)',face:'x',size:0,color:'white',fixed:true,showInfobox:false,
label:{offset:[-15,-15],color:'#0000FF'}});
OppB1=brd500.create('point',[-4.2,0.4],{name:'\legend3 \legend4 \(\widehat{ABC}\)',face:'x',size:0,color:'white',
fixed:true,showInfobox:false,label:{offset:[-15,-15],color:'#0000FF'}});
OppC1=brd500.create('point',[1.2,2.8],{name:'\legend3',face:'x',size:0,color:'white',fixed:true,
showInfobox:false,label:{offset:[-15,-15],color:'#993300'}});
OppC2=brd500.create('point',[1.2,2.1],{name:'\legend4 \(\widehat{ACB}\)',face:'x',size:0,color:'white',fixed:true,
showInfobox:false,label:{offset:[-15,-15],color:'#993300'}});
AdjC1=brd500.create('point',[-4.2,-0.5],{name:'\legend2 \legend4 \(\widehat{ACB}\)',face:'x',size:0,color:'white',
fixed:true,showInfobox:false,label:{offset:[-15,-15],color:'#993300'}});

brd500.create('angle',[B,A,C],{name:' ',radius:0.5,strokeColor:'red',fillColor:'red',fillOpacity:0.8});
brd500.create('angle',[C,B,A],{name:' ',radius:0.7,strokeColor:'black',fillColor:'#0000FF',fillOpacity:1});
brd500.create('angle',[A,C,B],{name:' ',radius:0.7,strokeColor:'black',fillColor:'#993300',fillOpacity:1});
brd500.create('polygon',[A,B,C],{strokeColor: 'black',fillColor: 'white',highlightfillColor:'grey'});
)}
#endif

#if defined TARGET_10DeuxMesures || defined TARGET_11LigneTrigoUniteEtape || defined TARGET_12LigneTrigoUnite 
%%%%%%%%%%%%%%%%%%%%%%%% FIGURE VALEUR ARRONDIE BLOC SOLUTION %%%%%%%%%%%%%%%%%%%%%%%

\text{Fig3=slib(geo2D/jsxgraph jsxbox3,250x50,
var board3=JXG.JSXGraph.initBoard('jsxbox3',{boundingbox:[\Borne_Inf,1.5,\Borne_Sup,-1.5],
showCopyright:false,showNavigation:false,axis:false,grid:false});
var p1=board3.create('point',[\Val_Inf,0],
 {face:'+',fixed:true,withLabel:true,showInfobox:false,name:'\Val_Inf_t',label:{position:'top',offset:[-5,15]}});
var p2=board3.create('point',[\Val_Sup,0],
 {face:'+',fixed:true,showInfobox:false,withLabel:true,showInfobox:false,name:'\Val_Sup_t',label:{position:'top',offset:[-5,15]}});
var p1Inf=board3.create('point',[\Val_Inf-0.1,0],{face:'',fixed:true,showInfobox:false,withLabel:false});
var p2Sup=board3.create('point',[\Val_Sup+0.1,0],{face:'',fixed:true,showInfobox:false,withLabel:false});
var l1=board3.create('segment',[p1,p2]);
var l2=board3.create('segment',[p1Inf,p2Sup]);
var p3=board3.create('point',[\Val_Med,0],
 {face:'+',color:'red',fixed:true,showInfobox:false,withLabel:true,showInfobox:false,name:'\Val_Med_t',label:{position:'top',offset:[-15,15]}});
var p4F=board3.create('point',[\angle,0],{face:'x',color:'green',fixed:true,showInfobox:false,withLabel:true,showInfobox:false,name:'\angle_t',
label:{position:'bot',offset:[-10, -12]}});
var t=board3.create('ticks',[l1],{ticksDistance:0.5});
)
}

# if defined TARGET_10DeuxMesures

\text{Fig4=slib(geo2D/jsxgraph jsxbox4,250x50,
var board4=JXG.JSXGraph.initBoard('jsxbox4',{boundingbox:[\Borne_Inf2,1.5,\Borne_Sup2,-1.5],
showCopyright:false,showNavigation:false,axis:false,grid:false});
var p1=board4.create('point',[\Val_Inf2,0],
 {face:'+',fixed:true,withLabel:true,showInfobox:false,name:'\Val_Inf2_t',label:{position:'top',offset:[-5,15]}});
var p2=board4.create('point',[\Val_Sup2,0],
 {face:'+',fixed:true,showInfobox:false,withLabel:true,showInfobox:false,name:'\Val_Sup2_t',label:{position:'top',offset:[-5,15]}});
var p1Inf=board4.create('point',[\Val_Inf2-0.1,0],{face:'',fixed:true,showInfobox:false,withLabel:false});
var p2Sup=board4.create('point',[\Val_Sup2+0.1,0],{face:'',fixed:true,showInfobox:false,withLabel:false});
var l1=board4.create('segment',[p1,p2]);
var l2=board4.create('segment',[p1Inf,p2Sup]);
var p3=board4.create('point',[\Val_Med2,0],
 {face:'+',color:'red',fixed:true,showInfobox:false,withLabel:true,showInfobox:false,name:'\Val_Med2_t',label:{position:'top',offset:[-15,15]}});
var p4F=board4.create('point',[\angle2,0],{face:'x',color:'green',fixed:true,showInfobox:false,withLabel:true,showInfobox:false,name:'\angle2_t',
label:{position:'bot',offset:[-10, -12]}});
var t=board4.create('ticks',[l1],{ticksDistance:0.5});
)
}
# endif

#endif
