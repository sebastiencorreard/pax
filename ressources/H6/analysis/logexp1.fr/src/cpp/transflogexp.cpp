target=transflogexp

#include "header.inc"
#include "lang_titles.inc"

\if{\confparm1=}{
\text{type=1}
}{
\text{type=randitem(\confparm1,\confparm1)}
}

\text{typerep=numexp}

\text{l=shuffle(2,3,4,5)}
\text{p=\l[1]}
\text{q=\l[2]}

\if{\type=1}{
\text{u=randint(2..4)}
\text{a=simplify(\p^(\u))}
\text{expr=\u ln (\p)}
}
\if{\type=2}{
\text{u=randint(-4..-2)}
\text{a=simplify(\p^(\u))}
\text{expr=\u ln (\p)}
}
\if{\type=3}{
\text{a=simplify(\p*\q)}
\text{expr=ln(\p)+ln(\q)}
}
\if{\type=4}{
\text{a=simplify(\p/\q)}
\text{expr=randitem(ln(\p)-ln(\q),-ln(\q)+ln(\p))}
}
\if{\type=5}{
\text{l1=shuffle(1,randitem(2,3,4))}
\integer{u=\l1[1]}
\integer{v=\l1[2]}
\text{expr=\u*ln(\p)+\v*ln(\q)}
\text{a=simplify(\p^(\u)*\q^(\v))}
}
\if{\type=6}{
\text{a=simplify(\p/\q)}
\text{l1=shuffle(1,randitem(2,3,4))}
\text{l2=shuffle(-1,1)}
\integer{u=\l1[1]*\l2[1]}
\integer{v=\l1[2]*\l2[2]}
\text{expr=\u*ln(\p)+\v*ln(\q)}
\text{a=simplify(\p^(\u)*\q^(\v))}
}
\if{\type=7}{
\text{a=simplify(\p/\q)}
\text{l1=shuffle(2,3,4)}
\integer{u=\l1[1]}
\integer{v=\l1[2]}
\text{expr=\u*ln(\p)+\v*ln(\q)}
\text{a=simplify(\p^(\u)*\q^(\v))}
}
\if{\type=8}{
\text{a=simplify(\p/\q)}
\text{l1=shuffle(2,3,4)}
\text{l2=shuffle(-1,1)}
\integer{u=\l1[1]*\l2[1]}
\integer{v=\l1[2]*\l2[2]}
\text{expr=\u*ln(\p)+\v*ln(\q)}
\text{a=simplify(\p^(\u)*\q^(\v))}
}
\if{\type=9}{
\text{typerep=algexp}
\text{expr=randitem(ln(\p)+\q,\q+ln(\p))}
\text{a=simplify(\p*exp(\q))}
}
\if{\type=10}{
\text{typerep=algexp}
\text{l1=shuffle(-1,1)}
\integer{s1=\l1[1]}
\integer{s2=\l1[2]}
\text{expr=randitem(\s1*ln(\p)+\s2*\q,\s2*\q+\s1*ln(\p))}
\text{a=simplify(exp(\expr))}
}
\if{\type=11}{
\text{typerep=algexp}
\text{u=randint(2..4)}
\text{expr=randitem(\u*ln(\p)+\q,\q+\u*ln(\p))}
\text{a=simplify(\p^(\u)*exp(\q))}
}
\if{\type=12}{
\text{typerep=algexp}
\text{u=randint(2..4)}
\text{l1=shuffle(-1,1)}
\integer{s1=\l1[1]}
\integer{s2=\l1[2]}
\text{expr=randitem(\s1*\u*ln(\p)+\s2*\q,\s2*\q+\s1*\u*ln(\p))}
\text{a=simplify(exp(\expr))}
}

\text{l=shuffle(2,3,4,5)}
\integer{p=randitem(-1,1)*\l[1]}
\integer{q=randitem(-1,1)*\l[2]}

\if{\type=51}{
\integer{u=randitem(-1,1)*randint(2..4)}
\text{a=simplify((\p)*(\u))}
\text{expr=(exp(\p))^{\u}}
}
\if{\type=52}{
\integer{u=randitem(-1,1)*randint(2..4)}
\text{a=simplify((-\p)*(\u))}
\text{expr=1/(exp(\p))^{\u}}
}
\if{\type=53}{
\text{a=simplify(\p+\q)}
\text{expr=exp(\p)\times exp(\q)}
}
\if{\type=54}{
\text{a=simplify(\p-\q)}
\text{expr=exp(\p)/exp(\q)}
}
\if{\type=55}{
\integer{u=randitem(-1,1)*randint(2..4)}
\text{expr=randitem((exp(\p))^{\u} \times exp(\q),exp(\q) \times (exp(\p))^{\u})}
\text{a=simplify((\p)*(\u) +\q)}
}
\if{\type=56}{
\integer{u=randitem(-1,1)*randint(2..4)}
\if{randitem(1,2)=1}{
\text{expr=\frac{(exp(\p))^{\u}}{exp(\q)}}
\text{a=simplify(\p*(\u)-(\q))}
}{
\text{expr=\frac{exp(\q)}{(exp(\p))^{\u}}}
\text{a=simplify(\q-(\p)*(\u))}
}
}
\if{\type=57}{
\text{l1=shuffle(2,3,4)}
\integer{u=randitem(-1,1)*\l1[1]}
\integer{v=randitem(-1,1)*\l1[2]}
\text{expr=(exp(\p))^{\u} \times (exp(\q))^{\v}}
\text{a=simplify((\p)*(\u)+(\q)*(\v))}
}
\if{\type=58}{
\text{l1=shuffle(2,3,4)}
\integer{u=randitem(-1,1)*\l1[1]}
\integer{v=randitem(-1,1)*\l1[2]}
\text{expr=\frac{(exp(\p))^{\u}}{(exp(\q))^{\v}}}
\text{a=simplify((\p)*(\u)-(\q)*(\v))}
}
\if{\type=59}{
\text{typerep=algexp}
\integer{q=abs(\q)}
\text{expr=randitem(exp(\p)\times \q,\q \times exp(\p))}
\text{a=simplify(\p+ln(\q))}
}
\if{\type=60}{
\text{typerep=algexp}
\integer{q=abs(\q)}
\if{randitem(1,2)=1}{
\text{expr=\frac{exp(\p)}{\q}}
\text{a=simplify(\p-ln(\q))}
}{
\text{expr=\frac{\q}{exp(\p)}}
\text{a=simplify(ln(\q)-\p)}
}
}
\if{\type=61}{
\text{typerep=algexp}
\integer{q=abs(\q)}
\integer{u=randitem(-1,1)*randint(2..4)}
\text{expr=randitem(exp(\p)^{\u}\times \q,\q \times exp(\p)^{\u})}
\text{a=simplify((\p)*(\u)+ln(\q))}
}
\if{\type=62}{
\text{typerep=algexp}
\integer{q=abs(\q)}
\integer{u=randitem(-1,1)*randint(2..4)}
\if{randitem(1,2)=1}{
\text{expr=\frac{exp(\p)^{\u}}{\q}}
\text{a=simplify((\p)*(\u)-ln(\q))}
}{
\text{expr=\frac{\q}{exp(\p)^{\u}}}
\text{a=simplify(ln(\q)-(\p)*(\u))}
}
}


\if{\type<50}{
\text{ff=ln}
}{
\text{ff=exp}
}

#include "lang.inc"

\statement{<div class="spacer">\name_statement1 \(\ff (a)\), \name_where \(a\) \name_statement2.</div>

<div> \(\expr= \ff\)(\embed{reply1,6})</div>
}
\answer{}{\a}{type=\typerep}
