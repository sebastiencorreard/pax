\title{Question 304 S Reconnaitre l'équation d'une parabole}
\keywords{quizz,equations,graphing}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }

\integer{n=randomitem(10,20,30)}
%%%% fonction
\text{fcts=x^2-\n,-x^2-\n,-x^2+\n,-x^2+\n x}


\text{nf=shuffle(4)}


%%%%% fonction du graphique
\text{fctsg=x^2-4,-x^2-4,-x^2+4,-x^2+4*x}
\function{f=\fctsg[\nf[1]]}

\text{xmin=-5}
\text{xmax=5}
\text{ymin=-10}
\text{ymax=10}

%%%% Etiquette de (P)

\real{xp=\nf[1]=2?2:3}
\real{yp=evalue(\f,x=\xp)}
\real{yp=\yp+0.5}
\real{xp=\xp+0.5}
%%%%%% graduations

\text{grad=
  text black,3.5,-0.5,big,x
  segment -0.1,10,0.1,10,black
  text black,0.4,-0.4,big,0
  text black,-0.5,9,big,y  
  }
\text{plotf=linewidth 2
  trange \xmin,\xmax
  plot red,\f
  text black,\xp,\yp,big,(P)} 
\text{img=
range \xmin,\xmax,\ymin,\ymax
linewidth 1
arrow \xmin,0,\xmax,0,10,black
arrow 0,\ymin,0,\ymax,10,black
\grad
}
%% image statement %%%%
\text{imgstat0=draw(200,200
\img
\plotf
)}
\text{imgstat=<img src="\imgstat0" alt="représentation graphique">}

\text{enonce= On a représenté ci-dessous une parabole <b>(P)</b>.<div class="wimscenter">\imgstat</div> Une seule des quatre fonctions ci-dessous est susceptible d’être représentée par la parabole (P).<br>Laquelle&nbsp;&#63; }

\text{good= \(x \mapsto \fcts[\nf[1]]\)}
%%%%%
\text{bad1=\(x \mapsto \fcts[\nf[2]]\)}
\text{bad2=\(x \mapsto \fcts[\nf[3]]\)}
\text{bad3=\(x \mapsto \fcts[\nf[4]]\)}
\text{bads=\bad1,\bad2,\bad3}
%%%% feedback %%%%%%%
\text{var=\nf[1]>1?croissante puis décroissante:décroissante puis croissante}
\text{sgnx2=\nf[1]>1?négatif:positif}
\text{img_zero=négative,négative,positive,nulle}
\text{img_zero=\img_zero[\nf[1]]}
\text{feedback=La bonne réponse est \good.<br> En observant la courbe on sait que <ul><li>La fonction est \var</li><li>L'image de zéro est \img_zero </li></ul><u>Rappel&nbsp;&#58;</u> pour les polynômes du second degré&#44; lorsque le coefficient de \(x^2\) est \sgnx2&#44; la fonction est \var.}
