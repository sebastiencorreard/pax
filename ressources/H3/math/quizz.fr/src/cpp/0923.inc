\title{Question 0923 Calcul de l'aire d'une partie d'un rectangle}
\keywords{mental_calculation,multiplication,area,rectangles,fraction}
\integer{L=random(8,10,12,16,20)}
\text{texte1= \L cm}
\text{l=randint(3..min(9,\L))}
\text{texte2= \l cm}
\text{codefig8=xrange -150,150
yrange -140,140
fpoly grey,-130,-110,-130,110,0,110,130,-110
rect -130,-110,130,110,black
segment -65,100,-55,120,black
segment 55,100,65,120,black
rect -130,-110,-110,-90,black
rect -130,110,-110,90,black
rect 130,110,110,90,black
segment 0,110,130,-110,black
text black,-140,130,large,A
text black,140,130,large,B
text black,140,-120,large,C
text black,-140,-120,large,D
text black,0,130,large,E
text black,-40,-110,large,\texte1
arrow 30,-120,130,-120,10,black
arrow -50,-120,-130,-120,10,black
textup black,-149,-20,large,\texte2
arrow -137,-30,-137,-110,10,black
arrow -137,30,-137,110,10,black
}
\text{fig8=draw(300,280
\codefig8)}
\text{fig8=<div class="wimscenter"><img src="\fig8" alt=""></div>}
\text{enonce=\fig8 Quelle est l'aire de la surface grisée ?}
\text{enonceb=\( cm^2 \).}
\real{rep=\l*\L*3/4}
\text{figsol8=draw(300,280
\codefig8
polyline red,-130,-110,0,110,0,-110
)}
\text{feedback= Méthode : par découpage la partie grisée a pour aire les \(\frac{3}{4}\) de l'aire du rectangle. }
