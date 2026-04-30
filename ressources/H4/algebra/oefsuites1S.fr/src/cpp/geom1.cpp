target=geom1
\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{n1=random(0..5)}
\integer{n2=\n1+random(1,2)}
\integer{n3=\n2+random(1,2)}
\integer{nr=random(1..9)*random(1,-1)}
\integer{nu1=random(-100..100)}
\integer{nu2=random(-100..100)}
\text{u1=\nu1}
\text{u2=\nu2}
\integer{v=random(0,1)}
\integer{nu2=\v=0?(\nu1)*(\nr)^(\n2-\n1)}
\text{u2=\nu2}
\rational{c1=(\nu2)/(\nu1)}
\rational{c2= (\nr)^(\n2-\n1)}
\if{\c1 ==\c2}{\integer{v=0}}
\integer{nu3=random(-10000..10000)}
\text{u3=\nu3}
\integer{v3= (\nu2)*(\nr)^((\n3)-(\n2))}
\integer{nu3=\v=0?\v3}
\text{u3=\nu3}
\integer{v=\nu3=\v3?0}
\text{b=\v=0?\name_yesno[1]:\name_yesno[2]}
\text{m=\v=0?\name_yesno[2]:\name_yesno[1]}
\text{size=\confparm1=1 ? :x-large}
\statement{
\name_enonce \( u \):
<table class="wimscenter wimsborder"><tr><th>n</th><td>\n1</td><td>\n2</td><td>\n3</td></tr>
<tr><th>\(u_n \)</th><td>\(\u1)</td><td>\(\u2\)</td><td>\(\u3\)</td></tr></table>
<p>
\name_question?
</p>
\name_answer: \embed{c1}
}

\choice{}{\b}{\m}
