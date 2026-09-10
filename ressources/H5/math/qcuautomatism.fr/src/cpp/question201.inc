\title{Question 201 T Signe fonction affine}
\keywords{quizz,inequations,affine_function}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }
%%% MB %%%%
\integer{sol=randomitem(1,2,3,4)*randomitem(-1,1)}
\text{list=shuffle(2,3,4)}
\integer{coeffdir=\list[1]*randomitem(-1,1)}
\integer{ordorig=-\sol*\coeffdir}
\function{f=\coeffdir*x+\ordorig}
\function{f1=x+\sol}
\function{f1b=\coeffdir<0? x-\sol:\sol-x}
\integer{bada=\coeffdir<0?-1*\list[2]:\list[2]}
\function{f2=\bada*x+\sol}
\text{tableau=slib(function/tabsignes [[x,\f],[-Inf,+Inf;\sol; ]],text=[\(f(x)\),replace,2] wimscenter wims_scrollable)}
\text{enonce=On considère une fonction \(f\) définie sur \(RR\) dont le tableau de signes est donné ci-dessous.  \tableau Quelle est la seule expression de \(f(x)\) possible&nbsp;&#63;}
\text{good=\(f(x)=\f\)}
\text{bads=\(f(x) =  \f1b \),\(f(x) = \f1\) ,\(f(x) = \f2\)}
\text{mot1=\coeffdir<0?négatif:positif}
\text{mot2=\coeffdir<0?positive:négative}
\text{mot3=\coeffdir<0?négative:positive}
\text{feedback=La bonne réponse était \good.<br> Puisque \(f(\sol)=0\) et que son coefficient directeur \(\coeffdir\) est \mot1.<br><u>Rappel&nbsp;&#58;</u> la fonction est d'abord \mot2 puis \mot3 donc le coefficient directeur est \mot1 .}
