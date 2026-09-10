target=varTrinome

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format	{html}

\integer{a1=random(1..3)*random(1,-1)}
\integer{a2=random(1..3)*random(1,-1)}
\rational{c1=randint(1..10)*random(1,-1)/randint(1,2,3,5)}
\rational{c2=randint(1..10)*random(1,-1)/randint(1,2,3,5)}
\rational{c3=randint(1..10)*random(1,-1)/randint(1,2,3,5)}

\text{flist=\c1*x^2+\c2*x+\c3,
\c1*x^2+\c2*x,
\c1*x^2+\c3,
\c1*(\a2*x+\a1)^2}

\integer{\cas=random(1..4)}
\function{f=item(\cas,\flist)}

\function{F=diff(\f,x)}

\rational{x0=\cas<3?-(\c2)/(2*\c1) }
\rational{x0=\cas==3?0 }
\rational{x0=\cas==4?-(\a1/\a2) }
\rational{valextr=evaluate(\f,x=\x0)}
\text{inf=&#8734}
\text{I1=&#93; -&#8734; ; \(\x0) &#91;}
\text{I2=&#93; \(\x0) ; +&#8734; &#91;}
\text{choix3=+,-}
\integer{rep3=\c1>0?2:1}
\text{choix4=+,-}
\integer{rep4=\c1>0?1:2}
\text{choix5=\name_choix[1],\name_choix[2]}
\integer{rep5=\rep3}
\text{choix6=\name_choix[1],\name_choix[2]}
\integer{rep6=\rep4}
\integer{rep7=\rep6}

\steps{reply1,reply2
reply3,reply4,reply5,reply6,reply7,reply8
}
\statement{
<div class="wims_question">
\name_enonce \(f(x) = \f\).
<p>\name_question</p>
</div>
\if{\step==1}{
<ol>
<li>\name_question1[1] \(\,\RR) :
  <div class="wimscenter">\name_question1[2], \(f'(x)\) = \embed{reply1,20}</div>
</li><li>\name_answer[3] \(f') :
  <div class="wimscenter">\name_question1[3] \(x_0 \) = \embed{reply2,10}
</div>
</li>
</ol>
}
\if{\step>1}{
<ol>
<li>\name_answer[6] \(f\) :
<div class="wimscenter">\(f'(x) = \F \)</div>
</li>
<li>\name_answer[3] \(f'\) :
<table class="wimscenter wimsborder" style="width:50%">
<tr>
<td style="width:10%;text-align:center">\(x)</td>
<td style="width:30%;text-align:left">-\inf</td>
<td style="width:5%;text-align:center">\x0</td>
<td style="width:30%;text-align:right">+\inf</td>
</tr><tr>
<td>\(f'(x)\)</td>
<td>\embed{reply3}</td><td>0</td>
<td>\embed{reply4}</td>
</tr>
</table>
</li>
<li>\name_answer[7] \(f\) :
<ul><li>
\(f\) \name_question2[1] \embed{reply5} \name_question2[2] \I1
</li><li>
\(f\) \name_question2[1] \embed{reply6} \name_question2[2] \I2
</li></ul>
</li><li>\name_answer[8] \(f\) :
<ul>
<li>\(f\) \name_question3[1] \(\x0\) \embed{reply7}
\name_question3[2] \embed{reply8, 10}
</li></ul>
</li>
</ol>}
}
\answer{\name_answer[1] \(f'(x)\)}{\F}{type=formal}
\answer{f'(x) \name_answer[2]}{\x0}
\answer{\name_answer[3] f'}{\rep3;\choix3}{type=menu}
\answer{\name_answer[3] f'}{\rep4;\choix4}{type=menu}
\answer{f \name_choix[1]}{\rep5;\choix5}{type=menu}
\answer{f \name_choix[2]}{\rep6;\choix6}{type=menu}
\answer{\name_answer[4]}{\rep7;\choix7}{type=menu}
\answer{\name_answer[5] \(f\)}{\valextr}

\hint{\name_hint[1] \(\x_0\), \name_hint[2] \(f(\x_0)\) \name_hint[3] \(f\).}
