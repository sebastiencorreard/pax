target=recur1

\format{html}
#define TITLE Raisonnement par récurrence
#if defined TARGET_recur1
\title{TITLE}
#include "author.inc"
&&& x pour u_n, y pour u_{n+1}, z pour u_{n-1},
\integer{k=randint(2..8)}
\integer{a=randint(1..10)}
\integer{b=\a+randint(1..10)}
\text{data=\(u_n < u_{n+1}),0,&lt;,u_0,u_1,u_{n+1},u_{n+2},raw
\(u_n > u_{n+1}),0,&gt;,u_0,u_1,u_{n+1} , u_{n+2},raw
\(u_{n+1}-u_n < \frac{1}{\k}(u_n-u_{n-1})),1,&lt;,u_2-u_1,(u_1-u_0)/\k,u_{n+2}-u_{n+1},(u_{n+1}-u_n)/\k,raw
\(u_n < \b),0,&lt;,u_0,\b, u_{n+1}, \b,formal
\(u_n=\frac{\a n +\b}{(n-1)u_{n-1}+n}),1,=,u_1,\a+\b,u_{n+1},(\a*(n+1)+\b)/(n*u_n+n+1),formal
\(u_n=\frac{\a (n+1)+\b}{n u_{n-1}+\a}),1,=,u_1,(2*\a+\b)/(u_0+\a),u_{n+1},(\a*(n+2)+\b)/((n+1)*u_n+\a),formal
\(u_n=\frac{n(n+1)}{2}),0,=,u_0,0,u_{n+1},(n+1)*(n+2)/2
\(u_n=\frac{n(n-1)}{2}),1,=,u_1,0,u_{n+1},n*(n+1)/2
\(u_n=\frac{n(n+1)(2n+1)}{6}),0,=,u_0,0,u_{n+1},(n+1)*(n+2)*(2*n+3)/6
\(u_n=\frac{n(n-1)(2n-1)}{6}),1,=,u_1,0,u_{n+1},n*(n+1)*(2*n+1)/6
}
\integer{i=randint(1..rows(\data))}
integer{i=8}
\text{cedata=row(\i,\data)}
\text{pn=\cedata[1]}
\text{symb=\cedata[3]}
\integer{n0=\cedata[2]}
\text{p0g=\cedata[4]}
\text{p0d=\cedata[5]}
\text{pnpg=\cedata[6]}
\text{pnpd=\cedata[7]}
\text{ttype=\cedata[8]}

\statement{On considère la propriété
  <div class="wimscenter">\( P(n)): \pn</div>
  <ol> <li>
  Écrire cette propriété au rang \n0:
  <div class="wimscenter"><label for="reply1">\(P(\n0)):</label>
    \embed{reply1} <label for="reply2">\symb</label> \embed{reply2}</div>
  </li><li>
  Écrire cette propriété au rang \(n+1):
  <div class="wimscenter"><label for="reply3">\(P(n+1)):</label> \embed{reply3}
  <label for="reply4">\symb</label> \embed{reply4}</div>
  </li></ol>
  <div class="wims_instruction">Taper <span class="tt">u_n</span> pour \(u_n) et u_{n+1} pour \(u_{n+1}).</div>
}
\answer{\(P(\n0)) gauche}{\p0g}{type=formal}
\answer{\(P(\n0)) droite}{\p0d}{type=\ttype}
\answer{\(P(n+1)) gauche}{\pnpg}{type=raw}
\answer{\(P(n+1)) droite}{\pnpd}{type=\ttype}

#endif
