target=deriverQuotient

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format	{html}

/** modif. oct 2006 : change type=algexp to type=formal in answer f'(x) (reply7) **/

\integer{a1=random(1..4)}
\integer{c1=random(1..4)*random(1,-1)}
\integer{c2=random(1..8)*random(1,-1)}
\integer{c3=random(1..4)*random(1,-1)}
\integer{c4=random(1..8)*random(1,-1)}

\text{ulist= \c1*x + \c2,
 x^2 + \c1,
 \c1*x^2 + \c2*x + \c3,
 \a1*random(x,x^2)
}
\text{vlist= \c3*x+\c4,
 (\c3*x+\c4)^2,
 \a1*random(x,x^2),
 x^2+\a1
}
\integer{casv=random(1..4)}
\integer{casu=(\casv==3)?random(1..3):random(1..4)}

\function{num=item(\casu , \ulist)}
\function{deno=item(\casv , \vlist)}
\rational{vi = \casv<3 ?-\c4 / \c3}
\rational{vi = \casv==3 ?0}
\rational{vi = \casv==4 ?0}
\integer{novi=\casv==4?1:0}
\text{ensder=\(\,\RR),\(\RR \setminus\{\vi\})}
\integer{rep5=\casv==4?1:2}

\function{dernum=diff(\num,x)}
\function{derdeno=diff(\deno,x)}
\function{f= (\num)/(\deno)}
\function{derf=diff(\f,x)}
\function{facderf=maxima(factor(\derf))}
\function{denoder=maxima(expand(\dernum*\deno-\num*\derdeno))}
\integer{casf=randint(1..3)}
\text{numA=u'v + uv'}
\text{numB=u'v - uv'}
\text{denoA=v^2}
\text{form1=\(f' = \numA)}
\text{form2=\(f' = \numB)}
\text{form3=\(f' = \frac{\numB}{\denoA})}
\text{form4=\(f' = \frac{u'}{v'})}
\text{form5=\(f' = \frac{\numA}{\denoA})}
\text{formules=\casf==3?\form1,\form2,\form3,\form4,\form5}
\text{formules=\casf==2?\form1,\form3,\form2,\form4,\form5}
\text{formules=\casf==1?\form3,\form1,\form2,\form4,\form5}
\integer{rep6=\casf}

\steps{reply1,reply2,reply3,reply4
reply5, reply6
reply7}
\statement{
<div class="wims_question">
<p>
  \name_enonce[1]
 \if{\novi==1}{\(\,\RR\)}{\(\RR \setminus\{\vi \}\)} \name_enonce[2]
  \(f(x) = (\num)/(\deno)\).
</p><p>\name_enonce[3] \name_enonce[4]</p>
</div>
\if{\step==1}{
  <ul>
  <li>\name_question1 :
  <div class="wimscenter"><label for="reply1">\(u(x)\) =</label> \embed{reply1, 15}
   \name_and
  <label for="reply2">\(v(x) = \)</label> \embed{reply2, 15} </div>
  </li><li>\name_question2 \(\,\RR):
  <div class="wimscenter"><label for="reply3">\(u'(x)\) =</label>
    \embed{reply3, 15} \name_and
   <label for="reply4">\(v'(x) = \)</label> \embed{reply4, 15} </div>
  </li>}{
  <li>\(f = \frac{u}{v}\) \name_with:
  <div class="wimscenter"><p>\(u(x) = \num) \name_and \(u'(x) = \dernum\) </p>
  <p>\(v(x) = \deno \) \name_and \(v'(x) = \derdeno\) </p>
  </div>
</li>
}
\if{\step==2}{
  <li> \name_question3[1] \(f = \frac{u}{v}\) \name_question3[2]
  <div class="wimscenter">\embed{reply5}</div>
  </li><li>\name_question4:
<div class="wimscenter"> \embed{reply6}</div>
</li>}
\if{\step==3}{
<li>
\(f\) \name_question3[2] \if{\novi==1}{\RR}{\(\RR \setminus\{\vi \})}.
</li><li>
\name_question4: \form3
</li>
<li>\name_oneget :
<div class="wimscenter">\(f'(x)\) = \embed{reply7, 50}</div>
</li>}
</ul>
}
\answer{\name_answer[1] u (x) }{\num}{type=formal}
\answer{\name_answer[2] v (x) }{\deno}{type=formal}
\answer{\name_answer[3]: \(u'(x)\) }{\dernum}{type=formal}
\answer{\name_answer[4]: \(v'(x)\) }{\derdeno}{type=formal}
\answer{\name_answer[5]}{\rep5 ; \ensder}{type=radio}
\answer{\name_answer[6] }{\rep6 ; \formules}{type=radio}
\answer{\name_answer[7]: \(f'(x)\)}{\facderf}{type=formal}

\feedback{0==0}{<b>\name_feed[1]</b> \name_feed[2]
  \if{\novi!=1}{\name_feed[3] \(\vi)} \name_feed[4] &nbsp;
  \(f'(x) = \facderf\) &nbsp; (\name_feed[5]).
}
