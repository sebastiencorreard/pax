\title{Question 1025 Ecrire un calcul}
\keywords{mental_calculation,literal_calculation}
%%%%%%%%%%% question 10 %%%%%%%%%%%

\text{t110=randitem(2,3,4,5)x}
\text{t210=randitem(6,7,8,9)}
\integer{choix110=randitem(1,2)} #choix110=1 -> "carré", sinon "cube"
\integer{choix210=randitem(1,2)} #choix210=1 -> "somme", sinon "différence"
\text{mot110=\choix110==1 ? carré : cube}
\text{mot210=\choix210==1 ? somme : différence}
\text{rep=\choix110==1 and \choix210==1 ?(\t110)^2+\t210}
\text{rep=\choix110==1 and \choix210==2 ?(\t110)^2-\t210}
\text{rep=\choix110==2 and \choix210==1 ?(\t110)^3+\t210}
\text{rep=\choix110==2 and \choix210==2 ?(\t110)^3-\t210}
\text{enonce=Écrire sous la forme d'une expression littérale la \mot210 du \mot110 de \(\t110 \) et de \(\t210 \). <br> Réponse : }
\text{enonceb=<div class="wims_instruction">Ne pas développer ni réduire.</div>}
\text{feedback=Ne pas oublier les parenthèses pour les priorités...}
