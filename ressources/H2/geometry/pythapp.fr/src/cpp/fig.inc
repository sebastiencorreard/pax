%%%%%%   FIGURES   %%%%%%
#if defined TARGET_01a || defined TARGET_01b ||  defined TARGET_02a || defined TARGET_02b ||   defined TARGET_03a || defined TARGET_03b ||  defined TARGET_04a || defined TARGET_04b ||   defined TARGET_05a || defined TARGET_05b || defined TARGET_09   

%%% Couleurs
\integer{red=randint(0..255)}
\integer{green=randint(0..255)}
\integer{blue=randint(0..255)}
\text{couleur=rgb(\red,\green,\blue)
}

  #if defined TARGET_01a || defined TARGET_01b || defined TARGET_09
    %% Figure
    %%% Les points
    \integer{x_B=randint(1..3)}
    \integer{y_C=randint(1..3)}
    \real{angleRot=random(0..6.28)}
    \real{angleRot2=Pi/2+\angleRot}
    \real{x_B2=\x_B*cos(\angleRot)}
    \real{y_B2=\x_B*sin(\angleRot)}
    \real{x_C2=\y_C*cos(\angleRot2)}
    \real{y_C2=\y_C*sin(\angleRot2)}
    \real{radiusAngle=min(0.3,min(\x_B/10,\y_C/10))
    }
    \real{xMin=min(min(0,\x_B2),\x_C2)-1}
    \real{xMax=max(max(0,\x_B2),\x_C2)+1}
    \real{yMin=min(min(0,\y_B2),\y_C2)-1}
    \real{yMax=max(max(0,\y_B2),\y_C2)+1}
  #endif

  #if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b ||  TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
    %% Figure
    %%% Les points
    \integer{dispo=randint(1..4)}
    \if{\dispo==1}{
    \real{x_B=sqrt(\A_B)}
    \real{y_C=sqrt(\A_C)}
    \real{x_B1=\x_B}
    \real{y_B1=-1*\x_B}
    \real{y_B2=-1*\x_B}
    \real{x_C1=-1*\y_C}
    \real{y_C1=\y_C}
    \real{x_C2=-1*\y_C}
    \real{x_D1=\y_C+\x_B}
    \real{y_D1=\x_B}
    \real{x_D2=\y_C}
    \real{y_D2=\x_B+\y_C}
    \real{radiusAngleX=min(1,min(\x_B/6,\y_C/6))}
    \real{radiusAngleY=\radiusAngleX}
    \real{xMin=-1*\y_C-1.5}
    \real{xMax=\x_D1+1.5}
    \real{yMin=-1*\x_B-2}
    \real{yMax=\y_D2+2}
    }
    {\if{\dispo==2}{
    \real{x_B=-1*sqrt(\A_B)}
    \real{y_C=sqrt(\A_C)}
    \real{x_B1=\x_B}
    \real{y_B1=\x_B}
    \real{y_B2=\x_B}
    \real{x_C1=\y_C}
    \real{y_C1=\y_C}
    \real{x_C2=\y_C}
    \real{x_D1=-1*\y_C+\x_B}
    \real{y_D1=-1*\x_B}
    \real{x_D2=-1*\y_C}
    \real{y_D2=\y_C-\x_B}
    \real{radiusAngleX=-1*min(1,min(sqrt(\A_B)/6,\y_C/6))}
    \real{radiusAngleY=-1*\radiusAngleX}
    \real{xMin=\x_D1-1.5}
    \real{xMax=\x_C1+1.5}
    \real{yMin=\y_B1-2}
    \real{yMax=\y_D2+2}
    }
    {\if{\dispo==3}{
    \real{x_B=sqrt(\A_B)}
    \real{y_C=-1*sqrt(\A_C)}
    \real{x_B1=\x_B}
    \real{y_B1=\x_B}
    \real{y_B2=\x_B}
    \real{x_C1=\y_C}
    \real{y_C1=\y_C}
    \real{x_C2=\y_C}
    \real{x_D1=-1*\y_C+\x_B}
    \real{y_D1=-1*\x_B}
    \real{x_D2=-1*\y_C}
    \real{y_D2=-1*\x_B+\y_C}
    \real{radiusAngleX=min(1,min(\x_B/6,sqrt(\A_C)/6))}
    \real{radiusAngleY=-1*\radiusAngleX}
    \real{xMin=\y_C-1.5}
    \real{xMax=\x_D1+1.5}
    \real{yMin=\y_D2-2}
    \real{yMax=\x_B+2}
    }
    {\real{x_B=-1*sqrt(\A_B)}
    \real{y_C=-1*sqrt(\A_C)}
    \real{x_B1=\x_B}
    \real{y_B1=-1*\x_B}
    \real{y_B2=-1*\x_B}
    \real{x_C1=-1*\y_C}
    \real{y_C1=\y_C}
    \real{x_C2=-1*\y_C}
    \real{x_D1=\y_C+\x_B}
    \real{y_D1=\x_B}
    \real{x_D2=\y_C}
    \real{y_D2=\x_B+\y_C}
    \real{radiusAngleX=-1*min(1,min(sqrt(\A_B)/6,sqrt(\A_C)/6))}
    \real{radiusAngleY=\radiusAngleX}
    \real{xMin=\x_D1-1.5}
    \real{xMax=\x_C1+1.5}
    \real{yMin=\y_D2-2}
    \real{yMax=\y_B1+2}
    }
    }
    }
    \real{x_AireB=\x_B1/2}
    \real{y_AireB=\y_B1/2}
    \real{x_AireC=\x_C1/2}
    \real{y_AireC=\y_C1/2}
    \real{x_AireHyp=\x_D1/2}
    \real{y_AireHyp=(\y_C+\y_D1)/2}
  #endif

