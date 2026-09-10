target=oefconstangl5
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{ang=randint(15..85)}
\real{l=randint(30..90)/10}
\integer{rep=20*\l*sin(pi*\ang/360)}
\real{rep1=(\rep-1)/10}
\real{rep2=(\rep+1)/10}

\statement{
<ul>
<li>
\name_enonce[1;1] \(\widehat{xAy}) \name_enonce[1;2] \ang ° \name_enonce[1;3]
</li><li>
\name_enonce[2;1] &#91;Ax&#41; \name_enonce[2;2]  AB = \l cm.
</li><li>
\name_enonce[3;1] &#91;Ay&#41; \name_enonce[3;2] AC = \l cm.
</li><li>
\name_enonce[4;] [BC].
<div class="wimscenter"><label for="reply1">BC =</label> \embed{r1,4} cm </div>
</li></ul>}

\answer{}{\rep1,\rep2}{type=range}
