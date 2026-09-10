target=signe1

&&& cas d'un binôme \(a x + b)
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = (-1)^random(0,1)*random(1..4)}
\integer{b = (-1)^random(0,1)*random(1..10)}
\rational{zero=-\b/\a}
\function{u=\a *x + \b}
\function{u=\a==1?x + \b}
\function{u=\a==-1?-x + \b}

\rational{rep1=-\b/\a}
\text{signes1=-,+}
\text{signes2=-,+}
\text{chges=0,||,|}
\text{rep2=\a>0?1:2}
\text{rep4=\a>0?2:1}
\text{rep3=1}


\statement{
\if{\step=1}{
<div class="background-color:#FFFF66">
<p>\name_statement[1] \(\u\) \name_statement[2]?</p>
<div class="wimscenter"> \(\u = 0 \) \name_statement[3] <label for="reply1">\(x\) =</label>
\embed{reply1,5}.</div></div>
}
\if{\step=2}{
<div class="background-color:#FFFF66">
<p>\name_statement2[1] \(\u\) \name_statement2[2] \( x \) = \rep1.</p>
<p>\name_question \(\u\).</p>
<table class="wimscenter" border=1 border="solid" width="70%">
<tr>
<td width="15%" align="center">
\(x\)</td><td width="30%" align="left">\(-\infty)</td>
<td width="5%" align="center">\embed{reply2,5}</td>
<td width="30%" align="right">\(+\infty)</td>
</tr><tr>
<td width="15%" align="center">\(\u)</td><td width="30%" align="center">
\embed{reply3}</td><td width="5%" align="center">\embed{reply4}</td><td width="30%" align="center"> \embed{reply5}</td>
</tr>
</table>
</div>
}
}
\steps{reply1
reply2,reply3,reply4,reply5
}
\answer{}{\rep1}{type=numexp}{option=nonstop}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2 ; \signes1}{type=menu}
\answer{}{\rep3 ; \chges}{type=menu}
\answer{}{\rep4 ; \signes2}{type=menu}
\hint{
<p style="color:blue">\name_hint[1] \(-\frac{b}{a}\) \name_hint[2]\(-\frac{b}{a}\).
\name_hint[3] \(x > -\frac{b}{a}\).</p>
}
