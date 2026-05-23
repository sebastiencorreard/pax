\title{Question 1128 Probabilité et arbre}
\keywords{mental_calculation,probability,events}

\text{temp=shuffle(9)} %%% avoir des proba distinctes
\real{pAB=\temp[1]/10}
\real{pnAB=\temp[2]/10}
\real{pnA=\temp[3]/10}
\real{pA=1-\pnA}
\real{pAnB=1-\pAB}
\real{pnAnB=1-\pnAB}
\real{pAinterB=\pA*\pAB}
\real{pnAinternB=\pnA*\pnAnB}
\text{quest=\(P(\bar{A} \cap \bar{B})={}\),\pnAinternB,\(P_\bar{A} (\bar{B})=1-\pnAB\),\(P(\bar{A} \cap \bar{B})=\pnA\times\pnAnB\);
\(P(A \cap B)={}\),\pAinterB,\(P_{A} =1-\pnA\),\(P({A} \cap {B})=\pA \times \pAB\)}
\text{quest=randomrow(\quest)}

\text{dessinprelim=
xrange 0,256
yrange 0,160
copy 0,160,-1,-1,-1,-1,1128.png
text black,150,150,giant,\pAB
text black,150,70,giant,\pnAB
text black,40,58,giant,\pnA}
\text{img=draw(256,160
\dessinprelim)}
\real{rep=\quest[2]}
\text{enonce=<img src="\img" alt="arbre"> <br>\quest[1]}
\text{enonceb=}
\text{feedback=On a \quest[3], donc \quest[4]}
