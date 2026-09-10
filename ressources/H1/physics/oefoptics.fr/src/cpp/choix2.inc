utiise dans eclipse
\text{range=30}
\text{l=5}
\text{rS=20}
\real{the=randint(80..83)*pi/180}
\real{A=\rS/cos(\the)} extremite du cone
\text{n=0.6,0.8}
\real{T=\A*\n[1]}
\real{L=\A*\n[2]}
\real{rT=\rS*(1-\T/\A)}
\real{rL=\rT/4}
\real{dist=\L-\T}
\text{tangente=slib(tangente \S,0,\rS,\T,0,\rT)}
\text{data=\tangente[1..4]}
\text{tangente=\tangente[5]}
\text{dessin_tangente=wims(declosing \tangente)}
\text{dessin_tangente=wims(replace internal XXXXXX1 by 1000 in \dessin_tangente)}
\text{dessin_tangente=wims(replace internal XXXXXX2 by 1000 in \dessin_tangente)}
\text{sl1=\data[1]}
\text{sl2=\data[2]}
\text{Z1=\data[3]}
\text{Z2=\data[4]}
real{limite1=(\sl1)^2/(1+(\sl1)^2)*\Z1}
real{limite2=(\sl2)^2/(1+(\sl2)^2)*\Z2}

\text{ang3=pari([pi-asin(\rT/\dist)-atan(\sl1),\the+pi/2,
  -\the-pi/2,-pi+asin(\rT/\dist)+atan(\sl1)])}
\text{angmil=pari(ang=[\ang3]; [ang[2]-pi/4,(ang[1]+ang[2])/2,pi+(ang[4]+ang[1])/2,2*pi-(ang[1]+ang[2])/2,2*pi-(ang[1]+ang[2])/2+pi/6])}
\text{ang=\angmil,\ang3[1],\ang3[2],-\ang3[1],-\ang3[2]}
\text{ang=\ang[1,6,2,7,3,9,4,8,5]}
text{ang=\ang[1,3,5,7,9]}

1 rien
3 pénombrale
4 partielle
5 totale
totale, partielle, pénombrale

\integer{angcnt=items(\ang)}
\text{orbite=}
\text{verif=}
\for{i=1 to \angcnt}{
  \text{ang2=\ang[\i]}
  \text{orbite=\orbite,\T-cos(\ang2)*\dist,sin(\ang2)*\dist,\rL}
  \text{verif=\verif
  text black,\T-cos(\ang2)*\dist,sin(\ang2)*\dist,small,\i}
}

\text{choixang=randitem(1,3,4,5,6,7,9)}
\text{La=\T-cos(\ang[\choixang])*\dist,sin(\ang[\choixang])*\dist}
\text{dessin_circles=fcircles yellow,0,0,\rS
fcircles blue,\La,\rL
circles red,\T,0,\rT}

\text{choixe=\choixang iswordof 1 9?3:2}
\text{choixp=\choixang=5?1}
\text{choixp=\choixang iswordof 3 7 ?3}
\text{choixp=\choixang iswordof 4 6 ?2}
\text{choixp=\choixang iswordof 5 ?1}

