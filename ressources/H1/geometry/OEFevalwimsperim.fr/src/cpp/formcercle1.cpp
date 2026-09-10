target=oefformcercle1
#include "author.inc"
\precision{10000}
\keywords{perimeter}
#include "lang_titles.inc"
#include "lang.inc"

\text{pi=3,3&#44;1,3&#44;14}
\integer{ch=randint(1..3)}
\text{pi=pi[\ch]}
\if{\ch=1}{\text{list=1,2,3,4,5,6,7,8,9}}
\if{\ch=2}{\text{list=2&#44;7,2&#44;9,3&#44;1,3&#44;3,3&#44;5,3&#44;7,3&#44;9}}
\if{\ch=3}{\text{list=3&#44;08,3&#44;12,3&#44;14,3&#44;16,3&#44;18,3&#44;21,3&#44;41}}
\if{\ch=1}{\integer{rp=3}}
\if{\ch=2}{\integer{rp=3}}
\if{\ch=3}{\integer{rp=3}}

\statement{\name_enonce \(pi\) : \embed{r1,\size}
}
\answer{}{\rp;\list}{type=menu}
