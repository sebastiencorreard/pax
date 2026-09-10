target=ineqQuotient2
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{100}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
/** inéquation (x-b)/(x-c)<a/(x-c-d) **/
/** équivalente à (x^2-(c+2d)^2)/(x-c)(x-c-d) **/
\integer{c = random(1..5)}
\integer{d = random(1..5)}
\integer{b = -3*\c-4*\d}
\integer{a = 2*\c+3*\d}
\integer{e = \c + \d}
\integer{f = \c+2*\d}
\integer{f2 = \f^2}
\function{ u = x - \b}
\function{ v = x - \c}
\function{ w = x - \e}
\function{ Udev = x^2 - \f2 }
\function{ Ufact = (x - \f)(x+\f) }
\function{V = (\v)(\w)}
\function{q = (\Ufact) / (\V)}

\text{lsymb=<,>,\leq,\geq}
\text{symb=item(1,shuffle(\lsymb))}
\text{ ineq = (\u) / (\v) \symb (\a) / (\w) }

/** choix des intervalles **/

\text{I1of=&#93; -&#8734; &#44; -\f &#93; }
\text{I1oo= &#93; -&#8734; &#44; -\f &#91; }

\text{I2ff=&#91; -\f &#44; \c &#93; }
\text{I2oo=&#93; -\f &#44; \c &#91; }
\text{I2of=&#93; -\f &#44; \c &#93; }
\text{I2fo=&#91; -\f &#44; \c &#91; }

\text{I3ff=&#91; \c &#44; \e &#93; }
\text{I3oo=&#93; \c &#44; \e &#91; }
\text{I3of=&#93; \c &#44; \e &#93; }
\text{I3fo=&#91; \c &#44; \e &#91; }

\text{I4ff=&#91; \e &#44; \f &#93; }
\text{I4oo=&#93; \e &#44; \f &#91; }
\text{I4of=&#93; \e &#44; \f &#93; }
\text{I4fo=&#91; \e &#44; \f &#91; }

\text{I5fo=&#91; \f &#44; +&#8734; &#91; }
\text{I5oo= &#93; \f &#44; +&#8734; &#91; }

\text{choix=\I1oo,\I1of,\I2ff,\I2oo,\I2of,\I2fo,\I3ff,\I3oo,\I3of,\I3fo,\I4ff,\I4oo,\I4of,\I4fo,\I5fo,\I5oo}

\text{sol=(\symb issametext < )?4,12}
\text{sol=(\symb issametext \leq )?6,13}
\text{sol=(\symb issametext > )?1,8,16}
\text{sol=(\symb issametext \geq )?2,8,15}

\steps{reply1, reply2
reply3}

\statement{
<div class="wims_question">\name_question: \(\ineq\).</div>
<ol>
<li>
\if{\step==1}{
  \name_question2: \(\frac{u(x)}{(\v)(\w)} \symb 0\)
  <div class="wimscenter">\(u(x)) = \embed{reply1, 16} (\name_form[1]).</div>
  <div class="wimscenter">\(u(x)) = \embed{reply2, 16} (\name_form[2]).</div>
}{\name_enonce1 : \(\q) \(\symb 0\).}
</li>
\if{\step==2}{<li>\name_brouillon \( \q \).
  <br>
  \name_question3:
  <div class="wimscenter">
  <table class="tablesansbord">
  <tr>\for{k=1 to 2}{<td>\embed{reply3,\k}</td>}\for{k=15 to 16}{<td>\embed{reply3,\k}</td>}</tr>
  <tr>\for{k=3 to 6}{<td>\embed{reply3,\k}</td>}</tr>
  <tr>\for{k=7 to 10}{<td>\embed{reply3,\k}</td>}</tr>
  <tr>\for{k=11 to 14}{<td>\embed{reply3,\k}</td>}</tr>
  </table></div>
  </li>
}
</ol>
}
\answer{\expl1}{\Udev}{type=algexp}{option=nonstop}
\answer{\expl2}{\Ufact}{type=algexp}{option=nonstop}
\answer{}{\sol; \choix}{type=checkbox}
