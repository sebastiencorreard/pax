target=multiplicity3 multiplicity4 multiplicity5 multiplicity6

#include "header.inc"

#if defined TARGET_multiplicity3
# define DEG 3
#endif
#if defined TARGET_multiplicity4
# define DEG 4
#endif
#if defined TARGET_multiplicity5
# define DEG 5
#endif
#if defined TARGET_multiplicity6
# define DEG 6
#endif

#include "lang_titles.inc"  

\text{roots=shuffle(wims(makelist x for x=-20 to 20))}
\integer{mult=randint(1 .. DEG)}
\text{rootm=\roots[1]}
\text{roots=item(1 .. DEG,wims(makelist \rootm for x=1 to \mult),item(2..-1,\roots))}
\text{poly=wims(makelist (x - y) for y in \roots)}
\function{poly=randitem(1,-1,2,-2,3,-3)*wims(translate internal , to * in \poly)}
\function{dev=pari(\poly)}

#include "lang.inc"

\statement{\name_statement[1] \(\rootm\) \name_statement[2].
	   \name_statement2.
<div class="wimscenter">
\(P(x) = \dev)
</div>
}

\answer{\name_answer \(\rootm\)}{\mult}{type=number}
