target=interdtepl1 interdtepl2 interdtepl3 interdtepl4 interdtepl5
test=0
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ggb=(\confparm1==)?1:\confparm1}

\text{lstposrel=strictement parallèle, incluse, sécante}
#if defined TARGET_interdtepl1
# include "cubepts.inc"
\integer{nplan=8}
\integer{ndte=8}
\integer{nf=6}
#endif
#if defined TARGET_interdtepl2
# include "cubepts.inc"
  \integer{nplan=8}
  \integer{ndte=20}
  \integer{nf=6}
#endif
#if defined TARGET_interdtepl3
# include "cubepts.inc"
  \integer{nplan=20}
  \integer{ndte=20}
  \integer{nf=6}
#endif
#if defined TARGET_interdtepl4
# include "tetrapts.inc"
  \integer{nplan=4}
  \integer{ndte=16}
  \integer{nf=4}
#endif
#if defined TARGET_interdtepl5
# include "tetrapts.inc"
  \integer{nplan=16}
  \integer{ndte=16}
  \integer{nf=4}
#endif

%%%%% choix de la face du cube
\integer{face = randint(1..\nf)}
\text{lstpts=}
\for{ii=1 to \nplan}{
  \if{\face isitemof \faces[\ii;]}{
    \text{lstpts= wims(append item \listpoint[\ii] to \lstpts)}
  }
}
\text{lstpts = shuffle(\lstpts)}
%%%%%text{lstpts=G,M,O}
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
\text{tplan=\ptsplan[1]\ptsplan[2]\ptsplan[3]}

%%%%%integer{face=2}
  text{tplan=GMO}

%%%%% Choix de la  droite
\integer{facedte=randint(1..\nf)}
  %%%%%integer{facedte=5}
\text{lstpt=}
\for{ ii = 1 to \ndte}{
  \if {\facedte isitemof \faces[\ii;]}{
    \text{lstpt= wims(append item \listpoint[\ii] to \lstpt)}
  }
}
\text{lstpt = shuffle (\lstpt)}
\text{lstpt=item(1..2,\lstpt)}
\text{lstpt=wims(sort list \lstpt)}
%%%%%text{lstpt=Q,T}
\text{pt1 = \lstpt[1]}
\text{pt2 = \lstpt[2]}
\for{i=1 to 6}{
  \if{\pt1 isitemof \dtept[\i;] and \pt2 isitemof \dtept[\i;]}{
    \text{pt1=\dtept[\i;1]}
    \text{pt2=\dtept[\i;2]}
    \integer{i=7}
  }
}
\integer{indpt1=position(\pt1,\listpoint)}
\integer{indpt2=position(\pt2,\listpoint)}
\integer{indpl1=position(\ptsplan[1],\listpoint)}
\integer{indpl2=position(\ptsplan[2],\listpoint)}
\integer{indpl3=position(\ptsplan[3],\listpoint)}
\text{dessin=
 poly blue,\pt[\indpl1;],\pt[\indpl2;],\pt[\indpl3;]
   segment \pt[\indpt1;],\pt[\indpt2;],red
}
\text{incluse=(\pt1\pt2)}

%%%%% détermination des bonnes réponses
#if (defined TARGET_interdtepl1  || defined TARGET_interdtepl2  || defined TARGET_interdtepl3 )
#include "cubedraw.inc"
\text{goodrep=pt}
\text{facedest= wims(listintersect \faces[\indpt1;] and \faces[\indpt2;])}
\if{\face isitemof \facedest}{
  \text{goodrep=\incluse}
}{
  \text{faceimpair=1,3,5}
  \if{\face isitemof \faceimpair}{
    \integer{facepar=\face+1}}
     {\integer{facepar=\face-1}}
  \if{\facepar isitemof \facedest}{
    \text{goodrep=vide}
  }{
    %%%%%tester droites des milieux
    \if{ \face=1 or \face=2}{
      \text{mill=Q,R,S,T}
    }
    \if{ \face=3 or \face=4}{
      \text{mill=O,P,K,L}
    }
    \if{ \face=5 or \face=6}{
      \text{mill=I,J,M,N}
    }
    \if{\pt1 isitemof \mill and \pt2 isitemof \mill}{
      \text{goodrep=vide}
    }
  }
}
\if{\goodrep=pt}{
%%%%% on cherche une droite du plan coplanaire avec la droite
  \text{lstdtes=\facedtes[\face;]}
  \integer{idte=0}
  \for{i=1 to 4}{
    \if{\idte=0}{
      \text{coplan=wims(listintersect \facedest and \dteface[\lstdtes[\i];])}
      \if{\coplan=}{}{
        \text{goodrep=\nomdte[\lstdtes[\i]] inter (\pt1\pt2)}
        \integer{idte=\i}
%%%%% on essaie de nommer le point d'intersection
        \text{lespts=wims(declosing \nomdte[\lstdtes[\i]])}
        \text{pt3=wims(text copy \lespts mask 10)}
        \text{pt4=wims(text copy \lespts mask 01)}
        \if{\pt1=\pt3 or \pt1=\pt4 or \pt1=\milieu[\lstdtes[\i]]}{
          \text{goodrep=\pt1}
        }
        \if{\pt2=\pt3 or \pt2=\pt4 or \pt2=\milieu[\lstdtes[\i]]}{
          \text{goodrep=\pt2}
        }
        \for{nn = 1 to 12}{
          \if{\pt1 isitemof \dtept[\nn;] and \pt2 isitemof \dtept[\nn;] and \pt3 isitemof \dtept[\nn;]}{
            \text{goodrep=\pt3}
          }
          \if{\pt1 isitemof \dtept[\nn;] and \pt2 isitemof \dtept[\nn;] and \pt4 isitemof \dtept[\nn;]}{
            \text{goodrep=\pt4}
          }

        }
      }
     }
   }
 }
