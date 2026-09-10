target=oefaxesym2
#define NUM 2
#include "lang_titles.inc"
#include "lang.inc"

#include "author.inc"
\keywords{symmetry}
#include "dessin.inc"
\text{n=shuffle(16)}
\text{rep1=row(\n[1],\fig)}
\text{rep2=row(\n[2],\fig)}
\text{rep3=row(\n[3],\fig)}
\statement{
<ol>
<li><img src="\rep1[1]" alt="">
\name_stat \rep1[2] : \embed{r1}
</li><li><img src="\rep2[1]" alt="">
\name_stat \rep2[2] : \embed{r2}
</li><li><img src="\rep3[1]" alt="">
\name_stat \rep3[2] : \embed{r3}
</li></ol>}

\answer{}{\rep1[3];\name_choice}{type=menu}
\answer{}{\rep2[3];\name_choice}{type=menu}
\answer{}{\rep3[3];\name_choice}{type=menu}

