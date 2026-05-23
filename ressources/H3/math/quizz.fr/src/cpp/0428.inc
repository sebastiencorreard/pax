\title{Question 0428 Produit par regroupement}
\keywords{mental_calculation,methodical_calculation}
%%%% inspiré de 0904  %%%%%%%%
\matrix{quest0904=4,25;
2,50;
2,5;
5,20}
\text{temp0904=randomrow(\quest0904)}
\integer{type0904=1}
%%%%%% 1 : regrouper a et c 2: regrouper c et d
\integer{a0904=\type0904=1?\temp0904[1]:randint(3,6,7,8,9)}
\integer{b0904=\type0904=1?randint(3,6,7,8,9):\temp0904[1]}
\integer{c0904=\type0904=1?\temp0904[2]:randint(3,6,7,8,9)}

\integer{rep=\a0904*\b0904*\c0904}
\text{enonce= \(\a0904 \times \b0904 \times \c0904 =\)}
\text{enonceb=}
%%%% feedback %%%%
\integer{k0904=\temp0904[1]*\temp0904[2]}
\text{feedback=Il faut regrouper les termes pour faciliter l'opération. Ici : \(\temp0904[1] \times \temp0904[2]=\k0904\).}