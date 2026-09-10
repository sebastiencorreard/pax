\title{Question 209 S Isoler une variable}
\keywords{quizz,literal_calculation,equations}
\observation{Question du sujet zéro sujet-specialite-2_0.pdf publié sur EDUSCOL en juin 2025 }
\text{q=la vitesse \(v\),le rayon \(\R\)}
\integer{cas=randomitem(1,1,2)}
\text{goods=\(v=\sqrt{a R}\),\(R=\frac{v^2}{a}\)}

\text{enonce=Lorsqu’un point mobile suit une trajectoire circulaire de rayon \(R\)&#44; en mètre (m)&#44; son accélération centripète \(a\) (en m/s²) s’exprime en fonction de la vitesse \(v\) (en m/s) de la manière suivante&nbsp;&#58; <div class="wimscenter">\(a=\frac{v^2}{R}\)</div> L’expression permettant&#44; à partir de cette formule&#44; d’exprimer \q[\cas] est&nbsp;&#58; }

\text{good=\goods[\cas]}
\if{\cas=1}{
\text{bad1=\(v=a R^2\)}
\text{bad2=\(v=\sqrt{\frac{a}{R}}\)}
\text{bad3=\(v=\frac{a^2}{R}\)}
}
\if{\cas=2}{
\text{bad1=\(R=a v^2\)}
\text{bad2=\(R=\sqrt{\frac{a}{v}}\)}
\text{bad3=\(R=\frac{a^2}{v}\)}
}
%%%
\text{bads=\bad1,\bad2,\bad3}

\text{feed0=On a \(a=\frac{v^2}{R}\)  \({}\Leftrightarrow a R=v^2\) }
\text{feedend= \({}\Leftrightarrow \sqrt{a R}=v\) <i>puisque \(v\) est positive.</i>, \({}\Leftrightarrow R=\frac{v^2}{a}\)}
\text{feedback=La bonne réponse est \good.  <br>\feed0  \feedend[\cas] }
