target=deriverProduit

#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\format	{html}

\integer{a1=random(1..8)*random(1,-1)}
\integer{a2=random(1..8)*random(1,-1)}
\integer{c1=random(1..8)*random(1,-1)}
\integer{c2=random(1..8)*random(1,-1)}
\integer{c3=random(1..8)*random(1,-1)}
\integer{c4=random(1..8)*random(1,-1)}

\function{u=randitem(
 \a1*x+\a2,
 \a1*x^randint(2,3)
)}

\function{v=randitem(\c1*x^2+\c2*x+\c3,
\c3*x^2+random(\c4,\c4*x),
\c3*x+\c4)}

\function{f=(\u)(\v)}
\function{U=diff(\u,x)}
\function{V=diff(\v,x)}
\function{F=diff(\f,x)}
\function{factorF=maxima(factor(\F))}
\function{devF=maxima(expand(\F))}

\text{formule= \(f'=u'v+uv'\)}
\text{list= \(f'=u'v'\) , \formule, \(f'=u'v-uv'\)}
\text{choix=shuffle(\list)}
\integer{rep3=position(\formule,\choix)}
\statement{
<div class="wims_question">
<p>\name_question[1]
\name_question[2] \(\,\RR\) \name_question[3] \(f(x) = u(x) v(x)) \name_question[4]:</p>
<div class="wimscenter">\(u(x) = \u\)<br>\(v(x) = \v \)</div>
</div>

<p>\name_question1: </p>
<div class="wimscenter"><label for="reply1">\(u'(x)\)</label> = \embed{reply1,20} </div>
<div class="wimscenter"><label for="reply2">\(v'(x)\)</label> = \embed{reply2,20} </div>
<p><label for="reply3">\name_question2[1]:</label></p>
<div class="wimscenter">\embed{reply3}</div>
<p> \name_question2[2]:</p>
<div class="wimscenter"><label for="reply4">\(f'(x)\)</label> = \embed{reply4,30}</div>
}
\answer{\name_answer[1] \(u'(x)) }{\U}{type=formal}
\answer{\name_answer[1] \(v'(x)) }{\V}{type=formal}
\answer{\name_answer[2] }{\rep3;\choix}{type=checkbox}
\answer{\name_answer[1] \(f'(x)) }{\devF}{type=algexp}

\feedback{0==0}{<b>\name_sol[1]</b> <br>
\name_sol[2] \(\devF\).<br>
\name_sol[3] \(\factorF\).}
