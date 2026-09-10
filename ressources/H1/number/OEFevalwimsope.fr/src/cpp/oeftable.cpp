target=oeftable1 oeftable2 oeftable3 oeftable4 oeftable5
#include "author.inc"

#if defined TARGET_oeftable1
# define NUM 1
\text{a=3,4,5,6,7,8,9}
\text{b=shuffle(\a)}
\text{a=shuffle(\a)}
\text{a=item(1..3,\a)}
\text{b=item(1..3,\b)}
\text{res=}
\for{h=1 to 3}{
  \for{i=1 to 3}{
    \integer{c=\a[\i]+\b[\h]}
    \text{res=wims(append item \c to \res)}
}}
#endif

#if defined TARGET_oeftable2
# define NUM 2
\text{b=15,16,17,18,19,25,26,27,28,29}
\text{b=shuffle(\b)}
\text{a=15,16,17,18,19,35,36,37,38,39}
\text{a=shuffle(\a)}
\text{a=item(1..3,\a)}
\text{b=item(1..3,\b)}
\text{res=}
\for{h=1 to 3}{
  \for{i=1 to 3}{
    \integer{c=\a[\i]+\b[\h]}
    \text{res=wims(append item \c to \res)}
}}
#endif

#if defined TARGET_oeftable3
# define NUM 1
\text{b=2,3,4,5,6,7,8,9}
\text{b=shuffle(\b)}
\text{a=2,3,4,5}
\text{a=shuffle(\a)}
\text{a=item(1..3,\a)}
\text{b=item(1..3,\b)}
\text{res=}
\for{h=1 to 3}{
\for{i=1 to 3}{
\integer{c=\a[\i]*\b[\h]}
\text{res=wims(append item \c to \res)}
}}
#endif

#if defined TARGET_oeftable4
# define NUM 2
\text{b=2,3,4,5,6,7,8,9}
\text{b=shuffle(\b)}
\text{a=6,7,8,9}
\text{a=shuffle(\a)}
\text{a=item(1..3,\a)}
\text{b=item(1..3,\b)}
\text{res=}
\for{h=1 to 3}{
  \for{i=1 to 3}{
    \integer{c=\a[\i]*\b[\h]}
    \text{res=wims(append item \c to \res)}
}}
#endif

#if defined TARGET_oeftable5
# define NUM 3
\text{b=23,24,25,16,17,18,19}
\text{b=shuffle(\b)}
\text{a=2,3,4,5}
\text{a=shuffle(\a)}
\text{a=item(1..3,\a)}
\text{b=item(1..3,\b)}
\text{res=}
\for{h=1 to 3}{
  \for{i=1 to 3}{
    \integer{c=\a[\i]*\b[\h]}
    \text{res=wims(append item \c to \res)}
}}
#endif
#include "lang_titles.inc"
#include "lang.inc"

\statement{
\name_enonce \enonc[1] :
<table class="wimscenter wimsborder">
 <tr>
  <th>\enonc[2]</th>
  \for{e=1 to 3}{<th>\a[\e]</th>}
 </tr><tr>
  <th>\b[1]</th>
  <td>\embed{r1,2}</td><td>\embed{r2,2}</td>
  <td>\embed{r3,2}</td>
 </tr><tr>
  <th>\b[2] </th>
  <td>\embed{r4,2}</td><td>\embed{r5,2}</td>
  <td>\embed{r6,2}</td>
 </tr><tr>
  <th>\b[3]</th>
  <td>\embed{r7,2}</td>
  <td>\embed{r8,2}</td>
  <td>\embed{r9,2}</td>
 </tr>
</table>}

\answer{}{\res[1]}
\answer{}{\res[2]}
\answer{}{\res[3]}
\answer{}{\res[4]}
\answer{}{\res[5]}
\answer{}{\res[6]}
\answer{}{\res[7]}
\answer{}{\res[8]}
\answer{}{\res[9]}
