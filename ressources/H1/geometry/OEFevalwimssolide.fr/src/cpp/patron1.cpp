target=oefpatron1
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{reps=\name_reps}
\integer{rep=2}

\statement{
\name_enonce[1;],
<ul>
<li>\name_enonce[2;1], \embed{r1} \name_enonce[2;2]
</li><li>\name_enonce[3;] \embed{r2}.
</li><li>\name_enonce[4;],
</li><li>\name_enonce[5;]
</li></ul>
}
\answer{}{6;1,2,3,4,5,6,7,8,9}{type=menu}
\answer{}{\rep;\reps}{type=menu}{option=shuffle}
