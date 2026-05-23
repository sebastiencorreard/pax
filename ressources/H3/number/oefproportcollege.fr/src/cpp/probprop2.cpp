target=oefprobprop2
\langage{fr}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format{html}
\language{fr}
\range{-5..5}
\precision{10000}

\integer{a=randint(1..10)}
\text{t=row(\a,\t)}
\if{\a=7}{\real{d=100}}{\real{d=1}}
\if{\a=3}{\real{d=3}}

\real{v1=randint(\t[13]..\t[14])*\t[15]}
\real{v2=randint(\t[16]..\t[17])*\t[18]}
\real{v=randint(\t[16]..\t[17])*\t[18]}
\if{\v=\v2}{\real{v=\v2+randint(1..3)*\d}}
\real{v=\v/\d}
\real{rep=\v1*\v2/\d}
\real{e=\d*\v}
\real{f=\v1*\v}

\statement{\name_enonce:
<p>\t[1] \e \t[2] \f \t[6] \t[3] \v2 \t[5] \t[4]</p>
<table class="wimscenter wimsborder">
<tr><th style="width:200px;">\t[10]</th>
<td style="width:120px;">\e</td>
<td style="width:120px;">\embed{r1,50x200}</td></tr>
<tr><th>\embed{r2,150x40}</th>
<td>\embed{r3,5}</td>
<td>\embed{r4,5}</td></tr>
</table>
<div><label for="reply5">\name_answer:</label> \embed{r5,5} \t[6].</div>
}

\answer{}{\v2}{type=numeric}
\answer{}{\t[7];\t[8],\t[9]}{type=dragfill}{option=shuffle}
\answer{}{\f}{type=numeric}
\answer{}{\rep}{type=numeric}
\answer{}{\rep}{type=numeric}
