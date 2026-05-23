\title{Question 0626 Taille}
\keywords{pbsolving,masse,length,time}
%% type mark%%
\matrix{data=une fourmi mesure,1,3 mm,3 dm,3 m
une voiture pèse,2,1500 g,1500 kg,1500 tonnes
une voiture pèse,3,1.5 g,1.5 kg,1.5 tonnes
un éléphant pèse,3,5 g,5 kg,5 tonnes
un éléphant pèse,2,5000 g,5000 kg,5000 tonnes
une guitare a une longueur de,2,100 mm,100 cm,100 m
une guitare a une longueur de,2,1 cm,1 m,1 km
un car a une longueur de,2,11 cm, 11 m, 11 km
une baleine bleue mesure,2,1.25 m,25 hm, 25 km
une baleine bleue pèse,3,130 g,130 kg,130 tonnes
une raquette de tennis a une longueur de,2,6.85 cm,6.85 dm,6.85 m
une raquette de tennis a une longueur de,1,68.5 cm,68.5 dm,68.5 m
un pigeon pèse,2,300 mg,300 g,300 kg
un marathon dure,3,2 s,2 min,2 h
un film au cinéma dure,2,120 s,120 min,120 h
une brique pèse,2,3.5 g,3.5 kg,3.5 tonnes
un adulte mesure,1,175 cm,175 dm,175 m
un adulte mesure,2,1.8 dm,1.8 m,1.8 dam
}

\integer{choix26=randint(1..rows(\data))}
\real{rep=\data[\choix26;2]}
\text{prop=\data[\choix26;3..-1]}
\text{enonce=Clique sur la bonne réponse &#58;<br> \data[\choix26;1]}
\text{enonceb=}
\text{feedback=}
