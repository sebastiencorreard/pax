target=trans3im trans3ant

#include "author.inc"
#include "lang_titles.inc"
\css{<style>
.ans {text-decoration:underline;font-weight:bold;}
</style>
}
\keywords{translation}

\matrix{nom=A,B,C,D
E,F,G,H
M,N,R,P}
\text{don=randrow(\nom)}
\text{tdon=\don}
\text{don=shuffle(\don)}
\text{A=\don[1]}
\text{B=\don[2]}
\text{C=\don[3]}
\text{D=\don[4]}
\integer{xA=random(1..5)}
\integer{yA=random(1..5)}
\integer{xB=random(-5..-1)}
\integer{yB=random(1..5)}
\integer{xC=random(-5..-1)}
\integer{yC=random(-5..-1)}

%%Eviter les points A,B et C alignés
\integer{tmp=(\xB-(\xA))*(\yC-(\yA))-(\yB-(\yA))*(\xC-(\xA))}
\if{\tmp=0}{
 \integer{xA=1}
 \integer{yA=-1}
 \integer{xB=3}
 \integer{yB=5}
 \integer{xC=-2}
 \integer{yC=-2}
}

#include "lang.inc"

%%Matrice de données
\matrix{don=\A \name_mapsto \B,\xB-\xA,\yB-\yA,\A \B \D \C,\A,\B,\xA,\yA,\xB,\yB,\(\A\) \name_mapsto \(\B\)
\B \name_mapsto \A,\xA-\xB,\yA-\yB,\B \A \D \C,\B,\A,\xB,\yB,\xA,\yA,\(\B\) \name_mapsto \(\A\)}

\integer{choix=randint(2)}
\if{\choix=1}{\text{don=\don[1;]}
              \text{pt3=\D}
              \integer{pt3x=\xD}
              \integer{pt3y=\yD}
              \text{pt4=\C}   
              \integer{pt4x=\xC}
              \integer{pt4y=\yC}         
             }{
             \text{don=\don[2;]}
             \text{pt3=\C}
             \text{pt4=\D}
             }
\text{dep=\don[5]}
\text{arr=\don[6]}              
\text{vect=\don[1]}
\integer{Vx=\don[2]}
\integer{Vy=\don[3]}
\integer{xD=\xC+\Vx}
\integer{yD=\yC+\Vy}
\integer{badx1=\xC-\Vx}
\integer{bady1=\yC-\Vy}
\integer{badx2=\xC+2*\Vx}
\integer{bady2=\yC+2*\Vy}
\if{\choix=1}{\text{pt3=\D}
              \integer{pt3x=\xD}
              \integer{pt3y=\yD}
              \text{pt4=\C}   
              \integer{pt4x=\xC}
              \integer{pt4y=\yC}         
             }{
             \text{pt3=\C}
             \integer{pt3x=\xC}
             \integer{pt3y=\yC}     
             \text{pt4=\D}
             \integer{pt4x=\xD}
             \integer{pt4y=\yD}
             }
             
\text{para=\don[4]}

\integer{xdep=0}
\integer{ydep=0}

#if defined TARGET_trans3im
\text{enonce=\name_statement2[1], \name_statement2[2] \(\D\) \name_statement2[3] \(\C\) \name_statement2[4] \don[11].}
\if{\xD=0 and \yD=0}{\integer{xdep=\xD+randint(1..5)}
                     \integer{ydep=\yD+randint(1..5)}
                     }
#endif
#if defined TARGET_trans3ant
\text{enonce=\name_statement2[1], \name_statement2[2] \(\C\) \name_statement2[3] \(\D\) \name_statement2[4] \don[11].}
\if{\xC=0 and \yC=0}{\integer{xdep=\xC+randint(1..5)}
                     \integer{ydep=\yC+randint(1..5)}
                     }
