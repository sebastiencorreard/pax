target=tabproportion2
\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{yes}
\precision{10000}

\real{prop=randint(2..9)/10}
\real{a=randint(30..60)/10}
\real{b=randint(40..90)/10}
\real{b=\a=\b? \b+1}
\real{aa=\a*\prop}
\real{bb=\b*\prop}
\text{pr=\prop}
\text{choix=random(1,2,3,4)}
\text{rep1=\choix=1? \a:\aa}
\text{rep1=\choix=2? \b}
\text{rep1=\choix=4? \bb}
\text{h1=item(\choix,\(\frac{\bb}{\b}),\(\frac{\aa}{\a}),\(\frac{\bb}{\b}),\(\frac{\aa}{\a}))}
\text{h2=item(\choix,\b &times
 &#63
 = \bb,\a &times
 &#63
 = \aa,\b &times
 &#63
 = \bb,\a &times
 &#63
 = \aa)}

\statement{\name_question:
<table class="wimscenter wimsborder">
<tr><td>
\if{\choix=1}{\embed{reply 1,5}}{\a}</td><td>\if{\choix=2}{\embed{reply 1,5}}{\b}</td></tr>
<tr><td>\if{\choix=3}{\embed{reply 1,5}}{\aa}</td><td>
\if{\choix=4}{\embed{reply 1,5}}{\bb}</td>
</tr>
</table>
<div><label for="reply2">\name_question2</label> \embed{reply 2,6}.
</div>
}
\hint{\name_hint1:
<div class="wimscenter"><b>\h2</b> \name_or \h1</div>
  \name_hint2:
<div class="wimscenter"<b>\h3</b></div>}
\answer{}{\rep1}{type=numeric}
\answer{}{\pr}{type=numeric}
