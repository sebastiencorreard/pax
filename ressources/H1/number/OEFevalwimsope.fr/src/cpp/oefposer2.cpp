target=oefposer2
#include "author.inc"
#define NUM 2
#include "lang_titles.inc"

\text{sg=+}
\integer{l1=3}
\integer{l2=3}
\integer{ltr=max(\l1,\l2)+2}
\text{row1=wims(makelist <td></td> for x=3+\l1 to \ltr)}
\text{row2=wims(makelist <td></td> for x=3+\l2 to \ltr)}
\text{row1=wims(items2words \row1)}
\text{row2=wims(items2words \row2)}
\integer{v=randint(2..\l1-1)}
\integer{e=\v-1}
\integer{d=\l1-\v}
\text{chif1=}
\for{i=1 to \e }
    {\integer{chif=randint(1..9)}
     \text{chif1=wims(append item \chif to \chif1)}
}
\text{chif1=wims(append item &#44; to \chif1)}
\integer{f=randint(0..2)}
\if{\f=0}{\for{i=1 to \d}{\text{chif1=wims(append item 0 to \chif1)}}}
\if{\f=1}{ \integer{chif=randint(1..9)}
           \text{chif1=wims(append item \chif to \chif1)}
           \for{i=1 to \d-1}{\text{chif1=wims(append item 0 to \chif1)}}}
\if{\f=2}{\for{i=1 to \d-1}{ \integer{chif=randint(1..9)}
                     \text{chif1=wims(append item \chif to \chif1)}}
                     \text{chif1=wims(append item 0 to \chif1)}}
\text{chif2=}
\if{\v=2}{\integer{chif=randint(1..9)}
           \text{chif2=wims(append item 0 to \chif2)}}
\if{\v=3}{\integer{chif=random(0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9)}
           \text{chif2=wims(append item \chif to \chif2)}
           \integer{chif=randint(1..9)}
           \text{chif2=wims(append item \chif to \chif2)}}
\if{\v=4}{ \text{chif2=wims(append item 0 to \chif2)}
           \integer{chif=random(0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9)}
           \text{chif2=wims(append item \chif to \chif2)}
           \integer{chif=randint(1..9)}
           \text{chif2=wims(append item \chif to \chif2)}}
\text{chif2=wims(append item &#44; to \chif2)}
\for{i=1 to \d }
    {\integer{chif=randint(1..9)}
     \text{chif2=wims(append item \chif to \chif2)}
     }
\text{nb1=}
\text{nb2=}
\for{i=1 to 5}{
   \if{\i<>\v}{\text{nb1=\nb1\chif1[\i]}}}
\for{i=1 to 5}{
   \if{\i<>\v}{\text{nb2=\nb2\chif2[\i]}}}
\real{nb1=\nb1/10^\d}
\real{nb2=\nb2/10^\d}
\text{nb1=wims(replace internal . by , in \nb1)}
\text{nb2=wims(replace internal . by , in \nb2)}
\text{size=25x35x1}
#include "lang.inc"
\statement{
\name_enonce[1] \nb1 \sg \nb2. \name_enonce[2]:
<div class="wims_instruction">\name_warning</div>
<table class="wimscenter wimsnoborder">
 <tr>
\for{a=1 to 2}{<td></td>}
\for{a=1 to \l1}{<td ><span class="larger">\embed{r\a,\size}</span></td>}
\row1</tr>
 <tr>
 <td>\sg</td>
<td></td>
\for{a=\l1+1 to \l1+\l2}{<td><span class="larger">\embed{r\a,\size}</span></td>}
\row2</tr>
 <tr>
  <td colspan="\ltr"><hr></td>
 </tr>
 </table>
}
\answer{}{\chif1[1];0,1,2,3,4,5,6,7,8,9,&#44;}{type=clickfill}
\answer{}{\chif1[2];0,1,2,3,4,5,6,7,8,9,&#44;}{type=clickfill}
\answer{}{\chif1[3];0,1,2,3,4,5,6,7,8,9,&#44;}{type=clickfill}
\answer{}{\chif2[1];0,1,2,3,4,5,6,7,8,9,&#44;}{type=clickfill}
\answer{}{\chif2[2];0,1,2,3,4,5,6,7,8,9,&#44;}{type=clickfill}
\answer{}{\chif2[3];0,1,2,3,4,5,6,7,8,9,&#44;}{type=clickfill}
