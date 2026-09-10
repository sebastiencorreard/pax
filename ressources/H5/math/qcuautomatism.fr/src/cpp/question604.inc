\title{Question 604 NS résolution graphique d'une équation}
\keywords{quizz,functions,equations}
\observation{Question du sujet zéro sujet-specifique-3.pdf publié sur EDUSCOL en juin 2025 }

%%choix des solutions et génération de la fonction de degré 3 ou 4%%
\integer{deg=randitem(3,4)}
\if{\deg==3}{
\integer{x1=randitem(-2,-1)}
\integer{x2=(\x1==-2)? randitem(-1,0,1):randitem(0,1,2)}
\integer{x3=(\x2==2)? 3:randitem(2,3)}
\real{a=(\x3==3)? 0.05*randint(7..14)*randitem(-1,1):0.1*randint(4..10)*randitem(-1,1)}%%coefficient de x^3%%
\function{f=\a*(x-\x1)*(x-\x2)*(x-\x3)}
\text{good=&#123;\x1;\x2;\x3&#125;}
\text{bad1=&#91;\x1;\x3&#93;}
\text{bad2=&#123;3&#125;}
}{
\integer{x1=randitem(-2,-1)}
\integer{x2=(\x1==-2)?-1:0}
\integer{x3=(\x2==0)?randitem(1,2):randitem(0,1)}
\integer{x4=(\x3==2)? 3:randitem(2,3)}
\real{a=(\x4==3)? 0.02*randint(13..20)*randitem(-1,1):0.05*randint(10..20)*randitem(-1,1)}%%coefficient de x^4%%
\function{f=\a*(x-\x1)*(x-\x2)*(x-\x3)*(x-\x4)}
\text{good=&#123;\x1;\x2;\x3;\x4&#125;}
\text{bad1=&#91;\x1;\x4&#93;}
\text{bad2=&#123;4&#125;}
}

%%%%%%%%%%%%%% graphique
\integer{xmin=-6}
\integer{xmax=6}
\integer{ymin=-6}
\integer{ymax=6}

\text{grad=
  text black,5.5,1,giant,x
  text black,0.1,-0.2,giant,0
  text black,-1,5.8,giant,y  
  text black,1.1,-0.2,giant,1
  text black,0.1,1,giant,1
  segment 1,-0.4,1,0.4,black
  segment -0.4,1,0.4,1,black
  }
\text{img=
range \xmin,\xmax,\ymin,\ymax
arrow \xmin,0,\xmax,0,15,black
arrow 0,\ymin,0,\ymax,15,black
parallel -6,-6,-6,6,1,0,13,grey
parallel -6,-6,6,-6,0,1,13,grey
hline 0,0,black
vline 0,0,black
\grad
linewidth 1
  plot black,\f
}
%% image statement %%%%
\text{imgstat0=draw(200,200
\img
)}
\text{imgstat=<img src="\imgstat0" alt="représentation graphique">}

\real{image=floor(evalue(\f,x=0)*10)/10}
\text{bad3=&#123;\image&#125;}
\text{bads=\bad1,\bad2,\bad3}
\text{enonce=Soit \(f\) une fonction définie sur \(\mathbb{R}\) dont la représentation graphique est donnée ci-dessous. <div class="wimscenter">\imgstat</div>
L’ensemble \(\mathcal{S}\) des solutions de l’équation \(f(x)=0\) est&nbsp;&#58;}

\text{feedback=La bonne réponse est \good. <br> Les solutions sont les abscisses des points d'intersection de la courbe avec l'axe des abscisses. }
