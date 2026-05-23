target=oefechelle1 oefechellereelle1
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
\statement{
#if defined TARGET_oefechelle1
\name_enonce[1], \name_enonce[2] \lm m \name_enonce[3] \l cm.
<p>\name_tabl:</p>
<table class="wimscenter wimsborder">
<tr><th>\name_head[1]</th><td>\l</td><td>\embed{reply 1}</td></tr>
<tr><th>\name_head[2]</th><td>\embed{reply 2}</td><td>\embed{reply 3}</td>
</tr></table>
#endif
#if defined TARGET_oefechellereelle1
\name_enonce[1] 1/\ee. \name_enonce[2] \l cm.
<p>\name_tabl:</p>
<table class="wimscenter wimsborder">
<tr><th>\name_head[1]</th><td>\embed{reply 1}</td><td>\l</td></tr>
<tr><th>\name_head[2]</th><td>\embed{reply 2}</td><td>\embed{reply 3}</td>
</tr></table>
#endif
<div>
#if defined TARGET_oefechelle1
<label for="reply4">\name_enonce2 1/ </label>\embed{reply 4}.
#endif
#if defined TARGET_oefechellereelle1
<label for="reply4">\name_enonce2</label> \embed{reply 4} m.
#endif
</div>
}
#if defined TARGET_oefechelle1
\answer{}{\s}{type=numeric}
\answer{}{\lr}{type=numeric}
\answer{}{\ee}{type=numeric}
\answer{}{\ee}{type=numeric}
#endif
#if defined TARGET_oefechellereelle1
\answer{}{\s}{type=numeric}
\answer{}{\ee}{type=numeric}
\answer{}{\lr}{type=numeric}
\answer{}{\lm}{type=numeric}
#endif

