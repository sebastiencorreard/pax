target=trans1 egalite1

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "css.inc"

\text{vect=randitem(u,v,w)}
\text{pt=randitem(A,B,C,M,N)}
\text{pt2=\pt'}
\integer{Vx=random(1,-1)*random(1..10)}
\integer{Vy=random(1,-1)*random(1..10)}
\integer{XA=random(-10..10)}
\integer{YA=random(-10..10)}
\integer{XB=\XA+\Vx}
\integer{YB=\YA+\Vy}

#if defined TARGET_trans1
\keywords{translation}
\title{Image par une translation 1}
\text{enonce=Dans le plan muni d'un repère, le point \(\pt\) a pour
  coordonnées \((\XA,\YA)\).
  Quelles sont les coordonnées de l'image du point \(\pt\) par la translation
  de vecteur \(\overrightarrow{\vect}(\Vx,\Vy))&nbsp;}
\text{textrep=L'image du point \(\pt) par la translation de vecteur
  \(\overrightarrow{\vect}) a pour coordonnées}
#endif
#if defined TARGET_egalite1
\keywords{vectors}
\title{Égalité vectorielle 1}
\matrix{choix=\XA,\YA,\XB,\YB,\pt \pt2
\XB,\YB,\XA,\YA,\pt2 \pt}
\text{choix=randrow(\choix)}
\integer{XA=item(1,\choix)}
\integer{YA=item(2,\choix)}
\integer{XB=item(3,\choix)}
\integer{YB=item(4,\choix)}
\text{vect2=item(5,\choix)}
\text{enonce=Dans le plan muni d'un repère, le point \(\pt\) a pour coordonnées
  \((\XA,\YA)). Le vecteur \(\overrightarrow{\vect}) a pour coordonnées
  \((\Vx,\Vy)). Quelles sont les coordonnées du point \(\pt2) tel que
  \(\overrightarrow{\vect2}=\overrightarrow{\vect})&nbsp;}
\text{textrep=Le point \(\pt2) a pour coordonnées}
#endif
\statement{
\enonce?
<hr class="wimscenter" style="width:50%">
<span class="ans">Votre réponse</span> :
<div><label for="reply1">\textrep</label>(\embed{r1,3},\embed{r2,3}).</div>
}

\answer{Première coordonnée}{\XB}{type=numexp}
\answer{Deuxième coordonnée}{\YB}{type=numexp}
