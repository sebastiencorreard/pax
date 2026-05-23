target=hypotenuse1 hypotenuse2 hypotenuse4
#define TITRE Reconnaître l'hypoténuse
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}

\integer{xmax=randint(300..350)}
\integer{ymax=200}

#if defined TARGET_hypotenuse1
 \title{TITRE 1}
#include "triangle1.inc"
 \text{bad=[\A\B],[\A\C]}
 \text{good=[\B\C]}
 \text{question=Quelle est son hypoténuse}
#endif

#if defined TARGET_hypotenuse2
 \title{TITRE 2}
#include "triangle2.inc"
 \text{bad=[\A\B],[\A\C]}
 \integer{ymax=200}
 \integer{xmax=200}
 \text{good=[\B\C]}
 \text{question=Quelle est son hypoténuse}
#endif

#if defined TARGET_hypotenuse4
 \title{TITRE 4}
#include "triangle1.inc"
 \integer{nx=\s[5]-(\s[3])}
 \integer{ny=\s[6]-(\s[4])}
 \real{N=sqrt((\nx)^2+(\ny)^2)}
 \real{l=(\xmax-40)*(\ymax-40)/\N}
 \integer{xd=\s[1]+\ny*\l/\N}
 \integer{yd=\s[2]-\nx*\l/\N}
 \integer{xd2=\xd+10*\nx/\N}
 \integer{yd2=\yd+10*\ny/\N}
 \integer{tdy=\nx<0?\yd+5:\yd-15}
 \text{dessin=\dessin
segment \s[1],\s[2],\xd,\yd,black
segment \xd2,\yd2,\xd2-10*\ny/\N,\yd2+10*\nx/\N,red
segment \xd2-10*\ny/\N,\yd2+10*\nx/\N,\xd-10*\ny/\N,\yd+10*\nx/\N,red}
 \text{compenonce=\D est le pied de la hauteur issue de \A du triangle \A\B\C.}
 \integer{ch=randitem(1,2)}
 \text{tri=item(\ch,\A\D\C,\A\D\B)}
 \text{question=Quelle est l'hypoténuse du triangle \tri}
 \text{good=item(\ch,[\A\C],[\A\B])}
 \text{bad=[\A\C],[\A\B],[\A\D],[\B\C],[\B\D],[\D\C]}
#endif

\text{figure=draw(\xmax,\ymax
\dessin)}

\statement{<div class="wims_columns">
 <div class="medium_size img_col">
  <img src="\figure" alt=""></div>
  <div class="medium_size text_col">
\A\B\C est un triangle rectangle en \A. \compenonce
<div class="spacer">
   \question ?
  </div>
</div>
</div>
}

\choice{}{\good}{\bad}
