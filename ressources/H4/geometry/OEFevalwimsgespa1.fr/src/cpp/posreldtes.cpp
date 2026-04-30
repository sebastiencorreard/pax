target=posreldte1 posreldte2 posreldte3 posreldte4 posreldte5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}

#if defined TARGET_posreldte1
# include "cubepts.inc"
\integer{n2=8}
\integer{n1=1}
\integer{nf=6}
#endif
#if defined TARGET_posreldte2
# include "cubepts.inc"
\integer{n2=20}
\integer{n1=1}
\integer{nf=6}
#endif
#if defined TARGET_posreldte3
# include "cubepts.inc"
\integer{n2=20}
\integer{n1=9}
\integer{nf=6}
#endif
#if defined TARGET_posreldte4
# include "tetrapts.inc"
\integer{n2=4}
\integer{n1=1}
\integer{nf=4}
#endif
#if defined TARGET_posreldte5
# include "tetrapts.inc"
\integer{n2=16}
\integer{n1=1}
\integer{nf=4}
#endif

%%%%% Choix des droites
\integer{facedeb=randint(1..\nf)}
%%%integer{facedeb=4}
\integer{facefin=randint(1..\nf)}
%%%integer{facefin=3}
\text{lstpt=}
\for{ ii = \n1 to \n2}{
  \if {\facedeb isitemof \faces[\ii;]}{
    \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle (\lstpt)}
%%%%%text{lstpt=N,T}
\text{pt1 = \lstpt[1]}
\text{pt2 = \lstpt[2]}
\text{lstpt=}
\for{ ii = \n1 to \n2}{
  \if {\facefin isitemof \faces[\ii;]}{
     \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle(\lstpt)}
%%%%%text{lstpt=R,I}
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
\integer{goodrep=1}
\text{lstpt=\pt1,\pt2,\pt3,\pt4}
\text{lstpt = wims(listuniq \lstpt)}
\integer{n=items(\lstpt)}
\text{face1= wims(listintersect \faces[\indpt1;] and \faces[\indpt2;])}
\text{face2= wims(listintersect \faces[\indpt3;] and \faces[\indpt4;])}
\text{lstface= wims(listintersect \face1 and \face2)}
\rational{den1 =  \pt[\indpt1;1]-(\pt[\indpt2;1])}
\rational{den2 =  \pt[\indpt3;1]-(\pt[\indpt4;1])}
\rational{num1 =  \pt[\indpt1;2]-(\pt[\indpt2;2])}
\rational{num2 =  \pt[\indpt3;2]-(\pt[\indpt4;2])}
\rational{colin=\den1*(\num2)-(\den2)*(\num1)}
\if {\colin<0.001 and \colin>-0.001}{
#if (defined TARGET_posreldte4  || defined TARGET_posreldte5 )
%%%% elles ont l'air d'être parallèles, mais si elles ne sont pas dans la même face
%%%% elles doivent être parallèles à la droite d'intersection des faces
\text{trace=colin}
\if{items(\lstface)<1}{
  \text{trace=pasmemeface}
%%%% elles ne sont pas dans la même face, y a-til un effet d'optique?
  \text{dteinter= wims(listintersect \facedtes[\face1;] and \facedtes[\face2;])}
  \text{pt5=\dtept[\dteinter;1]}
  \text{pt6=\dtept[\dteinter;2]}
  \integer{indpt5=position(\pt5,\listpoint)}
  \integer{indpt6=position(\pt6,\listpoint)}
  \rational{den3 =  \pt[\indpt5;1]-(\pt[\indpt6;1])}
  \rational{num3 =  \pt[\indpt5;2]-(\pt[\indpt6;2])}
  \rational{colin=\den1*(\num3)-(\den3)*(\num1)}
  \if {\colin<0.001 and \colin>-0.001}{
     \integer{goodrep=3}
  }{
    \if{\n<4}{ \integer{goodrep=2}}{ \integer{goodrep=1}}
 }
}{
  \integer{goodrep=3}
}
#else
%%%%% elles ont l'air parallèles mais ce n'est possible dans le cube que si elles sont dans des faces parallèles
ou dans la même face
%%%%% meme face?
\text{lstface= wims(listintersect \face1 and \face2)}
\integer{nf=items(\lstface)}
\if{\nf>0}{
  \integer{goodrep=3}
}{
%%%%% faces parallèles ?
%%%%% une droite peut-être une arête et appartenir à plusieurs faces
  \integer{trouvepar=0}
  \integer{n1= items(\face1)}
  \integer{n2= items(\face2)}
  \if{ \n1>1 and \n2>1}{
%%%%% deux arêtes semblant parallèles sont parallèles
    \integer{trouvepar=1}
  }
  \text{lst1=1,3,5}
  \if{ \n1>1 and \trouvepar=0}{
    \for{ ii=1 to 2}{
      \integer{facedeb1=\face1[\ii]}
      \if{ \facedeb1 isitemof \lst1}{
        \integer{facepar = \facedeb1 + 1}
      }{
        \integer{facepar = \facedeb1 - 1}
      }
      \if{ \facefin=\facepar}{
        \integer{trouvepar=1}
       }
     }
  }
  \if{ \n2>1 and \trouvepar=0}{
    \for{ ii=1 to 2}{
      \integer{facefin1=\face2[\ii]}
      \if{ \facefin1 isitemof \lst1}{
        \integer{facepar = \facefin1 + 1}
      }{
        \integer{facepar = \facefin1 - 1}
      }
      \if{\facedeb=\facepar}{
        \integer{trouvepar=1}
      }
    }
  }
  \if{ \n2=1 and \n1=1 and \trouvepar=0}{
    \if{\facedeb isitemof \lst1}{
      \integer{facepar = \facedeb + 1}
    }{
      \integer{facepar = \facedeb - 1}
    }
    \if{\facefin=\facepar}{
      \integer{trouvepar=1}
    }
  }
  \if{\trouvepar=1}{
    \integer{goodrep=3}
  }{
    \integer{goodrep=1}
  }
}
#endif
}{
%%%%% si elles ne sont pas parallèles, sont-elles dans la même face?
  \if{\n<4}{
    \if{\n<3}{ \integer{goodrep=3}}{ \integer{goodrep=2}}
  }{
    \if{\facedeb = \facefin}{
      \integer{goodrep=2}
    }{
    \text{lstdte= wims(listintersect \dtes[\indpt1;] and \dtes[\indpt2;])}
    \integer{n=items(\lstdte)}
    \if{\n>0}{
      \text{ladte = \lstdte[1]}
      \text{pt11=\dtept[\ladte;1]}
      \text{pt21=\dtept[\ladte;2]}
    }{
     \text{pt11=\pt1}
     \text{pt21=\pt2}
    }
    \text{lstdte= wims(listintersect \dtes[\indpt3;] and \dtes[\indpt4;])}
    \integer{n=items(\lstdte)}
    \if{\n>0}{
       \text{ladte = \lstdte[1]}
       \text{pt31=\dtept[\ladte;1]}
       \text{pt41=\dtept[\ladte;2]}
    }{
       \text{pt31=\pt3}
       \text{pt41=\pt4}
    }
    \text{lstpt2=\pt11,\pt21,\pt31,\pt41}
    \text{lstpt2 = wims(listuniq \lstpt2)}
    \integer{n=items(\lstpt2)}
    \if{\n<4}{
      \integer{goodrep=2}
      }{
        \if{items(\lstface)>=1}{
          \integer{goodrep=2}
        }
      }
    }
  }
}
\if{\ggb==2}{
  \text{lp_enon=aa=Segment(\pt1,\pt2)
SetColor[aa,red]
ShowLabel[aa, false]
bb=Segment(\pt3,\pt4)
SetColor[bb,blue]
ShowLabel[bb, false]}
  \text{listlab=a,b,c,d,e,f,g,h,i,j,k,l}
  \text{lp_lab=}
  \for{i in \listlab}{
    \text{t=ShowLabel[\i, false]}
    \text{lp_lab=wims(append line \t to \lp_lab)}
  }
}
#if defined TARGET_posreldte1
#include "cubedraw.inc"
#endif
#if defined TARGET_posreldte2
#include "cubedraw.inc"
#endif
#if defined TARGET_posreldte3
#include "cubedraw.inc"
#endif
#if (defined TARGET_posreldte1 || defined TARGET_posreldte2 || defined TARGET_posreldte3 )
#include "ggbc_milieu.inc"
#include "ggbc.inc"
#endif
#if defined TARGET_posreldte4
#include "tetradraw.inc"
#include "ggbt.inc"
#endif
#if defined TARGET_posreldte5
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
  \objet. \tpoints.
  <p>
  On considère les droites <span style="color:red">(\pt1\pt2)</span>
  et <span style="color:blue">(\pt3\pt4)</span> et on s'intéresse à
  leur position relative:
  Les droites <span style="color:red">(\pt1\pt2)</span>
     et <span style="color:blue">(\pt3\pt4)</span> sont
  </p>
<ul>
  <li>\embed{reply1,1}</li>
  <li>\embed{reply1,2}</li>
  <li>\embed{reply1,3}</li>
</ul>
</div>
\if{\ggb=1}{</div>}
}
\answer{position relative}{\goodrep;\lstposrel}{type=radio}
