target=add

#include "header.inc"
#include "lang_titles.inc"

\title{TITLE}
\title_it{TITLE_it}
\integer{b=randint(3..9)}
\integer{b1=\b-1}
\text{n1=randint(0..\b1),randint(0..\b1),randint(0..\b1)}
\text{n2=randint(0..\b1),randint(0..\b1),randint(0..\b1)}
\integer{d0=pari(lift(Mod(\n1[3]+\n2[3],\b)))}
\integer{r0=floor((\n1[3]+\n2[3])/\b)}
\integer{d1=pari(lift(Mod(\n1[2]+\n2[2]+\r0,\b)))}
\integer{r1=pari(floor((\n1[2]+\n2[2]+\r0)/\b))}
\integer{d2=pari(lift(Mod(\n1[1]+\n2[1]+\r1,\b)))}
\integer{d3=floor((\n1[1]+\n2[1]+\r1)/\b)}
\text{\N1=wims(items2words \n1)}
\text{\N2=wims(items2words \n2)}

#include "lang.inc"

\statement{<div class="spacer">\name_statement
  \((\N1)_{\b}\) \name_and \((\N2)_{\b}\) :
  </div>
<table class="wimscenter wimsnoborder">
  <tr>
    <td></td><td>\n1[1]</td><td>\n1[2]</td><td>\n1[3]</td>
  </tr><tr>
    <td>+</td><td>\n2[1]</td><td>\n2[2]</td><td>\n2[3]</td>
  </tr><tr>
  <td colspan="4"><hr></td>
  </tr><tr>
    <td>\embed{reply 4,5}</td><td>\embed{reply 3,5}</td><td>
  \embed{reply 2,5}</td><td>\embed{reply 1,5}</td>
  </tr>
</table>
}

\answer{digits0}{\d0}{type=default}
\answer{digits1}{\d1}{type=default}
\answer{digits2}{\d2}{type=default}
\answer{digits3}{\d3}{type=default}
