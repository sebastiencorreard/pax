\matrix{donnees=-4,2,-10,-3,-2,0,4,3,0,6,-2,-1
-5,3,-6,-3,-1,0,4,3,0,6,-1,-7
-5,3,-10,-3,-3,0,3,3,0,6,-3,-7
-4,3,-10,-3,-1,0,4,3,0,6,-1,-4
-5,3,-10,-3,-3,0,2,3,0,6,-3,-1
-5,4,-10,-3,-3,0,2,3,0,6,-3,-3
}
\text{valeurs=randomrow(\donnees)}
%%% courbe passant par (x_i;y_i)
\integer{x0=\valeurs[1]}
\integer{y0=\valeurs[2]}
\integer{z0=\valeurs[3]}
\integer{x1=\valeurs[4]}
\integer{y1=\valeurs[5]} %%%% 
\integer{z1=\valeurs[6]}
\integer{x2=\valeurs[7]}
\integer{y2=\valeurs[8]}
\integer{z2=\valeurs[9]}
\integer{x3=\valeurs[10]}
\integer{y3=\valeurs[11]} %%%%%
\integer{z3=\valeurs[12]}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%Interpolation Hermite

\function{d0=(((x-(\x1))*(x-(\x2))*(x-(\x3))/((\x0-(\x1))*(\x0-(\x2))*(\x0-(\x3)))))^2}
\function{d1=(((x-(\x0))*(x-(\x2))*(x-(\x3))/((\x1-(\x0))*(\x1-(\x2))*(\x1-(\x3)))))^2}
\function{d2=(((x-(\x0))*(x-(\x1))*(x-(\x3))/((\x2-(\x0))*(\x2-(\x1))*(\x2-(\x3)))))^2}
\function{d3=(((x-(\x0))*(x-(\x1))*(x-(\x2))/((\x3-(\x0))*(\x3-(\x1))*(\x3-(\x2)))))^2}

\function{dd0=(diff(\d0,x))}
\real{dd0=evalue(\dd0,x=\x0)}
\function{dd1=(diff(\d1,x))}
\real{dd1=evalue(\dd1,x=\x1)}
\function{dd2=(diff(\d2,x))}
\real{dd2=evalue(\dd2,x=\x2)}
\function{dd3=(diff(\d3,x))}
\real{dd3=evalue(\dd3,x=\x3)}
\function{f02=(\d0*(\y0+(x-(\x0))*(\z0-\dd0*\y0)) + (\d1)*(\y1+(x-(\x1))*(\z1-\dd1*\y1)) +(\d2)*(\y2+(x-(\x2))*(\z2-\dd2*\y2))+ (\d3)*(\y3+(x-(\x3))*(\z3-\dd3*\y3)) )}
%%%%%%
\integer{xmin=-6}
\integer{xmax=8}
\integer{ymin=-4}
\integer{ymax=5}
\text{taille=320,210}
\text{courbe02=draw(\taille
xrange \xmin,\xmax
yrange \ymin,\ymax
linewidth 2
  parallel \xmin,\ymin,\xmin,\ymax,1,0,14,grey
  parallel \xmin,\ymin,\xmax,\ymin,0,1,11,grey
vline 0,0,black
hline 0,0,black
segment -0.2,1,0.2,1,black
segment 1,-0.2,1,0.2,black
text black,0.7,-0.1,medium,I
text black,-0.4,1,medium,J
text black,-0.3,-0.1,medium,O
segment -0.2,4,0.2,4,black
text black,-0.4,4,medium,4
text black,-1,-5,medium,-5
segment -0.2,-5,0.2,-5,black
segment 1,-0.2,1,0.2,black
segment 5,-0.2,5,0.2,black
text black,4.7,-0.2,medium,5
text black,-5.5,-0.2,medium,-5
segment -5,-0.2,-5,0.2,black
plot blue,\f02)}
