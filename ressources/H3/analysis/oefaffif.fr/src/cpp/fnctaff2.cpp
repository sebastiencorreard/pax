target=fnctaff2
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\text{nom=randitem(f,g,h)}
\text{listn=wims(values v,-v for v=1 to 10)}
\text{listn=shuffle(\listn)}
\integer{abs1=\listn[1]}
\integer{abs2=\listn[2]}
\integer{abs3=\listn[3]}

\integer{a=random(-1,1)*random(1..10)}
\integer{b=random(1,-1)*random(1..10)}
\integer{c=random(1,-1)*random(1..10)}
\text{list=\a*(x)+(\b),\a*(x)^2+(\b)*(x)+(\c)}
\integer{ch=random(1,2)}
\function{funct=item(\ch,\list)}

\integer{ord1=evalue(\funct,x=\abs1)}
\integer{ord2=evalue(\funct,x=\abs2)}
\integer{ord3=evalue(\funct,x=\abs3)}
\text{good=item(\ch,\bad)}
\matrix{enonce=wims(replace internal FFFF by \(\nom\) in \name_enonce)}
\text{enonce=randrow(\enonce)}

\statement{\enonce.
<table class="wimscenter wimsborder">
  <tr>
    <th>x</th>
    <td>\(\abs1)</td>
    <td>\(\abs2)</td>
    <td>\(\abs3)</td>
  </tr><tr>
    <th>\(\nom (x)\)</th>
    <td>\(\ord1\)</td>
    <td>\(\ord2\)</td>
    <td>\(\ord3\)</td>
  </tr>
</table>
\(\nom\) \name_question?}

\choice{\name_answer}{\good}{\bad}
