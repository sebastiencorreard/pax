target=signeBinome
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
<div class="wims_question">
<p>\name_question \(\u\).</p>
<div class="center">
<table class="wimsborder" style="width:70%">
<tr>
<td style="width:15%;text-align:center">\(x\)</td><td style="width:30%;text-align:left">
\(-\infty\)</td><td style="width:5%;text-align:center">\embed{reply1,5}</td>
<td style="width:30%;text-align:right">\(+\infty\)</td>
</tr>
<tr>
<td style="width:15%;text-align:center">\(\u\)</td><td style="width:30%;text-align:center">
\embed{reply2}</td><td style="width:5%;text-align:center">\embed{reply3}</td><td style="width:30%;text-align:center">\embed{reply4}</td>
</tr>
</table>
</div>
</div>
}
\answer{}{\rep1}{type=numexp}
\answer{}{\rep2 ; \signes1}{type=menu}
\answer{}{\rep3 ; \chges}{type=menu}
\answer{}{\rep4 ; \signes2}{type=menu}
\hint{
<div class="enbleu">\name_hint</div>
}
