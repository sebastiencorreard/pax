target=oefmediat1
#include "lang.inc"
#include "author.inc"
#define NUM 1
#include "lang_titles.inc"
\keywords{perpendicular_bisector}
\integer{a=randint(0..5)*2}
\text{enonc1=row(\a+1,\enonc)}
\text{enonc2=row(\a+2,\enonc)}

\statement{
\name_stat:
<ul class="inline">
<li>\embed{r1,180x30}</li>
<li>\embed{r2,180x30}</li>
</ul>}

\answer{}{\enonc1;\enonc1}{type=dragfill}{option=shuffle}
\answer{}{\enonc2;\enonc2}{type=dragfill}{option=shuffle}
