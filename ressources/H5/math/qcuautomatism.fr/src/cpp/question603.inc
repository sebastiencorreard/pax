\title{Question 603 NS Lecture graphique du coefficient directeur}
\keywords{quizz,functions,affine_function}
\observation{Question du sujet zéro sujet-specifique-3.pdf publié sur EDUSCOL en juin 2025 }
%%% MB %%%%
\integer{a=randitem(-4,-3,-2,-1,1,2,3,4)}
\integer{b=randint(1..4)*-\a/abs(\a)}

\function{f=\a*x+\b}

%%%%%%%%%%%%%% graphique
\integer{xmin=-6}
\integer{xmax=6}
\integer{ymin=-6}
\integer{ymax=6}

\text{grad=
  text black,5.7,1,medium,x
  text black,-5.3,-0.05,small,-5
  text black,-4.3,-0.05,small,-4
  text black,-3.3,-0.05,small,-3
  text black,-2.3,-0.05,small,-2
  text black,-1.3,-0.05,small,-1
  text black,0.9,-0.05,small,1
  text black,1.9,-0.05,small,2
  text black,2.9,-0.05,small,3
  text black,3.9,-0.05,small,4
  text black,4.9,-0.05,small,5
  text black,-1,5.8,medium,y 
  text black,-0.8,-0.55,small,-1
  text black,-0.8,-1.55,small,-2
  text black,-0.8,-2.55,small,-3
  text black,-0.8,-3.55,small,-4
  text black,-0.8,-4.55,small,-5
  text black,-0.5,1.4,small,1
  text black,-0.5,2.4,small,2
  text black,-0.5,3.4,small,3
  text black,-0.5,4.4,small,4
  text black,-0.5,5.4,small,5

  }
\text{img=
range \xmin,\xmax,\ymin,\ymax

parallel -6,-6,-6,6,1,0,13,grey
parallel -6,-6,6,-6,0,1,13,grey
hline 0,0,black
vline 0,0,black
arrow \xmin,0,\xmax,0,12,black
arrow 0,\ymin,0,\ymax,12,black
\grad

linewidth 1
  plot black,\f
}
%% image statement %%%%
\text{imgstat0=draw(200,200
\img
)}
\text{imgstat=<img src="\imgstat0" alt="représentation graphique">}
\integer{good=\a}
\integer{bad1=\b}
\integer{bad2=(\b==-\a)? \b+\b/abs(\b):-\a}
\integer{bad3=(\a<0)? \a-1:\a+1}
\text{bads=\bad1,\bad2,\bad3}
\text{enonce=On a représenté ci-dessous une droite <span class="nowrap">\(\mathcal{D}\).</span> <div class="wimscenter">\imgstat</div><br>
Le coefficient directeur de cette droite \(\mathcal{D}\) est&nbsp;&#58; }

\integer{c=\a+\b}
\text{btxt=\b<0?(\b):\b}
\text{feedback=La bonne réponse est \good. <br> Les points A(0&#59;\b) et B(1&#59;\c) appartenant à la droite&#44; le coefficient directeur est <span class="nowrap">\(\frac{\c-\btxt}{1-0}\).</span> }
