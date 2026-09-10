\title{Question 301 S Equation carrée}
\keywords{quizz,equations,squareroot}
\observation{Question du sujet zéro sujet-specialite-2.pdf publié sur EDUSCOL en juin 2025 }
\text{x=randomitem(x,y,t)}
\integer{p=randomitem(6,8,10)*randomitem(1,1,1,-1)}
\integer{p2=abs(\p/2)}

\text{enonce=On note \(\mathcal{S}\) l’ensemble des solutions de l’équation \(\x^2=\p\) sur <span class="nowrap">\(RR\).</span> On a&nbsp;&#58;}
\text{rgood=\sqrt{\p}}
\text{good=\p<0?\(\mathcal{S}=\varnothing\):\(\mathcal{S}=\left\{ -\rgood ; \rgood \right\} \)}
\integer{temp2=abs(\p)}
\text{bad2=\p<0?\(\mathcal{S}=\left\{ -\sqrt{\temp2} ; \sqrt{\temp2} \right\} \):\(\mathcal{S}=\varnothing\)}
\text{bad3=\(\mathcal{S}=\left\{ -\p2 ; \p2 \right\} \)}
\text{bads=\(\mathcal{S}=\left\{ -\sqrt{\p2} ; \sqrt{\p2} \right\} \),\bad2,\bad3} 
\text{feed1=Tous les carrés sont positifs. Aucun ne peut être égal à \p.}
\text{feed2=Si on l'a oublié&#44; on peut résoudre&nbsp;&#58; <br>\(\x^2-\p=0\) \(\Leftrightarrow\) \((\x-\sqrt{\p})(\x+\sqrt{\p})=0\)}
\text{feed=\p<0?\feed1:\feed2}

\text{feedback=La bonne réponse est "\good".<br> \feed}
