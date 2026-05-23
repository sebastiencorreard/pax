\title{Question 1113 Conversion de longueur}
\keywords{mental_calculation,conversion,length}
\text{a=random(11..29)}
\text{unit=random(cm,mm)}
\integer{tempconv=\unit issametext cm ?10000:1000}
\real{rep=\a*\tempconv}
\text{enonce=\(\a\)\unit=}
\text{enonceb= \(\mu m\)}
\text{feedback=On a : 1\unit= \tempconv \(\mu m\) }
