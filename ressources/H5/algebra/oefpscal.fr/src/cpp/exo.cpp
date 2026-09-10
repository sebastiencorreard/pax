target= proj dist equ vnor med cercle triangle ctan tanc

#if defined TARGET_ctan
\title{Equation d'un cercle tangent}
#include "header.inc"
#include "param.inc"
\statement{Déterminer l'équation du cercle de centre \(A(\x2;\y2)),
   qui est tangent à la droite d d'équation \(y=\eqd). L'équation de ce cercle est :
<div class="wimscenter">
 \embed{reply 1}=0
</div>
<div class="wims_instruction">
<b>Remarque: </b> Donner la réponse sous forme dévelopée.
</div>
}
\answer{}{\equcertan}{type=default}
#endif
#if defined TARGET_tanc
\title{Tangente à un cercle}
#include "header.inc"
#include "param.inc"
\statement{Déterminer l'équation de la tangente au cercle de centre
\(A(\x2;\y2)), passant par le point \(M(\x1;\y1)).
<p>L'équation de cette tangente est :</p>
<div class="wimscenter">
   y=\embed{reply 1,5}x+\embed{reply 2,5}
</div>
<div class="spacer">
<b>Remarque: </b> Le point \(M) est situé sur le cercle.
</div>
}
\answer{}{\a}{type=default}
\answer{}{\b}{type=default}
#endif
#if defined TARGET_triangle
	\title{Droites remarquables d'un triangle}
#include "header.inc"
#include "param.inc"
 \statement{Dans un repère orthonormé, on considère trois points \(A(\x2;\y2)), \(B(\x0;\y0))
 et \(C(\x4;\y4)). Déterminer l'équation de la \droite.
<div class="wimscenter">
   L'équation de la \droite est \(y=) \embed{reply 1}
</div>}
\answer{}{\dr}{type=formal}
#endif
#if defined TARGET_proj
  \title{Projection orthogonale}
#include "header.inc"
#include "param.inc"
  \statement{
  <div class="float_right"><img src="\cercle" alt=""></div>
  On a représenté ci-contre une droite d passant par A(\x0;\y0)
  et admettant le vecteur \(\v)(\xv;\yv) pour vecteur \vec.
  Déterminer les coordonnées du point H projeté orthogonal de M(\x2;\y2) sur d.
<div class="wimscenter">
  H(\embed{reply 1,6};\embed{reply 2,6})
</div>
}
\answer{abs}{\x1}{type=default}
\answer{ord}{\y1}{type=default}
#endif
#if defined TARGET_dist
  \title{Distance à une droite}
#include "header.inc"
#include "param.inc"
  \statement{<div class="float_right"><img src="\cercle" alt=""></div>
  On a représenté ci-contre, une droite d passant par A(\x0;\y0) et
  admettant le vecteur \(\v)(\xv;\yv) pour vecteur \vec.
  Déterminer la distance du point M(\x2;\y2) à la droite  d.
<div class="wimscenter">
  dist(M,d)=\embed{reply 1,12}
</div>
<div class="wims_instruction">
 <b>Remarque:</b> Pour entrer \(\sqrt{a}),saisir
 <span class="tt">sqrt(a).</span>
 </div>
}
\answer{dist}{\dist}{type=formal}
#endif
#if defined TARGET_equ
\title{Equation d'une normale}
#include "header.inc"
#include "param.inc"
  \statement{
  <div class="float_right"><img src="\cercle" alt=""></div>
  On a représenté ci-contre, une droite d
  passant par A(\x0;\y0) et admettant le vecteur \(\v)(\xv;\yv) pour vecteur \vec.
  Déterminer l'équation réduite de la perpendiculaire à d
  passant par le point M(\x2;\y2).
<div class="wimscenter">
  y=\embed{reply 1,6}x+\embed{reply 2,6}
</div>
}
\answer{a}{\a1}{type=rational}
\answer{b}{\b1}{type=rational}
#endif
#if defined TARGET_vnor
\title{Vecteur normal à une droite}
#include "header.inc"
#include "param.inc"
  \statement{  <div class="float_right"><img src="\cercle" alt=""></div>
  On a représenté ci-contre une droite d passant par A(\x0;\y0)
  et admettant le vecteur \(\overrightarrow{u})(\xu;\yu) pour vecteur directeur.
  Déterminer les coordonnées d'un vecteur normal à d.
<div class="wimscenter">
   Le vecteur \(\overrightarrow{n}) de coordonnées (\embed{reply 1,6};\embed{reply 2,6})
   est normal à d.
</div>
}
\answer{a}{\rep1}{type=default}
\answer{b}{\rep2}{type=default}
\real{t1=\xu*\rep1+\yu*\rep2}
\real{t2=(\rep1)^2+(\rep2)^2}
\condition{Les vecteurs \(\overrightarrow{u}) et \(\overrightarrow{n}) sont orthogonaux}{(\t1=0) and (\t2!=0)}
\solution{Le produit scalaire des vecteurs \(\overrightarrow{u}) et
\(\overrightarrow{n}) est égal à \t1.}
#endif
#if defined TARGET_med
  \title{Equation d'une médiatrice}
#include "header.inc"
#include "param.inc"
\statement{<div class="float_right"><img src="\med" alt=""></div>
   On a représenté ci-contre deux points A(\x0;\y0) et B(\x3;\y3).
   Déterminer l'équation réduite de la médiatrice du segment &#91; AB &#93;
<div class="wimscenter">
  y=\embed{reply 1,6}x+\embed{reply 2,6}
</div>
}
\answer{a}{\a1}{type=rational}
\answer{b}{\b1}{type=rational}
#endif
#if defined TARGET_cercle
  \title{Cercle tangent à une droite}
#include "header.inc"
#include "param.inc"
  \statement{<div class="float_right"><img src="\cerct>" alt=""></div>
  On a représenté ci dessous, une droite d passant par A(\x0;\y0) et admettant
  le vecteur \(\v)(\xv;\yv) pour vecteur \vec. Déterminer le rayon du
  cercle de centre M(\x2;\y2) et tangent à la droite  d.
<div class="wimscenter">
  R=\embed{reply 1,12}
</div>
<div class="wims_instruction">
 <b>Remarque:</b> Pour entrer \(\sqrt{a}),saisir
 <span class="tt">sqrt(a).</span>
 </div>
}
\answer{dist}{\dist}{type=formal}
#endif
