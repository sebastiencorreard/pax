\title{Question 1216 Lecture de l'équation réduite }
\keywords{mental_calculation,coordinates,lines,affine_function,line_equation}
%%%% mx+p
\real{m=1/random(1,2,2)*(-1)}
\integer{p=\m=-0.5 ? random(1,2)}
\integer{p=\m=-1 ? random(3,2)}
\function{f=\m*x+\p}
\integer{x0=-\p/\m}
\text{cross=
crosshairs black,0,\p,\x0,0}
\if{\m=-0.5}{
\integer{ym2=\m*(-2)+\p}
\integer{y2=\m*(2)+\p}
\text{crossbis=linewidth 2
crosshairsize 5
crosshairs blue,-2,\ym2,2,\y2}

}
\if{\m=-1}{
\integer{ym1=\m*(-1)+\p}
\integer{y1=\m*(1)+\p}
\integer{y2=\m*(2)+\p}
\text{crossbis=linewidth 2
crosshairsize 5
crosshairs blue,-1,\ym1,1,\y1,2,\y2}
}
\real{temp=0.3}
\real{xnomf=0.5+\temp}
\real{ynomf=\m*\xnomf+\p+\temp}
\text{nomf=text black,\xnomf,\ynomf,giant, (d)}


\text{repere=xrange -3,5.2
yrange -1,3.5
linewidth 2
parallel -3,-1,5.2,-1,0,1,8,grey
parallel -3,-1,-3,3.5,1,0,8,grey
linewidth 1
parallel -3,-1,5.2,-1,0,0.2,40,grey
parallel -3,-1,-3,3.5,0.2,0,45,grey
linewidth 2
\nomf
plot black,\f

linewidth 1
parallel -0.1,1,0.1,1,0,1,4,black
parallel -2,-0.1,-2,0.1,1,0,8,black
segment -3,0,5.2,0,black
segment 0,-1,0,3.5,black
text black,-0.3,-0.1,medium,0
text black,-0.3,1.1,medium,1
text black,-0.3,2.1,medium,2
text black,-0.3,3.1,medium,3
text black,-0.3,4.1,medium,4
text black,1,-0.3,medium,1
text black,2,-0.3,medium,2
text black,3,-0.3,medium,3
text black,4,-0.3,medium,4
text black,5,-0.3,medium,5
text black,-1,-0.3,medium,-1
text black,-2,-0.3,medium,-2


}
\text{img=draw(500,300
\repere
\crossbis
\cross
)}
\text{imgsol=draw(300,300
\repere
linewidth 2
crosshairsize 6
crosshairs blue,0,\p
crosshairs red,\x0,0
)}
\real{rep=\m}
\real{repb=\p}
%%% deux champs de réponse %%%%%%%%%%%%%%%%%%%%%
\text{enonce=<img src="\img" alt="représentation graphique"> <br> Equation réduite de la droite (d).<br>\(y={}\)}
\text{enonceb=\(x +{}\)}
\text{enoncec=<div class="wims_instruction">Complétez par des nombres</div>}
\text{feedback=<img src="\imgsol" alt="représentation graphique"><br>L'ordonnée à l'origine se lit sur le graphique &#58; \p <br><small>C'est la croix bleue</small>.<br> Le coefficient directeur se calcule  \(\m=\frac{\Delta y}{\Delta x}\)}
