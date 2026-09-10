target=oefcercle1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{a=randint(1..4)}
\text{enonc=row(\a,\enonc)}

\statement{
\name_statement:
<div class="spacer">\embed{r1,150x40}</div>
}

\answer{}{\enonc;\enonc}{type=dragfill}{option=shuffle}
