  pas utilisé ?

  \text{range=30}
  \text{rS=20}
  \real{the=randint(79..83)*pi/180}
  \text{P=\rS*cos(\the),\rS*sin(\the)}
  \real{A=\rS/cos(\the)}
  \text{n=0.6,randint(80..90)/100}
  \text{n=0.6,0.8}
  \real{T=\A*\n[1]}
  \real{L=\A*\n[2]}
  \text{B=\A,0} point d'observation
  \text{La=\L,0}
  \real{rT=\rS*(1-\T/\A)}
  \real{rL1=\rS*(\A-\L)/\A}
  \real{s1=randint(5..7)/10}
  \real{rL=\rL1*\s1}
  \real{rL=\rT/4}
  \real{dist=\L-\T}
  \text{ang=randitem(0,1/3,1/6,1/9)}
  \text{orbite=}
  \for{ang2 in 0,1/12, 1/6,-1/12,-1/6}{
    \text{orbite=\orbite,\T+cos(2*pi*\ang2)*\dist,sin(2*pi*\ang2)*\dist,\rL}
  }
  \text{l=5}
  \real{Z=\T[1]*\rS/(\rT+\rS)}
  \text{slope1=pari(tan(asin(cos(\the)*(2-\n[1])/\n[1])))}
  \text{droite1=\slope1*(x-\Z)}
  \text{slope2=pari(-tan(asin(cos(\the)*(2-\n[1])/\n[1])))}
  \text{droite2=\slope2*(x-\Z)}
  \real{limite1= (\slope1)^2/(1+(\slope1)^2)*\Z}
  \real{limite2= (\slope2)^2/(1+(\slope2)^2)*\Z}
  \text{dessin3=
dsegment \limite1,(\slope1)*(\limite1-\Z), \B[1],(\slope1)*(\B[1]-\Z),blue
dsegment \limite2,(\slope2)*(\limite2-\Z), \B[1],(\slope2)*(\B[1]-\Z),black}
  \text{ang=randitem(0,1/24,1/6)}
  \text{La=\T+cos(2*pi*\ang)*\dist,sin(2*pi*\ang)*\dist}
  \if{\ang=0}{
    \text{choixp=1}
  }{
    \text{test1=pari(subst(\La[2]-(\droite1),x,\La[1]))}
    \text{test2=pari(subst(\La[2]-(\droite2),x,\La[1]))}
    \text{choixp=\test2>0?3}
    \text{choixp=\test1<0 and \test2<0 ?1}
    \text{choixp=\test1>0 and \test2<0 ?2}
  }
