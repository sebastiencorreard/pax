target=Internonpar1 Internonpar2 Internonpar3 Internonpar4 Internonpar5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}
\matrix{nstep=(\ggb==1)?reply1}
\matrix{nstep=(\ggb==2)?reply2}
\nextstep{\nstep}
\integer{confoutil=(\confparm2==)?2:\confparm2}
#if defined TARGET_Internonpar1 || defined TARGET_Internonpar2 || defined TARGET_Internonpar3
# include "cubepts.inc"
#endif
#if defined TARGET_Internonpar4
# include "pyrampts.inc"
#endif
#if defined TARGET_Internonpar5
# include "tetrapts.inc"
#endif

%%%%% choix de l'arête
#if defined TARGET_Internonpar1
\integer{idte=randint(1..12)}
\matrix{plans=A,B,S,T,G,H,P,O
B,C,T,R,H,E,N,M
C,D,Q,R,E,F,O,P
A,D,S,R,G,F,N,M
E,F,S,T,C,D,L,K
F,G,T,Q,D,A,J,I
G,H,Q,R,A,B,K,L
E,H,S,R,C,B,J,I
A,E,N,J,G,C,P,L
B,F,O,K,H,D,N,J
C,G,O,K,E,A,M,I
D,H,P,L,F,B,M,I
}
\integer{j=randint(1..3)}
\text{donnees=slib(draw/repere 400,400,0,-5,15,-5,15,1,1,black,grey)}
#endif
#if defined TARGET_Internonpar2
\integer{idte=randint(1..12)}
\matrix{plans=Q,R,C,D,L,K,G,H,P,O
K,L,S,T,R,Q,F,E,G,H
S,T,O,P,K,L,E,F,A,B
O,P,R,Q,S,T,B,A,C,D
Q,T,C,B,G,F,N,M,J,I
M,N,C,B,D,A,S,R,T,Q
R,S,H,E,D,A,N,M,J,I
I,J,H,E,G,F,T,Q,S,R
I,M,H,D,G,C,O,K,P,L
L,P,H,D,E,A,N,J,M,I
J,N,E,A,F,B,O,K,P,L
K,O,G,C,F,B,N,J,M,I
}
\integer{j=randint(1..4)}
\text{donnees=slib(draw/repere 400,400,0,-5,15,-5,15,1,1,black,grey)}
#endif
#if defined TARGET_Internonpar3
\integer{idte=randint(1..12)}
\matrix{plans=F,H,K,I,J,L
D,B,P,N,M,O
E,G,J,K,L,I
A,C,N,O,P,M
A,H,P,R,S,L
D,E,R,L,P,S
B,G,T,K,O,Q
C,F,Q,K,O,T
A,F,N,T,S,J
B,E,N,S,T,J
D,G,M,Q,R,I
C,H,M,R,Q,I
}
\integer{j=randint(1..2)}
\text{donnees=slib(draw/repere 400,400,0,-5,15,-5,15,1,1,black,grey)}
#endif
#if defined TARGET_Internonpar4
\integer{idte=randint(1..12)}
\matrix{plans=N,O,J,I
A,D,O,N
I,J,O,N
I,J,P,M
B,C,P,M
P,M,I,J
M,N,L,K
C,D,M,N
L,K,M,N
P,O,L,K
L,K,P,O
A,B,O,P
}
\integer{j=1}
\text{donnees=slib(draw/repere 400,400,0,-5,15,-5,15,1,1,black,grey)}
#endif

#if defined TARGET_Internonpar5
\integer{idte=randint(1..8)}
\matrix{plans=M,P,T,K,S,L
N,O,T,K,S,L
I,K,Q,O,R,P
S,L,N,O,M,P
O,Q,K,I,L,J
P,R,K,I,L,J
N,Q,T,J,S,I
M,R,T,J,S,I
}
\integer{j=randint(1..2)}
\text{donnees=slib(draw/repere 400,400,0,-3,30,-3,20,1,1,black,grey)}
#endif
\text{pt1=\plans[\idte;1]}
\text{pt2=\plans[\idte;2]}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{iw=randint(1,2)}
\text{pt3=\plans[\idte;2*\j+\iw]}
\integer{indpt3=position(\pt3,\listpoint)}
\if{\iw=1}{
\text{dessin=
linewidth 3
polyline red,\pt[\indpt1;1],\pt[\indpt1;2],\pt[\indpt2;1],\pt[\indpt2;2],\pt[\indpt3;1],\pt[\indpt3;2]
}
\text{pt4=\plans[\idte;2*\j+2]}
  }{
\text{dessin=
linewidth 3
polyline red,\pt[\indpt2;1],\pt[\indpt2;2],\pt[\indpt1;1],\pt[\indpt1;2],\pt[\indpt3;1],\pt[\indpt3;2]
}
\text{pt4=\plans[\idte;2*\j+1]}
  }
