target=oefutitabl1 oefutitabl2 oefutitabl3 oefutitabl4 oefutitabl5
#include "author.inc"
#include "css.inc"
\precision{10000}
#if defined TARGET_oefutitabl1
# define NUM 1
#endif
#if defined TARGET_oefutitabl2
# define NUM 2
#endif
#if defined TARGET_oefutitabl3
# define NUM 3
#endif
#if defined TARGET_oefutitabl4
# define NUM 4
#endif
#if defined TARGET_oefutitabl5
# define NUM 5
#endif
#include "lang_titles.inc"
#include "lang.inc"

\matrix{val=randint(30..70),randint(30..70),randint(30..70),randint(30..70)
randint(30..70),randint(30..70),randint(30..70),randint(30..70)
randint(30..70),randint(30..70),randint(30..70),randint(30..70)
randint(30..70),randint(30..70),randint(30..70),randint(30..70)}

\text{totl=}
\text{aff=}
\for{i=1 to 4}{\text{lig=row(\i,\val)}
\text{aff=\aff,\lig}
\integer{tot=\lig[1]+\lig[2]+\lig[3]+\lig[4]}
\text{totl=wims(append item \tot to \totl)}}

\text{totc=}
\for{i=1 to 4}{\text{col=column(\i,\val)}
\integer{tot=\col[1]+\col[2]+\col[3]+\col[4]}
\text{totc=wims(append item \tot to \totc)}}

\integer{tott=\totc[1]+\totc[2]+\totc[3]+\totc[4]}
#if defined TARGET_oefutitabl1
\integer{b=randint(1..4)}
\text{enonc1=\name_enonc1 \niv[\b]}
\integer{rp1=\totc[\b]}
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 4}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}{<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{\if{\j=\b}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}
   {<td>\aff[\j+4*(\k-1)+1]</td>}}
   </tr>}
</table>
\(\aff[\b+1]+\aff[\b+5]+\aff[\b+9]+\aff[\b+13]=\totc[\b]\).
\sol}
#endif
#if defined TARGET_oefutitabl2
\integer{b=randint(1..4)}
\text{enonc1=\name_enonc1 \sex[floor((\b+1)/2)] \qual[\b]}
\integer{rp1=\totl[\b]}
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 4}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{\if{\k=\b}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}
   {<td>\aff[\j+4*(\k-1)+1]</td>}}
   </tr>}
</table>
\(\aff[1+4*(\b-1)+1]+\aff[2+4*(\b-1)+1]+\aff[3+4*(\b-1)+1]+\aff[4+4*(\b-1)+1]=\totl[\b]\).
\sol}
#endif
#if defined TARGET_oefutitabl3
\integer{b=randint(1..2)}
\text{enonc1=\name_enonc1 \sex[\b]}
\integer{rp1=\totl[\b*2-1]+\totl[\b*2]}
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 4}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{\if{(\k=1 and \b=1) or (\k=2 and \b=1)}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}
   \if{(\k=3 and \b=2) or (\k=4 and \b=2)}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}
   \if{(\k=1 and \b=2) or (\k=2 and \b=2)}{<td>\aff[\j+4*(\k-1)+1]</td>}
   \if{(\k=3 and \b=1) or (\k=4 and \b=1)}{<td>\aff[\j+4*(\k-1)+1]</td>}}
   </tr>}
</table>
\sol}
#endif
#if defined TARGET_oefutitabl4
\integer{b=randint(1..2)}
\text{enonc1=\name_enonc1 \qual[\b]}
\integer{rp1=\totl[\b]+\totl[\b+2]}
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 4}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{\if{(\k=1 and \b=1) or (\k=3 and \b=1)}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}
   \if{(\k=2 and \b=2) or (\k=4 and \b=2)}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}
   \if{(\k=1 and \b=2) or (\k=3 and \b=2)}{<td>\aff[\j+4*(\k-1)+1]</td>}
   \if{(\k=2 and \b=1) or (\k=4 and \b=1)}{<td>\aff[\j+4*(\k-1)+1]</td>}}
   </tr>}
</table>
\sol}
#endif
#if defined TARGET_oefutitabl5
\text{enonc1=\name_enonc1}
\integer{rp1=\tott}
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 4}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{
   <td class="yellow">\aff[\j+4*(\k-1)+1]</td>}
   </tr>}
</table>
\sol}
#endif
#include "solution.inc"
\statement{
\name_instruction
<table class="wimscenter wimsborder table-scroll">
<tr><th></th>
\for{m=0 to 4}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{
   <td>\aff[\j+4*(\k-1)+1]</td>}
   </tr>}
</table>
<div class="spacer"><label for="reply1">\enonc1</label> \embed{r1,4}.</div>
}

\answer{}{\rp1}{type=numeric}
