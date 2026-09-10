target=bornesup3

\title{Upper bound 3} %titre qui apparaît dans l'exo
\author{Chantal, Menini}
\email{chantal.menini@math.u-bordeaux.fr}
\credits{}

%énoncé une ligne sera prise, texte puis 1 pour réponse juste et 0 pour réponse fausse

\matrix{mhyp=\(\sup(A)\leq \sup(B)),1,1,0,0,0,0
\(\sup(A)< \sup(B)),1,1,1,0,0,1
\(\sup(A)=\sup(B)),1,1,0,0,0,0
\(\inf(A)\geq \inf(B)),1,1,0,0,0,0
\(\inf(A)> \inf(B)),1,1,1,0,0,1
\(\inf(A)=\inf(B)),1,1,0,0,0,0
}

%liste des réponses
\matrix{rep=\(\sup(B)) is an upper bound of \(A)
\(\forall x\in A\quad x\leq \sup(B))
\(\forall x\in A\quad x< \sup(B))
\(\sup(A)) is a lower bound of \(B)
\(\forall x\in B\quad x\geq \sup(A))
\(\exists x\in B\quad x> \sup(A))
\(\inf(B)) is a lower bound of \(A)
\(\forall x\in A\quad x\geq \inf(B))
\(\forall x\in A\quad x> \inf(B))
\(\inf(A)) is an upper bound of \(B)
\(\forall x\in B\quad x\leq \inf(A))
\(\exists x\in B\quad x< \inf(A))
}

\integer{Nh=rows(\mhyp)/2} %nombre de lignes de la matrice pour le sup (cf même nombre pour sup et pour inf)
\integer{Nr=rows(\rep)/2}
\integer{nn=randint(1..\Nh)}

\integer{p=randint(0..1)} %0 on aura un sup, 1 on aura un inf

%pour adapter le texte de l'énoncé en fonction de sup-inf
\text{cond= \p==0 ? above:below}
\text{condA= \p==0 ? \sup(A) : \inf(A)}
\text{condB= \p==0 ? \sup(B) : \inf(B)}
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
  <div class="oef_explain">Let \(A) and \(B) be two non-empty sets that are bounded \cond.
  We denote respectively by \(\condA) and \(\condB) their \supinf bounds. We know that :
<div class="wimscenter">
 \thyp .
</div>
We can deduce (there can be one or several good answers) :
</div>
  \for{i=1 to \Nr}
  {<div class="oefreply">\embed{reply 1,\i, \list[\i] : \rep[\i+\p*\Nr;]}</div>}} #commande pour afficher les choix de propositions à cocher list[\i] permet de mettre en début de ligne une lettre pour la repérer

\answer{The answer}{\ans;\list}{type=checkbox}{option=split} #test pour reconnaître les bonnes réponses c'est là qu'arrive vraiment la contrainte de tout ou pas cliquer et de plus ici sera rappelé les lettres des lignes correspondant aux bonnes réponses
