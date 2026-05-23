\matrix{question=0,1,3,1,4,-2,2,2,3;0,1,3,1,4,-2,2,2,2;0,2,3,1,4,-2,2,2,3;0,2,3,1,4,-2,2,2,1;0,2,3,1,5,-2,2,2,3;0,1,3,1,4,-2,2,2,2;0,2,3,1,5,-2,2,2,1;0,1,3,1,4,-2,2,2,3}
\text{question=randomrow(\question)}
\integer{x0=\question[1]}
\integer{y0=\question[2]}
\integer{z0=\question[3]}
\integer{x1=\question[4]}
\integer{y1=\question[5]}
\integer{z1=\question[6]}
\integer{x2=\question[7]}
\integer{y2=\question[8]}
\integer{z2=\question[9]}
%%%%% eviter que la tangente passe par le point (x1,x2)
\integer{z2=evalue(\y2-\y1)=\z2?1:\z2}
%%%%%tangente
\function{tang2=\z2(x-\x2)+\y2}

%%%%Intrep Hermite

\function{d0=simplify(((x-(\x1))*(x-(\x2))/((\x0-(\x1))*(\x0-(\x2))))^2)}
\function{d1=simplify(((x-(\x0))*(x-(\x2))/((\x1-(\x0))*(\x1-(\x2))))^2)}
\function{d2=simplify(((x-(\x0))*(x-(\x1))/((\x2-(\x0))*(\x2-(\x1))))^2)}
%%%%
\function{dd0=simplify(diff(\d0,x))}
\real{dd0=evalue(\dd0,x=\x0)}
\function{dd1=simplify(diff(\d1,x))}
\real{dd1=evalue(\dd1,x=\x1)}
\function{dd2=simplify(diff(\d2,x))}
\real{dd2=evalue(\dd2,x=\x2)}

\function{f=simplify(\d0*(\y0+(x-\x0)*(\z0-\dd0*\y0)) + (\d1)*(\y1+(x-\x1)*(\z1-\dd1*\y1)) +(\d2)*(\y2+(x-\x2)*(\z2-\dd2*\y2)))}

%%%%% affichage (Cf) sur dessin
\real{xl=solve(\f=\y0+1,x=0.1..0.9)}
\real{yl=\y0+1}

\text{repere=xrange -0.8,3.2
yrange -0.8,5.2
linewidth 1
parallel 0,0,3,0,0,1,6,grey
parallel 0,0,0,5,1,0,6,grey
linewidth 2
plot black,\f
plot black,\tang2
fpoly white,-0.8,-0.8,-0.8,5.2,-0.1,5.2,-0.1,-0.8
linewidth 1
parallel -0.1,1,0.1,1,0,1,4,black
parallel 1,-0.1,1,0.1,1,0,2,black
arrow -1,0,3,0,15,black
arrow 0,-1,0,5,15,black
text black,-0.3,-0.1,medium,0 
text black,-0.3,1.1,medium,1 
text black,-0.3,2.1,medium,2 
text black,-0.3,3.1,medium,3 
text black,-0.3,4.1,medium,4 
text black,1,-0.3,medium,1 
text black,2,-0.3,medium,2 
text black,3,-0.3,medium,3

text black,\xl,\yl,medium, (Cf)
}
\text{intro=À partir du graphique ci-dessous qui représente une fonction f et une tangente à cette représentation &#58;}
