\text{listmilieu=I,J,K,L,M,N,O,P}
\text{lp_mil=I=Midpoint(a)
J=Midpoint(c)
K=Midpoint(d)
L=Midpoint(b)
M=Midpoint(e)
N=Midpoint(f)
O=Midpoint(g)
P=Midpoint(h)
}

\for{i in \listmilieu}{\text{t=SetColor[\i,darkgreen]}
\text{lp_mil=wims(append line \t to \lp_mil)}}
