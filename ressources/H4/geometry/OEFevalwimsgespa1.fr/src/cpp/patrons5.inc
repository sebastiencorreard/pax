\text{diags=(segment 0,5,5,0,blue),(segment 5,0,10,5,blue),(segment 10,5,5,10,blue),BD,BF,FH
(segment 0,0,5,5,blue),(segment 5,5,10,10,blue),(segment 10,10,15,15,blue),AE,EI,IM
(segment 5,10,10,5,blue),(segment 10,5,15,10,blue),(segment 15,10,10,15,blue),FH,FJ,JL
(segment 0,5,5,0,blue),(segment 15,10,20,5,blue),(segment 20,5,25,10,blue),BE,IL,IN
(segment 0,5,5,0,blue),(segment 5,0,10,5,blue),(segment 10,5,15,10,blue),BE,BG,GL
(segment 5,5,10,0,blue),(segment 10,0,15,5,blue),(segment 15,5,10,10,blue),CF,CH,HK
(segment 5,10,10,5,blue),(segment 10,5,15,10,blue),(segment 15,10,20,15,blue),FI,FK,KN
(segment 5,0,10,5,blue),(segment 10,5,15,10,blue),(segment 15,10,20,5,blue),BF,FK,HK
(segment 0,0,5,5,blue),(segment 5,5,10,10,blue),(segment 15,15,20,10,blue),AE,EJ,LM
(segment 10,0,5,5,blue),(segment 5,5,10,10,blue),(segment 10,10,15,5,blue),CE,EJ,GJ
(segment 0,0,5,5,blue),(segment 5,5,10,10,blue),(segment 10,10,15,15,blue),AE,EJ,JN
(segment 5,10,10,5,blue),(segment 10,5,15,10,blue),(segment 15,10,10,15,blue),FI,FK,KM
(segment 0,5,5,0,blue),(segment 5,10,10,15,blue),(segment 15,10,20,5,blue),BD,IN,HK
(segment 5,15,10,10,blue),(segment 10,10,15,5,blue),(segment 15,5,20,10,blue),JM,GJ,GL
(segment 0,0,5,5,blue),(segment 5,5,10,0,blue),(segment 15,5,20,10,blue),AE,CE,GL

}
\text{cedata=randomrow(\diags)}
\integer{i=randint(1..3)}
\integer{j=randint(0..4)}
\integer{k=\j*3+\i}
\text{cedata=row(\k,\diags)}
\text{indl=shuffle(3)}
\text{diag1=wims(declosing \cedata[\indl[1]])}
\text{diag2=wims(declosing \cedata[\indl[2]])}
\text{rep=(\cedata[3+\indl[3]])}

\text{pat2=
xrange -5,30
yrange -5,20
linewidth 2
poly black,0,0,15,0,15,5,0,5
poly black,10,5,25,5,25,10,10,10
segment 5,0,5,5,black
segment 10,0,10,5,black
segment 15,5,15,10,black
segment 20,5,20,10,black
text red,0,-1,medium,A
text red,5,-1,medium,B
text red,10,-1,medium,C
text red,15,-1,medium,D
text red,0,6.4,medium,E
text red,5,6.4,medium,F
text red,10,6.4,medium,G
text red,15,6.4,medium,H
text red,20,6.4,medium,I
text red,25,6.4,medium,J
text red,10,11.4,medium,K
text red,15,11.4,medium,L
text red,20,11.4,medium,M
text red,25,11.4,medium,N

\diag1
\diag2
}
\text{pat1=
xrange -5,30
yrange -5,20
linewidth 2
poly black,0,0,10,0,10,5,0,5
poly black,5,5,15,5,15,10,5,10
poly black,10,10,20,10,20,15,10,15
segment 5,0,5,5,black
segment 10,5,10,10,black
segment 15,10,15,15,black
\diag1
\diag2
text red,0,-1,medium,A
text red,5,-1,medium,B
text red,10,-1,medium,C
text red,0,6.4,medium,D
text red,5,6.4,medium,E
text red,10,6.4,medium,F
text red,15,6.4,medium,G
text red,5,11.4,medium,H
text red,10,11.4,medium,I
text red,15,11.4,medium,J
text red,20,11.4,medium,K
text red,10,16.4,medium,L
text red,15,16.4,medium,M
text red,20,16.4,medium,N


}
\text{pat3=
xrange -5,30
yrange -5,20
linewidth 2
poly black,0,0,10,0,10,5,0,5
poly black,5,5,20,5,20,10,5,10
poly black,15,10,20,10,20,15,15,15
segment 5,0,5,5,black
segment 10,5,10,10,black
segment 15,5,15,10,black
\diag1
\diag2
text red,0,-1,medium,A
text red,5,-1,medium,B
text red,10,-1,medium,C
text red,0,6.4,medium,D
text red,5,6.4,medium,E
text red,10,6.4,medium,F
text red,15,6.4,medium,G
text red,20,6.4,medium,H
text red,5,11.4,medium,I
text red,10,11.4,medium,J
text red,15,11.4,medium,K
text red,20,11.4,medium,L
text red,15,16.4,medium,M
text red,20,16.4,medium,N
}
\text{pat4=
xrange -5,30
yrange -5,20
linewidth 2
poly black,0,0,10,0,10,5,0,5
poly black,5,5,20,5,20,10,5,10
poly black,10,10,15,10,15,15,10,15
segment 5,0,5,5,black
segment 10,5,10,10,black
segment 15,5,15,10,black
\diag1
\diag2
text red,0,-1,medium,A
text red,5,-1,medium,B
text red,10,-1,medium,C
text red,0,6.4,medium,D
text red,5,6.4,medium,E
text red,10,6.4,medium,F
text red,15,6.4,medium,G
text red,20,6.4,medium,H
text red,5,11.4,medium,I
text red,10,11.4,medium,J
text red,15,11.4,medium,K
text red,20,11.4,medium,L
text red,10,16.4,medium,M
text red,15,16.4,medium,N
}
\text{pat5=
xrange -5,30
yrange -5,20
linewidth 2
poly black,0,0,10,0,10,5,0,5
poly black,5,5,20,5,20,10,5,10
poly black,5,10,10,10,10,15,5,15
segment 5,0,5,5,black
segment 10,5,10,10,black
segment 15,5,15,10,black
\diag1
\diag2
text red,0,-1,medium,A
text red,5,-1,medium,B
text red,10,-1,medium,C
text red,0,6.4,medium,D
text red,5,6.4,medium,E
text red,10,6.4,medium,F
text red,15,6.4,medium,G
text red,20,6.4,medium,H
text red,5,11.4,medium,I
text red,10,11.4,medium,J
text red,15,11.4,medium,K
text red,20,11.4,medium,L
text red,5,16.4,medium,M
text red,10,16.4,medium,N
}
\if{\j=0}{\text{patron=\pat1}}
\if{\j=1}{\text{patron=\pat2}}
\if{\j=2}{\text{patron=\pat3}}
\if{\j=3}{\text{patron=\pat4}}
\if{\j=4}{\text{patron=\pat5}}
