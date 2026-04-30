target=Interpar1 Interpar2 Interpar3 Interpar4 Interpar5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}
\matrix{nstep=(\ggb==1)?reply1}
\matrix{nstep=(\ggb==2)?reply2}
\nextstep{\nstep}
\integer{confoutil=(\confparm2==)?2:\confparm1}
\text{s=shuffle(1,2,3,4)}

#if (defined TARGET_Interpar1  || defined TARGET_Interpar2  || defined TARGET_Interpar3  || defined TARGET_Interpar4  )
\if{\ggb==2}{
  \integer{po=randint(1..5)}
  \text{dqs=du quatrième sommet de ce quadrilatère.}
  \text{embopt=}
  \text{cons=Cliquer à l'emplacement \dqs}

  \text{lp_outil=showToolBar=true;}
  \text{lp_outil=(\confoutil==1)?\lp_outil
customToolBar="0||1";:\lp_outil
customToolBar="0||5||2||3";}
  \text{listlab=a,b,c,d,e,f,g,h,i,j,k,l}
  \text{lp_lab=}
  \for{i in \listlab}{
    \text{t=ShowLabel[\i, false]}
    \text{lp_lab=wims(append line \t to \lp_lab)}
  }
}

# include "cubepts.inc"
#if defined TARGET_Interpar1
\integer{offsetx=randint(1..9)}
\integer{offsety=0}
\text{indl=1,4,5,8}
\if{\ggb==2}{
  \text{pt_trans=A,D,E,H}
  \text{vectt=v=Vector((\po, 0,0))}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[1])?-3+\po,-3,0}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[2])?-3+\po,3,0}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[3])?-3+\po,-3,6}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[4])?-3+\po,3,6}
}
#endif
#if defined TARGET_Interpar2
\integer{offsety=randint(1..9)}
\integer{offsetx=0}
\text{indl=1,2,3,4}
\if{\ggb==2}{
  \text{pt_trans=A,B,C,D}
  \text{vectt=v=Vector((0,0,\po))}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[1])?-3,-3,\po}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[2])?3,-3,\po}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[3])?3,3,\po}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[4])?-3,3,\po}
}
#endif
#if defined TARGET_Interpar3
\rational{offsety=randint(5..25)/10}
\rational{offsetx=2*\offsety / 3}
\text{indl=1,2,5,6}
\if{\ggb==2}{
  \text{pt_trans=A,B,E,F}
  \text{vectt=v=Vector((0,\po,0))}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[1])?-3,-3+\po,0}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[2])?3,-3+\po,0}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[3])?-3,-3+\po,6}
  \matrix{coordi=(\pt_trans[\s[4]] isin \pt_trans[4])?3,-3+\po,6}
}
#endif

#if (defined TARGET_Interpar1  || defined TARGET_Interpar2  || defined TARGET_Interpar3 )
\if{\ggb==2}{
  \rational{pg=(\confoutil==1)?0.2:0.00001}
  \text{ptenon=I}
  \text{vectt=\vectt
SetVisibleInView(v,-1,false);
U=\pt_trans[\s[1]]+v
V=\pt_trans[\s[2]]+v
W=\pt_trans[\s[3]]+v}
}
#include "ggbc.inc"
#endif

