target=bornesup4
#define NUM 4
#include "lang_titles.inc"
\author{Chantal, Menini}
\email{chantal.menini@math.u-bordeaux.fr}
\credits{}
#include "lang.inc"
\integer{a=randint(-2..2)}

%énoncé une ligne sera prise, texte puis 1 pour réponse juste et 0 pour réponse fausse
\matrix{mhyp=\a \name_mhyp[1] \(A) \name_mhyp[3] \(\sup(A)=\a\),0,0,0,0,1,0,0
\(\a) \name_mhyp[1] \(A\) \name_mhyp[3] \(\sup(A)\leq\a\),1,0,0,0,0,0,0
\(\a) \name_mhyp[1] \(A\) \name_mhyp[3] \(\sup(A)\geq\a\),0,0,0,0,1,0,0
\(\a) \name_mhyp[1] \(A\) \name_mhyp[3] \(\sup(A)< \a\),0,0,0,0,0,0,1
\(\a) \name_mhyp[1] \(A\) \name_mhyp[3] \(\sup(A)> \a\),0,1,0,0,0,0,0
\(\a) \name_mhyp[2] \(A\) \name_mhyp[3] \(\inf(A)=\a\),0,0,0,0,1,0,0
\(\a) \name_mhyp[2] \(A\) \name_mhyp[3] \(\inf(A)\geq\a\),1,0,0,0,0,0,0
\(\a) \name_mhyp[2] \(A\) \name_mhyp[3] \(\inf(A)\leq\a\),0,0,0,0,1,0,0
\(\a) \name_mhyp[2] \(A\) \name_mhyp[3] \(\inf(A)> \a\),0,0,0,0,0,0,1
\(\a) \name_mhyp[2] \(A\) \name_mhyp[3] \(\inf(A)< \a\),0,1,0,0,0,0,0
}

%liste des réponses
\matrix{rep=\name_rep[1]
\name_rep[3]
\name_rep[4] \(\a\in A)
\name_rep[4] \(\forall x\in A\quad x\leq \a)
\name_rep[4] \(\forall \varepsilon>0\ \exists x\in A ,\ \a-\varepsilon<x)
\name_rep[4] \(\exists \varepsilon>0\ \exists x\in A ,\ \a-\varepsilon<x)
\name_rep[4] \(\exists \varepsilon>0\ \forall x\in A ,\ \a-\varepsilon\geq x)
\name_rep[2]
\name_rep[3]
\name_rep[4] \(\a\in A)
\name_rep[4] \(\forall x\in A\quad x\geq \a)
\name_rep[4] \(\forall \varepsilon>0\ \exists x\in A ,\ \a+\varepsilon>x)
\name_rep[4] \(\exists \varepsilon>0\ \exists x\in A ,\ \a+\varepsilon>x)
\name_rep[4] \(\exists \varepsilon>0\ \forall x\in A ,\ \a+\varepsilon\leq x)
}

\integer{Nh=rows(\mhyp)/2} %nombre de lignes de la matrice pour le sup (cf même nombre pour sup et pour inf)
\integer{Nr=rows(\rep)/2}
\integer{nn=randint(1..\Nh)}
\integer{p=randint(0..1)} %0 on aura un sup, 1 on aura un inf

%pour adapter le texte de l'énoncé en fonction de sup-inf
\text{cond= \p==0 ? majoré : minoré}
\text{condA= \p==0 ? \sup(A) : \inf(A)}
\text{supinf= \p==0 ? supérieure : inférieure}

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
  <div class="oef_explain">\name_enonce[1] \cond,
\name_enonce[2] \(\condA) \name_enonce[3] \supinf. \name_enonce[4]
<div class="wimscenter">
 \thyp .
</div>
\name_question
</div>
  \for{i=1 to \Nr}
  {<div class="oefreply">\embed{reply 1,\i, \list[\i] : \rep[\i+\p*\Nr;]}</div>}} #commande pour afficher les choix de propositions à cocher list[\i] permet de mettre en début de ligne une lettre pour la repérer

\answer{\name_answer}{\ans;\list}{type=checkbox}{option=split} #test pour reconnaître les bonnes réponses c'est là qu'arrive vraiment la contrainte de tout ou pas cliquer et de plus ici sera rappelé les lettres des lignes correspondant aux bonnes réponses
