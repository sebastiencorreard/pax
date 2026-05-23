\title{Question 1112 Terme d'une suite récurrrente}
\keywords{mental_calculation,sequence,geometric_sequence,recurrence_relation}
\text{u0=random(-1,1)}
\integer{q=random(3,2,5)}
\integer{n=\q=5?3:4}
\integer{u=\q*\u0}
\for{i=2 to \n}{
\integer{temp=\q*\u[\i-1]}
\text{u=\u,\temp}
}
\integer{rep=\u[\n]}
\text{defsuite=\(u_0=\u0 \) et \( u_{n+1}=\q \times u_n\)}
\text{enonce=Pour tout entier \(n\),<br> \defsuite.<br> \(u_\n\)=}
\text{enonceb= }
\text{feedback=On a : \(u_1=\q \times \u0=\u[1]\), \(u_2=\u[2]\) etc... }
