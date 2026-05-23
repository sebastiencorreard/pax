target=trans2 egalite2 para1

\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "css.inc"

\matrix{nom=A,B,C,D
E,F,G,H
M,N,R,P}
\text{don=randrow(\nom)}
\text{don=shuffle(\don)}
\text{A=item(1,\don)}
\text{B=item(2,\don)}
\text{C=item(3,\don)}
\text{D=item(4,\don)}


\integer{XA=random(-10..10)}
\integer{YA=random(-10..10)}
\integer{XB=random(-10..10)}
\integer{YB=random(-10..10)}
\integer{XC=random(-10..10)}
\integer{YC=random(-10..10)}

\integer{tmp=(\XB-\XA)*(\YC-\YA)-(\YB-\YA)*(\XC-\XA)}
\if{\tmp=0}
{\integer{XA=1}
\integer{YA=-1}
\integer{XB=3}
\integer{YB=5}
\integer{XC=-2}
\integer{YC=-2}}

\text{vect=\overrightarrow{\A \B}}
\integer{Vx=\XB-\XA}
\integer{Vy=\YB-\YA}
\integer{XD=\XC+\Vx}
\integer{YD=\YC+\Vy}

#if defined TARGET_trans2
\title{Image par une translation 2}
\keywords{translation}
\text{enonce=Dans le plan muni d'un repère, les points \(\A) et \(\B) ont
  pour coordonnées respectives \((\XA,\YA)) et \((\XB,\YB)).
  Quelles sont les coordonnées de l'image du point de coordonnées \((\XC,\YC))
  par la translation de vecteur \(\vect)}
\text{textrep=L'image du point de coordonnées \((\XC,\YC)) par la translation de vecteur \(\vect) a pour coordonnées}
#endif
#if defined TARGET_egalite2
\title{Égalité vectorielle 2}
\keywords{vectors}
\matrix{choix=\XC,\YC,\XD,\YD,\C \D
\XD,\YD,\XC,\YC,\D \C}
\text{choix=randrow(\choix)}
\integer{XC=item(1,\choix)}
\integer{YC=item(2,\choix)}
\integer{XD=item(3,\choix)}
\integer{YD=item(4,\choix)}
\text{vect2=item(5,\choix)}
\text{enonce=Dans le plan muni d'un repère, les points \(\A), \(\B) et \(\C)
  ont coordonnées respectives \((\XA,\YA)), \((\XB,\YB)) et \((\XC,\YC)).
  Quelles sont les coordonnées du point \(\D) tel que
  \(\overrightarrow{\vect2}=\overrightarrow{\A \B})}
\text{textrep=Le point \(\D) a pour coordonnées}
#endif
#if defined TARGET_para1
\title{Parallélogramme (4ième sommet)}
\keywords{parallelogram}
\text{enonce=Dans le plan muni d'un repère, les points \(\A), \(\B) et \(\C)
  ont pour coordonnées respectives \((\XA,\YA)), \((\XB,\YB)) et \((\XC,\YC)).
  Quelles sont les coordonnées du point \(\D) tel que \(\A \B \D \C) soit
  un parallèlogramme}
\text{textrep=Le point \(\D) a pour coordonnées}
#endif

\statement{
\enonce ?

<hr class="wimscenter" style="width:50%">
<span class="ans">Votre réponse</span> :
<div><label for="reply1">\textrep </label>(\embed{r1,3},\embed{r2,3}).</div>
}

\answer{Première coordonnée}{\XD}{type=numexp}
\answer{Deuxième coordonnée}{\YD}{type=numexp}
