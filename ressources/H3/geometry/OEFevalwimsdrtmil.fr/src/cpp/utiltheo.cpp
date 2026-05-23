target=utiltheo1 utiltheo2 utiltheo3
#define TITRE Triangles et parallèles

\text{lt=shuffle(A,B,C,D,E,F,G,H)}
\text{A=\lt[1]}
\text{B=\lt[2]}
\text{C=\lt[3]}
\text{I=\lt[4]}
\text{J=\lt[5]}

#if defined TARGET_utiltheo1
\title{TITRE B1}
 \text{enonce=\A\B\C est un triangle. randitem(\I est le milieu du côté
 \([\A\B]\) et \J le milieu du côté \([\A\C]\),\I et \J sont respectivement
 les milieux des côtés \([\A\B]\) et \([\A\C]\)).
 <br>Montrer que la droite \((\I\J)\) est parallèle à la droite \((\B\C)\).}
 \integer{good=1}
#endif
#if defined TARGET_utiltheo2
\title{TITRE B2}
 \text{enonce=\A\B\C est un triangle et \I est le milieu du côté \([\A\B]\).
 La parallèle à \((\B\C)\) passant par \I coupe le côté \([\A\C]\) en \J.
 <br>Montrer que \J est le milieu de \([\B\C]\).}
 \integer{good=2}
#endif
#if defined TARGET_utiltheo3
\title{TITRE B3}
 \integer{long=randint(12..25)}
 \text{enonce=\A\B\C est un triangle. randitem(\I est le milieu du côté \([\A\B]\)
 et \J le milieu du côté \([\A\C]\),
 \I et \J sont respectivement les milieux des côtés \([\A\B]\) et \([\A\C]\)).
 Le segment \([\B\C]\) mesure \long cm.<br>Calculer \(\I\J\).}
 \integer{good=3}
#endif

\text{bad=Si une droite passe par les milieux de deux côtés d'un
  triangle alors elle est parallèle au troisième côté.,
  Si une droite est parallèle à un côté d'un triangle et passe par le milieu
  d'un deuxième alors elle passe par le milieu du troisième côté.,
  Si un segment joint les milieux de deux côtés d'un triangle alors
  il mesure la moitié de la longueur du troisième côté.}
\text{Good=item(\good,\bad)}

\statement{
  Voici l'énoncé d'un problème :
<div class="wimscenter" style="font-style:italic">\enonce</div>
   Quelle propriété parmi les suivantes faut-il utiliser pour répondre à la question ?}

\choice{}{\Good}{\bad}
