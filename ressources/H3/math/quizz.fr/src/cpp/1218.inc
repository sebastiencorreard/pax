\title{Question 1218 Résoudre graphiquement f'(x)=0}
\keywords{mental_calculation,derivative,equations}
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


\text{repere=xrange -1,3.2
yrange -0.8,5.2
linewidth 2
plot red,\f
linewidth 1
arrow -1,0,3.2,0,15,black
arrow 0,-1,0,5,15,black
text black,0.1,5,medium, y
text black,3,-0.1,medium, x
}

\text{graph=draw(300,300
\repere)}
\function{df=diff(\f,x)}
\text{r=solve(\df,x=-0.8..3.2)}
\integer{r=items(\r)}
\integer{rep=\r}
\text{enonce=<img src="\graph" alt="graph"><br> La fonction \(f\) est représentée ci-dessus. A l'aide de ce graphique, quel est le nombre de solutions de l'équation \(f &#8242;(x) = 0\) &#63;}
\text{enonceb=}
\text{feedback=Cela correspond au nombre de fois où la courbe a une tangente horizontale.}
