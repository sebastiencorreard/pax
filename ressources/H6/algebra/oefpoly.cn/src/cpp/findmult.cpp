target=findmult3 findmult4 findmult5 findmult6

#include "xiao.inc"

#if #TARGET (findmult3)
 #define DEG 3
#endif
#if #TARGET (findmult4)
 #define DEG 4
#endif
#if #TARGET (findmult5)
 #define DEG 5
#endif
#if #TARGET (findmult6)
 #define DEG 6
#endif

\title{DEG 次多项式的重根}

\text{roots=shuffle(wims(makelist x for x=-20 to 20))}
\integer{mult=randint(2 .. DEG - 1)}
\text{rootm=\roots[1]}
\text{roots=item(1 .. DEG,wims(makelist \rootm for x=1 to \mult),item(2..-1,\roots))}
\text{poly=wims(makelist (x - y) for y in \roots)}
\function{poly=randitem(1,-1,2,-2,3,-3)*wims(translate internal , to * in \poly)}
\function{dev=pari(\poly)}

\statement{以下多项式有一个重根. 试求出这个根.
<p><center>
\(P(x) = \dev)
</center>
}

\answer{重根}{\rootm}{type=number}
