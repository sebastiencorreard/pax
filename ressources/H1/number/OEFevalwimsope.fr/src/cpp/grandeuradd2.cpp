target=oefgrandeuradd2
#include "author.inc"
#define NUM 2
#include "lang_titles.inc"
#include "lang.inc"

\text{list1=1,10,100,1 000,10 000,100 000,1 000 000}
\text{list2=1,0.1,0.01,0.001}
\text{list3=0.001,0.01,0.1,1,10,100,1000}

\integer{g=randint(1..3)}
\text{e=0,0,0,0,0,0,0,0,0,0}
\for{i=1 to 6}{
  \text{f=randint(0-\g..3-\g)}
  \text{e=wims(append item \f to \e)}}
\integer{e=randomitem(\e)}
\real{nb1=randint(501..4999)/10^(\g+3)}
\real{nb2=randint(501..4999)/10^(\g+\e+3)}
\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}
\text{nb1=wims(translate . to , in \nb1)}
\text{nb2=wims(translate . to , in \nb2)}
\text{rep1=\list2[\g+1]}
\text{rep2=\list2[\e+\g+1]}

\text{list=\list2}
\text{sg= +}
\text{size=120x50}
\statement{
\name_enonce:
<table class="wimscenter wimsnoborder">
  <tr>
    <td></td>
    <td><span class="larger">\nb1</span></td>
    <td><span class="larger">\sg</span></td>
    <td><span class="larger">\nb2</span></td>
  </tr><tr>
    <th>\name_enonce2[1]</th>
    <td><span class="larger">\embed{r1,\size}</span></td>
    <td><span class="larger">\sg</span></td>
    <td><span class="larger">\embed{r2,\size}</span></td>
  </tr>
</table>
<div class="wims_instruction">\name_warning</div>}
\answer{}{\rep1;\list}{type=clickfill}
\answer{}{\rep2;\list}{type=clickfill}
