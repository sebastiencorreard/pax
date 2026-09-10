target=oefgrandeurdiff4
#include "author.inc"
#define NUM 4
#include "lang_titles.inc"
#include "lang.inc"

\text{list=10,100,1 000,10000,100000,1000000,10000000}
\integer{g=randint(2..6)}
\integer{ee=0}
\integer{gg=0}

\text{e=0,0,0}
\for{i=1 to 8}{
  \text{f=randint(1-\g..6-\g)}
  \text{e=wims(append item \f to \e)}}
\integer{e=randomitem(\e)}

\integer{nb1=randint(110000..890000)}
\integer{nb2=randint(\nb1+10000..990000)}
\integer{nb1=\nb1*10^(\g-5)}
\integer{nb2=\nb2*10^(\g+\e-5)}

\text{c1=wims(char 1 to 2 of \nb1)}
\text{cc1=wims(char 3  to 3 of \nb1)}

\if{\cc1>4}{
  \if{\c1=99}{
    \integer{gg=1}
    \integer{c1=100}}
  {\integer{c1=\c1+1}}}
\text{list1=}
\for{i=1 to 7}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c1/10}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list1=wims(append item \v to \list1)}
}

\text{c2=wims(char 1 to 2 of \nb2)}
\text{cc2=wims(char 3 to 3 of \nb2)}
\if{\cc2>4}{
  \if{\c2=99}{\integer{gg=1}\integer{c2=100}}
   {\integer{c2=\c2+1}}}
\text{list2=}
\for{i=1 to 7}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c2/10}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list2=wims(append item \v to \list2)}}

\real{z=0}
\if{\nb1<\nb2}{
  \real{z=\nb1}
  \real{nb1=\nb2}
  \real{nb2=\z}}

\if{\z=0}{
  \text{rep1=\list1[\g+\gg]}
  \text{rep2=\list2[\e+\g+\ee]}}{
  \text{rep2=\list1[\g+\gg]}
  \text{rep1=\list2[\e+\g+\ee]}}

\integer{rep=\rep1-\rep2}

\text{c3=wims(char 1 to 2 of \rep)}
\text{cc3=wims(char 3  to 3 of \rep)}

\if{\cc3>4}{
   \if{\c3=99}{\integer{gg=1}
             \integer{c3=100}}
           {\integer{c3=\c3+1}}}

\text{list3=}
\for{i=1 to 7}{
     \text{v=item(\i,\list)}
     \real{v=\v*\c3/10}
     \text{v=slib(numeration/ecriturenombre \v)}
     \text{list3=wims(append item \v to \list3)}}

\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}

\integer{r=floor(lg(\rep))}
\text{rep3=\list3[\r]}

\text{sg= -}

\text{size=100x30}
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
<div class="wims_instruction">\name_warning</div>
<div class="spacer">\name_enonce2[2]:\embed{r3,\size}</div>
}

\answer{}{\rep1;\list1}{type=clickfill}
\answer{}{\rep2;\list2}{type=clickfill}
\answer{}{\rep3;\list3}{type=clickfill}
