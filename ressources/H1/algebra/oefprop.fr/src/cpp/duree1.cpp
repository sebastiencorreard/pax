target=duree1
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}
\format{html}
\precision{10000}

\integer{du=randint(70..180)}
\integer{vi=randint(85..165)}
\real{vk=\vi*6/10}
\integer{h=floor(\du/60)}
\integer{m=\du-60*\h}
\real{di=\du*\vi/100}
\integer{s=60}
\statement{\name_enonce[1] \vk \(\textrm{km/h}\).
\name_enonce[2] \di \(\textrm{km}\).
<p>\name_question[1;] (\name_question[2;]) :</p>
<table class="wimscenter wimsborder">
<tr><th>\name_head[1] min</th><td>\embed{reply 1}</td><td>\embed{reply 2}</td></tr>
<tr><th>\name_head[2] \(\textrm{km}\)</th><td>\vk</td><td>\embed{reply 3}</td></tr>
</table>
<ul><li><label for="reply4">\name_question2</label> \embed{reply 4,4} \(\textrm{min}\).
</li><li>
\name_question3: \embed{reply 5,4} \(\textrm{h}) \embed {reply 6,4} \(\textrm{min}\).
</li></ul>
}
\answer{}{\s}{type=numeric}
\answer{}{\du}{type=numeric}
\answer{}{\di}{type=numeric}
\answer{}{\du}{type=numeric}
\answer{}{\h}{type=numeric}
\answer{}{\m}{type=numeric}
