target=posrelpl1 posrelpl2 posrelpl3 posrelpl4 posrelpl5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}

#if defined TARGET_posrelpl1
# include "cubepts.inc"
  \integer{nplan=8}
  \integer{ndte=8}
  \integer{nf=6}
#endif
#if defined TARGET_posrelpl2
# include "cubepts.inc"
  \integer{nplan=8}
  \integer{ndte=20}
  \integer{nf=6}
#endif
#if defined TARGET_posrelpl3
# include "cubepts.inc"
  \integer{nplan=20}
  \integer{ndte=20}
  \integer{nf=6}
#endif
#if defined TARGET_posrelpl4
# include "tetrapts.inc"
  \integer{nplan=4}
  \integer{ndte=16}
  \integer{nf=4}
#endif
#if defined TARGET_posrelpl5
# include "tetrapts.inc"
  \integer{nplan=16}
  \integer{ndte=16}
  \integer{nf=4}
#endif

%%%%% choix de la face du cube
\integer{face = randint(1..\nf)}
%%%%%
%%%integer{face=5}
\text{lstpts=}
\for{ii=1 to \nplan}{
  \if{\face isitemof \faces[\ii;]}{
      \text{lstpts= wims(append item \listpoint[\ii] to \lstpts)}
  }
}
\text{lstpts = shuffle(\lstpts)}
%%%%%
%%%%%text{lstpts=A,D,H}
\text{ptsplan = \lstpts[1],\lstpts[2]}
\integer{indpl1=position(\lstpts[1],\listpoint)}
\integer{indpl2=position(\lstpts[2],\listpoint)}

\text{lstdte=wims(listintersect \dtes[\indpl1;] and \dtes[\indpl2;])}
\text{lstdte2=}
\integer{trouvept=0}
\for{ ii=3 to items(\lstpts)}{
  \if{\trouvept=0}{
    \integer{indplii=position(\lstpts[\ii],\listpoint)}
    \text{lstdte2=wims(listintersect \lstdte and \dtes[\indplii;])}
    \if{\lstdte2=}{
      \text{ptsplan= wims(append item \lstpts[\ii] to \ptsplan)}
      \integer{trouvept=1}
    }
  }
}
\text{ptsplan = wims(sort item \ptsplan)}
%%%%%
%%%%%text{ptsplan=A,D,H}

\text{tplan=\ptsplan[1]\ptsplan[2]\ptsplan[3]}

%%%%% Choix de la  droite
\integer{facedte=randint(1..\nf)}

%%%%%
  %%%integer{facedte=6}
\text{lstpt=}
\for{ ii = 1 to \ndte}{
  \if {\facedte isitemof \faces[\ii;]}{
     \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle (\lstpt)}
%%%%%
%%%%%text{lstpt=F,B}
\text{pt1 = \lstpt[1]}
\text{pt2 = \lstpt[2]}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpl1=position(\ptsplan[1],\listpoint)}
\integer{indpl2=position(\ptsplan[2],\listpoint)}
\integer{indpl3=position(\ptsplan[3],\listpoint)}
\text{dessin=
   poly blue,\pt[\indpl1;],\pt[\indpl2;],\pt[\indpl3;]
   segment \pt[\indpt1;],\pt[\indpt2;],red
}
\if{\ggb==2}{
  \text{lp_enon=aa=Segment(\pt1,\pt2)
SetColor[aa,red]
ShowLabel[aa, false]
SetLineThickness[aa,10]
bb=Polygon(\ptsplan[1],\ptsplan[2],\ptsplan[3])
SetColor[bb,blue]
ShowLabel[bb, false]}
  \text{suplab=a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w}
  \for{i in \suplab}{
    \text{t=ShowLabel[\i, false]
ShowLabel[\i _1, false]}
  \text{lp_enon=wims(append line \t to \lp_enon)}
  }
}

%%%%% détermination des bonnes réponses
#if (defined TARGET_posrelpl1 || defined TARGET_posrelpl2 || defined TARGET_posrelpl3 )
#if defined TARGET_posrelpl1
# include "grrelplcu.inc"
# include "cubedraw.inc"
#endif
#if defined TARGET_posrelpl2
# include "grrelplcu.inc"
# include "cubedraw.inc"
#endif
#if defined TARGET_posrelpl3
# include "grrelplcu.inc"
# include "cubedraw.inc"
#endif

#include "ggbc_milieu.inc"
#include "ggbc.inc"
#endif
#if defined TARGET_posrelpl4
# include "grrelpltetr.inc"
# include "tetradraw.inc"
#include "ggbt.inc"
#endif
#if defined TARGET_posrelpl5
# include "grrelpltetr.inc"
# include "tetradraw.inc"
#include "ggbt.inc"
#endif
\if{\ggb==2}{
  \text{A=slib(geo2D/geogebra width=600;
height=600;
\fig_ggb)}
}

\text{lstposrel=strictement parallèle, incluse, sécante}
\statement{
#include "intro_stat.inc"
  \objet. \tpoints.<p>
  On considère la droite <span style="color:red">(\pt1\pt2)</span> et
  le plan <span style="color:blue">(\tplan)</span> et on s'intéresse à leur
  position relative.</p>
  Par rapport au plan <span style="color:blue">(\tplan)</span>,
  la droite <span style="color:red">(\pt1\pt2)</span> est
  <ul>
     <li>\embed{reply1,1}</li>
     <li>\embed{reply1,2}</li>
     <li>\embed{reply1,3}</li>
  </ul>
</div>
\if{\ggb==1}{</div>}
}
\answer{position relative}{\goodrep;\lstposrel}{type=radio}
