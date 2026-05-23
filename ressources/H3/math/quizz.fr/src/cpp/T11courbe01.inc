\integer{alpha=randint(-2..2)}
\integer{beta=randint(-2..1)}
\integer{a=\b=3 ? randitem(2,3,5) : randitem(2,4,5)}
\function{f01=maxima(0.0081*(x-\alpha)^4-0.0696*(x-\alpha)^3-0.22*(x-\alpha)^2+1.4601*(x-\alpha)+1.8245+\beta)}
\integer{xmin=-6+\alpha}
\integer{xmax=7+\alpha}
\integer{ymin=-4+\beta}
\integer{ymax=5+\beta}
\text{taille=300,210}
\text{courbe01=draw(\taille
xrange \xmin,\xmax
yrange \ymin,\ymax

linewidth 2
parallel \xmin,\ymin,\xmin,\ymax,1,0,14,grey
parallel \xmin,\ymin,\xmax,\ymin,0,1,11,grey
vline 0,0,black
hline 0,0,black
segment -0.2,1,0.2,1,black
segment -0.2,5,0.2,5,black
text black,-0.4,5,medium,5
text black,-1,-5,medium,-5
segment -0.2,-5,0.2,-5,black
segment 1,-0.2,1,0.2,black
segment 5,-0.2,5,0.2,black
text black,4.7,-0.2,medium,5
text black,-5.5,-0.2,medium,-5
segment -5,-0.2,-5,0.2,black
text black,0.7,-0.1,medium,I
text black,-0.4,1,medium,J
text black,-0.3,-0.1,medium,O
plot blue,\f01)}
\matrix{valeurs=-2+\beta,-3+\alpha,6.1+\alpha
-1+\beta,-4+\alpha,-1.8+\alpha,5.5+\alpha
0+\beta,-4.4+\alpha,-1.1+\alpha,5+\alpha
1+\beta,-4.6+\alpha,-0.5+\alpha,4.4+\alpha
2+\beta,-4.8+\alpha,0.1+\alpha,3.8+\alpha
3+\beta,-5+\alpha,1,3+\alpha}
\matrix{valeursp=-2+\beta,-3+\alpha,6.08+\alpha
-1+\beta,-4+\alpha,-1.78+\alpha,5.52+\alpha
0+\beta,-4.37+\alpha,-1.13+\alpha,5+\alpha
1+\beta,-4.64+\alpha,-0.53+\alpha,4.45+\alpha
2+\beta,-4.85+\alpha,0.12+\alpha,3.85+\alpha
3+\beta,-5.04+\alpha,1,3+\alpha}
