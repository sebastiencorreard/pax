target=oeffairetabl5
#include "author.inc"
\precision{10000}
#if defined TARGET_oeffairetabl5
# define NUM 5
#endif
#include "lang_titles.inc"

\text{effs=randint(35..79)}
\for{j=1 to 8}{\integer{n=randint(35..79)}
\text{effs=\effs,\n}}
#include "lang.inc"
\statement{
\enonc
<p>
\name_question:
</p>
<table class="wimscenter wimsborder table-scroll">
 <tr><th></th><th>0 \name_header[1]</th><th>1 \name_header[1]</th>
 <th>2 \name_header[2]</th>
</tr><tr><th>0 \name_header[3]</th>
 \for{i=1 to 3}{<td>\embed{r\i,3}</td>}
</tr><tr><th>1 \name_header[3]</th>
 \for{i=4 to 6}{<td>\embed{r\i,3}</td>}
</tr><tr><th>2 \name_header[4]</th>
 \for{i=7 to 9}{<td>\embed{r\i,3}</td>}
</tr></table>
}
\answer{}{\effs[1]}{type=numeric}
\answer{}{\effs[2]}{type=numeric}
\answer{}{\effs[4]}{type=numeric}
\answer{}{\effs[7]}{type=numeric}
\answer{}{\effs[3]}{type=numeric}
\answer{}{\effs[5]}{type=numeric}
\answer{}{\effs[8]}{type=numeric}
\answer{}{\effs[9]}{type=numeric}
\answer{}{\effs[6]}{type=numeric}
