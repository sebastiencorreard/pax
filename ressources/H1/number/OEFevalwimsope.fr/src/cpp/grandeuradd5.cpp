target=oefgrandeuradd5
#include "author.inc"
#define NUM 5
#include "lang_titles.inc"
#include "lang.inc"

\text{list=0.001,0.01,0.1,1,10,100,1 000,10000}
\integer{g=randint(1..7)}
\integer{ee=0}
\integer{gg=0}
\text{e=0,0,0,0,0,0,0,0,0,0}
\for{i=1 to 8}{
  \text{f=randint(1-\g..7-\g)}
  \text{e=wims(append item \f to \e)}}
\integer{e=randomitem(\e)}

\real{nb1=randint(1100..9900)}
\real{nb2=randint(1100..9900)}

\text{c1=wims(char 1 to 1 of \nb1)}
\text{cc1=wims(char 2 to 2 of \nb1)}
\if{\cc1>4}{
  \if{\c1=9}{\integer{gg=1}
    \integer{c1=1}}
  {\integer{c1=\c1+1}}}
\text{list1=}
\for{i=1 to 8}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c1}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list1=wims(append item \v to \list1)}}

\text{c2=wims(char 1 to 1 of \nb2)}
\text{cc2=wims(char 2  to 2 of \nb2)}
\if{\cc2>4}{
  \if{\c2=9}{
    \integer{ee=1}
    \integer{c2=1}}
  {\integer{c2=\c2+1}}}
\text{list2=}
\for{i=1 to 8}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c2}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list2=wims(append item \v to \list2)}}

\real{nb1=\nb1*10^(\g-7)}
\real{nb2=\nb2*10^(\g+\e-7)}

\text{nb1=slib(numeration/ecriturenombre \nb1)}
\text{nb1=wims(translate . to , in \nb1)}
\text{nb2=slib(numeration/ecriturenombre \nb2)}
\text{nb2=wims(translate . to , in \nb2)}
\text{rep1=\list1[\g+\gg]}
\text{rep2=\list2[\e+\g+\ee]}
\real{rep=\rep1+\rep2}

\integer{i=1}
\integer{c3=0}
\while{\c3=0 or \c3=.}{
  \text{c3=wims(char \i to \i of \rep)}
  \text{cc3=wims(char \i+1  to \i+1 of \rep)}
  \text{i=\i+1}
}

\if{\cc3>4}{\integer{c3=\c3+1}}
\text{list3=}
\for{i=1 to 8}{
  \text{v=item(\i,\list)}
  \real{v=\v*\c3}
  \text{v=slib(numeration/ecriturenombre \v)}
  \text{list3=wims(append item \v to \list3)}
}

\if{\e=0 and \c1+\c2>9}{\integer{e=\e+1+\ee}}
\if{\e<0}{\text{rep3=\list3[\g+\gg]}}{\text{rep3=\list3[\e+\g+\ee+\gg]}}

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
<div class="wims_instruction">\name_warning</div>
<div class="spacer">\name_enonce2[2]\embed{r3,\size}.</div>
}

\answer{}{\rep1;\list1}{type=clickfill}
\answer{}{\rep2;\list2}{type=clickfill}
\answer{}{\rep3;\list3}{type=clickfill}
