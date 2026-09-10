\title{Question 651 S Solutions d'inéquation (graphique)}
\keywords{quizz,inequations,graphing}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }

\real{k=randomitem(0.1,-0.1)}

\function{f=\k*(x+3)*(x-3)*(x-5)}
%%%%%%
\real{xA=-0.1*randint(35..40)}
\real{yA=evalue(\f,x=\xA)}
\real{xB=-0.1*randint(15..20)}
\real{yB=evalue(\f,x=\xB)}
\real{xR=0.1*randint(5..20)}
\real{yR=evalue(\f,x=\xR)}
\real{xS=0.1*randint(35..45)}
\real{yS=evalue(\f,x=\xS)}
%%%%%%%
\text{xmin=-6}
\text{xmax=6}
\text{ymin=-10}
\text{ymax=10}
\real{hx=0.7}
\real{hy=1}

\real{xAtxt=\xA-\hx}
\real{yAtxt=\yA+\hy}
\real{xBtxt=\xB-\hx}
\real{yBtxt=\yB+\hy}
\real{xRtxt=\xR+\hx}
\real{yRtxt=\yR+\hy}
\real{xStxt=\xS+\hx}
\real{yStxt=\k<0?\yS+1.4*\hy:\yS-0.2*\hy}
\integer{diam=8}
\text{points=
 fcircle \xA,\yA,\diam,black
 text black,\xAtxt,\yAtxt,big,A
 fcircle \xB,\yB,\diam,black
 text black,\xBtxt,\yBtxt,big,B
 fcircle \xR,\yR,\diam,black
 text black,\xRtxt,\yRtxt,big,R
  fcircle \xS,\yS,\diam,black
 text black,\xStxt,\yStxt,big,S }
 %%%%%% graduations
\text{grad=
  text black,-0.4,-0.2,big,O
  }
\text{plotf=linewidth 2
  trange \xmin,\xmax
  plot red,\f
  }
\text{img=
range \xmin,\xmax,\ymin,\ymax
linewidth 1
segment \xmin,0,\xmax,0,10,black
segment 0,\ymin,0,\ymax,10,black
\grad
}
%% image statement %%%%
\text{imgstat0=draw(200,200
\img
\plotf
\points
)}
\text{imgstat=<img src="\imgstat0" alt="représentation graphique">}
\text{sgn=randomitem(>,<)}
\text{sgntxt=\sgn issametext >?&gt; :&lt;}
\text{enonce= On a représenté ci-dessous la courbe \(\mathcal{C}\) d’une fonction <span class="nowrap">\(f\).</span>
<br>Les points \(A\)&#44; \(B\)&#44; \(R\) et \(S\) appartiennent à la courbe <span class="nowrap">\(\mathcal{C}\).</span>
<br>Leurs abscisses sont notées respectivement \(x_A\)&#44; \(x_B\)&#44; \(x_R\) et <span class="nowrap">\(x_S\).</span>
<div class="wimscenter">\imgstat</div>
L’inéquation \(x \times f(x) \sgntxt 0\) est vérifiée par&nbsp;&#58; }
%%%%%%%%%%%%%%%
\text{reponses=\(x_A\) et \(x_R\),\(x_A\) et \(x_B\),\(x_A\) et \(x_S),\(x_A\)&#44; \(x_B\) et \(x_R\),\(x_B\) et \(x_S\) }
\if{\k<0}{
  \if{\sgn issametext >}{
    \text{good= \reponses[5]}
    \text{shu=shuffle(1,2,3,4)}
    \text{bad1= \reponses[\shu[1]]}
    \text{bad2= \reponses[\shu[2]]}
    \text{bad3= \reponses[\shu[3]]}
    }{
    \text{good= \reponses[1]}
    \text{shu=shuffle(5,2,3,4)}
    \text{bad1= \reponses[\shu[1]]}
    \text{bad2= \reponses[\shu[2]]}
    \text{bad3= \reponses[\shu[3]]}
   }
}
\if{\k>0}{
  \if{\sgn issametext >}{
    \text{good= \reponses[1]}
    \text{shu=shuffle(5,2,3,4)}
    \text{bad1= \reponses[\shu[1]]}
    \text{bad2= \reponses[\shu[2]]}
    \text{bad3= \reponses[\shu[3]]}
    }{
    \text{good= \reponses[5]}
    \text{shu=shuffle(1,2,3,4)}
    \text{bad1= \reponses[\shu[1]]}
    \text{bad2= \reponses[\shu[2]]}
    \text{bad3= \reponses[\shu[3]]}
  }
}
\text{bads=\bad1,\bad2,\bad3}
%%%% feedback %%%%%%%
\text{sgnfA=\yA<0?négatif:positif}
\text{sgnfB=\yB<0?négatif:positif}

\text{prodA=\xA*\yA>0?positif:négatif}
\text{prodB=\xB*\yB>0?positif:négatif}

\text{solA=((\sgn issametext >) and (\prodA issametext positif)) or ((\sgn issametext <) and (\prodA issametext négatif))?vérifie l'inéquation:ne vérifie pas l'inéquation}
\text{solB=((\sgn issametext >) and (\prodB issametext positif)) or ((\sgn issametext <) and (\prodB issametext négatif))?vérifie l'inéquation:ne vérifie pas l'inéquation}

\text{exemplefeed=randomitem(<ul><li>\(x_A) est négatif (abscisse de \(A\))</li><li> \(f(x_A)) est \sgnfA (ordonnée de \(A\))</li></ul>Le produit \(x_A \times f(x_A)\) est donc \prodA&#44; \(x_A) \solA.,<ul><li>\(x_B) est négatif (abscisse de \(B\))</li><li> \(f(x_B)) est \sgnfB (ordonnée de \(B\))</li></ul>Le produit \(x_B \times f(x_B)\) est donc \prodB&#44; \(x_B) \solB.)}

\text{feedback=La bonne réponse est \good.
<br>En observant la position des points par rapport aux axes&#44; on peut lire les signes des nombres \(x_A\)&#44; \(x_B\)&#44; \(x_R\) et \(x_S\) ainsi que les signes de leurs images.<br>
<br>Avec ces informations&#44; on peut tester chaque solution. Par exemple&nbsp;&#58;\exemplefeed}
