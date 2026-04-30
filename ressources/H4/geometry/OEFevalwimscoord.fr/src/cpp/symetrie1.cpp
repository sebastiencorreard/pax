target=symetrie1

\title{Coordonnées du symétrique}
\author{Cyrille,Douriez;Bruno,Mifsud}
\email{cyrille.douriez@ac-amiens.fr;communaute.mutuwims@laposte.net}
%%%% 16/03/22%%%%
\computeanswer{no}
\keywords{symmetry,coordinates}
\integer{x1=random(15..40)}
\integer{x2=random(-20..60)}
\integer{y1=random(-20..20)}
\integer{y2=\y1+random(2..20)*randint(-1,1)}
\integer{x3=2*\x2-\x1}
\integer{y3=2*\y2-\y1}
\integer{x2d=2*\x2}
\integer{y2d=2*\y2}
\matrix{points=A,B,A,D,F,M,R,A
B,A,C,E,G,N,S,B
C,C,B,F,H,P,T,C}
\integer{choix=random(1..8)}
%%%%% affichage en ligne des coordonnées %%%%%
\if{\confparm1=2}
{
 \text{affcoord=[\left( reply1 ; reply2 \right)]}
}{
 \text{affcoord=[\begin{pmatrix} reply1 \\ reply2 \end{pmatrix}]}
}
%%%%%%%%% sol
\text{xsol=x_\points[3;\choix]}
\text{ysol=y_\points[3;\choix]}
\statement{
<p>Dans le plan muni d'un repère \((O,I,J)\), on donne \(\points[1;\choix](\x1 ; \y1)\) et \(\points[2;\choix](\x2 ; \y2)\).
</p>
<div class="wims_question">
  Déterminer les coordonnées de \(\points[3;\choix]\), symétrique de \(\points[1;\choix]\) par rapport à \(\points[2;\choix]\).
<div class="wimscenter">\special{mathmlinput \affcoord,5,noanswer
reply1,,color:blue;text-align:center;
reply2,,color:blue;text-align:center;
}
.</div></div>}
\answer{\( x_\points[3;\choix]\)}{\x3}{type=numeric}
\answer{\( y_\points[3;\choix] \)}{\y3}{type=numeric}
\solution{<p>Le point \(\points[2;\choix]) est le milieu du segment \( [\points[1;\choix] \points[3;\choix]] \).
Si \((x_\points[3;\choix];y_\points[3;\choix])\) sont les coordonnées de
\(\points[3;\choix]\) cela se traduit par la relation suivante sur les coordonnées : </p>
\(\left\lbrace
 \begin{array}{lcl}
\frac{\x1+\xsol}{2} & = & \x2 \\ \frac{\y1+\ysol}{2} & = & \ \y2
 \end{array}
\right.
\)
\(\Leftrightarrow
\left\lbrace
\begin{array}{lcl}
\x1+x_\points[3;\choix] &= & \x2d \\ \y1+y_\points[3;\choix] & = & \y2d
\end{array}
\right.\)
\(\Leftrightarrow \left\lbrace \begin{array}{lcl}x_\points[3;\choix]=\x3 \\ \y_\points[3;\choix]=\y3 \end{array}\right.\)
<p>D'où le résultat.</p>
}
