\title{Question 102 T Calculs et conversions de longueurs}
\keywords{quizz,conversion,power,length}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }

\integer{a=randomitem(50,60,70,80,90)}
\integer{n=randomitem(-3,-3,-4)}
\text{unite=\n=-3?mm:cm}
\integer{k=randint(2..4)*randomitem(100,1000)}
\real{temp1=\k*\a*10^(\n)} %%%% valeur en unite
\real{tempgood=\unite issametext mm?\temp1/10:\temp1*10} %%% valeur en cm / valeur en mm
\text{tempgood1=\unite issametext mm?\tempgood cm:\tempgood mm}
\text{good=\tempgood1}
\text{bad1=\unite issametext mm?\tempgood mm:\tempgood cm} %%% bonne valeur mauvaise unité
\real{tempbad=\unite issametext cm?\temp1/10:\temp1*10} %%%% mauvaise valeur
\text{bad2=\unite issametext mm?\tempbad cm:\tempbad mm} %%%% mauvaise valeur bonne unité
\text{bad3=\unite issametext mm?\tempbad mm:\tempbad cm} %%%% mauvais valeur et mauvaise unité
\text{bads=\bad1,\bad2,\bad3}
\text{enonce=L’épaisseur d’une feuille de papier est égale à <span class="nowrap">\(\a \times 10^{\n} \unite\).</span><br>L’épaisseur d’une pile de \( \k \) feuilles est égale à&nbsp;&#58;}
\text{feedback=Il faut effectuer le calcul suivant&nbsp;&#58;  \(\k \times \a \times 10^{\n} \unite=\temp1 \unite\)<br><span class="nowrap">\({}= \good \).</span>}
