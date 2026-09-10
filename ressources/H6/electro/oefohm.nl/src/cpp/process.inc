
\text{namelist=v1,r1,r2,r3,r}
\text{vlist=\v1,\r1,\r2,\r3,\r}
\integer{vcnt=items(\vlist)}
\text{flist=\f_a1,\f_a2,\f_v2}
\text{res=}
\text{digits=\tolerance>=1?3:4}
\for{f in \flist}{
 \text{ff=\f}
 \for{i=1 to \vcnt}{
  \text{ff=wims(mathsubst \namelist[\i]=(\vlist[\i]) in \ff)}
 }
 \int{log=floor(log10(\ff))}
 \real{ff=rint((\ff)*10^(\digits-(\log)))*10^(\log-\digits)}
 \text{res=\res\ff,}
}
\real{a1=\res[1]*\Afactor}
\real{a2=\res[2]*\Afactor}
\text{v2=\res[3]}

\text{comp2=\comp}
\text{comp=wims(replace internal _R1_ by \R1 in \comp)}
\text{comp=wims(replace internal _R2_ by \R2 in \comp)}
\text{comp=wims(replace internal _R3_ by \R3 in \comp)}
\text{comp2=wims(replace internal _R1_ by \Rt1 in \comp2)}
\text{comp2=wims(replace internal _R2_ by \Rt2 in \comp2)}
\text{comp2=wims(replace internal _R3_ by \Rt3 in \comp2)}

\if{v1 iswordof \given}{
 \text{comp=wims(replace internal _V1_ by \v1 V in \comp)}
}{
 \text{comp=wims(replace internal _V1_ by U in \comp)}
}
\if{r iswordof \given}{
 \if{a2 isin \method}{
  \text{comp=wims(replace internal _R_ by R=\R in \comp)}
 }{
  \text{comp=wims(replace internal _R_ by \R in \comp)}
 }
 \text{comp2=wims(replace internal _R_ by \Rt in \comp2)}
}{
 \text{comp=wims(replace internal _R_ by @@R in \comp)}
}

\if{v1 iswordof \ask}{
 \text{quest=\name_quest[1;]}
 \text{qunit=V}
 \text{goodc=\v1}
}
\if{v2 iswordof \ask}{
 \text{quest=\name_quest[2;]}
 \text{qunit=V}
 \text{goodc=\v2}
}
\if{a1 iswordof \ask}{
 \text{quest=\name_quest[3;]}
 \text{qunit=\Aunit}
 \text{goodc=\a1}
}
\if{a2 iswordof \ask}{
 \text{quest=\name_quest[4;]}
 \text{qunit=\Aunit}
 \text{goodc=\a2}
}
\if{r iswordof \ask}{
 \text{quest=\name_quest[5;]}
 \text{qunit=\Runit}
 \real{goodc=\r/\Rfactor}
}

\text{more=}
\if{\A notsametext and v2 isin \method}{
 \text{more=linewidth 7
point \A,black
text black,\A[1]+0.4,\A[2]+0.3,large,A
 }
}
\text{circ=slib(circuits/draw \ctype,\drawsize,black,\comp)
\more}
\text{size=wims(line 1 of \circ)}
\text{size=wims(word 2 to -1 of \size)}
\text{size=\size=?300,300}
\text{circ=draw(\size
\circ)}
\real{good1=\goodc*(1-\tolerance/100)}
\real{good2=\goodc*(1+\tolerance/100)}
\real{good3=\goodc*(1-2*\tolerance/100)}
\real{good4=\goodc*(1+2*\tolerance/100)}
\text{good=\good1,\good2,\goodc}

