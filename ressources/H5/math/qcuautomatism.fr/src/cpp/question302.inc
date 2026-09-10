\title{Question 302 S Equation carrée bis}
\keywords{quizz,equations,graphing}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }

\integer{n=randomitem(10,20,30)}
\real{sqrtn=sqrt(10)}
\text{sgn=randomitem(\geq,\leq)} signe gleq ou leq
%%%% fonction
\text{f=x^2}


\text{xmin=-4}
\text{xmax=4}
\text{ymin=-5}
\text{ymax=15}
%%%%%% graduations

\text{grad=
  text black,3.5,-0.5,big,x
  segment -0.1,10,0.1,10,black
  text black,0.4,10.5,big,\n
  text black,0.4,-0.4,big,0
  text black,-0.5,14,big,y  
  }
\text{plotf=linewidth 2
  trange \xmin,\xmax
  plot red,\f} 
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
%%%% feed %%%%
\if{\sgn issametext \geq}{
  \text{\tracesol=linewidth 2
  segment \xmin,0,-\sqrtn,0,blue 
  segment \sqrtn,0,\xmax,0,blue
  trange \xmin,-\sqrtn
   plot red,\f 
  trange \sqrtn,\xmax
   plot red,\f
  }
  }{
  \text{\tracesol=linewidth 2
  segment -\sqrtn,0,\sqrtn,0,blue
  trange -\sqrtn,\sqrtn
  plot red,\f }
  }
\text{imgf=draw(200,200
\img
trange \xmin,\xmax
  plot green,10
\tracesol 
)}
\text{imgfeed=<img src="\imgf" alt="représentation graphique">}

\text{enonce=On a représenté ci-contre la parabole d’équation <span class="nowrap">\(y=x^2\).</span><br>On note \((\mathcal{I})\) l’inéquation&#44;  sur \(\mathbb{R}\)&#44;  <span class="nowrap">\(x^2\sgn \n\).</span><div class="wimscenter">\imgstat</div>L’inéquation \((\mathcal{I})\) est équivalente à&nbsp;&#58; }


\text{good= \sgn issametext \geq? \(x \leq -\sqrt{\n}\) ou \(x \geq \sqrt{\n}\):\(-\sqrt{\n} \leq x \leq \sqrt{\n}\)}
%%%%%
\text{bad1=\sgn issametext \leq? \(x \leq -\sqrt{\n}\) ou \(x \geq \sqrt{\n}\):\(-\sqrt{\n} \leq x \leq \sqrt{\n}\)}
\text{bad2=\sgn issametext \geq? \(x \geq \sqrt{\n}\):\(x \leq \sqrt{\n}\)}
\text{bad3=\(x = \sqrt{\n}\)}
\text{bads=\bad1,\bad2,\bad3}
%%%% feedback %%%%%%%
\text{mot1=\sgn issametext \geq?au dessus:au dessous}
\text{feedback=La question revient à chercher toutes les solutions de <span class="nowrap">\(x^2 \sgn \n\).</span>
<br>Ci-dessous on a tracé en rouge les points qui conviennent.
<br>Ce sont les points qui sont <b>\mot1</b> de la droite (verte) d'équation <span class="nowrap">\(y=\n\).</span>
<br>Toutes les abscisses de ces points sont en bleu ci-dessous <div class="wimscenter">\imgfeed</div>
<br>\((\mathcal{I})\) est donc équivalente à \good}
