target=oefliretabl1 oefliretabl2 oefliretabl3 oefliretabl4 oefliretabl5
#include "css.inc"
#include "author.inc"
\precision{10000}
#if defined TARGET_oefliretabl1
# define NUM 1
#endif
#if defined TARGET_oefliretabl2
# define NUM 2
#endif
#if defined TARGET_oefliretabl3
# define NUM 3
#endif
#if defined TARGET_oefliretabl4
# define NUM 4
#endif
#if defined TARGET_oefliretabl5
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
\text{totl=\totl,\tot}}

\text{totc=}
\for{i=1 to 4}{\text{col=column(\i,\val)}
\integer{tot=\col[1]+\col[2]+\col[3]+\col[4]}
\text{totc=\totc,\tot}}

\integer{tott=\totc[5]+\totc[2]+\totc[3]+\totc[4]}

#if defined TARGET_oefliretabl1
\text{a=shuffle(4)}
\integer{b=randint(1..4)}
\integer{d=randint(1..4)}
\integer{rp1=item(\a[1],row(\b,\val))}
\integer{rp2=item(\a[2],row(\d,\val))}
#endif
#if defined TARGET_oefliretabl2
\text{a=shuffle(4)}
\integer{rp1=\totc[\a[1]+1]}
\integer{rp2=\totc[\a[2]+1]}
\integer{aux1=\a[1]+1}
\integer{aux2=\a[2]+1}
#endif
#if defined TARGET_oefliretabl3
\text{a=shuffle(4)}
\integer{rp1=\totl[\a[1]+1]}
\integer{rp2=\totl[\a[2]+1]}
\integer{aux1=\a[1]+1}
\integer{aux2=\a[2]+1}
#endif
#if defined TARGET_oefliretabl4
\text{a=randint(1..4)}
\integer{b=randint(1..2)}
\integer{rp1=item(\a[1],row(\b*2,\val))+item(\a[1],row(\b*2-1,\val))}
\integer{rp2=\tott}
\integer{aux1=\a[1]}
\integer{aux2=\b*2}
#endif
#if defined TARGET_oefliretabl5
\text{a=shuffle(4)}
\integer{b=randint(1..2)}
\integer{rp1=item(\a[1],row(\b,\val))+item(\a[1],row(\b+2,\val))}
\integer{rp2=item(\a[2],row(\b,\val))+item(\a[2],row(\b+2,\val))}
\integer{aux1=\a[1]}
\integer{aux2=\a[2]}
#endif
#include "lang.inc"
#include "solution.inc"
\statement{\name_instruction
<table class="wimscenter wimsborder table-scroll">
<tr><th></th>
\for{m=0 to 5}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{
   <td>\aff[\j+4*(\k-1)+1]</td>}
   <td>\totl[\k+1]</td></tr>}

<tr><th></th><th>\name_total</th>
\for{l=2 to 5}{<td>\totc[\l]</td>}
<td>\tott</td></tr></table>

<div class="spacer">\name_question:</div>
<ul>
<li><label for="reply1">\enonc1</label> \embed{r1,4}</li>
<li><label for="reply2">\enonc2</label> \embed{r2,4}</li>
</ul>
}

\answer{}{\rp1}{type=numeric}
\answer{}{\rp2}{type=numeric}

#if defined TARGET_oefliretabl1
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 5}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{\if{\j=\a[1] and \k=\b}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}{\if{\j=\a[2] and \k=\d}{<td class="PaleGreen">\aff[\j+4*(\k-1)+1]</td>}
   {<td >\aff[\j+4*(\k-1)+1]</td>}}}
   <td>\totl[\k+1]</td></tr>}
<tr><th></th><th>Total</th>
\for{l=2 to 5}{<td>\totc[\l]</td>}
<td>\tott</td></tr></table>
\sol}
#endif
#if defined TARGET_oefliretabl2
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 5}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{<td >\aff[\j+4*(\k-1)+1]</td>}
   <td>\totl[\k+1]</td></tr>}
<tr><th></th><th>Total</th>
\for{z=2 to 5}{\if{\z=\aux1}{<td class="yellow">\totc[\z]</td>}{\if{\z=\aux2}{<td class="PaleGreen">\totc[\z]</td>}{<td>\totc[\z]</td>}}}
<td>\tott</td></tr></table>
\sol}
#endif
#if defined TARGET_oefliretabl3
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 5}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{<td >\aff[\j+4*(\k-1)+1]</td>}
   \if{\k=\a[1]}{<td class="yellow">\(\rp1\)</td>}{\if{\k=\a[2]}{<td class="PaleGreen">\(\rp2\)</td>}{<td>\totl[\k+1]</td></tr>}}}
<tr><th></th><th>Total</th>
\for{z=2 to 5}{<td>\totc[\z]</td>}
<td>\tott</td></tr></table>
\sol}
#endif
#if defined TARGET_oefliretabl4
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 5}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{
   \if{\j=\aux1}{\if{((\b=1 and \k=1) or (\b=1 and \k=2)) or ((\b=2 and \k=3) or (\b=2 and \k=4))}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}{<td>\aff[\j+4*(\k-1)+1]</td>}
         }
   \if{\j<>\aux1}{<td>\aff[\j+4*(\k-1)+1]</td>}}
   <td>\totl[\k+1]</td></tr>}
<tr><th></th><th>Total</th>
\for{l=2 to 5}{<td>\totc[\l]</td>}
<td class="PaleGreen">\tott</td></tr></table>
\sol}
#endif
#if defined TARGET_oefliretabl5
\solution{<table class="wimscenter wimsborder">
<tr><th></th>
\for{m=0 to 5}{<th>\niv[\m]</th>}
</tr>
\for{k=1 to 4}
  {<tr>
   \if{\k=1 or \k=3}{<th colspan="1" rowspan="2">\sex[\k/2+1]</th>}
   <th>\qual[\k]</th>
   \for{j=1 to 4}{
   \if{\j=\aux1}{\if{((\b=1 and \k=1) or (\b=1 and \k=3)) or ((\b=2 and \k=2) or (\b=2 and \k=4))}{<td class="yellow">\aff[\j+4*(\k-1)+1]</td>}{<td>\aff[\j+4*(\k-1)+1]</td>}
         }
   \if{\j<>\aux1 and \j<>\aux2}{<td>\aff[\j+4*(\k-1)+1]</td>}
   \if{\j=\aux2}{\if{((\b=1 and \k=1) or (\b=1 and \k=3)) or ((\b=2 and \k=2) or (\b=2 and \k=4))}{<td class="PaleGreen">\aff[\j+4*(\k-1)+1]</td>}{<td>\aff[\j+4*(\k-1)+1]</td>}
         }
   }
   <td>\totl[\k+1]</td></tr>}
<tr><th></th><th>Total</th>
\for{l=2 to 5}{<td>\totc[\l]</td>}
<td>\tott</td></tr></table>
\sol}
#endif
