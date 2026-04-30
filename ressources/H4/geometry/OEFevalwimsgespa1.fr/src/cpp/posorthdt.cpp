target=posorthdte1 posorthdte2 posorthdte3
\text{lstposrel=orthogonales, non orthogonales}

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}

#if defined TARGET_posorthdte1
  \integer{n2=8}
  \integer{n1=1}
#endif
#if defined TARGET_posorthdte2
  \integer{n2=20}
  \integer{n1=1}
#endif
#if defined TARGET_posorthdte3
  \integer{n2=20}
  \integer{n1=9}
#endif

#include "cubepts.inc"

%%%%% Choix des droites
\integer{facedeb=randint(1..6)}
\integer{facefin=randint(1..6)}
\text{lstpt=}
\for{ ii = \n1 to \n2}{
  \if {\facedeb isitemof \faces[\ii;]}{
     \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle (\lstpt)}
%%%%%text{lstpt=H,C}
\text{pt1 = \lstpt[1]}
\text{pt2 = \lstpt[2]}
\text{lstpt=}
\for{ ii = \n1 to \n2}{
  \if {\facefin isitemof \faces[\ii;]}{
    \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle(\lstpt)}
%%%%%text{lstpt=N,D}
\text{pt3 = \lstpt[1]}
\text{pt4 = \lstpt[2]}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpt3=position(\pt3,\listpoint)}
\integer{indpt4=position(\pt4,\listpoint)}
\text{dessin=
 segment \pt[\indpt1;],\pt[\indpt2;],red
 segment \pt[\indpt3;],\pt[\indpt4;],blue
}

%%%%% détermination des bonnes réponses
\integer{goodrep=0}
\rational{vect1x =  \PT[\indpt1;1]-(\PT[\indpt2;1])}
\rational{vect2x =  \PT[\indpt3;1]-(\PT[\indpt4;1])}
\rational{vect1y =  \PT[\indpt1;2]-(\PT[\indpt2;2])}
\rational{vect2y =  \PT[\indpt3;2]-(\PT[\indpt4;2])}
\rational{vect1z =  \PT[\indpt1;3]-(\PT[\indpt2;3])}
\rational{vect2z =  \PT[\indpt3;3]-(\PT[\indpt4;3])}
\rational{pdtscal=(\vect1x) * (\vect2x) + (\vect1y) * (\vect2y) + (\vect1z) * (\vect2z)}
\if {\pdtscal<0.001 and \pdtscal>-0.001}{\integer{goodrep=1}}{\integer{goodrep=2}}

%%%%% dessin de l'objet
\text{cube=linewidth 3
polyline black,0,0,0,10,10,10,10,0,0,0
polyline black,0,10,2,13,12,13,10,10
dpolyline black,0,0,2,3,12,3
dsegment 2,3,2,13,black
polyline black,10,0,12,3,12,13
}

\text{cadre=
xrange -5,15
yrange -5,15
\cube
text \color[1],-0.4,-0.5,medium,A
text \color[2],10.1,-0.5,medium,B
text \color[4],2.6,3,medium,D
text \color[3],12.1,3,medium,C
text \color[5],-1,11,medium,E
text \color[6],10.7,10.8,medium,F
text \color[7],2.6,14.2,medium,H
text \color[8],12.1,14.2,medium,G
text \color[9],5,-0.5,medium,I
text \color[10],7,4.2,medium,J
text \color[11],1.4,1.8,medium,K
text \color[12],11.5,1.8,medium,L
text \color[13],5,9.5,medium,M
text \color[14],7,14.5,medium,N
text \color[15],0,12.2,medium,O
text \color[16],11.3,11.8,medium,P
text \color[17],-0.8,5.5,medium,Q
text \color[18],10.3,5.5,medium,R
text \color[19],12.3,8.5,medium,S
text \color[20],2.2,8.5,medium,T
linewidth 5
points blue,0,0,0,10,10,10,10,0,2,13,12,13,2,3,12,3
points green,5,0,7,3,1,1.5,11,1.5,5,10,7,13,1,11.5,11,11.5,0,5,10,5,2,8,12,8
linewidth 3
\dessin
}
\if{\ggb==2}{
  \text{lp_enon=aa=Segment(\pt1,\pt2)
SetColor[aa,red]
ShowLabel[aa, false]
bb=Segment(\pt3,\pt4)
SetColor[bb,blue]
ShowLabel[bb, false]
}
#include "ggbc_milieu.inc"
#include "ggbc.inc"
\text{A=slib(geo2D/geogebra width=600;
height=600;
\fig_ggb)}
}

\statement{
#include "intro_stat.inc"
\objet. \tpoints.
  <p>
  On considère les droites <span style="color:red">(\pt1\pt2)</span>
  et <span style="color:blue">(\pt3\pt4)</span>
 et on s'intéresse à leur orthogonalité éventuelle.
 </p>
  Les droites <span style="color:red">(\pt1\pt2)</span>
  et <span style="color:blue">(\pt3\pt4)</span> sont
<ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
</ul>
</div>
\if{\ggb=1}{</div>}
}
\answer{orthogonalité relative}{\goodrep;\lstposrel}{type=radio}
