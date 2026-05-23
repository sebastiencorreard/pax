\title{Question 0828 Théorème de Pythagore}
\keywords{mental_calculation,length,squareroot,triangles,angles}
%%%%%%%%%%% question 6 %%%%%%%%%%%
\integer{b=random(10,9)}
\integer{c=random(2,3,5,6,7,8)}
\integer{temp61=\b^2-\c^2}
\text{temp6=ceil(sqrt(\temp61))=sqrt(\temp61)?simplify(sqrt(\temp61)):sqrt(\temp61)}
\text{rep=\temp6}

\text{fig6=draw(240,200
xrange 0,60
yrange 0,50

triangle 10,20,40,10,48.29,34.87,black
segment 33.61,12.13,35.46,17.68,black
segment 35.46,17.68,41.85,15.55,black

text black,8,20,medium,A
text black,50,37,medium,C
text black,40,8,medium,B
text black,24,33,medium,\b cm 
text black,20,13,medium,\c cm )}

\text{fig6=<img src="\fig6" alt="">}

\text{enonce=\fig6<br> La valeur exacte de BC est &#58;   }
\text{enonceb= \(cm\)}
\text{feedback=Par le théorème de Pythagore \(BC^2=\AC^2-AB^2=\temp61\) }