#endif                     
%%Dessin JSXGRAPH
#if defined TARGET_trans3im                  
\text{script=var brd = JXG.JSXGraph.initBoard('jxgbox', {
 axis:false,boundingbox: [-10, 10, 10, -10], grid:true,showCopyright:false}); 
var ptdep = brd.create('point', [\don[7],\don[8]], {name: "\dep",fixed:true,face:'cross',showInfobox:false});
var ptarr = brd.create('point', [\don[9],\don[10]], {name: "\arr",fixed:true,face:'cross',showInfobox:false});
var C = brd.create('point', [\xC,\yC], {name: "\C",fixed:true,face:'cross',showInfobox:false});
var deparr = brd.create('arrow', [ptdep, ptarr]);
jxgbox_rep1 = brd.create('point',jxgbox_var1,{name:"\D",showInfoBox:false,snapToGrid:true} );}
#endif
#if defined TARGET_trans3ant                  
\text{script= var brd = JXG.JSXGraph.initBoard('jxgbox', {
 axis:false,boundingbox: [-10, 10, 10, -10], grid:true,showCopyright:false});
var ptdep = brd.create('point', [\don[7],\don[8]], {name: "\dep",fixed:true,face:'cross',showInfobox:false});
var ptarr = brd.create('point', [\don[9],\don[10]], {name: "\arr",fixed:true,face:'cross',showInfobox:false});
var D = brd.create('point', [\xD,\yD], {name: "\D",fixed:true,face:'cross',showInfobox:false});
var deparr = brd.create('arrow', [ptdep, ptarr]);
jxgbox_rep1 = brd.create('point',jxgbox_var1,{name:"\C",showInfoBox:false,snapToGrid:true} );}
#endif
%%Fin du dessin avec jsxgraph

#include "lang2.inc"

\statement{\name_statement1 \(\tdon[1]\),\(\tdon[2]\), \(\tdon[3]\) \name_and \(\tdon[4]\).
<p>\enonce
\embed{r1,400x400
jxgbox brd [responsive left min=300px max=600px]
\script
jxgbox_var1=[\xdep,\ydep]
  }
}

\answer{}{\rep}{type=jsxgraph}{option=precision=10}
\text{rep=\reply1}

#if defined TARGET_trans3im
\real{test1=abs(\rep[1]-\xD)}
\real{test2=abs(\rep[2]-\yD)}
#endif
#if defined TARGET_trans3ant
\real{test1=abs(\rep[1]-\xC)}
\real{test2=abs(\rep[2]-\yC)}
#endif

\condition{\name_condition}{\test1<0.1 and \test2<0.1}
\hint{\name_hint}

%%Bloc Solution en cas d'erreur seulement
\if{\choix=1}{
\text{scriptsol=var brd2 = JXG.JSXGraph.initBoard('jxgbox2', {
axis:false,boundingbox: [-10, 10, 10, -10], grid:true,showCopyright:false});
var A = brd2.create('point', [\xA,\yA], {name: "\A",fixed:true,face:'cross',showInfobox:false});
var B = brd2.create('point', [\xB,\yB], {name: "\B",fixed:true,face:'cross',showInfobox:false});
var C = brd2.create('point', [\xC,\yC], {name: "\C",fixed:true,face:'cross',showInfobox:false});
var D = brd2.create('point', [\xD,\yD], {name: "\D",fixed:true,face:'cross',showInfobox:false});
var E = brd2.create('point', [\rep[1],\rep[2]], {name: "\name_yourreply",fixed:true,face:'cross',color:'black',showInfobox:false});
var deparr = brd2.create('arrow', [A,B]);
var CD = brd2.create('arrow', [C, D]);
var BC = brd2.create('segment', [B,D], {name: "",fixed:true,color:'green',dash:2,showInfobox:false});
var DA = brd2.create('segment', [A,C], {name: "",fixed:true,color:'green',dash:2,showInfobox:false});}
          }{
\text{scriptsol=var brd2 = JXG.JSXGraph.initBoard('jxgbox2', {
axis:false,boundingbox: [-10, 10, 10, -10], grid:true,showCopyright:false}); 
var A = brd2.create('point', [\xA,\yA], {name: "\A",fixed:true,face:'cross',showInfobox:false});
var B = brd2.create('point', [\xB,\yB], {name: "\B",fixed:true,face:'cross',showInfobox:false});
var C = brd2.create('point', [\xC,\yC], {name: "\C",fixed:true,face:'cross',showInfobox:false});
var D = brd2.create('point', [\xD,\yD], {name: "\D",fixed:true,face:'cross',showInfobox:false});
var E = brd2.create('point', [\rep[1],\rep[2]], {name: "\name_yourreply",fixed:true,face:'cross',color:'black',showInfobox:false});
var deparr = brd2.create('arrow', [B,A]);
var CD = brd2.create('arrow', [C, D]);
var BC = brd2.create('segment', [B,C], {name: "",fixed:true,color:'green',dash:2,showInfobox:false});
var DA = brd2.create('segment', [A,D], {name: "",fixed:true,color:'green',dash:2,showInfobox:false});}         
}
\text{image2=slib(geo2D/jsxgraph jxgbox2 brd2,[250x250, min=250px max=350px left],\scriptsol)}
\feedback{\sc_reply1<1}{\name_solution
\image2
}
