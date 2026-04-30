target=factdir1

\language{fr}
\range{-5..5}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\computeanswer{no}
\format{html}
\precision{100}
\keywords{literal_calculation,factorization}
#include "style.inc"

\text{list=wims(values v,-v for v=1 to 13)}
\text{list=shuffle(\list)}
\integer{a=item(1,\list)}
\integer{b=item(2,\list)}
\integer{c=item(3,\list)}
\integer{d=item(4,\list)}
\integer{f=random(2..5)}
\integer{e=random(2..5)}
\integer{aa=(\a)^2}
\integer{bb=(\b)^2}
\integer{a2=\e*\a}
\integer{b2=\e*\b}

\text{s1=random(-,+)}
\text{s2=random(-,+)}
\text{s3=random(-,+)}
\text{s4=random(-,+)}
\integer{choix=random(1,2)}

\text{tt1=choix=1?(\a*x+\b)*(\c*x+\d):(\c*x+\d)*(\a*x+\b)}
\text{tt2=(\a*x+\b)^2}
\text{tt3=(\aa*x^2-\bb)}
\text{tt4=(\a2*x+\b2)}
\text{tt5=\f*x*(\a*x+\b)}
\text{termes=\tt1,\tt2,\tt3,\tt4,\tt5}
\text{stermes=shuffle(\termes)}
\text{t1=item(1,\stermes)}
\text{t2=item(2,\stermes)}
\integer{it1=position(\t1,\termes)}
\integer{it2=position(\t2,\termes)}
\text{alist=\c,\a,\a,0,\f}
\text{blist=\d,\b,-\b,\e,0}
\text{aaa1=item(\it1,\alist)}
\text{aaa2=item(\it2,\alist)}
\text{bbb1=item(\it1,\blist)}
\text{bbb2=item(\it2,\blist)}

\text{q=(\a*x+\b)*(\c*x+\d)\s1(\a*x+\b)^2\s2(\aa*x^2-\bb)\s3(\a2*x+\b2)\s4\f*x*(\a*x+\b)}
\text{ch11=texmath(\a*x+\b)}
\text{ch12=texmath(\c*x+\d)}
\text{ch13=texmath(\aa*x^2-\bb)}
\text{ch14=texmath(\a2*x+\b2)}
\text{ch15=texmath(\a*x-\b)}
\text{ch16=texmath(\f*x)}
\integer{aaa=\c\s1\a\s2(\a)\s4\f}
\integer{aaa=\aaa1\s1\aaa2}
\integer{bbb=\d\s1\b\s2(-\b)\s3\e}
\integer{bbb=\bbb1\s1\bbb2}
\text{bad1=\ch11,\ch12,\ch13,\ch14,\ch15,\ch16}
\text{good1=\ch11}
\text{good2=\ch12}
\text{good3=\ch11}
\text{good4=\ch15}
\text{good5=\e}
\text{good6=\ch16}
\text{good7=texmath(\aaa*x+\bbb)}
\text{lgood=\ch12,\ch11,\ch15,\e,\ch16}
\text{sgood2=item(\it1,\lgood)}
\text{sgood3=item(\it2,\lgood)}
\text{rep=(\good1)(\good7)}
\text{ans=maxima(expand((\a*x+\b)*(\aaa*x+\bbb)))}
\statement{\tintro
<div class="wimscenter"><span class="blue">\(\t1\)</span>
<span class="purple">\s1</span>
<span class="blue">\(\t2)</span>.
</div>
<div>
\name_expr: \embed{reply1,5}\(\times)\embed{reply2,5}.
</div>}

\answer{facteur 1}{\rep1}{type=function}
\answer{facteur 2}{\rep2}{type=function}
\text{ansel=maxima(expand(\rep1 * \rep2))}
\condition{\name_expr}{\ansel issametext \ans}
\solution{\name_solution[1] \((\good1)). \name_solution[2] \(\rep\).}
feedback{1=1}{\ansel : \ans}
