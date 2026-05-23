target=sommesimple1 sommesimple2 sommesimple3 sommedouble1 sommedouble2 sommedouble3 sommepriorite1 sommepriorite2  sommepriorite3 sommeproduit1 sommeproduit2 sommeproduit3 produit1 produit2 produit3 quotient1 quotient2 quotient3 quotientfrac1 quotientfrac2 quotientfrac3
\language{fr}
\author{Jean-Baptiste Frondas}
\email{jbfrondas@gmail.com}
\format{html}
\precision{10000}
\computeanswer{no}
#if defined TARGET_sommesimple1 || defined TARGET_sommedouble1 || defined TARGET_sommepriorite1 || defined TARGET_sommeproduit1 || defined TARGET_produit1 || defined TARGET_quotient1 || defined TARGET_quotientfrac1
\integer{n=12}
\integer{m=8}
#endif
#if defined TARGET_sommesimple2 || defined TARGET_sommedouble2 || defined TARGET_sommepriorite2 || defined TARGET_sommeproduit2 || defined TARGET_produit2 || defined TARGET_quotient2 || defined TARGET_quotientfrac2
\integer{n=24}
\integer{m=12}
#endif
#if defined TARGET_sommesimple3 || defined TARGET_sommedouble3 || defined TARGET_sommepriorite3 || defined TARGET_sommeproduit3 || defined TARGET_produit3 || defined TARGET_quotient3 || defined TARGET_quotientfrac3
\integer{n=48}
\integer{m=16}
#endif
\text{a=}
\for{u=1 to 25}{
  \integer{s=randint(1..\n)*random(-1,1)}
  \text{a=wims(append item \s to \a)}
}
\text{b=}
\for{u=1 to 25}{
  \integer{s=randint(1..\m)}
  \text{b=wims(append item \s to \b)}
}
#if defined TARGET_sommesimple1 || defined TARGET_sommesimple2 || defined TARGET_sommesimple3
% Matrice des expressions. En première colonne l'expression pour les logiciels de calculs, en deuxième colonne en LaTeX pour l'affichage sur wims ou pour sujet papier.
\matrix{expression=(\a[1])/(\b[1])+(\a[2])/(\b[1]), \dfrac{\a[1]}{\b[1]}+\dfrac{\a[2]}{\b[1]}
(\a[3])/(\b[5])-(\a[4])/(\b[5]),\dfrac{\a[3]}{\b[5]}-\dfrac{\a[4]}{\b[5]}
((\a[5]))/(\b[8])+(\a[6])/(\b[10]),\dfrac{\a[5]}{\b[8]}+\dfrac{\a[6]}{\b[10]}
(\a[7])/(\b[12])-(\a[8])/(\b[14]),\dfrac{\a[7]}{\b[12]}-\dfrac{\a[8]}{\b[14]}}
#endif
#if defined TARGET_sommedouble1 || defined TARGET_sommedouble2 || defined TARGET_sommedouble3
% Matrice des expressions. En première colonne l'expression pour les logiciels de calculs, en deuxième colonne en LaTeX pour l'affichage sur wims ou pour sujet papier.
\matrix{expression=(\a[1])/(\b[1])+(\a[2])/(\b[2])+(\a[3])/(\b[3]),\dfrac{\a[1]}{\b[1]}+\dfrac{\a[2]}{\b[2]}+\dfrac{\a[3]}{\b[3]}
(\a[4])/(\b[4])-((\a[5]))/(\b[5])+(\a[6])/(\b[6]),\dfrac{\a[4]}{\b[4]}-\dfrac{\a[5]}{\b[5]}+\dfrac{\a[6]}{\b[6]}
(\a[7])/(\b[7])+(\a[8])/(\b[8])-(\a[9])/(\b[9]),\dfrac{\a[7]}{\b[7]}+\dfrac{\a[8]}{\b[8]}-\dfrac{\a[9]}{\b[9]}
(\a[10])/(\b[10])-(\a[11])/(\b[11])-(\a[12])/(\b[12]),\dfrac{\a[10]}{\b[10]}-\dfrac{\a[11]}{\b[11]}-\dfrac{\a[12]}{\b[12]}}
#endif
#if defined TARGET_sommepriorite1 || defined TARGET_sommepriorite2 || defined TARGET_sommepriorite3
% Matrice des expressions. En première colonne l'expression pour les logiciels de calculs, en deuxième colonne en LaTeX pour l'affichage sur wims ou pour sujet papier.
\matrix{expression=(\a[1])/(\b[1])+((\a[2])/(\b[2])+(\a[3])/(\b[3])),\dfrac{\a[1]}{\b[1]}+\left( \dfrac{\a[2]}{\b[2]}+\dfrac{\a[3]}{\b[3]}\right)
(\a[4])/(\b[4])-((\a[5])/(\b[5])+(\a[6])/(\b[6])),\dfrac{\a[4]}{\b[4]}-\left( \dfrac{\a[5]}{\b[5]}+\dfrac{\a[6]}{\b[6]} \right)
(\a[7])/(\b[7])+((\a[8])/(\b[8])-(\a[9])/(\b[9])),\dfrac{\a[7]}{\b[7]}+\left( \dfrac{\a[8]}{\b[8]}-\dfrac{\a[9]}{\b[9]} \right)
(\a[10])/(\b[10])-((\a[11])/(\b[11])-(\a[12])/(\b[12])),\dfrac{\a[10]}{\b[10]}-\left( \dfrac{\a[11]}{\b[11]}-\dfrac{\a[12]}{\b[12]} \right)
((\a[1])/(\b[1])+(\a[2])/(\b[2]))+(\a[3])/(\b[3]),\left( \dfrac{\a[1]}{\b[1]}+\dfrac{\a[2]}{\b[2]}\right)+\dfrac{\a[3]}{\b[3]}
((\a[4])/(\b[4])-(\a[5])/(\b[5]))+(\a[6])/(\b[6]),\left( \dfrac{\a[4]}{\b[4]}-\dfrac{\a[5]}{\b[5]}\right)+\dfrac{\a[6]}{\b[6]}
((\a[7])/(\b[7])+(\a[8])/(\b[8]))-(\a[9])/(\b[9]),\left( \dfrac{\a[7]}{\b[7]}+\dfrac{\a[8]}{\b[8]}\right)-\dfrac{\a[9]}{\b[9]}
((\a[10])/(\b[10])-(\a[11])/(\b[11]))-(\a[12])/(\b[12]),\left( \dfrac{\a[10]}{\b[10]}-\dfrac{\a[11]}{\b[11]}\right)-\dfrac{\a[12]}{\b[12]}}
#endif
#if defined TARGET_sommeproduit1 || defined TARGET_sommeproduit2 || defined TARGET_sommeproduit3
% Matrice des expressions. En première colonne l'expression pour les logiciels de calculs, en deuxième colonne en LaTeX pour l'affichage sur wims ou pour sujet papier.
\matrix{expression=(\a[1])/(\b[1])+((\a[2])/(\b[2])) * ((\a[3])/(\b[3])), \dfrac{\a[1]}{\b[1]}+\dfrac{\a[2]}{\b[2]} \times \dfrac{\a[3]}{\b[3]}
(\a[4])/(\b[4])+((\a[5])/(\b[5])) / ((\a[6])/(\b[6])),\dfrac{\a[4]}{\b[4]}+\dfrac{\a[5]}{\b[5]} \div \dfrac{\a[6]}{\b[6]}
(\a[7])/(\b[7])-((\a[8])/(\b[8])) * ((\a[9])/(\b[9])), \dfrac{\a[7]}{\b[7]}-\dfrac{\a[8]}{\b[8]} \times \dfrac{\a[9]}{\b[9]}
(\a[10])/(\b[10]) - ((\a[11])/(\b[11])) / ((\a[12])/(\b[12])),\dfrac{\a[10]}{\b[10]} - \dfrac{\a[11]}{\b[11]} \div \dfrac{\a[12]}{\b[12]}
((\a[13])/(\b[13]))*((\a[14])/(\b[14]))+(\a[15])/((\b[15])), \dfrac{\a[13]}{\b[13]} \times \dfrac{\a[14]}{\b[14]}+\dfrac{\a[15]}{\b[15]}
((\a[16])/(\b[16]))*((\a[17])/(\b[17]))-(\a[18])/(\b[18]), \dfrac{\a[16]}{\b[16]} \times \dfrac{\a[17]}{\b[17]}-\dfrac{\a[18]}{\b[18]}
((\a[19])/(\b[19]))/((\a[20])/(\b[20]))+(\a[21])/(\b[21]), \dfrac{\a[19]}{\b[19]} \div \dfrac{\a[20]}{\b[20]}+\dfrac{\a[21]}{\b[21]}
((\a[22])/(\b[22]))/((\a[23])/(\b[23]))-(\a[24])/(\b[24]), \dfrac{\a[22]}{\b[22]} \div \dfrac{\a[23]}{\b[23]}-\dfrac{\a[24]}{\b[24]}}
#endif
#if defined TARGET_produit1 || defined TARGET_produit2 || defined TARGET_produit3
% Matrice des expressions. En première colonne l'expression pour les logiciels de calculs, en deuxième colonne en LaTeX pour l'affichage sur wims ou pour sujet papier.
\matrix{expression=(\a[1])/(\b[1]) * (\a[2])/(\b[2]), \dfrac{\a[1]}{\b[1]} \times \dfrac{\a[2]}{\b[2]}
(\a[3])/(\b[3]) * (\a[4])/(\b[4]),\dfrac{\a[3]}{\b[3]} \times \dfrac{\a[4]}{\b[4]}
(\a[5])/(\b[5]) *(\a[6])/(\b[6]),\dfrac{\a[5]}{\b[5]} \times \dfrac{\a[6]}{\b[6]}
(\a[7])/(\b[7]) * (\a[8])/(\b[8]),\dfrac{\a[7]}{\b[7]} \times \dfrac{\a[8]}{\b[8]}}
#endif
#if defined TARGET_quotient1 || defined TARGET_quotient2 || defined TARGET_quotient3
% Matrice des expressions. En première colonne l'expression pour les logiciels de calculs, en deuxième colonne en LaTeX pour l'affichage sur wims ou pour sujet papier.
\matrix{expression=((\a[1])/(\b[1])) / ((\a[2])/(\b[2])), \dfrac{\a[1]}{\b[1]} \div \dfrac{\a[2]}{\b[2]}
((\a[3])/(\b[3])) / ((\a[4])/(\b[4])),\dfrac{\a[3]}{\b[3]} \div \dfrac{\a[4]}{\b[4]}
((\a[5])/(\b[5])) / ((\a[6])/(\b[6])),\dfrac{\dfrac{\a[5]}{\b[5]}}{\dfrac{\a[6]}{\b[6]}}
((\a[7])/(\b[7])) / ((\a[8])/(\b[8])),\dfrac{\dfrac{\a[7]}{\b[7]}}{\dfrac{\a[8]}{\b[8]}}
((\a[9]) / (\a[10])) / (\a[11]),\dfrac{\dfrac{\a[9]}{\a[10]}}{\a[11]}
((\b[9]) / (\b[10])) / (\b[11]),\dfrac{\b[9]}{\b[10]} \div \b[11]
(\a[12]) / ((\a[13]) / (\a[14])),\a[12] \div \dfrac{\a[13]}{\a[14]}
(\b[12]) / ((\b[13]) / (\b[14])),\dfrac{\b[12]}{\dfrac{\b[13]}{\b[14]}}}
#endif
#if defined TARGET_quotientfrac1 || defined TARGET_quotientfrac2 || defined TARGET_quotientfrac3
% Matrice des expressions. En première colonne l'expression pour les logiciels de calculs, en deuxième colonne en LaTeX pour l'affichage sur wims ou pour sujet papier.
\if{(\a[3])+(\a[4])/(\b[4])=0}{wims(replace item number 3 by \a[3]+1 in \a)}
\if{(\a[11])-(\a[12])/(\b[12])=0}{wims(replace item number 11 by \a[11]+1 in \a)}
\if{((\a[14])/(\b[14]))-((\a[15])/(\b[15]))=0}{wims(replace item number 14 by \a[14]+1 in \a)}
\if{((\a[17])/(\b[17]))+((\a[18])/(\b[18]))=0}{wims(replace item number 17 by \a[17]+1 in \a)}
\if{(\a[21])/(\b[21])+(\a[22])/(\b[22])=0}{wims(replace item number 21 by \a[21]+1 in \a)}
\if{(\a[1])/(\b[1])-(\a[2])/(\b[2])=0}{wims(replace item number 1 by \a[1]+1 in \a)}
\if{(\a[5])/(\b[5])+(\a[6])/(\b[6])=0}{wims(replace item number 5 by \a[5]+1 in \a)}
\if{(\a[9])/(\b[9])-(\a[10])/(\b[10])=0}{wims(replace item number 9 by \a[9]+1 in \a)}
\matrix{expression=((\a[1])-(\a[2])/(\b[2]))/(\a[3])+(\a[4])/(\b[4]),\dfrac{\a[1]-\dfrac{\a[2]}{\b[2]}}{\a[3]+\dfrac{\a[4]}{\b[4]}}
((\a[5])+(\a[6])/(\b[6]))/(\a[7])*(\a[8])/(\b[8]),\dfrac{\a[5]+\dfrac{\a[6]}{\b[6]}}{\a[7] \times \dfrac{\a[8]}{\b[8]}}
((\a[9]) * (\a[10])/(\b[10]))/((\a[11])-(\a[12])/(\b[12])),\dfrac{\a[9]\times \dfrac{\a[10]}{\b[10]}}{\a[11]-\dfrac{\a[12]}{\b[12]}}
((\a[13])/(\b[13]))/((\a[14])/(\b[14]))-((\a[15])/(\b[15])),\dfrac{\dfrac{\a[13]}{\b[13]}}{\dfrac{\a[14]}{\b[14]}}-\dfrac{\a[15]}{\b[15]}
((\a[16])/(\b[16]))/((\a[17])/(\b[17]))+((\a[18])/(\b[18])),\dfrac{\dfrac{\a[16]}{\b[16]}}{\dfrac{\a[17]}{\b[17]}}+\dfrac{\a[18]}{\b[18]}
((\a[19])/(\b[19])+(\a[20])/(\b[20]))/((\a[21])/(\b[21])+(\a[22])/(\b[22])),\dfrac{\dfrac{\a[19]}{\b[19]}+\dfrac{\a[20]}{\b[20]}}{\dfrac{\a[21]}{\b[21]}+\dfrac{\a[22]}{\b[22]}}
((\a[23])/(\b[23])+(\a[24])/(\b[24]))/((\a[1])/(\b[1])-(\a[2])/(\b[2])),\dfrac{\dfrac{\a[23]}{\b[23]}+\dfrac{\a[24]}{\b[24]}}{\dfrac{\a[1]}{\b[1]}-\dfrac{\a[2]}{\b[2]}}
((\a[3])/(\b[3])-(\a[4])/(\b[4]))/((\a[5])/(\b[5])+(\a[6])/(\b[6])),\dfrac{\dfrac{\a[3]}{\b[3]}-\dfrac{\a[4]}{\b[4]}}{\dfrac{\a[5]}{\b[5]}+\dfrac{\a[6]}{\b[6]}}
((\a[7])/(\b[7])-(\a[8])/(\b[8]))/((\a[9])/(\b[9])-(\a[10])/(\b[10])),\dfrac{\dfrac{\a[7]}{\b[7]}-\dfrac{\a[8]}{\b[8]}}{\dfrac{\a[9]}{\b[9]}-\dfrac{\a[10]}{\b[10]}}
}
#endif
% Mélange des expressions
\text{mix=shuffle(rows(\expression))}
\text{expressionmix=\expression[\mix;]}
% les expresisons en latex pour affichage et sujet papier
\text{A=\expressionmix[1;2]}
\text{B=\expressionmix[2;2]}
\text{C=\expressionmix[3;2]}
\text{D=\expressionmix[4;2]}
% Le calcul des expressions
\rational{repA=\expressionmix[1;1]}
\rational{repB=\expressionmix[2;1]}
\rational{repC=\expressionmix[3;1]}
\rational{repD=\expressionmix[4;1]}
% Mise au format LaTeX pour sujet papier
\text{repAA=texmath(\repA)}
\text{repBB=texmath(\repB)}
\text{repCC=texmath(\repC)}
\text{repDD=texmath(\repD)}
#include "lang_title.inc"
#include "lang.inc"
\title{TITRE}
\statement{
\enonce
<ul>
<li>\( A=\A \) ; <label for="reply1">\(A=\)</label> \embed{reply1,5} </li>
<li>\( B=\B \) ; <label for="reply2">\(B=\)</label> \embed{reply2,5} </li>
<li>\( C=\C \) ; <label for="reply3">\(C=\)</label>\embed{reply3,5} </li>
<li>\( D=\D \) ; <label for="reply4">\(D=\)</label>\embed{reply4,5} </li>
</ul>}
\answer{ A }{ \repA }
\answer{ B }{ \repB }
\answer{ C }{ \repC }
\answer{ D }{ \repD }
\latex{
\begin{statement}
\titretex \par
\enonce
\begin{align*}
	A &=\A\\\\
	B &=\B\\\\
	C &=\C\\\\
	D &=\D
\end{align*}
\end{statement}
\begin{solution}
	\[ A=\repAA \qquad B=\repBB \qquad C=\repCC \qquad D=\repDD \]
\end{solution}
}
