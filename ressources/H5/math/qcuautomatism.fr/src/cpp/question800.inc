\title{Question 800 S Probabilités et dés}
\keywords{quizz,probability}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }
\text{np1=randomitem(1,3,5)}
\text{p1=0.\np1}
\text{dp2=randomitem(3,6)}
\text{p2=1/\dp2}
\real{np3=\dp2=3?1:2} %%% p
\real{p3=0.\np3}
\integer{dgood=\dp2*10}
\integer{numgood=(\np1+\np3)*\dp2+10}
\integer{temp=maxima(gcd(\dgood,\numgood))}
%%%% réduction de la somme
\integer{dgood=\dgood/\temp}
\integer{numgood=\numgood/\temp}
%%%%% pourfeedback %%%%
\integer{nsomme=\numgood}
\integer{dsomme=\dgood}
%%%% complément à 1
\integer{numgood=\dgood-\numgood}
%%%%% bonne réponse
\text{good=\numgood/\dgood}
%%% malange des probabilités
\text{p=shuffle(\p1,\p2,\p3)}
\text{p1=\p[1]}
\text{p2=\p[2]}
\text{p3=\p[3]}
\text{x=randomitem(x,x,y,p)}
\text{enonce=On lance un dé à 4 faces. La probabilité d’obtenir chacune des faces est donnée dans le tableau ci-dessous&nbsp;&#58;
<div class="wimscenter wims_scrollable">
<table class="wimsborder">
  <tr>
    <th>Face numéro 1 </th>
    <th>Face numéro 2 </th>
    <th>Face numéro 3 </th>
    <th>Face numéro 4 </th>
  </tr>
  <tr>
    <td>\(\p1\)</td>
    <td>\(\p2\)</td>
    <td>\(\p3\)</td>
    <td>\(\x\)</td>
    </tr>
</table>
</div>
On peut affirmer que&nbsp;&#58;}
\text{good=\(\x=\good\)}
%%%%% mauvaise réponse : p1+p2 
\integer{np1p2=\np1*\dp2+10}
\integer{dp1p2=10*\dp2}
%%% simplification
\integer{temp=maxima(gcd(\np1p2,\dp1p2))}
%%%% réduction de la somme
\integer{np1p2=\np1p2/\temp}
\integer{dp1p2=\dp1p2/\temp}

\text{bad1=\np1p2/\dp1p2}
%%%%% mauvaise réponse : arrondi à 0.1 de p2+p3 
\integer{bad2=floor(10*(\p2+\p3))}
\text{bad2=0.\bad2}
%%%%% mauvaise réponse : somme plus grande que 1 des 4 probab 
\integer{bad3=floor(10-10*(\p1+\p2+\p3))+randomitem(1,2)}
\text{bad3=0.\bad3}
\real{temp=\bad2+0.1}
\text{bad3=\bad3=\bad2?\temp:\bad3}

\text{bads=\(\x=\bad1\),\(\x=\bad2 \),\( \x=\bad3\)}
\text{feedback=La bonne réponse est <b>"\good"</b>.<br> Il faut calculer \(\p1+\p2+\p3\) <span class="nowrap">\({}=\frac{\nsomme}{\dsomme}\).</span><br>Puis <span class="nowrap">\(1-\frac{\nsomme}{\dsomme}\).</span>}
