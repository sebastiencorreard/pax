target=posorthdte4 posorthdte5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}
#include "cubepts.inc"
#if defined TARGET_posorthdte4
 \integer{npts=8}
#endif
#if defined TARGET_posorthdte5
 \integer{npts=20}
#endif

%%%%% Choix du triangle
\text{lstind=shuffle(\npts)}
\text{pt1=\listpoint[\lstind[1]]}
\text{pt2=\listpoint[\lstind[2]]}
\text{pt3=\listpoint[\lstind[1]]}
\text{pt4=\listpoint[\lstind[4]]}
%%%%%text{pt1=G}
%%%%%text{pt2=E}
%%%%%text{pt3=G}
%%%%%text{pt4=H}
\text{dte=wims(listintersect \faces[\lstind[1]] and \faces[\lstind[2]])}
\text{dte=wims(listintersect \dte and \faces[\lstind[4]])}
\integer{n=items(\dte)}
\if {\n>0}{\text{pt4=\listpoint[\lstind[3]]}}

\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpt3=position(\pt3,\listpoint)}
\integer{indpt4=position(\pt4,\listpoint)}
\text{dessin=
   poly red,\pt[\indpt1;],\pt[\indpt2;],\pt[\indpt4;]      }

%%%%% détermination des bonnes réponses
\integer{goodrep=5}
\rational{vect1x =  \PT[\indpt1;1]-(\PT[\indpt2;1])}
\rational{vect1y =  \PT[\indpt1;2]-(\PT[\indpt2;2])}
\rational{vect1z =  \PT[\indpt1;3]-(\PT[\indpt2;3])}
\rational{vect2x =  \PT[\indpt1;1]-(\PT[\indpt4;1])}
\rational{vect2y =  \PT[\indpt1;2]-(\PT[\indpt4;2])}
\rational{vect2z =  \PT[\indpt1;3]-(\PT[\indpt4;3])}
\rational{vect3x =  \PT[\indpt2;1]-(\PT[\indpt4;1])}
\rational{vect3y =  \PT[\indpt2;2]-(\PT[\indpt4;2])}
\rational{vect3z =  \PT[\indpt2;3]-(\PT[\indpt4;3])}
\rational{pdtscal1=(\vect1x) * (\vect2x) + (\vect1y) * (\vect2y) + (\vect1z) * (\vect2z)}
\rational{pdtscal2=(\vect3x) * (\vect2x) + (\vect3y) * (\vect2y) + (\vect3z) * (\vect2z) }
\rational{pdtscal3=(\vect1x) * (\vect3x) + (\vect1y) * (\vect3y) + (\vect1z) * (\vect3z) }
\real{pdtscal=(\pdtscal1)*(\pdtscal2)*(\pdtscal3)}
\if {\pdtscal=0}{\integer{goodrep=1}}
\rational{nvect1=(\vect1x)^2 + (\vect1y)^2 + (\vect1z)^2}
\rational{nvect2=(\vect2x)^2 + (\vect2y)^2 + (\vect2z)^2}
\rational{nvect3=(\vect3x)^2 + (\vect3y)^2 + (\vect3z)^2}
\integer{nat_iso=0}
\if{ \nvect1=\nvect2}{
  \integer{nat_iso=1}
  \if{\goodrep=1}{\integer{goodrep=3}}{\integer{goodrep=2}}
}
\if{ \nvect2=\nvect3}{
  \if{\goodrep=1}{\integer{goodrep=3}}{\integer{goodrep=2}}
  \if {\nat_iso=1}{\integer{goodrep=4}}
  \integer{nat_iso=1}
}
\if{ \nvect1=\nvect3}{
  \if{\goodrep=1}{\integer{goodrep=3}}{\integer{goodrep=2}}
  \if {\nat_iso=1}{\integer{goodrep=4}}
  \integer{nat_iso=1}
}

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
\text{name_instruction=Seule la réponse la plus précise sera valorisée.}

\if{\ggb==2}{
\text{lp_enon=aa=Polygon(\pt1,\pt2,\pt4)
SetColor[aa,red]
ShowLabel[aa, false]}
\text{suplab=a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w}
\for{i in \suplab}{\text{t=ShowLabel[\i _1, false]
ShowLabel[\i, false]}
\text{lp_enon=wims(append line \t to \lp_enon)}}
#include "ggbc_milieu.inc"
#include "ggbc.inc"
\text{A=slib(geo2D/geogebra width=600
height=600
\fig_ggb)}
}

\statement{
#include "intro_stat.inc"
   \objet. \tpoints.<p>
  On a tracé le triangle  <span style="color:red">\pt1\pt2\pt4</span>
  dans le cube ABCDEFGH et on s'intéresse à sa nature.
 </p>
Le triangle <span style="color:red">\pt1\pt2\pt4</span> est
<ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
  <li>\embed{reply1,3}</li>
  <li>\embed{reply1,4}</li>
  <li>\embed{reply1,5}</li>
</ul>
<div class="wims_instruction">
\name_instruction
</div>
</div>
\if{\ggb=1}{</div>}

}
\answer{nature du triangle}{\goodrep;\lstposrel}{type=radio}
