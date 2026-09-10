target=sumvect sumvect1
#if defined TARGET_sumvect
\author{Bruno, Mifsud;Hubert, Prohal}
\email{communaute.mutuwims@laposte.net;hubert.proal@ac-aix-marseille.fr}
#endif
#if defined TARGET_sumvect1
\author{Bernadette, Perrin-Riou}
\email{bernadette.m.riou@orange.fr}
#endif
\keywords{vectors}
\format{html}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_sumvect
\text{taille=medium}
\text{color=blue,red,green,black}
#endif
#if defined TARGET_sumvect1
\text{taille=large}
\text{color=black,black,black,green}
#endif
%%%%%%%%%% exercice de Régine Mangeard modifié
\text{lstpts=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X}
\text{ind=shuffle(24)}
\text{pt1=\lstpts[\ind[1]]}
\text{pt2=\lstpts[\ind[2]]}
\text{pt3=\lstpts[\ind[3]]}
%%%% coord de tous les points nommés
\text{abs=0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3}
\text{cot=0,0,0,0,1,1,1,1,2,2,2,2,0,0,0,0,1,1,1,1,2,2,2,2}
\text{ord=0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1}
\matrix{coord=\abs
\ord
\cot}
\text{alphabet=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X}
\text{coord2d=}
\for{s=1 to 24}{
  \text{coord2d=\coord2d
  pari([\abs[\s]*5+(\ord[\s])*3,\cot[\s]*5+(\ord[\s])*2]),\alphabet[\s]}
}
\matrix{coord2d=wims(nonempty lines \coord2d)}
#if defined TARGET_sumvect1
\text{coord2dmagnetic=wims(replace internal ; by , in \coord2d[;1,2])}
\text{snaptopoints=snaptopoints \coord2dmagnetic}
#endif
%%%%%%%%%%% u+v=sol
\integer{ux=\abs[\ind[2]]-\abs[\ind[1]]}
\integer{uy=\ord[\ind[2]]-\ord[\ind[1]]}
\integer{uz=\cot[\ind[2]]-\cot[\ind[1]]}
\integer{vx=\abs[\ind[3]]-\abs[\ind[2]]}
\integer{vy=\ord[\ind[3]]-\ord[\ind[2]]}
\integer{vz=\cot[\ind[3]]-\cot[\ind[2]]}
%%%%% trouver un autre représentant pour v1 et v2
%%% remplacer u
%%% prendre un point puis un autre et regarder si le vecteur a les même coordonnées que u
\for{i=1 to 24}{
  \for{j=1 to 24}{
    \integer{wx=\abs[\j]-\abs[\i]}
    \integer{wy=\ord[\j]-\ord[\i]}
    \integer{wz=\cot[\j]-\cot[\i]}
    \if{\wx=\ux and \wy=\uy and \wz=\uz}{
      \integer{i1=\i}
      \integer{i2=\j}
    }
  }
}
\text{pt1bis=\lstpts[\i1]}
\text{pt2bis=\lstpts[\i2]}
\text{v1bis=\overrightarrow{\pt1bis \pt2bis}}
%%% même chose avec v : prendre un point puis un autre et regarder si le vecteur a les même coordonnées que v
\for{i=1 to 24}{
  \for{j=1 to 24}{
    \integer{tx=\abs[\j]-\abs[\i]}
    \integer{ty=\ord[\j]-\ord[\i]}
    \integer{tz=\cot[\j]-\cot[\i]}
    \if{\tx=\vx and \ty=\vy and \tz=\vz}{
      \integer{j1=\i}
      \integer{j2=\j}
    }
  }
}
\text{pt3bis=\lstpts[\j1]}
\text{pt4bis=\lstpts[\j2]}
\text{v2bis=\overrightarrow{\pt3bis \pt4bis}}

%%%%%%% tracé du vecteur 1 : colin à u
\text{vectv1bis= arrow \coord2d[\i1;1],\coord2d[\i1;2],\coord2d[\i2;1],\coord2d[\i2;2],10,\color[1]}
%%%%%%tracé du vecteur u
\text{vectv1= darrow \coord2d[\ind[1];1],\coord2d[\ind[1];2],\coord2d[\ind[2];1],\coord2d[\ind[2];2],10,\color[1]}
%%%%%%% tracé du vecteur 2 : colin à v
\text{vectv2bis= arrow \coord2d[\j1;1],\coord2d[\j1;2],\coord2d[\j2;1],\coord2d[\j2;2],10,\color[3]}
%%%%%%tracé du vecteur v
\text{vectv2= darrow \coord2d[\ind[2];1],\coord2d[\ind[2];2],\coord2d[\ind[3];1],\coord2d[\ind[3];2],10,\color[3]}

