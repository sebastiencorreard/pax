target=tabpuis2
#include "lang_titles.inc"
\language{fr}
\range{-5..5}
#include "author.inc"
\computeanswer{no}
\format{html}
\precision{10000}
#include "lang.inc"
\integer{n=randint(2,3)}
\integer{m=randint(2,3)}
\integer{m=\m=\n? \m+1}
\integer{mn=\m*\n}
\integer{msn=\m+\n}
\integer{nn=\n^2}
\integer{mm=\m^2}
\integer{a=randint(2..5)*random(1,-1)}
\text{an=pari((\a)^\n)}
\text{am=pari((\a)^\m)}
\text{amn=pari((\a)^(\mn))}
\text{amsn=pari((\a)^(\msn))}
\text{ann=pari((\a)^(\nn))}
\text{amm=pari((\a)^(\mm))}
\statement{\name_statement:
<div class="unbreakable">
<table class="wimscenter wimsborder">
<tr>
<td>\(a\)</td>
<td><label for="reply1">\(a^\n\)</label></td>
<td><label for="reply2">\(a^\m\)</label></td>
<td><label for="reply3">\((a^\n)^\n\)</label></td>
<td><label for="reply4">\((a^\n)^\m\)</label></td>
<td><label for="reply5">\((a^\m)^\m\)</label></td>
<td><label for="reply6">\(a^\m a^\n\)</label></td>
<td><label for="reply7">\(a^\mn\)</label></td>
<td><label for="reply8">\(a^\nn\)</label></td>
<td><label for="reply9">\(a^\mm\)</label></td></tr>
<tr>
<td>\a</td>
<td>\embed{reply 1,6}</td>
<td>\embed{reply 2,6}</td>
<td>\embed{reply 3,6}</td>
<td>\embed{reply 4,6}</td>
<td>\embed{reply 5,6}</td>
<td>\embed{reply 6,6}</td>
<td>\embed{reply 7,6}</td>
<td>\embed{reply 8,6}</td>
<td>\embed{reply 9,6}</td>
</tr>
</table></div>
}
\answer{\(a^\n\)}{\an}{type=litexp}
\answer{\(a^\m\)}{\am}{type=litexp}
\answer{\((a^\n)^\n\)}{\ann}{type=litexp}
\answer{\((a^\n)^\m\)}{\amn}{type=litexp}
\answer{\((a^\m)^\m\)}{\amm}{type=litexp}
\answer{\(a^\m a^\n\)}{\amsn}{type=litexp}
\answer{\(a^\mn\)}{\amn}{type=litexp}
\answer{\(a^\nn\)}{\ann}{type=litexp}
\answer{\(a^\mm\)}{\amm}{type=litexp}
\feedback{\reply3 <>\reply8}{\name_warning \((a^\n)^\n = a^\nn\)}
\feedback{\reply4<>\reply7}{\name_warning \((a^\n)^\m = a^\mn\).}
\feedback{\reply5<>\reply9}{\name_warning \((a^\m)^\m = a^\mm\).}
\feedback{\reply6 = \reply7 and \mn<>4}{\name_feed}
