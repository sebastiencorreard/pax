target=oefechelcarte1
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}
\format{html}
\precision{10000}

\integer{lc=randint(60..250)}
\integer{e=randint(12..90)}
\integer{ee=\e*10}
\real{l=\lc/10}
\integer{lr=\lc*\e}
\real{lm=\lr/100}
\integer{s=1}
\text{nam}
\statement{\name_enonce[1] 1/\ee. \name_enonce[2] \lm m.
<p>\name_tabl:</p>
<table class="wimscenter wimsborder">
<tr><th>\name_head[1]</th><td>\embed{reply 1}</td><td>\embed{reply 2}</td></tr>
<tr><th>\name_head[2]</th><td>\embed{reply 3}</td><td>\lr</td></tr>
</table>
<div><label for="reply4">\name_question</label> \embed{reply 4} cm.</div>
}
\answer{}{\s}{type=numeric}
\answer{}{\l}{type=numeric}
\answer{}{\ee}{type=numeric}
\answer{}{\l}{type=numeric}
