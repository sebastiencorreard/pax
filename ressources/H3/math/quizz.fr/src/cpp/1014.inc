\title{Question 1014 Proportionnalité dans les formules}
\keywords{mental_calculation,proportionality}
%%%%%%%%%%%%% question 14 %%%%%%%%%%%%%

\matrix{data14=Le volume d'un cube est proportionnel à la longueur de son arête,2,V=a^3,2e
Le volume d'un prisme est proportionnel à sa hauteur,1,V=base \times hauteur,1er
La longueur d'un cercle est proportionnelle à son rayon,1,L=2\pi \times rayon ,1er
L'aire d'un cercle est proportionnelle à son rayon,2,A=\pi R^2,2e
L'aire d'un carré est proportionnelle à la longueur de son côté,2,A=c^2,2e
Le périmètre d'un carré est proportionnel à la longueur de son côté,1,P=4 \times c,1er}
\text{dat14= randomrow(\data14)}
\text{enonce=\dat14[1]}
\integer{rep=\dat14[2]}
\text{bad1=\dat14[2]=1?FAUX:VRAI}
\text{enonceb=}
\text{feedback="\( A \)" est proportionnel à "\(b \)" si on a une formule du type "\(A=k times b\)" où \(k \) ne dépend pas de \(b \).
<br>Si on a une formule du type "\(A=k \times b^2\)", \(A \) n'est pas proportionnel à \(b \).
<br>Ici, on a \(\dat14[3]\). On est donc dans le \dat14[4] cas...}
