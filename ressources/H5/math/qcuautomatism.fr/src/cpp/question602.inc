\title{Question 602 S Deviner l'équation d'une fct affine}
\keywords{quizz,functions,affine_function}
\observation{Question du sujet zéro sujet-specialite-2.pdf publié sur EDUSCOL en juin 2025 }
%%% MB %%%%


\text{signa=randomitem(-1,1)}
\function{f=\signa*x}

%%%%%%%%%%%%%% graphique
\integer{xmin=-6}
\integer{xmax=6}
\integer{ymin=-6}
\integer{ymax=6}

\text{grad=
  text black,5.5,1,giant,x
  text black,0.1,-0.4,giant,0
  text black,-1,5.8,giant,y  
  }
\text{coordD=\signa=-1?-5.2,4.5:5.2,5} 
\text{img=
range \xmin,\xmax,\ymin,\ymax
arrow \xmin,0,\xmax,0,20,black
arrow 0,\ymin,0,\ymax,20,black
\grad
linewidth 1
  plot black,\f

}
%% image statement %%%%
\text{imgstat0=draw(200,200
\img
)}
\text{imgstat=<img src="\imgstat0" alt="représentation graphique">}
\text{cas=randomitem(1,2,3)} %%%% 1 .... forme avec les carrés 2...Equation réduite 3... equation cartésienne
%%%% Condition sens de variation et passe par l'origine
\text{goodred=}
\if{\cas=1}{
  \text{good=\signa=-1?\(\mathcal{y}=\mathcal{x}^2-(\mathcal{x}+1)^2+1\):\(\mathcal{y}=\mathcal{x}^2-(\mathcal{x}-1)^2+1\)}
  \text{goodred=\signa=-1?\({}=-2\mathcal{x}\):\({}=2\mathcal{x}\)} %%% pour feed
  \text{bad1=\signa=-1?\(\mathcal{y}=-2\mathcal{x}+1\):\(\mathcal{y}=2 \mathcal{x}+1\)} %%%% red qui passe pas par l'origine
  \text{bad2=\signa=-1?\(\mathcal{x}+\mathcal{y} +1=0\):\(-\mathcal{x}+\mathcal{y} +1=0\)} %%%% cartes qui passe pas par l'origine
  \text{bad3=\signa=-1?\(2\mathcal{x}-\mathcal{y} =0\):\(2\mathcal{x}+\mathcal{y} +1=0\)} %%%% cartes pas bon sens de variation
 }
\if{\cas=2}{
  \text{good=\signa=-1?\(\mathcal{y}=-2\mathcal{x}\):\(\mathcal{y}=2 \mathcal{x}\)} %%%% red 
  \text{bad1=\signa=1?\(\mathcal{y}=\mathcal{x}^2-(\mathcal{x}+1)^2+1\):\(\mathcal{y}=\mathcal{x}^2-(\mathcal{x}-1)^2+1\)} %%% pas bon sens de var
  \text{bad2=\signa=-1?\(\mathcal{x}+\mathcal{y} +1=0\):\(-\mathcal{x}+\mathcal{y} +1=0\)} %%%% cartes qui passe pas par l'origine
  \text{bad3=\signa=-1?\(2\mathcal{x}-\mathcal{y} =0\):\(2\mathcal{x}+\mathcal{y}=0\)} %%%% cartes pas bon sens de variation
}
\if{\cas=3}{
  \text{good=\signa=-1?\(2\mathcal{x}+\mathcal{y} =0\):\(2\mathcal{x}-\mathcal{y}=0\)}
  \text{bad1=\signa=1?\(\mathcal{y}=\mathcal{x}^2-(\mathcal{x}+1)^2+1\):\(\mathcal{y}=\mathcal{x}^2-(\mathcal{x}-1)^2+1\)} %%% pas bon sens de var
  \text{bad2=\signa=-1?\(\mathcal{x}+\mathcal{y} +1=0\):\(-\mathcal{x}+\mathcal{y} +1=0\)} %%%% cartes qui passe pas par l'origine
  \text{bad3=\signa=-1?\(\mathcal{y}=-2\mathcal{x}+1\):\(\mathcal{y}=2 \mathcal{x}+1\)} %%%% red qui passe pas par l'origine
}
  
\text{bads=\bad1,\bad2,\bad3}
\text{enonce=On a représenté ci-dessous une droite <span class="nowrap">\(\mathcal{D}\).</span> <div class="wimscenter">\imgstat</div><br>Parmi les quatre équations ci-dessous&#44; la seule susceptible de représenter la droite \(\mathcal{D}\) est&nbsp;&#58; }
\text{croissance=\signa=-1?décroissante:croissante}
\text{mot1=\signa=-1?négatif:positif}
\text{feed1=\cas=1?\goodred (après développement et réduction):}
\text{feedback=La bonne réponse est \good\feed1. <br> On peut lire sur le graphique les informations suivantes&nbsp;&#58; <br>La fonction affine associée est \croissance ce qui signifie que le coefficient directeur est \mot1.<br>La droite passe par le point de coordonnées \(\left(0 &#59; 0\right)\) l'ordonnée à l'origine est donc égal à <span class="nowrap">\(0\).</span><br><b>Avec ces informations</b> on peut regarder si chacune des équations données vérifient ces deux conditions. }