%%% Le cadre 
\integer{LCadre=(\xMax-\xMin)}
\integer{hCadre=(\yMax-\yMin)}

%%% Options JSXGraph
\text{options=
  {showCopyright : false,axis:false,
   boundingbox: [\xMin,\yMax,\xMax,\yMin],
   grid:false,
   keepaspectratio : true,
   zoom: {factorX: 1.25,factorY: 1.25,wheel: true,needShift: true,eps: 0.001},
   pan:{
    needShift: false,
    enabled: true,
    needTwoFingers: true,
    pinchHorizontal: true,
    pinchVertical: true,
    pinchSensitivity: 7
   }
  }
}
  #if defined TARGET_01a || defined TARGET_01b || defined TARGET_09
    \text{constructions=
    A=brd.create('point',[0,0],{name:'\Sommet',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{autoPosition: true,fixed: false}});
    B=brd.create('point',[\x_B2,\y_B2],{name:'\Hyp[1]',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{autoPosition: true,fixed: false}});
    C=brd.create('point',[\x_C2,\y_C2],{name:'\Hyp[2]',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{autoPosition: true,fixed: false}});
    brd.create('angle',[B,A,C],{name:' ',radius:\radiusAngle,strokeColor:'black',fillColor:'red',fillOpacity:0.8});
    brd.create('polygon',[A,B,C],{strokeColor: 'black',fillColor: '\couleur',highlightfillColor:'\couleur'})
    }
  #endif 

  #if defined TARGET_02a || defined TARGET_02b || defined TARGET_03a || defined TARGET_03b ||  TARGET_04a || defined TARGET_04b || defined TARGET_05a || defined TARGET_05b
    \text{constructions=
    A=brd.create('point',[0,0],{name:'\Sommet',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{autoPosition: true,fixed: false}});
    B=brd.create('point',[\x_B,0],{name:'\Hyp[1]',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{autoPosition: true,fixed: false}});
    C=brd.create('point',[0,\y_C],{name:'\Hyp[2]',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false,label:{autoPosition: true,fixed: false}});
    a1=brd.create('point',[\radiusAngleX,0],{name:'',face:'x',size:0,color:'red',fixed:true,showInfobox:false});
    a2=brd.create('point',[0,\radiusAngleY],{name:'',face:'x',size:0,color:'red',fixed:true,showInfobox:false});
    a3=brd.create('point',[\radiusAngleX,\radiusAngleY],{name:'',face:'x',size:0,color:'red',fixed:true,showInfobox:false});
    adroit=brd.create('polygon',[A,a1,a3,a2],{strokeColor: 'black',fillColor: 'red',fillOpacity:1,highlightfillColor:'red'});
    t=brd.create('polygon',[A,B,C],{strokeColor: 'black',fillColor: 'white',fillOpacity:0,highlightfillColor:'white'});
    B1=brd.create('point',[\x_B,\y_B1],{name:'',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false});
    B2=brd.create('point',[0,\y_B2],{name:'',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false});
    cB=brd.create('polygon',[A,B,B1,B2],{strokeColor: 'black',fillColor: '\couleur',fillOpacity:0.2,highlightfillColor:'\couleur'});
    C1=brd.create('point',[\x_C1,\y_C],{name:'',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false});
    C2=brd.create('point',[\x_C2,0],{name:'',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false});
    cC=brd.create('polygon',[A,C,C1,C2],{strokeColor: 'black',fillColor: '\couleur',fillOpacity:0.2,highlightfillColor:'\couleur'});
    D1=brd.create('point',[\x_D1,\y_D1],{name:'',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false});
    D2=brd.create('point',[\x_D2,\y_D2],{name:'',face:'x',size:3,color:'\couleur',fixed:true,showInfobox:false});
    cD=brd.create('polygon',[C,B,D1,D2],{strokeColor: 'black',fillColor: '\couleur',fillOpacity:0.5,highlightfillColor:'\couleur'});
    Pt_AireB=brd.create('point',[\x_AireB,\y_AireB],{name:'\A_B',face:'x',size:0,fixed:true,showInfobox:false,color:'\couleur',strokeOpacity:0,label:{position:'top',offset:[-5,0]}});
    #if defined TARGET_02a || defined TARGET_02b || defined TARGET_04a || defined TARGET_04b 
      Pt_AireC=brd.create('point',[\x_AireC,\y_AireC],{name:'\A_C',face:'x',size:0,fixed:true,showInfobox:false,color:'\couleur',strokeOpacity:0,label:{position:'top',offset:[-5,0]}});
    #endif
    #if defined TARGET_03a || defined TARGET_03b || defined TARGET_05a || defined TARGET_05b 
      Pt_AireHyp=brd.create('point',[\x_AireHyp,\y_AireHyp],{name:'\A_Hyp',face:'x',size:0,fixed:true,showInfobox:false,color:'\couleur',strokeOpacity:0,label:{position:'top',offset:[-5,0]}});
    #endif 
    }
  #endif
    
  #if defined TARGET_01a || defined TARGET_02a || defined TARGET_03a || defined TARGET_04a || defined TARGET_05a || defined TARGET_09
    %%% Le dessin énoncé
    \text{fig_enonce=slib(geo2D/jsxgraph enonce brd,[\LCadre x \hCadre,center min=200px max=300px scroll],var brd = JXG.JSXGraph.initBoard('enonce',\options); \constructions)}
  #endif
  #if defined TARGET_01a || defined TARGET_01b ||  defined TARGET_02a || defined TARGET_02b ||   defined TARGET_03a || defined TARGET_03b ||  defined TARGET_04a || defined TARGET_04b ||   defined TARGET_05a || defined TARGET_05b
    %%% Le dessin solution
    \text{fig_sol=slib(geo2D/jsxgraph sol brd,[\LCadre x \hCadre,center min=200px max=300px scroll],var brd = JXG.JSXGraph.initBoard('sol',\options); \constructions)}
  #endif
#endif
