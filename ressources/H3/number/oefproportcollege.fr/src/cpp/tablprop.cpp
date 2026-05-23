target=oeftablprop1 oeftablprop2 oeftablprop2euro oeftablprop1euro
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
\precision{10000}
#if defined TARGET_oeftablprop1 || defined TARGET_oeftablprop2
\real{prop= randint(15..49)}
#endif
#if defined TARGET_oeftablprop1euro || defined TARGET_oeftablprop2euro
\real{prop= randint(3..29)}
#endif
\text{T=shuffle(2,3,4,5,6,7,8,9,11)}
\integer{b=1}
\integer{c=\T[3]}
\integer{d=\T[4]}
\integer{e=\T[5]}
\integer{f=\T[6]}
\real{bb=\b*\prop}
\real{cc=\c*\prop}
\real{dd=\d*\prop}
\real{ee=\e*\prop}
\real{ff=\f*\prop}
#if defined TARGET_oeftablprop1 || defined TARGET_oeftablprop1euro
\statement{\name_enonce:
<table class="wimscenter wimsborder my">
<tr><th>\name_head[1]</th>
<td>\b</td>
<td>\embed{reply 1,6}</td>
<td>\embed{reply 2,6}</td>
<td>\embed{reply 3,6}</td>
<td>\embed{reply 4,6}</td></tr>
<tr><th>\name_head[2] \name_money</th>
<td>\bb</td>
<td>\cc</td>
<td>\dd</td>
<td>\ee</td>
<td>\ff</td>
</tr>
</table>
}
\answer{}{\c}{type=numeric}
\answer{}{\d}{type=numeric}
\answer{}{\e}{type=numeric}
\answer{}{\f}{type=numeric}
#endif
#if defined TARGET_oeftablprop2 || defined TARGET_oeftablprop2euro
\statement{\name_enonce:
<table class="wimscenter wimsborder my">
<tr><th>\name_head[1]</th><td>\b</td><td>\embed{reply 1,6}</td>
<td>\d</td><td>\embed{reply 3,6}</td><td>\f</td></tr>
<tr><th>\name_head[2] \name_money</th>
<td>\bb</td>
<td>\cc</td>
<td>\embed{reply 2,6}</td>
<td>\ee</td>
<td>\embed{reply 4,6}</td>
</tr>
</table>
}
\answer{}{\c}{type=numeric}
\answer{}{\dd}{type=numeric}
\answer{}{\e}{type=numeric}
\answer{}{\ff}{type=numeric}
#endif
