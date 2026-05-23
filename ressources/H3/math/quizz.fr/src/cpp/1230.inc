\title{Question 1230 Coordonnées dans l'espace}
\keywords{mental_calculation,cube,coordinates,3_shape,spatial_skill}
\text{coordA=0,0,0}
\text{coordB=0,1,0}
\text{coordD=1,0,0}
\text{coordE=0,0,1}
\text{coordC=1,1,0}
\text{coordF=0,1,1}
\text{coordG=1,1,1}
\text{coordH=1,0,1}
%%%%%%%
axes du repère
\text{AD1=-1,0,0}
\text{AD2=1.5,0,0}
\text{AB1=0,-1,0}
\text{AB2=0,1.5,0}
\text{AE1=0,0,-1}
\text{AE2=0,0,1.5}

%%%%% coord pour représent en perspective
\integer{k1=100}
\integer{k2=-30}
\integer{k3=-40}

\text{coordAbis=simplify(\coordA[1]*\k1+\coordA[2]*\k2),simplify(\coordA[3]*\k1+\coordA[2]*\k3)}
\text{coordBbis=simplify(\coordB[1]*\k1+\coordB[2]*\k2),simplify(\coordB[3]*\k1+\coordB[2]*\k3)}
\text{coordDbis=simplify(\coordD[1]*\k1+\coordD[2]*\k2),simplify(\coordD[3]*\k1+\coordD[2]*\k3)}
\text{coordEbis=simplify(\coordE[1]*\k1+\coordE[2]*\k2),simplify(\coordE[3]*\k1+\coordE[2]*\k3)}
\text{coordCbis=simplify(\coordC[1]*\k1+\coordC[2]*\k2),simplify(\coordC[3]*\k1+\coordC[2]*\k3)}
\text{coordFbis=simplify(\coordF[1]*\k1+\coordF[2]*\k2),simplify(\coordF[3]*\k1+\coordF[2]*\k3)}
\text{coordGbis=simplify(\coordG[1]*\k1+\coordG[2]*\k2),simplify(\coordG[3]*\k1+\coordG[2]*\k3)}
\text{coordHbis=simplify(\coordH[1]*\k1+\coordH[2]*\k2),simplify(\coordH[3]*\k1+\coordH[2]*\k3)}
%%%% axes du repère
\text{coordAD1=simplify(\AD1[1]*\k1+\AD1[2]*\k2),simplify(\AD1[3]*\k1+\AD1[2]*\k3)}
\text{coordAD2=simplify(\AD2[1]*\k1+\AD2[2]*\k2),simplify(\AD2[3]*\k1+\AD2[2]*\k3)}
\text{coordAB1=simplify(\AB1[1]*\k1+\AB1[2]*\k2),simplify(\AB1[3]*\k1+\AB1[2]*\k3)}
\text{coordAB2=simplify(\AB2[1]*\k1+\AB2[2]*\k2),simplify(\AB2[3]*\k1+\AB2[2]*\k3)}
\text{coordAE1=simplify(\AE1[1]*\k1+\AE1[2]*\k2),simplify(\AE1[3]*\k1+\AE1[2]*\k3)}
\text{coordAE2=simplify(\AE2[1]*\k1+\AE2[2]*\k2),simplify(\AE2[3]*\k1+\AE2[2]*\k3)}

\text{quest=E,F,G,H;G,H,D,C;A,B,C,D;F,G,C,B;E,F,B,A;A,D,C,B}
\text{quest=randomrow(\quest)}
%%%%%%%
\text{coordgraph=\quest}
\text{coordgraph=wims(replace internal A by \coordAbis in \coordgraph)}
\text{coordgraph=wims(replace internal B by \coordBbis in \coordgraph)}
\text{coordgraph=wims(replace internal C by \coordCbis in \coordgraph)}
\text{coordgraph=wims(replace internal D by \coordDbis in \coordgraph)}
\text{coordgraph=wims(replace internal E by \coordEbis in \coordgraph)}
\text{coordgraph=wims(replace internal F by \coordFbis in \coordgraph)}
\text{coordgraph=wims(replace internal G by \coordGbis in \coordgraph)}
\text{coordgraph=wims(replace internal H by \coordHbis in \coordgraph)}

%%%%%%
\text{face=wims(replace internal , by in \quest)}
\text{quest=wims(replace internal A by \coordA in \quest)}
\text{quest=wims(replace internal B by \coordB in \quest)}
\text{quest=wims(replace internal C by \coordC in \quest)}
\text{quest=wims(replace internal D by \coordD in \quest)}
\text{quest=wims(replace internal E by \coordE in \quest)}
\text{quest=wims(replace internal F by \coordF in \quest)}
\text{quest=wims(replace internal G by \coordG in \quest)}
\text{quest=wims(replace internal H by \coordH in \quest)}

\text{coordM=simplify((\quest[1]+\quest[7])/2),simplify((\quest[2]+\quest[8])/2),simplify((\quest[3]+\quest[9])/2)}

\text{coordMbis=simplify(\coordM[1]*\k1+\coordM[2]*\k2),simplify(\coordM[3]*\k1+\coordM[2]*\k3)}

%%% décalage des text 15
\integer{k0=15}
\text{pave=draw(300,300
xrange -100,230
yrange -120,180
vecteurs du repère
linewidth 2
arrow \coordAbis[1],\coordAbis[2],\coordBbis[1],\coordBbis[2],10,black
arrow \coordAbis[1],\coordAbis[2],\coordDbis[1],\coordDbis[2],10,black
arrow \coordAbis[1],\coordAbis[2],\coordEbis[1],\coordEbis[2],10,black
linewidth 1
axes du repere
arrow \coordAD1[1],\coordAD1[2],\coordAD2[1],\coordAD2[2],10,black
arrow \coordAB1[1],\coordAB1[2],\coordAB2[1],\coordAB2[2],10,black
arrow \coordAE1[1],\coordAE1[2],\coordAE2[1],\coordAE2[2],10,black
polygone ABCD
polygon black,\coordAbis[1],\coordAbis[2],\coordBbis[1],\coordBbis[2],\coordCbis[1],\coordCbis[2],\coordDbis[1],\coordDbis[2]
polygone EFGH
polygon black,\coordEbis[1],\coordEbis[2],\coordFbis[1],\coordFbis[2],\coordGbis[1],\coordGbis[2],\coordHbis[1],\coordHbis[2]
Arete FB, CG et HD
segments black,\coordFbis[1],\coordFbis[2],\coordBbis[1],\coordBbis[2],\coordCbis[1],\coordCbis[2],\coordGbis[1],\coordGbis[2],\coordHbis[1],\coordHbis[2],\coordDbis[1],\coordDbis[2],
%%%%%
text black,simplify(\coordAbis[1]-\k0),simplify(\coordAbis[2]+\k0),medium,A
text black,simplify(\coordBbis[1]-\k0),simplify(\coordBbis[2]+\k0),medium,B
text black,\coordCbis[1],\coordCbis[2],medium,C
text black,\coordDbis[1],\coordDbis[2],medium,D
text black,simplify(\coordEbis[1]-\k0),simplify(\coordEbis[2]+\k0),medium,E
text black,simplify(\coordFbis[1]-\k0),simplify(\coordFbis[2]+\k0),medium,F
text black,simplify(\coordGbis[1]-\k0),simplify(\coordGbis[2]+\k0),medium,G
text black,simplify(\coordHbis[1]-\k0),simplify(\coordHbis[2]+\k0),medium,H

diagonales
dsegment \coordgraph[1],\coordgraph[2],\coordgraph[5],\coordgraph[6],red
dsegment \coordgraph[3],\coordgraph[4],\coordgraph[7],\coordgraph[8],red
centre de la face
fcircle \coordMbis[1],\coordMbis[2],10,red

)}


\text{enonce=<img src="\pave" alt=""><br>\(ABCDEFGH\) est un cube. Coordonnées du centre de la face \((\face)\) dans le repère \(\left(A,\overrightarrow{AD}, \overrightarrow{AB}, \overrightarrow{AE}\right)\)<br>&#40;}
\text{enonceb=&#59;}
\text{enoncec=&#59;}
\text{enonced= &#41;}
\rational{rep=\coordM[1]}
\rational{repb=\coordM[2]}
\rational{repc=\coordM[3]}

\text{feedback=}
