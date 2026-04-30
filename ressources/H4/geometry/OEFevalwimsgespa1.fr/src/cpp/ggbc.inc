\text{listpoint=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W}
\text{lp_fix=}
\for{i in \listpoint}{\text{t=SetFixed[\i,true]}
\text{tt=\t
SetPointSize(\i,3);}
\text{lp_fix=wims(append line \tt to \lp_fix)}
}
\text{listlab=a,b,c,d,e,f,g,h,i,j,k,l}
\text{lp_lab=}
\for{i in \listlab}{\text{t=ShowLabel[\i, false]}
\text{lp_lab=wims(append line \t to \lp_lab)}
}
\text{listcol=U,V,W}
\text{lp_col=}
\for{i in \listcol}{\text{t=SetColor[\i,red]}
\text{lp_col=wims(append line \t to \lp_col)}
}

\matrix{coordg=-3,-3,0
3,-3,0
3,3,0
-3,3,0
-3,-3,6
3,-3,6
3,3,6
-3,3,6
0,-3,0
0,3,0
-3,0,0
3,0,0
0,-3,6
0,3,6
-3,0,6
3,0,6
-3,-3,3
3,-3,3
3,3,3
-3,3,3}

\text{lp_coord}
\for{i=1 to 8}{\text{jj=\listpoint[\i]=(\coordg[\i;])}
\text{lp_coord=wims(append line \jj to \lp_coord)}}

\text{fig_ggb=enable3d=true
SetVisibleInView(xAxis,-1,false);
SetVisibleInView(yAxis,-1,false);
SetVisibleInView(zAxis,-1,false);
\lp_outil
\lp_coord
\lp_mil
a=Segment(A,B);
b=Segment(B,C);
c=Segment(C,D);
d=Segment(D,A);

e=Segment(E,F);
f=Segment(F,G);
g=Segment(G,H);
h=Segment(H,E);

i=Segment(A,E);
j=Segment(B,F);
k=Segment(C,G);
l=Segment(D,H);
\vectt
\lp_fix
\lp_lab
\lp_col
\lp_enon
SetPerspective("T");
}
