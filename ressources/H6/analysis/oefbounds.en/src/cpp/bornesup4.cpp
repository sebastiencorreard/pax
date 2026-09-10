target=bornesup4
\title{Borne sup 4} %titre qui apparaît dans l'exo
\author{Chantal, Menini}
\email{chantal.menini@math.u-bordeaux.fr}
\credits{}

\integer{a=randint(-2..2)}

%énoncé une ligne sera prise, texte puis 1 pour réponse juste et 0 pour réponse fausse

\matrix{mhyp=\a is an upper bound of \(A) and we want to show that \(\sup(A)=\a),0,0,0,0,1,0,0
\(\a) is an upper bound of \(A) and we want to show that \(\sup(A)\leq\a),1,0,0,0,0,0,0
\(\a) is an upper bound of \(A) and we want to show that \(\sup(A)\geq\a),0,0,0,0,1,0,0
\(\a) is an upper bound of \(A) and we want to show that \(\sup(A)< \a),0,0,0,0,0,0,1
\(\a) is an upper bound of \(A) and we want to show that \(\sup(A)> \a),0,1,0,0,0,0,0
\(\a) is a lower bound of \(A) and we want to show that \(\inf(A)=\a),0,0,0,0,1,0,0
\(\a) is a lower bound of \(A) and we want to show that \(\inf(A)\geq\a),1,0,0,0,0,0,0
\(\a) is a lower bound of \(A) and we want to show that \(\inf(A)\leq\a),0,0,0,0,1,0,0
\(\a) is a lower bound of \(A) and we want to show that \(\inf(A)> \a),0,0,0,0,0,0,1
\(\a) is a lower bound of \(A) and we want to show that \(\inf(A)< \a),0,1,0,0,0,0,0
}

%liste des réponses
\matrix{rep=there is nothing more to do &#59; it is a consequence of the definition of the least upper bound
this case cannot occur
it remains to show that \(\a\in A)
it remains to show that \(\forall x\in A\quad x\leq \a)
it remains to show that \(\forall \varepsilon>0\ \exists x\in A ,\ \a-\varepsilon<x)
it remains to show that \(\exists \varepsilon>0\ \exists x\in A ,\ \a-\varepsilon<x)
it remains to show that \(\exists \varepsilon>0\ \forall x\in A ,\ \a-\varepsilon\geq x)
there is nothing more to do &#59; it is a consequence of the definition of the greatest lower bound
this case cannot occur
it remains to show that \(\a\in A)
it remains to show that \(\forall x\in A\quad x\geq \a)
it remains to show that \(\forall \varepsilon>0\ \exists x\in A ,\ \a+\varepsilon>x)
it remains to show that \(\exists \varepsilon>0\ \exists x\in A ,\ \a+\varepsilon>x)
it remains to show that \(\exists \varepsilon>0\ \forall x\in A ,\ \a+\varepsilon\leq x)
}

\integer{Nh=rows(\mhyp)/2} %nombre de lignes de la matrice pour le sup (cf même nombre pour sup et pour inf)
\integer{Nr=rows(\rep)/2}
\integer{nn=randint(1..\Nh)}
\integer{p=randint(0..1)} %0 on aura un sup, 1 on aura un inf

%pour adapter le texte de l'énoncé en fonction de sup-inf
\text{cond= \p==0 ?  above:below}
\text{condA= \p==0 ? \sup(A) : \inf(A)}
\text{supinf= \p==0 ? least upper:greatest lower}

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
  <div class="oef_explain">Let \(A) be a non-empty set that is bounded \cond.
We denote by \(\condA) its \supinf bound. We know that
<div class="wimscenter">
 \thyp .
</div>
Choose among the following proposals (only one correct answer)
</div>
  \for{i=1 to \Nr}
  {<div class="oefreply">\embed{reply 1,\i, \list[\i] : \rep[\i+\p*\Nr;]}</div>}} #commande pour afficher les choix de propositions à cocher list[\i] permet de mettre en début de ligne une lettre pour la repérer

\answer{The answer}{\ans;\list}{type=checkbox}{option=split} #test pour reconnaître les bonnes réponses c'est là qu'arrive vraiment la contrainte de tout ou pas cliquer et de plus ici sera rappelé les lettres des lignes correspondant aux bonnes réponses
