\title{Question 0824 Réduction de fraction}
\keywords{mental_calculation,primes,fraction}
\text{lterme=shuffle(2,3,5)}
\text{coeff=random(4,9,6)}
%% frac= a/b, coeff
\integer{a=\coeff*\lterme[1]}
\integer{b=\coeff*\lterme[2]}
\text{rep=simplify(\a/\b)}
\text{enonce= Simplifie au maximum la fraction &#58; \(\frac{\a}{\b}\)<br>}
\text{enonceb=<div class="wims_instruction">Seule l'écriture fractionnaire sera acceptée.</div>}
\text{feedback=\(\frac{\a}{\b}=\frac{\coeff \times \lterme[1]}{\coeff \times \lterme[2]}=\frac{\lterme[1]}{\lterme[2]}\)
<br> \(\lterme[1]\) est premier avec \(\lterme[2]\).}
%%%%%% attention condition pour tester même texte que rep
%%%%%%%%%%%%%%%%%%%%%%%% ANSTYPE 60 pour condition : %answer{}{\reponse}{type=text}
%%%%%%%%%%%%%%%%%%%%%%%%       %condition{}{\reponse issametext \rep}
