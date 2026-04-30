target=pos2pl1 pos2pl2 pos2pl3 pos2pl4 pos2pl5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}

#if defined TARGET_pos2pl1
# include "cubepts.inc"
  \integer{nplan=8}
  \integer{n=8}
  \integer{n1=1}
  \integer{nf=6}
#endif
#if defined TARGET_pos2pl2
# include "cubepts.inc"
  \integer{nplan=8}
  \integer{n=20}
  \integer{n1=1}
  \integer{nf=6}
#endif
#if defined TARGET_pos2pl3
#include "cubepts.inc"
  \integer{nplan=20}
  \integer{n=20}
  \integer{n1=9}
  \integer{nf=6}
#endif
#if defined TARGET_pos2pl4
#include "pyrampts.inc"
  \integer{nplan=13}
  \integer{n=13}
  \integer{n1=1}
  \integer{nf=5}
#endif
#if defined TARGET_pos2pl5
#include "tetrapts.inc"
  \integer{nplan=16}
  \integer{n=16}
  \integer{n1=1}
  \integer{nf=4}
#endif

%%%%%choix de la réponse
\integer{k=randint(1..5)}

%%%%k=1 vide, k=2, confondus, k=3 choix d'une droite

%%%%% Choix des plans
%%%%%premier plan
\text{indface=shuffle(\nf)}
\integer{face = \indface[1]}
#if defined TARGET_pos2pl4
\integer{face=1}
#endif
\text{lstpts=}
\for{ii=1 to \nplan}{
  \if{\face isitemof \faces[\ii;]}{
    \text{lstpts= wims(append item \listpoint[\ii] to \lstpts)}
  }
}
\text{lstpts = shuffle(\lstpts)}
\text{ptsplan = \lstpts[1],\lstpts[2]}
\integer{indpl1=position(\ptsplan[1],\listpoint)}
\integer{indpl2=position(\ptsplan[2],\listpoint)}


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
\text{tplan1=(\ptsplan[1]\ptsplan[2]\ptsplan[3])}
\text{pt1=\ptsplan[1]}
\text{pt2=\ptsplan[2]}
\text{pt3=\ptsplan[3]}

%%%%%deuxième plan
\if{\k=1}{
%%%%%   choix d'un plan parallèle
#if (defined TARGET_pos2pl1  || defined TARGET_pos2pl2  || defined TARGET_pos2pl3 )
  \text{faceimpair=1,3,5}
  \if{\face isitemof \faceimpair}{\integer{face2=\face+1}}{\integer{face2=\face-1}}
#endif
}
\if{\k=2}{
%%%%%choix du même plan
  \integer{face2 = \face}
}
\if{\k>2}{
  \integer{face2 = \indface[2]}
#if (defined TARGET_pos2pl1  || defined TARGET_pos2pl2  || defined TARGET_pos2pl3 )
  \text{faceimpair=1,3,5}
  \if{\face isitemof \faceimpair}{
    \integer{facepar=\face+1}
    \if{\face2=\facepar}{ \integer{k=1}}
  }{
    \integer{facepar=\face-1}
    \if{\face2=\facepar}{ \integer{k=1}}
  }
#endif
#if defined TARGET_pos2pl4
  \if{\face=1}{\integer{face2=random(2..5)}}
  \if{\face=2 or \face=4}{\integer{face2=random(1,3,5)}}
  \if{\face=3 or \face=5}{\integer{face2=random(1,2,4)}}
#endif
}
\text{lstpts=}
\for{ii=1 to \nplan}{
  \if{\face2 isitemof \faces[\ii;]}{
    \text{lstpts= wims(append item \listpoint[\ii] to \lstpts)}
  }
}
\text{lstpts = shuffle(\lstpts)}
\text{ptsplan = \lstpts[1],\lstpts[2]}
\integer{indpl4=position(\lstpts[1],\listpoint)}
\integer{indpl5=position(\lstpts[2],\listpoint)}

\text{lstdte=wims(listintersect \dtes[\indpl4;] and \dtes[\indpl5;])}
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
\if{\k=1}{
#if defined TARGET_pos2pl5
  \integer{kk=randint(1,2)}
  \if{\face=1}{\text{ptsplan=\kk=1?K,Q,T:L,R,S}}
  \if{\face=2}{\text{ptsplan=\kk=1?J,L,N:I,K,M}}
  \if{\face=3}{\text{ptsplan=\kk=1?M,P,R:N,O,Q}}
  \if{\face=4}{\text{ptsplan=\kk=1?I,O,S:J,P,T}}
#endif
#if defined TARGET_pos2pl4
  \text{data=M,N,O
M,N,P
M,O,P
N,O,P
  }
 \text{ptsplan=randomrow(\data)}
#endif
}
\text{tplan2=(\ptsplan[1]\ptsplan[2]\ptsplan[3])}
\text{pt4=\ptsplan[1]}
\text{pt5=\ptsplan[2]}
\text{pt6=\ptsplan[3]}

\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpt3=position(\pt3,\listpoint)}
\integer{indpt4=position(\pt4,\listpoint)}
\integer{indpt5=position(\pt5,\listpoint)}
\integer{indpt6=position(\pt6,\listpoint)}
\text{dessin=
   poly red,\pt[\indpt1;],\pt[\indpt2;],\pt[\indpt3;]
   poly blue,\pt[\indpt4;],\pt[\indpt5;],\pt[\indpt6;]
}

%%%%%détermination de la réponse
\if{\k=1}{ \integer{goodrep=2}}
\if{\k=2}{\integer{goodrep=3}}
\if{\k>2}{\integer{goodrep=1}}

\if{\ggb==2}{
\text{lp_enon=aa=Polygon(\pt1,\pt2,\pt3)
SetColor[aa,red]
ShowLabel[aa, false]
bb=Polygon(\pt4,\pt5,\pt6)
SetColor[bb,blue]
ShowLabel[bb, false]}
\text{suplab=a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w}
\for{i in \suplab}{\text{t=ShowLabel[\i, false]
ShowLabel[\i _1, false]
ShowLabel[\i _2, false]}
\text{lp_enon=wims(append line \t to \lp_enon)}}
}

#if defined TARGET_pos2pl1 || defined TARGET_pos2pl2 || defined TARGET_pos2pl3
#include "ggbc_milieu.inc"
#include "ggbc.inc"
#include "cubedraw.inc"
#endif
#if defined TARGET_pos2pl4
#include "pyramdraw.inc"
#include "ggbp_milieu.inc"
#include "ggbp.inc"
#endif
#if defined TARGET_pos2pl5
#include "tetradraw.inc"
#include "ggbt.inc"

#endif
\if{\ggb==2}{
  \text{A=slib(geo2D/geogebra width=600;
height=600;
\fig_ggb)}
}
\statement{
#include "intro_stat.inc"
  \objet. \tpoints.<p>
  On considère les plans <span style="color:red">(\pt1\pt2\pt3)</span> et
  <span style="color:blue">(\pt4\pt5\pt6)</span> et on s'intéresse à leur position
  relative. Les plans <span style="color:red">(\pt1\pt2\pt3)</span> et
     <span style="color:blue">(\pt4\pt5\pt6)</span> sont</p>
<ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
  <li>\embed{reply1,3}</li>
</ul>
</div>
\if{\ggb=1}{</div>}
}
\answer{position relative}{\goodrep;\lstposrel}{type=radio}
