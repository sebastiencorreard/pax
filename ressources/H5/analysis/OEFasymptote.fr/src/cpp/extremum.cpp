target=extremum1 extremum2
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\text{symb=\ge,>,\le,<}
\integer{kh=randint(1,-1)}
\integer{a=randint(1..9)*\kh}
\integer{b=randint(1..9)*\kh}
\integer{c=randint(1..9)*randint(1,-1)}
\integer{mc=\c*(-1)}
\integer{d=randint(1..9)*randint(1,-1)}
\integer{e=randint(1..9)*randint(1,-1)}
\integer{u=randint(1..9)}
\integer{v=randint(1..9)}
#if defined TARGET_extremum1
\text{h=\a*x^2+\b}
\integer{niveau=1}
#endif
#if defined TARGET_extremum2
\text{h=\a*(x+\e)^2+\b}
\text{h=maxima(expand(\h))}
\integer{niveau=2}
#endif
\text{th=texmath(\h)}
\integer{sh=\kh=1?2:4}
\integer{choix=randint(1..3)}
\if{\choix=1}{
   \if{\niveau=1}{
    \text{g=maxima(expand((x+\c)^2))}
    \text{tg=texmath((x+\c)^2)}
    \text{fnum=maxima(expand((x+\c)^2+\d*(\a*x^2+\b)))}
    }{
    \text{g=maxima(expand(\u*(x+\c)^2))}
    \text{tg=texmath(\u*(x+\c)^2)}
    \text{fnum=maxima(expand(\u*(x+\c)^2+\d*(\a*(x+\e)^2+\b)))}
    }
   \text{tfnum=texmath(\fnum)}
   \integer{sg=1}
   \integer{sf=\kh=1?1:3}
   \integer{nat=\kh=1?3:1}
   \text{suitesol=\name_suitesol[1] \(x=\mc)}
  }
\if{\choix=2}{
   \if{\niveau=1}{
    \text{g=maxima(expand(-(x+\c)^2))}
    \text{tg=texmath(-(x+\c)^2)}
    \text{fnum=maxima(expand(-(x+\c)^2+\d*(\a*x^2+\b)))}
    }{
    \integer{u=-\u}
    \text{g=maxima(expand(\u*(x+\c)^2))}
    \text{tg=texmath(\u*(x+\c)^2)}
    \text{fnum=maxima(expand(\u*(x+\c)^2+\d*(\a*(x+\e)^2+\b)))}
    }
   \text{tfnum=texmath(\fnum)}
   \integer{sg=3}
   \integer{sf=\kh=1?3:1}
   \integer{nat=\kh=1?1:3}
   \text{suitesol=\name_suitesol[1] \(x=\mc)}
  }
\if{\choix=3}{
   \if{\niveau=1}{
    \text{g=\c}
    \text{tg=texmath(\g)}
    \text{fnum=maxima(expand(\c+\d*(\a*x^2+\b)))}
    \integer{ku=\c>0?1:-1}
    }{
    \integer{ku=randint(1,-1)}
    \integer{u=\u*\ku}
    \integer{v=\v*\ku}
    \text{g=maxima(expand(\u*(x+\c)^2)+\v)}
    \text{tg=texmath(\u*(x+\c)^2)+\v}
    \text{fnum=maxima(expand(\u*(x+\c)^2+\v+\d*(\a*(x+\e)^2+\b)))}
    }
   \text{tfnum=texmath(\fnum)}
   \integer{sg=\ku>0?2:4}
   \integer{sf=(\kh=1 and \ku>0) or (\kh=-1 and \ku<0)?2:4}
   \integer{nat=\sf=2?4:2}
   \text{suitesol=\name_suitesol[2]}
  }
\text{tf=\frac{\tfnum}{\th}}
\text{dd=\d>0 ? -\d: -(\d)}
\statement{
 \name_enonce[1]:
<div class="wimscenter">\(f(x) = \tf\) .</div>
 \name_enonce[2] \d \name_enonce[3] \(f\).
<ol>
<li> \name_question[1] <span style="color:red">\(f(x) \dd\)</span>
  \name_question[2]:
<table class="wimscenter wimsnoborder">
<tr>
  <td style="text-align:right" rowspan="3"> \(f(x) \dd =\)</td>
  <td style="text-align:left"> \embed{reply1,12}</td>
</tr>
<tr><td><hr></td></tr>
<tr><td style="text-align:left"> \embed{reply2,12}</td>
</tr></table>
</li>
<li> \name_question2[1]? \embed{reply3}
<div>
 \name_question2[2]?\embed{reply4}
</div><div>
 \name_question2[3] \(f(x) - (\d)):\embed{reply5}
</div>
</li><li>
 \name_question2[4] \(\d\) \name_question2[5] \embed{reply6} \name_question2[6] \(f).
</li>
</ol>
}
\answer{\name_answer[1]}{\g}{type=function}
\answer{\name_answer[2]}{\h}{type=function}
\answer{\name_answer[3]}{\sg;\lstsigne}{type=menu}
\answer{\name_answer[4]}{\sh;\lstsigne}{type=menu}
\answer{\name_answer[5] \(f(x)-(\d))}{\sf;\lstsigne}{type=menu}
\answer{\name_answer[6]}{\nat;\lstextr}{type=menu}
\feedback{1=1}{\(f(x) \dd=\frac{\tg}{\th} \symb[\sf] 0 \Leftrightarrow f(x) \symb[\sf] \d\)
<p>
\name_feed[1] \d \name_feed[2] \lstextr[\nat] \name_feed[3] \(f\) \suitesol.
</p>}

