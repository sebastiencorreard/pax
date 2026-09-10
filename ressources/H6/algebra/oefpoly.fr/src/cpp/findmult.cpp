target=findmult3 findmult4 findmult5 findmult6

#include "header.inc"

#if defined TARGET_findmult3
# define DEG 3
#endif
#if defined TARGET_findmult4
# define DEG 4
#endif
#if defined TARGET_findmult5
# define DEG 5
#endif
#if defined TARGET_findmult6
# define DEG 6
#endif

#include "lang_titles.inc"

\text{roots=shuffle(wims(makelist x for x=-20 to 20))}
\integer{mult=randint(2 .. DEG - 1)}
\text{rootm=\roots[1]}
\text{roots=item(1 .. DEG,wims(makelist \rootm for x=1 to \mult),item(2..-1,\roots))}
\text{poly=wims(makelist (x - y) for y in \roots)}
\function{poly=randitem(1,-1,2,-2,3,-3)*wims(translate internal , to * in \poly)}
\function{dev=pari(\poly)}

#include "lang.inc"

\statement{\name_statement.
<div class="wimscenter">
\(P(x) = \dev)
</div>
}

\answer{\name_answer}{\rootm}{type=number}
