target=thalesA1
#include "author.inc"
#define TITRE Triangles et proportionnalité
#if defined TARGET_thalesA1
# define NUM A1
#endif
\title{TITRE NUM}
\matrix{sommets=A,B,C,D,E,F
E,F,G,H,I,J
M,N,O,P,Q,R}
\text{sommet=randrow(\sommets)}
\text{sommet=shuffle(\sommet)}
\text{A=item(1,\sommet)}
\text{B=item(2,\sommet)}
\text{C=item(3,\sommet)}
\text{D=item(4,\sommet)}
\text{E=item(5,\sommet)}
\text{F=item(6,\sommet)}
\text{X=randrow(\D,\B,\E,\C
\E,\C,\D,\B)}
 \text{dessin=segment 20,20,180,130,black
segment 20,20,50,180,black
segment 180,130,50,180,red
segment 35,100,100,75,red
text black,10,10,medium,\A
text black,190,135,medium,\X[2]
text black,35,185,medium,\X[4]
text black,25,100,medium,\X[3]
text black,115,70,medium,\X[1]}
\text{image=draw(200,200
\dessin)}

\text{good=(\D\E) et (\B\C) sont parallèles}
\text{bad=(\D\E) et (\B\C) sont perpendiculaires,(\D\E) et (\B\C) sont sécantes}

\statement{<div class="wims_columns">
 <div class="medium_size img_col"><img src="\image" alt=""></div>
 <div class="medium_size text_col">
   Dans la situation ci-contre, quelle hypothèse faut-il vérifier pour conclure que :
   <div class="wimscenter">\(\frac{\A\D}{\A\B}=\frac{\A\E}{\A\C}=\frac{\E\D}{\C\B})</div>
</div></div>
}
\choice{}{\good}{\bad}
