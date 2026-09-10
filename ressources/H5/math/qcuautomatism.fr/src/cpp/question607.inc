\title{Question 607 NS image par une fonction du second degré sous forme développée}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }
\keywords{quizz,functions,reference_function}
%%% CD %%%%
\rational{c=randomitem(1/2,1/4)*randomitem(-1,-1,1)}

\integer{a=randint(2..4)*-1}
\integer{b=randint(2..5)}
\integer{c=randint(2..9)}

\function{f=\a*x^2+\b*x+\c}
\integer{x=randint(2..4)*-1}
\integer{b=(\b==\a*\x)? \b+1:\b}%%éviter des réponses identiques%%
\integer{imgf=evalue(\f,x=\x)}

\text{enonce=On considère la fonction \(f\) définie pour tout réel \(x\) par\(f(x)=\f\). <br>L'image de \(\x\) par la fonction \(f\) est &nbsp;&#58;}

\real{bad1=-\a*(\x)^2+\b*\x+\c}
\real{bad2=\a*(\x)^2-\b*\x+\c}
\real{bad3=(\a*\x)^2+\b*\x+\c}

\text{good=\imgf}
\text{bads=\bad1,\bad2,\bad3}
\text{feedback=La bonne réponse était \good.<br> Il suffit de remplacer la variable \(x\) par \(\x\) pour calculer l'image \(f(\x)\).}
