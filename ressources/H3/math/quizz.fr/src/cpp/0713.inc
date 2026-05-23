\title{Question 0713 Multiplication entier décimal }
\keywords{multiplication,decimals}
\integer{n=randint(5..9)*10}
\integer{cas=randomitem(1,2,2)}
\real{p1=randint(2..4)}
\real{p=\p1/(10^\cas)}
\real{p10=\cas==1?0.1:0.01}
\text{enonce= \(\n \times \p ={}\) }
\text{enonceb=}

%% 
\text{decim=\cas==1?une décimale:deux décimales}
\real{rep=\n*\p}
\text{feedback=\p possède \decim, le résultat doit en avoir autant. Ou encore : \(\n \times \p1 \times \p10\)  }
