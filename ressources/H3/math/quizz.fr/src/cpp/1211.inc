\title{Question 1211 Entier le plus proche}
\keywords{mental_calculation,decimals}

\matrix{quest=e,Pi,sqrt(2);e,\pi,\sqrt{2}}
\text{n=shuffle(3)}
\real{a=\quest[1;\n[1]]}
\real{approxa=rint(\a*100)/100}
\text{atxt=\quest[2;\n[1]]}
\real{b=\quest[1;\n[2]]}
\text{btxt=\quest[2;\n[2]]}
\real{approxb=rint(\b*100)/100}
\text{sign=random(+,-)}
\real{temp01=\sign issametext + ?\a + \b:\a-\b}
\real{rep=rint(\temp01) }
\text{enonce=L'entier le plus proche de \(\atxt \sign \btxt\). }
\text{enonceb=}
\text{feedback= Rappel &#58;  \(\atxt \simeq \approxa \) à \(0.01\) près <br>et \(\btxt \simeq \approxb \) à \(0.01\) près }
