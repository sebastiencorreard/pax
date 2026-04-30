
\integer{temoin=2}
\integer{nx=8}
\integer{ny=12}
\text{data_dessin=\data_dessin[1..\nx]}
\text{tem=\data_dessin[1]}
\text{data_dessin=wims(makelist \tem for x=1 to \temoin),\data_dessin}
\text{Data=0:\data_dessin[1]}
\for{j=1 to \nx-1}{
  \text{Data=\Data:\j:\data_dessin[\j+1]}
}
\text{points=wims(replace internal : by , in \Data)}
\text{legende=Évolution de la concentration en \molecule}
\text{label=temps en minutes,Concentration en \molecule en mg/L}
\text{textfleche=injection de glucose}
\text{dessin=xrange -1,\nx
yrange -1,\ny
precision 1
fontfamily bold 15px Ariel
axis
axisnumbering
xlabel \label[1]
ylabel \label[2]
grid 1,1,grey,1,1,2,black
arrow \temoin,\tem+2,\temoin,\tem,10,blue
text blue,\temoin-1,\tem+2,huge,\textfleche
linewidth 3
strokecolor red
linegraph \Data
points black,\points
legend \legende}
\text{dessin=canvasdraw(500,400
\dessin)}
