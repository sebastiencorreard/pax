target=vecteur1,vecteur2,vecteur3,vecteur4,vecteur5
#define TITRE Coordonnées d'un vecteur
\keywords{coordinates, vectors}
#include "author.inc"

\text{lettres=shuffle(A,B,C,D,E,F,G,H,K,L,M,N,P)}
\text{A=\lettres[1]}
\text{B=\lettres[2]}

#if defined TARGET_vecteur1
 \title{TITRE 1}
 \text{v=shuffle(1,2,3,4,5,6,7,8,9,10)}
 \integer{x2=\v[1]}
 \integer{x1=\v[2]}
 \integer{y2=\v[3]}
 \integer{y1=\v[4]}
#endif
#if defined TARGET_vecteur2
 \title{TITRE 2}
 \text{v=shuffle(1,2,3,4,5,6,7,8,9,10)}
 \integer{x2=\v[1]}
 \integer{x1=-\v[2]}
 \integer{y2=\v[3]}
 \integer{y1=\v[4]}
#endif
#if defined TARGET_vecteur3
 \title{TITRE 3}
 \text{v=shuffle(1,2,3,4,5,6,7,8,9,10)}
 \integer{x2=-\v[1]}
 \integer{x1=-\v[2]}
 \integer{y2=\v[3]}
 \integer{y1=\v[4]}
#endif
#if defined TARGET_vecteur4
 \title{TITRE 4}
 \text{v=shuffle(1,2,3,4,5,6,7,8,9,10)}
 \integer{x2=-\v[1]}
 \integer{x1=-\v[2]}
 \integer{y2=-\v[3]}
 \integer{y1=\v[4]}
#endif
#if defined TARGET_vecteur5
 \title{TITRE 5}
 \text{v=shuffle(1,2,3,4,5,6,7,8,9,10)}
 \integer{x2=-\v[1]}
 \integer{x1=-\v[2]}
 \integer{y2=-\v[3]}
 \integer{y1=-\v[4]}
#endif

\text{x=simplify(\x2-\x1)}
\text{y=simplify(\y2-\y1)}

\if{\confparm1=2}
{
 \text{affcoord=[\left( reply1 ; reply2 \right)]}
 \text{cor1=(x_B-x_A ; y_B-y_A)}
 \text{cor2=(\x2-(\x1) ; \y2-(\y1))}
 \text{cor3=(\x ; \y) }
}{
 \text{affcoord=[\begin{pmatrix} reply1 \\ reply2 \end{pmatrix}]}
 \text{cor1=\begin{pmatrix} x_B-x_A \\ y_B-y_A\end{pmatrix}}
 \text{cor2=\begin{pmatrix}\x2-(\x1) \\ \y2-(\y1)\end{pmatrix}}
 \text{cor3=\begin{pmatrix}\x \\ \y\end{pmatrix}}
}

\statement{
   Soient \(\A) et \(\B) deux points du plan de coordonnées respectives
   \((\x1 ; \y1)) et \((\x2 ; \y2 )) dans un repère \((O,I,J)).
<p>
  Quelles sont les coordonnées du vecteur \(\overrightarrow{\A \B}\) ?
</p><div class="spacer">
  <b>Votre réponse</b> :
  Les coordonnées du vecteur \(\overrightarrow{\A \B}) sont
<div class="wimscenter">
\special{mathmlinput \affcoord,5,noanswer
reply1,,color:blue;text-align:center;
reply2,,color:blue;text-align:center;
}
.</div>
</div>}

\answer{Abscisse}{\x}{type=numexp}
\answer{Ordonnée}{\y}{type=numexp}

\solution{Pour \(A) de coordonnées \((x_A;y_A)\) et \(B\) de coordonnées \((x_B;y_B)\), les coordonnées
du vecteur \(\overrightarrow{A B}) sont données par la formule :
<div class="wimscenter">
\(\cor1)
</div>
On utilise la formule et on obtient les coordonnées du vecteur \(\overrightarrow{\A \B}\)
<div class="wimscenter">
\(\cor2 = \cor3).
</div>}
