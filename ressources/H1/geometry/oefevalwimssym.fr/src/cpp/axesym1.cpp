target=oefaxesym1
#define NUM 1
#include "lang_titles.inc"
#include "author.inc"
#include "lang.inc"
\keywords{symmetry}
#include "dessin.inc"
\integer{n=randint(1..16)}
\text{rep=row(\n,\fig)}

\statement{
<div class="wimscenter">
    <img src="\rep[1]" alt="">
</div>
\name_stat \rep[2] : \embed{r1}.
}

\answer{}{\rep[3];\name_choice}{type=menu}
