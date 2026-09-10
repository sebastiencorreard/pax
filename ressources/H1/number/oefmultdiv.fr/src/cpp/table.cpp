target=table

#include "author.inc"
#include "lang_title.inc"
#include "lang.inc"
\text{a=3,4,5,6,7,8,9}
\text{b=shuffle(\a)}
\text{a=shuffle(\a)}
\text{a=item(1..4,\a)}
\text{b=item(1..4,\b)}
\text{res=}
\for{h=1 to 4}{
\for{i=1 to 4}{
\integer{c=\a[\i]*\b[\h]}
\text{res=wims(append item \c to \res)}
}}

\integer{r=\a[1]*\b[3]}

\statement{
\name_enonce:
<table style="background-color:yellow" class="wimscenter wimsborder">
<tr><td> X </td> \for{e=1 to 4}{<td><span class="larger"> \a[\e]</span></td>} </tr>
<tr><td><span class="larger"> \b[1] </span></td><td>\embed{r1,2}</td><td> \embed{r2,2}</td>
<td>\embed{r3,2}</td><td> \embed{r4,2}</td></tr>
<tr><td><span class="larger"> \b[2] </span></td><td>\embed{r5,2}</td><td> \embed{r6,2}</td>
<td>\embed{r7,2}</td><td> \embed{r8,2}</td></tr>
<tr><td><span class="larger"> \b[3] </span></td><td>\embed{r9,2}</td><td> \embed{r10,2}</td>
<td>\embed{r11,2}</td><td> \embed{r12,2}</td></tr>
<tr><td><span class="larger"> \b[4] </span></td><td>\embed{r13,2}</td><td> \embed{r14,2}</td>
<td>\embed{r15,2}</td><td>\embed{r16,2}</td></tr>
</table>
}

\answer{}{\res[1]}
\answer{}{\res[2]}
\answer{}{\res[3]}
\answer{}{\res[4]}
\answer{}{\res[5]}
\answer{}{\res[6]}
\answer{}{\res[7]}
\answer{}{\res[8]}
\answer{}{\res[9]}
\answer{}{\res[10]}
\answer{}{\res[11]}
\answer{}{\res[12]}
\answer{}{\res[13]}
\answer{}{\res[14]}
\answer{}{\res[15]}
\answer{}{\res[16]}
