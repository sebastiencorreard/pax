\title{Question 1022 Probabilité deux tirages}
\keywords{mental_calculation,probability}
%%%%%%%%%%% question 7 %%%%%%%%%%%

\matrix{data7=On obtient au moins une fois PILE,3/4,3 ont au moins un PILE
On obtient au moins une fois FACE,3/4,3 ont au moins un FACE
On obtient deux fois PILE,1/4,1 a deux PILE
On obtient deux fois FACE,1/4,1 a deux FACE
On obtient exactement une fois PILE,2/4,2 ont exactement un PILE
On obtient exactement une fois PILE,2/4,2 ont exactement un PILE}

\text{data7=randomrow(\data7)}
\real{rep=\data7[2]}
\text{enonce=On lance deux fois de suite une pièce de monnaie parfaitement équilibrée. Quelle est la probabilité de l'évènement : «\data7[1]» &#63; <br> Réponse : }
\text{enonceb=}
\text{feedback=On imagine un arbre, sur lequel figurent les 4 évènements équiprobables "PILE1-PILE2", "PILE1-FACE2", "FACE1-PILE2", "FACE1-FACE2". Sur ces 4 issues possibles, \data7[3]. Donc la réponse est \(\data7[2]\)}
