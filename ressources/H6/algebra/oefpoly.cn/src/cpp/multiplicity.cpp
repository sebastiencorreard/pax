target=multiplicity3 multiplicity4 multiplicity5 multiplicity6

#include "xiao.inc"

#if #TARGET (multiplicity3)
 #define DEG 3
#endif
#if #TARGET (multiplicity4)
 #define DEG 4
#endif
#if #TARGET (multiplicity5)
 #define DEG 5
#endif
#if #TARGET (multiplicity6)
 #define DEG 6
#endif

\title{DEG 次多项式根的重数}

\text{roots=shuffle(wims(makelist x for x=-20 to 20))}
\integer{mult=randint(1 .. DEG)}
\text{rootm=\roots[1]}
\text{roots=item(1 .. DEG,wims(makelist \rootm for x=1 to \mult),item(2..-1,\roots))}
\text{poly=wims(makelist (x - y) for y in \roots)}
\function{poly=randitem(1,-1,2,-2,3,-3)*wims(translate internal , to * in \poly)}
\function{dev=pari(\poly)}

\statement{\rootm 是以下多项式的一个根.
求它的重数.
<p><center>
\(P(x) = \dev)
</center>
}

\answer{\rootm 的重数}{\mult}{type=number}
