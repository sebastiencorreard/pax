\integer{M5=max(\M/\l,\n)}
\integer{m4=-0.1*\n}


\integer{p=floor(\M*0.0018)*50+50}
\integer{p1=floor(\M1*0.002)*25+25}
\integer{p5=ceil(\M5*0.005)*5}
\real{d1=0.5*\p1}
#if defined TARGET_compevol
\integer{p2=ceil(\n*0.005)*5}
\real{d3=0.15*\p5}
#endif
#if defined TARGET_comployer1
\integer{p2=ceil(\n*0.01)*10}
\real{d3=0.15*\p5}
#endif

\real{d4=0.4*\p2}
\real{d5=0.2*\p5}

\text{X1 = text black, 0,-1,large, 0}
\text{U1 = text black, -1, \d1, large,0}
\text{U2 = text black, -1,2,large,0 %}
\text{U3 = text red, -1,\d3,large,0}
\text{U4 = text blue, -1,0.2*\p2,large,0}
\text{U5 = text blue, 9.1,0.2*\p5,large,0}

\for{i=1 to 10}{
   \integer{j=\p*\i}
   \integer{j2=\p1*\i}
   \real{j3=\j/\l}
   \integer{j4=\p2*\i}
   \integer{j5=\p5*\i}

   \text{X1 = \X1;text black, \i,-1,large, \i}  
   \text{U1 = \U1;text black, -1,\j+\d1, large,\j}
   \text{U2 = \U2;text black, -1.5, \j2+5, large,\j2 %}
   \text{U3 = \U3;text red, -1, \j3+\d3,large,\j}
   \text{U4 = \U4;text blue, -1,\j4+\d4,large,\j4}
   \text{U5 = \U5;text blue, 9.1,\j5+\d5,large,\j5}
   }
#if defined TARGET_comployer1
\for{i=1 to 9}{
   \integer{wi=\L[\i+1]/\l}
   \text{P5=\P5,\i,\wi}
   }

\text{Analyse=Les loyers ont augmenté moins vite que les prix,Les loyers ont augmenté environ comme les prix,Les loyers ont augmenté plus vite que les prix}
\integer{rA=2+\s}

#endif
\text{graph= xrange -2,11
yrange -0.1*\M,\M
linewidth 3
arrow 0,0,11,0,10,black
arrow 0,0,0,\M,10,black
linewidth 4
\X1
\U1
}
\text{graph1=\graph

\P1
\P2
}
\text{graph2= xrange -2,11
yrange -0.1*\M1,\M1
linewidth 3
arrow 0,0,11,0,10,black
arrow 0,0,0,\M1,10,black
linewidth 4
\X1
\U2
\P3
\P4
}
\text{graph3=\graph
\P1
}

\text{graph4= xrange -2,11
yrange \m4,\n
linewidth 3
arrow 0,0,11,0,10,black
arrow 0,0,0,\n,10,black
linewidth 4
\X1
\U4
\P2
}

\text{graph5= xrange -2,10
yrange -0.1*\M5,\M5
linewidth 3

arrow 0,0,10,0,10,black
arrow 9,0,9,\M5,10,blue
arrow 0,0,0,\M5,10,red
linewidth 4

\X1
\U3
\U5

\P2
\P5
}

#if defined TARGET_compevol
\text{X6 = text red, -10,-1,large, 0}
\text{U6 = text blue, -30,0.2*\p2,large, 0}
\text{P6=points black, \a0,\b0}

\for{i=1 to 10}{
   \integer{j=\p*\i}
   \integer{j3=5*\i}
   \text{X6 = \X6;text red, \j-15, -1, large,\j}
   \text{U6 = \U6;text blue, -30,\j3+0.2*\p2,large,\j3}
   \text{P6=\P6,\L[\i],\V[\i]}
   }

\text{graph6= xrange -0.1*\M,\M
yrange \m4,\n
linewidth 3
arrow 0,0,\M,0,10,black
arrow 0,0,0,\n,10,black

linewidth 4
\X6
\U6
\P6
}
#endif
