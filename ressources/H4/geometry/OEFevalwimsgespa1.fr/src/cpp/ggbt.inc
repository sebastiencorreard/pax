\text{listpoint=A,B,C,D,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W}
\text{lp_fix=}
\for{i in \listpoint}{\text{t=SetFixed[\i,true]}
\text{tt=\t
SetPointSize(\i,3);}
\text{lp_fix=wims(append line \tt to \lp_fix)}
}

\matrix{cg=-3,-3,0
0,0,5
3,-3,0 
0,sqrt(18),0}

\matrix{coord_1323=1/3*(\cg[3;1])+2/3*(\cg[1;1]),1/3*(\cg[3;2])+2/3*(\cg[1;2]),1/3*(\cg[3;3])+2/3*(\cg[1;3])
2/3*(\cg[3;1])+1/3*(\cg[1;1]),2/3*(\cg[3;2])+1/3*(\cg[1;2]),2/3*(\cg[3;3])+1/3*(\cg[1;3])
1/3*(\cg[4;1])+2/3*(\cg[1;1]),1/3*(\cg[4;2])+2/3*(\cg[1;2]),1/3*(\cg[4;3])+2/3*(\cg[1;3])
2/3*(\cg[4;1])+1/3*(\cg[1;1]),2/3*(\cg[4;2])+1/3*(\cg[1;2]),2/3*(\cg[4;3])+1/3*(\cg[1;3])
1/3*(\cg[2;1])+2/3*(\cg[1;1]),1/3*(\cg[2;2])+2/3*(\cg[1;2]),1/3*(\cg[2;3])+2/3*(\cg[1;3])
2/3*(\cg[2;1])+1/3*(\cg[1;1]),2/3*(\cg[2;2])+1/3*(\cg[1;2]),2/3*(\cg[2;3])+1/3*(\cg[1;3])
1/3*(\cg[3;1])+2/3*(\cg[2;1]),1/3*(\cg[3;2])+2/3*(\cg[2;2]),1/3*(\cg[3;3])+2/3*(\cg[2;3])
2/3*(\cg[3;1])+1/3*(\cg[2;1]),2/3*(\cg[3;2])+1/3*(\cg[2;2]),2/3*(\cg[3;3])+1/3*(\cg[2;3])
1/3*(\cg[4;1])+2/3*(\cg[2;1]),1/3*(\cg[4;2])+2/3*(\cg[2;2]),1/3*(\cg[4;3])+2/3*(\cg[2;3])
2/3*(\cg[4;1])+1/3*(\cg[2;1]),2/3*(\cg[4;2])+1/3*(\cg[2;2]),2/3*(\cg[4;3])+1/3*(\cg[2;3])
2/3*(\cg[4;1])+1/3*(\cg[3;1]),2/3*(\cg[4;2])+1/3*(\cg[3;2]),2/3*(\cg[4;3])+1/3*(\cg[3;3])
1/3*(\cg[4;1])+2/3*(\cg[3;1]),1/3*(\cg[4;2])+2/3*(\cg[3;2]),1/3*(\cg[4;3])+2/3*(\cg[3;3])}

\matrix{coordg=\cg
\coord_1323}


\text{lp_coord}
\for{i=1 to 8}{\text{jj=\listpoint[\i]=(\coordg[\i;])}
\text{lp_coord=wims(append line \jj to \lp_coord)}}

\rational{h1=1/3}
\rational{h2=2/3}

\text{vectt=\vectt
I=Dilate(C,\h1,A)
J=Dilate(C,\h2,A)
K=Dilate(D,\h1,A)
L=Dilate(D,\h2,A)
M=Dilate(B,\h1,A)
N=Dilate(B,\h2,A)
O=Dilate(C,\h1,B)
P=Dilate(C,\h2,B)
Q=Dilate(D,\h1,B)
R=Dilate(D,\h2,B)
S=Dilate(C,\h1,D)
T=Dilate(C,\h2,D)}

\text{list3=I,J,K,L,M,N,O,P,Q,R,S,T}
\text{lp_col=}
\for{i in \list3}{\text{t=SetColor[\i,darkgreen]}
\text{lp_col=wims(append line \t to \lp_col)}}

\text{fig_ggb=enable3d=true
SetVisibleInView(xAxis,-1,false);
SetVisibleInView(yAxis,-1,false);
SetVisibleInView(zAxis,-1,false);
\lp_outil
\lp_coord
\lp_mil
a=Segment(A,B);
b=Segment(A,C);
c=Segment(A,D);
d=Segment(B,C);
e=Segment(B,D);
f=Segment(C,D);
\vectt
\lp_fix
\lp_lab
\lp_col
\lp_enon
SetPerspective("T");
}