%%%%%%%%% cas Chasles évident pt2bis==pt3bis ie i2=j1
\text{vsolbis1= darrow \coord2d[\i1;1],\coord2d[\i1;2],\coord2d[\j2;1],\coord2d[\j2;2],10,\color[1]}
%%%%%%%%% cas Chasles en inversant les termes : XA+BX
\text{vsolbis2= darrow \coord2d[\j1;1],\coord2d[\j1;2],\coord2d[\i1;1],\coord2d[\i1;2],10,\color[1]}

\if{\i2=\j1}{
  \text{affsol=\vsolbis1}
  }{
    \if{\i1=\j2}{\text{affsol=\vsolbis2}
      }{
      \text{affsol=\vectv1
  \vectv2}
    }
  }
%%%%%
%%%% sol
\text{v1=\overrightarrow{\pt1 \pt2}}
\text{v2=\overrightarrow{\pt2 \pt3}}
\text{rep=\lstpts[\ind[3]]}
\text{vsol= darrow \coord2d[\ind[1];1],\coord2d[\ind[1];2],\coord2d[\ind[3];1],\coord2d[\ind[3];2],10,\color[2]}
%%%% somme des deux vecteurs
\integer{solx=\ux+\vx}
\integer{soly=\uy+\vy}
\integer{solz=\uz+\vz}
%%%%%%%

\matrix{dessin=
  xrange -2,20
  yrange -2,15
  poly black,0,0,0,10,15,10,15,0
  segment 0,5,15,5,black
  polyline black,0,10,3,12,18,12,18,2,15,0
  parallel 15,10,18,12,0,-5,2,black
  polyline gray,0,0,3,2,18,2
  polyline gray,0,5,3,7,18,7
  parallel 3,2,3,12,5,0,3,gray
  parallel 5,0,8,2,0,5,2,gray
  parallel 10,0,13,2,0,5,2,gray
  polyline black,5,0,5,10,8,12
  polyline black,10,0,10,10,13,12
  centered
  fontfamily 20px
  text \color[4],-0.2,-0.3,\taille,A
  text \color[4],4.8,-0.3,\taille,B
  text \color[4],9.8,-0.3,\taille,C
  text \color[4],14.8,-0.3,\taille,D
  text \color[4],-0.3,4.8,\taille,E
  text \color[4],4.7,4.8,\taille,F
  text \color[4],9.7,4.8,\taille,G
  text \color[4],14.7,4.8,\taille,H
  text \color[4],-0.3,9.8,\taille,I
  text \color[4],4.7,9.8,\taille,J
  text \color[4],9.7,9.8,\taille,K
  text \color[4],14.7,9.8,\taille,L
  text \color[4],2.8,1.8,\taille,M
  text \color[4],7.8,1.8,\taille,N
  text \color[4],12.8,1.8,\taille,O
  text \color[4],17.8,1.8,\taille,P
  text \color[4],2.7,6.8,\taille,Q
  text \color[4],7.7,6.8,\taille,R
  text \color[4],12.7,6.8,\taille,S
  text \color[4],17.7,6.8,\taille,T
  text \color[4],2.7,12.7,\taille,U
  text \color[4],7.7,12.7,\taille,V
  text \color[4],12.7,12.7,\taille,W
  text \color[4],17.7,12.7,\taille,X
  \snaptopoints
  linewidth 3
  \vectv1bis
  \vectv2bis
}
#if defined TARGET_sumvect1
\text{rep=wims(select \coord2d where column 3 isin \pt1,\lstpts[\ind[3]])}
\text{rep1=position(\pt1,\rep[;3])}
\text{rep2=position(\pt3,\rep[;3])}
\text{rep=wims(nospace \rep[\rep1;1,2],\rep[\rep2;1,2])}
\statement{
  <p>\name_instruction1</p>
  <div class="wims_question">
  \name_instruction2[1] \(\v1bis+\v2bis\) \name_instruction2[2] \(\pt1\).
  </div>
  <div class="wimscenter">
  \embed{reply1,500x300}
  </div>
}
\answer{}{[\dessin];arrows,\rep}{type=draw}
\text{repe=\reply1}
\real{deter=(\repe[3]-\repe[1])*(\rep[4]-\rep[2])-(\repe[4]-\repe[2])*(\rep[3]-\rep[1])}
\real{long=(\repe[3]-\repe[1])^2+(\repe[4]-\repe[2])^2-(\rep[3]-\rep[1])^2-(\rep[4]-\rep[2])^2}

