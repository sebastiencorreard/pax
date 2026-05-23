\title{Question 1217 Raison d'une suite arithmétique}
\keywords{arithmetic_sequence,mental_calculation}

\integer{r=random(1,2,3)}
\text{u0=randint(1..5)}

\text{u=simplify(\u0+\r),simplify(\u0+2*\r),simplify(\u0+3*\r),simplify(\u0+4*\r)}
\integer{rang=random(2,3)}
\integer{temp=\u[\rang]-\u0}
\integer{rep=\r}
\text{enonce=\(u\) est une suite arithmétique telle que \(u_0 = \u0\) et \(u_\rang = \u[\rang]\). Quelle est sa raison &#63;}
\text{enonceb=}
\text{feedback=Puisque \( u_\rang -u_0 =\temp\). On calcule \(\temp \div \rang =\r\)}
