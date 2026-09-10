\title{Question 300 T Equation graphique}
\keywords{quizz,equations,graphing}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }

\integer{cas=randomitem(1,2,3,4)} 

%%%% 1->0 sol , 
%%%% 2->1 unique, 
%%%% 3->2 racines de mm signe, 
%%%% 4->2 racines de signe opposés

\text{a=2,7,5,5}
\real{temp1=randint(25..35)/10}
\real{temp4=randint(2..16)/10}
\text{b=\temp1,12,2.8,\temp4}
\real{temp3=-1*randint(9..22)/10}
\text{c=3,0,\temp3,-0.9}
\text{d=1,1,1.3,1.3}
\real{a=\a[\cas]}
\real{b=\b[\cas]}
\real{c=\c[\cas]}
\real{d=\d[\cas]}


\text{eq=\( f(x)=0\)}
\text{listrep=L’équation \eq n’admet aucune solution.,L’équation \eq admet exactement une solution.,L’équation \eq admet exactement deux solutions et ces solutions sont de même signe.,L’équation \eq admet exactement deux solutions et ces solutions sont de signes contraires.}

%%%% fonction
\text{f=\a*sin(\d*x-\b)+\c}

%%%%% symétrie par rapport à l'axe des abscisses
\text{f=randomitem(1,1,-1)*(\f)}
\text{xmin=-3}
\text{xmax=2}
%%%%%% graduations

\text{grad=
  text black,2.5,-0.5,big,x
  parallel -3,-0.5,-3,0.5,1,0,6,black
  text black,-3,-0.5,big,-3
  text black,-2,-0.5,big,-2
  text black,-1,-0.5,big,-1
  text black,1,-0.5,big,1
  text black,2,-0.5,big,2
  
  text black,0.3,9.8,big,y  
  parallel -0.1,-10,0.1,-10,0,2,10,black
  text black,0.3,-1.5,big,-2
  text black,0.3,-3.5,big,-4
  text black,0.3,-5.5,big,-6
  text black,0.3,-7.5,big,-8
  text black,0.3,2.5,big,2
  text black,0.3,4.5,big,4
  text black,0.3,6.5,big,6
  text black,0.3,8.5,big,8}
 
\text{img=
range -4,3,-10,10
linewidth 1
  parallel -4,-11,-4,11,1,0,10,grey
  parallel -4,-10,3,-10,0,2,12,grey
arrow -4,0,3,0,10,black
arrow 0,-11,0,10,10,black
\grad
linewidth 2
  trange -3,2
  plot red,\f

}
%% image statement %%%%
\text{imgstat0=draw(200,200
\img
)}
\text{imgstat=<img src="\imgstat0" alt="représentation graphique">}
%%% image feedback %%%%%%
\text{abssol=solve(\f,x=-3..2)}
\text{cross=}
\if{\cas=2}{\text{cross=linewidth 2
  crosshair \abssol,0,green}
  }
\if{\cas>2}{\text{cross=linewidth 2
  crosshair \abssol[1],0,green
  crosshair \abssol[2],0,green}
  }
\text{imgfeed=draw(200,200
  \img
  \cross)}
\text{imgfeed=<img src="\imgfeed" alt="solution">}
%%%
\text{enonce=On donne ci-contre la courbe représentative \( \mathcal{C} \) d’une fonction \(f\) définie sur l’intervalle <span class="nowrap">\(\left[\xmin \,;\, \xmax \right]\).</span> <br>On s’intéresse à l’équation \eq. <div class="wimscenter">\imgstat</div>Une seule de ces propositions est exacte&nbsp;&#58; }

\text{good=\listrep[\cas]}
%%%%%
\if{\cas==1}{\text{bads=\listrep[2],\listrep[3],\listrep[4]}}
\if{\cas==2}{\text{bads=\listrep[1],\listrep[3],\listrep[4]}}
\if{\cas==3}{\text{bads=\listrep[1],\listrep[2],\listrep[4]}}
\if{\cas==4}{\text{bads=\listrep[1],\listrep[2],\listrep[3]}}

%%%% feedback %%%%%%%
\text{nbpoints=il n'y en a pas,il y en a qu'un seul,il y en a deux,il y en a deux}
\text{infopt=}
\text{infopt=\cas>1?<i>(Croix verte ci-dessous)</i>:\infopt}
\text{infopt=\cas>2?<i>(Croix vertes ci-dessous)</i>:\infopt}

\if{\cas=3}{
  \text{tempfeed=<br>Ces deux points ont des abscisses de même signe. 
  <br>Les solutions sont de même signe.}
  }
\if{\cas=4}{
  \text{tempfeed=<br>Ces deux points ont des abscisses de signes contraires. 
  <br>Les solutions sont de signes contraires.}
  }
  
\text{feedback=La bonne réponse est <b>\good</b> <br>Il suffit de regarder le nombre de points d'intersection de la courbe avec l'axe des abscisses. <br>Ici \nbpoints[\cas] \infopt. \tempfeed <div class="wimscenter">\imgfeed</div>}
