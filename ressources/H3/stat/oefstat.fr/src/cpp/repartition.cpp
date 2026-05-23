target=repartition
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

#include "repartition.inc"

\statement{<div class="wims_question">
\name_enonce1[1] \effc5 name_enonce1[2]
<table class="wimscenter wimsborder">
<tr><th>\name_head[1]</th>
<td>\(0\leq N <4 \)</td>
<td>\(4\leq N <8 \)</td>
<td>\(8\leq N <12 \)</td>
<td>\(12\leq N <16 \)</td>
<td>\(16\leq N \leq 20 \)</td>
</tr>
<tr><th>\name_head[2]</th>
<td>\eff1</td>
<td>\eff2</td>
<td>\eff3</td>
<td>\eff4</td>
<td>\eff5</td>
</tr>
<tr><th>\name_head[3]</th>
<td>\embed{reply 1,5} </td>
<td>\embed{reply 2,5} </td>
<td>\embed{reply 3,5} </td>
<td>\embed{reply 4,5} </td>
<td>\embed{reply 5,5} </td>
</tr>
<tr><th>\name_head[4] (%)</th>
<td>\embed{reply 6,5} </td>
<td>\embed{reply 7,5} </td>
<td>\embed{reply 8,5} </td>
<td>\embed{reply 9,5} </td>
<td>\embed{reply 10,5} </td>
</tr>
</table>
</div>
<div class="wims_instruction">\name_inst</div>
}

\answer{\name_head[3]}{\effc1}{type=numeric}
\answer{\name_head[3]}{\effc2}{type=numeric}
\answer{\name_head[3]}{\effc3}{type=numeric}
\answer{\name_head[3]}{\effc4}{type=numeric}
\answer{\name_head[3]}{\effc5}{type=numeric}

\answer{\name_head[4]}{\freq1}{type=numeric}
\answer{\name_head[4]}{\freq2}{type=numeric}
\answer{\name_head[4]}{\freq3}{type=numeric}
\answer{\name_head[4]}{\freq4}{type=numeric}
\answer{\name_head[4]}{\freq5}{type=numeric}


