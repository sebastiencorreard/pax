target=oefposer1
#include "author.inc"
#define NUM 1
#include "lang_titles.inc"

\text{sg=random(+,-)}

\if{\sg=+}{
     \integer{l1=randint(1..3)}
     \if{\l1=3}{\integer{l2=randint(1..2)}}{\integer{l2=3}}}
          {\integer{l1=3}
           \integer{l2=randint(1..2)}}

\text{chif1=}
\for{i=1 to 3-\l1 }
    {\text{chif1=wims(append item 0 to \chif1)}}
\for{i=1 to \l1 }
    {\integer{chif=randint(1..9)}
     \text{chif1=wims(append item \chif to \chif1)}}

\text{chif2=}
\for{i=1 to 3-\l2 }
    {\text{chif2=wims(append item 0 to \chif2)}}
\for{i=1 to \l2 }
    {\integer{chif=randint(1..9)}
     \text{chif2=wims(append item \chif to \chif2)}
     }
\text{nb1=}
\text{nb2=}
\for{i=1 to 3}{\text{nb1=\nb1\chif1[\i]}}
\for{i=1 to 3}{\text{nb2=\nb2\chif2[\i]}}
\integer{nb1=\nb1}
\integer{nb2=\nb2}

\integer{ltr=6}
\text{size=25x35x1}

#include "lang.inc"
\statement{
\name_enonce[1] \nb1 \sg \nb2. \name_enonce[2].
<div class="wims_instruction">\name_warning</div>
<table class="wimscenter wimsnoborder">
  <tr>
    \for{a=1 to 2}{<td></td>}
    \for{a=1 to 3}{<td><span class="larger">\embed{r\a,\size}</span></td>}
    <td></td>
  </tr><tr>
    <td>\embed{r4}</td><td></td>
    \for{a=5 to 7}{<td><span class="larger">\embed{r\a,\size}</span></td>}
    <td></td>
  </tr><tr>
    <td colspan="\ltr"><hr></td>
  </tr>
</table>
}
\answer{}{\chif1[1];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\chif1[2];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\chif1[3];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\sg;+,-}{type=clickfill}
\answer{}{\chif2[1];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\chif2[2];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
\answer{}{\chif2[3];0,1,2,3,4,5,6,7,8,9}{type=clickfill}
