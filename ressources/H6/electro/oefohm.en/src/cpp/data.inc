
\integer{drawsize=20}
\text{E6=10,15,22,33,47,68}
\text{E12=10,12,15,18,22,27,33,39,47,56,68,82}
\text{E24=10,11,12,13,15,16,18,20,22,24,27,30,33,36,39,43,47,51,56,62,68,75,82,91}

\text{vlist=1,1.2,1.5,1.8,2,2.5,3,3.5,4,4.5,5,6,7,8,9}

\text{vunit=randitem(1,10,100)}
\text{runit=randitem(1,10,100,1000)}

\if{\vunit > \runit}{
 \text{Afactor=1}
 \text{Aunit=A}
}{
 \text{Afactor=1000}
 \text{Aunit=mA}
}
\if{\runit >=  100}{
 \text{Rfactor=1000}
 \text{Runit=K\(Omega)}
}{
 \text{Rfactor=1}
 \text{Runit=\(Omega)}
}

\real{v1=randitem(\vlist)*\vunit}

\text{EE=wims(values x*10 for x in \E12)}
\text{start=randint(1..10)}
\text{rlist=item(\start..\start+8,\E12,\EE)}
\text{rlist=shuffle(\rlist)}
\text{rlist=wims(values x*\runit for x in \rlist)}
\text{Rlist=}
\text{Rlist2=}
\for{i=1 to 4}{
 \integer{Rt=floor(\rlist[\i]/1000)}
 real{rr=\rlist[\i]/1000-\Rt}
 text{rt=\rlist[\i]%1000>0?wims(char 3 to -1 of \rr):}
 text{Rt=\rlist[\i]<1000?\rlist[\i]:\Rt[]K\rt}
 \real{rt=\rlist[\i]<1000?\rlist[\i]:\rlist[\i]/1000}
 \text{Rt=\rlist[\i]<1000?\rt:\rt[]K}
 \text{Rt2=\rlist[\i]<1000?OMEGA:}
 \text{Rlist=\Rlist\Rt,}
 \text{Rlist2=\Rlist2\Rt2,}
}

\real{r1=\rlist[1]}
\real{r2=\rlist[2]}
\real{r3=\rlist[3]}
\real{r=\rlist[4]}
\text{R1=\Rlist[1]}
\text{R2=\Rlist[2]}
\text{R3=\Rlist[3]}
\text{R=\Rlist[4]}
\text{Rt1=\Rlist2[1]}
\text{Rt2=\Rlist2[2]}
\text{Rt3=\Rlist2[3]}
\text{Rt=\Rlist2[4]}