\integer{indpt4=position(\pt4,\listpoint)}
\rational{Xx=\pt[\indpt4;1]}
\rational{Xy=\pt[\indpt4;2]}

\text{tmp=row(1,\donnees)}
%%%%%coordonnéées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%%%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}


\integer{fxm=\Ox+\Xx*\ex-\ex/3}
\integer{fxp=\Ox+\Xx*\ex+\ex/3}
\integer{fym=\Oy+\Xy*\ey-\ey/3}
\integer{fyp=\Oy+\Xy*\ey+\ey/3}

\text{dqs=du quatrième sommet de ce quadrilatère.}
\text{cons=Cliquer à l'emplacement \dqs}
#if defined TARGET_Internonpar1
#include "cubedraw.inc"
#endif
#if defined TARGET_Internonpar2
#include "cubedraw.inc"
#endif
#if defined TARGET_Internonpar3
#include "cubedraw.inc"
#endif

\if{\ggb==2}{
  \rational{pg=(\confoutil==1)?0.2:0.00001}
  \text{siw=(\iw==1)?\pt2,\pt3:\pt1,\pt3}
  \text{ssiw=(\iw==1)?\pt1,\pt2:\pt1,\pt2}
  \text{lp_outil=showToolBar=true;}
  \text{lp_outil=(\confoutil==1)?\lp_outil
customToolBar="0||1";:\lp_outil
customToolBar="0||5||2||3";}
  \text{lp_enon=aa=Segment(\ssiw)
SetColor[aa,red]
ShowLabel[aa, false]
bb=Segment(\siw)
SetColor[bb,red]
ShowLabel[bb, false]}
  \text{listlab=a,b,c,d,e,f,g,h,i,j,k,l}
  \text{lp_lab=}
  \for{i in \listlab}{
    \text{t=ShowLabel[\i, false]}
    \text{lp_lab=wims(append line \t to \lp_lab)}
  }
}
#if (defined TARGET_Internonpar1 || defined TARGET_Internonpar2 || defined TARGET_Internonpar3 )
#include "ggbc_milieu.inc"
#include "ggbc.inc"
\text{ptenon=U}
#endif
#if defined TARGET_Internonpar4
#include "pyramdraw.inc"
#include "ggbp_milieu.inc"
#include "ggbp.inc"
\text{ptenon=E}
#endif
#if defined TARGET_Internonpar5
#include "tetradraw.inc"
#include "ggbt.inc"
\text{ptenon=E}
#endif
\text{image=draw(400,400
\cadre
)}

\if{\ggb==2}{
\integer{letp=position(\pt4,\listpoint)}
\matrix{repp=\coordg[\indpt4;]}
\real{rep1=\repp[1;1]}
\real{rep2=\repp[1;2]}
\real{rep3=\repp[1;3]}
\text{embopt=,800 x 800
\fig_ggb}
\text{cons=Placer le point \(\ptenon\) \dqs <div class="wims_instruction">}
\text{cons=(\confoutil==1)?\cons Pour construire le point, cliquer sur un segment en dehors des points puis
 faire glisser le point.:\cons Construire des droites pour que le point se trouve à l'intersection de celles-ci.}
 \text{cons=\cons </div>}
}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Debug :iw=\iw||j=\j
<br>pt1=\pt1||pt2=\pt2||pt3=\pt3||pt4=\pt4|\rep1;\rep2;\rep3
<br>repp=\repp
<br>coordg=\coordg
<div class="wimscenter"><img src="\image"></div>
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\statement{
  \objet. \tpoints.
<p>
  On considère le plan <span style="color:red">(\pt1\pt2\pt3)</span>
  et on s'intéresse à son intersection avec ABCDEFGH: c'est un quadrilatère.
</p>
  \cons
<div class="wimscenter">
\if{\ggb==1}{\embed{reply1}}
\if{\ggb==2}{\embed{reply2 \embopt}}
</div>
}
\answer{X}{\image;rectangle,\fxm,\fym,\fxp,\fyp}{type=coord}

\answer{}{n,abs(x_\ptenon-(\rep1))<0.2,L'abscisse du point \(\ptenon\) est bien placée;
n,abs(y_\ptenon-(\rep2))<0.2,L'ordonnée du point \(\ptenon\) est bien placée;
n,abs(z_\ptenon-(\rep3))<0.2,La cote du point \(\ptenon\) est bien placée;}{type=geogebra}{option=max=100 extra=yes output=coord feedbackscript=Correction}


\text{nstep=(\step==2)?}
\feedback{\ggb==2}{
<script>
function  Correction(){ggbApplet0.evalCommand("Plane(\pt1,\pt2,\pt3)");}
</script>}
