\title{Question 1219 Abscisse du sommet de la parabole}
\keywords{mental_calculation,functions,coordinates}
\real{x1=randint(1..3)*(-1)-0.5}
\real{x2=\x1+randint(4..6)}
\function{f=(x-\x1)*(x-\x2)}
\real{xs=(\x1+\x2)/2}
\real{ys=evalue(\f,x=\xs)}
\function{f=-1*(\f/(\ys))}
\real{ys=evalue(\f,x=\xs)}
\real{k=0.3}
\real{xsb=\xs-\k}
\real{ysb=\ys-\k}
\real{x1b=\x1+\k}
\real{x2b=\x2-3*\k}
\text{repere=xrange -5,5
yrange -2,2
linewidth 2
plot black,\f
linewidth 1
arrow -5,0,10,0,15,black
arrow 0,-3,0,10,15,black
crosshairsize 5
linewidth 2
crosshairs black,\x1,0,\x2,0,\xs,\ys
text black,\x1b,\k,medium,\x1
text black,\x2b,\k,medium,\x2
text black,\xsb,\ysb,giant,S
}

\text{graph=draw(300,200
\repere)}
\real{rep=(\x1+\x2)/2}
\text{enonce=<img src="\graph" alt="graph"><br> Abscisse du sommet S de cette parabole.<br>Réponse &#58;}
\text{enonceb=}
\text{feedback=C'est la moyenne \(\frac{\x1+\x2}{2}\).}