\feedback{\sc_reply1<1}{
  <ul>
  \if{\repe[1]!=\rep[1] or \repe[2]!=\rep[2]}{<li>\name_orig[1].</li>}
  \if{\repe[3]!=\rep[3] or \repe[4]!=\rep[4]}{<li>\name_orig[2].</li>}
  <li>\if{\deter!=0}{\name_direction[1]}{\name_direction[2]}.</li>
  <li>\if{\long!=0}{\name_long[1]}{\name_long[2]}.</li>
  </ul>
   <div class="wimscenter">
  \draw{500,300}{\dessin
  \affsol
  \vsol
  arrow \rep,10,green
  }
  </div>
}
#else
\statement{
  <p class="wimscenter">
  \draw{500,300}{\dessin}</p>
  <p>\name_instruction1</p>
  <div class="wims_question">
  \name_instruction2
    <div class="wimscenter">
    \special{mathmlinput [\v1bis+\v2bis=\overrightarrow{\pt1 reply1\phantom{\,}}],2,noanswer
    reply1}.
    </div>
  </div>
}
\answer{\name_answer:}{\rep}{type=case}
\solution{
  <div class="wimscenter">
  \draw{500,300}{\dessin
\affsol
\vsol
  }
  </div>
  \if{\i2=\ind[2] and \i1=\ind[1] and \j1=\ind[3]}{
     <p>
     \name_feedback[1;1]: \(\v1+\v2=\widevec{\pt1 \pt3}) (\name_feedback[1;2]).
     </p>
   }{
    \if{\pt3bis==\pt2bis}{
       <p>\name_feedback[1;1] (\name_feedback[1;2]):
       \(\v1bis+\v2bis=\widevec{\pt1bis \pt4bis}\) <i>\name_pointille[1]</i>.</p>
       \if{\pt4bis!=\pt3}{
          <p>\name_hint, \name_feedback[4;] \(\,\pt1bis \pt4bis \pt3 \pt1\)
          \name_feedback[3;].
          \name_feedback[5;]
          \(\widevec{\pt1bis \pt4bis}\) \name_and \(\widevec{\pt1 \pt3}\)
          \name_feedback[6;].</p>
        }
     }{
      \if{\pt1bis==\pt4bis}{
         <p>
         \name_feedback[1;1] (\name_feedback[1;2]):
         \(\v1bis+\v2bis=\v2bis +\v1bis=\widevec{\pt3bis \pt2bis}\).
         </p>
          \if{\pt2bis!=\pt3}{
            <p>
            \name_hint, \name_feedback[4;]
            \(\,\pt3bis \pt2bis \pt3 \pt1\) \name_feedback[3;].
            \name_feedback[5;] \(\widevec{\pt3bis \pt2bis}\)
            \name_and \(\widevec{\pt1 \pt3}) \name_feedback[6;].
            </p>
          }
         }{
          \if{\v1==\v1bis}{}{
            <p>\name_hint,
             \name_feedback[4;] \(\,\pt1bis \pt2bis \pt2 \pt1 \) \name_feedback[3;].
             \name_feedback[5;] \(\v1bis) \name_and \(\v1\)
             <i>\name_pointille[1]</i> \name_feedback[6;].
            </p>
           }
          \if{\v2==\v2bis}{}{
            <p>
            \name_hint,
            \name_feedback[4;] \(\,\pt3bis \pt4bis \pt3 \pt2 \) \name_feedback[3;].
            \name_feedback[5;] \(\v2bis\) \name_and \(\v2\)
            <i>\name_pointille[2]</i> \name_feedback[6;].
            </p>
           }
           <p>\name_feedback[7;],\(\v1bis+\v2bis=\v1+\v2=\widevec{\pt1 \pt3})
           (\name_feedback[1;2]).</p>
         }
       }
     }
  <p>\name_feedback[2;] \(\pt3\).</p>
}
#endif
