\text{listmilieu=I,J,K,L,M,N,O,P,Q,R,S,T}
\text{lp_mil=I=(0,-3,0)
J=(0,3,0)
K=(-3,0,0)
L=(3,0,0)
M=(0,-3,6)
N=(0,3,6)
O=(-3,0,6)
P=(3,0,6)
Q=(-3,-3,3);
R=(3,-3,3);
S=(3,3,3);
T=(-3,3,3);}
\for{i in \listmilieu}{\text{t=SetColor[\i,darkgreen]}
\text{lp_mil=wims(append line \t to \lp_mil)}}
