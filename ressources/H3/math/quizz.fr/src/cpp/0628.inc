\title{Question 0628 Multiplication}
\keywords{multiplication,methodical_calculation}
\integer{a=randint(3..9)}
\matrix{data=50,\a,2
2,\a,50
25,\a,4
4,\a,25
2,\a,5
5,\a,2
20,\a,5
5,\a,20}
\integer{choix28=randint(1..rows(\data))}
\integer{rep=\data[\choix28;1]*\data[\choix28;2]*\data[\choix28;3]}
\text{enonce=\(\data[\choix28;1] \times \data[\choix28;2] \times \data[\choix28;3]\)=}
\text{enonceb=}
\text{feedback=Regrouper astucieusement les facteurs pour faciliter le calcul.}
