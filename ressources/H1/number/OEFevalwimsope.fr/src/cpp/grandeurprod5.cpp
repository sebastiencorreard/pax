target=oefgrandeurprod5
#define NUM 5
#include "lang_titles.inc"
#include "lang.inc"
#include "author.inc"

\precision{10000000000}

\text{list=1 000 000 000,100 000 000,10 000 000,1 000 000,100 000,10 000,1 000,100,10,1,0.1,0.01,0.001,0.000 1}
\integer{listcnt=items(\list)}
\integer{g=randint(4..8)}
\integer{ee=0}
\integer{gg=0}

\text{e=0,0,0}
\for{i=1 to 8}{
  \text{f=randint(4-\g..8-\g)}
  \text{e=wims(append item \f to \e)}}
\integer{e=randomitem(\e)}

\real{nb1=randint(1100..9900)}
\real{nb2=randint(1100..9900)}

\text{c1=wims(char 1 to 1 of \nb1)}
\text{cc1=wims(char 2 to 2 of \nb1)}
\if{\cc1>4}{
  \if{\c1=9}{
    \integer{gg=1}
    \integer{c1=1}}
  {\integer{c1=\c1+1}}}
\text{list1=}
\for{i=1 to \listcnt}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c1}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list1=wims(append item \v to \list1)}}

\text{c2=wims(char 1 to 1 of \nb2)}
\text{cc2=wims(char 2 to 2 of \nb2)}
\if{\cc2>4}{
  \if{\c2=9}{
    \integer{ee=1}
    \integer{c2=1}}
  {\integer{c2=\c2+1}}}
\text{list2=}
\for{i=1 to \listcnt}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c2}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list2=wims(append item \v to \list2)}}

\real{nb1=\nb1/10^(\g-5)}
\real{nb2=\nb2/10^(\g+\e-5)}

\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb1=wims(translate . to , in \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}
\text{nb2=wims(translate . to , in \nb2)}

\text{c3=pari(\c1*\c2)}
\integer{c3=\c1*\c2}
\text{list3=}
\for{i=1 to \listcnt}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c3/10}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list3=wims(append item \v to \list3)}}

\text{rep1=\list1[\g-\gg+2]}
\text{rep2=\list2[\e+\g-\ee+2]}
\text{rep3=\list3[2*\g+\e-\gg-\ee-9+2]}
\text{rep1=wims(translate . to , in \rep1)}
\text{rep2=wims(translate . to , in \rep2)}
\text{rep3=wims(translate . to , in \rep3)}
\text{sg=\times}

\text{size=10}

\statement{\name_enonce
<table class="wimscenter wimsnoborder">
  <tr>
    <td></td>
    <td><span class="larger">\nb1</span></td>
    <td><span class="larger">\(\sg)</span></td>
    <td><span class="larger">\nb2</span></td>
  </tr><tr>
    <th>\name_enonce2[1]</th>
    <td><span class="larger">\embed{r1,\size}</span></td>
    <td><span class="larger">\(\sg)</span></td>
    <td><span class="larger">\embed{r2,\size}</span></td>
  </tr>
</table>
\name_enonce2[2]:
\embed{r3,\size}
<div class="wims_instruction">\name_warning</div>}
\answer{}{\rep1}{type=raw}
\answer{}{\rep2}{type=raw}
\answer{}{\rep3}{type=raw}
