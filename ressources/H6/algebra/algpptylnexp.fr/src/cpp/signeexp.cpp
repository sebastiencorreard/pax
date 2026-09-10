target=signeexp1
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"

\integer{a = (-1)^random(0,1)*random(1..4)}
\integer{b = random(-8..8)}
\rational{zero=-\b/\a}
\function{u=simplify(\a *x + \b)}
\integer{ a = random(-1,1)*random(1..4)}
\integer{ b = random(-8..8)}
\rational{ zero=-\b/\a}
\function{ u=\a *x + \b}
\function{ u=simplify(\u)}
\text{ sg1=\a>0?-:+}
\text{ sg2=\a>0?+:-}
\integer{ c = random(-1,1)*random(1..5)}
\integer{ d = random(-10..10)}
\function{ f = maxima((\u)*e^(\c*x+\d))}
\function{ e = maxima(e^(\c*x+\d))}
\function{ f1 = maxima(expand(\f))}
\integer{ a1 = random(-10..10)}
\integer{ b1 = random(-10..10)}
\integer{ a2 = \a - \a1}
\integer{ b2 = \b - \b1}
\integer{ a3 = \a + \a1}
\integer{ b3 = \b + \b1}
\function{ g = maxima((\a1*x + \b1)*e^(\c*x+\d))}
\function{ f2 = maxima((\a2*x + \b2)*e^(\c*x+\d))}
\function{ f3 = maxima((\a3*x + \b3)*e^(\c*x+\d))}
\integer{ cas = random(1..4)}
\function{ enonce = item(\cas,\f,\f1,\f2 + \g, \f3 -\g)}

\rational{rep1=-\b/\a}
\text{signes1=-,+,0}
\text{signes2=-,+,0}
\text{chges=-,+,0}
\text{rep2=\a>0?1:2}
\text{rep4=\a>0?2:1}
\text{rep3=3}
\statement{\name_enonce \(E(x) = \enonce\).
<table style="width:70%" class="wimsborder wimscenter">
<tr>
<td style="width:20%;"> \(x\)</td>
<td style="width:30%;text-align:left">\(-\infty)</td>
<td style="width:5%;">\embed{reply1,5}</td>
<td style="width:30%;text-align:right">\(+\infty)</td>
</tr><tr>
<td>\(E(x)\)</td>
<td>\embed{reply2} </td>
<td>\embed{reply3}</td>
<td>\embed{reply4}</td>
</tr>
</table>
}
\answer{}{\rep1}{type=rational}
\answer{}{\rep2 ; \signes1}{type=menu}
\answer{}{\rep3 ; \chges}{type=menu}
\answer{}{\rep4 ; \signes2}{type=menu}

\hint{\name_hint[1;] \(\e\). \name_hint[2;] \name_hint[3;] \(a x + b).}

\feedback{1=1}{<b>Justification</b> :
<br>L'expression \(E(x)) s'écrit sous forme factorisée :
\(E(x) = \f\).<br>
Le facteur \(\e\) étant toujours strictement positif,
\(E(x)\) est alors du signe du binôme (\u\).
}