#if defined TARGET_Interpar4
# include "pyrampts.inc"
\text{indl=1,2,3,4}
\if{\ggb==2}{
  \rational{pg=(\confoutil==1)?0.3:0.00001}
  \text{ptenon=E}
  \rational{hh=randint(1..9)/10}
  \text{pt_trans=A,B,C,D}
  \text{vectt=U=Dilate(S,\hh,\pt_trans[\s[1]])
V=Dilate(S,\hh,\pt_trans[\s[2]])
W=Dilate(S,\hh,\pt_trans[\s[3]])}
#include "ggbp.inc"
  \integer{ptnt=(\pt_trans[\s[4]] isin \pt_trans[1])?1}
  \integer{ptnt=(\pt_trans[\s[4]] isin \pt_trans[2])?2}
  \integer{ptnt=(\pt_trans[\s[4]] isin \pt_trans[3])?3}
  \integer{ptnt=(\pt_trans[\s[4]] isin \pt_trans[4])?4}
  \matrix{Sv=\cg[\ptnt;1]-\cg[5;1],\cg[\ptnt;2]-\cg[5;2],\cg[\ptnt;3]-\cg[5;3]}
  \real{jj=(6*\hh-(\cg[5;3]))/(\Sv[1;3])}
\matrix{coordi=(\cg[\ptnt;1])*\jj,(\cg[\ptnt;2])*\jj,6*\hh}
}
#endif
#if (defined TARGET_Interpar1  || defined TARGET_Interpar2  || defined TARGET_Interpar3 || defined TARGET_Interpar4)
\if{\ggb==2}{
  \text{embopt=,800 x 800
\fig_ggb}
  \text{cons=Placer le point \(\ptenon\) \dqs <div class="wims_instruction">}
  \text{cons=(\confoutil==1)?\cons Pour construire le point, cliquer sur un segment en dehors des points puis faire glisser le point.:
 \cons Construire des droites pour que le point se trouve à l'intersection de celles-ci.}
  \text{cons=\cons</div>}
  \text{listlab=a,b,c,d,e,f,g,h,i,j,k,l}
  \text{lp_lab=}
  \for{i in \listlab}{
    \text{t=ShowLabel[\i, false]}
    \text{lp_lab=wims(append line \t to \lp_lab)}
  }
}
#endif

\text{donnees=slib(draw/repere 400,400,0,-5,15,-5,15,1,1,black,grey)}

\text{tmp=row(1,\donnees)}
%%%%%coordonnées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%%%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}

\text{indl=shuffle(\indl)}
#if defined TARGET_Interpar4
\rational{rapport=randint(3..7)/10}
\rational{ux=\pt[\indl[1];1]+ \rapport*(\pt[5;1]-\pt[\indl[1];1])}
\rational{uy=\pt[\indl[1];2]+ \rapport*(\pt[5;2]-\pt[\indl[1];2])}
\rational{vx=\pt[\indl[2];1]+ \rapport*(\pt[5;1]-\pt[\indl[2];1])}
\rational{vy=\pt[\indl[2];2]+ \rapport*(\pt[5;2]-\pt[\indl[2];2])}
\rational{wx=\pt[\indl[3];1]+ \rapport*(\pt[5;1]-\pt[\indl[3];1])}
\rational{wy=\pt[\indl[3];2]+ \rapport*(\pt[5;2]-\pt[\indl[3];2])}
\rational{Xx=\pt[\indl[4];1]+ \rapport*(\pt[5;1]-\pt[\indl[4];1])}
\rational{Xy=\pt[\indl[4];2]+ \rapport*(\pt[5;2]-\pt[\indl[4];2])}
#else
\rational{ux=\offsetx+\pt[\indl[1];1]}
\rational{uy=\offsety+\pt[\indl[1];2]}
\rational{vx=\offsetx+\pt[\indl[2];1]}
\rational{vy=\offsety+\pt[\indl[2];2]}
\rational{wx=\offsetx+\pt[\indl[3];1]}
\rational{wy=\offsety+\pt[\indl[3];2]}
\rational{Xx=\offsetx+\pt[\indl[4];1]}
\rational{Xy=\offsety+\pt[\indl[4];2]}
#endif
\integer{fxm=\Ox+\Xx*\ex-\ex/3}
\integer{fxp=\Ox+\Xx*\ex+\ex/3}
\integer{fym=\Oy+\Xy*\ey-\ey/3}
\integer{fyp=\Oy+\Xy*\ey+\ey/3}

