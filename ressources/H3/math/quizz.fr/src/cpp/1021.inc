\title{Question 1021 Théorème de Pythagore}
\keywords{mental_calculation,proportionality,velocity}
%%%%%%%%%%% question 6 %%%%%%%%%%%

\integer{b=randitem(3,4,5)}
\integer{a=\b=3 ? randitem(2,3,5) : randitem(2,4,5)}
\integer{temp61=\b^2+\a^2}
\text{temp6=sqrt(\temp61)}
\text{rep=\temp6}

\text{fig6=draw(230,115
xrange -60,60
yrange -55,55
triangle -15,40,30,40,30,-37,black
segment 20,40,20,30,black
segment 20,30,30,30,black
text black,-20,45,medium,A
text black,35,45,medium,C
text black,35,-42,medium,B
text black,35,1,medium,\a cm
text black,5,55,medium,\b cm)}

\text{fig6=<img src="\fig6" alt="">}

\text{enonce=<table><tr><td>\fig6 </td><td> La valeur exacte de AB est : <br>AB =  }
\text{enonceb= \(cm\)</td></tr></table>}
\text{feedback=Utiliser le théorème de Pythagore : \(AB=\sqrt{AC^2+BC^2}=\sqrt{\a^2+\b^2}=\sqrt{\temp61}\)}
