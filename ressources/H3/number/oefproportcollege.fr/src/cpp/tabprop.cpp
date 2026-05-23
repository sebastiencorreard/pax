target=tabprop
\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
#include "css.inc"
\real{prop= randint(20..190)/10}
\text{T=shuffle(1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19)}
\integer{a=\T[1]}
\integer{b=\T[2]}
\integer{c=\T[3]}
\integer{d=\T[4]}
\integer{e=\T[5]}
\integer{f=\T[6]}
\real{aa=\a*\prop}
\real{bb=\b*\prop}
\real{cc=\c*\prop}
\real{dd=\d*\prop}
\real{ee=\e*\prop}
\real{ff=\f*\prop}

\statement{\name_enonce:
<table class="wimsborder wimscenter my">
<tr><td>\a</td><td>\b</td><td>\c</td><td>\embed{reply 1,6}</td><td>\embed{reply 2,6}</td><td>\f</td></tr>
<tr><td>\aa</td><td>\bb</td>
<td>\embed{reply 3,6}</td><td>\dd</td><td>\ee</td><td>\embed{reply 4,6}</td>
</tr>
</table>
<div><label for="reply5">\name_question:</label> \embed{reply 5,6}.</div>
}
\answer{}{\d}{type=numeric}
\answer{}{\e}{type=numeric}
\answer{}{\cc}{type=numeric}
\answer{}{\ff}{type=numeric}
\answer{}{\prop}{type=numeric}
