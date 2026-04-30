%%%%% données du cube
\text{listpoint=A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T}
\text{numpoint=1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}
\text{color=}
\for {i=1 to 20}{\text{color=wims(append item green to \color)}}

%%%%% coordonnées des points à plat
\matrix{pt=0,0
10,0
12,3
2,3
0,10
10,10
12,13
2,13
5,0
7,3
1,1.5
11,1.5
5,10
7,13
1,11.5
11,11.5
0,5
10,5
12,8
2,8}


%%%%% face ABCD 1
%%%%% face EFGH 2
%%%%% face ABFE 3
%%%%% face DCHG 4
%%%%% face ADHE 5
%%%%% face BCGF 6
\matrix{faces=1,3,5
1,3,6
1,4,6
1,4,5
2,3,5
2,3,6
2,4,6
2,4,5
1,3
1,4
1,5
1,6
2,3
2,4
2,5
2,6
3,5
3,6
4,6
4,5}
%%%%% droite d'appartenance
%%%%% AB=1 BC=2 CD=3 DA=4
%%%%% EF=5 FG=6 GH=7 HE=8
%%%%% AE=9 BF=10 CG=11 DH=12
\text{nomdte=(AB),(BC),(CD),(AD),(EF),(FG),(GH),(EH),(AE),(BF),(CG),(DH)}
\text{milieu=I,L,J,K,M,P,N,O,Q,R,S,T}
\matrix{dtept=A,B,A-B,1,3,I
B,C,B-C,1,6,L
C,D,C-D,1,4,J
A,D,A-D,1,5,K
E,F,E-F,2,3,M
F,G,F-G,2,6,P
G,H,G-H,2,4,N
E,H,E-H,2,5,O
A,E,A-E,3,5,Q
B,F,B-F,3,6,R
C,G,C-G,4,6,S
D,H,D-H,4,5,T
}

\matrix{dtes=1,4,9
1,2,10
2,3,11
3,4,12
5,8,9
5,6,10
6,7,11
7,8,12
1
3
4
2
5
7
8
6
9
10
11
12}

\matrix{PT=0,0,0
0,1,0
0,1,1
0,0,1
1,0,0
1,1,0
1,1,1
1,0,1
0,0.5,0
0,0.5,1
0,0,0.5
0,1,0.5
1,0.5,0
1,0.5,1
1,0,0.5
1,1,0.5
0.5,0,0
0.5,1,0
0.5,1,1
0.5,0,1}

%%%%%faceABCD=AB,BC,CD,DA
%%%%%faceEFGH=EF,FG,GH,HE
%%%%%faceABFE=AB,BF,EF,AE
%%%%%faceDCGH=CD,CG,GH,DH
%%%%%faceADHE=AD,DH,EH,AE
%%%%%faceBCGF=BC,CG,FG,BF
\matrix{facedtes=1,2,3,4
5,6,7,8
1,10,5,9
3,11,7,12
4,12,8,9
2,11,6,10
}
\matrix{dteface=1,3
1,6
1,4
1,5
2,3
2,6
2,4
2,5
3,5
3,6
4,6
4,5
}
