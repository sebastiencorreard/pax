target=oefplusmoins1
\langage{fr}
#include "author.inc"
\format{html}
\precision{100000000}

#include "lang_titles.inc"
#include "lang.inc"
\text{op=-100,-10,-1,-0.1,-0.01,-0.001,+0.001,+0.01,+0.1,+1,+10,+100}
\text{flech=\(\longrightarrow\)}

\real{nb1=randint(1..999)/10^randint(1..3)}
\integer{r1=randint(4-log10(\nb1)..12)}
\text{rep1=\op[\r1]}
\real{nb2=\nb1+\op[\r1]}
\integer{r2=randint(4-log10(\nb2)..12)}
\text{rep2=\op[\r2]}
\real{nb3=\nb2+\op[\r2]}
\integer{r3=randint(4-log10(\nb3)..12)}
\text{rep3=\op[\r3]}
\real{nb4=\nb3+\op[\r3]}
\integer{r4=randint(4-log10(\nb4)..12)}
\text{rep4=\op[\r4]}
\real{nb5=\nb4+\op[\r4]}

\statement{
\name_stat:
<table class="wimscenter wimsborder">
<tr>
<td></td>
<td>\embed{r1,55x50}</td>
<td></td>
<td>\embed{r2}</td>
<td></td>
<td>\embed{r3}</td>
<td></td>
<td>\embed{r4}</td>
<td></td>
</tr><tr>
<td>\nb1</td>
<td>\flech</td>
<td>\nb2</td>
<td>\flech</td>
<td>\nb3</td>
<td>\flech</td>
<td>\nb4</td>
<td>\flech</td>
<td>\nb5</td></tr>
</table>
}

\answer{}{\rep1;\op}{type=clickfill}
\answer{}{\rep2;\op}{type=clickfill}
\answer{}{\rep3;\op}{type=clickfill}
\answer{}{\rep4;\op}{type=clickfill}
