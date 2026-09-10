target=tabpuis
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang.inc"
\integer{a=randint(3..6)*random(1,-1)}
\integer{b=randint(3..9)*random(1,-1)}
\integer{ab=\a*(\b)}
\integer{abab=(\ab)^2}
\integer{aa=(\a)^2}
\integer{bb=(\b)^2}
\statement{\name_statement:
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr><td>\(a)</td><td><label for="reply1">\(\b a\)</label></td><td><label for="reply2">\((\b a)^2\)
</label></td><td><label for="reply3">\(a^2\)</label></td>
<td><label for="reply4">\(\bb a^2\)</label></td></tr>
<tr><td>\a</td><td>\embed{reply 1,6}</td>
<td>\embed{reply 2,6}</td>
<td>\embed{reply 3,6}</td>
<td>\embed{reply 4,6}</td>
</tr>
</table>
</div>
}
\answer{\(\b*a\)}{\ab}{type=litexp}
\answer{\((\b*a)^2\)}{\abab}{type=litexp}
\answer{\(a^2\)}{\aa}{type=litexp}
\answer{\(\bb*a^2\)}{\abab}{type=litexp}

\feedback{\reply2 <>\reply4}{\name_feed \((\b a)^2=\bb a^2\).}
