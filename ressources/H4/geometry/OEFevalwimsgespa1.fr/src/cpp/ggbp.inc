\text{listpoint=A,B,C,D,S,I,J,K,L,M,N,O,P}
\text{lp_fix=}
\for{i in \listpoint}{\text{t=SetFixed[\i,true]}
\text{tt=\t
SetPointSize(\i,3);}
\text{lp_fix=wims(append line \tt to \lp_fix)}
}

\text{listcol=U,V,W}
\text{lp_col=}
\for{i in \listcol}{\text{t=SetColor[\i,red]}
\text{lp_col=wims(append line \t to \lp_col)}
}

\integer{po=randint(1..3)}
\integer{ppo=-randint(1..3)}

\matrix{cg=-3+\ppo,-3,0
3+\ppo,-3,0
3+\po,3,0
-3+\po,3,0
0,0,6}

\matrix{coord_milieu=(\cg[1;1]+\cg[2;1])/2,(\cg[1;2]+\cg[2;2])/2,(\cg[1;3]+\cg[2;3])/2
(\cg[3;1]+\cg[4;1])/2,(\cg[3;2]+\cg[4;2])/2,(\cg[3;3]+\cg[4;3])/2
(\cg[1;1]+\cg[4;1])/2,(\cg[1;2]+\cg[4;2])/2,(\cg[1;3]+\cg[4;3])/2
(\cg[3;1]+\cg[2;1])/2,(\cg[3;2]+\cg[2;2])/2,(\cg[3;3]+\cg[2;3])/2
(\cg[1;1]+\cg[5;1])/2,(\cg[1;2]+\cg[5;2])/2,(\cg[1;3]+\cg[5;3])/2
(\cg[5;1]+\cg[2;1])/2,(\cg[5;2]+\cg[2;2])/2,(\cg[5;3]+\cg[2;3])/2
(\cg[3;1]+\cg[5;1])/2,(\cg[3;2]+\cg[5;2])/2,(\cg[3;3]+\cg[5;3])/2
(\cg[5;1]+\cg[4;1])/2,(\cg[5;2]+\cg[4;2])/2,(\cg[5;3]+\cg[4;3])/2}

\matrix{coordg=\cg
\coord_milieu}

\text{lp_coord=}
\for{i=1 to 5}{\text{jj=\listpoint[\i]=(\coordg[\i;])}
\text{lp_coord=wims(append line \jj to \lp_coord)}}

\text{fig_ggb=enable3d=true
SetVisibleInView(xAxis,-1,false);
SetVisibleInView(yAxis,-1,false);
SetVisibleInView(zAxis,-1,false);
\lp_outil
\lp_coord

a=Segment(A,B);
b=Segment(B,C);
c=Segment(C,D);
d=Segment(D,A);

e=Segment(A,S);
f=Segment(B,S);
g=Segment(C,S);
h=Segment(D,S);
\lp_mil
\vectt
\lp_fix
\lp_lab
\lp_col
\lp_enon
SetPerspective("T");
}
