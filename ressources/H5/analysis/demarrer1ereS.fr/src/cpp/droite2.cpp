target=droite2

\language{fr}
\range{-5..5}
\computeanswer{no}
\format{html}
\precision{10}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
&&###Droites parallèles par les vecteurs

\integer{x1=random(-5..5)}
\integer{y1=random(-5..5)}
\integer{x3=random(-5..5)}
\integer{y3=random(-5..5)}
\integer{u=random(1..5)}
\integer{v=random(1..5)}
\integer{d1=random(1..2)}
\integer{d2=random(1..2)}
\integer{k2=random(1..4)}
\integer{k3=random(1..4)}
\integer{x2=\x1+\u*\k2*(-1)^\d1}
\integer{y2=\y1+\v*\k2*(-1)^\d1}

\integer{e1=random(0,1,1,0,0,0)}
\integer{e2=random(0,1,0,1,0,0)}

\integer{x4=\x3+\u*\k3*(-1)^\d2+\e1}
\integer{y4=\y3+\v*\k3*(-1)^\d2+\e2}
\integer{x=(\x2-\x1)}
\integer{y=(\y2-\y1)}
\integer{X=(\x4-\x3)}
\integer{Y=(\y4-\y3)}
\integer{d=\x*\Y-\y*\X}
\rational{repk=\d==0?\X/\x:0}
\rational{k1=\X/\x}
\rational{k2=\y!=0?\Y/\y}
\integer{ok=\d==0?1:2}
\statement{
<div style="background-color:#FFFF66">
\name_enonce1:
<div class="wimscenter">\(A( \x1 ; \y1 )\), \(B(\x2 ; \y2)\),
  \(C( \x3 ; \y3)\) et \(D( \x4 ; \y4)\).</div>
\name_enonce2.
<ul><li>
\name_question[1] \(\overrightarrow{A B}\) \name_question[2]:
<label for="reply1">\(x\) =</label> \embed{reply1,5} \name_and
<label for="reply2">\(y\) =</label> \embed{reply2,5}.
</li><li>
\name_question[1] \(\overrightarrow{C D}\) \name_question[2]:
<label for="reply3">\(x'\) =</label> \embed{reply3,5} et
<label for="reply4">\(y'\) =</label> \embed{reply4,5}.
</li><li>
\name_question[3]
\(\overrightarrow{C D} = k\overrightarrow{A B}\) ?
<div class="wims_instruction">\name_inst</div>
<div class="wimscenter"><label for="reply5">\(k \) =</label> \embed{reply5,5}.</div>
</li><li>
\name_question2 \embed{reply6,10}.
</li></ul>
</div>
}
\answer{\name_answer[1] x}{\x}{type=default}
\answer{\name_answer[2] y}{\y}{type=default}
\answer{\name_answer[1] x'}{\X}{type=default}
\answer{\name_answer[2] y'}{\Y}{type=default}
\answer{\name_answer[3] k}{\repk}{type=default}
\answer{\name_answer[4]}{\ok;\choix}{type=menu}{option=shuffle}
\hint{\name_hint1<br>
\name_hint2
\(\overrightarrow{CD} = k\overrightarrow{CD}\).
}

\feedback{0==0}{
<div style="color:blue">
<h3>Solution</h3>
<p>Les vecteurs \(\overrightarrow{AB}\) et \(\overrightarrow{CD}\)
ont pour coordonnées respectives :
\(\overrightarrow{AB}\left(\begin{array}{c} x=\x \\ y=\y \end{array}\right)\) et
\(\overrightarrow{CD}\left(\begin{array}{c} x'=\X \\ y'=\Y \end{array}\right)\).</p>

<p>Critère de colinéarité :</p>
 <div class="wimscenter">
\( \overrightarrow{AB} =k\overrightarrow{CD} \Longleftrightarrow
\left|\begin{array}{c} x' = k x \\ y' = k y \end{array}\right.\)
\if{\y!=0}{
\(\Longleftrightarrow
\left|\begin{array}{c} k = \frac{\X}{\x} = \k1 \\ k = \frac{\Y}{\y} = \k2 \end{array}\right.\)}
{\(\Longleftrightarrow
\left|\begin{array}{c} k = \frac{\X}{\x} = \k1 \\ \Y=k\times\y \end{array}\right.\)}
</div>
\if{\ok==1}{Le système admet une solution \(k = \repk\).}{
  Le système n'admet aucune solution.}
<p>Donc les vecteurs \(\overrightarrow{AB}\) et \(\overrightarrow{C D}\)
\if{\ok==1}{sont}{ne sont pas} colinéaires et les droites \((A B)\)
et \((CD)\)\if{\ok==0}{sont donc}{ne sont donc pas} parallèles.
</p>
</div>}
