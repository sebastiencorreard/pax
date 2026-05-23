\title{Question 0608 Groupes }
\keywords{pbsolving,divisibility}
\matrix{data=15,1,3
16,2
18,1
20,2,3
21,1,4
24,1,2
25,3
27,1
28,2,4
30,1,3
}
\integer{choix08=randint(1..rows(\data))}
\text{rep=\data[\choix08;2..-1]}##type checkbox##
\text{prop=3 joueurs,4 joueurs,5 joueurs,7 joueurs}
\text{enonce=Un entraineur répartit \(\data[\choix08;1]\) joueurs dans des équipes ayant le même nombre de joueurs.<br>Il peut faire des équipes de &#58;}
\text{enonceb=<div class="wims_instruction">Cocher <u>toutes</u> les réponses justes.</div>}
\text{feedback=Il suffit de vérifier si les nombres proposés sont des diviseurs du nombre de joueurs.}
