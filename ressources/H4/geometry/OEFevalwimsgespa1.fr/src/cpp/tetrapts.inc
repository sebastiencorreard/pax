%%%%% données du tétraèdre
\text{listpoint=A,B,C,D,I,J,K,L,M,N,O,P,Q,R,S,T}
\text{numpoint=1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}
\text{color=}
\for {i=1 to 16}{\text{color=wims(append item green to \color)}}
\matrix{pt=0,0
6,18
24,0
18,12
8,0
16,0
6,4
12,8
2,6
4,12
12,12
18,6
10,16
14,14
20,8
22,4}

%%%%% face ABC 1
%%%%% face BCD 2
%%%%% face ACD 3
%%%%% face ABD 4
\matrix{faces=1,3,4
1,2,4
1,2,3
2,3,4
1,3
1,3
4,3
4,3
1,4
1,4
1,2
1,2
2,4
2,4
2,3
2,3}

\matrix{facedtes=1,2,5
2,3,6
3,4,5
1,4,6}

%%%%% droite d'appartenance
%%%%% AB=1 BC=2 CD=3 DA=4, AC=5, BD=6
\text{nomdte=(AB),(BC),(CD),(AD),(AC),(BD)}
\text{tiers1=M,O,T,K,I,Q}
\text{tiers2=N,P,S,L,J,R}

\matrix{dtept=A,B,A-B,1,4,M,N
B,C,B-C,1,2,O,P
C,D,C-D,2,3,S,T
A,D,A-D,3,4,K,L
A,C,A-C,1,3,I,J
B,D,B-D,2,4,Q,R}
\matrix{dtes=1,4,5
1,2,6
2,3,5
3,4,6
5
5
4
4
1
1
2
2
6
6
3
3}

\matrix{PT=0,0,0
6,18,6
24,0,0
18,12,0
8,0,0
16,0,0
6,4,0
12,8,0
2,6,2
4,12,4
12,12,4
18,6,2
10,16,4
14,14,2
20,8,0
22,4,0
}

%%%%%faceABC=AB,BC,AC
%%%%%faceBCD=BC,CD,BD
%%%%%faceACD=AC,CD,AD
%%%%%faceABD=AB,BD,AD

\matrix{facedtes=1,2,5
2,3,6
5,3,4
1,6,4
}
\matrix{dteface=1,4
1,2
2,3
3,4
1,3
2,4
}

\matrix{PT=0,0,0
12,6,18
0,24,0
0,18,12
0,8,0
0,16,0
0,6,4
0,12,8
4,2,6
8,4,12
8,12,12
4,18,6
8,10,16
4,14,14
0,20,8
0,22,4}
