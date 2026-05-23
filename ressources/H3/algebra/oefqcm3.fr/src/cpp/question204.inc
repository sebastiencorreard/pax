\title{Question 204 Théorème de Thalès (num.)}
\keywords{quizz,thales}
\observation{Question du sujet zéro sujet-zero-dnb-serie-generale-a-mathematiques.pdf du DNB publié sur éduscol en décembre 2025  }
%%%BM%%%%
AC,BC,DE
\integer{bc=randomitem(2,2,3,3,4)}
\integer{k=randomitem(2,5,2,3)}
\integer{ac=\k*\bc}
\integer{de=randomitem(7,13,9,7)}
\text{d=\ac,\bc,\de}


\text{dessin=canvasdraw(300,300
range -10,100,-10,40
segment 0,0,80,0,black
segment 0,0,64,26,black
segment 25,10,30,0,black
segment 64,26,80,0,black
text black,30,-3,medium,B
text black,24,13,medium,C
text black,-5,2,medium,A

text black,64,28,medium,D
text black,85,0,medium,E
text black,5,7,medium,\d[1] cm
text black,30,6,medium,\d[2] cm
text black,80,14,medium,\d[3] cm
)}

\integer{size=5}

\text{enonce= Sur la figure ci-contre&#44; dans le triangle \(ADE\) les droites \((DE)\) et \((CB)\) sont parallèles.
\dessin 
Déterminer la longueur <span style="white-space:nowrap;">\(AD).</span>}
\text{enonceb= cm}

\integer{rep=\d[1]*\d[3]/\d[2]}
\text{typerep=numeric}
\text{feedalea=randomitem(\(AD =\d[1] \times \d[3]\div \d[2]\),\(AD =\frac{\d[1] \times \d[3]}{\d[2]}\))}
\text{feedback=La bonne réponse est <b>\rep cm</b>.<ul class="wims_nopuce"><li>Par le théorème de Thalès on a \(\frac{AC}{AD}=\frac{BC}{DE}\)</li>
<li>C'est à dire \(\frac{\d[1]}{AD}=\frac{\d[2]}{\d[3]}\)</li>
<li>Ainsi \feedalea \({}=\k \times \d[3]\)</li>
<li>\(AD=\rep\) cm}
