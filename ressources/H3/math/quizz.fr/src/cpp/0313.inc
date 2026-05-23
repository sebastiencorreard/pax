\title{Question 0313 Estimer la longueur d'un objet}
\keywords{mental_calculation,length}
\text{repposs=130 cm,13 m,130 m}
\matrix{quest0313=d'un rateau,1;d'un autocar,2}%%% trouver un objet de longueur 130m
\integer{cas=random(1,2)} %%% question
\text{quest0313=row(\cas,\quest0313)}
\text{rep=\repposs[\quest0313[2]]}
\integer{temp=\quest0313[2]}
\integer{bad1=\temp==1?2:1}
\text{bad1=\repposs[\bad1]}
\text{bad2=\repposs[3]}
\text{bads=\bad1,\bad2}
\text{enonce=Choisis la longueur possible \quest0313[1] &#63; }
\text{enonceb=}
\text{feedback=Il faut faire attention aussi aux unités de mesure. Ne pas confondre les mètres et les centimètres.}
