target=calcprio
#define NUM
#include "author.inc"
#include "lang_titles.inc"
\precision{10000}
#include "lang.inc"
\text{choix=random(1,2)}
\integer{a=randint(1,3,5,7,6,2)}
\integer{b=randint(4,5,11)}
\integer{c=randint(1,2,3,5)}
\integer{d=randint(4,7,9,8)}
\integer{e=randint(1,2,3,7)}
\integer{f=randint(5,10)}

\text{u= \frac{\a}{\b}+\frac{\c}{\d}}
\text{u=\choix=2? \u: (\u)}
\text{v=\frac{\e}{\f}}
\text{sol= \choix=2? item(1,\listechoix): item(2,\listechoix)}
\text{symb=\choix=2 ? +: \(\times)}
\text{symb2=\choix=2 ? +: \times}
\text{sol1= \choix=2? pari(numerator(\a/\b)): pari(numerator(\a/\b+\c/\d))}
\text{sol2= \choix=2? pari(denominator(\a/\b)): pari(denominator(\a/\b+\c/\d))}
\text{sol3= \choix=1? pari(numerator(\e/\f)): pari(numerator(\c*\e/(\d*\f)))}
\text{sol4= \choix=1? pari(denominator(\e/\f)): pari(denominator(\c*\e/(\d*\f)))}
\text{sol5= \choix=1? pari(numerator( (\a/\b+\c/\d)*(\e/\f))):
pari(numerator( \a/(\b)+(\c/(\d)*(\e/(\f)))))}
\text{sol6= \choix=1? pari(denominator( (\a/\b+\c/\d)*(\e/\f))):
pari(denominator( \a/(\b)+(\c/(\d)*(\e/(\f)))))}
\steps{choice 1
reply1, reply2,reply3,reply4
reply5, reply6}
\statement{\name_statement[1]
<div class="wimscenter">\(A=\u\times \v\) </div>
\name_statement[2]
<div>
\if{\step<=1}{\name_statement[3]? \embed{choice 1}.</div>
}
\if{\step=2}{\name_statement[4]:</div>
<table class="wimscenter"> <tr>
<td></td><td>\embed{reply 1, 3}</td><td></td><td>\embed{reply 3, 3}</td></tr>
<tr><td>\(\u\times \v =\)</td><td><hr></td><td> &nbsp;&nbsp;\symb &nbsp;&nbsp;</td><td><hr></td><tr>
<tr><td></td><td>\embed{reply 2, 3}</td><td></td><td>\embed{reply 4, 3}</td></tr>
</table>}
\if{\step=3}{ </p><table class="wimscenter"> <tr>
<td></td><td>\embed{reply 5, 3}</td></tr>
<tr><td>\(A =\frac{\sol1}{\sol2}\symb2\frac{\sol3}{\sol4}=\)</td><td><hr></td></tr>
<td></td><td>\embed{reply 6, 3}</td></tr>
</table>}
}

\choice{\name_answer}{\sol}{\listechoix}
\answer{}{\sol1}{type=numeric}
\answer{}{\sol2}{type=numeric}
\answer{}{\sol3}{type=numeric}
\answer{}{\sol4}{type=numeric}
\answer{}{\sol5}{type=numeric}
\answer{}{\sol6}{type=numeric}
