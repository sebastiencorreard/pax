\title{Question 0813 Aire d'un triangle}
\keywords{mental_calculation,2_shape,triangles,altitude,area}
\text{listelong=shuffle(5,6,7,8,9,10)}
\integer{AH=\listelong[1]}
\integer{CB=\listelong[2]}
\integer{BH=2/3*\CB}
\integer{AB=sqrt(\AH^2+\BH^2)}
\text{codefig8=xrange 0,120
yrange 0,90
linewidth 2
ABCAH
polygon black,10,10,100,10,67.8114,66.33,10,10,77.8462,48.7692
text black,4,8,large,A
text black,102,8,large,B
text black,82,55,large,H
text black,67,75,large,C
arrow 45,5,10,5,10,black
arrow 70,5,100,5,10,black
text black,47,8,large,\AB cm
arrow 93.7782,49.2959,80.5068,72.5209,10,black
arrow 103.1632,32.8722,113.3704,16.0095,10,black
text black,90,48,large,\CB cm
text black,43,29,large,AH= \AH cm
polygon black,77.8462,48.7692,74.8942,53.9351,67.6369,49.788,70.5888,44.6222,77.8462,48.7692
}
\text{fig8=draw(240,180
\codefig8)}
\text{fig8=<div class="wimscenter"><img src="\fig8" alt=""></div>}
\text{enonce=\fig8 Calcule l'aire du triangle \(ABC\)<br> Réponse &#58; }
\text{enonceb=\( cm^2 \).}
\real{rep=\AH*\CB/2}
\text{figsol8=draw(300,280
\codefig8
polyline red,-130,-110,0,110,0,-110
)}
\text{feedback= L'aire est égale à \(\frac{CB \times AH}{2}\) d'après la formule \(base \times hauteur \div 2\). }
