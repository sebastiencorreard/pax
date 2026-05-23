\title{Question 0711 Cubes }
\keywords{cube,mental_calculation,volume,multiplication}
\text{cas=5,4,3
3,3,3
3,3,4
3,5,2
2,5,6
2,5,5
}

\text{coeff=shuffle(randomrow(\cas))}
\integer{d1=\coeff[1]}
\integer{d2=\coeff[2]}
\integer{d3=\coeff[3]}
\integer{ymax=1.8*max(max(\coeff[1],\coeff[2]),\coeff[3])}
\integer{d1b=\d1+1}
\integer{d2b=\d2+1}
\integer{d3b=\d3+1}

\real{p1x=\d3*0.5}
\real{p1y=\d2+\d3*0.5}

\real{p2x=\d1+\d3*0.5}
\real{p2y=\d3*0.5}

\text{fig711=draw(300,300
xrange -1,\ymax
yrange -1,\ymax
parallel 0,0,0,\d2,1,0,\d1b,black
parallel 0,0,\d1,0,0,1,\d2b,black
parallel 0,\d2,\d1,\d2,0.5,0.5,\d3b,black
parallel 0,\d2,\p1x,\p1y,1,0,\d1b,black
parallel \d1,0,\d1,\d2,0.5,0.5,\d3b,black
parallel \d1,0,\p2x,\p2y,0,1,\d2b,black
)}

\text{fig711=<div class="wimscenter"><img src="\fig711" alt="Pavé droit"></div>}
\text{enonce=\fig711 Combien y a-t-il de petits cubes dans ce pavé droit &#63;   }
\text{enonceb= }
\real{rep0711=\d1*\d2*\d3}
\real{rep=\rep0711}
\text{feedback=On peut faire cela par multiplication : \(\d1 \times \d2 \times \d3 = \rep0711\). }
