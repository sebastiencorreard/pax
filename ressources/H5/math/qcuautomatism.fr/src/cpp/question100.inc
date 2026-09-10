\title{Question 100 T Calculs avec les puissances}
\keywords{quizz,power,calculation,multiplication,division}
\observation{Question du sujet zéro sujet-techno-1_0.pdf publié sur EDUSCOL en juin 2025 }
\text{enonce=La seule égalité vraie est&nbsp;&#58;}
%%% une question par ligne, premier item vrai, second faux
%%%% proposition 1
\integer{a=randomitem(2,3,5)}
\integer{b=\a+randomitem(2,3)}
\integer{c=-\a-\b}
\integer{cbad=\b-\a}

\text{questions=\(\frac{10^{-\a}}{10^\b}=10^{\c}\),\(\frac{10^{-\a}}{10^\b}=10^{\cbad}\)}
\text{feedback=La bonne réponse est \(\frac{10^{-\a}}{10^{\b}}=10^{\c}\) puisque \(\frac{10^{-\a}}{10^{\b}}=10^{-\a-\b}\)}
%%%% proposition 2
\text{temp=shuffle(2,3,5)}
\integer{a=\temp[1]}
\integer{b=\temp[2]}
\integer{c=\temp[3]}
\integer{d=-\b*\c}
\integer{dbad=\c-\b}

\matrix{questions=\questions
\( (\a^{-\b})^\c=\a^{\d} \),\( (\a^{-\b})^\c=\a^{\dbad} \)}
\text{feedback=\feedback,La bonne réponse est \( (\a^{-\b})^{\c}=\a^{\d} \) puisque \( (\a^{-\b})^\c=\a^{-\b \times \c} \)}
%%%% proposition 3
\text{temp=shuffle(2,3,5)}
\integer{a=\temp[1]*10}
\integer{b=\temp[2]}
\integer{c=1-\b}
\integer{cbad=\b-1}
\matrix{questions=\questions
\(\a \times \frac{1}{\a^{\b}}=\a^{\c}\),\(\a \times \frac{1}{\a^{\b}}=\a^{\cbad}\) }
\text{feedback=\feedback,La bonne réponse est \(\a \times \frac{1}{\a^{\b}}=\a^{\c}\) puisque \(\a \times \frac{1}{\a^{\b}}=\a \times \a^{-\b}=\a^{1-\b}\)}
%%%% proposition 4

\integer{a=randomitem(8,9,10,11)}
\integer{b=randomitem(2,3,4)}
\integer{c=randomitem(5,6,7)}
\integer{d=\a*\b}
\integer{cbad=2*\c}
\matrix{questions=\questions
\( \b^{-\c} \times \a^{-\c}=\d^{-\c}\),\( \b^{-\c} \times \a^{-\c}=\d^{-\cbad}\) }
\text{feedback=\feedback,La bonne réponse est \( \b^{-\c} \times \a^{-\c}=\d^{-\c}\) puisque \( \b^{-\c} \times \a^{-\c}=(\a \times \b)^{-\c}\)}

%%% choix du bon 
\integer{k=randomitem(1,2,3,4)}
%%%%
\text{good=\questions[\k;1]}
\text{bads=}
\for{k100=1 to 4}
  {\if{\k100!=\k}{
  \text{bads=\bads==?\questions[\k100;2]:\bads,\questions[\k100;2]}}
  }

\text{feedback=\feedback[\k]}
