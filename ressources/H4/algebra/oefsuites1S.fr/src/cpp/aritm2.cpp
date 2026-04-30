target=aritm2

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10000}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
\integer{n1=random(0..5)}
\integer{n2=random(6..10)}
\integer{off1=\n2-\n1}
\integer{nr=random(1..9)*random(1,-1)}
\integer{qr=random(1..5)}
\integer{n3=random(10..100)}
\integer{nu1=random(-100..100)}
\integer{qu1=random(1..5)}
\integer{nu2=random(-100..100)}
\integer{qu2=random(1..5)}
\text{u1=simplify((\nu1)/(\qu1))}
\text{u2=simplify((\nu2)/(\qu2))}
\integer{v=random(0,1)}
\integer{w=\v}
\if{\v=0}{
  \text{u2=simplify((\nu1)/(\qu1)+(\n2-\n1)*(\nr)/(\qr))}
  \integer{nu2=\qr*(\nu1)+(\n2-\n1)*(\nr)*\qu1}
  \integer{qu2=\qr*\qu1}
}
\rational{c1=((\u2)-(\u1))*(\qr)}
\rational{c2= (\n2-\n1)*(\nr)}
\if{\c1 == \c2}{\integer{v=0}}
\integer{nu3=random(-100..100)}
\integer{qu3=random(1..5)}
\text{u3=simplify((\nu3)/(\qu3))}
\integer{n3=\v=0?\n1+random(2..6)*(\n2-\n1)}
\text{v3= simplify((\nu1)/(\qu1)+((\n3)-(\n1))*(\nr)/(\qr))}
\if{\v=0}{
\text{u3=\v3}
\integer{nu3=\qr*(\nu1)+(\n3-\n1)*(\nr)*\qu1}
\integer{qu3=\qr*\qu1}
}
\rational{c1=((\nu3)/(\qu3)-(\nu2)/(\qu2))*(\n2-\n1)}
\rational{c2=((\nu2)/(\qu2)-(\nu1)/(\qu1))*(\n3-\n2)}
\if{\c1 == \c2}{\integer{v=0}}{\integer{v=1}}
\text{b=\v=0?\name_yesno[1]:\name_yesno[2]}
\text{m=\v=0?\name_yesno[2]:\name_yesno[1]}
\text{u1=wims(replace internal / by , in \u1)}
\text{u1=items(\u1)=1?\u1:\frac{\u1[1]}{\u1[2]}}
\text{u2=wims(replace internal / by , in \u2)}
\text{u2=items(\u2)=1?\u2:\frac{\u2[1]}{\u2[2]}}
\text{u3=wims(replace internal / by , in \u3)}
\text{u3=items(\u3)=1?\u3:\frac{\u3[1]}{\u3[2]}}

\text{size=\confparm1=1 ? :x-large}
\statement{
\name_enonce \( u\) :
<table class="wimscenter wimsborder">
<tr><th>\(n\)</th><td>\n1</td><td>\n2</td><td>\n3</td></tr>
<tr><th>\(u_n\)</th><td>\(\u1\)</td><td>\(\u2\)</td><td>\(\u3\)</td></tr>
</table>
<p>
\name_question?
</p>
\name_answer: \embed{c1}
}

\choice{}{\b}{\m}
