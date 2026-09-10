utiliser dans eclipse.cpp
\text{range=35}
\text{rS=randint(17..20)}
\text{rL=randint(4..6)}
\text{L=randint(100..150)}
\real{rT=4*\rL}
\text{La=\L,0}

\text{tangente=slib(tangente \S,0,\rS,\La,\rL)}
\text{data=\tangente[1..4]}
\text{tangente=\tangente[5]}
\text{dessin_tangente=wims(declosing \tangente)}

\text{listT=\data[4]+2*\rT,\data[4]+3*\rT}
\if{\data[4]-\L>\rT+2*\rL}{
  \text{listT=\listT, \data[4]+\rT/2}
}
\text{cnt=items(\listT)}
\integer{T1=randint(1..\cnt)}
\real{T=\listT[\T1]}
\integer{l=ceil((\T+\rT+\rS)/(2*\rS))}

\text{ch=randitem(1,2,2,2,3)}
\text{bary=randitem(0.3,0.5,0.7)}

\real{sl1=\data[1]}
\real{Z1=\data[3]}
\real{sl2=\data[2]}
\real{Z2=\data[4]}
\real{disc=(\T+(\sl1)^2*\Z1)^2-(\T^2+(\sl1)^2*\Z1^2-\rT^2)*((\sl1)^2+1)}
\real{lim1=(\T+(\sl1)^2*\Z1-\disc^(1/2))/((\sl1)^2+1)}
\text{dessin_tangente=wims(replace internal XXXXXX1 by \lim1 in \dessin_tangente)}
\real{disc=(\T+(\sl2)^2*\Z2)^2-(\T^2+(\sl2)^2*\Z2^2-\rT^2)*((\sl2)^2+1)}
\real{lim2=(\T+(\sl2)^2*\Z2-\disc^(1/2))/((\sl2)^2+1)}
\text{dessin_tangente=wims(replace internal XXXXXX2 by \lim2 in \dessin_tangente)}

\text{listangle=pari(B=[arccos((\T-\lim1)/\rT),arccos((\T-\lim2)/\rT)];concat(-B,B))}
\text{listangle=wims(sort numeric item \listangle)}
\text{listarc=arc \T,0,2*\rT,2*\rT,pari([\listangle[1]+pi,\listangle[2]+pi]*180/pi),green
arc \T,0,2*\rT,2*\rT,pari([\listangle[2]+pi,\listangle[3]+pi]*180/pi),green
arc \T,0,2*\rT,2*\rT,pari([\listangle[3]+pi,\listangle[4]+pi]*180/pi),green}
\text{dessin_zone=linewidth 5
row(\ch,\listarc)}
\text{the=\listangle[\ch]}
\real{the=\bary*\listangle[\ch]+(1-\bary)*\listangle[\ch+1]}
\text{P=pari([\T-\rT*cos(\the),-\rT*sin(\the)])}
\text{LP2=pari(norml2([\P]-[\L,0]))}
\real{limx1=0}
\real{limx2=0}
\ifval{abs(\P[2])>10^-5}{
  \text{t1=pari(sqrt(\LP2-\rL^2)/\rL)}
  \text{t2=\P[2]!=0?(\P[1]-\L)/\P[2]:0}
  \real{slx1=pari((\t1-\t2)/(1+\t1*\t2))}
  \real{slx2=(\t1+\t2)/(1-\t1*\t2)}
  \real{slx2=-\slx2}
  \real{Zx1=\P[1]-(\P[2])/\slx1}
  \real{discx=\rS^2*(1+(\slx1)^2)-(\slx1*\Zx1)^2}
  \if{\discx<0}{
    \real{limx1=0}
  }{
    \real{limx1=((\slx1)^2*\Zx1+(\discx)^(1/2))/((\slx1)^2+1)}
  }
  \real{Zx2=\P[1]-(\P[2])/\slx2}
  \real{discx2=\rS^2*(1+(\slx2)^2)-(\slx2*\Zx2)^2}
  \if{\discx2<0}{
    \real{limx2=0}
  }{
    \real{limx2=((\slx2)^2*\Zx2+(\discx2)^(1/2))/((\slx2)^2+1)}
  }
}{
  \real{slx1=\rL/((\P[1]-\L)^2-\rL^2)^(1/2)}
  \real{slx2=-\slx1}
  \real{Zx1=\P[1]}
  \real{discx=\rS^2*(1+(\slx1)^2)-(\slx1*\Zx1)^2}
  \if{\discx<0}{
    \real{limx1=0}
  }{
    \text{limx1=((\slx1)^2*\Zx1+(\discx)^(1/2))/((\slx1)^2+1)}
  }
  \real{limx2=\limx1}
}
\text{PS1=pari([\limx1,\slx1 *(\limx1-\P[1])+\P[2]])}
\text{PS2=pari([\limx2,\slx2 *(\limx2-\P[1])+\P[2]])}

\text{dessin_coneombre=segments black, \P,\PS1
  segments black, \P,\PS2}

\text{choixp=\ch iswordof 1 3? 2}
\if{\ch=2 and \T> \data[4]+\rT}{
  \text{choixp=3}
}
\text{choixp=\ch=2 and \T<=\data[4]+\rT ? 1}
