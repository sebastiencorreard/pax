target=oefcompltabl1 oefcompltabl2 oefcompltabl3 oefcompltabl4

#if defined TARGET_oefcompltabl1
# define NUM 1
#endif
#if defined TARGET_oefcompltabl2
# define NUM 2
#endif
#if defined TARGET_oefcompltabl3
# define NUM 3
#endif
#if defined TARGET_oefcompltabl4
# define NUM 4
#endif
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

\integer{a=randint(1..6)}
\text{col=row(\a,\col)}
\text{lig=row(\a,\lig)}

\integer{lig11=randint(60..150)}
\integer{lig12=randint(60..150)}
#if defined TARGET_oefcompltabl4
\integer{lig13=randint(60..150)}
\integer{lig14=randint(60..150)}
\integer{totl1=\lig11+\lig12+\lig13+\lig14}
\integer{lig21=randint(60..150)}
\integer{lig22=randint(60..150)}
\integer{lig23=randint(60..150)}
\integer{lig24=randint(60..150)}
\integer{totl2=\lig21+\lig22+\lig23+\lig24}
\integer{totc1=\lig11+\lig21}
\integer{totc2=\lig12+\lig22}
\integer{totc3=\lig13+\lig23}
\integer{totc4=\lig14+\lig24}
\integer{tott=\totc1+\totc2+\totc3+\totc4}

\integer{rp1=\lig12}
\integer{rp2=\lig13}
\integer{rp3=\lig21}
\integer{rp4=\lig24}
\integer{rp5=\totl2}
\integer{rp6=\totc3}
\integer{rp7=\tott}
#endif
#if defined TARGET_oefcompltabl1 || defined TARGET_oefcompltabl2 || defined TARGET_oefcompltabl3
\integer{totl1=\lig11+\lig12}
\integer{lig21=randint(60..150)}
\integer{lig22=randint(60..150)}
\integer{totl2=\lig21+\lig22}
# if defined TARGET_oefcompltabl1
\integer{rp1=\totl1}
\integer{rp2=\lig22}
# endif
# if defined TARGET_oefcompltabl2
\integer{totc1=\lig11+\lig21}
\integer{totc2=\lig12+\lig22}
\integer{tott=\totc1+\totc2}
\integer{rp1=\totl1}
\integer{rp2=\totl2}
\integer{rp3=\totc1}
\integer{rp4=\totc2}
\integer{rp5=\tott}
# endif
# if defined TARGET_oefcompltabl3
\integer{totc1=\lig11+\lig21}
\integer{totc2=\lig12+\lig22}
\integer{tott=\totc1+\totc2}
\integer{rp1=\lig12}
\integer{rp2=\lig21}
\integer{rp3=\lig22}
\integer{rp4=\totl2}
\integer{rp5=\totc1}
# endif
#endif

\statement{\name_instruction \lig[4].
<p>\name_question:</p>

<table class="wimscenter wimsborder table_scroll">
<tr><th>\col[1]</th>
<th>\col[2]</th>
<th>\col[3]</th>
#if defined TARGET_oefcompltabl4
<th>\col[4]</th>
<th>\col[5]</th>
#endif
<th>\name_total</th>
</tr>
#if defined TARGET_oefcompltabl2 || defined TARGET_oefcompltabl1
<tr><th>\lig[2]</th>
<td>\lig11</td>
<td>\lig12</td>
<td>\embed{r1,4}</td>
</tr>
<tr><th>\lig[3]</th>
<td>\lig21</td>
# if defined TARGET_oefcompltabl1
<td>\embed{r2,4}</td>
<td>\totl2</td>
# endif
# if defined TARGET_oefcompltabl2
<td>\lig22</td>
<td>\embed{r2,4}</td>
</tr>
<tr><th>\name_total</th>
<td>\embed{r3,4}</td>
<td>\embed{r4,4}</td>
<td>\embed{r5,4}</td>
# endif
#endif
#if defined TARGET_oefcompltabl3
<tr><th>\lig[2]</th>
<td>\lig11</td>
<td>\embed{r1,4}</td>
<td>\totl1</td>
</tr>
<tr><th>\lig[3]</th>
<td>\embed{r2,4}</td>
<td>\embed{r3,4}</td>
<td>\embed{r4,4}</td>
</tr>
<tr><th>\name_total</th>
<td>\embed{r5,4}</td>
<td>\totc2</td>
<td>\tott</td>
#endif
#if defined TARGET_oefcompltabl4
<tr><th>\lig[2]</th>
<td>\lig11</td>
<td>\embed{r1,4}</td>
<td>\embed{r2,4}</td>
<td>\lig14</td>
<td>\totl1</td>
</tr>
<tr><th>\lig[3]</th>
<td>\embed{r3,4}</td>
<td>\lig22</td>
<td>\lig23</td>
<td>\embed{r4,4}</td>
<td>\embed{r5,4}</td>
</tr>
<tr><th>\name_total</th>
<td>\totc1</td>
<td>\totc2</td>
<td>\embed{r6,4}</td>
<td>\totc4</td>
<td>\embed{r7,4}</td>
#endif
</tr></table>
}
\answer{}{\rp1}{type=numeric}
\answer{}{\rp2}{type=numeric}
#if defined TARGET_oefcompltabl2 || defined TARGET_oefcompltabl3 || defined TARGET_oefcompltabl4
\answer{}{\rp3}{type=numeric}
\answer{}{\rp4}{type=numeric}
\answer{}{\rp5}{type=numeric}
#endif
#if defined TARGET_oefcompltabl4
\answer{}{\rp6}{type=numeric}
\answer{}{\rp7}{type=numeric}
#endif

#include "solution.inc"
\solution{\sol}
