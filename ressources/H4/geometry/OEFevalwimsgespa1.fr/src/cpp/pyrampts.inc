%%%%% données du cube
\text{listpoint=A,B,C,D,S,I,J,K,L,M,N,O,P}
\text{numpoint=1,2,3,4,5,6,7,8,9,10,11,12,13}
\text{color=}
\for {i=1 to 13}{\text{color=wims(append item green to \color)}}

%%%%% coordonnées des points à plat
\matrix{pt=0,0
10,0
13,5
3,5
8,8
5,0
8,5
1.5,2.5
11.5,2.5
4,4
9,4
10.5,6.5
5.5,6.5}


%%%%% face ABCD 1
%%%%% face SAB 2
%%%%% face SBC 3
%%%%% face SCD 4
%%%%% face SAD 5
\matrix{faces=1,2,5
1,2,3
1,3,4
1,4,5
2,3,4,5
1,2
1,4
1,5
1,3
2,5
2,3
3,4
4,5}
%%%%% droite d'appartenance
%%%%% AB=1 BC=2 CD=3 DA=4
%%%%% SA=5 SB=6 SC=7 SD=8
\text{nomdte=(AB),(BC),(CD),(AD),(AS),(BS),(CS),(DS)}
\matrix{facedtes=1,2,3,4
1,5,6
2,6,7
3,7,8
4,8,5
}
\matrix{dtes=1,4,5
1,2,6
2,3,7
3,4,8
5,6,7,8
1
3
4
2
5
6
7
8}


\matrix{PT=0,0,0
0,10,0
0,13,5
0,3,5
10,6.5,2.5
0,5,0
0,8,5
0,1.5,2.5
0,11.5,2.5
5,3.25,1.25
5,8.25,1.25
5,9.75,3.75
5,4.75,3.75
}
