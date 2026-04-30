target=droitespara2

\language{fr}
\range{-5..5}

\computeanswer{no}
\format{html}
\precision{10}
#include "author.inc"
#include "lang_titles.inc"
#include "lang.inc"
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
Dans un repère \((O,\vec{i},\vec{j})\) donné du plan,
on considère les quatre points :
<div class="wimscenter">\(A( \x1 ; \y1 )\), \(B(\x2 ; \y2)\), \(C( \x3 ; \y3)\), \(D( \x4 ; \y4)\)</div>
On se propose de déterminer si les droites \((A B)\) et \((C D)\) sont parallèles,
<b>par le calcul vectoriel</b>.
<ul><li>
Le vecteur \(\overrightarrow{A B}\) a pour coordonnées :
<label for="reply1">\(x\) =</label> \embed{reply1,5} et
<label for="reply2">\(y\) =</label> \embed{reply2,5}
</li><li>
Le vecteur \(\overrightarrow{C D}\) a pour coordonnées :
<label for="reply3">\(x'\) = \embed{reply3,5}</label>
et <label for="reply4">\(y'\) =</label> \embed{reply4,5}
</li><li>
Existe-t-il un réel \(k\) tel que
\(\overrightarrow{C D} = k\overrightarrow{A B}\) ?
<br>
<b>Si <span style="color:green">oui, donnez la valeur exacte de
<span class="tt">k</span></span> ,
<span style="color:red">sinon, entrez la valeur 0 </span></b>:
<div class="wimscenter"><label for="reply5">\(k \) = \embed{reply5,5} </label></div>
</li><li>
Les droites \((A B)\) et \((C D)\) sont donc \embed{reply6,10}.
</li>
</ul>
</div>
}
\answer{\name_answer[1] x}{\x}{type=default}
\answer{\name_answer[2] y}{\y}{type=default}
\answer{\name_answer[1] x'}{\X}{type=default}
\answer{\name_answer[2] y'}{\Y}{type=default}
\answer{\name_answer[3] k}{\repk}{type=default}
\answer{\name_answer[4]}{\ok;\name_choix}{type=menu}{option=shuffle}

\hint{Montrer que les droites \((A B)\) et \((C D)\) sont parallèles, équivaut à montrer que
les vecteurs \(\overrightarrow{A B}\) et \(\overrightarrow{C D}\) sont colinéaires.
<br>
Les vecteurs \(\overrightarrow{A B}\) et \(\overrightarrow{C D}\) sont colinéaires si et seulement si il existe un réel \(k\) tel que
\(\overrightarrow{C D} = k\overrightarrow{C D}\).
}

\feedback{0==0}{
<h2 class="small">\name_solution</h2>
Les vecteurs \(\overrightarrow{A B}\) et \(\overrightarrow{C D}\) ont pour coordonnées respectives :
\(\overrightarrow{A B}\left(\begin{array}{c} x=\x \\ y=\y \end{array}\right)\) et
\(\overrightarrow{C D}\left(\begin{array}{c} x'=\X \\ y'=\Y \end{array}\right)\).</p>
<p>Critère de colinéarité :
 <div class="wimscenter">
\( \overrightarrow{A B} =k\overrightarrow{C D} \Longleftrightarrow
\left|\begin{array}{c} x' = kx \\ y' = ky \end{array}\right.\)
\if{\y!=0}{
\(\Longleftrightarrow
\left|\begin{array}{c} k = \frac{\X}{\x} = \k1 \\ k = \frac{\Y}{\y} = \k2 \end{array}\right.\)}
{\(\Longleftrightarrow
\left|\begin{array}{c} k = \frac{\X}{\x} = \k1 \\ \Y=k\times\y \end{array}\right.\)}
</div>

\if{\ok==1}{Le système admet une solution : \(k = \repk\).}{Le système n'admet aucune solution.}
</p>

<p>Donc les vecteurs \(\overrightarrow{A B}\) et \(\overrightarrow{C D}\)
\if{\ok==1}{sont}{ne sont pas} colinéaires et les droites \((A B)\) et \((C D)\)\if{\ok==0}{sont donc}{ne sont donc pas} parallèles.
</p>
}
