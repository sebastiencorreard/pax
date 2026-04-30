%%%%%%%%%%%%%%%%% APPLET GEOGEBRA %%%%%%%%%%%%%%%%%%%

#if GGB==1
%%% APPEL ET CONSTRUCTION AVANT STATEMENT %%%

\text{appletoption=
\sizew x \sizeh
file=vector.ggb
language=\lang
showMenuBar=false
showToolBar=true
enableRightClick=false
enableLabelDrags=true
useBrowserForJS=true
customToolBar=0|40|41|42
borderColor=white
setPointCapture(1, 2)
setCoordSystem(-1*\maxi,\maxi,-1*\maxi,\maxi)
\A=(\xA,\yA)
setFixed('\A',true)
SetColor[\A,black]
SetPointSize(\A,1)
\B=(\xB,\yB)
setFixed('\B',true)
SetColor[\B,black]
SetPointStyle(\B,3)
SetPointSize(\B,1)
\C=(\xC,\yC)
setFixed('\C',true)
SetColor[\C,black]
SetPointSize(\C,1)
\D=(\xD,\yD)
setFixed('\D',false)
SetColor[\D,\borderColor]
SetPointSize(\D,3)
SetPointStyle(\D,2)
u=Vector(\A,\B)
v=Vector(\C,\D)
SetColor[u,black]
SetColor[v,\borderColor]
setVisible('tableau',false)
setVisible('k',false)
}
# if !defined TARGET_06memenorme && !defined TARGET_07memenormenoncoli
\if{\conf3=1}{\text{appletoption=\appletoption
d_1=Line(\A,\B)
d_2=Line(\C,\D)
SetLineStyle(d_1,3)
SetLineStyle(d_2,3)
SetColor[d_1,Gray]
SetColor[d_2,Gray]
}
}
# endif
#endif

#if GGB==2
%%% FEEDBACKSCRIPT %%%
\text{script_curseur=
ggbApplet0.evalCommand("k=Slider(\slide_range)");
ggbApplet0.evalCommand("ShowLabel(k,false)");
ggbApplet0.evalCommand("SetVisible('k',false)");
}
\text{script_vec_v=
ggbApplet0.evalCommand("SetLineStyle(v,2)");
ggbApplet0.evalCommand("SetColor(v,\borderColor)");
}

\text{script_ptD=
ggbApplet0.evalCommand("ShowLabel[\D,false]");
ggbApplet0.evalCommand("SetColor(\D,\borderColor)");
ggbApplet0.evalCommand("SetPointStyle(\D,10)");
ggbApplet0.evalCommand("SetPointSize(\D,1)");
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose
ggbApplet0.evalCommand("pgcd=\pgcd");
ggbApplet0.evalCommand("coef=k*(1/pgcd)");
ggbApplet0.evalCommand("D_s=If(k<>0,\C+k*(1/\pgcd)*u)");
#endif
#if defined TARGET_04egaux || defined TARGET_05oppose
# if defined TARGET_04egaux
ggbApplet0.evalCommand("D_s=\C+Vector(\A,\B)");
ggbApplet0.evalCommand("para1=Segment(\A,\C)");
ggbApplet0.evalCommand("para2=Segment(\B,D_s)");
# endif
# if defined TARGET_05oppose
ggbApplet0.evalCommand("D_s=\C+Vector(\B,\A)");
ggbApplet0.evalCommand("para1=Segment(\A,D_s)");
ggbApplet0.evalCommand("para2=Segment(\B,\C)");
# endif
ggbApplet0.evalCommand("SetLineStyle(para1,3)");
ggbApplet0.evalCommand("SetLineStyle(para2,3)");
ggbApplet0.evalCommand('SetLineThickness[para1,7]');
ggbApplet0.evalCommand('SetLineThickness[para2,7]');
ggbApplet0.evalCommand('SetColor[para1,"orange"]');
ggbApplet0.evalCommand('SetColor[para2,"orange"]');
#endif
#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
ggbApplet0.evalCommand("seg3=Segment(\A,(x(\B),y(\A)))");
ggbApplet0.evalCommand("seg4=Segment((x(\B),y(\A)),\B)");
ggbApplet0.evalCommand("SetLineStyle(seg3,1)");
ggbApplet0.evalCommand("SetLineStyle(seg4,3)");
ggbApplet0.evalCommand('SetColor[seg3,"orange"]');
ggbApplet0.evalCommand('SetColor[seg4,"blue"]');
ggbApplet0.evalCommand('SetLineThickness[seg3,7]');
ggbApplet0.evalCommand('SetLineThickness[seg4,7]');
ggbApplet0.evalCommand("ListeSol={\sol}");
ggbApplet0.evalCommand("D_s=\C+Vector(Element(ListeSol,k))");
ggbApplet0.evalCommand("seg1=Segment(\C,(x(D_s),y(\C)))");
ggbApplet0.evalCommand("seg2=Segment((x(D_s),y(\C)),D_s)");
ggbApplet0.evalCommand('SetLineThickness[seg1,7]');
ggbApplet0.evalCommand('SetLineThickness[seg2,7]');
ggbApplet0.evalCommand('SetColor(seg1,If(seg1==seg3,"orange","blue"))');
ggbApplet0.evalCommand('SetColor(seg2,If(seg2==seg4,"blue","orange"))');
ggbApplet0.evalCommand("SetLineStyle(seg1,If(seg1==seg3,1,3))");
ggbApplet0.evalCommand("SetLineStyle(seg2,If(seg2==seg4,3,1))");
#endif
ggbApplet0.evalCommand('SetColor[D_s,"#008000"]');
ggbApplet0.evalCommand("SetPointStyle(D_s,10)");
ggbApplet0.evalCommand("SetPointSize(D_s,1)");
ggbApplet0.evalCommand('SetCaption(D_s,"\D")');
ggbApplet0.evalCommand("SetLabelStyle(D_s,3)");
ggbApplet0.evalCommand("w=Vector(\C,D_s)");
ggbApplet0.evalCommand('SetColor[w,"#008000"]');
ggbApplet0.evalCommand('DisplayRep=Checkbox("\display",{\D,v})');
#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose || defined TARGET_04egaux || defined TARGET_05oppose
ggbApplet0.evalCommand('d_1=Line(\A,\B)');
ggbApplet0.evalCommand('d_2=Line(\C,u)');
ggbApplet0.evalCommand("SetLineStyle(d_1,3)");
ggbApplet0.evalCommand("SetLineStyle(d_2,3)");
ggbApplet0.evalCommand('SetColor[d_1,"Gray"]');
ggbApplet0.evalCommand('SetColor[d_2,"Gray"]');
#endif
var tempo=setInterval(function(){UpdateConstruct()}, 100);
document.getElementById("ggbApplet0").onmouseleave = function() {
clearInterval(tempo);
};
document.getElementById("ggbApplet0").onmouseenter = function() {
var tempo=setInterval(function(){UpdateConstruct()}, 100);
};
function UpdateConstruct(){
 ggbApplet0.evalCommand('UpdateConstruction[]');
#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
 ggbApplet0.evalCommand('SetColor(seg1,If(seg1==seg3,"orange","blue"))');
 ggbApplet0.evalCommand('SetColor(seg2,If(seg2==seg4,"blue","orange"))');
 ggbApplet0.evalCommand("SetLineStyle(seg1,If(seg1==seg3,1,3))");
 ggbApplet0.evalCommand("SetLineStyle(seg2,If(seg2==seg4,3,1))");
#endif
 }
}

#endif
