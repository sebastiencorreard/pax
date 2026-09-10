\title{Question 115 NS Fraction en mots}
\keywords{quizz,fraction}
\observation{Question du sujet zéro sujet-specifique-1_0.pdf publié sur EDUSCOL en juin 2025 }

\text{ope=wims(shuffle moitié,tiers,quart)}
\text{article1=(\ope[1] issametext moitié)? La:Le}
\text{article2=(\ope[2] issametext moitié)? d'une:d'un}
\integer{c1=(\ope[1] issametext moitié)? 2:3}
\integer{c1=(\ope[1] issametext quart)? 4:\c1}
\integer{c2=(\ope[2] issametext moitié)? 2:3}
\integer{c2=(\ope[2] issametext quart)? 4:\c2}

\text{enonce=\article1 \ope[1] \article2 \ope[2] correspond à la fraction&nbsp;&#58; }
\integer{g=\c2*\c1}
\integer{b3=\c1+\c2}

\text{good=\(1/\g\)}
\text{goodtxt=\frac{1}{g}}
\text{bads=\(\c1/\c2\),\(\c2/\c1\),\(1/\b3\)}

\text{feedback=La bonne réponse est <span class="nowrap">\good.</span> <br> En effet le calcul à produire est  <span class="nowrap">\(\frac{1}{\c1} \times \frac{1}{\c2}=\frac{1}{\c1 \times \c2}\).</span>}
