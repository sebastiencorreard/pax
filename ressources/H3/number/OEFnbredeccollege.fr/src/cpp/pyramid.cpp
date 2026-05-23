target=oefpyramid1 oefpyramid2 oefpyramid3 oefpyramid4 oefpyramid5
\langage{fr}
#include "author.inc"
\format{html}
\precision{100000000}
#include "lang_titles.inc"
#include "lang.inc"
#if defined TARGET_oefpyramid5
\text{e=randint(1..9)}
\text{f=0.1,0.01,0.001}
\text{f=shuffle(\f)}
\text{g=random(0.9,0.09,0.009)}
\text{v=\e,\f[1],\f[2],\g}
#else
\text{confparm1=\confparm1=? 1}
\text{champ=wims(record \confparm1 of src/generateur)}
\text{l1=row(2,\champ)}
\text{l2=row(3,\champ)}
\integer{k=randint(1..3)}
\text{v=}
\for{i=1 to \k}{
    \real{a=(randint(0..\l1[1])randint(0..\l1[2])randint(1..\l1[3]))/\l2[1]}
    \text{v=wims(append item \a to \v)}
 }
\for{i=1 to 4-\k}{
    \real{a=(randint(0..\l1[4])randint(0..\l1[5])randint(1..\l1[6]))/\l2[2]}
    \text{v=wims(append item \a to \v)}
 }
#endif
\text{v=shuffle(\v)}
\real{a=\v[1]+\v[2]}
\real{b=\v[2]+\v[3]}
\real{c=\v[3]+\v[4]}
\real{d=\a+\b}
\real{e=\b+\c}
\real{f=\d+\e}
\text{v=\v[1],\v[2],\v[3],\v[4],\a,\b,\c,\d,\e,\f}

\statement{
<p>\name_inst</p>
#if defined TARGET_oefpyramid1
<table class="wimscenter wimsborder">
<tr><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\v[10]</td>
<td></td><td></td><td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r5,5}</td><td colspan="4" style="background-color:#FFFF00">\v[9]</td>
<td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r3,5}</td><td colspan="4" style="background-color:#FFFF00">\v[6]</td>
<td colspan="4" style="background-color:#FFFF00">\embed{r4,5}</td><td></td><td></td></tr>
<tr><td colspan="4" style="background-color:#FFFF00">\embed{r1,5}</td><td colspan="4" style="background-color:#FFFF00">\v[2]</td>
<td colspan="4" style="background-color:#FFFF00">\v[3]</td><td colspan="4" style="background-color:#FFFF00">\embed{r2,5}</td></tr>
</table>
#endif
#if defined TARGET_oefpyramid2
<table class="wimscenter wimsborder">
<tr><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r6,5}</td>
<td></td><td></td><td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\v[8]</td><td colspan="4" style="background-color:#FFFF00">\embed{r5,5}</td>
<td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r4,5}</td><td colspan="4" style="background-color:#FFFF00">\v[6]</td>
<td colspan="4" style="background-color:#FFFF00">\v[7]</td><td></td><td></td></tr>
<tr><td colspan="4" style="background-color:#FFFF00">\embed{r1,5}</td><td colspan="4"  style="background-color:#FFFF00">\embed{r2,5}</td>
<td colspan="4" style="background-color:#FFFF00">\v[3]</td><td colspan="4"  style="background-color:#FFFF00">\embed{r3,5}</td></tr>
</table>
#endif
#if defined TARGET_oefpyramid3
<table class="wimscenter wimsborder">
<tr><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\v[10]</td>
<td></td><td></td><td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r6,5}</td><td colspan="4" style="background-color:#FFFF00">\v[9]</td>
<td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r4,5}</td><td colspan="4" style="background-color:#FFFF00">\embed{r5,5}</td>
<td colspan="4" style="background-color:#FFFF00">\v[7]</td><td></td><td></td></tr>
<tr><td colspan="4"   style="background-color:#FFFF00">\embed{r1,5}</td><td colspan="4"  style="background-color:#FFFF00">\v[2]</td>
<td colspan="4"  style="background-color:#FFFF00">\embed{r2,5}</td><td colspan="4"  style="background-color:#FFFF00">\embed{r3,5}</td></tr>
</table>
#endif
#if defined TARGET_oefpyramid4
<table class="wimscenter wimsborder">
<tr><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\v[10]</td>
<td></td><td></td><td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r5,5}</td><td colspan="4" style="background-color:#FFFF00">\embed{r6,5}</td>
<td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r3,5}</td><td colspan="4" style="background-color:#FFFF00">\v[6]</td>
<td colspan="4" style="background-color:#FFFF00">\embed{r4,5}</td><td></td><td></td></tr>
<tr><td colspan="4" style="background-color:#FFFF00">\v[1]</td><td colspan="4" style="background-color:#FFFF00">\embed{r1,5}</td>
<td colspan="4" style="background-color:#FFFF00">\v[3]</td><td colspan="4" style="background-color:#FFFF00">\embed{r2,5}</td></tr>
</table>
#endif
#if defined TARGET_oefpyramid5
<table class="wimscenter wimsborder">
<tr><td></td><td></td><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\v[10]</td>
<td></td><td></td><td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r6,5}</td><td colspan="4" style="background-color:#FFFF00">\v[9]</td>
<td></td><td></td><td></td><td></td></tr>
<tr><td></td><td></td><td colspan="4" style="background-color:#FFFF00">\embed{r4,5}</td>
<td colspan="4" style="background-color:#FFFF00">\embed{r5,5}</td>
<td colspan="4" style="background-color:#FFFF00">\v[7]</td><td></td><td></td></tr>
<tr><td colspan="4" style="background-color:#FFFF00">\embed{r1,5}</td><td colspan="4" style="background-color:#FFFF00">\v[2]</td>
<td colspan="4" style="background-color:#FFFF00">\embed{r2,5}</td>
<td colspan="4" style="background-color:#FFFF00">\embed{r3,5}</td></tr>
</table>
#endif
<p>\name_statement</p>
<div class="wims_instruction">
\name_decimal
</div>
}
#if defined TARGET_oefpyramid4
\answer{}{\v[2]}{type=numeric}
\answer{}{\v[4]}{type=numeric}
\answer{}{\v[5]}{type=numeric}
\answer{}{\v[7]}{type=numeric}
\answer{}{\v[8]}{type=numeric}
\answer{}{\v[9]}{type=numeric}
#else
\answer{}{\v[1]}{type=numeric}
# if defined TARGET_oefpyramid2
\answer{}{\v[2]}{type=numeric}
# endif
# if defined TARGET_oefpyramid3 || defined TARGET_oefpyramid5
\answer{}{\v[3]}{type=numeric}
# endif
\answer{}{\v[4]}{type=numeric}
\answer{}{\v[5]}{type=numeric}
#if defined TARGET_oefpyramid3 || defined TARGET_oefpyramid5
\answer{}{\v[6]}{type=numeric}
\answer{}{\v[8]}{type=numeric}
# endif
# if defined TARGET_oefpyramid1
\answer{}{\v[7]}{type=numeric}
\answer{}{\v[8]}{type=numeric}
# endif
# if defined TARGET_oefpyramid2
\answer{}{\v[9]}{type=numeric}
\answer{}{\v[10]}{type=numeric}
# endif
#endif
