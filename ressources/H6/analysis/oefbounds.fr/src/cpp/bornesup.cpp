target=bornesup1 bornesup2
#if defined TARGET_bornesup1
# define NUM 1
#endif
#if defined TARGET_bornesup2
# define NUM 2
#endif
\author{Chantal, Menini}
\email{chantal.menini@math.u-bordeaux.fr}
\credits{}
#include "lang_titles.inc"
#include "lang.inc"
\integer{a=randint(-2..2)}

%énoncé une ligne sera prise, texte puis 1 pour réponse juste et 0 pour réponse fausse
#if defined TARGET_bornesup1
\matrix{mhyp=\(A) majoré par \a,0,0,0,1,0,0
\(\forall x\in A\quad x\leq \a),0,0,0,1,0,0
\(\exists x\in A\quad x\leq \a),0,0,0,0,0,1
\(\exists x\in A\quad x< \a),0,0,0,0,0,1
\(A\subset \rbrack -\infty, \a \rbrack),0,0,0,1,0,0
\(A\subset \rbrack-\infty, \a \lbrack),0,0,0,1,0,0
\(\a\in A),0,0,0,0,0,1
\(A) minoré par \a,0,0,0,1,0,0
\(\forall x\in A\quad x\geq \a),0,0,0,1,0,0
\(\exists x\in A\quad x\geq \a),0,0,0,0,0,1
\(\exists x\in A\quad x> \a),0,0,0,0,0,1
\(A\subset \rbrack \a ,+\infty, \lbrack),0,0,0,1,0,0
\(A\subset \lbrack \a , +\infty\lbrack),0,0,0,1,0,0
\(\a\in A),0,0,0,0,0,1
}
%liste des réponses
\matrix{rep=\(\sup(A)\geq \a)
\(\sup(A)>\a)
\(\sup(A)= \a)
 \(\sup(A)\leq \a)
\(\sup(A)< \a)
\name_rep[1] \(\sup(A)) \name_rep[2]
\(\inf(A)\leq \a)
\(\inf(A)<\a)
\(\inf(A)= \a)
 \(\inf(A)\geq \a)
\(\inf(A)> \a)
\name_rep[1] \(\inf(A)) \name_rep[2]
}
#endif
#if defined TARGET_bornesup2
\matrix{mhyp=\(\sup(A)\geq \a),0,0,0,0,0,0,1
\(\sup(A)> \a),0,0,0,0,1,0,0
\(\sup(A)= \a),0,1,1,0,0,0,0
 \(\sup(A)\leq \a),0,1,1,0,0,0,0
\(\sup(A)< \a),0,1,1,1,0,0,0
\(\inf(A)\leq \a),0,0,0,0,0,0,1
\(\inf(A)< \a),0,0,0,0,1,0,0
\(\inf(A)= \a),0,1,1,0,0,0,0
 \(\inf(A)\geq \a),0,1,1,0,0,0,0
\(\inf(A)> \a),0,1,1,1,0,0,0
}

%liste des réponses
\matrix{rep=\(A\) \name_rep[1] \a
\(A) \name_rep[2] \a
\(\forall x\in A\quad x\leq \a\)
\(\forall x\in A\quad x< \a\)
\(\exists x\in A \quad x>\a\)
\(\a\in A)
\name_rep[3]
\(A) \name_rep[2] \a
\(A) \name_rep[1] \a
\(\forall x\in A\quad x\geq \a)
\(\forall x\in A\quad x> \a)
\(\exists x\in A \quad x<\a)
\(\a\in A)
\name_rep[3]
}
#endif
\integer{Nh=rows(\mhyp)/2} %nombre de lignes de la matrice pour le sup (cf même nombre pour sup et pour inf)
\integer{Nr=rows(\rep)/2}
\integer{nn=randint(1..\Nh)}
\integer{p=randint(0..1)} %0 on aura un sup, 1 on aura un inf

\integer{n=\nn+\p*\Nh} %ligne qui sera choisie
\integer{idebut=1+ \p*\Nr} %dédut des réponses
\integer{ifin=\Nr+ \p*\Nr} %fin des réponses

\text{ahyp=\mhyp[\n ;2..-1]} %garde que les 1 et 0 de la ligne n de la matrice des énoncés
\text{thyp=\mhyp[\n ;1]}

\text{ans=position(1,\ahyp)} %va permettre de controler les réponses
\text{list=item(1..\Nr,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)} % pour avoir les lettres A,B...
devant chaque case à cocher
text{list=\list,\list}

\statement{
  <div class="oef_explain">\name_enonce
  \name_know :
  <div class="wimscenter">
   \thyp .
  </div>
  \name_question
  </div>
  \for{i=1 to \Nr}
  {<div class="oefreply">\embed{reply 1,\i, \list[\i] : \rep[\i+\p*\Nr;]}</div>}} #commande pour afficher les choix de propositions à cocher list[\i] permet de mettre en début de ligne une lettre pour la repérer

\answer{\name_answer}{\ans;\list}{type=checkbox}{option=split} %%test pour reconnaître les bonnes réponses c'est là qu'arrive vraiment la contrainte de tout ou pas cliquer et de plus ici sera rappelé les lettres des lignes correspondant aux bonnes réponses
