target=derivarc

\language{fr}
\author{Chantal, Menini}
\format{html}
\computeanswer{yes}
#include "lang_titles.inc"
#include "lang.inc"
\range{1..5}
\text{a=randitem(2,3,sqrt(2),pi)}

\text{b=randitem((sqrt(2)),pi, (3/4), (1/3))}

\integer{f1=randint(1..3)}
\integer{f2=randint(1..2)}

\text{list1=arcsin(x),arccos(x),arctan(x)}
\text{dom1=\(\lbrack -1,1\rbrack\),
\(\rbrack -1,1\lbrack\),
\(\ \RR\),
\(\lbrack -\frac{\pi}{2},\frac{\pi}{2}\rbrack\),
\(\rbrack -\frac{\pi}{2},\frac{\pi}{2}\lbrack\),
\(\lbrack 0,\pi\rbrack\),
\(\rbrack 0,\pi\lbrack\)
}

\text{domc1=1,1,3}
\text{domd1= 2, 2, 3}

\text{list2=\a^x,x^\b}
\text{dom2=\(\mathbb R\),
\(\lbrack 0,+\infty\lbrack\),
\(\rbrack 0,+\infty\lbrack\)
}
\text{domc2= 1,3}
\text{domd2=1,3}

\text{A1=\list1[\f1]}
\text{aff1=texmath(\A1)}
\text{derive1=diff(\A1,x)}
\text{cont1=\domc1[\f1]}
\text{der1=\domd1[\f1]}

\text{A2=\list2[\f2]}
\text{aff2=texmath(\A2)}
\function{derive2=simplify(maxima(diff(\A2,x)))}
\text{cont2=\domc2[\f2]}
\text{der2=\domd2[\f2]}

\text{ETAPE = r1,r2,r3
r4,r5,r6}

\steps{\ETAPE}
\statement{
\if{\step=1}{
  \name_enonce[1;1] \(A\) \name_enonce[1;2]:
  <div class="wimscenter">\(A(x) = \aff1\)</div>
  <p>\name_enonce[2;]</p>
  <ul class="wims_nopuce spacer">
  \for{j=1 to 7}{<li>\embed{r1,\j}</li>}
 </ul>
<p>\name_enonce[3;]</p>
<ul class="wims_nopuce spacer">
\for{j=1 to 7}{<li>\embed{r2,\j}</li>}
 </ul>
  \name_enonce[4;1] \(A\)  \name_enonce[4;2]:
<div class="wimscenter"><label for="reply3">\(A'(x)\)=</label>\embed{r3}</div>
}
\if{\step=2}{
  \name_enonce[1;1] \(B\) \name_enonce[1;2]:
<div class="wimscenter">\(B(x) = \aff2)</div>
<p>\name_enonce[2;]</p>
<ul class="wims_nopuce spacer">
\for{j=1 to 3}{ <li>\embed{r4,\j}</li>}
 </ul>
<p>\name_enonce[3;]</p>
<ul class="wims_nopuce spacer">
\for{j=1 to 3}{<li>\embed{r5,\j}</li> }
 </ul>
  \name_enonce[4;1] \(B\)  \name_enonce[4;2]:
<div class="wimscenter"><label for="reply6">\(B'(x)\)</label>=\embed{r6}</div>
}
}

\answer{\name_answer[1] \name_of \A1 :}{\cont1;\dom1}{type=radio}{option=nonstop}
\answer{\name_answer[2] \name_of \A1 :}{\der1;\dom1}{type=radio}{option=nonstop}
\answer{\name_answer[3] \name_of \A1 : }{\derive1}{type=algexp}{option=nonstop}

\answer{\name_answer[1]}{\cont2;\dom2}{type=radio}{option=nonstop}
\answer{\name_answer[2]}{\der2;\dom2}{type=radio}{option=nonstop}
\answer{\name_answer[3]}{\derive2}{type=function}
