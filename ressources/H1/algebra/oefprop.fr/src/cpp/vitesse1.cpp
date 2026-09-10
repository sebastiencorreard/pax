target=vitesse1

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\precision{10000}
\integer{du=randint(70..180)}
\integer{vi=randint(85..165)}
\real{vk=\vi*6/10}
\integer{h=floor(\du/60)}
\integer{m=\du-60*\h}
\real{di=\du*\vi/100}
\integer{s=60}
\statement{\name_enonce[1] \di \(\mathrm{km}\) (\name_enonce[2] \h \(\textrm{h}\) \m \(\textrm{min}\)).
<p>\name_question[1;] (\name_question[2;]):</p>
<table class="wimscenter wimsborder">
<tr><th><label for="reply1">\name_header[1] \(\textrm{min}\)</label></th><td>\embed{reply 1}</td><td>\embed{reply 2}</td></tr>
<tr><th><label for="reply3">\name_header[2] \(\textrm{km}\)</label></th><td>\di</td><td>\embed{reply 3}</td>
</tr></table>
<div><label for="reply4">\name_question2</label> \embed{reply 4} \(\textrm{km / h}\).</div>
}
\answer{}{\du}{type=numeric}
\answer{}{\s}{type=numeric}
\answer{}{\vk}{type=numeric}
\answer{}{\vk}{type=numeric}
