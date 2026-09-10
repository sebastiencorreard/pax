\title{Question 606 NS image par une fonction du second degré}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }
\keywords{quizz,functions,reference_function}
%%% CD %%%%
\rational{c=randomitem(1/2,1/4)*randomitem(-1,-1,1)}
\integer{b=-1*randint(1..7)}
\integer{a=randint(2..12)}
\function{f=maxima(\a+\c*(x+\b)^2)}
\integer{x=randitem(-\b,-\b-2,-\b-4)}
\integer{imgf=evalue(\f,x=\x)}

\text{enonce=On considère la fonction \(f\) définie pour tout réel \(x\) par\(f(x)=\f\). <br>L'image de \(\x\) par la fonction \(f\) est &nbsp;&#58;}

\real{bad1=(\x==-\b)? \a+\c:randitem(0,\a+2*\c*(\x+\b))}
\real{bad2=(\x==-\b)? 0:(\a+\c)*(\x+\b)*(\x+\b)}
\real{bad3=(\x==-\b)? \a-\c:\a-\c*(\x+\b)*(\x+\b)}

\text{good=\imgf}
\text{bads=\bad1,\bad2,\bad3}
\text{feedback=La bonne réponse était \good.<br> Il suffit de remplacer la variable \(x\) par \(\x\) pour calculer l'image \(f(\x)\).}