\text{dessin=
linewidth 6
points red,\ux,\uy,\vx,\vy,\wx,\wy
text red,\ux,\uy,medium,U
text red,\vx,\vy,medium,V
text red,\wx,\wy,medium,W
}
#if defined TARGET_Interpar1
# include "cubedraw2.inc"
\text{poly=ABCDEFGH}
#endif
#if defined TARGET_Interpar2
# include "cubedraw2.inc"
\text{poly=ABCDEFGH}
#endif
#if defined TARGET_Interpar3
# include "cubedraw2.inc"
\text{poly=ABCDEFGH}
#endif
#if defined TARGET_Interpar4
# include "pyramdraw2.inc"
\text{poly=SABCD}
#endif
\text{image=draw(400,400
\cadre
)}
%%debug
\pt_trans[\s[4]]||\hh||\coordi||\jj||\Sv||cg4,3=\cg[4;3]
<div class="wimscenter"><image src="\image"></div>

\statement{
   \objet. <p>
  On considère le plan <span style="color:red">(UVW)</span>, parallèle à une
  face du solide et on s'intéresse à son intersection avec \poly qui
  est un quadrilatère.
</p><p>
\cons
</p>
<div class="wimscenter">
\if{\ggb==1}{\embed{reply1}}
\if{\ggb==2}{\embed{reply2 \embopt}}
</div>}


\answer{X}{\image;rectangle,\fxm,\fym,\fxp,\fyp}{type=coord}

\answer{}{f,\ptenon=Point,Le point \ptenon est construit;
n,abs(x_\ptenon-(\coordi[1;1]))<\pg,L'abscisse du point \(\ptenon\) est correcte;
n,abs(y_\ptenon-(\coordi[1;2]))<\pg,L'ordonnée du point \(\ptenon\) est correcte;
n,abs(z_\ptenon-(\coordi[1;3]))<\pg,La cote du point \(\ptenon\) est correcte;}{type=geogebra}{option=max=100 extra=yes output=coord feedbackscript=Correction}

\matrix{arep=\reply2}

\text{nstep=(\step==2)?}

\feedback{sc_reply2!=1}{
<script>
function  Correction(){ggbApplet0.evalCommand("Plane(U,V,W)");}
</script>}
#endif
#if defined TARGET_Interpar5
# include "tetrapts.inc"

\text{donnees=slib(draw/repere 400,400,0,-3,30,-3,20,1,1,black,grey)}

\text{tmp=row(1,\donnees)}
%%%%coordonnéées de l'origine du repère
\integer{Ox=item(1,\tmp)}
\integer{Oy=item(2,\tmp)}

\text{tmp=row(2,\donnees)}
%%%%échelle des axes
\integer{ex=item(1,\tmp)}
\integer{ey=item(2,\tmp)}
\integer{k=randint(1..4)}
\if{\k=1}{
 \text{tface=(ABC)}
 \text{indl=1,2,3}
 \integer{sommet=4}
 }
\if{\k=2}{
 \text{tface=(BCD)}
 \text{indl=2,3,4}
 \integer{sommet=1}
 }
\if{\k=3}{
 \text{tface=(ACD)}
 \text{indl=1,3,4}
 \integer{sommet=2}
 }
\if{\k=4}{
 \text{tface=(ABD)}
 \text{indl=1,2,4}
 \integer{sommet=3}
 }
\rational{rapport=randint(3..7)/10}
\rational{ux=\pt[\indl[1];1]+ \rapport*(\pt[\sommet;1]-\pt[\indl[1];1])}
\rational{uy=\pt[\indl[1];2]+ \rapport*(\pt[\sommet;2]-\pt[\indl[1];2])}
\rational{vx=\pt[\indl[2];1]+ \rapport*(\pt[\sommet;1]-\pt[\indl[2];1])}
\rational{vy=\pt[\indl[2];2]+ \rapport*(\pt[\sommet;2]-\pt[\indl[2];2])}
\rational{Xx=\pt[\indl[3];1]+ \rapport*(\pt[\sommet;1]-\pt[\indl[3];1])}
\rational{Xy=\pt[\indl[3];2]+ \rapport*(\pt[\sommet;2]-\pt[\indl[3];2])}

