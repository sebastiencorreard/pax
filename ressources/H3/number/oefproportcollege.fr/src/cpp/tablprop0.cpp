target=oeftablprop0euro oeftablprop0
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}
\format{html}
\precision{10000}
#include "css.inc"
#if defined TARGET_oeftablprop0euro
\real{prop=randint(3..29)}
#endif
#if defined TARGET_oeftablprop0
\real{prop=randint(15..49)}
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

\statement{\name_enonce:
<table class="wimscenter wimsborder my">
<tr><th>\name_head[1]</th>
<td>\b</td><td>\c</td><td>\d</td><td>\e</td><td>\f</td></tr>
<tr><th>\name_head[2] \name_money</th>
<td>\bb</td>
<td>\embed{reply 1,6}</td>
<td>\embed{reply 2,6}</td>
<td>\embed{reply 3,6}</td>
<td>\embed{reply 4,6}</td>
</tr>
</table>
}
\answer{}{\cc}{type=numeric}
\answer{}{\dd}{type=numeric}
\answer{}{\ee}{type=numeric}
\answer{}{\ff}{type=numeric}
