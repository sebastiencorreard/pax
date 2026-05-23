target=repartition2

\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}

#include "repartition.inc"

\integer{eff6=\eff1+\eff2}
\integer{eff7=\eff3+\eff4}
\integer{effc6=\eff6}
\integer{effc7=\effc6+\eff7}
\real{freq6=floor(1000*\eff6/\effc5)/10}
\real{freq7=floor(1000*\eff7/\effc5)/10}

\steps{reply1,reply2,reply3,reply4,reply5,reply6,reply7,reply8,reply9,reply10
reply11,reply12,reply13,reply14,reply15,reply16,reply17,reply18,reply19}

\statement{\if{\step=1}{\name_enonce1[1] \effc5 \name_enonce1[2]

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
}
\if{\step=2}{\name_enonce2[1]:
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
<td>\effc1 </td>
<td>\effc2 </td>
<td>\effc3 </td>
<td>\effc4 </td>
<td>\effc5 </td>
</tr>
<tr><th>\name_head[4] (%)</th>
<td>\freq1 </td>
<td>\freq2 </td>
<td>\freq3 </td>
<td>\freq4 </td>
<td>\freq5 </td>
</tr>
</table>
<div class="wims_question">
\name_enonce2[2]:
<table class="wimscenter wimsborder">
<tr><th>\name_head[1]</th>
<td>\(0\leq N <8 \)</td>
<td>\(8\leq N <16\)</td>
<td>\(16\leq N \leq 20 \)</td></tr>
<tr><th>\name_head[2]</th>
<td>\embed{reply 11,5} </td>
<td>\embed{reply 12,5} </td>
<td>\embed{reply 13,5} </td></tr>
<tr><th>\name_head[3]</th>
<td>\embed{reply 14,5} </td>
<td>\embed{reply 15,5} </td>
<td>\embed{reply 16,5} </td></tr>
<tr><th>\name_head[4] (%)</th>
<td>\embed{reply 17,5} </td>
<td>\embed{reply 18,5} </td>
<td>\embed{reply 19,5} </td>
</tr>
</table>
</div>}
\name_inst
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

\answer{\name_head[2]}{\eff6}{type=numeric}
\answer{\name_head[2] }{\eff7}{type=numeric}
\answer{\name_head[2] }{\eff5}{type=numeric}

\answer{\name_head[3]}{\effc6}{type=numeric}
\answer{\name_head[3]}{\effc7}{type=numeric}
\answer{\name_head[3]}{\effc5}{type=numeric}

\answer{\name_head[4]}{\freq6}{type=numeric}
\answer{\name_head[4]}{\freq7}{type=numeric}
\answer{\name_head[4]}{\freq5}{type=numeric}