\integer{fxm=\Ox+\Xx*\ex-\ex/3}
\integer{fxp=\Ox+\Xx*\ex+\ex/3}
\integer{fym=\Oy+\Xy*\ey-\ey/3}
\integer{fyp=\Oy+\Xy*\ey+\ey/3}

\text{dessin=
linewidth 6
points red,\ux,\uy,\vx,\vy
text red,\ux,\uy,medium,U
text red,\vx,\vy,medium,V
}
\if{\ggb==2}{\text{lp_outil=showToolBar=true;}
\text{lp_outil=(\confoutil==1)?\lp_outil
customToolBar="0||1";:\lp_outil
customToolBar="0||5||2||3";}
\text{pt_trans=A,B,C,D}
\rational{hh=randint(1..9)/10}
\rational{rap=1-\rapport}
\rational{pg=(\confoutil==1)?0.2:0.00001}
\text{ptenon=E}
\text{vectt=U=Dilate(\pt_trans[\indl[1]],(1-\rapport),\pt_trans[\sommet])
V=Dilate(\pt_trans[\indl[2]],(1-\rapport),\pt_trans[\sommet])}
\text{listcol=U,V}
\for{i in \listcol}{\text{t=SetColor[\i,red]}
\text{vectt=wims(append line \t to \vectt)}
}
\text{listlab=a,b,c,d,e,f,g,h,i,j,k,l}
\text{lp_lab=}
\for{i in \listlab}{\text{t=ShowLabel[\i, false]}
\text{lp_lab=wims(append line \t to \lp_lab)}
}
}

#include "ggbt.inc"
\if{\ggb==2}{
\matrix{coordi=(1-\rapport)*(\coordg[\indl[3];1])+\rapport*\coordg[\sommet;1],(1-\rapport)*(\coordg[\indl[3];2])+\rapport*\coordg[\sommet;2],(1-\rapport)*(\coordg[\indl[3];3])+\rapport*\coordg[\sommet;3]}
\text{embopt=,800 x 800
\fig_ggb}
}
\text{tfacee=}
\text{facee=wims(declosing \tface)}
\for{i=1 to 3}{\text{t=wims(char \i of \facee)}
\text{tfacee=wims(append item \t to \tfacee)}}


#include "tetradraw.inc"
\text{image=draw(400,400
\cadre
)}

Debug%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\pt_trans[\sommet]||\pt_trans[\indl[3]]||sommet=\sommet||indl=\indl[3]||\coordi
<br>
rapport=\rapport
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


\statement{
  \objet.<p>
  On considère le plan parallèle à la face <span style="color:blue">\tface </span>
  et passant par les points <span style="color:red">\(U) et \(V)</span>.
</p><p>
  L'intersection de ce plan avec le tétraèdre est un triangle.
  Cliquer à l'emplacement du troisième sommet de ce triangle.
</p>
<div class="wimscenter">
\if{\ggb==1}{\embed{reply1}}
\if{\ggb==2}{\embed{reply2 \embopt}}
</div>
}

\answer{X}{\image;rectangle,\fxm,\fym,\fxp,\fyp}{type=coord}


\answer{}{f,\ptenon=Point,Le point \ptenon est construit;
n,abs(x_\ptenon-(\coordi[1;1]))<\pg,L'abscisse du point \(\ptenon\) est bien placée;
n,abs(y_\ptenon-(\coordi[1;2]))<\pg,L'ordonnée du point \(\ptenon\) est bien placée;
n,abs(z_\ptenon-(\coordi[1;3]))<\pg,La cote du point \(\ptenon\) est bien placée;}{type=geogebra}{option=max=100 extra=yes output=coord feedbackscript=Correction}

\text{nstep=(\step==2)?}

\feedback{\ggb==2}{
<script>
function  Correction(){ggbApplet0.evalCommand("pp=Plane(\tfacee)");
ggbApplet0.evalCommand("Plane(U,pp)");}
</script>}

#endif
