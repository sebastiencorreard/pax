\title{Question 350 S Reconnaitre le tableau de signe}
\keywords{quizz,inequations,trinomial,roots}
\observation{Question du sujet zéro sujet-specialite-2_0.pdf publié sur EDUSCOL en juin 2025 }
\text{listrac=shuffle(2,3,5)}
\integer{k=randomitem(2,3,5)*randomitem(-1,1)}
\text{sgn=shuffle(+,-)}%%% signe racine
\integer{rac1=\listrac[1]*randomitem(1,-1)}
\integer{rac2=\listrac[2]*randomitem(1,-1)}
\function{f1=pari(\k*x-(\rac1)*\k)}
\function{f2=pari(x-(\rac2))}

\function{f=(\f1)*(\f2)}
\text{tsf=slib(function/tabsignes [[x,\f],[-Inf,+Inf;\rac1,\rac2;]],text=[\(f\),replace,2])}
\text{enonce= La fonction \(f\) définie sur \(RR\) par \(f(x)= (\f1)(\f2)\) admet pour tableau de signes&nbsp;&#58; }

\text{good= \tsf}
%%%%%
\function{fb=-1*\f}

\integer{rac1b=-1*\rac1}
\integer{rac2b=-1*\rac2}
\function{g1=\k*x-(\rac1b)*\k}
\function{g2=x-(\rac2b)}
\function{g=(\g1)*(\g2)}
\function{gb=-1*(\g)}
\text{tsf1=slib(function/tabsignes [[x,\fb],[-Inf,+Inf;\rac1,\rac2;]],text=[\(f\),replace,2])}
\text{tsg=slib(function/tabsignes [[x,\g],[-Inf,+Inf;\rac1b,\rac2b;]],text=[\(f\),replace,2])}
\text{tsg1=slib(function/tabsignes [[x,\gb],[-Inf,+Inf;\rac1b,\rac2b;]],text=[\(f\),replace,2])}
\text{bad1=\tsf1}
\text{bad2=\tsg}
\text{bad3=\tsg1}
\text{bads=\bad1,\bad2,\bad3}
%%%% feedback %%%%%%%
\text{sgnk=\k>0?positif:négatif}
\text{sgnkbis=\k<0?positif:négatif}
\text{feedback=La bonne réponse est \good On note que&nbsp;&#58;<ul><li> les deux racines sont \rac1 et \rac2 </li><li> en développant le coefficient de \(x^2\) vaut \k</li></ul> On sait donc que la fonction est de signe \sgnkbis (l'opposé du signe de \k) entre les racines&#44; \sgnk sinon.}
