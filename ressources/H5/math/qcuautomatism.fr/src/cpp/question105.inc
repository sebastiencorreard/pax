\title{Question 105 S Programme de calcul }
\keywords{quizz,quizz,skill_calculate,calculation}
\observation{Question du sujet zéro sujet-specialite-1.pdf publié sur EDUSCOL en juin 2025 }
\integer{n=randomitem(5,7,8,6,10)}
\text{cas=floor(\n/2)=\n/2?m:d}
\text{mot2=\cas issametext m?de la moitié:du double}
\text{cas2=randomitem(i,o)}
\text{mot1=\cas2 issametext i?L'inverse:L'opposé}
\text{enonce=\mot1 \mot2 de \n est égal à&nbsp;&#58;  }

\if{\cas issametext m}
  {%%%% moitié
  \if{\cas2 issametext i}
    {%%%%% L'inverse de la moitié
    \integer{temp=\n/2}
    \text{good=\(\frac{1}{\temp}\)}
    \integer{temp0=\n/2}
    \text{bad1=\(\temp0\)}
    \text{bad2=\(-\temp0\)} %%%% confusion inverse opposé
    \integer{temp=2*\n}
    \text{bad3=\(\frac{1}{\temp}\)} %%%% confusion moitié et double
    \text{finfeed=<br> Pour obtenir la moitié de \n on divise par 2 (on obtient \temp0) puis on prend l'inverse \(\frac{1}{\temp0}\)}
    }
    {%%%%% L'opposé de la moitié
    \integer{temp0=\n/2}
    \text{good=\(-\temp0\)}
    \text{bad1=\(\temp0\)}
    \text{bad2=\(\frac{1}{\temp0}\)} %%%% confusion inverse opposé
    \integer{temp=2*\n}
    \text{bad3=\(\frac{1}{\temp}\)} %%%% confusion moitié et double
    \text{finfeed=<br> Pour obtenir la moitié de \n on divise par 2 (on obtient \temp0) puis on prend l'oppposé \(-\temp0\)}
    }
  }
  {%%%%% le double
  \if{\cas2 issametext i}
    {%%% L'inverse du double
    \integer{temp=2*\n}
    \text{good=\(\frac{1}{\temp}\)}
    \text{bad1=\(\temp\)}
    \text{bad2=\(-\temp\)} %%%% confusion inverse opposé
    \text{bad3=\(\frac{2}{\n}\)} %%%% confusion moitié et double
    \text{finfeed=<br> Pour obtenir le double de \n on multiplie par 2 (on obtient \temp) puis on prend l'inverse \(\frac{1}{\temp}\)}
    }
    {%%% L'opposé du double
    \integer{temp=2*\n}
    \text{good=\(-\temp\)}
    \text{bad1=\(\temp\)}
    \text{bad2=\(\frac{2}{\n}\)}
    \text{bad3=\(\frac{1}{\temp}\)} %%%% confusion moitié et double
    \text{finfeed=<br> Pour obtenir le double de \n on multiplie par 2 (on obtient \temp) puis on prend l'opposé \(-\temp\)}
    }
  }

\text{bads= \bad1,\bad2,\bad3}
\text{feedback=La bonne réponse est \good. \finfeed.}
