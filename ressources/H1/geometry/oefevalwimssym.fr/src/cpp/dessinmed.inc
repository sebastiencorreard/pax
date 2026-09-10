#if defined TARGET_oefutimed5
\text{med1=draw(300,300
xrange -150,150
yrange -150,150
rotate 40
segment 0,-150,0,150,black
segment 5,-80,-5,-80,black
segment 5,80,-5,80,black
segment -48,6,-52,-6,red
segment -52,6,-56,-6,red
segment 48,-6,52,6,red
segment 52,-6,56,6,red
segment -100,5,-100,-5,black
segment 100,5,100,-5,black
segment 0,10,10,10,red
segment 10,10,10,0,red
text black,-110,-5,medium,A
text black,105,-5,medium,B
segment -100,0,100,0,black
text black,10,-85,medium,E
text black,10,95,medium,F
text black,-10,20,medium,M
circle 0,40,10,red
circle 0,-40,10,red
)}
#else
\text{med1=draw(300,300
xrange -150,150
yrange -150,150
rotate 40
segment 0,-150,0,150,black
segment -100,-50,100,-50,black
segment -48,-44,-52,-56,red
segment -52,-44,-56,-56,red
segment 48,-56,52,-44,red
segment 52,-56,56,-44,red
segment -100,-55,-100,-45,black
segment 100,-55,100,-45,black
segment 0,-40,10,-40,red
segment 10,-40,10,-50,red
text black,10,140,medium,(d)
text black,-110,-55,medium,A
text black,105,-55,medium,B
)}
#endif
\text{fig=\med1}
