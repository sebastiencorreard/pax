\text{range=35}
\text{l=10}
\text{rS=30}
\real{the=randint(83..83)*pi/180}
\text{P=\rS*cos(\the),\rS*sin(\the)}
\real{A=\rS/cos(\the)} extremite du cone
\text{B=\A,0}
\text{n=1,0.7}
\real{rT=randint(30..40)}
\real{T=randitem(\A+2*\rT, \A-2*\rT)} centre de la terre

\real{sl0=(\rS+\rT)/\T[1]}
\real{Z=\T[1]*\rS/(\rT+\rS)}
\real{limx1=pari(\T[1]- sin(atan(\sl0)))}
\real{limx0=pari(sin(atan(\sl0)))}
\real{sl1=(\rS-\rT)/sqrt(\T^2-(\rS-\rT)^2)}
\text{Z1=\rS*\T[1]/(\rS-\rT)}
\real{limx2=\rS*(\rS-\rT)/\T[1]}
\real{limx3=\T[1]+\rT*(\rS-\rT)/\T[1]}
\text{droite01=\sl0*(t-\Z)}
\text{droite02=-\sl0*(t-\Z)}
\text{droite11=\sl1*(t-\Z1)} pas utilisé
\text{droite12=-\sl1*(t-\Z1)}
\real{sl=(\B[2]-\P[2])/(\B[1]-\P[1])}
\real{inter1=(\sl0*(\Z)-(\sl*\A))/(\sl0-\sl)}
\text{inter1=\inter1,pari(\sl*(\inter1-\A))}
\real{L=\A*\n[2]}
\text{L=\inter1[1]}
\text{rL=\inter1[2]}

real{rL_=\rS*(\A-\L)/\A}
real{rL=\rT/4}

\text{alp=2*random(1..2)/3*pi}
text{B=pari([\T+\rT*cos(\alp), \rT*sin(\alp)])}

\text{a=shuffle(20)}
\real{a=randitem(0,0,0,randitem(1,-1)*(\a[1]/10+1),randitem(1,-1)*(\a[2]/10+1))}
\real{a=0}
\text{La=\L+\rL/\rS*\P[1]*\a, \rL/\rS*\P[2]*\a}
\text{La=\L,0}
\text{choixe=\rL_>\rL?3:\choix}
\text{choixp=\rL_>\rL?1:2}
!!trange \limx2,\limx3
!!plot green,t,\droite11
!!trange \limx2,\limx3
!!plot black,t,\droite12
\text{dessin3=
trange \limx0, \limx1
plot green,t,\droite01
trange \limx0, \limx1
plot green,t,\droite02
}
