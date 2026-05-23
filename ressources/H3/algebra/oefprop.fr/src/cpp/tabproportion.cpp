target=tabproportion
\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\rational{prop= random(randint(2..9), random(3/2,1/2,5/2))}
\integer{a=randint(3..6)}
\integer{b=randint(4..9)}
\integer{b=\a=\b? \b+1}
\rational{aa=\a*\prop}
\rational{bb=\b*\prop}
\text{pr=\prop}
\text{choix=random(1,2,3,4)}
\text{rep1=\choix=1? \a:\aa}
\text{rep1=\choix=2? \b}
\text{rep1=\choix=4? \bb}

\statement{ \name_question1:
<table class="wimscenter wimsborder">
<tr><td>
\if{\choix=1}{\embed{reply 1,5}}{\a}</td><td>\if{\choix=2}{\embed{reply 1,5}}{\b}</td></tr>
<tr><td>\if{\choix=3}{\embed{reply 1,5}}{\aa}</td><td>
\if{\choix=4}{\embed{reply 1,5}}{\bb}</td>
</tr>
</table>
<div><label for="reply2">\name_question2</label> \embed{reply 2,6}.</div>
}
\answer{}{\rep1}{type=numeric}
\answer{}{\pr}{type=numexp}
