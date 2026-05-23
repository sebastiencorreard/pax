target=tabproportion tabprop0

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\precision{10000}

#if defined TARGET_tabproportion
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
\statement{<label for="reply1">\name_enonce:</label>
<table class="wimsborder wimscenter">
<tr><td>
\if{\choix=1}{\embed{reply 1,5}}{\a}</td><td>\if{\choix=2}{\embed{reply 1,5}}{\b}</td></tr>
<tr><td>\if{\choix=3}{\embed{reply 1,5}}{\aa}</td><td>
\if{\choix=4}{\embed{reply 1,5}}{\bb}</td>
</tr>
</table>
<div><label for="reply2">\name_question:</label> \embed{reply 2,6}.</div>
}
\answer{}{\rep1}{type=numeric}
\answer{}{\pr}{type=numeric}
#endif
#if defined TARGET_tabprop0
\real{prop= randint(2..19)}
\text{T=shuffle(1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19)}
\integer{a=\T[1]}
\integer{b=\T[2]}
\integer{c=\T[3]}
\integer{d=\T[4]}
\integer{e=\T[5]}
\integer{f=\T[6]}
\real{aa=\a*\prop}
\real{bb=\b*\prop}
\real{cc=\c*\prop}
\real{dd=\d*\prop}
\real{ee=\e*\prop}
\real{ff=\f*\prop}

\statement{\name_enonce:
<table class="wimsborder wimscenter my">
<tr><td>\a</td><td>\b</td><td>\c</td>
  <td>\embed{reply 1,6}</td><td>\embed{reply 2,6}</td><td>\f</td></tr>
<tr><td>\aa</td><td>\bb</td>
<td>\embed{reply 3,6}</td><td>\dd</td><td>\ee</td><td>\embed{reply 4,6}</td>
</tr>
</table>
<div><label for="reply5">\name_question:</label> \embed{reply 5,6}.</div>
}
\answer{}{\d}{type=numeric}
\answer{}{\e}{type=numeric}
\answer{}{\cc}{type=numeric}
\answer{}{\ff}{type=numeric}
\answer{}{\prop}{type=numeric}
#endif
