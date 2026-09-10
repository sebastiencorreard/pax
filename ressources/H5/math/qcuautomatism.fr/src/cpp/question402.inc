\title{Question 402 T Comparaison de proportions}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }
%%%%%% attention ne pas mélanger les réponses possibles pas de course1.inc dans le modèle
%%% trois proportions (la quatrième c'est le reste) puis le moins de vote, puis le plus de vote
\matrix{quest=quart,\(20\%\),tiers,D,C
tiers,\(20\%\),quart,B,C
cinquième,\(25\%\),tiers,A,C
tiers,\(25\%\),cinquième,C,A
dixième,\(30\%\),cinquième,A,D
dixième,\(8\%\),cinquième,B,D
}

\text{coeff=randomrow(\quest)}
\text{cas=randomitem(4,5)} %%% 4 le moins et 5 le plus
\text{mot1=\cas issametext 4?moins:plus}
\text{enonce=Lors d’une élection&#44; le \coeff[1] des électeurs a voté pour A&#44; \coeff[2] a voté pour B&#44; un \coeff[3] a voté pour C&#44; et le reste a voté pour D.<br>Le candidat ayant recueilli le <u>\mot1</u> de votes est le candidat&nbsp;&#58;}

\text{good=\coeff[\cas]}
\text{bads=} %%%%% inutile pour cet exercice
\text{endfeed=<br><u>Rappel&nbsp;&#58;</u> <ul><li>Un quart correspond à \(25\%\)</li><li>Un cinquième correspond à \(20\%\)</li><li>Un tiers correspond à environ \(33.33\%\)</li><li>Un dixième correspond à \(10\%\)</li></ul>}
\text{feedback=La bonne réponse est le candidat <b>\good </b>. <br>Pour comparer on peut comparer les pourcentages sachant que la somme de toutes les proportions doit faire <span class="nowrap">\(100\%\).</span> \endfeed}