#endif
#if (defined TARGET_interdtepl4  || defined TARGET_interdtepl5 )
# include "tetradraw.inc"
\text{goodrep=pt}
\text{facedest= wims(listintersect \faces[\indpt1;] and \faces[\indpt2;])}
\if{ \face isitemof \facedest}{
  \text{goodrep=\incluse}
}{
  !! calcul de la pente de la droite choisie
  \text{cpt1=\pt[\indpt1;]}
  \text{cpt2=\pt[\indpt2;]}
  \rational{den1=\cpt1[1] - (\cpt2[1])}
  \rational{num1=\cpt1[2] - (\cpt2[2])}
  \integer{trouvept=0}
  \text{lstdte=\facedtes[\face;]}
  \for{ ii=1 to 3}{
    \if{\trouvept=0}{
      \integer{jj=\lstdte[\ii]}
      \text{dte=\dtept[\jj;]}
      \integer{indpt3=position(\dte[1],\listpoint)}
      \integer{indpt4=position(\dte[2],\listpoint)}
      \text{pt3=\pt[\indpt3;]}
      \text{pt4=\pt[\indpt4;]}
      \rational{den2=\pt3[1] - (\pt4[1])}
      \rational{num2=\pt3[2] - (\pt4[2])}
      \rational{colin=\den1 *(\num2) - (\den2)*(\num1)}
      \if{ \colin<0.001 and \colin>-0.001}{
        \text{goodrep=vide}
        \integer{trouvept=1}
      }
    }
  }
}
\if{\goodrep=vide}{
  \if{\pt1 isitemof \ptsplan}{
    \text{goodrep=\pt1}
  }
  \if{\pt2 isitemof \ptsplan}{
  \text{goodrep=\pt2}
  }
}
\if{\goodrep=pt}{
%%%%% on cherche une droite du plan coplanaire avec la droite
  \text{lstdtes=\facedtes[\face;]}
  \integer{idte=0}
  \for{i=1 to 3}{
    \if{\idte=0}{
      \text{coplan=wims(listintersect \facedest and \dteface[\lstdtes[\i];])}
      \if{\coplan=}{}{
        \text{goodrep=\nomdte[\lstdtes[\i]] inter (\pt1\pt2)}
        \integer{idte=\i}
%%%%% on essaie de nommer le point d'intersection
        \text{lespts=wims(declosing \nomdte[\lstdtes[\i]])}
        \text{pt3=wims(text copy \lespts mask 10)}
        \text{pt4=wims(text copy \lespts mask 01)}
        \if{\pt1=\pt3 or \pt1=\pt4 or \pt1=\tiers1[\lstdtes[\i]] or \pt1=\tiers2[\lstdtes[\i]]}{
          \text{goodrep=\pt1}
        }
        \if{\pt2=\pt3 or \pt2=\pt4 or \pt2=\tiers1[\lstdtes[\i]] or \pt2=\tiers2[\lstdtes[\i]]}{
          \text{goodrep=\pt2}
        }
      }
    }
  }
}
#endif
\if{\ggb==2}{
  \text{lp_enon=aa=Segment(\pt1,\pt2)
SetColor[aa,red]
ShowLabel[aa, false]
SetLineThickness[aa,10]
bb=Polygon(\ptsplan[1],\ptsplan[2],\ptsplan[3])
SetColor[bb,blue]
ShowLabel[bb, false]}
\text{suplab=a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w}
\for{i in \suplab}{\text{t=ShowLabel[\i, false]
ShowLabel[\i _1, false]}
\text{lp_enon=wims(append line \t to \lp_enon)}}
}
#if (defined TARGET_interdtepl1 || defined TARGET_interdtepl2 || defined TARGET_interdtepl3 )
#include "ggbc_milieu.inc"
#include "ggbc.inc"
#endif
#if (defined TARGET_interdtepl4 || defined TARGET_interdtepl5 )
#include "ggbt.inc"
#endif

\if{\ggb==2}{
\text{A=slib(geo2D/geogebra width=600;
height=600;
\fig_ggb)}}

\statement{
#include "intro_stat.inc"
   \objet. \tpoints.
   <p>
  On considère la droite <span style="color:red">(\pt1\pt2)</span> et
  le plan <span style="color:blue">(\tplan)</span> et on s'intéresse à leur
 intersection.
 </p>
 <label for="reply1">(\tplan)\(\cap\)(\pt1\pt2)=</label>\embed{reply1,8}
<div class="wims_instruction">
  <ul class="wims_nopuce">
  <li>
  Si la droite est incluse dans le plan, taper \incluse.
  </li><li>
  Si la droite est strictement parallèle au plan, taper <span class="tt">vide</span>.
  </li><li>
  Sinon, si le point d'intersection est déjà nommé sur la figure, taper ce point.
  Dans le cas contraire, taper (xy)  <span class="tt">
  inter</span>
  \incluse, où (xy) est le nom d'une droite du plan (\tplan) en respectant l'ordre
  alphabétique dans ce nom.
  </li></ul>
 </div>
</div>
\if{\ggb=1}{</div>}
}
\answer{position relative}{\goodrep}{type=raw}
