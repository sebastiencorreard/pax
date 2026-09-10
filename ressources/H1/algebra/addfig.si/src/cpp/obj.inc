
\text{redund=}
\text{red=wims(listcomplement \bb in \list)}
\integer{rcnt=min(\confparm2,items(\red))}
\for{t=1 to \rcnt}{
 \text{rrr=item(1..\confparm2,\red)}
 \text{tt=/ isin \rrr[\t]?wims(replace / by /( in \(\rrr[\t]))):\(\rrr[\t])}
 \text{redund=\redund,\tt}
}
\text{obj=}
\for{t=1 to \Tot}{
 \if{/ isin \bb[\t]}{
  \text{tt=wims(replace / by /( in \(\bb[\t])))}
 }{\text{tt=\(\bb[\t])}}
 \text{obj=wims(append item \tt to \obj)}
}
