\title{Question 600 T Reconnaître graphiquement une fct affine}
\observation{Question du sujet zéro sujet-techno-2_0.pdf publié sur EDUSCOL en juin 2025 }
\keywords{quizz,affine_function}
%%% MB %%%%
\integer{coeffdir=randomitem(1,2,3)*randomitem(-1,1)}
\integer{ordorig=item(1,shuffle(2,3,4))*randomitem(-1,1)}
\function{f=\coeffdir*x+\ordorig}
\function{f1=-\coeffdir*x+\ordorig}
\function{f2=-\coeffdir*x-\ordorig}
\function{f3=\coeffdir*x-\ordorig}
%%%%% image
\text{img=
range -5,5,-5,5
linewidth 1
arrow -5,0,5,0,10,black
arrow 0,-5,0,5,10,black
linewidth 2
  trange -5,5
}
\text{imagef=\img
  plot red,\f}
\text{imagef1=\img
  plot red,\f1}
\text{imagef2=\img
  plot red,\f2}
\text{imagef3=\img
  plot red,\f3}

%% image statement %%%%
\text{imgstatf=draw(80,80
\imagef
)}
\text{imgf=<img src="\imgstatf" alt="représentation graphique">}
\text{imgstatf1=draw(80,80
\imagef1
)}
\text{imgf1=<img src="\imgstatf1" alt="représentation graphique">}
\text{imgstatf2=draw(80,80
\imagef2
)}
\text{imgf2=<img src="\imgstatf2" alt="représentation graphique">}
\text{imgstatf3=draw(80,80
\imagef3
)}
\text{imgf3=<img src="\imgstatf3" alt="représentation graphique">}

\text{enonce=La seule droite pouvant correspondre à l’équation \(y=\f\) est&nbsp;&#58;}

\text{good=\imgf}
\text{bads=\imgf1,\imgf2 ,\imgf3}
\text{mot1=\coeffdir<0?négatif:positif}
\text{mot2=\coeffdir<0?décroissante:croissante}
\text{mot4=\ordorig<0?négative:positive}
\text{feedback=La bonne réponse était \good.<br> Puisque le coefficient directeur \(\coeffdir\) est \mot1 la fonction est donc \mot2 et que \(\ordorig\) est \mot4.<br><u>Rappel&nbsp;&#58;</u> l'ordonnée à l'origine est l'ordonnée du point d'intersection de la droite et de l'axe des ordonnées.}
