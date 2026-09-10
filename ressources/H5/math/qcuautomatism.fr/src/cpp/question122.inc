\title{Question 122 NS Un prix }
\keywords{quizz,skill_calculate}
\observation{Question du sujet zéro sujet-specifique-2_0.pdf publié sur EDUSCOL en juin 2025 }
\integer{n=randitem(4,6,8,10)}
\real{prixn=\n*randitem(1.15,1.2,1.25,1.3,1.4,1.5)}
\real{c=randitem(1.5,2.5)}
\integer{m=\n*\c}

\text{enonce=\n croissants coûtent \prixn euros. \m croissants coûtent&nbsp;&#58; }

\real{g=\m*\prixn/\n}
\text{good=\g euros}
%%%%%%%%%% 
\real{bad1=\prixn*\m}
\real{bad2=floor(100*\prixn*\prixn/\n)/100}
\real{bad3=\prixn+(\m-\n)}
\text{bads=\bad1 euros,\bad2 euros,\bad3 euros}

\text{feedback=La bonne réponse est \good car \m croissants coûtent \(\frac{\prixn*\m}{\n}=\g) euros. }
