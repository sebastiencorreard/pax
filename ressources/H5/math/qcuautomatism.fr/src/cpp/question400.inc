\title{Question 400 T Proportion de proportion}
\keywords{quizz,percentage,percents,fraction}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }

%%%%% p1 , p2 ,ecrt fract de p1, 
\matrix{coeff=25,randomitem(80,40),\frac{1}{4}
10,randomitem(70,80,90,50,40,30),\frac{1}{10}
20,randomitem(70,80,90,40,50,30),\frac{1}{5}
}

\text{coeff=randomrow(\coeff)}
\integer{p1=\coeff[1]}
\real{p1dec=\p1/100}
\integer{p2=\coeff[2]}
\real{p2decfx=\p2/1000}

\text{benoit=slib(lang/fname )}
\text{jour=randomitem(samedi,dimanche)}

\text{enonce=\benoit consacre \(\p1 \% \) de sa journée de \jour à faire ses devoirs.
\(\p2 \% \) du temps consacré aux devoirs est consacré à faire un exposé.
<br>Le pourcentage du temps consacré à l’exposé par rapport à la journée de \jour
est égal à&nbsp;&#58;}

\text{good=\( \coeff[3] \times \p2 \% \)}
\text{bads=\(\p2 \%-\p1 \%\),\( \p2decfx \times \p1 \%\),Cela dépend de la durée de la journée du \jour.}
\text{feedback=La bonne réponse est \( \coeff[3] \times \p2 \% \) puisque \(\p1 \%\) de \( \p2 \% \) se calcule en faisant \( \p1dec \times \p2 \%\) et que \( \p1dec=\coeff[3]\)}
