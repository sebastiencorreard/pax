target=echelcarte1
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
\statement{\name_enonce[1] 1/\ee. \name_enonce[2] \lm \(\textrm{m}).
<p>\name_question[1;] (\name_question[2;]):</p>
<table class="wimscenter wimsborder">
<tr><th><label for="reply1">\name_head[1] \(\textrm{cm}\)</label></th>
<td>\embed{reply 1}</td><td>\embed{reply 2}</td></tr>
<tr><th><label for="reply3">\name_head[2] cm</label></th><td>\embed{reply 3}</td>
<td>\lr</td></tr>
</table>
<div><label for="reply4">\name_question2</label> \embed{reply 4} \(\textrm{cm}\).</div>
}
\answer{}{\s}{type=numeric}
\answer{}{\l}{type=numeric}
\answer{}{\ee}{type=numeric}
\answer{}{\l}{type=numeric}
