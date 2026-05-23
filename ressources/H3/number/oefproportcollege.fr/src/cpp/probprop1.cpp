target=oefprobprop1euro oefprobprop1
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
\precision{10000}
\integer{a=randint(1..10)}
\text{t=row(\a,\t)}

\text{b=randint(1..2)}
\if{\b=1}{\text{rep=\t[6]}}{\text{rep=\t[3]}}
\text{reps=\t[4],\t[5],\t[7],\t[8]}

\statement{\t[1]
<p>\name_enonce:</p>
\if{\b=1}{<table class="wimscenter wimsborder"><tr>
<td style="width:160px;">\embed{r1,150x40}</td>
<td style="width:120px;">\t[11]</td>
<td>\embed{r2}</td>
<tr><td> \t[3] </td>
<td>\t[9]</td>
<td>\embed{r3}</td></tr>
</table>}
{<table class="wimscenter wimsborder"><tr>
<td style="width:160px;">\t[6]</td>
<td style="width:120px;">\t[11]</td>
<td>\embed{r2,150x40}</td>
<tr><td>\embed{r1}  </td>
<td>\t[9]</td>
<td>\embed{r3}</td></tr>
</table>}
}

\answer{}{\rep;\reps}{type=dragfill}{option=shuffle}
\answer{}{\t[12];\t[11]}{type=dragfill}{option=shuffle}
\answer{}{\t[10];\t[9]}{type=dragfill}{option=shuffle}
