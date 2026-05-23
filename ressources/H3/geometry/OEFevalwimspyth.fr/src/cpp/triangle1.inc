\text{lettres=shuffle(A,B,C,D,E,F,G,H,J,K,L,M,O,P,R,S)}
\text{A=item(1,\lettres)}
\text{B=item(2,\lettres)}
\text{C=item(3,\lettres)}
\text{D=item(4,\lettres)}

\text{s=randrow(20,20,\xmax-20,20,20,\ymax-20
\xmax-20,20,\xmax-20,\ymax-20,20,20
\xmax-20,\ymax-20,20,\ymax-20,\xmax-20,20
20,\ymax-20,20,20,\xmax-20,\ymax-20)}
 \text{ts=}
 \text{M=\xmax,\ymax,\xmax,\ymax,\xmax,\ymax}
 \text{f=(m-25)/(m-40)*(x)+(10-20*(m-25)/(m-40))}
 \for{k=1 to 6}{
  \text{tmp=simplify(evalue(\f,x=\s[\k],m=\M[\k]))}
  \text{ts=wims(append item \tmp to \ts)}
 }
 \text{f=(m-60)/(m-40)*(x)+(30-20*(m-60)/(m-40))}
 \text{xc=simplify(evalue(\f,x=\s[1],m=\xmax))}
 \text{yc=simplify(evalue(\f,x=\s[2],m=\ymax))}
 \text{dessin=triangle \s,black
text black,\ts[1],\ts[2],medium,\A
text black,\ts[3],\ts[4],medium,\B
text black,\ts[5],\ts[6],medium,\C
segment \s[1],\yc,\xc,\yc,red
segment \xc,\yc,\xc,\s[2],red}
