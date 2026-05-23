target=oefvitesse1
\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{du=randint(70..180)}
\integer{vi=randint(85..165)}
\real{vk=\vi*6/10}
\integer{h=floor(\du/60)}
\integer{m=\du-60*\h}
\real{di=\du*\vi/100}
\integer{s=60}
\statement{\name_enonce[1] \di km \name_enonce[2] \h h \m min.
\name_enonce[3]
<p>\name_tabl:</p>
<table class="wimsborder wimscenter">
<tr><th>\name_head[1]</th>
  <td>\embed{reply 1}</td>
  <td>\embed{reply 2}</td></tr>
<tr><th>\name_head[2]</th>
  <td>\di</td>
  <td>\embed{reply 3}</td></tr>
</table>
<div><label for="reply4">\name_question</label> \embed{reply 4} km / h.</div>
}
\answer{}{\du}{type=numeric}
\answer{}{\s}{type=numeric}
\answer{}{\vk}{type=numeric}
\answer{}{\vk}{type=numeric}
