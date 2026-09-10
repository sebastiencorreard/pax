
\integer{condcnt=rows(\conds)}
\for{c=1 to \condcnt}{
 \text{cond=\conds[\c;]}
 \integer{cc=items(\cond)}
 \text{tt=(\sum)}
 \for{i=2 to \cc}{
  \text{tt=\tt-(\bb[\cond[\i]])}
 }
 \if{\randtype issametext computed}{
  \real{tt=\tt}
 }{
  \text{tt=maxima(expand(\tt))}
 }
 \text{bb=wims(replace item number \cond[1] by \tt in \bb)}
}
