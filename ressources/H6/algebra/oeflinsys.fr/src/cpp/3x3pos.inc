\text{random=random}
\text{det=0}
\text{matrix=}
\integer{cnt=0}
\while{\cnt<10 and (\cnt<3 or \det<\max^2)}{
 \text{matrix1=pari(matrix(3,3,x,y,\random(\max-(\min))+(\min)))}
 \text{det1=pari(abs(matdet([\matrix1])))}
 \if{\det1>\det}{
  \text{matrix=\matrix1}
  \text{det=\det1}
 }
 \integer{cnt=\cnt+1}
}

\text{values=randint(\min..\max),randint(\min..\max),randint(\min..\max)}
\text{const=pari([\values]*[\matrix]~)}
