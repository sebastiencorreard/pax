target=oeftablprop3 oeftablprop4 oeftablprop4euro oeftablprop5 oeftablprop5euro oeftablprop6 oeftablprop6euro
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
\computeanswer{yes}
\format{html}
\precision{10000}
#if defined TARGET_oeftablprop3
\real{prop= randint(1..9) + randint(1..9)/10}
\text{T=shuffle(2,3,4,5,6,7,8,9,11)}
\integer{b=1}
#endif
#if defined TARGET_oeftablprop4 || defined TARGET_oeftablprop5 || defined TARGET_oeftablprop6
\real{prop= randint(15..49)}
\text{T=shuffle(3,4,5,6,7,8,9,11)}
\integer{b=\T[1]}
#endif
#if defined TARGET_oeftablprop4euro || defined TARGET_oeftablprop5euro || defined TARGET_oeftablprop6euro
\real{prop=randint(3..29)}
\text{T=shuffle(3,4,5,6,7,8,9,11)}
\integer{b=\T[1]}
#endif
\integer{c=\T[3]}
\integer{d=\T[4]}
\integer{e=\T[5]}
\integer{f=\T[6]}
\real{bb=\b*\prop}
\real{cc=\c*\prop}
\real{dd=\d*\prop}
\real{ee=\e*\prop}
\real{ff=\f*\prop}
#if defined TARGET_oeftablprop3
\text{enonce=\name_enonce[1] \prop cm. \name_enonce[2], \name_enonce[3]}
#endif
#if defined TARGET_oeftablprop6 || defined TARGET_oeftablprop6euro || defined TARGET_oeftablprop4 || defined TARGET_oeftablprop4euro || defined TARGET_oeftablprop5 || defined TARGET_oeftablprop5euro
\text{enonce=\name_enonce}
#endif
#if defined TARGET_oeftablprop3 || defined TARGET_oeftablprop3euro
\statement{\enonce <p>\name_question:</p>
<table class="wimscenter wimsborder my">
<tr><th>\name_head[1]</th>
<td>\b</td><td>\embed{reply 1,6}</td><td>\d</td>
<td>\embed{reply 3,6}</td><td>\f</td></tr>
<tr><th>\name_head[2]</th><td>\bb</td><td>\cc</td><td>\embed{reply 2,6}</td>
<td>\ee</td><td>\embed{reply 4,6}</td>
</tr>
</table>}
#endif
#if defined TARGET_oeftablprop5 || defined TARGET_oeftablprop5euro
\statement{\name_enonce:
<table class="wimscenter wimsborder my">
<tr><th>\name_head[1]</th><td>\b</td>
<td>\embed{reply 1,6}</td>
<td>\embed{reply 2,6}</td>
<td>\embed{reply 3,6}</td>
<td>\embed{reply 4,6}</td></tr>
<tr>
<th>\name_head[2] \name_money</th>
<td>\bb</td><td>\cc</td><td>\dd</td><td>\ee</td><td>\ff</td></tr>
</table>}
#endif
#if defined TARGET_oeftablprop4euro || defined TARGET_oeftablprop4
\statement{\enonce:
<table class="wimscenter wimsborder my">
<tr><th>\name_head[1]</th><td>\b</td><td>\c</td><td>\d</td><td>\e</td><td>\f</td></tr>
<tr><th>\name_head[2] \name_money</th>
<td>\bb</td>
<td>\embed{reply 1,6}</td>
<td>\embed{reply 2,6}</td>
<td>\embed{reply 3,6}</td>
<td>\embed{reply 4,6}</td>
</tr>
</table>}
#endif
#if defined TARGET_oeftablprop6 || defined TARGET_oeftablprop6euro
\statement{\enonce:
<table class="wimscenter wimsborder my">
<tr><th>\name_head[1]</th>
<td>\b</td>
<td>\embed{reply 1,6}</td>
<td>\d</td>
<td>\embed{reply 3,6}</td>
<td>\f</td></tr>
<tr><th>\name_head[2] \name_money</th>
<td>\bb</td>
<td>\cc</td>
<td>\embed{reply 2,6}</td>
<td>\ee</td>
<td>\embed{reply 4,6}</td>
</tr>
</table>}
#endif
#if defined TARGET_oeftablprop3 || defined TARGET_oeftablprop3euro || defined TARGET_oeftablprop6 || defined TARGET_oeftablprop6euro
\answer{}{\c}{type=numeric}
\answer{}{\dd}{type=numeric}
\answer{}{\e}{type=numeric}
\answer{}{\ff}{type=numeric}
#endif
#if defined TARGET_oeftablprop4 || defined TARGET_oeftablprop4euro
\answer{}{\cc}{type=numeric}
\answer{}{\dd}{type=numeric}
\answer{}{\ee}{type=numeric}
\answer{}{\ff}{type=numeric}
#endif
#if defined TARGET_oeftablprop5 || defined TARGET_oeftablprop5euro
\answer{}{\c}{type=numeric}
\answer{}{\d}{type=numeric}
\answer{}{\e}{type=numeric}
\answer{}{\f}{type=numeric}
#endif


