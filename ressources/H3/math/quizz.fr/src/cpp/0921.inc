\title{Question 0921 Vitesse&#44; temps et distance}
\keywords{mental_calculation,pbsolving,proportionality,velocity,time,distance}
\integer{d6=randint(3..9)*10}
\integer{d2=\d6/2}
\integer{t=60}
\integer{t2=\t/3}
\integer{t3=\t-5}%%%% alignement de t sur le graphique
\integer{nx=100/\t2-1}
\integer{ny=100/\d2-1}
\text{B=100,simplify(\d6/\t*100)}
\text{B=\B[2]>100?simplify(100*\t/\d6),100:\B}
\text{fig6=draw(300,300
xrange -20,110
yrange -20,120
arrow 0,0,0,100,10,black
arrow 0,0,100,0,10,black
parallel \t2,0,\t2,100,\t2,0,\nx,grey
parallel 0,\d2,100,\d2,0,\d2,\ny,grey
segment 0,0,\B[1],\B[2],black
dsegment 0,\d6,\t,\d6,black
dsegment \t,0,\t,\d6,black
text black,-10,\d6,large,\d6
text black,\t3,-6,large,\t
text black,-10,110,large,Distance en km
text black,65,-6,large,Temps en min
)}
\text{fig6=<div class="wimscenter"><img src="\fig6" alt=""></div>}
\integer{h6=randint(4,5,7)}
\text{enonce=\fig6 À vitesse constante, le graphique ci-dessous donne la distance parcourue en fonction du temps. Quelle est la distance parcourue en \(\h6\) heures?}
\text{enonceb= \( km \).}
\real{rep=\d6*\h6}
\text{feedback=Graphiquement la vitesse est de \(\d6 km\) pour \(60 min\) donc \(\d6 km\) en une heure.
  Il reste à faire la multiplication \(\d6 \times \h6\) pour trouver la réponse.}
