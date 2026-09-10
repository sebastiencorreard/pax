target=calcesp1 calcesp2 calcesp3 calcesp4 calcesp5

#include "author.inc"
#define TITRE Produit scalaire dans l'espace
#if defined TARGET_calcesp1
# define NUM 1
#endif
#if defined TARGET_calcesp2
# define NUM 2
#endif
#if defined TARGET_calcesp3
# define NUM 3
#endif
#if defined TARGET_calcesp4
# define NUM 4
#endif
#if defined TARGET_calcesp5
# define NUM 5
#endif
\title{TITRE NUM}
#if defined TARGET_calcesp1
\integer{ux=randint(-10..10)}
\integer{uy=randint(-10..10)}
\integer{uz=randint(-10..10)}
\integer{vx=randint(-10..10)}
\integer{vy=\vx+randint(1..5)*randint(1,-1)}
\integer{vz=randint(-10..10)}
\integer{p=\ux*\vx+\uy*\vy+\uz*\vz}
\statement{<p>
  L'espace est muni d'un repère orthonormal \((O,\vec{i},\vec{j},\vec{k})).
  On considère les vecteurs \(\vec{u}\left(\begin{array}{c} \ux \\ \uy \\ \uz \end{array}\right))
  et \(\vec{v}\left(\begin{array}{c} \vx \\ \vy \\ \vz \end{array}\right)) :</p><p>
  Calculer \(\vec{u}\cdot\vec{v}).</p>
<div class="wimscenter">
  <label for="reply1">\(\vec{u}\cdot\vec{v}) =</label> \embed{reply1,5} </div>
}
\answer{produit scalaire}{\p}{type=numeric}
#endif
#if defined TARGET_calcesp2
\matrix{V=slib(matrix/invertible 3,3)}

///// coordonnées de A: matrice m
\matrix{a=slib(matrix/random 1,3,5)}

///// coordonnées de B: A+u
\matrix{u=\V[1;]}
\matrix{b=pari(print([\a]+[\u]))}

///// coordonnées de C: A+v
\matrix{v=\V[2;]}
\matrix{c=pari(print([\a]+[\v]))}

\integer{p=\u[1]*\v[1]+\u[2]*\v[2]+\u[3]*\v[3]}
\statement{<p>
 L'espace est muni d'un repère orthonormal \((O,\vec{i},\vec{j},\vec{k})).
 On considère les points \(A(\a[1],\a[2],\a[3]),B(\b[1],\b[2],\b[3]))
 et \(C(\c[1],\c[2],\c[3])).</p>
<p>
 Calculer \(\overrightarrow{A B}\cdot\overrightarrow{A C}):
</p>
<div class="wimscenter"><label for="reply1">
\(\overrightarrow{A B}\cdot\overrightarrow{A C}) =</label> \embed{reply1,5} </div>
}
\answer{produit scalaire}{\p}{type=numeric}
#endif

#if defined TARGET_calcesp3
\matrix{V=slib(matrix/orthogonal 3,3)}
\matrix{V=pari(content([\V])^(-1)*[\V])}
\matrix{u=\V[1;]}
\matrix{v=\V[2;]}

\integer{x=randint(-5..5)}
\integer{y=randint(-5..5)}
\integer{k=randint(1..4)}

\if{\k=1}{
  ///// coordonnées de A: matrice m
  \matrix{a=pari(print(\x*[\u]+\y*[\v]))}
  ///// coordonnées de B: A+u
  \matrix{b=pari(print([\a]+[\u]))}
  ///// coordonnées de C: A+v
  \matrix{c=pari(print([\a]+[\v]))}
}
\if{\k=2}{
  ///// coordonnées de A: matrice m
  \matrix{b=pari(print(\x*[\u]+\y*[\v]))}
  ///// coordonnées de B: A+u
  \matrix{a=pari(print([\b]+[\u]))}
  ///// coordonnées de C: A+v
  \matrix{c=pari(print([\b]+[\v]))}
}
\if{\k=3}{
  ///// coordonnées de A: matrice m
  \matrix{c=pari(print(\x*[\u]+\y*[\v]))}
  ///// coordonnées de B: A+u
  \matrix{a=pari(print([\c]+[\u]))}
  ///// coordonnées de C: A+v
  \matrix{b=pari(print([\c]+[\v]))}
}
\if{\k=4}{
  ///// coordonnées de A: matrice m
  \matrix{b=pari(print(\x*[\u]+\y*[\v]))}
  ///// coordonnées de B: A+u
  \matrix{a=pari(print([\b]+[\u]+[\v]))}
  ///// coordonnées de C: A+v
  \integer{t=randitem(2,3,-2)}
  \matrix{c=pari(print([\b]+\t*[\u]+[\v]))}
}

