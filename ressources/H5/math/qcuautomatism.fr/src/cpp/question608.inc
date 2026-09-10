\title{Question 608 NS antécédent par une fonction du second degré sous forme développée}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }
\keywords{quizz,functions,reference_function}

\integer{a=randint(2..4)}
\integer{b=randint(2..5)*randitem(1,-1)}
\integer{c=randint(1..9)}

\function{f=\a*x^2+\b*x+\c}
\integer{x=randint(-2..2)}
\integer{imgf=evalue(\f,x=\x)}
\integer{imgb=evalue(\f,x=\imgf)}

\text{enonce=On considère la fonction \(f\) définie pour tout réel \(x\) par\(f(x)=\f\). <br>Un antécédent de \(\imgf\) par la fonction \(f\) est &nbsp;&#58;}

\real{bad1=\x+randitem(1,-1)}
\real{bad2=(\bad1>\x)? \x+randitem(-1,2):\x+randitem(1,-2)}
\real{bad3=(abs(\imgb-\x)<3)? \x+randitem(3,-3):\imgb}

\text{good=\x}
\text{bads=\bad1,\bad2,\bad3}
\text{feedback=La bonne réponse était \good.<br> Il suffit de tester les images des réponses proprosées (on remplace la variable \(x\) par \(\x\) pour calculer l'image \(f(\x)\)).}
