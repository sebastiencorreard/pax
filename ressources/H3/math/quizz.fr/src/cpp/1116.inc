\title{Question 1116 Terme d'une suite explicite}
\keywords{mental_calculation,sequence,arithmetic_sequence,recurrence_relation}
\integer{u0=random(2..7)}
\integer{r=random(3,2,5)}
\integer{n=random(10,11,9,8)}
\integer{u=\u0+\r}
\for{i=2 to \n}{
\integer{temp=\u0+\r*\i}
\text{u=\u,\temp}
}
\integer{rep=\u[\n]}
\text{defsuite=\( u_{n}=\u0+\r n\)}
\text{enonce=Pour tout entier \(n\), \defsuite.<br> \(u_\n\)=}
\text{enonceb= }
\text{feedback=On a : \(u_n=\u0 +\n \times \r=\u[\n]\) }