text{test=pari(a=[\a];b=[\b]; c=[\c]; [(b-a)*(b-c)~,(b-c)*(a-c)~,(a-c)*(b-a)~])}

\integer{rep=\k}
\text{lstrep=\(A B C) est rectangle en A,\(A B C) est rectangle en B,\(A B C) est rectangle en C,\(A B C) n'est pas rectangle }
\statement{
  <p>
   L'espace est muni d'un repère orthonormal \((O,\vec{i},\vec{j},\vec{k})).
    On considère les points \(A(\a[1],\a[2],\a[3]),B(\b[1],\b[2],\b[3])) et
  \(C(\c[1],\c[2],\c[3])).</p>
  <p>Le triangle \(A B C) est-il rectangle ?</p>
  <ul class="wims_nopuce"><li>
  \embed{reply1,1}
  </li><li>
  \embed{reply1,2}
  </li><li>
  \embed{reply1,3}
  </li><li>
  \embed{reply1,4}
  </li></ul>
}
\answer{nature}{\rep;\lstrep}{type=radio}
#endif
#if defined TARGET_calcesp4
\matrix{V=slib(matrix/random 3,3)}
\matrix{u=\V[1;]}
\matrix{v=\V[2;]}
\integer{k=randint(1..4)}
\if{\k=1}{
 \integer{ux=\u[1]}
 \integer{uy=\u[2]=0?\u[1]:\u[2]}
 \integer{uz=\u[3]}
 \integer{vz=\v[3]}
 \integer{vx=\v[1]}
 \integer{d=randint(-5..5)}
 \text{vy=\d=0?x:texmath(x+\d)}
 \rational{x=-(\ux*\vx+\uz*\vz)/\uy-\d}
}
\if{\k=2}{
 \integer{uy=\u[2]}
 \integer{ux=\u[1]=0?\u[2]:\u[1]}
 \integer{uz=\u[3]}
 \integer{vz=\v[3]}
 \integer{vy=\v[2]}
 \integer{d=randint(-5..5)}
 \text{vx=\d=0?x:texmath(x+\d)}
 \rational{x=-(\uy*\vy+\uz*\vz)/\ux-\d}
}
\if{\k=3}{
 \integer{vx=\v[1]}
 \integer{vy=\v[2]=0?\v[1]:\v[2]}
 \integer{uz=\u[3]}
 \integer{vz=\v[3]}
 \integer{ux=\u[1]}
 \integer{d=randint(-5..5)}
 \text{uy=\d=0?x:texmath(x+\d)}
 \rational{x=-(\ux*\vx+\uz*\vz)/\vy-\d}
}
\if{\k=4}{
 \integer{vy=\v[2]}
 \integer{vx=\v[1]=0?\v[2]:\v[1]}
 \integer{uz=\u[3]}
 \integer{vz=\v[3]}
 \integer{uy=\u[2]}
 \integer{d=randint(-5..5)}
 \text{ux=\d=0?x:texmath(x+\d)}
 \rational{x=-(\uy*\vy+\uz*\vz)/\vx-\d}
}

\statement{
<p>
 L'espace est muni d'un repère orthonormal \((O,\vec{i},\vec{j},\vec{k})).
 Soient
 \(\vec{u}\left(\begin{array}{c} \ux \\ \uy \\ \uz\end{array}\right))
 et \(\vec{v}\left(\begin{array}{c} \vx \\ \vy \\ \vz\end{array}\right)).
 Déterminer la ou les valeurs de \(x) pour que les vecteurs \(\vec{u}) et \(\vec{v})
 soient orthogonaux :</p>
<div class="wimscenter"><label for="reply1">\(x\)=</label> \embed{reply1,3}.</div>
}
\answer{\(x\)}{\x}{type=numexp}
#endif
#if defined TARGET_calcesp5
\text{lstpts=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X}
\text{ind=shuffle(24)}
\text{pt1=\lstpts[\ind[1]]}
\text{pt2=\lstpts[\ind[2]]}
\text{pt3=\lstpts[\ind[3]]}
\text{pt4=\lstpts[\ind[4]]}
\text{abs=0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3}
\text{cot=0,0,0,0,1,1,1,1,2,2,2,2,0,0,0,0,1,1,1,1,2,2,2,2}
\text{ord=0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1}
\integer{ux=\abs[\ind[2]]-\abs[\ind[1]]}
\integer{uy=\ord[\ind[2]]-\ord[\ind[1]]}
\integer{uz=\cot[\ind[2]]-\cot[\ind[1]]}
\integer{vx=\abs[\ind[4]]-\abs[\ind[3]]}
\integer{vy=\ord[\ind[4]]-\ord[\ind[3]]}
\integer{vz=\cot[\ind[4]]-\cot[\ind[3]]}
\integer{p=\ux*\vx+\uy*\vy+\uz*\vz}
\text{v1=\overrightarrow{\pt1 \pt2}}
\text{v2=\overrightarrow{\pt3 \pt4}}
\text{dessin=
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
 text black,-0.2,-0.2,medium,A
 text black,4.8,-0.2,medium,B
 text black,9.8,-0.2,medium,C
 text black,14.8,-0.2,medium,D
 text black,-0.3,4.8,medium,E
 text black,4.7,4.8,medium,F
 text black,9.7,4.8,medium,G
 text black,14.7,4.8,medium,H
 text black,-0.3,9.8,medium,I
 text black,4.7,9.8,medium,J
 text black,9.7,9.8,medium,K
 text black,14.7,9.8,medium,L
 text black,2.8,1.8,medium,M
 text black,7.8,1.8,medium,N
 text black,12.8,1.8,medium,O
 text black,17.8,1.8,medium,P
 text black,2.7,6.8,medium,Q
 text black,7.7,6.8,medium,R
 text black,12.7,6.8,medium,S
 text black,17.7,6.8,medium,T
 text black,2.7,11.8,medium,U
 text black,7.7,11.8,medium,V
 text black,12.7,11.8,medium,W
 text black,17.7,11.8,medium,X
 linewidth 3
 arrow \abs[\ind[1]]*5+(\ord[\ind[1]])*3,\cot[\ind[1]]*5+(\ord[\ind[1]])*2,\abs[\ind[2]]*5+(\ord[\ind[2]])*3,\cot[\ind[2]]*5+(\ord[\ind[2]])*2,10,blue
 arrow \abs[\ind[3]]*5+(\ord[\ind[3]])*3,\cot[\ind[3]]*5+(\ord[\ind[3]])*2,\abs[\ind[4]]*5+(\ord[\ind[4]])*3,\cot[\ind[4]]*5+(\ord[\ind[4]])*2,10,green
}

\statement{
<div class="wims_columns">
 <div class="medium_size img_col">\draw{500,300}{\dessin}</div>
 <div class="medium_size text_col">
  L'espace est muni du repère orthonormal
 \((A,\overrightarrow{A B},\overrightarrow{A M},\overrightarrow{A E})).
  Calculer le produit scalaire \(\v1 \cdot \v2):
  <div class="wimscenter">
  <label for="reply1">\(\v1 \cdot \v2)= </label>\embed{reply1,7}.
  </div>
  </div></div>
}
\answer{\(\v1 \cdot \v2)}{\p}{type=numeric}
#endif
