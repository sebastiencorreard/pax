target=mediane4
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{donnees=wims(randrecord src/stat2.don)}
\integer{eff=19+2*randint(1..5)}
\text{tmp=row(2,\donnees)}
\integer{min=randint(\tmp[1]..\tmp[2])}
\text{tmp=row(3,\donnees)}
\integer{max=\min+randint(4..6)}
\text{enonce=row(4,\donnees)}
\text{nameclass=row(5,\donnees)}
\text{et=wims(values v for v=\min to \max)}
\integer{nb=\max-\min+1}
\text{E=slib(generator \nb,\eff)}

\text{med=slib(stat/median [\et;\E])}

\statement{
  \enonce
  <table class="wimscenter wimsborder">
   <tr>
    <th>\nameclass</th>
    \for{l=1 to \nb}{<th>\et[\l]</th>}
   </tr><tr>
    <td>\name_head[1]</td>
    \for{l=1 to \nb}{<td>\E[\l]</td>}
   </tr>
  </table>
  \name_enonce
  }

\answer{\name_head[2]}{\med}{type=numexp}
