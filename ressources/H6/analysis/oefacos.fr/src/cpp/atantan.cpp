target=atantan

#include "author.inc"
\precision{10000}
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}

\real{x=random(-1,1)*floor(random(10..150))/10}
\real{r=\x+pi/2}
\real{c=floor(\r/pi)}
\real{a=\x}
\real{b=-(\c)}
\statement{\name_enonce[1] \(x = arctg(tg(\x))\) \name_enonce[2]
\(x = a + b pi\) \name_enonce[3].
}

\answer{\(a\)}{\a}
\answer{\(b\)}{\b}
\hint{\name_hint.}
