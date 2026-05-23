\title{Question 1107 Calcul de fréquence}
\keywords{mental_calculation,descriptive_statistics}
\integer{n=7}
\integer{nb=randint(3..\n)-2}
\integer{nn=\n-\nb}
\text{couleurs=black}
\for{k=2 to \nn}{\text{couleurs=\couleurs,black}}
\for{k=1 to \nb}{\text{couleurs=\couleurs,white}}
\text{couleurs=shuffle(\couleurs)}
%%%%
\integer{taille=20} %%% des cercles et disques
\integer{l=\n*20+10} %%% longueur de l'image
\text{cercle=\couleurs[1] issametext black ? fcircle 5,0,\taille,black:circle 5,0,\taille,black}
\for{k=1 to \n-1}{
\integer{temp=5+10*\k}
\text{cerclen=fcircle \temp,0,\taille,black}
\text{cercleb=circle \temp,0,\taille,black}
\text{cercletemp=\couleurs[\k+1] issametext black ?\cerclen:\cercleb}
\text{cercle=\cercle
\cercletemp}}
\text{barre=draw(300,\taille
xrange 0,\l
yrange -15,15
\cercle
)}
\text{couleur=random(noires,blanches)}

\rational{rep=\couleur issametext noires ?\nn/\n:\nb/\n}
\text{enonce=Calculer la fréquence de boules \couleur parmi ces boules &#58; <br> <img src="\barre" alt=""><br>Réponse : }
\text{enonceb=}
\text{feedback=Attention, on vous demande la fréquence des boules <STRONG> \couleur</STRONG>.}
